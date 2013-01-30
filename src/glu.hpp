///////////////////////////////////////////////////////////////////////
// \file glu.hpp
// \author Jonathan Dupuy (onrendering@gmail.com)
// \brief OpenGL helper functions. All the functions restore 
//  the OpenGL state as it was prior to their execution.
//
///////////////////////////////////////////////////////////////////////

#ifndef _GLU_HPP_
#define _GLU_HPP_

// --------------------------------------------------------------------
// Includes
#include "GL3/gl3w.h"
#include "debug.hpp"
#include <vector>


namespace glu {

// --------------------------------------------------------------------
// OpenGL debug

	// Perform State checks
	// Return GL_FALSE in case of failure
	GLboolean check_gl_extension_support(const std::string& name);
	// These print additional information (if any) to the log file
	GLboolean check_gl_no_error();
	GLboolean check_gl_framebuffer_complete();
	GLboolean check_gl_program_link_status(GLuint program);

	// Sets up debug output (if available)
	GLvoid init_gl_debug_output();


// --------------------------------------------------------------------
// Screenshots

	// Save a portion of the OpenGL front/back buffer (= take a screenshot).
	// File will be a TGA in BGR format, uncompressed.
	// The OpenGL state is restored the way it was before this function call.
	// User should make sure the dimensions of the screenshot are less or 
	// equal to the front buffer size
	GLvoid save_gl_front_buffer(GLint x,
	                            GLint y,
	                            GLsizei width,
	                            GLsizei height);


// --------------------------------------------------------------------
// Draw commands

	// Indirect drawing command : DrawArraysIndirectCommand
	typedef struct {
		GLuint count;
		GLuint primCount;
		GLuint first;
		GLuint baseInstance;
	} DrawArraysIndirectCommand;


	// Indirect drawing command : DrawElementsIndirectCommand
	typedef struct {
		GLuint count;
		GLuint primCount;
		GLuint firstIndex;
		GLint baseVertex;
		GLuint baseInstance;
	} DrawElementsIndirectCommand;


// --------------------------------------------------------------------
// Atomic manipulation

	// power of twos
	GLboolean is_power_of_two(GLuint number);
	GLuint next_power_of_two(GLuint number);
	GLuint next_power_of_two_exponent(GLuint number);

	// float <-> half
	GLhalf float_to_half(GLfloat f);
	GLfloat half_to_float(GLhalf h);

	// Pack four normalized floats in an unsigned integer using
	// equation 2.1 from August 6, 2012 GL4.3 core profile specs.
	// The values must be in range [0.f,1.f] (checked ifndef NDEBUG)
	// Memory layout: msb                                 lsb
	//                wwzz zzzz zzzz yyyy yyyy yyxx xxxx xxxx
	GLuint pack_4f_to_uint_2_10_10_10_rev(GLfloat x,
	                                      GLfloat y,
	                                      GLfloat z,
	                                      GLfloat w);
	GLuint pack_4fv_to_uint_2_10_10_10_rev(const GLfloat *v);

	// Pack four normalized floats in a signed integer using
	// equation 2.2 from August 6, 2012 GL4.3 core profile specs.
	// The values must be in range [-1.f,1.f] (checked ifndef NDEBUG)
	// Memory layout: msb                                 lsb
	//                wwzz zzzz zzzz yyyy yyyy yyxx xxxx xxxx
	GLint pack_4f_to_int_2_10_10_10_rev(GLfloat x,
	                                    GLfloat y,
	                                    GLfloat z,
	                                    GLfloat w);
	GLint pack_4fv_to_int_2_10_10_10_rev(const GLfloat *v);

	// Convert RGB8 to packed types.
	GLubyte pack_3ub_to_ubyte_3_3_2(GLubyte r,
	                                GLubyte g,
	                                GLubyte b);
	GLushort pack_3ub_to_ushort_4_4_4(GLubyte r,
	                                  GLubyte g,
	                                  GLubyte b);
	GLushort pack_3ub_to_ushort_5_5_5(GLubyte r,
	                                  GLubyte g,
	                                  GLubyte b);
	GLushort pack_3ub_to_ushort_5_6_5(GLubyte r,
	                                  GLubyte g,
	                                  GLubyte b);
	GLubyte pack_3ubv_to_ubyte_3_3_2(const GLubyte *v);
	GLushort pack_3ubv_to_ushort_4_4_4(const GLubyte *v);
	GLushort pack_3ubv_to_ushort_5_5_5(const GLubyte *v);
	GLushort pack_3ubv_to_ushort_5_6_5(const GLubyte *v);

	// Convert RGBA8 to packed types.
	GLushort pack_4ub_to_ushort_4_4_4_4(GLubyte r,
	                                    GLubyte g,
	                                    GLubyte b,
	                                    GLubyte a);
	GLushort pack_4ub_to_ushort_5_5_5_1(GLubyte r,
	                                    GLubyte g,
	                                    GLubyte b,
	                                    GLubyte a);
	GLushort pack_4ubv_to_ushort_4_4_4_4(const GLubyte *v);
	GLushort pack_4ubv_to_ushort_5_5_5_1(const GLubyte *v);


// --------------------------------------------------------------------
// Misc.

	// Safely cast an offset pointer for various calls (such as DrawElements)
	const GLvoid* buffer_offset(GLuint offset);

	// Read the content of a file
	std::string load_string_from_file(const std::string& path,
	                                  bool binary);

	// Sleep for a specific amount of milliseconds
	GLvoid sleep(GLint ms);


// --------------------------------------------------------------------
// Timing (requires GL_ARB_timer_query)

	// Each Ticks() call should be preceded by a Start() / Stop() call
	// If a Ticks() query is performed before a Stop() call, the previous result
	// of a Start/Stop cycle is returned.

	// CPU Timer
	class TimerCpu {
	public:
		// Constructor / Destructor
		TimerCpu();

		// Manipulation
		GLvoid Start();
		GLvoid Stop();
		GLdouble Ticks() const;
	private:
		// Members
		GLint64 mStartTicks; // start time
		GLdouble mTicks;     // last ticks
		bool mIsTicking;     // running flag
	};

	// Asynchronous GPU timer
	// It is safe to interleave some Timers (some implementations may 
	// generate OpenGL errors, but not this one)
	class TimerGpu {
	public:
		// Constructor / Destructor
		TimerGpu();
		~TimerGpu();

		// Manipulation
		GLvoid Start();
		GLvoid Stop();
		GLdouble Ticks();
	private:
		// Members
		GLdouble mTicks;    // last time
		GLuint *mQueries;   // query objects
		GLint mIsReady;     // ready flag
		bool mIsTicking;    // running flag
	};


// --------------------------------------------------------------------
// Program loader

	// Build a GLSL program from an "effect" file
	GLvoid load_glsl_program(GLuint program,
	                         const std::string& srcfile,
	                         const std::string& options,
	                         GLboolean link);


// --------------------------------------------------------------------
// Texture loaders

	// TexImage data
	typedef struct {
		GLvoid *data;       // data pointer
		GLenum format;      // R, RG, RGB, RGBA
		GLenum type;        // data type
		GLint swapBytes, lsbFirst, rowLength, imageHeight; // packing
		GLint skipRows, skipPixels, skipImages, alignment; // packing ctd
		GLuint unpackBuffer;  // buffer to read from
		GLsizei width, height, depth; // dimensions
	} TexImage;

	typedef std::vector<TexImage*> TexImageArray; // Array of TexImages

	// loads data to a bound GL_TEXTURE_1D
	GLvoid load_texture_image1D(const TexImage& image,
	                            GLenum internalFormat,
	                            GLboolean genMipmaps,
	                            GLboolean immutable);


	// loads data to a bound GL_TEXTURE_2D
	GLvoid load_texture_image2D(const TexImage& image,
	                            GLenum internalFormat,
	                            GLboolean genMipmaps,
	                            GLboolean immutable);


	// loads data to a bound GL_TEXTURE_3D
	GLvoid load_texture_image3D(const TexImage& image,
	                            GLenum internalFormat,
	                            GLboolean genMipmaps,
	                            GLboolean immutable);


	// loads data to a bound GL_TEXTURE_CUBE_MAP
	GLvoid load_texture_cube_map(const TexImageArray& images,
	                             GLenum internalFormat,
	                             GLboolean genMipmaps,
	                             GLboolean immutable);


	// loads data to a bound GL_TEXTURE_2D_ARRAY
	GLvoid load_texture_image2D_array(const TexImageArray& images,
	                                  GLenum internalFormat,
	                                  GLboolean genMipmaps,
	                                  GLboolean immutable);


	// RGBA4ub TexImage loader (see glu.cpp)
	class TexImageRgba4ub : public TexImage {
	public:
		TexImageRgba4ub(GLsizei width, GLsizei height, GLsizei depth, 
		                GLubyte r, GLubyte g, GLubyte b, GLubyte a);
		~TexImageRgba4ub();
	private:
		// Non copyable
		TexImageRgba4ub(const TexImageRgba4ub& rgba);
		TexImageRgba4ub& operator=(const TexImageRgba4ub& rgba);
	};


	// TGA TexImage loader (see glu.cpp)
	class TexImageTga : public TexImage {
	public:
		TexImageTga(const std::string& filename);
		~TexImageTga();
	private:
		// Non copyable
		TexImageTga(const TexImageTga& tga);
		TexImageTga& operator= (const TexImageTga& tga);

		// internal manipulation
		GLushort unpackUint16(GLubyte msb, GLubyte lsb);
		GLvoid flip(GLint);
		GLvoid setFormat(GLint);
		GLvoid loadColourMapped(std::ifstream&, GLchar*);
		GLvoid loadLuminance(std::ifstream&, GLchar*);
		GLvoid loadUnmapped(std::ifstream&, GLchar*);
		GLvoid loadUnmappedRle(std::ifstream&, GLchar*);
		GLvoid loadColourMappedRle(std::ifstream&, GLchar*);
		GLvoid loadLuminanceRle(std::ifstream&, GLchar*);
	};


	// Radiance (.hdr) TexImage loader
	class TexImageRgbe : public TexImage {
	public:
		TexImageRgbe(const std::string& filename);
		~TexImageRgbe();
		GLfloat GetExposure() const;
	private:
		// Non copyable
		TexImageRgbe(const TexImageRgbe& rgbe);
		TexImageRgbe& operator= (const TexImageRgbe& rgbe);

		// Internal manipulation
		struct Rgbe;
		struct Rgb;
		GLvoid loadRle(std::ifstream&, GLubyte*);

		// Members
		GLfloat mExposure;
	};


// --------------------------------------------------------------------
// Mesh loaders

	// Data pointer attributes
	typedef struct {
		GLvoid *pointer; // data pointer
		GLint size;      // number of components
		GLenum type;     // type
		GLsizei stride;  // stride
	} AttribPointer;

	typedef struct {
		std::vector<AttribPointer> attribs; // array of attributes
		GLvoid *data; // vertex data
		GLuint count; // vertex count
	} ArrayData;

	typedef struct {
		GLvoid *indexData;  // index data
		GLenum type;   // type of indices
		GLuint count;  // index count
	} ElementArrayData;

	// loads mesh data to bound GL_ARRAY_BUFFER and GL_DRAW_INDIRECT_BUFFER.
	GLvoid load_array_draw_data(const ArrayData& data);


	// loads mesh data to bound GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER
	// and GL_DRAW_INDIRECT_BUFFER.
	GLvoid load_indexed_array_draw_data(const ElementArrayData& data);


//	// Cube indexed mesh.
//	// Provides vertex positions, normals and texcoords with 
//	// a cube parametrization
//	class UnitTriangleMeshedCube : public IndexedArrayData {
//	public:
//		enum VertexAttrib {
//			VERTEX_ATTRIB_POSITION =0,
//			VERTEX_ATTRIB_NORMAL,
//			VERTEX_ATTRIB_TEXCOORD,
//			VERTEX_ATTRIB_COLOUR,
//			VERTEX_ATTRIB_COUNT
//		};
//		UnitTriangleMeshedCube();
//		~UnitTriangleMeshedCube();
//	};

} // namespace glu

#endif

