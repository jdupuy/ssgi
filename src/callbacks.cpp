///////////////////////////////////////////////////////////////////////
// \file callbacks.cpp
// \author Jonathan Dupuy (onrendering@gmail.com)
// \brief main callbacks
//
///////////////////////////////////////////////////////////////////////


// --------------------------------------------------------------------
// Includes
#include "callbacks.hpp"
#include "glu.hpp"
#include "AntTweakBar.h"
#include "Transform.hpp"
#include <cmath>


// --------------------------------------------------------------------
// macros / constants
#define GL_TEXTURE_MAX_ANISOTROPY_EXT          0x84FE
#define PI          3.14159265359f
#define WIDTH       1024
#define HEIGHT      700
#define ZNEAR       0.1f
#define ZFAR        3000.f
#define SAMPLE_CNT  32
const GLfloat FOVY  = PI*0.35f;
const GLfloat RATIO = GLfloat(WIDTH)/GLfloat(HEIGHT);

// names
enum {
	BUFFER_SAMPLES = 0,
	BUFFER_COUNT,

	VERTEX_ARRAY_EMPTY = 0,
	VERTEX_ARRAY_COUNT,

	TEXTURE_ND = 0,
	TEXTURE_ALBEDO,
	TEXTURE_CORNELL,
	TEXTURE_NOISE,
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
	LOCATION_SSGI_NOISE,
	LOCATION_SSGI_SCREENSIZE,
	LOCATION_SSGI_LIGHTPOS,
	LOCATION_SSGI_TANFOV,
	LOCATION_SSGI_CLIPZ,
	LOCATION_SSGI_SAMPLECNT,
	LOCATION_SSGI_SAMPLES,
	LOCATION_SSGI_RADIUS,
	LOCATION_SSGI_GIBOOST,
	LOCATION_COUNT,

	UNIFORM_BINDING_SAMPLES = 0,
	UNIFORM_BINDING_COUNT,

	GI_NONE = 0,
	GI_SSAO,
	GI_SSDO,
	GI_COUNT
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
GLint sampleCnt(8);   // samples per pixel
GLint giMode(GI_NONE); // global illum mode
GLfloat radius(3.0f); // radius size
GLfloat giBoost(1.0f); // gi boost
bool rotate(true);   // rotate scene;


// --------------------------------------------------------------------
// callbacks
static GLvoid load_buffers();
static GLvoid load_programs();
static GLvoid load_textures();
static GLvoid load_renderbuffers();
static GLvoid load_framebuffers();
static GLvoid setup_hud();

// gui callbacks
static GLvoid TW_CALL gen_samples(GLvoid *twSatisfy);
static GLvoid TW_CALL set_sample_count(const GLvoid *value, GLvoid *clientData);
static GLvoid TW_CALL set_radius(const GLvoid *value, GLvoid *clientData);
static GLvoid TW_CALL set_boost(const GLvoid *value, GLvoid *clientData);
static GLvoid TW_CALL set_gi(const GLvoid *value, GLvoid *clientData);
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
	glClearColor(0.0,0.0,0.0,1.0);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_CULL_FACE);
	glPatchParameteri(GL_PATCH_VERTICES,4);
	glBindVertexArray(vertexArrays[VERTEX_ARRAY_EMPTY]);
}


// --------------------------------------------------------------------
// on_display
GLvoid on_display() {
	// build matrices
	static GLfloat t = 0.0f;
	t = fmod(t+0.025f, 2.0*PI);
	Matrix4x4 mv = cameraFrame.ExtractTransformMatrix();
	Matrix4x4 mvp = Matrix4x4::Perspective(FOVY,RATIO,ZNEAR,ZFAR) 
	              * mv;
	Matrix3x3 rot = cameraFrame.GetUnitAxis();
	Vector3 eye   = rot.Transpose() * -cameraFrame.GetPosition();
	Vector4 light = rotate ? mv*Vector4(cos(t)*450.0,0,sin(t)*450.0,1)
	                       : mv*Vector4(0,0,0,1);

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
	                    locations[LOCATION_SSGI_LIGHTPOS],
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
	std::ostringstream c;
	c << SAMPLE_CNT;
	std::string ssgiOpt("#define SAMPLE_CNT "+c.str()+'\n');
	if(giMode==GI_SSAO)
		ssgiOpt+= "#define GI_SSAO\n";
	else if(giMode==GI_SSDO)
		ssgiOpt+= "#define GI_SSDO\n";

	// cleanup
	if(glIsProgram(programs[0]))
		for(GLint i=0; i<PROGRAM_COUNT; ++i)
			glDeleteProgram(programs[i]);

	// gen
	for(GLint i=0; i<PROGRAM_COUNT; ++i)
		programs[i] = glCreateProgram();

	// load
	glu::load_glsl_program(programs[PROGRAM_CORNELL],
	                       SHADER_DIR+std::string("cornell.glsl"),
	                       "",
	                       GL_TRUE);
	glu::load_glsl_program(programs[PROGRAM_SSGI],
	                       SHADER_DIR+std::string("ssgi.glsl"),
	                       ssgiOpt,
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
	locations[LOCATION_SSGI_LIGHTPOS]
		= glGetUniformLocation(programs[PROGRAM_SSGI],"uLightPos");
	locations[LOCATION_SSGI_TANFOV]
		= glGetUniformLocation(programs[PROGRAM_SSGI],"uTanFovs");
	locations[LOCATION_SSGI_CLIPZ]
		= glGetUniformLocation(programs[PROGRAM_SSGI],"uClipZ");
	locations[LOCATION_SSGI_SAMPLECNT]
		= glGetUniformLocation(programs[PROGRAM_SSGI],"uSampleCnt");
	locations[LOCATION_SSGI_RADIUS]
		= glGetUniformLocation(programs[PROGRAM_SSGI],"uRadius");
	locations[LOCATION_SSGI_GIBOOST]
		= glGetUniformLocation(programs[PROGRAM_SSGI],"uGiBoost");
	locations[LOCATION_SSGI_ND]
		= glGetUniformLocation(programs[PROGRAM_SSGI],"sNd");
	locations[LOCATION_SSGI_ALBEDO]
		= glGetUniformLocation(programs[PROGRAM_SSGI],"sKa");
	locations[LOCATION_SSGI_NOISE]
		= glGetUniformLocation(programs[PROGRAM_SSGI],"sNoise");
	locations[LOCATION_SSGI_SAMPLES]
		= glGetUniformBlockIndex(programs[PROGRAM_SSGI],"Samples");

	// set constants
	glProgramUniform1i(programs[PROGRAM_CORNELL],
	                   locations[LOCATION_CORNELL_SKY],
	                   TEXTURE_CORNELL);
	glProgramUniform2f(programs[PROGRAM_CORNELL],
	                   locations[LOCATION_CORNELL_PLANES],
//	                   ZNEAR, ZFAR);
	                   1.f/(ZFAR-ZNEAR), -ZNEAR/(ZFAR-ZNEAR));
	glProgramUniform2f(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_SCREENSIZE],
	                   WIDTH,HEIGHT);
	glProgramUniform2f(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_TANFOV],
	                   tan(FOVY*RATIO*0.5f),tan(FOVY*0.5f));
	glProgramUniform2f(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_CLIPZ],
	                   ZFAR-ZNEAR,+ZNEAR);
	glProgramUniform1i(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_SAMPLECNT],
	                   sampleCnt);
	glProgramUniform1f(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_RADIUS],
	                   radius);
	glProgramUniform1f(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_GIBOOST],
	                   giBoost);
	glProgramUniform1i(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_ND],
	                   TEXTURE_ND);
	glProgramUniform1i(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_ALBEDO],
	                   TEXTURE_ALBEDO);
	glProgramUniform1i(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_NOISE],
	                   TEXTURE_NOISE);
	glUniformBlockBinding(programs[PROGRAM_SSGI],
	                      locations[LOCATION_SSGI_SAMPLES],
	                      UNIFORM_BINDING_SAMPLES);
}


// ====================================================================
// load textures
static GLvoid load_textures() {
	const std::string TEXTURE_DIR("../../textures/");
	glActiveTexture(GL_TEXTURE0+TEXTURE_CORNELL);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textures[TEXTURE_CORNELL]); {
		glu::TexImageRgba4ub red  (256,256,1,255,0,0,255);
		glu::TexImageRgba4ub green(256,256,1,0,255,0,255);
		glu::TexImageRgba4ub white(256,256,1,255,255,255,255);
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
	glActiveTexture(GL_TEXTURE0+TEXTURE_NOISE);
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_NOISE]);
		glTexStorage2D(GL_TEXTURE_2D,
		               1,
		               GL_RGB8,
		               64,64);
	{
		std::vector<GLint> noise(64*64);
		for(GLint i=0;i<64*64;++i) {
			GLubyte r1 = GLubyte(glu::random(0,255));
			GLubyte r2 = GLubyte(glu::random(0,255));
			GLubyte r3 = GLubyte(glu::random(0,255));
			noise[i] = r1 | r2 << 8 | r3 << 16;
		}
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 64, 64, 
		                GL_RGBA, GL_UNSIGNED_BYTE, &noise[0]);
	}
		glTexParameteri(GL_TEXTURE_2D,
		                GL_TEXTURE_MIN_FILTER,
		                GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,
		                GL_TEXTURE_MAG_FILTER,
		                GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,
		                GL_TEXTURE_WRAP_S,
		                GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,
		                GL_TEXTURE_WRAP_T,
		                GL_REPEAT);
	glActiveTexture(GL_TEXTURE0); // for ant ?
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
	glBindBuffer(GL_UNIFORM_BUFFER, buffers[BUFFER_SAMPLES]);
		glBufferData(GL_UNIFORM_BUFFER,
		             sizeof(Vector4)*SAMPLE_CNT,
		             NULL,
		             GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 
	                 UNIFORM_BINDING_SAMPLES,
	                 buffers[BUFFER_SAMPLES]);
	gen_samples(NULL);
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

	TwAddButton(hud,
	            "Gen samples",
	            &gen_samples,
	            NULL,
	            "group= SSGI help='Generate new samples'");
	TwAddVarCB(hud,
	           "Sample count",
	           TW_TYPE_INT32,
	           &set_sample_count,
	           &get_t<GLint>,
	           &sampleCnt,
	           "group='SSGI' \
	            min=1 max=32 \
	            help='Number of samples per pixel.'");
	TwAddVarCB(hud,
	           "Radius",
	           TW_TYPE_FLOAT,
	           &set_radius,
	           &get_t<GLfloat>,
	           &radius,
	           "group='SSGI' \
	            min=0.1 max=128 \
	            help='Radius.'");
	TwAddVarCB(hud,
	           "Boost",
	           TW_TYPE_FLOAT,
	           &set_boost,
	           &get_t<GLfloat>,
	           &giBoost,
	           "group='SSGI' \
	            min=0.1 max=128 \
	            help='Boost GI.'");
	TwAddVarRW(hud, 
	           "Rotate light",
	           TW_TYPE_BOOLCPP,
	           &rotate,
	           "true=ON false=OFF");

	TwEnumVal giEV[] = {
		{GI_NONE, "None"  },
		{GI_SSAO, "SSAO" },
		{GI_SSDO, "SSDO" }
	};
	TwType giMethod= TwDefineEnum("Gi", giEV, 3);
	TwAddVarCB(hud,
	           "GI method",
	           giMethod,
	           &set_gi,
	           &get_t<GLint>,
	           &giMode,
	           "help='Global illum method.' group='SSGI' ");
}


// ====================================================================
// gui callbacks
static GLvoid TW_CALL gen_samples(GLvoid *twSatisfy) {
	std::vector<Vector4> samples(SAMPLE_CNT);
	for(GLint i=0; i<SAMPLE_CNT; ++i) {
		Vector3 dir = Vector3(glu::random(-1.0,1.0),
		                      glu::random(-1.0,1.0),
		                      glu::random(-1.0,1.0)).Normalize();
		samples[i] = glu::random(1e-5,1.0)*Vector4(dir[0],dir[1],dir[2],1.0);
	}
	glBindBuffer(GL_UNIFORM_BUFFER, buffers[BUFFER_SAMPLES]);
		Vector4 *p = reinterpret_cast<Vector4 *>
			(glMapBuffer(GL_UNIFORM_BUFFER,GL_WRITE_ONLY));
		memcpy(p, &samples[0], SAMPLE_CNT*sizeof(Vector4));
		glUnmapBuffer(GL_UNIFORM_BUFFER);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

static GLvoid TW_CALL set_sample_count(const GLvoid *value, 
                                       GLvoid *clientData) {
	sampleCnt = *reinterpret_cast<const GLint *>(value);
	glProgramUniform1i(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_SAMPLECNT],
	                   sampleCnt);
}

static GLvoid TW_CALL set_radius(const GLvoid *value, 
                                       GLvoid *clientData) {
	radius = *reinterpret_cast<const GLfloat *>(value);
	glProgramUniform1f(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_RADIUS],
	                   radius);
}

static GLvoid TW_CALL set_boost(const GLvoid *value, 
                                      GLvoid *clientData) {
	giBoost = *reinterpret_cast<const GLfloat *>(value);
	glProgramUniform1f(programs[PROGRAM_SSGI],
	                   locations[LOCATION_SSGI_GIBOOST],
	                   giBoost);
}

static GLvoid TW_CALL set_gi(const GLvoid *value, GLvoid *clientData) {
	giMode = *reinterpret_cast<const GLint *>(value);
	load_programs();
}

template<typename T>
static inline GLvoid TW_CALL get_t(GLvoid *value, GLvoid *clientData) {
	*reinterpret_cast<T*>(value) = 
		*reinterpret_cast<T*>(clientData);
}

