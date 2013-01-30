-- ---------------------------------------------------------
solution "OpenGL"
	configurations {"debug", "release"}
	location       ( _OPTIONS["to"] )


-- ---------------------------------------------------------
-- Project 
	project "DEMOGL"
		targetname  "DEMOGL"
		language    "C++"
		kind        "ConsoleApp"
		includedirs {"../anttweakbar", "../gl3w", "../freeglut", "../math"}
		files       { "../*.cpp" }
		files       { "../**.c", "../anttweakbar/*.cpp", "../math/*.cpp"}

		-- exclude os specific files
		excludes {
			"../anttweakbar/TwEventWin.c",
			"../anttweakbar/TwEventX11.c"
		}

-- Debug configuration
	configuration   {"debug"}
		targetdir   "../../bin/debug"
		defines     {"DEBUG"}
		flags       {"Symbols", "ExtraWarnings"}

-- Release configuration
	configuration   {"release"}
		targetdir   "../../bin/release"
		defines     {"NDEBUG"}
		flags       {"Optimize"}

-- unix specific
	configuration   {"linux"}
		links       {"X11", "GL", "Xext", "m"}
		defines     {"_UNIX"}
		files       {"../anttweakbar/TwEventX11.c"}

-- macosx specific  
	configuration    "macosx"
			defines  {"LUA_USE_MACOSX"}

	configuration    {"macosx", "gmake"}
		buildoptions {"-mmacosx-version-min=10.1"}
		linkoptions  {"-lstdc++-static", "-mmacosx-version-min=10.1"}

-- windows specific
	configuration    "windows"
		files        {"../anttweakbar/TwEventWin.c"}

	configuration    "vs*"
		defines      {"_CRT_SECURE_NO_WARNINGS"}

-- cleanup
	if _ACTION == "clean" then
		os.rmdir("../../bin")
		os.rmdir("../../build")
	end

--
-- Use the --to=path option to control where the project files get generated. I use
-- this to create project files for each supported toolset, each in their own folder,
-- in preparation for deployment.
--
	newoption {
		trigger = "to",
		value   = "path",
		description = "Set the output location for the generated files"
	}

