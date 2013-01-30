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
#define BUMP_RES   1024


// names
enum {
	VERTEX_ARRAY_EMPTY = 0,
	VERTEX_ARRAY_COUNT,

	TEXTURE_GROVE = 0,
	TEXTURE_GRACE,
	TEXTURE_BUMP,
	TEXTURE_COUNT,

	RENDERBUFFER_COLOUR = 0,
	RENDERBUFFER_DEPTH,
	RENDERBUFFER_COUNT,

	FRAMEBUFFER_DISPLAY = 0,
	FRAMEBUFFER_BUMP,
	FRAMEBUFFER_COUNT,

	PROGRAM_GEOMETRY = 0,
	PROGRAM_TANGENT,
	PROGRAM_SKYBOX,
	PROGRAM_BUMP,
	PROGRAM_COUNT,

	LOCATION_SPHERE_MVP = 0,
	LOCATION_SPHERE_EYE,
	LOCATION_SPHERE_SKY,
	LOCATION_SPHERE_MEAN,
	LOCATION_SPHERE_VAR, // variance
	LOCATION_SPHERE_COR, // correlation
	LOCATION_SPHERE_EXP, // exposure
	LOCATION_SPHERE_ALPHA, // controls blend between diffuse and specular
	LOCATION_TANGENT_MVP,
	LOCATION_SKYBOX_MVP,
	LOCATION_SKYBOX_SKY,
	LOCATION_SKYBOX_EXP,
	LOCATION_BUMP_TIME,
	LOCATION_COUNT,

	LAYER_BUMP_DATA = 0,
	LAYER_STATS,
	LAYER_COUNT,

	GEOMETRY_SPHERE = 0,
	GEOMETRY_TORUS,
	GEOMETRY_SHELL,
	GEOMETRY_KLEINBOTTLE,
	GEOMETRY_COUNT,

	TIMERCPU_BRDF=0,
	TIMERCPU_TIME,
	TIMERCPU_COUNT,

	TIMERGPU_BRDF=0,
	TIMERGPU_COUNT
};


// --------------------------------------------------------------------
// global variables

// opengl names
std::vector<GLuint> vertexArrays(VERTEX_ARRAY_COUNT);
std::vector<GLuint> renderbuffers(RENDERBUFFER_COUNT);
std::vector<GLuint> framebuffers(FRAMEBUFFER_COUNT);
std::vector<GLuint> textures(TEXTURE_COUNT);
std::vector<GLuint> programs(PROGRAM_COUNT);

// uniform locations
std::vector<GLint> locations(LOCATION_COUNT);

// timers
glu::TimerGpu *gpuTimers(NULL);
glu::TimerCpu *cpuTimers(NULL);

// camera transformations
Affine cameraFrame(Affine::Translation(Vector3(0,0,-128)));

// cursor
GLint prevX(0), prevY(0);
bool leftButton(false), rightButton(false);

// distribution params
Vector2 mean(0,0);
Vector2 variance(0.05,0.05);
GLfloat correlation(0.0);

// envmap
GLuint cubemap(TEXTURE_GROVE);

// visualisation
bool wireframe(false);
bool showTangents(false);
bool showCubemap(true);
GLfloat exposure(4.0f);
Vector3 alpha(0.5,0.5,0.5);
GLuint geometry(GEOMETRY_SPHERE);
GLuint sampleCnt(1); // aa factor
GLfloat cpuTime(0), gpuTime(0);


// --------------------------------------------------------------------
// callbacks
static GLvoid load_programs();
static GLvoid load_textures();
static GLvoid load_renderbuffers();
static GLvoid load_framebuffers(bool aaOnly);
static GLvoid setup_hud();
static GLvoid gen_bumps(GLfloat time);
// gui callbacks
static GLvoid TW_CALL set_exposure(const GLvoid *value, GLvoid *clientData);
static GLvoid TW_CALL set_mean(const GLvoid *value, GLvoid *clientData);
static GLvoid TW_CALL set_variance(const GLvoid *value, GLvoid *clientData);
static GLvoid TW_CALL set_correlation(const GLvoid *value, GLvoid *clientData);
static GLvoid TW_CALL set_alpha(const GLvoid *value, GLvoid *clientData);
static GLvoid TW_CALL set_environment(const GLvoid *value, GLvoid *clientData);
static GLvoid TW_CALL set_geometry(const GLvoid *value, GLvoid *clientData);
static GLvoid TW_CALL set_aa(const GLvoid *value, GLvoid *clientData);
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

	// framebuffers
	glGenFramebuffers(FRAMEBUFFER_COUNT, &framebuffers[0]);
	load_framebuffers(false);

	// programs
	load_programs();

	// set up hud
	setup_hud();

	// create timers
	cpuTimers = new glu::TimerCpu[TIMERCPU_COUNT];
	gpuTimers = new glu::TimerGpu[TIMERGPU_COUNT];

	// set state
	glClearColor(0.2,0.2,0.2,1);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glPatchParameteri(GL_PATCH_VERTICES,4);
	glBindVertexArray(vertexArrays[VERTEX_ARRAY_EMPTY]);
}


// --------------------------------------------------------------------
// on_display
GLvoid on_display() {
	// build matrices
	Matrix4x4 mvp = Matrix4x4::Perspective(PI*0.65f,
	                                       WIDTH/GLfloat(HEIGHT),
	                                       0.1f,
	                                       5024.f)
	              * cameraFrame.ExtractTransformMatrix();
	Matrix3x3 rot = cameraFrame.GetUnitAxis().Transpose();
	Vector3 eye   = rot * -cameraFrame.GetPosition();

	// update mvp TODO: use UBO and buffer streaming
	glProgramUniformMatrix4fv(programs[PROGRAM_GEOMETRY],
	                          locations[LOCATION_SPHERE_MVP],
	                          1, GL_FALSE, &mvp[0][0]);
	glProgramUniformMatrix4fv(programs[PROGRAM_TANGENT],
	                          locations[LOCATION_TANGENT_MVP],
	                          1, GL_FALSE, &mvp[0][0]);
	glProgramUniformMatrix4fv(programs[PROGRAM_SKYBOX],
	                          locations[LOCATION_SKYBOX_MVP],
	                          1, GL_FALSE, &mvp[0][0]);
	glProgramUniform3fv(programs[PROGRAM_GEOMETRY],
	                    locations[LOCATION_SPHERE_EYE],
	                    1, &eye[0]);

	// generate bumps
	static GLfloat t=0.f;
	gen_bumps(t);
	t+= 0.125f;

	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glBindFramebuffer(GL_FRAMEBUFFER,
	                  framebuffers[FRAMEBUFFER_DISPLAY]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_MULTISAMPLE);
	glViewport(0,0,WIDTH,HEIGHT);
	if(wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// draw sphere
		cpuTimers[TIMERCPU_BRDF].Start();
		gpuTimers[TIMERGPU_BRDF].Start();
		glUseProgram(programs[PROGRAM_GEOMETRY]);
			glDrawArrays(GL_PATCHES, 0, 4*16*16);
	if(wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		cpuTimers[TIMERCPU_BRDF].Stop();
		gpuTimers[TIMERGPU_BRDF].Stop();
		cpuTime = cpuTimers[TIMERCPU_BRDF].Ticks()*1e3;
		gpuTime = gpuTimers[TIMERGPU_BRDF].Ticks()*1e3;

		// draw sphere tangents
		if(showTangents) {
			glUseProgram(programs[PROGRAM_TANGENT]);
				glDrawArrays(GL_PATCHES, 0, 4);
		}

		// draw cubemap
		glEnable(GL_CULL_FACE);
		if(showCubemap) {
			glUseProgram(programs[PROGRAM_SKYBOX]);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);
	}
	glDisable(GL_MULTISAMPLE);
	glDisable(GL_DEPTH_TEST);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER,
	                  framebuffers[FRAMEBUFFER_DISPLAY]);
	glViewport(0,0,WIDTH,HEIGHT);
		// copy scene
		glBlitFramebuffer(0,0,WIDTH,HEIGHT,0,0,WIDTH,HEIGHT,
		                  GL_COLOR_BUFFER_BIT,GL_NEAREST);
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
	TwWindowSize(w, h);
}


// --------------------------------------------------------------------
// on_keypress
GLvoid on_keypress(GLubyte key, GLint x, GLint y) {
	if(1==TwEventKeyboardGLUT(key, x, y))
		return;
	switch(key) {
		case 'r': load_programs(); break; // reload programs
		case 'w': wireframe = !wireframe; break; // wireframe
		case 't': showTangents = !showTangents; break; // wireframe
		case 'p': glu::save_gl_front_buffer(0,0,WIDTH,HEIGHT);  break; // screenshot
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
	delete[] cpuTimers;
	delete[] gpuTimers;
	for(GLint i=0; i<PROGRAM_COUNT; ++i)
		glDeleteProgram(programs[i]);
	glDeleteFramebuffers(FRAMEBUFFER_COUNT, &framebuffers[0]);
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
	const std::string SURFACE_PATH(SHADER_DIR+"surfaces.glsl");
	const std::string HDR_PATH(SHADER_DIR+"hdr.glsl");
	const std::string BRDF_PATH(SHADER_DIR+"brdf.glsl");
	const char* geomOptStr[] = {"#define _SPHERE\n",
	                            "#define _TORUS\n",
	                            "#define _SHELL\n",
	                            "#define _KLEINBOTTLE\n"};
	const std::string surfaceSrc(glu::load_string_from_file(SURFACE_PATH,
	                                                        false));
	const std::string hdrSrc(glu::load_string_from_file(HDR_PATH,
	                                                    false));

	// cleanup
	if(glIsProgram(programs[0]))
		for(GLint i=0; i<PROGRAM_COUNT; ++i)
			glDeleteProgram(programs[i]);

	// gen
	for(GLint i=0; i<PROGRAM_COUNT; ++i)
		programs[i] = glCreateProgram();

	// load
	std::string options = geomOptStr[geometry];
	options+= cubemap == TEXTURE_GRACE ? "#define _SKY_GRACE\n" : "";
	glu::load_glsl_program(programs[PROGRAM_GEOMETRY],
	                       SHADER_DIR+std::string("geometry.glsl"),
	                       options+surfaceSrc+hdrSrc,
	                       GL_TRUE);
	glu::load_glsl_program(programs[PROGRAM_TANGENT],
	                       SHADER_DIR+std::string("tangents.glsl"),
	                       options+surfaceSrc,
	                       GL_TRUE);
	glu::load_glsl_program(programs[PROGRAM_SKYBOX],
	                       SHADER_DIR+std::string("skybox.glsl"),
	                       hdrSrc,
	                       GL_TRUE);
	glu::load_glsl_program(programs[PROGRAM_BUMP],
	                       SHADER_DIR+std::string("bumps.glsl"),
	                       "",
	                       GL_TRUE);

	// save uniform locations
	locations[LOCATION_SPHERE_MVP]
		= glGetUniformLocation(programs[PROGRAM_GEOMETRY],"uModelViewProjection");
	locations[LOCATION_SPHERE_EYE]
		= glGetUniformLocation(programs[PROGRAM_GEOMETRY],"uEye");
	locations[LOCATION_SPHERE_SKY]
		= glGetUniformLocation(programs[PROGRAM_GEOMETRY],"sSky");
	locations[LOCATION_SPHERE_EXP]
		= glGetUniformLocation(programs[PROGRAM_GEOMETRY],"uExposure");
	locations[LOCATION_SPHERE_MEAN]
		= glGetUniformLocation(programs[PROGRAM_GEOMETRY],"uMean");
	locations[LOCATION_SPHERE_VAR]
		= glGetUniformLocation(programs[PROGRAM_GEOMETRY],"uVariance");
	locations[LOCATION_SPHERE_COR]
		= glGetUniformLocation(programs[PROGRAM_GEOMETRY],"uCorrelation");
	locations[LOCATION_SPHERE_ALPHA]
		= glGetUniformLocation(programs[PROGRAM_GEOMETRY],"uAlpha");
	locations[LOCATION_TANGENT_MVP]
		= glGetUniformLocation(programs[PROGRAM_TANGENT],"uModelViewProjection");
	locations[LOCATION_SKYBOX_MVP]
		= glGetUniformLocation(programs[PROGRAM_SKYBOX],"uModelViewProjection");
	locations[LOCATION_SKYBOX_SKY]
		= glGetUniformLocation(programs[PROGRAM_SKYBOX],"sSky");
	locations[LOCATION_SKYBOX_EXP]
		= glGetUniformLocation(programs[PROGRAM_SKYBOX],"uExposure");
	locations[LOCATION_BUMP_TIME]
		= glGetUniformLocation(programs[PROGRAM_BUMP],"uT");

	// set constants
	glProgramUniform1i(programs[PROGRAM_GEOMETRY],
	                   glGetUniformLocation(programs[PROGRAM_GEOMETRY],"sBumps"),
	                   TEXTURE_BUMP);
	glProgramUniform1f(programs[PROGRAM_GEOMETRY],
	                   locations[LOCATION_SPHERE_EXP],
	                   exposure);
	glProgramUniform1f(programs[PROGRAM_SKYBOX],
	                   locations[LOCATION_SKYBOX_EXP],
	                   exposure);
	glProgramUniform2f(programs[PROGRAM_GEOMETRY],
	                   locations[LOCATION_SPHERE_MEAN],
	                   mean[0], mean[1]);
	glProgramUniform2f(programs[PROGRAM_GEOMETRY],
	                   locations[LOCATION_SPHERE_VAR],
	                   variance[0], variance[1]);
	glProgramUniform1f(programs[PROGRAM_GEOMETRY],
	                   locations[LOCATION_SPHERE_COR],
	                   correlation);
	glProgramUniform1i(programs[PROGRAM_GEOMETRY],
	                   locations[LOCATION_SPHERE_SKY],
	                   cubemap);
	glProgramUniform1i(programs[PROGRAM_SKYBOX],
	                   locations[LOCATION_SKYBOX_SKY],
	                   cubemap);
	glProgramUniform3fv(programs[PROGRAM_GEOMETRY],
	                   locations[LOCATION_SPHERE_ALPHA],
	                   1, &alpha[0]);
	glProgramUniform1f(programs[PROGRAM_BUMP],
	                   locations[LOCATION_BUMP_TIME],
	                   0.0f);
}


// ====================================================================
// load textures
static GLvoid load_textures() {
	const std::string TEXTURE_DIR("../../textures/");
	glActiveTexture(GL_TEXTURE0+TEXTURE_GROVE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textures[TEXTURE_GROVE]); {
		glu::TexImageRgbe xpos(TEXTURE_DIR+std::string("grove_xpos.hdr"));
		glu::TexImageRgbe xneg(TEXTURE_DIR+std::string("grove_xneg.hdr"));
		glu::TexImageRgbe ypos(TEXTURE_DIR+std::string("grove_ypos.hdr"));
		glu::TexImageRgbe yneg(TEXTURE_DIR+std::string("grove_yneg.hdr"));
		glu::TexImageRgbe zpos(TEXTURE_DIR+std::string("grove_zneg.hdr"));
		glu::TexImageRgbe zneg(TEXTURE_DIR+std::string("grove_zpos.hdr"));
		glu::TexImageArray array;
		array.push_back(&xpos);
		array.push_back(&xneg);
		array.push_back(&ypos);
		array.push_back(&yneg);
		array.push_back(&zpos);
		array.push_back(&zneg);
		glu::load_texture_cube_map(array, GL_RGB16F, GL_TRUE, GL_FALSE);
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
	glActiveTexture(GL_TEXTURE0+TEXTURE_GRACE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textures[TEXTURE_GRACE]); {
		glu::TexImageRgbe xpos(TEXTURE_DIR+std::string("grace_xpos.hdr"));
		glu::TexImageRgbe xneg(TEXTURE_DIR+std::string("grace_xneg.hdr"));
		glu::TexImageRgbe ypos(TEXTURE_DIR+std::string("grace_ypos.hdr"));
		glu::TexImageRgbe yneg(TEXTURE_DIR+std::string("grace_yneg.hdr"));
		glu::TexImageRgbe zpos(TEXTURE_DIR+std::string("grace_zneg.hdr"));
		glu::TexImageRgbe zneg(TEXTURE_DIR+std::string("grace_zpos.hdr"));
		glu::TexImageArray array;
		array.push_back(&xpos);
		array.push_back(&xneg);
		array.push_back(&ypos);
		array.push_back(&yneg);
		array.push_back(&zpos);
		array.push_back(&zneg);
		glu::load_texture_cube_map(array, GL_RGB16F, GL_TRUE, GL_FALSE);
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
	glActiveTexture(GL_TEXTURE0+TEXTURE_BUMP);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textures[TEXTURE_BUMP]);
		glTexStorage3D(GL_TEXTURE_2D_ARRAY,
		               glu::next_power_of_two_exponent(BUMP_RES),
		               GL_RGB16F,
		               BUMP_RES,
		               BUMP_RES,
		               LAYER_COUNT);
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
		glTexParameteri(GL_TEXTURE_2D_ARRAY,
		                GL_TEXTURE_MIN_FILTER,
		                GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY,
		                GL_TEXTURE_MAG_FILTER,
		                GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D_ARRAY,
		                GL_TEXTURE_MAX_ANISOTROPY_EXT,
		                16.0f);
}


// ====================================================================
// setup renderbuffers
static GLvoid load_renderbuffers() {
	glBindRenderbuffer(GL_RENDERBUFFER,
	                   renderbuffers[RENDERBUFFER_COLOUR]);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER,
		                                 sampleCnt,
		                                 GL_RGBA8,
		                                 WIDTH,
		                                 HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER,
	                   renderbuffers[RENDERBUFFER_DEPTH]);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER,
		                                 sampleCnt,
		                                 GL_DEPTH_COMPONENT24,
		                                 WIDTH,
		                                 HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}


// ====================================================================
// setup framebuffers
static GLvoid load_framebuffers(bool aaOnly) {
	if(!aaOnly) {
		const GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0+LAYER_BUMP_DATA,
		                              GL_COLOR_ATTACHMENT0+LAYER_STATS};
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[FRAMEBUFFER_BUMP]);
			glFramebufferTextureLayer(GL_FRAMEBUFFER,
			                          GL_COLOR_ATTACHMENT0+LAYER_BUMP_DATA,
			                          textures[TEXTURE_BUMP],
			                          0, LAYER_BUMP_DATA);
			glFramebufferTextureLayer(GL_FRAMEBUFFER,
			                          GL_COLOR_ATTACHMENT0+LAYER_STATS,
			                          textures[TEXTURE_BUMP],
			                          0, LAYER_STATS);
			glDrawBuffers(LAYER_COUNT,
			              drawBuffers);
		ASSERT(glu::check_gl_framebuffer_complete()
		       &&  "Invalid framebuffer configuration" );
	}
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[FRAMEBUFFER_DISPLAY]);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER,
		                          GL_COLOR_ATTACHMENT0,
		                          GL_RENDERBUFFER,
		                          renderbuffers[RENDERBUFFER_COLOUR]);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER,
		                          GL_DEPTH_ATTACHMENT,
		                          GL_RENDERBUFFER,
		                          renderbuffers[RENDERBUFFER_DEPTH]);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
	ASSERT(glu::check_gl_framebuffer_complete()
		       &&  "Invalid framebuffer configuration" );
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


// ====================================================================
// generate bumps
static GLvoid gen_bumps(GLfloat t) {
	// upload time
	glProgramUniform1f(programs[PROGRAM_BUMP],
	                   locations[LOCATION_BUMP_TIME],
	                   t);

	// setup framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[FRAMEBUFFER_BUMP]);
	glViewport(0,0,BUMP_RES,BUMP_RES);
	glDisable(GL_DEPTH_TEST);

	// render
	glUseProgram(programs[PROGRAM_BUMP]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// reset state
	glEnable(GL_DEPTH_TEST);

	// prefilter
	glActiveTexture(GL_TEXTURE0+TEXTURE_BUMP);
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}


// ====================================================================
// setup hud
static GLvoid setup_hud() {
	// start ant
	TwInit(TW_OPENGL_CORE, NULL);
	TwGLUTModifiersFunc(glutGetModifiers); // GLUT specific

	TwBar* hud = TwNewBar("HUD");
	TwDefine("HUD size='198 285'");
	TwDefine("HUD position='16 16'");
	TwDefine("HUD alpha='90'");
	TwDefine("HUD color='0 0 0'");
	TwDefine("HUD text='light'");
	TwDefine("HUD valueswidth=64");

	TwAddVarRO(hud,
	           "CPU",
	           TW_TYPE_FLOAT,
	           &cpuTime,
	           "group='Speed'");
	TwAddVarRO(hud,
	           "GPU",
	           TW_TYPE_FLOAT,
	           &gpuTime,
	           "group='Speed'");
	TwAddVarCB(hud,
	           "MeanX",
	           TW_TYPE_FLOAT,
	           &set_mean,
	           &get_t<GLfloat>,
	           &mean[0],
	           "min=-4.0 max=4.0 step=0.1 group='BRDF'");
	TwAddVarCB(hud,
	           "MeanY",
	           TW_TYPE_FLOAT,
	           &set_mean,
	           &get_t<GLfloat>,
	           &mean[1],
	           "min=-4.0 max=4.0 step=0.1 group='BRDF'");
	TwAddVarCB(hud,
	           "VarX",
	           TW_TYPE_FLOAT,
	           &set_variance,
	           &get_t<GLfloat>,
	           &variance[0],
	           "min=0.001 max=500.0 step=0.005 group='BRDF'");
	TwAddVarCB(hud,
	           "VarY",
	           TW_TYPE_FLOAT,
	           &set_variance,
	           &get_t<GLfloat>,
	           &variance[1],
	           "min=0.001 max=500.0 step=0.005 group='BRDF'");
	TwAddVarCB(hud,
	           "Correlation",
	           TW_TYPE_FLOAT,
	           &set_correlation,
	           &get_t<GLfloat>,
	           &correlation,
	           "min=-0.99 max=0.99 step=0.01 group='BRDF'");
	TwAddVarCB(hud,
	           "AlphaR",
	           TW_TYPE_FLOAT,
	           &set_alpha,
	           &get_t<GLfloat>,
	           &alpha[0],
	           "min=0.0 max=1.0 step=0.01 group='BRDF'");
//	TwAddVarCB(hud,
//	           "AlphaG",
//	           TW_TYPE_FLOAT,
//	           &set_alpha,
//	           &get_t<GLfloat>,
//	           &alpha[1],
//	           "min=0.0 max=1.0 step=0.01 group='BRDF'");
//	TwAddVarCB(hud,
//	           "AlphaB",
//	           TW_TYPE_FLOAT,
//	           &set_alpha,
//	           &get_t<GLfloat>,
//	           &alpha[2],
//	           "min=0.0 max=1.0 step=0.01 group='BRDF'");
	TwAddVarCB(hud,
	           "AA factor",
	           TW_TYPE_UINT32,
	           &set_aa,
	           &get_t<GLuint>,
	           &sampleCnt,
	           "min=1 max=8 step=1 group='Scene' \
	           help ='Sets the anti aliasing factor' ");
	TwAddVarCB(hud,
	           "Exposure",
	           TW_TYPE_FLOAT,
	           &set_exposure,
	           &get_t<GLfloat>,
	           &exposure,
	           "min=0.1 max=50.0 step=0.1 group='Scene'");

	TwEnumVal envEV[] = {
		{TEXTURE_GRACE,        "Grace"},
		{TEXTURE_GROVE,        "Grove"}
	};
	TwType envType= TwDefineEnum("Environment", envEV, 2);
	TwAddVarCB(hud,
	           "Sky",
	           envType,
	           &set_environment,
	           &get_t<GLint>,
	           &cubemap,
	           "help='Change environment map.' group='Scene' ");
	TwAddVarRW(hud,
	           "Render sky",
	           TW_TYPE_BOOLCPP,
	           &showCubemap,
	           "true='ON' false='OFF' group='Scene' ");
	TwEnumVal geometryEV[] = {
		{GEOMETRY_SPHERE,      "Sphere"     },
		{GEOMETRY_TORUS,       "Torus"      },
		{GEOMETRY_SHELL,       "Shell"      },
		{GEOMETRY_KLEINBOTTLE, "Kleinbottle"}
	};
	TwType geometryType= TwDefineEnum("Geometry", geometryEV, 4);
	TwAddVarCB(hud,
	           "Geometry",
	           geometryType,
	           &set_geometry,
	           &get_t<GLint>,
	           &geometry,
	           "help='Change geometry.' group='Scene' ");
}


// ====================================================================
// gui callbacks
static GLvoid TW_CALL set_mean(const GLvoid *value, GLvoid *clientData) {
	*reinterpret_cast<GLfloat *>(clientData) =
		*reinterpret_cast<const GLfloat *>(value);
	glProgramUniform2f(programs[PROGRAM_GEOMETRY],
	                   locations[LOCATION_SPHERE_MEAN],
	                   mean[0], mean[1]);
}

static GLvoid TW_CALL set_variance(const GLvoid *value, GLvoid *clientData) {
	*reinterpret_cast<GLfloat *>(clientData) =
		*reinterpret_cast<const GLfloat *>(value);
	glProgramUniform2f(programs[PROGRAM_GEOMETRY],
	                   locations[LOCATION_SPHERE_VAR],
	                   variance[0], variance[1]);
}

static GLvoid TW_CALL set_correlation(const GLvoid *value, GLvoid *clientData) {
	correlation = *reinterpret_cast<const GLfloat *>(value);
	glProgramUniform1f(programs[PROGRAM_GEOMETRY],
	                   locations[LOCATION_SPHERE_COR],
	                   correlation);
}

static GLvoid TW_CALL set_exposure(const GLvoid *value, GLvoid *clientData) {
	exposure = *reinterpret_cast<const GLfloat *>(value);
	glProgramUniform1f(programs[PROGRAM_GEOMETRY],
	                   locations[LOCATION_SPHERE_EXP],
	                   exposure);
	glProgramUniform1f(programs[PROGRAM_SKYBOX],
	                   locations[LOCATION_SKYBOX_EXP],
	                   exposure);
}

static GLvoid TW_CALL set_alpha(const GLvoid *value, GLvoid *clientData) {
	*reinterpret_cast<GLfloat *>(clientData) =
		*reinterpret_cast<const GLfloat *>(value);
	alpha[1]=alpha[2]=alpha[0]; // tmp
	glProgramUniform3fv(programs[PROGRAM_GEOMETRY],
	                   locations[LOCATION_SPHERE_ALPHA],
	                   1, &alpha[0]);
}

GLvoid TW_CALL set_aa(const GLvoid *value, GLvoid *clientData) {
	sampleCnt = *reinterpret_cast<const GLuint *>(value);
	load_renderbuffers();
	load_framebuffers(true); // crashes without 
}

static GLvoid TW_CALL set_environment(const GLvoid *value, GLvoid *clientData) {
	cubemap = * reinterpret_cast<const GLint *>(value);
	load_programs();
}

static GLvoid TW_CALL set_geometry(const GLvoid *value, GLvoid *clientData) {
	geometry = * reinterpret_cast<const GLint *>(value);
	load_programs();
}

template<typename T>
static inline GLvoid TW_CALL get_t(GLvoid *value, GLvoid *clientData) {
	*reinterpret_cast<T*>(value) = 
		*reinterpret_cast<T*>(clientData);
}

