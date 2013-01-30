///////////////////////////////////////////////////////////////////////
// \file main.cpp
// \author Jonathan Dupuy (onrendering@gmail.com)
// \brief main function
//
///////////////////////////////////////////////////////////////////////


// --------------------------------------------------------------------
// Includes
#include "callbacks.hpp"


// --------------------------------------------------------------------
// Main
int main(int argc, char **argv) {
	// variables
	WindowParams windowParams;
	GLint windowId;

	// set core funcs
	set_window_params(windowParams);

	// init glut 
	glutInit(&argc, argv);

	// create a dummy window
	LOG("Creating dummy window...");
	glutInitContextVersion(1,5);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1, 1);
	windowId = glutCreateWindow("dummy");

	// check platform capabilities
	if(gl3wInit()) {
		LOG("Failed to load OpenGL functions.");
		return EXIT_FAILURE;
	}

	LOG("Platform information:");
	LOG("GL_VENDOR    " << glGetString(GL_VENDOR));
	LOG("GL_RENDERER  " << glGetString(GL_RENDERER));
	LOG("GL_VERSION   " << glGetString(GL_VERSION));
	LOG("GL_SHADING_LANGUAGE_VERSION " << glGetString(GL_SHADING_LANGUAGE_VERSION));
	if(!gl3wIsSupported(windowParams.major, windowParams.minor)) {
		LOG("This platform does not support the requested OpenGL context");
		return EXIT_FAILURE;
	}
	// destroy dummy window and create requested context
	glutDestroyWindow(windowId);
	LOG("Creating requested window...");
	glutInitContextVersion(windowParams.major,windowParams.minor);
	glutInitContextProfile(GLUT_CORE_PROFILE);
#ifdef NDEBUG
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
#else
	glutInitContextFlags(GLUT_DEBUG | GLUT_FORWARD_COMPATIBLE);
#endif
	glutInitDisplayMode(windowParams.glutDisplayMode);
	glutInitWindowSize(windowParams.width, windowParams.height);
	glutInitWindowPosition(-1, -1);
	windowId = glutCreateWindow("OpenGL");
	gl3wInit();

	// set callbacks
	glutCloseFunc(&on_exit);
	glutReshapeFunc(&on_resize);
	glutDisplayFunc(&on_display);
	glutKeyboardFunc(&on_keypress);
	glutKeyboardUpFunc(&on_keyrelease);
	glutMouseFunc(&on_mousebutton);
	glutMotionFunc(&on_mousemotion);
	glutPassiveMotionFunc(&on_mousepassivemotion);
	glutMouseWheelFunc(&on_mousewheel);

	// run
	LOG("Initializing resources...");
	on_init(argc, argv);
	LOG("Running...");
	glutMainLoop();
}


