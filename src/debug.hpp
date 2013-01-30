///////////////////////////////////////////////////////////////////////
// \file debug.hpp
// \author Jonathan Dupuy (onrendering@gmail.com)
// \brief Debug macros
//
///////////////////////////////////////////////////////////////////////

#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_

// --------------------------------------------------------------------
// Includes
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>


// --------------------------------------------------------------------
// Class forward decl
namespace impl {
class Log;
}


// --------------------------------------------------------------------
// FILE macro
#ifdef _WIN32
#	define FILE (strrchr(__FILE__, '\\') ? \
		strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#	define FILE (strrchr(__FILE__, '/') ? \
		strrchr(__FILE__, '/') + 1 : __FILE__)
#endif


// --------------------------------------------------------------------
// Logger
#ifndef NDEBUG
#	define LOG(msg) do {\
		std::ostringstream __debug_stream__; \
		__debug_stream__ << msg; \
		impl::Log::GetInstance().Print(\
		__debug_stream__.str()); \
		} while(false) 
#else
#	define LOG(msg) do{} while(false)
#endif

/*
	// usage
	LOG("Hello " << "world!");
*/


// --------------------------------------------------------------------
// assert
#ifndef NDEBUG
#define ASSERT(expr) \
do {\
	if((expr) == false) {\
		LOG("Assertion failed: " << #expr \
		                         << ", " \
		                         << FILE \
		                         << ", " \
		                         << __LINE__); \
		abort(); \
	} \
} while(false)
#else
#define ASSERT(expr) do{} while(false)
#endif

/*
	// usage
	_ASSERT(a==1 && "testing equality");
*/


// ====================================================================
// Private data
namespace impl {
// --------------------------------------------------------------------
// Log class
class Log {
public:
	static Log& GetInstance();
	void Print(const std::string& message);
private:
	Log();
	~Log();
	std::ofstream mOutputStream;
};
}

#endif

