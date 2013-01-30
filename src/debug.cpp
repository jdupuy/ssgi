///////////////////////////////////////////////////////////////////////
// \file debug.cpp
// \author Jonathan Dupuy (onrendering@gmail.com)
// \brief Debug macros
//
///////////////////////////////////////////////////////////////////////


// --------------------------------------------------------------------
// Includes
#include <cassert>
#include <iostream>
#include "debug.hpp"

// private namespace
namespace impl {

///////////////////////////////////////////////////////////////////////
// Get Instance
Log& Log::GetInstance() {
	static Log log;
	return log;
}


///////////////////////////////////////////////////////////////////////
// Constructor
Log::Log() : mOutputStream("log.txt") {
	assert(mOutputStream.is_open() && "Failed to create log file.");
	mOutputStream << __DATE__ <<':' << __TIME__ << '\n';
	mOutputStream << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << '\n';
}


///////////////////////////////////////////////////////////////////////
// Destructor
Log::~Log() {
	mOutputStream.close();
}


///////////////////////////////////////////////////////////////////////
// Print
void Log::Print(const std::string& message) {
	mOutputStream << "> "
	              << message
	              << std::endl;
	std::cout << message << std::endl;
}

} // namespace impl

