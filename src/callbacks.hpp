///////////////////////////////////////////////////////////////////////
// \file callbacks.hpp
// \author Jonathan Dupuy (onrendering@gmail.com)
// \brief main callbacks
//
///////////////////////////////////////////////////////////////////////

#ifndef _CALLBACKS_HPP_
#define _CALLBACKS_HPP_

// --------------------------------------------------------------------
// Includes
#include "GL3/gl3w.h"
#include "GL/freeglut.h"
#include "debug.hpp"


// --------------------------------------------------------------------
// Structures
typedef struct {
	GLint width, height;
	GLint major, minor;
	GLint glutDisplayMode;
} WindowParams;


// --------------------------------------------------------------------
// Core configuration functions
GLvoid set_window_params(WindowParams &windowParams);


// --------------------------------------------------------------------
// GLUT callbacks
GLvoid on_init(GLint argc, GLchar **argv);
GLvoid on_resize(GLint w, GLint h);
GLvoid on_keypress(GLubyte key, GLint x, GLint y);
GLvoid on_keyrelease(GLubyte key, GLint x, GLint y);
GLvoid on_mousebutton(GLint button, GLint state, GLint x, GLint y);
GLvoid on_mousemotion(GLint x, GLint y);
GLvoid on_mousepassivemotion(GLint x, GLint y);
GLvoid on_mousewheel(GLint wheel, GLint direction, GLint x, GLint y);
GLvoid on_display();
GLvoid on_exit();

#endif

