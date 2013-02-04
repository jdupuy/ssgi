///////////////////////////////////////////////////////////////////////
// \file glu.cpp
// \author Jonathan Dupuy (onrendering@gmail.com)
// \brief OpenGL helper functions implementation.
//
///////////////////////////////////////////////////////////////////////

#include "glu.hpp"
#include <fstream>   // std::ifstream
#include <climits>   // CHAR_BIT
#include <cstring>   // memcpy
#include <algorithm> // std::min std::max
#include <cmath>     // ldexp

#ifdef _WIN32
#	define NOMINMAX
#	include <windows.h>
//#	include <winbase.h>
#else
#	include <unistd.h>
#endif // _WIN32

#include <iostream> // tmp

namespace glu {

///////////////////////////////////////////////////////////////////////
// Pixel Unpacking push/pop utility class
class PixelStore {
protected:
	PixelStore() {}
	GLint mSwapBytes, mLsbFirst, mRowLength, mImageHeight; // packing
	GLint mSkipRows, mSkipPixels, mSkipImages, mAlignment; // packing ctd
};

class PixelStorePack : public PixelStore {
public:
	PixelStorePack() {
		glGetIntegerv(GL_PACK_SWAP_BYTES, &mSwapBytes);
		glGetIntegerv(GL_PACK_LSB_FIRST, &mLsbFirst);
		glGetIntegerv(GL_PACK_ROW_LENGTH, &mRowLength);
		glGetIntegerv(GL_PACK_IMAGE_HEIGHT, &mImageHeight);
		glGetIntegerv(GL_PACK_SKIP_ROWS, &mSkipRows);
		glGetIntegerv(GL_PACK_SKIP_PIXELS, &mSkipPixels);
		glGetIntegerv(GL_PACK_SKIP_IMAGES, &mSkipImages);
		glGetIntegerv(GL_PACK_ALIGNMENT, &mAlignment);
	}
	~PixelStorePack() {
		glPixelStorei(GL_PACK_SWAP_BYTES, mSwapBytes);
		glPixelStorei(GL_PACK_LSB_FIRST, mLsbFirst);
		glPixelStorei(GL_PACK_ROW_LENGTH, mRowLength);
		glPixelStorei(GL_PACK_IMAGE_HEIGHT, mImageHeight);
		glPixelStorei(GL_PACK_SKIP_ROWS, mSkipRows);
		glPixelStorei(GL_PACK_SKIP_PIXELS, mSkipPixels);
		glPixelStorei(GL_PACK_SKIP_IMAGES, mSkipImages);
		glPixelStorei(GL_PACK_ALIGNMENT, mAlignment);
	}
};

class PixelStoreUnpack : public PixelStore {
public:
	PixelStoreUnpack() {
		glGetIntegerv(GL_UNPACK_SWAP_BYTES, &mSwapBytes);
		glGetIntegerv(GL_UNPACK_LSB_FIRST, &mLsbFirst);
		glGetIntegerv(GL_UNPACK_ROW_LENGTH, &mRowLength);
		glGetIntegerv(GL_UNPACK_IMAGE_HEIGHT, &mImageHeight);
		glGetIntegerv(GL_UNPACK_SKIP_ROWS, &mSkipRows);
		glGetIntegerv(GL_UNPACK_SKIP_PIXELS, &mSkipPixels);
		glGetIntegerv(GL_UNPACK_SKIP_IMAGES, &mSkipImages);
		glGetIntegerv(GL_UNPACK_ALIGNMENT, &mAlignment);
	}
	~PixelStoreUnpack() {
		glPixelStorei(GL_UNPACK_SWAP_BYTES, mSwapBytes);
		glPixelStorei(GL_UNPACK_LSB_FIRST, mLsbFirst);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, mRowLength);
		glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, mImageHeight);
		glPixelStorei(GL_UNPACK_SKIP_ROWS, mSkipRows);
		glPixelStorei(GL_UNPACK_SKIP_PIXELS, mSkipPixels);
		glPixelStorei(GL_UNPACK_SKIP_IMAGES, mSkipImages);
		glPixelStorei(GL_UNPACK_ALIGNMENT, mAlignment);
	}
};


///////////////////////////////////////////////////////////////////////
// Get filename (without full path)
static const std::string _clean_filename(const std::string& file) {
#ifdef _WIN32
	if(strrchr(file.c_str(),'\\'))
		return std::string(strrchr(file.c_str(),'\\')+1);
#else
	if(strrchr(file.c_str(),'/'))
		return std::string(strrchr(file.c_str(),'/')+1);
#endif
	return file;
}


///////////////////////////////////////////////////////////////////////
// Convert GL error code to string
static const std::string _gl_error_to_string(GLenum error) {
	switch(error) {
	case GL_NO_ERROR:
		return "GL_NO_ERROR";
	case GL_INVALID_ENUM:
		return "GL_INVALID_ENUM";
	case GL_INVALID_VALUE:
		return "GL_INVALID_VALUE";
	case GL_INVALID_OPERATION:
		return "GL_INVALID_OPERATION";
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return "GL_INVALID_FRAMEBUFFER_OPERATION";
	case GL_OUT_OF_MEMORY:
		return "GL_OUT_OF_MEMORY";
	default:
		return "unknown code";
	}
}


///////////////////////////////////////////////////////////////////////
// Convert GL framebuffer status code to string
static const std::string _gl_framebuffer_status_to_string(GLenum error) {
	switch(error) {
	case GL_FRAMEBUFFER_COMPLETE:
		return "GL_FRAMEBUFFER_COMPLETE";
	case GL_FRAMEBUFFER_UNDEFINED:
		return "GL_FRAMEBUFFER_UNDEFINED";
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
		return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
		return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
	case GL_FRAMEBUFFER_UNSUPPORTED:
		return "GL_FRAMEBUFFER_UNSUPPORTED";
	case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
		return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
	case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
		return "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
	default:
		return "unknown code";
	}
}


///////////////////////////////////////////////////////////////////////
// Load and compile a shader
static GLvoid _attach_shader(GLuint program,
                             GLenum shaderType,
                             const GLchar* stringsrc) {
	const GLchar **string = &stringsrc;
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, string, NULL);
	glCompileShader(shader);

	// check compilation
#ifndef NDEBUG
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE) {
		GLint logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> logContent(logLength);
		glGetShaderInfoLog(shader, logLength, NULL, &logContent[0]);
		LOG("Compilation failed:\n" << std::string(&logContent[0],logLength));
		ASSERT(false && "Shader compilation error.");
	}
#endif

	// attach shader and flag for deletion
	glAttachShader(program, shader);
	glDeleteShader(shader);
}


///////////////////////////////////////////////////////////////////////
// Debug output callback
static GLvoid _gl_debug_message_callback(GLenum source,
                                         GLenum type,
                                         GLuint id,
                                         GLenum severity,
                                         GLsizei length,
                                         const GLchar* message,
                                         GLvoid* userParam ) {
	LOG("GL_ARB_debug_output:\n" << message << ".");
}


///////////////////////////////////////////////////////////////////////
// Image Mip levels
static GLsizei _tex_image_levels(GLsizei width,
                                 GLsizei height,
                                 GLsizei depth,
                                 GLboolean genMipmaps) {
	if(!genMipmaps)
		return 1;
	GLsizei size = std::max(std::max(width, height), depth);
	return next_power_of_two_exponent(size);
}


// --------------------------------------------------------------------
// extension check
GLboolean check_gl_extension_support(const std::string &name) {
	GLint i = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &i);
	for(--i; i>-1; --i) {
		if(0==strcmp(name.c_str(),
		             reinterpret_cast<const GLchar*>
		             (glGetStringi(GL_EXTENSIONS, i))))
			return GL_TRUE;
	}
	return GL_FALSE;
}


// --------------------------------------------------------------------
// error check
GLboolean check_gl_no_error() {
	GLenum error = glGetError();
	if(error != GL_NO_ERROR) {
		LOG("OpenGL error: " << _gl_error_to_string(error));
		return GL_FALSE;
	}
	return GL_TRUE;
}


// --------------------------------------------------------------------
// framebuffer check
GLboolean check_gl_framebuffer_complete() {
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(GL_FRAMEBUFFER_COMPLETE != status) {
		LOG("Incomplete framebuffer status: " << _gl_framebuffer_status_to_string(status));
		return GL_FALSE;
	}
	return GL_TRUE;
}


// --------------------------------------------------------------------
// program status check
GLboolean check_gl_program_link_status(GLuint program) {
	GLint status = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
#ifndef NDEBUG
	if(GL_FALSE == status) {
		GLint logLength=0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> logContent(logLength);
		glGetProgramInfoLog(program, logLength, NULL, &logContent[0]);
		LOG("Invalid link status: " << std::string(&logContent[0], logLength));
		return GL_FALSE;
	}
#endif
	return status;
}


// --------------------------------------------------------------------
// Init debug output
GLvoid init_gl_debug_output() {
	if(check_gl_extension_support("GL_ARB_debug_output")==GL_TRUE) {
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		glDebugMessageCallbackARB(
			reinterpret_cast<GLDEBUGPROCARB>(&_gl_debug_message_callback),
			NULL);
		ASSERT(check_gl_no_error() && "OpenGL error");
		LOG("GL_ARB_debug_output enabled.");
	}
	else LOG("GL_ARB_debug_output unsupported.");
}


// --------------------------------------------------------------------
// Screen shot
GLvoid save_gl_front_buffer(GLint x,
                            GLint y,
                            GLsizei width,
                            GLsizei height) {
	// check values
	ASSERT(x>=0 && y>=0 && width > 0 && height > 0
	             && "Invalid viewport dimensions.");

	static GLuint sShotCounter = 1;
	GLint readFramebuffer,
	      readBuffer,
	      pixelPackBufferBinding,
	      packSwapBytes, packLsbFirst, packRowLength, packImageHeight,
	      packSkipRows, packSkipPixels, packSkipImages, packAlignment;

	// save GL state
	glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFramebuffer);
	glGetIntegerv(GL_READ_BUFFER, &readBuffer);
	glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING, &pixelPackBufferBinding);
	glGetIntegerv(GL_PACK_SWAP_BYTES, &packSwapBytes);
	glGetIntegerv(GL_PACK_LSB_FIRST, &packLsbFirst);
	glGetIntegerv(GL_PACK_ROW_LENGTH, &packRowLength);
	glGetIntegerv(GL_PACK_IMAGE_HEIGHT, &packImageHeight);
	glGetIntegerv(GL_PACK_SKIP_ROWS, &packSkipRows);
	glGetIntegerv(GL_PACK_SKIP_PIXELS, &packSkipPixels);
	glGetIntegerv(GL_PACK_SKIP_IMAGES, &packSkipImages);
	glGetIntegerv(GL_PACK_ALIGNMENT, &packAlignment);

	// push GL state
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glReadBuffer(GL_FRONT);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
	glPixelStorei(GL_PACK_SWAP_BYTES, 0);
	glPixelStorei(GL_PACK_LSB_FIRST, 0);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
	glPixelStorei(GL_PACK_IMAGE_HEIGHT, 0);
	glPixelStorei(GL_PACK_SKIP_ROWS, 0);
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_PACK_SKIP_IMAGES, 0);
	glPixelStorei(GL_PACK_ALIGNMENT, 4);

	// allocate data and read pixels from framebuffer
	std::vector<GLubyte> tgaPixels(width*height*3);
	glReadPixels(x, y, width, height, GL_BGR, GL_UNSIGNED_BYTE, &tgaPixels[0]);

	// compute new filename
	std::stringstream ss;
	ss << "screenshot";
	if(sShotCounter < 10)
		ss << '0';
	if(sShotCounter < 100)
		ss << '0';
	if(sShotCounter < 1000)
		ss << '0';
	ss << sShotCounter << ".tga";

	// open file
	std::ofstream fileStream(ss.str().c_str(),
	                         std::ifstream::out | std::ifstream::binary);
	// check opening
	ASSERT(fileStream.is_open() && "Failed to create screenshot file.");

	// create header
	GLchar tgaHeader[18]= {
		0,                                     // image identification field
		0,                                     // colormap type
		2,                                     // image type code
		0,0,0,0,0,                             // color map spec (ignored here)
		0,0,                                   // x origin of image
		0,0,                                   // y origin of image
		width & 255,  width >> 8 & 255,        // width of the image
		height & 255, height >> 8 & 255,       // height of the image
		24,                                    // bits per pixel
		0                                      // image descriptor byte
	};

	// write header and pixel data
	fileStream.write(tgaHeader, 18);
	fileStream.write(reinterpret_cast<const GLchar*>(&tgaPixels[0]),
	                 width*height*3);
	fileStream.close();

	// restore GL state
	glBindFramebuffer(GL_READ_FRAMEBUFFER, readFramebuffer);
	glReadBuffer(readBuffer);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, pixelPackBufferBinding);
	glPixelStorei(GL_PACK_SWAP_BYTES, packSwapBytes);
	glPixelStorei(GL_PACK_LSB_FIRST, packLsbFirst);
	glPixelStorei(GL_PACK_ROW_LENGTH, packRowLength);
	glPixelStorei(GL_PACK_IMAGE_HEIGHT, packImageHeight);
	glPixelStorei(GL_PACK_SKIP_ROWS, packSkipRows);
	glPixelStorei(GL_PACK_SKIP_PIXELS, packSkipPixels);
	glPixelStorei(GL_PACK_SKIP_IMAGES, packSkipImages);
	glPixelStorei(GL_PACK_ALIGNMENT, packAlignment);

	// increment screenshot counter
	++sShotCounter;
}


// --------------------------------------------------------------------
// Is power of two
GLboolean is_power_of_two(GLuint number) {
	if((number != 0) && !(number & (number - 1)))
		return GL_TRUE;
	return GL_FALSE;
}


// --------------------------------------------------------------------
// Next power of two
GLuint next_power_of_two(GLuint number) {
	if (number == 0)
		return 1;
	--number;
	for (GLuint i=1; i<sizeof(GLuint)*CHAR_BIT; i<<=1)
		number = number | number >> i;
	return number+1;
}


// --------------------------------------------------------------------
// Next power of two exponent
GLuint next_power_of_two_exponent(GLuint number) {
	if(number==0)
		return 1;

	GLuint pot = next_power_of_two(number);
	GLuint exp = 0;
	while(!(pot & 0x01)){
		pot >>= 1;
		++exp;
	}
	return exp;
}


// --------------------------------------------------------------------
// Pack to uint_2_10_10_10_rev
GLuint pack_4f_to_uint_2_10_10_10_rev(GLfloat x,
                                      GLfloat y,
                                      GLfloat z,
                                      GLfloat w) {
	// clamp and expand
	GLuint ix = x*1023.0f;
	GLuint iy = y*1023.0f;
	GLuint iz = z*1023.0f;
	GLuint iw = w*3.0f;

	// pack
	GLuint pack;                   // msb                                 lsb
	pack = 0x000001FFu & ix;       // ---- ---- ---- ---- ---- --xx xxxx xxxx
	pack|= 0x000FFC00u & iy << 10; // ---- ---- ---- yyyy yyyy yyxx xxxx xxxx
	pack|= 0x1FF00000u & iz << 20; // --zz zzzz zzzz yyyy yyyy yyxx xxxx xxxx
	pack|= 0xC0000000u & iw << 30; // wwzz zzzz zzzz yyyy yyyy yyxx xxxx xxxx
	return pack;
}

GLuint pack_4fv_to_uint_2_10_10_10_rev(const GLfloat *v) {
	return pack_4f_to_uint_2_10_10_10_rev(v[0], v[1], v[2], v[3]);
}


// --------------------------------------------------------------------
// Pack to int_2_10_10_10_rev
GLint pack_4f_to_int_2_10_10_10_rev(GLfloat x,
                                    GLfloat y,
                                    GLfloat z,
                                    GLfloat w) {
	// clamp and expand
	GLint ix = x*511.0f;
	GLint iy = y*511.0f;
	GLint iz = z*511.0f;
	GLint iw = w;

	// pack
	GLuint pack;                  // msb                                 lsb
	pack = 0x000001FF & ix;       // ---- ---- ---- ---- ---- --xx xxxx xxxx
	pack|= 0x000FFC00 & iy << 10; // ---- ---- ---- yyyy yyyy yyxx xxxx xxxx
	pack|= 0x1FF00000 & iz << 20; // --zz zzzz zzzz yyyy yyyy yyxx xxxx xxxx
	pack|= 0xC0000000 & iw << 30; // wwzz zzzz zzzz yyyy yyyy yyxx xxxx xxxx
	return pack;
}

GLint pack_4fv_to_int_2_10_10_10_rev(const GLfloat *v) {
	return pack_4f_to_int_2_10_10_10_rev(v[0], v[1], v[2], v[3]);
}


// --------------------------------------------------------------------
// RGB packing (saves most significant bits)
GLubyte pack_3ub_to_ubyte_3_3_2(GLubyte r,
	                            GLubyte g,
	                            GLubyte b) {
	return (r & 0xE0u) | (g >> 3 & 0x1Cu) | (b >> 6 & 0x03u); // rrrg ggbb
}

GLushort pack_3ub_to_ushort_4_4_4(GLubyte r,
	                              GLubyte g,
	                              GLubyte b) {
	GLushort pack;               // msb             lsb
	pack = (0x0F00u & (r << 4)); // ---- rrrr ---- ----
	pack|= (0x00F0u & g);        // ---- rrrr gggg ----
	pack|= (0x000Fu & (b >> 4)); // ---- rrrr gggg bbbb
	return pack;
}

GLushort pack_3ub_to_ushort_5_5_5(GLubyte r,
	                              GLubyte g,
	                              GLubyte b) {
	GLushort pack;               // msb             lsb
	pack = (0x7C00u & (r << 7)); // -rrr rr-- ---- ----
	pack|= (0x03E0u & (g << 2)); // -rrr rrgg ggg- ----
	pack|= (0x001Fu & (b >> 3)); // -rrr rrgg gggb bbbb
	return pack;
}

GLushort pack_3ub_to_ushort_5_6_5(GLubyte r,
	                              GLubyte g,
	                              GLubyte b) {
	GLushort pack;               // msb             lsb
	pack = (0xF800u & (r << 8)); // rrrr r--- ---- ----
	pack|= (0x07E0u & (g << 3)); // rrrr rggg ggg- ----
	pack|= (0x001Fu & (b >> 3)); // rrrr rggg gggb bbbb
	return pack;
}

GLubyte pack_3ubv_to_ubyte_3_3_2(const GLubyte *v) {
	return pack_3ub_to_ubyte_3_3_2(v[0],v[1],v[2]);
}

GLushort pack_3ubv_to_ushort_4_4_4(const GLubyte *v) {
	return pack_3ub_to_ushort_4_4_4(v[0],v[1],v[2]);
}

GLushort pack_3ubv_to_ushort_5_5_5(const GLubyte *v) {
	return pack_3ub_to_ushort_5_5_5(v[0],v[1],v[2]);
}

GLushort pack_3ubv_to_ushort_5_6_5(const GLubyte *v) {
	return pack_3ub_to_ushort_5_6_5(v[0],v[1],v[2]);
}


// --------------------------------------------------------------------
// RGBA packing (saves most significant bits)
GLushort pack_4ub_to_ushort_4_4_4_4(GLubyte r,
                                    GLubyte g,
                                    GLubyte b,
                                    GLubyte a) {
	GLushort pack;               // msb             lsb
	pack = (0xF000u & (r << 8)); // rrrr ---- ---- ----
	pack|= (0x0F00u & (g << 4)); // rrrr gggg ---- ----
	pack|= (0x00F0u & b);        // rrrr gggg bbbb ----
	pack|= (0x000Fu & (a >> 4)); // rrrr gggg bbbb aaaa
	return pack;
}

GLushort pack_4ub_to_ushort_5_5_5_1(GLubyte r,
                                    GLubyte g,
                                    GLubyte b,
                                    GLubyte a) {
	GLushort pack;               // msb             lsb
	pack = (0xF800u & (r << 8)); // rrrr r--- ---- ----
	pack|= (0x07C0u & (g << 3)); // rrrr rggg gg-- ----
	pack|= (0x003Eu & (b >> 2)); // rrrr rggg ggbb bbb-
	pack|= (0x0001u & (a >> 7)); // rrrr rggg ggbb bbba
	return pack;
}

GLushort pack_4ubv_to_ushort_4_4_4_4(const GLubyte *v) {
	return pack_4ub_to_ushort_4_4_4_4(v[0],v[1],v[2],v[3]);
}

GLushort pack_4ubv_to_ushort_5_5_5_1(const GLubyte *v) {
	return pack_4ub_to_ushort_5_5_5_1(v[0],v[1],v[2],v[3]);
}


// --------------------------------------------------------------------
// Half to float and float to half conversions
// Left the work to smarter people :p (see comments below)

/*
 * Ork: a small object-oriented OpenGL Rendering Kernel.
 * Copyright (c) 2008-2010 INRIA
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.
 */

/*
 * Authors: Eric Bruneton, Antoine Begault, Guillaume Piolat.
 */

// Code derived from:
// http://code.google.com/p/nvidia-texture-tools/source/browse/trunk/src/nvmath/Half.cpp

// Branch-free implementation of half-precision (16 bit) floating point
// Copyright 2006 Mike Acton <macton@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE
//
// Half-precision floating point format
// ------------------------------------
//
//   | Field    | Last | First | Note
//   |----------|------|-------|----------
//   | Sign     | 15   | 15    |
//   | Exponent | 14   | 10    | Bias = 15
//   | Mantissa | 9    | 0     |
//
// Compiling
// ---------
//
//  Preferred compile flags for GCC:
//     -O3 -fstrict-aliasing -std=c99 -pedantic -Wall -Wstrict-aliasing
//
//     This file is a C99 source file, intended to be compiled with a C99
//     compliant compiler. However, for the moment it remains combatible
//     with C++98. Therefore if you are using a compiler that poorly implements
//     C standards (e.g. MSVC), it may be compiled as C++. This is not
//     guaranteed for future versions.
//
// Features
// --------
//
//  * QNaN + <x>  = QNaN
//  * <x>  + +INF = +INF
//  * <x>  - -INF = -INF
//  * INF  - INF  = SNaN
//  * Denormalized values
//  * Difference of ZEROs is always +ZERO
//  * Sum round with guard + round + sticky bit (grs)
//  * And of course... no branching
//
// Precision of Sum
// ----------------
//
//  (SUM)        uint16 z = half_add( x, y );
//  (DIFFERENCE) uint16 z = half_add( x, -y );
//
//     Will have exactly (0 ulps difference) the same result as:
//     (For 32 bit IEEE 784 floating point and same rounding mode)
//
//     union FLOAT_32
//     {
//       float    f32;
//       uint32 u32;
//     };
//
//     union FLOAT_32 fx = { .u32 = half_to_float( x ) };
//     union FLOAT_32 fy = { .u32 = half_to_float( y ) };
//     union FLOAT_32 fz = { .f32 = fx.f32 + fy.f32    };
//     uint16       z  = float_to_half( fz );
//

// Negate
#ifdef _MSC_VER
// prevent a MSVC warning
#   define _unsigned_neg(a) (~(a) + 1)
#else
#   define _unsigned_neg(a) (-(a))
#endif

// Select on Sign bit
static inline unsigned _unsigned_sels(unsigned test, unsigned a, unsigned b) {
    unsigned mask = ((int)test) >> 31; // sign-extend
    unsigned sel_a  = a & mask;
    unsigned sel_b  = b & (~mask);
    unsigned result =  sel_a | sel_b;
    return result;
}

// Count Leading Zeros
static inline unsigned _unsigned_cntlz(unsigned x) {
#ifdef __GNUC__
  /* On PowerPC, this will map to insn: cntlzw */
  /* On Pentium, this will map to insn: clz    */
    unsigned nlz = __builtin_clz(x);
    return nlz;
#else
    unsigned x0  = x >> 1l;
    unsigned x1  = x | x0;
    unsigned x2  = x1 >> 2l;
    unsigned x3  = x1 | x2;
    unsigned x4  = x3 >> 4l;
    unsigned x5  = x3 | x4;
    unsigned x6  = x5 >> 8l;
    unsigned x7  = x5 | x6;
    unsigned x8  = x7 >> 16l;
    unsigned x9  = x7 | x8;
    unsigned xA  = ~x9;
    unsigned xB  = xA >> 1l;
    unsigned xC  = xB & 0x55555555;
    unsigned xD  = xA - xC;
    unsigned xE  = xD & 0x33333333;
    unsigned xF  = xD >> 2l;
    unsigned x10 = xF & 0x33333333;
    unsigned x11 = xE + x10;
    unsigned x12 = x11 >> 4l;
    unsigned x13 = x11 + x12;
    unsigned x14 = x13 & 0x0f0f0f0f;
    unsigned x15 = x14 >> 8l;
    unsigned x16 = x14 + x15;
    unsigned x17 = x16 >> 16l;
    unsigned x18 = x16 + x17;
    unsigned x19 = x18 & 0x0000003f;
    return x19;
#endif
}

GLhalf float_to_half(float x) {
	union {
		float f32;
		unsigned ui32;
	} u;

	u.f32 = x;
	unsigned f = u.ui32;

	unsigned one                        = 0x00000001;
	unsigned f_e_mask                   = 0x7f800000;
	unsigned f_m_mask                   = 0x007fffff;
	unsigned f_s_mask                   = 0x80000000;
	unsigned h_e_mask                   = 0x00007c00;
	unsigned f_e_pos                    = 0x00000017;
	unsigned f_m_round_bit              = 0x00001000;
	unsigned h_nan_em_min               = 0x00007c01;
	unsigned f_h_s_pos_offset           = 0x00000010;
	unsigned f_m_hidden_bit             = 0x00800000;
	unsigned f_h_m_pos_offset           = 0x0000000d;
	unsigned f_h_bias_offset            = 0x38000000;
	unsigned f_m_snan_mask              = 0x003fffff;
	unsigned h_snan_mask                = 0x00007e00;
	unsigned f_e                        = f & f_e_mask;
	unsigned f_m                        = f & f_m_mask;
	unsigned f_s                        = f & f_s_mask;
	unsigned f_e_h_bias                 = f_e - f_h_bias_offset;
	unsigned f_e_h_bias_amount          = f_e_h_bias >> (int)f_e_pos;
	unsigned f_m_round_mask             = f_m & f_m_round_bit;
	unsigned f_m_round_offset           = f_m_round_mask << 1;
	unsigned f_m_rounded                = f_m + f_m_round_offset;
	unsigned f_m_rounded_overflow       = f_m_rounded & f_m_hidden_bit;
	unsigned f_m_denorm_sa              = one - f_e_h_bias_amount;
	unsigned f_m_with_hidden            = f_m_rounded | f_m_hidden_bit;
	unsigned f_m_denorm                 = f_m_with_hidden >> (int)f_m_denorm_sa;
	unsigned f_em_norm_packed           = f_e_h_bias | f_m_rounded;
	unsigned f_e_overflow               = f_e_h_bias + f_m_hidden_bit;
	unsigned h_s                        = f_s >> (int)f_h_s_pos_offset;
	unsigned h_m_nan                    = f_m >> (int)f_h_m_pos_offset;
	unsigned h_m_denorm                 = f_m_denorm >> (int)f_h_m_pos_offset;
	unsigned h_em_norm                  = f_em_norm_packed >> (int)f_h_m_pos_offset;
	unsigned h_em_overflow              = f_e_overflow >> (int)f_h_m_pos_offset;
	unsigned is_e_eqz_msb               = f_e - 1;
	unsigned is_m_nez_msb               = _unsigned_neg(f_m);
	unsigned is_h_m_nan_nez_msb         = _unsigned_neg(h_m_nan);
	unsigned is_e_nflagged_msb          = f_e - f_e_mask;
	unsigned is_ninf_msb                = is_e_nflagged_msb | is_m_nez_msb;
	unsigned is_underflow_msb           = is_e_eqz_msb - f_h_bias_offset;
	unsigned is_nan_nunderflow_msb      = is_h_m_nan_nez_msb | is_e_nflagged_msb;
	unsigned is_m_snan_msb              = f_m_snan_mask - f_m;
	unsigned is_snan_msb                = is_m_snan_msb & (~is_e_nflagged_msb);
	unsigned is_overflow_msb            = _unsigned_neg(f_m_rounded_overflow);
	unsigned h_nan_underflow_result     = _unsigned_sels(is_nan_nunderflow_msb, h_em_norm, h_nan_em_min);
	unsigned h_inf_result               = _unsigned_sels(is_ninf_msb, h_nan_underflow_result, h_e_mask);
	unsigned h_underflow_result         = _unsigned_sels(is_underflow_msb, h_m_denorm, h_inf_result);
	unsigned h_overflow_result          = _unsigned_sels(is_overflow_msb, h_em_overflow, h_underflow_result);
	unsigned h_em_result                = _unsigned_sels(is_snan_msb, h_snan_mask, h_overflow_result);
	unsigned h_result                   = h_em_result | h_s;
	return h_result;
}


GLfloat half_to_float(GLhalf h) {
	unsigned h_e_mask              = 0x00007c00;
	unsigned h_m_mask              = 0x000003ff;
	unsigned h_s_mask              = 0x00008000;
	unsigned h_f_s_pos_offset      = 0x00000010;
	unsigned h_f_e_pos_offset      = 0x0000000d;
	unsigned h_f_bias_offset       = 0x0001c000;
	unsigned f_e_mask              = 0x7f800000;
	unsigned f_m_mask              = 0x007fffff;
	unsigned h_f_e_denorm_bias     = 0x0000007e;
	unsigned h_f_m_denorm_sa_bias  = 0x00000008;
	unsigned f_e_pos               = 0x00000017;
	unsigned h_e_mask_minus_one    = 0x00007bff;
	unsigned h_e                   = h & h_e_mask;
	unsigned h_m                   = h & h_m_mask;
	unsigned h_s                   = h & h_s_mask;
	unsigned h_e_f_bias            = h_e + h_f_bias_offset;
	unsigned h_m_nlz               = _unsigned_cntlz(h_m);
	unsigned f_s                   = h_s << h_f_s_pos_offset;
	unsigned f_e                   = h_e_f_bias << h_f_e_pos_offset;
	unsigned f_m                   = h_m << h_f_e_pos_offset;
	unsigned f_em                  = f_e | f_m;
	unsigned h_f_m_sa              = h_m_nlz - h_f_m_denorm_sa_bias;
	unsigned f_e_denorm_unpacked   = h_f_e_denorm_bias - h_f_m_sa;
	unsigned h_f_m                 = h_m << h_f_m_sa;
	unsigned f_m_denorm            = h_f_m & f_m_mask;
	unsigned f_e_denorm            = f_e_denorm_unpacked << f_e_pos;
	unsigned f_em_denorm           = f_e_denorm | f_m_denorm;
	unsigned f_em_nan              = f_e_mask | f_m;
	unsigned is_e_eqz_msb          = h_e - 1;
	unsigned is_m_nez_msb          = _unsigned_neg(h_m);
	unsigned is_e_flagged_msb      = h_e_mask_minus_one - h_e;
	unsigned is_zero_msb           = is_e_eqz_msb & (~is_m_nez_msb);
	unsigned is_inf_msb            = is_e_flagged_msb & (~is_m_nez_msb);
	unsigned is_denorm_msb         = is_m_nez_msb & is_e_eqz_msb;
	unsigned is_nan_msb            = is_e_flagged_msb & is_m_nez_msb;
	unsigned is_zero               = ((int)is_zero_msb) >> 31; // sign-extend
	unsigned f_zero_result         = f_em & (~is_zero);
	unsigned f_denorm_result       = _unsigned_sels(is_denorm_msb, f_em_denorm, f_zero_result);
	unsigned f_inf_result          = _unsigned_sels(is_inf_msb, f_e_mask, f_denorm_result);
	unsigned f_nan_result          = _unsigned_sels(is_nan_msb, f_em_nan, f_inf_result);
	unsigned f_result              = f_s | f_nan_result;

	union {
		float f32;
		unsigned ui32;
	} u;

	u.ui32 = f_result;
	return u.f32;
}


// --------------------------------------------------------------------
// buffer offset
const GLvoid* buffer_offset(GLuint offset) {
	return ((GLubyte*)NULL + offset);
}


// --------------------------------------------------------------------
// string from file
std::string load_string_from_file(const std::string& path,
                                  bool binary) {
	// open file
	std::string contents;
	std::ifstream::openmode openMode = std::ifstream::in; 
	if(binary) openMode|= std::ifstream::binary;
	std::ifstream fileStream(path.c_str(), openMode);
	ASSERT(fileStream.is_open() && "file not found");

	// read contents
	fileStream.seekg(0, std::ios::end);
	contents.resize(fileStream.tellg());
	fileStream.seekg(0, std::ios::beg);
	fileStream.read(&contents[0], contents.size());

	// close file and return content
	fileStream.close();
	return contents;
}


// --------------------------------------------------------------------
// sleep
GLvoid sleep(GLint ms) {
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(ms*1000);
#endif
}


// --------------------------------------------------------------------
// load GLSL program
GLvoid load_glsl_program(GLuint program,
                         const std::string& srcfile,
                         const std::string& options,
                         GLboolean link) {
	ASSERT(glIsProgram(program)==GL_TRUE && "invalid name");

	// open source file
	LOG("Loading program file \"" << _clean_filename(srcfile) << "\"...");
	std::ifstream file(srcfile.c_str());
	ASSERT(file.is_open() && "file not found");

	// check first line (must be the version specification)
	std::string source;
	getline(file, source);
	ASSERT(source.find("#version") != std::string::npos && 
	        "first line must specify GLSL version.");

	// add the endline character
	source += '\n';

	// add options (if any)
	if(!options.empty())
		source += options + '\n';

	// backup position
	const size_t posbu = source.length();

	// recover whole source
	std::string line;
	while(getline(file, line))
		source += line + '\n';

	// find different stages and build shaders
	bool hasStage = false;
	if(source.find("_VERTEX_") != std::string::npos) {
		std::string vsource = source;
		vsource.insert(posbu, "#define _VERTEX_\n");
		_attach_shader(program, GL_VERTEX_SHADER, vsource.data());
		hasStage=true;
	}
	if(source.find("_TESS_CONTROL_") != std::string::npos) {
		std::string csource = source;
		csource.insert(posbu, "#define _TESS_CONTROL_\n");
		_attach_shader(program, GL_TESS_CONTROL_SHADER, csource.data());
		hasStage=true;
	}
	if(source.find("_TESS_EVALUATION_") != std::string::npos) {
		std::string esource = source;
		esource.insert(posbu, "#define _TESS_EVALUATION_\n");
		_attach_shader(program, GL_TESS_EVALUATION_SHADER, esource.data());
		hasStage=true;
	}
	if(source.find("_GEOMETRY_") != std::string::npos) {
		std::string gsource = source;
		gsource.insert(posbu, "#define _GEOMETRY_\n");
		_attach_shader(program, GL_GEOMETRY_SHADER, gsource.data());
		hasStage=true;
	}
	if(source.find("_FRAGMENT_") != std::string::npos) {
		std::string fsource = source;
		fsource.insert(posbu, "#define _FRAGMENT_\n");
		_attach_shader(program, GL_FRAGMENT_SHADER, fsource.data());
		hasStage=true;
	}
	ASSERT(hasStage && "no shader stages found in file");

	// close file
	file.close();

	// link program if requested
	if(GL_TRUE == link) {
		glLinkProgram(program);
		ASSERT(check_gl_program_link_status(program) && "link status");
	}
}


// --------------------------------------------------------------------
// Timer on the CPU
TimerCpu::TimerCpu() :
mStartTicks(0), mTicks(0.0), mIsTicking(false) {
}


GLvoid TimerCpu::Start() {
	if(!mIsTicking) {
		mIsTicking = true;
		glGetInteger64v(GL_TIMESTAMP, &mStartTicks);
	}
}


GLvoid TimerCpu::Stop() {
	if(mIsTicking) {
		mIsTicking = false;
		GLint64 now(0);
		glGetInteger64v(GL_TIMESTAMP, &now);
		mTicks = GLdouble(now - mStartTicks) / 1e9; 
	}
}


GLdouble TimerCpu::Ticks() const {
	return mTicks;
}


// --------------------------------------------------------------------
// Timer on the GPU
TimerGpu::TimerGpu() : 
mTicks(0.0), mQueries(NULL), mIsReady(GL_TRUE), mIsTicking(false) {
	mQueries = new GLuint[2];
	glGenQueries(2, mQueries);
}


TimerGpu::~TimerGpu() {
	glDeleteQueries(2, mQueries);
	delete[] mQueries;
}


GLvoid TimerGpu::Start() {
	if(!mIsTicking && mIsReady) {
		glQueryCounter(mQueries[0], GL_TIMESTAMP);
		mIsTicking = true;
	}
}


GLvoid TimerGpu::Stop() {
	if(mIsTicking && mIsReady) {
		glQueryCounter(mQueries[1], GL_TIMESTAMP);
		mIsTicking = false;
	}
}

GLdouble TimerGpu::Ticks() {
	if(!mIsTicking) {
		// check if result is available
		glGetQueryObjectiv(mQueries[1],
		                   GL_QUERY_RESULT_AVAILABLE,
		                   &mIsReady);
		if(mIsReady) {
			// get result
			GLuint64 start, stop;
			glGetQueryObjectui64v(mQueries[0],
			                      GL_QUERY_RESULT,
			                      &start);
			glGetQueryObjectui64v(mQueries[1],
			                      GL_QUERY_RESULT,
			                      &stop);
			mTicks = GLdouble(stop - start) / 1e9;
		}
	}
	return mTicks;
}


// --------------------------------------------------------------------
// Texture loading
// \TODO Use templates to lighten the code

// macros for pushing / popping the pixel unpack state
#define _GLU_PUSH_PIXEL_UNPACK_STATE() \
	{ \
		PixelStoreUnpack _pixelStoreUnpack; \
		GLint _pixelUnpackBufferBinding; \
		glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, \
		              &_pixelUnpackBufferBinding)

#define _GLU_POP_PIXEL_UNPACK_STATE() \
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, \
		             _pixelUnpackBufferBinding);\
	} do{} while(false)

// image 1D
GLvoid load_texture_image1D(const TexImage& image,
                            GLenum internalFormat,
                            GLboolean genMipmaps,
                            GLboolean immutable) {
	if(immutable)
		glTexStorage1D(GL_TEXTURE_1D,
		               _tex_image_levels(image.width, 1, 1, genMipmaps),
		               internalFormat,
		               image.width);
	else
		glTexImage1D(GL_TEXTURE_1D,
		             0,
		             internalFormat,
		             image.width,
		             0,
		             image.format,
		             image.type,
		             NULL);

	_GLU_PUSH_PIXEL_UNPACK_STATE(); // push pixel unpack state
		// set state
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, image.unpackBuffer);
		glPixelStorei(GL_UNPACK_SWAP_BYTES, image.swapBytes);
		glPixelStorei(GL_UNPACK_LSB_FIRST, image.lsbFirst);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, image.rowLength);
		glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, image.imageHeight);
		glPixelStorei(GL_UNPACK_SKIP_ROWS, image.skipRows);
		glPixelStorei(GL_UNPACK_SKIP_PIXELS, image.skipPixels);
		glPixelStorei(GL_UNPACK_SKIP_IMAGES, image.skipImages);
		glPixelStorei(GL_UNPACK_ALIGNMENT, image.alignment);

		// upload
		glTexSubImage1D(GL_TEXTURE_1D,
		                0,
		                0,
		                image.width,
		                image.format,
		                image.type,
		                image.data);
	_GLU_POP_PIXEL_UNPACK_STATE();  // pop pixel unpack state

	if(genMipmaps)
		glGenerateMipmap(GL_TEXTURE_1D);
}


// image 2D
GLvoid load_texture_image2D(const TexImage& image,
                            GLenum internalFormat,
                            GLboolean genMipmaps,
                            GLboolean immutable) {
	if(immutable)
		glTexStorage2D(GL_TEXTURE_2D,
		               _tex_image_levels(image.width,
		                                 image.height,
		                                 1,
		                                 genMipmaps),
		               internalFormat,
		               image.width,
		               image.height);
	else 
		glTexImage2D(GL_TEXTURE_2D,
		             0,
		             internalFormat,
		             image.width,
		             image.height,
		             0,
		             image.format,
		             image.type,
		             NULL);

	_GLU_PUSH_PIXEL_UNPACK_STATE(); // push pixel unpack state
		// set state
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, image.unpackBuffer);
		glPixelStorei(GL_UNPACK_SWAP_BYTES, image.swapBytes);
		glPixelStorei(GL_UNPACK_LSB_FIRST, image.lsbFirst);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, image.rowLength);
		glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, image.imageHeight);
		glPixelStorei(GL_UNPACK_SKIP_ROWS, image.skipRows);
		glPixelStorei(GL_UNPACK_SKIP_PIXELS, image.skipPixels);
		glPixelStorei(GL_UNPACK_SKIP_IMAGES, image.skipImages);
		glPixelStorei(GL_UNPACK_ALIGNMENT, image.alignment);

		// upload
		glTexSubImage2D(GL_TEXTURE_2D,
		                0,
		                0,0,
		                image.width,
		                image.height,
		                image.format,
		                image.type,
		                image.data);
	_GLU_POP_PIXEL_UNPACK_STATE();  // pop pixel unpack state

	if(genMipmaps)
		glGenerateMipmap(GL_TEXTURE_2D);
}


// image 3D
GLvoid load_texture_image3D(const TexImage& image,
                            GLenum internalFormat,
                            GLboolean genMipmaps,
                            GLboolean immutable) {
	if(immutable)
		glTexStorage3D(GL_TEXTURE_3D,
		               _tex_image_levels(image.width,
		                                 image.height,
		                                 image.depth,
		                                 genMipmaps),
		               internalFormat,
		               image.width,
		               image.height,
		               image.depth);
	else 
		glTexImage3D(GL_TEXTURE_3D,
		             0, 
		             internalFormat,
		             image.width,
		             image.height,
		             image.depth,
		             0,
		             image.format,
		             image.type,
		             NULL);

	_GLU_PUSH_PIXEL_UNPACK_STATE(); // push pixel unpack state
		// set state
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, image.unpackBuffer);
		glPixelStorei(GL_UNPACK_SWAP_BYTES, image.swapBytes);
		glPixelStorei(GL_UNPACK_LSB_FIRST, image.lsbFirst);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, image.rowLength);
		glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, image.imageHeight);
		glPixelStorei(GL_UNPACK_SKIP_ROWS, image.skipRows);
		glPixelStorei(GL_UNPACK_SKIP_PIXELS, image.skipPixels);
		glPixelStorei(GL_UNPACK_SKIP_IMAGES, image.skipImages);
		glPixelStorei(GL_UNPACK_ALIGNMENT, image.alignment);

		// upload
		glTexSubImage3D(GL_TEXTURE_3D,
		                0,
		                0,0,0,
		                image.width,
		                image.height,
		                image.depth,
		                image.format,
		                image.type,
		                image.data);
	_GLU_POP_PIXEL_UNPACK_STATE();  // pop pixel unpack state

	if(genMipmaps)
		glGenerateMipmap(GL_TEXTURE_3D);
}


// image cube map
GLvoid load_texture_cube_map(const std::vector<TexImage*>& images,
                             GLenum internalFormat,
                             GLboolean genMipmaps,
                             GLboolean immutable) {
	// check consistency
	ASSERT( images.size() > 5 && "not enough images");
	ASSERT(   images[0]->width == images[1]->width
	        && images[1]->width == images[2]->width
	        && images[2]->width == images[3]->width
	        && images[3]->width == images[4]->width
	        && images[4]->width == images[5]->width
	        && images[0]->height == images[1]->height
	        && images[1]->height == images[2]->height
	        && images[2]->height == images[3]->height
	        && images[3]->height == images[4]->height
	        && images[4]->height == images[5]->height);

	if(immutable)
		glTexStorage2D(GL_TEXTURE_CUBE_MAP,
		               _tex_image_levels(images[0]->width,
		                                 images[0]->height,
		                                 1,
		                                 genMipmaps),
		               internalFormat,
		               images[0]->width,
		               images[0]->height);
//	else
//		for(GLint i=0;i<6;++i)
//			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,
//			             0,
//			             internalFormat,
//			             images[i]->width,
//			             images[i]->height,
//			             0,
//			             images[i]->format,
//			             images[i]->type,
//			             NULL);

	_GLU_PUSH_PIXEL_UNPACK_STATE(); // push pixel unpack state
		for(GLint i=0;i<6;++i) {
			// set state
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, images[i]->unpackBuffer);
			glPixelStorei(GL_UNPACK_SWAP_BYTES, images[i]->swapBytes);
			glPixelStorei(GL_UNPACK_LSB_FIRST, images[i]->lsbFirst);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, images[i]->rowLength);
			glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, images[i]->imageHeight);
			glPixelStorei(GL_UNPACK_SKIP_ROWS, images[i]->skipRows);
			glPixelStorei(GL_UNPACK_SKIP_PIXELS, images[i]->skipPixels);
			glPixelStorei(GL_UNPACK_SKIP_IMAGES, images[i]->skipImages);
			glPixelStorei(GL_UNPACK_ALIGNMENT, images[i]->alignment);

			// upload
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,
			             0,
			             internalFormat,
			             images[i]->width,
			             images[i]->height,
			             0,
			             images[i]->format,
			             images[i]->type,
			             images[i]->data);
//			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,
//			                0,
//			                0,0,
//			                images[i]->width,
//			                images[i]->height,
//			                images[i]->format,
//			                images[i]->type,
//			                0);
		}
	_GLU_POP_PIXEL_UNPACK_STATE();  // pop pixel unpack state

	if(genMipmaps)
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}


// image 2d array
GLvoid load_texture_image2D_array(const std::vector<TexImage*>& images,
                                  GLenum internalFormat,
                                  GLboolean genMipmaps,
                                  GLboolean immutable) {
	if(immutable)
		glTexStorage3D(GL_TEXTURE_2D_ARRAY,
		               _tex_image_levels(images[0]->width,
		                                 images[0]->height,
		                                 1,
		                                 genMipmaps),
		               internalFormat,
		               images[0]->width,
		               images[0]->height,
		               images.size());
	else
		glTexImage3D(GL_TEXTURE_2D_ARRAY,
		             0,
		             internalFormat,
		             images[0]->width,
		             images[0]->height,
		             images.size(),
		             0,
		             images[0]->format,
		             images[0]->type,
		             NULL);

	_GLU_PUSH_PIXEL_UNPACK_STATE(); // push pixel unpack state
		for(size_t i=0;i<images.size();++i) {
			// set state
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, images[i]->unpackBuffer);
			glPixelStorei(GL_UNPACK_SWAP_BYTES, images[i]->swapBytes);
			glPixelStorei(GL_UNPACK_LSB_FIRST, images[i]->lsbFirst);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, images[i]->rowLength);
			glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, images[i]->imageHeight);
			glPixelStorei(GL_UNPACK_SKIP_ROWS, images[i]->skipRows);
			glPixelStorei(GL_UNPACK_SKIP_PIXELS, images[i]->skipPixels);
			glPixelStorei(GL_UNPACK_SKIP_IMAGES, images[i]->skipImages);
			glPixelStorei(GL_UNPACK_ALIGNMENT, images[i]->alignment);

			// upload
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
			                0,
			                0,0,i,
			                images[i]->width,
			                images[i]->height,
			                1,
			                images[i]->format,
			                images[i]->type,
			                images[i]->data);
		}
	_GLU_POP_PIXEL_UNPACK_STATE();  // pop pixel unpack state

	if(genMipmaps)
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}

#undef _GLU_PUSH_PIXEL_UNPACK_STATE
#undef _GLU_POP_PIXEL_UNPACK_STATE


// --------------------------------------------------------------------
// array mesh loading
GLvoid load_array_draw_data(const ArrayData& data) {
//	DrawArraysIndirectCommand cmd;
//	cmd.count     = data.count;
//	cmd.primCount = 1;
//	cmd.first     = 0;
//	cmd.baseInstance = 0;
//	glBufferData(GL_ARRAY_BUFFER,
//	             512*data.count,
//	             data.vertexData,
//	             GL_STATIC_DRAW);
//	glBufferData(GL_DRAW_INDIRECT_BUFFER,
//	             sizeof(DrawArraysIndirectCommand),
//	             &cmd,
//	             GL_STATIC_DRAW);
}


// --------------------------------------------------------------------
// indexed mesh loading
GLvoid load_indexed_array_draw_data(const ElementArrayData& data) {
//	glBufferData(GL_ARRAY_BUFFER,
//	             512*data.vertexCnt,
//	             data.vertexData,
//	             GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
//	             512*data.indexCnt,
//	             data.indexData,
//	             GL_STATIC_DRAW);
//	glBufferData(GL_DRAW_INDIRECT_BUFFER,
//	             512,
//	             NULL,
//	             GL_STATIC_DRAW);
}


////////////////////////////////////////////////////////////////////////////////
// LOADERS
//
////////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------------
// RGBA 4ub TexImage Loader
TexImageRgba4ub::TexImageRgba4ub(GLsizei w,
                                 GLsizei h,
                                 GLsizei d,
                                 GLubyte r,
                                 GLubyte g,
                                 GLubyte b,
                                 GLubyte a) {
	ASSERT(w>0 && h>0 && d>0 && "Invalid TexImage dimensions");

	// set data
	format = GL_RGBA;
	type   = GL_UNSIGNED_BYTE;
	swapBytes   = 0;
	lsbFirst    = 0;
	rowLength   = 0;
	imageHeight = 0,
	skipRows    = 0;
	skipPixels  = 0;
	skipImages  = 0;
	alignment   = 4;
	width  = w;
	height = h;
	depth  = d;
	const std::vector<GLuint> pixelData(width*height*depth,
	                                    a<<24|b<<16|g<<8|r);

	// save state
	GLint pixelUnpackBufferBinding;
	glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING,
	              &pixelUnpackBufferBinding);

	// generate pixel unpack buffer and fill
	glGenBuffers(1, &unpackBuffer);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, unpackBuffer);
		glBufferData(GL_PIXEL_UNPACK_BUFFER,
		             width*height*depth*4,
		             &pixelData[0],
		             GL_STATIC_DRAW);

	// pop state
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pixelUnpackBufferBinding);

	// set data ptr
	data = const_cast<GLvoid*>(buffer_offset(0));
}


TexImageRgba4ub::~TexImageRgba4ub() {
	glDeleteBuffers(1, &unpackBuffer);
}


// --------------------------------------------------------------------
// Tga TexImage Loader

// thanks to : http://paulbourke.net/dataformats/tga/
enum _TgaImageType {
	_TGA_TYPE_CM            = 1,
	_TGA_TYPE_RGB           = 2,
	_TGA_TYPE_LUMINANCE     = 3,
	_TGA_TYPE_CM_RLE        = 9,
	_TGA_TYPE_RGB_RLE       = 10,
	_TGA_TYPE_LUMINANCE_RLE = 11
};

////////////////////////////////////////////////////////////////////////////////
// Extract uint16 from two uint8
GLushort TexImageTga::unpackUint16(GLubyte msb, GLubyte lsb) {
	return (static_cast<GLushort>(lsb) | static_cast<GLushort>(msb) << 8);
}


////////////////////////////////////////////////////////////////////////////////
// Set format
GLvoid TexImageTga::setFormat(GLint pixelFormat) {
	switch(pixelFormat) {
		case 1: format = GL_RED;  break;
		case 2: format = GL_RG;   break;
		case 3: format = GL_BGR;  break;
		case 4: format = GL_BGRA; break;
	};
}


////////////////////////////////////////////////////////////////////////////////
// Flip horizontally
void TexImageTga::flip(GLint pixelFormat) {
	GLubyte* flippedData = new GLubyte[width*height*pixelFormat];
	for(GLushort y = 0; y<height; ++y)
		for(GLushort x = 0; x<width; ++x)
			memcpy(&flippedData[y*width*pixelFormat+x*pixelFormat],
			       &reinterpret_cast<GLubyte *>(data)
			                [(width-y)*width*pixelFormat+x*pixelFormat],
			       pixelFormat);
	delete[] reinterpret_cast<GLubyte *>(data);
	data = reinterpret_cast<GLvoid *>(flippedData);
}


////////////////////////////////////////////////////////////////////////////////
// colour mapped images
void TexImageTga::loadColourMapped(std::ifstream& fileStream,
                                   GLchar* header) {
	// set offset
	GLushort offset = unpackUint16(header[4], header[3])+header[0];
	fileStream.seekg(offset, std::ifstream::cur);

	// check image descriptor byte
	ASSERT(header[17]==0 && "Invalid image descriptor byte.");

	// get colourMap indexes
	GLuint indexSize = header[16];
	ASSERT(indexSize>0 && "Invalid bpp.");

	// check cm size
	GLuint colourMapSize = unpackUint16(header[5], header[6]);
	ASSERT(colourMapSize>0 && "Invalid colour map size.");

	GLubyte* colourMap = NULL;
	GLint pixelFormat = header[7]>>3;
	if(pixelFormat==4 || pixelFormat==3) {
		GLuint colourMapByteCnt = colourMapSize * pixelFormat;
		colourMap = new GLubyte[colourMapByteCnt];
		fileStream.read(reinterpret_cast<GLchar*>(colourMap),
		                colourMapByteCnt);
	}
	else if(pixelFormat==2) {
		colourMapSize = unpackUint16(header[5], header[6]);
		GLuint colourMapByteCnt = colourMapSize * 3;
		colourMap = new GLubyte[colourMapByteCnt];

		GLuint maxIter_cm = colourMapSize*2;
		GLushort rgb16    = 0;
		for(GLuint i=0; i<maxIter_cm; ++i) {
			fileStream.read(reinterpret_cast<GLchar*>(&rgb16), 2);
			colourMap[i*3]   = static_cast<GLubyte>((rgb16 & 0x001F)<<3);
			colourMap[i*3+1] = static_cast<GLubyte>(((rgb16 & 0x03E0)>>5)<<3);
			colourMap[i*3+2] = static_cast<GLubyte>(((rgb16 & 0x7C00)>>10)<<3);
		}
	}
	else
		ASSERT(false && "Invalid bpp.");

	// allocate pixel data
	data = reinterpret_cast<GLvoid *>(new GLubyte[width*height*pixelFormat]);

	// read data
	GLuint maxIter = width*height;
	GLubyte bytesPerIndex = header[16]>>3;
	GLuint index = 0;
	for(GLuint i=0; i<maxIter; ++i) {
		// read index
		fileStream.read(reinterpret_cast<GLchar*>(&index), bytesPerIndex);
		// get color
		memcpy(reinterpret_cast<GLubyte *>(data) + i*pixelFormat,
		       colourMap + index*pixelFormat,
		       pixelFormat);
	}

	// flip if necessary
	if(1==(header[17]>>5 & 0x01))
		flip(pixelFormat);

	// set format
	setFormat(pixelFormat);

	// free memory
	delete[] colourMap;
}


////////////////////////////////////////////////////////////////////////////////
void TexImageTga::loadLuminance(std::ifstream& fileStream,
                                GLchar* header) {
	// set offset
	GLuint offset = header[0]
	              + header[1]
	              * (unpackUint16(header[4], header[3])
	              +  unpackUint16(header[6], header[5] )
	              * (header[7]>>3));
	fileStream.seekg(offset, std::ifstream::cur);

	// read data depending on bits per pixel
	GLint pixelFormat;
	if(header[16]==8 || header[16]==16) {
		pixelFormat = header[16] >> 3;
		data        = reinterpret_cast<GLvoid *>
		              (new GLubyte[width*height*pixelFormat]);
		fileStream.read(reinterpret_cast<GLchar*>(data),
		                width*height*pixelFormat);
	}
	else
		ASSERT(false && "Invalid bpp.");

	// flip if necessary
	if(1==(header[17]>>5 & 0x01))
		flip(pixelFormat);

	// set format
	setFormat(pixelFormat);
}


////////////////////////////////////////////////////////////////////////////////
// unmapped
void TexImageTga::loadUnmapped(std::ifstream& fileStream,
                               GLchar* header) {
	// set offset
	GLuint offset = header[0]
	              + header[1]
	              * (unpackUint16(header[4], header[3])
	              +  unpackUint16(header[6], header[5] )
	              * (header[7]>>3));
	fileStream.seekg(offset, std::ifstream::cur);

	// read data depending on bits per pixel
	GLint pixelFormat;
	if(header[16]==16) {
		pixelFormat = 3;
		data        = reinterpret_cast<GLvoid *>
		              (new GLubyte[width*height*pixelFormat]);
		// load variables
		GLuint maxIter  = width*height;
		GLushort rgb16  = 0;
		for(GLuint i=0; i<maxIter; ++i) {
			fileStream.read(reinterpret_cast<GLchar*>(&rgb16), 2);
			reinterpret_cast<GLubyte *>(data)[i*3]
				= static_cast<GLubyte>((rgb16 & 0x001F)<<3);
			reinterpret_cast<GLubyte *>(data)[i*3+1]
				= static_cast<GLubyte>(((rgb16 & 0x03E0)>>5)<<3);
			reinterpret_cast<GLubyte *>(data)[i*3+2]
				= static_cast<GLubyte>(((rgb16 & 0x7C00)>>10)<<3);
		}
	}
	else if(header[16]==24 || header[16]==32) {
		pixelFormat = header[16] >> 3;
		data        = reinterpret_cast<GLvoid *>
		              (new GLubyte[width*height*pixelFormat]);
		fileStream.read(reinterpret_cast<GLchar*>(data),
		                width*height*pixelFormat);
	}
	else
		ASSERT(false && "Invalid bpp.");

	// flip if necessary
	if(1==(header[17]>>5 & 0x01))
		flip(pixelFormat);

	// set format
	setFormat(pixelFormat);
}


////////////////////////////////////////////////////////////////////////////////
// unmapped rle
void TexImageTga::loadUnmappedRle(std::ifstream& fileStream,
                                  GLchar* header) {
	// set offset
	GLuint offset = header[0]
	              + header[1]
	              * (unpackUint16(header[4], header[3])
	              +  unpackUint16(header[6], header[5] )
	              * (header[7]>>3));
	fileStream.seekg(offset, std::ifstream::cur);

	// read data depending on bits per pixel
	GLint pixelFormat;
	if(header[16]==16) {
		pixelFormat = 3;   // will be converted to bgr
		data        = reinterpret_cast<GLvoid *>
		              (new GLubyte[width*height*pixelFormat]);
		GLubyte* dataPtrMax = reinterpret_cast<GLubyte *>(data) 
		                    + (width*height*pixelFormat);
		GLubyte* dataPtr = reinterpret_cast<GLubyte *>(data);
		GLint blockSize, blockIter;
		GLubyte packetHeader = 0;
		GLushort rgb16 = 0;  // compressed data
		while(dataPtr < dataPtrMax) {
			// reset data block iterator
			blockIter = 1;
			// read first byte
			fileStream.read( reinterpret_cast<GLchar*>(&packetHeader),
			                 sizeof(GLubyte));
			blockSize = 1 + (packetHeader & 0x7F);
			fileStream.read(reinterpret_cast<GLchar*>(&rgb16), 16);  // read 16 bits
			dataPtr[0] = static_cast<GLubyte>((rgb16 & 0x001F) << 3);
			dataPtr[1] = static_cast<GLubyte>(((rgb16 & 0x03E0) >> 5) << 3);
			dataPtr[2] = static_cast<GLubyte>(((rgb16 & 0x7C00) >> 10) << 3);
			if(packetHeader & 0x80) { // RLE
				for(; blockIter<blockSize; ++blockIter)
					memcpy(dataPtr + blockIter * pixelFormat,
					       dataPtr,
					       pixelFormat);
			}
			else
				for(; blockIter<blockSize; ++blockIter) {
					fileStream.read(reinterpret_cast<GLchar*>(&rgb16), 
					                16);  // read 16 bits
					dataPtr[blockIter*pixelFormat+0] 
						= static_cast<GLubyte>((rgb16 & 0x001F) << 3);
					dataPtr[blockIter*pixelFormat+1] 
						= static_cast<GLubyte>(((rgb16 & 0x03E0) >> 5) << 3);
					dataPtr[blockIter*pixelFormat+2] 
						= static_cast<GLubyte>(((rgb16 & 0x7C00) >> 10) << 3);
				}
			// increment pixel ptr
			dataPtr+=pixelFormat*blockSize;
		}
	}
	else if(header[16]==24 || header[16]==32) {
		pixelFormat = header[16] >> 3;
		data        = reinterpret_cast<GLvoid *>
		              (new GLubyte[width*height*pixelFormat]);
		// read rle
		GLuint blockSize, blockIter;
		GLubyte* dataPtrMax  = (reinterpret_cast<GLubyte *>(data))
		                     + width*height*pixelFormat;
		GLubyte* dataPtr     = reinterpret_cast<GLubyte *>(data);
		GLubyte packetHeader = 0u;
		while(dataPtr < dataPtrMax) {
			// reset data block iterator
			blockIter = 1u;
			// read first byte
			fileStream.read(reinterpret_cast<GLchar*>(&packetHeader), 1);
			blockSize = 1u + (packetHeader & 0x7F);
			fileStream.read(reinterpret_cast<GLchar*>(dataPtr), 
			                pixelFormat);
			if(packetHeader & 0x80u)   // rle
				for(; blockIter<blockSize; ++blockIter)
					memcpy(dataPtr+blockIter*pixelFormat,
					       dataPtr,
					       pixelFormat);
			else
				for(; blockIter<blockSize; ++blockIter)
					fileStream.read(reinterpret_cast<GLchar*>(dataPtr
					                                         +blockIter
					                                         *pixelFormat),
					                pixelFormat);
			// increment pixel ptr
			dataPtr+=pixelFormat*blockSize;
		}
	}
	else
		ASSERT(false && "Invalid bpp.");


	// flip if necessary
	if(1==(header[17]>>5 & 0x01))
		flip(pixelFormat);

	// set format
	setFormat(pixelFormat);
}


////////////////////////////////////////////////////////////////////////////////
// colour mapped images rle
void TexImageTga::loadColourMappedRle(std::ifstream& fileStream,
                                      GLchar* header) {
	// set offset
	GLushort offset = unpackUint16(header[4], header[3])+header[0];
	fileStream.seekg(offset, std::ifstream::cur);

	// check image descriptor byte
	ASSERT(header[17]==0 && "Invalid image descriptor byte.");

	// get colourMap indexes
	GLuint indexSize = header[16];
	ASSERT(indexSize>0 && "Invalid bpp.");

	// check cm size
	GLuint colourMapSize = unpackUint16(header[5], header[6]);
	ASSERT(colourMapSize>0 && "Invalid colour map size.");

	GLubyte* colourMap = NULL;
	GLint pixelFormat = header[7]>>3;
	if(pixelFormat==4 || pixelFormat==3) {
		GLuint colourMapByteCnt = colourMapSize * pixelFormat;
		colourMap = new GLubyte[colourMapByteCnt];
		fileStream.read(reinterpret_cast<GLchar*>(colourMap),
		                colourMapByteCnt);
	}
	else if(pixelFormat==2) {
		colourMapSize = unpackUint16(header[5], header[6]);
		GLuint colourMapByteCnt = colourMapSize * 3;
		colourMap = new GLubyte[colourMapByteCnt];

		GLuint maxIter_cm = colourMapSize*2;
		GLushort rgb16    = 0;
		for(GLuint i=0; i<maxIter_cm; ++i) 	{
			fileStream.read(reinterpret_cast<GLchar*>(&rgb16), 2);
			colourMap[i*3]   = static_cast<GLubyte>((rgb16 & 0x001F)<<3);
			colourMap[i*3+1] = static_cast<GLubyte>(((rgb16 & 0x03E0)>>5)<<3);
			colourMap[i*3+2] = static_cast<GLubyte>(((rgb16 & 0x7C00)>>10)<<3);
		}
		pixelFormat = 3; // convert to bgr
	}
	else
		ASSERT(false && "Invalid bpp.");

	// allocate pixel data
	data = reinterpret_cast<GLvoid *>(new GLubyte[width*height*pixelFormat]);

	// read rle
	GLubyte* dataPtrMax = reinterpret_cast<GLubyte *>(data) 
	                    + width*height*pixelFormat;
	GLubyte* dataPtr = reinterpret_cast<GLubyte *>(data);
	GLuint blockSize, blockIter;
	GLubyte packetHeader = 0u;
	GLubyte bytesPerIndex = header[16]>>3;
	GLuint index = 0;
	while(dataPtr < dataPtrMax) {
		// reset data block iterator
		blockIter = 1u;
		// read first byte
		fileStream.read(reinterpret_cast<GLchar*>(&packetHeader), 1);
		blockSize = 1u + (packetHeader & 0x7F);
		fileStream.read(reinterpret_cast<GLchar*>(&index), bytesPerIndex);
		memcpy(dataPtr, &colourMap[index*pixelFormat], pixelFormat);
		if(packetHeader & 0x80u)   // rle
			for(; blockIter<blockSize; ++blockIter)
				memcpy(dataPtr+blockIter*pixelFormat, dataPtr, pixelFormat);
		else // raw
			for(; blockIter<blockSize; ++blockIter)	{
				fileStream.read(reinterpret_cast<GLchar*>(&index),
				                bytesPerIndex);
				memcpy( dataPtr+blockIter*pixelFormat,
				        &colourMap[index*pixelFormat], 
				        pixelFormat );
			}
		// increment pixel ptr
		dataPtr+=blockSize*pixelFormat;
	}

	// flip if necessary
	if(1==(header[17]>>5 & 0x01))
		flip(pixelFormat);

	// set format
	setFormat(pixelFormat);

	// free memory
	delete[] colourMap;
}


////////////////////////////////////////////////////////////////////////////////
// luminance images rle
void TexImageTga::loadLuminanceRle(std::ifstream& fileStream,
                                   GLchar* header) {
	// set offset
	GLuint offset = header[0]
	              + header[1]
	              *(unpackUint16(header[4], header[3])
	              + unpackUint16(header[6], header[5])
	              * (header[7]>>3) );
	fileStream.seekg(offset, std::ifstream::cur);

	// read data depending on bits per pixel
	GLint pixelFormat;
	if(header[16]==8 || header[16]==16) {
		pixelFormat = header[16] >> 3;
		data        = reinterpret_cast<GLvoid *>
		              (new GLubyte[width*height*pixelFormat]);

		// read rle
		GLubyte* dataPtrMax = reinterpret_cast<GLubyte *>(data)
		                    + width*height*pixelFormat;
		GLubyte* dataPtr = reinterpret_cast<GLubyte *>(data);
		GLuint blockSize, blockIter;
		GLubyte packetHeader = 0u;
		while(dataPtr < dataPtrMax) {
			// reset data block iterator
			blockIter = 1u;
			// read first byte
			fileStream.read(reinterpret_cast<GLchar*>(&packetHeader), 1);
			blockSize = 1u + (packetHeader & 0x7F);
			fileStream.read(reinterpret_cast<GLchar*>(dataPtr), pixelFormat);
			if(packetHeader & 0x80u)   // rle
				for(; blockIter<blockSize; ++blockIter)
					memcpy(dataPtr+blockIter*pixelFormat,
					       dataPtr,
					       pixelFormat );
			else
				for(; blockIter<blockSize; ++blockIter)
					fileStream.read(reinterpret_cast<GLchar*>(dataPtr
					                                         +blockIter
					                                         *pixelFormat),
					                 pixelFormat);
			// increment pixel ptr
			dataPtr+=pixelFormat*blockSize;
		}
	}
	else
		ASSERT(false && "Invalid bpp.");

	// flip if necessary
	if(1==(header[17]>>5 & 0x01))
		flip(pixelFormat);

	// set format
	setFormat(pixelFormat);
}


////////////////////////////////////////////////////////////////////////////////
// Overloaded constructor
TexImageTga::TexImageTga(const std::string& filename) {
	LOG("Loading TGA \"" << _clean_filename(filename) << "\"...");
	std::ifstream fileStream( filename.c_str(),
	                          std::ifstream::in | std::ifstream::binary );
	ASSERT(fileStream.is_open() && "File not found.");

	// read header
	GLchar header[18];   // header is 18 bytes
	fileStream.read(reinterpret_cast<char*>(header), 18);

	// get data
	type   = GL_UNSIGNED_BYTE,
	swapBytes   = 0;
	lsbFirst    = 0; 
	rowLength   = 0;
	imageHeight = 0,
	skipRows    = 0;
	skipPixels  = 0;
	skipImages  = 0;
	alignment   = 4;
	unpackBuffer = 0;
	width  = unpackUint16(header[13],header[12]);
	height = unpackUint16(header[15],header[14]);
	depth  = 1;

	// check image dimensions and pixel data
	ASSERT(width>0 && height >0);

	// load data according to image type code
	if(header[2]==_TGA_TYPE_RGB)
		loadUnmapped(fileStream, header);
	else if(header[2]==_TGA_TYPE_CM)
		loadColourMapped(fileStream, header);
	else if(header[2]==_TGA_TYPE_LUMINANCE)
		loadLuminance(fileStream, header);
	else if(header[2]==_TGA_TYPE_CM_RLE)
		loadColourMappedRle(fileStream, header);
	else if(header[2]==_TGA_TYPE_RGB_RLE)
		loadUnmappedRle(fileStream, header);
	else if(header[2]==_TGA_TYPE_LUMINANCE_RLE)
		loadLuminanceRle(fileStream, header);
	else
		ASSERT(false && "Unknown image type code.");

	fileStream.close();
}


////////////////////////////////////////////////////////////////////////////////
// Destructor
TexImageTga::~TexImageTga() {
	delete[] reinterpret_cast<GLubyte *>(data);
}


// --------------------------------------------------------------------
// Rgbe TexImage Loader


////////////////////////////////////////////////////////////////////////////////
// Internal types
struct TexImageRgbe::Rgbe {
	GLubyte r, g, b, e;
};

struct TexImageRgbe::Rgb {
	Rgb():r(1), g(0), b(0) {}
	Rgb(const TexImageRgbe::Rgbe& rgbe, GLfloat exposure) : r(0), g(0), b(0) {
		if(rgbe.e>0) {
			GLfloat v = ldexp(1.f/256.f, GLint(rgbe.e) - 128) / exposure;
			r = GLfloat(rgbe.r) * v;
			g = GLfloat(rgbe.g) * v;
			b = GLfloat(rgbe.b) * v;
		}
	}
	GLfloat r, g, b;
};


////////////////////////////////////////////////////////////////////////////////
// Load RLE (inspired from pfstools source code, Grzegorz Krawczyk)
GLvoid TexImageRgbe::loadRle(std::ifstream &fileStream, 
                             GLubyte *scanline) {
	GLint peek(0);
	while(peek < width) {
		GLubyte p[2];
		fileStream.read(reinterpret_cast<GLchar*>(p), 2);
		if(p[0]>128) {
			GLint runLength(p[0]-128);
			while(runLength>0) {
				scanline[peek++] = p[1];
				--runLength;
			}
		}
		else {
			scanline[peek++] = p[1];
			GLint nonRunLength(p[0]-1);
			if(nonRunLength>0) {
				fileStream.read(reinterpret_cast<GLchar*>(&scanline[0]+peek), 
				                nonRunLength);
				peek+= nonRunLength;
			}
		}
	}
	ASSERT(peek == width && "Difference in size while reading RLE scanline.");
}


////////////////////////////////////////////////////////////////////////////////
// Constructor
TexImageRgbe::TexImageRgbe(const std::string& filename) {
	LOG("Loading radiance file \"" << _clean_filename(filename) << "\"...");
	std::ifstream fileStream(filename.c_str(),
	                         std::ifstream::in | std::ifstream::binary);
	ASSERT(fileStream.is_open() && "File not found.");

	// check first line
	std::string buffer;
	getline(fileStream, buffer);
	ASSERT(strcmp(buffer.c_str(), "#?RADIANCE")==0
	       && "Invalid first line.");

	// get exposure and image size
	while(strcmp("", buffer.c_str())!=0) {
		getline(fileStream, buffer);
		if(buffer[0]=='#') // comment
			continue;
		if(buffer.find("EXPOSURE=") != std::string::npos)
			sscanf(buffer.c_str(), "EXPOSURE=%f", &mExposure);
	}
	fileStream >> buffer >> height >> buffer >> width;

	// eat useless lines
	while(strcmp("", buffer.c_str())!=0) {
		getline(fileStream, buffer);
	}

	// check data
	ASSERT(width>0 && height>0 && mExposure>0.0 && "Invalid data.");

	// set params
	data = reinterpret_cast<GLvoid*>(new GLfloat[width*height*3]);
	format = GL_RGB;
	type   = GL_FLOAT;
	swapBytes   = 0;
	lsbFirst    = 0; 
	rowLength   = 0;
	imageHeight = 0,
	skipRows    = 0;
	skipPixels  = 0;
	skipImages  = 0;
	alignment   = 4;
	unpackBuffer = 0;
	depth  = 1;

	// read RGBE pixels
	GLfloat *dataPtr =  reinterpret_cast<GLfloat*>(data);
	std::vector<GLubyte> scanline(width*4);
	for(GLint y=0; y<height; ++y) {
		GLubyte header[4];
#if 1
		fileStream.read(reinterpret_cast<GLchar*>(header), 4);
#else
		fileStream >> header[0] >> header[1] >> header[2] >> header[3];
#endif
		// unmapped data
		if(header[0] != 2 || header[1] != 2 
		                  || (header[2] << 8) + header[3] != width) {
			fileStream.read(reinterpret_cast<GLchar*>(&scanline[4]),
			                4*width-4);
			memcpy(reinterpret_cast<GLvoid*>(&scanline[0]),
			       reinterpret_cast<GLvoid*>(header),
			       4);  // header was first element
			// convert data
			for(GLint x=0; x<width; ++x) {
				TexImageRgbe::Rgbe rgbe;
				rgbe.r = scanline[x+width*0];
				rgbe.g = scanline[x+width*1];
				rgbe.b = scanline[x+width*2];
				rgbe.e = scanline[x+width*3];
				TexImageRgbe::Rgb rgb(rgbe,mExposure);
				dataPtr[y*width*3 + x*3 + 0] = rgb.r;
				dataPtr[y*width*3 + x*3 + 1] = rgb.g;
				dataPtr[y*width*3 + x*3 + 2] = rgb.b;
			}
		}
		// rle data
		else {
			for(GLint ch=0; ch<4; ++ch) {
				loadRle(fileStream,
				        reinterpret_cast<GLubyte*>(&scanline[0]+width*ch));
			}
			// convert data
			for(GLint x=0; x<width; ++x) {
				TexImageRgbe::Rgbe rgbe;
				rgbe.r = scanline[x+width*0];
				rgbe.g = scanline[x+width*1];
				rgbe.b = scanline[x+width*2];
				rgbe.e = scanline[x+width*3];
				TexImageRgbe::Rgb rgb(rgbe,mExposure);
//				reinterpret_cast<TexImageRgbe::Rgb*>(data)[x*height+y]
//					= TexImageRgbe::Rgb(rgbe, mExposure); // memcpy faster ?
				dataPtr[y*width*3 + x*3 + 0] = rgb.r;
				dataPtr[y*width*3 + x*3 + 1] = rgb.g;
				dataPtr[y*width*3 + x*3 + 2] = rgb.b;
			}
		}
	}

//	for(GLint y=0; y<height; ++y) 
//		for(GLint x=0; x<width; ++x) {
//			dataPtr[y*height*3 + x*3 + 0] = y/250.0f;
//			dataPtr[y*height*3 + x*3 + 1] = y/250.0f;
//			dataPtr[y*height*3 + x*3 + 2] = y/250.0f;
//		}

	// close file
	fileStream.close();
}


////////////////////////////////////////////////////////////////////////////////
// Destructor
TexImageRgbe::~TexImageRgbe() {
	delete[] reinterpret_cast<GLfloat*>(data);
}

} // namespace glu

