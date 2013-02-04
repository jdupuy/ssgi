///////////////////////////////////////////////////////////////////////
// \file callbacks.cpp
// \author Jonathan Dupuy (onrendering@gmail.com)
// \brief main function
//
///////////////////////////////////////////////////////////////////////


// --------------------------------------------------------------------
// Includes
#include "callbacks.hpp"
#include "glu.hpp"
#include "AntTweakBar.h"
#include "Transform.hpp"


// --------------------------------------------------------------------
// macros / constants
#define GL_TEXTURE_MAX_ANISOTROPY_EXT          0x84FE
#define PI         3.14159265359f
#define WIDTH      1024
#define HEIGHT     700
#define ZNEAR      0.1f
#define ZFAR       5000.f


// names
enum {
	BUFFER_RANDOM = 0,
	BUFFER_COUNT,

	VERTEX_ARRAY_EMPTY = 0,
	VERTEX_ARRAY_COUNT,

	TEXTURE_ND = 0,
	TEXTURE_ALBEDO,
	TEXTURE_CORNELL,
	TEXTURE_COUNT,

	RENDERBUFFER_DEPTH = 0,
	RENDERBUFFER_COUNT,

	FRAMEBUFFER_ND = 0,
	FRAMEBUFFER_COUNT,

	PROGRAM_CORNELL = 0,
	PROGRAM_SSGI,
	PROGRAM_COUNT,

	LOCATION_CORNELL_MVP = 0,
	LOCATION_CORNELL_MV,
	LOCATION_CORNELL_EYE,
	LOCATION_CORNELL_PLANES,
	LOCATION_CORNELL_SKY,
	LOCATION_SSGI_ND,
	LOCATION_SSGI_ALBEDO,
	LOCATION_SSGI_SCREENSIZE,
	LOCATION_SSGI_LIGHTDIR,
	LOCATION_COUNT,

	UNIFORM_BINDING_RANDOM = 0,
	UNIFORM_BINDING_COUNT
};


// --------------------------------------------------------------------
// global variables

// opengl names
std::vector<GLuint> vertexArrays(VERTEX_ARRAY_COUNT);
std::vector<GLuint> renderbuffers(RENDERBUFFER_COUNT);
std::vector<GLuint> textures(TEXTURE_COUNT);
std::vector<GLuint> buffers(BUFFER_COUNT);
std::vector<GLuint> framebuffers(FRAMEBUFFER_COUNT);
std::vector<GLuint> programs(PROGRAM_COUNT);

// uniform locations
std::vector<GLint> locations(LOCATION_COUNT);

// camera transformations
Affine cameraFrame(Affine::Translation(Vector3(0,0,-1000)));

// cursor
GLint prevX(0), prevY(0);
bool leftButton(false), rightButton(false);

// visualisation
bool wireframe(false);


// --------------------------------------------------------------------
// callbacks
static GLvoid load_buffers();
static GLvoid load_programs();
static GLvoid load_textures();
static GLvoid load_renderbuffers();
static GLvoid load_framebuffers();
static GLvoid setup_hud();
// gui callbacks
template<typename T>
static GLvoid TW_CALL get_t(GLvoid *value, GLvoid *clientData);


// --------------------------------------------------------------------
// on_init
GLvoid on_init(GLint argc, GLchar **argv) {
	// set up debug output
	glu::init_gl_debug_output();

	// vertex arrays
	glGenVertexArrays(VERTEX_ARRAY_COUNT, &vertexArrays[0]);
	glBindVertexArray(vertexArrays[VERTEX_ARRAY_EMPTY]);
	glBindVertexArray(0);

	// renderbuffers
	glGenRenderbuffers(RENDERBUFFER_COUNT, &renderbuffers[0]);
	load_renderbuffers();

	// textures
	glGenTextures(TEXTURE_COUNT, &textures[0]);
	load_textures();

	// buffers
	glGenBuffers(BUFFER_COUNT, &buffers[0]);
	load_buffers();

	// framebuffers
	glGenFramebuffers(FRAMEBUFFER_COUNT, &framebuffers[0]);
	load_framebuffers();

	// programs
	load_programs();

	// set up hud
	setup_hud();

	// set state
	glClearColor(1.0,0.0,0.0,0.0);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_CULL_FACE);
	glPatchParameteri(GL_PATCH_VERTICES,4);
	glBindVertexArray(vertexArrays[VERTEX_ARRAY_EMPTY]);
}


// --------------------------------------------------------------------
// on_display
GLvoid on_display() {
	// build matrices
	Matrix4x4 mvp = Matrix4x4::Perspective(PI*0.35f,
	                                       WIDTH/GLfloat(HEIGHT),
	                                       ZNEAR,
	                                       ZFAR)
	              * cameraFrame.ExtractTransformMatrix();
	Matrix3x3 rot = cameraFrame.GetUnitAxis();
	Vector3 eye   = rot.Transpose() * -cameraFrame.GetPosition();
	Vector3 light = rot * Vector3(1,2,1);
	light = light.Normalize();

	// update mvp TODO: use UBO and buffer streaming
	glProgramUniformMatrix4fv(programs[PROGRAM_CORNELL],
	                          locations[LOCATION_CORNELL_MVP],
	                          1, GL_FALSE, &mvp[0][0]);
	glProgramUniformMatrix3fv(programs[PROGRAM_CORNELL],
	                          locations[LOCATION_CORNELL_MV],
	                          1, GL_FALSE, &rot[0][0]);
	glProgramUniform3fv(programs[PROGRAM_CORNELL],
	                    locations[LOCATION_CORNELL_EYE],
	                    1, &eye[0]);
	glProgramUniform3fv(programs[PROGRAM_SSGI],
	                    locations[LOCATION_SSGI_LIGHTDIR],
	                    1, &light[0]);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[FRAMEBUFFER_ND]);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glUseProgram(programs[PROGRAM_CORNELL]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);
	glDisable(GL_DEPTH_TEST);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glUseProgram(programs[PROGRAM_SSGI]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//	glBlitFramebuffer(0,0,WIDTH,HEIGHT,
//	                  0,0,WIDTH,HEIGHT,
//	                  GL_COLOR_BUFFER_BIT,
//	                  GL_NEAREST);

	// draw gui
	TwDraw();

	// swap buffers
	glu::sleep(25);
	glutSwapBuffers();
	glutPostRedisplay();
}


// --------------------------------------------------------------------
// on_resize
GLvoid on_resize(GLint w, GLint h) {
	glutReshapeWindow(WIDTH, HEIGHT); // disable resizing
}


// --------------------------------------------------------------------
// on_keypress
GLvoid on_keypress(GLubyte key, GLint x, GLint y) {
	if(1==TwEventKeyboardGLUT(key, x, y))
		return;
	switch(key) {
		case 'r': load_programs(); break; // reload programs
		case 'w': wireframe = !wireframe; break; // wireframe
		case 'p': glu::save_gl_front_buffer(0,0,WIDTH,HEIGHT); break; // screenshot
		default: break;
	};
}


// --------------------------------------------------------------------
// on_keyrelease
GLvoid on_keyrelease(GLubyte key, GLint x, GLint y) {

}


// --------------------------------------------------------------------
// on_mousebutton
GLvoid on_mousebutton(GLint button, GLint state, GLint x, GLint y) {
	if(1 == TwEventMouseButtonGLUT(button, state, x, y))
		return;

	if(button==GLUT_LEFT_BUTTON)
		leftButton = state==GLUT_DOWN;
	if(button==GLUT_RIGHT_BUTTON)
		rightButton = state==GLUT_DOWN;

	if(button==3)
		cameraFrame.TranslateWorld(Vector3(0,0,+1));
	if(button==4)
		cameraFrame.TranslateWorld(Vector3(0,0,-1));
}


// --------------------------------------------------------------------
// on_mousemotion
GLvoid on_mousemotion(GLint x, GLint y) {
	if(1 == TwEventMouseMotionGLUT(x,y))
		return;
	GLint xrel(x-prevX), yrel(y-prevY);

	if(leftButton) {
		cameraFrame.RotateAboutWorldX(-yrel*0.01f);
		cameraFrame.RotateAboutLocalY(-xrel*0.02f);
	}
	if (rightButton) {
		cameraFrame.TranslateWorld(Vector3(0,0,xrel*0.8f));
	}

	prevX = x;
	prevY = y;
}


// --------------------------------------------------------------------
// on_mousemotion
GLvoid on_mousepassivemotion(GLint x, GLint y) {
	if(1 == TwEventMouseMotionGLUT(x,y))
		return;
	prevX = x;
	prevY = y;
}


// --------------------------------------------------------------------
// on_mousemotion
GLvoid on_mousewheel(GLint wheel, GLint direction, GLint x, GLint y) {
	if(1 == TwMouseWheel(wheel))
		return;
}


// --------------------------------------------------------------------
// on_exit
GLvoid on_exit() {
	LOG("Cleaning up...");
	TwTerminate();
	for(GLint i=0; i<PROGRAM_COUNT; ++i)
		glDeleteProgram(programs[i]);
	glDeleteFramebuffers(FRAMEBUFFER_COUNT, &framebuffers[0]);
	glDeleteBuffers(BUFFER_COUNT, &buffers[0]);
	glDeleteTextures(TEXTURE_COUNT, &textures[0]);
	glDeleteRenderbuffers(RENDERBUFFER_COUNT, &renderbuffers[0]);
	glDeleteVertexArrays(VERTEX_ARRAY_COUNT, &vertexArrays[0]);
}


// ====================================================================
// Window configuration callback
GLvoid set_window_params(WindowParams &windowParams) {
	windowParams.width  = WIDTH;
	windowParams.height = HEIGHT;
	windowParams.major  = 4;
	windowParams.minor  = 2;
	windowParams.glutDisplayMode = GLUT_RGBA /*| GLUT_DEPTH*/ | GLUT_DOUBLE;
}


// ====================================================================
// load programs
static GLvoid load_programs() {
	const std::string SHADER_DIR("../../src/shaders/");

	// cleanup
	if(glIsProgram(programs[0]))
		for(GLint i=0; i<PROGRAM_COUNT; ++i)
			glDeleteProgram(programs[i]);

	// gen
	for(GLint i=0; i<PROGRAM_COUNT; ++i)
		programs[i] = glCreateProgram();

	// load
//	std::string options = geomOptStr[geometry];
//	options+= cubemap == TEXTURE_GRACE ? "#define _SKY_GRACE\n" : "";
	glu::load_glsl_program(programs[PROGRAM_CORNELL],
	                       SHADER_DIR+std::string("cornell.glsl"),
	                       "",
	                       GL_TRUE);
	glu::load_glsl_program(programs[PROGRAM_SSGI],
	                       SHADER_DIR+std::string("ssgi.glsl"),
	                       "",
	                       GL_TRUE);

	// save uniform locations
	locations[LOCATION_CORNELL_MVP]
		= glGetUniformLocation(programs[PROGRAM_CORNELL],"uModelViewProjection");
	locations[LOCATION_CORNELL_MV]
		= glGetUniformLocation(programs[PROGRAM_CORNELL],"uModelView");
	locations[LOCATION_CORNELL_EYE]
		= glGetUniformLocation(programs[PROGRAM_CORNELL],"uEyePos");
	locations[LOCATION_CORNELL_PLANES]
		= glGetUniformLocation(programs[PROGRAM_CORNELL],"uPlanes");
	locations[LOCATION_CORNELL_SKY]
		= glGetUniformLocation(programs[PROGRAM_CORNELL],"sSky");
	locations[LOCATION_SSGI_SCREENSIZE]
		= glGetUniformLocation(programs[PROGRAM_SSGI],"uScreenSize");
	locations[LOCATION_SSGI_LIGHTDIR]
		= glGetUniformLocation(programs[PROGRAM_SSGI],"uLightDir");
	locations[LOCATION_SSGI_ND]
		= glGetUniformLocation(programs[PROGRAM_SSGI],"sNd");
	locations[LOCATION_SSGI_ALBEDO]
		= glGetUniformLocation(programs[PROGRAM_SSGI],"sKa");

	// set constants
	glProgramUniform1i(programs[PROGRAM_CORNELL],
	                   locations[LOCATION_CORNELL_SKY],
	                   TEXTURE_CORNELL);
	glProgramUniform2f(programs[PROGRAM_CORNELL],
	                   locations[LOCATION_CORNELL_PLANES],
//	                   ZNEAR, ZFAR);
	                   1.f/(ZFAR-ZNEAR), -ZNEAR/(ZFAR-ZNEAR));
	glProgramUniform1i(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_ND],
	                   TEXTURE_ND);
	glProgramUniform1i(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_ALBEDO],
	                   TEXTURE_ALBEDO);
	glProgramUniform2f(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_SCREENSIZE],
	                   WIDTH,HEIGHT);
}


// ====================================================================
// load textures
static GLvoid load_textures() {
	const std::string TEXTURE_DIR("../../textures/");
	glActiveTexture(GL_TEXTURE0+TEXTURE_CORNELL);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textures[TEXTURE_CORNELL]); {
		glu::TexImageRgba4ub red  (64,64,1,255,0,0,255);
		glu::TexImageRgba4ub green(64,64,1,0,255,0,255);
		glu::TexImageRgba4ub white(64,64,1,255,255,255,255);
		glu::TexImageArray array;
		array.push_back(&green); // xpos
		array.push_back(&red);   // xneg
		array.push_back(&white);
		array.push_back(&white);
		array.push_back(&white);
		array.push_back(&white);
		glu::load_texture_cube_map(array, GL_RGBA8, GL_TRUE, GL_FALSE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,
		                GL_TEXTURE_MIN_FILTER,
		                GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,
		                GL_TEXTURE_MAG_FILTER,
		                GL_LINEAR);
		glTexParameterf(GL_TEXTURE_CUBE_MAP,
		                GL_TEXTURE_MAX_ANISOTROPY_EXT,
		                16.0f);
	}
	glActiveTexture(GL_TEXTURE0+TEXTURE_ND);
	glBindTexture(GL_TEXTURE_RECTANGLE, textures[TEXTURE_ND]);
		glTexStorage2D(GL_TEXTURE_RECTANGLE,
		               1,
		               GL_RGBA16,
		               WIDTH,
		               HEIGHT);
		glTexParameteri(GL_TEXTURE_RECTANGLE,
		                GL_TEXTURE_MIN_FILTER,
		                GL_LINEAR);
		glTexParameteri(GL_TEXTURE_RECTANGLE,
		                GL_TEXTURE_MAG_FILTER,
		                GL_LINEAR);
	glActiveTexture(GL_TEXTURE0+TEXTURE_ALBEDO);
	glBindTexture(GL_TEXTURE_RECTANGLE, textures[TEXTURE_ALBEDO]);
		glTexStorage2D(GL_TEXTURE_RECTANGLE,
		               1,
		               GL_RGB8,
		               WIDTH,
		               HEIGHT);
		glTexParameteri(GL_TEXTURE_RECTANGLE,
		                GL_TEXTURE_MIN_FILTER,
		                GL_LINEAR);
		glTexParameteri(GL_TEXTURE_RECTANGLE,
		                GL_TEXTURE_MAG_FILTER,
		                GL_LINEAR);
}


// ====================================================================
// setup renderbuffers
static GLvoid load_renderbuffers() {
	glBindRenderbuffer(GL_RENDERBUFFER,
	                   renderbuffers[RENDERBUFFER_DEPTH]);
		glRenderbufferStorage(GL_RENDERBUFFER,
		                      GL_DEPTH_COMPONENT24,
		                      WIDTH,
		                      HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}


// ====================================================================
// setup framebuffers
static GLvoid load_framebuffers() {
	const GLenum drawBuffers[]={GL_COLOR_ATTACHMENT0, 
	                            GL_COLOR_ATTACHMENT1};
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[FRAMEBUFFER_ND]);
		glFramebufferTexture2D(GL_FRAMEBUFFER,
		                       GL_COLOR_ATTACHMENT0,
		                       GL_TEXTURE_RECTANGLE,
		                       textures[TEXTURE_ND],
		                       0);
		glFramebufferTexture2D(GL_FRAMEBUFFER,
		                       GL_COLOR_ATTACHMENT1,
		                       GL_TEXTURE_RECTANGLE,
		                       textures[TEXTURE_ALBEDO],
		                       0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER,
		                          GL_DEPTH_ATTACHMENT,
		                          GL_RENDERBUFFER,
		                          renderbuffers[RENDERBUFFER_DEPTH]);
		glDrawBuffers(2, drawBuffers);
	ASSERT(glu::check_gl_framebuffer_complete()
		       &&  "Invalid framebuffer configuration" );
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


// ====================================================================
// setup buffers
static GLvoid load_buffers() {
	glBindBuffer(GL_UNIFORM_BUFFER, buffers[BUFFER_RANDOM]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

// ====================================================================
// setup hud
static GLvoid setup_hud() {
	// start ant
	TwInit(TW_OPENGL_CORE, NULL);
	TwGLUTModifiersFunc(glutGetModifiers); // GLUT specific
	TwWindowSize(WIDTH, HEIGHT);

	TwBar* hud = TwNewBar("HUD");
	TwDefine("HUD size='198 285'");
	TwDefine("HUD position='16 16'");
	TwDefine("HUD alpha='90'");
	TwDefine("HUD color='0 0 0'");
	TwDefine("HUD text='light'");
	TwDefine("HUD valueswidth=64");

//	TwEnumVal geometryEV[] = {
//		{GEOMETRY_SPHERE,      "Sphere"     },
//		{GEOMETRY_TORUS,       "Torus"      },
//		{GEOMETRY_SHELL,       "Shell"      },
//		{GEOMETRY_KLEINBOTTLE, "Kleinbottle"}
//	};
//	TwType geometryType= TwDefineEnum("Geometry", geometryEV, 4);
//	TwAddVarCB(hud,
//	           "Geometry",
//	           geometryType,
//	           &set_geometry,
//	           &get_t<GLint>,
//	           &geometry,
//	           "help='Change geometry.' group='Scene' ");
}


// ====================================================================
// gui callbacks
template<typename T>
static inline GLvoid TW_CALL get_t(GLvoid *value, GLvoid *clientData) {
	*reinterpret_cast<T*>(value) = 
		*reinterpret_cast<T*>(clientData);
}

