##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## debug
ProjectName            :=DEMOGL
ConfigurationName      :=debug
IntermediateDirectory  :=obj/debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jdups/sources/libs/premake-4.3/build/codelite.unix"
ProjectPath            := "/home/jdups/sources/projects/ssgi/build/codelite.unix"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=jdups
Date                   :=13-02-04
CodeLitePath           :="/home/jdups/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=../../bin/debug/DEMOGL
Preprocessors          :=$(PreprocessorSwitch)DEBUG $(PreprocessorSwitch)_UNIX 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -Wall $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/anttweakbar" "$(IncludeSwitch)../../src/gl3w" "$(IncludeSwitch)../../src/freeglut" "$(IncludeSwitch)../../src/math" 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)X11 $(LibrarySwitch)GL $(LibrarySwitch)Xext $(LibrarySwitch)m 
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/gl3w_gl3w$(ObjectSuffix) $(IntermediateDirectory)/anttweakbar_TwEventGLUT$(ObjectSuffix) $(IntermediateDirectory)/anttweakbar_TwBar$(ObjectSuffix) $(IntermediateDirectory)/anttweakbar_LoadOGL$(ObjectSuffix) $(IntermediateDirectory)/anttweakbar_TwOpenGLCore$(ObjectSuffix) $(IntermediateDirectory)/anttweakbar_LoadOGLCore$(ObjectSuffix) $(IntermediateDirectory)/anttweakbar_TwMgr$(ObjectSuffix) $(IntermediateDirectory)/anttweakbar_TwOpenGL$(ObjectSuffix) $(IntermediateDirectory)/anttweakbar_TwPrecomp$(ObjectSuffix) $(IntermediateDirectory)/anttweakbar_TwColors$(ObjectSuffix) \
	$(IntermediateDirectory)/anttweakbar_TwFonts$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_display$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_init$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_callbacks$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_stroke_roman$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_gamemode$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_main$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_window$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_glutfont_definitions$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_ext$(ObjectSuffix) \
	$(IntermediateDirectory)/freeglut_freeglut_cursor$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_spaceball$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_misc$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_input_devices$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_font_data$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_stroke_mono_roman$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_structure$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_geometry$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_teapot$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_font$(ObjectSuffix) \
	$(IntermediateDirectory)/freeglut_freeglut_xinput$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_state$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_joystick$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_menu$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_overlay$(ObjectSuffix) $(IntermediateDirectory)/freeglut_freeglut_videoresize$(ObjectSuffix) $(IntermediateDirectory)/math_Affine$(ObjectSuffix) $(IntermediateDirectory)/math_Matrix2x2$(ObjectSuffix) $(IntermediateDirectory)/math_Vector2$(ObjectSuffix) $(IntermediateDirectory)/math_Matrix4x4$(ObjectSuffix) \
	$(IntermediateDirectory)/math_Vector3$(ObjectSuffix) $(IntermediateDirectory)/math_Projection$(ObjectSuffix) $(IntermediateDirectory)/math_Matrix3x3$(ObjectSuffix) $(IntermediateDirectory)/math_Vector4$(ObjectSuffix) $(IntermediateDirectory)/src_glu$(ObjectSuffix) $(IntermediateDirectory)/src_main$(ObjectSuffix) $(IntermediateDirectory)/src_debug$(ObjectSuffix) $(IntermediateDirectory)/src_callbacks$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d obj/debug || $(MakeDirCommand) obj/debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/gl3w_gl3w$(ObjectSuffix): ../../src/gl3w/gl3w.c $(IntermediateDirectory)/gl3w_gl3w$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/gl3w/gl3w.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/gl3w_gl3w$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gl3w_gl3w$(DependSuffix): ../../src/gl3w/gl3w.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/gl3w_gl3w$(ObjectSuffix) -MF$(IntermediateDirectory)/gl3w_gl3w$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/gl3w/gl3w.c"

$(IntermediateDirectory)/gl3w_gl3w$(PreprocessSuffix): ../../src/gl3w/gl3w.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gl3w_gl3w$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/gl3w/gl3w.c"

$(IntermediateDirectory)/anttweakbar_TwEventGLUT$(ObjectSuffix): ../../src/anttweakbar/TwEventGLUT.c $(IntermediateDirectory)/anttweakbar_TwEventGLUT$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwEventGLUT.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/anttweakbar_TwEventGLUT$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/anttweakbar_TwEventGLUT$(DependSuffix): ../../src/anttweakbar/TwEventGLUT.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/anttweakbar_TwEventGLUT$(ObjectSuffix) -MF$(IntermediateDirectory)/anttweakbar_TwEventGLUT$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwEventGLUT.c"

$(IntermediateDirectory)/anttweakbar_TwEventGLUT$(PreprocessSuffix): ../../src/anttweakbar/TwEventGLUT.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/anttweakbar_TwEventGLUT$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwEventGLUT.c"

$(IntermediateDirectory)/anttweakbar_TwBar$(ObjectSuffix): ../../src/anttweakbar/TwBar.cpp $(IntermediateDirectory)/anttweakbar_TwBar$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwBar.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/anttweakbar_TwBar$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/anttweakbar_TwBar$(DependSuffix): ../../src/anttweakbar/TwBar.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/anttweakbar_TwBar$(ObjectSuffix) -MF$(IntermediateDirectory)/anttweakbar_TwBar$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwBar.cpp"

$(IntermediateDirectory)/anttweakbar_TwBar$(PreprocessSuffix): ../../src/anttweakbar/TwBar.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/anttweakbar_TwBar$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwBar.cpp"

$(IntermediateDirectory)/anttweakbar_LoadOGL$(ObjectSuffix): ../../src/anttweakbar/LoadOGL.cpp $(IntermediateDirectory)/anttweakbar_LoadOGL$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/anttweakbar/LoadOGL.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/anttweakbar_LoadOGL$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/anttweakbar_LoadOGL$(DependSuffix): ../../src/anttweakbar/LoadOGL.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/anttweakbar_LoadOGL$(ObjectSuffix) -MF$(IntermediateDirectory)/anttweakbar_LoadOGL$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/anttweakbar/LoadOGL.cpp"

$(IntermediateDirectory)/anttweakbar_LoadOGL$(PreprocessSuffix): ../../src/anttweakbar/LoadOGL.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/anttweakbar_LoadOGL$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/anttweakbar/LoadOGL.cpp"

$(IntermediateDirectory)/anttweakbar_TwOpenGLCore$(ObjectSuffix): ../../src/anttweakbar/TwOpenGLCore.cpp $(IntermediateDirectory)/anttweakbar_TwOpenGLCore$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwOpenGLCore.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/anttweakbar_TwOpenGLCore$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/anttweakbar_TwOpenGLCore$(DependSuffix): ../../src/anttweakbar/TwOpenGLCore.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/anttweakbar_TwOpenGLCore$(ObjectSuffix) -MF$(IntermediateDirectory)/anttweakbar_TwOpenGLCore$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwOpenGLCore.cpp"

$(IntermediateDirectory)/anttweakbar_TwOpenGLCore$(PreprocessSuffix): ../../src/anttweakbar/TwOpenGLCore.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/anttweakbar_TwOpenGLCore$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwOpenGLCore.cpp"

$(IntermediateDirectory)/anttweakbar_LoadOGLCore$(ObjectSuffix): ../../src/anttweakbar/LoadOGLCore.cpp $(IntermediateDirectory)/anttweakbar_LoadOGLCore$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/anttweakbar/LoadOGLCore.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/anttweakbar_LoadOGLCore$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/anttweakbar_LoadOGLCore$(DependSuffix): ../../src/anttweakbar/LoadOGLCore.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/anttweakbar_LoadOGLCore$(ObjectSuffix) -MF$(IntermediateDirectory)/anttweakbar_LoadOGLCore$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/anttweakbar/LoadOGLCore.cpp"

$(IntermediateDirectory)/anttweakbar_LoadOGLCore$(PreprocessSuffix): ../../src/anttweakbar/LoadOGLCore.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/anttweakbar_LoadOGLCore$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/anttweakbar/LoadOGLCore.cpp"

$(IntermediateDirectory)/anttweakbar_TwMgr$(ObjectSuffix): ../../src/anttweakbar/TwMgr.cpp $(IntermediateDirectory)/anttweakbar_TwMgr$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwMgr.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/anttweakbar_TwMgr$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/anttweakbar_TwMgr$(DependSuffix): ../../src/anttweakbar/TwMgr.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/anttweakbar_TwMgr$(ObjectSuffix) -MF$(IntermediateDirectory)/anttweakbar_TwMgr$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwMgr.cpp"

$(IntermediateDirectory)/anttweakbar_TwMgr$(PreprocessSuffix): ../../src/anttweakbar/TwMgr.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/anttweakbar_TwMgr$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwMgr.cpp"

$(IntermediateDirectory)/anttweakbar_TwOpenGL$(ObjectSuffix): ../../src/anttweakbar/TwOpenGL.cpp $(IntermediateDirectory)/anttweakbar_TwOpenGL$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwOpenGL.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/anttweakbar_TwOpenGL$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/anttweakbar_TwOpenGL$(DependSuffix): ../../src/anttweakbar/TwOpenGL.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/anttweakbar_TwOpenGL$(ObjectSuffix) -MF$(IntermediateDirectory)/anttweakbar_TwOpenGL$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwOpenGL.cpp"

$(IntermediateDirectory)/anttweakbar_TwOpenGL$(PreprocessSuffix): ../../src/anttweakbar/TwOpenGL.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/anttweakbar_TwOpenGL$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwOpenGL.cpp"

$(IntermediateDirectory)/anttweakbar_TwPrecomp$(ObjectSuffix): ../../src/anttweakbar/TwPrecomp.cpp $(IntermediateDirectory)/anttweakbar_TwPrecomp$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwPrecomp.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/anttweakbar_TwPrecomp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/anttweakbar_TwPrecomp$(DependSuffix): ../../src/anttweakbar/TwPrecomp.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/anttweakbar_TwPrecomp$(ObjectSuffix) -MF$(IntermediateDirectory)/anttweakbar_TwPrecomp$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwPrecomp.cpp"

$(IntermediateDirectory)/anttweakbar_TwPrecomp$(PreprocessSuffix): ../../src/anttweakbar/TwPrecomp.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/anttweakbar_TwPrecomp$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwPrecomp.cpp"

$(IntermediateDirectory)/anttweakbar_TwColors$(ObjectSuffix): ../../src/anttweakbar/TwColors.cpp $(IntermediateDirectory)/anttweakbar_TwColors$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwColors.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/anttweakbar_TwColors$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/anttweakbar_TwColors$(DependSuffix): ../../src/anttweakbar/TwColors.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/anttweakbar_TwColors$(ObjectSuffix) -MF$(IntermediateDirectory)/anttweakbar_TwColors$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwColors.cpp"

$(IntermediateDirectory)/anttweakbar_TwColors$(PreprocessSuffix): ../../src/anttweakbar/TwColors.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/anttweakbar_TwColors$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwColors.cpp"

$(IntermediateDirectory)/anttweakbar_TwFonts$(ObjectSuffix): ../../src/anttweakbar/TwFonts.cpp $(IntermediateDirectory)/anttweakbar_TwFonts$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwFonts.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/anttweakbar_TwFonts$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/anttweakbar_TwFonts$(DependSuffix): ../../src/anttweakbar/TwFonts.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/anttweakbar_TwFonts$(ObjectSuffix) -MF$(IntermediateDirectory)/anttweakbar_TwFonts$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwFonts.cpp"

$(IntermediateDirectory)/anttweakbar_TwFonts$(PreprocessSuffix): ../../src/anttweakbar/TwFonts.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/anttweakbar_TwFonts$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/anttweakbar/TwFonts.cpp"

$(IntermediateDirectory)/freeglut_freeglut_display$(ObjectSuffix): ../../src/freeglut/freeglut_display.c $(IntermediateDirectory)/freeglut_freeglut_display$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_display.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_display$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_display$(DependSuffix): ../../src/freeglut/freeglut_display.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_display$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_display$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_display.c"

$(IntermediateDirectory)/freeglut_freeglut_display$(PreprocessSuffix): ../../src/freeglut/freeglut_display.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_display$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_display.c"

$(IntermediateDirectory)/freeglut_freeglut_init$(ObjectSuffix): ../../src/freeglut/freeglut_init.c $(IntermediateDirectory)/freeglut_freeglut_init$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_init.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_init$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_init$(DependSuffix): ../../src/freeglut/freeglut_init.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_init$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_init$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_init.c"

$(IntermediateDirectory)/freeglut_freeglut_init$(PreprocessSuffix): ../../src/freeglut/freeglut_init.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_init$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_init.c"

$(IntermediateDirectory)/freeglut_freeglut_callbacks$(ObjectSuffix): ../../src/freeglut/freeglut_callbacks.c $(IntermediateDirectory)/freeglut_freeglut_callbacks$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_callbacks.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_callbacks$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_callbacks$(DependSuffix): ../../src/freeglut/freeglut_callbacks.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_callbacks$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_callbacks$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_callbacks.c"

$(IntermediateDirectory)/freeglut_freeglut_callbacks$(PreprocessSuffix): ../../src/freeglut/freeglut_callbacks.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_callbacks$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_callbacks.c"

$(IntermediateDirectory)/freeglut_freeglut_stroke_roman$(ObjectSuffix): ../../src/freeglut/freeglut_stroke_roman.c $(IntermediateDirectory)/freeglut_freeglut_stroke_roman$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_stroke_roman.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_stroke_roman$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_stroke_roman$(DependSuffix): ../../src/freeglut/freeglut_stroke_roman.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_stroke_roman$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_stroke_roman$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_stroke_roman.c"

$(IntermediateDirectory)/freeglut_freeglut_stroke_roman$(PreprocessSuffix): ../../src/freeglut/freeglut_stroke_roman.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_stroke_roman$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_stroke_roman.c"

$(IntermediateDirectory)/freeglut_freeglut_gamemode$(ObjectSuffix): ../../src/freeglut/freeglut_gamemode.c $(IntermediateDirectory)/freeglut_freeglut_gamemode$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_gamemode.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_gamemode$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_gamemode$(DependSuffix): ../../src/freeglut/freeglut_gamemode.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_gamemode$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_gamemode$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_gamemode.c"

$(IntermediateDirectory)/freeglut_freeglut_gamemode$(PreprocessSuffix): ../../src/freeglut/freeglut_gamemode.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_gamemode$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_gamemode.c"

$(IntermediateDirectory)/freeglut_freeglut_main$(ObjectSuffix): ../../src/freeglut/freeglut_main.c $(IntermediateDirectory)/freeglut_freeglut_main$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_main.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_main$(DependSuffix): ../../src/freeglut/freeglut_main.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_main$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_main$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_main.c"

$(IntermediateDirectory)/freeglut_freeglut_main$(PreprocessSuffix): ../../src/freeglut/freeglut_main.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_main$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_main.c"

$(IntermediateDirectory)/freeglut_freeglut_window$(ObjectSuffix): ../../src/freeglut/freeglut_window.c $(IntermediateDirectory)/freeglut_freeglut_window$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_window.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_window$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_window$(DependSuffix): ../../src/freeglut/freeglut_window.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_window$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_window$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_window.c"

$(IntermediateDirectory)/freeglut_freeglut_window$(PreprocessSuffix): ../../src/freeglut/freeglut_window.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_window$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_window.c"

$(IntermediateDirectory)/freeglut_freeglut_glutfont_definitions$(ObjectSuffix): ../../src/freeglut/freeglut_glutfont_definitions.c $(IntermediateDirectory)/freeglut_freeglut_glutfont_definitions$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_glutfont_definitions.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_glutfont_definitions$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_glutfont_definitions$(DependSuffix): ../../src/freeglut/freeglut_glutfont_definitions.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_glutfont_definitions$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_glutfont_definitions$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_glutfont_definitions.c"

$(IntermediateDirectory)/freeglut_freeglut_glutfont_definitions$(PreprocessSuffix): ../../src/freeglut/freeglut_glutfont_definitions.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_glutfont_definitions$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_glutfont_definitions.c"

$(IntermediateDirectory)/freeglut_freeglut_ext$(ObjectSuffix): ../../src/freeglut/freeglut_ext.c $(IntermediateDirectory)/freeglut_freeglut_ext$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_ext.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_ext$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_ext$(DependSuffix): ../../src/freeglut/freeglut_ext.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_ext$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_ext$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_ext.c"

$(IntermediateDirectory)/freeglut_freeglut_ext$(PreprocessSuffix): ../../src/freeglut/freeglut_ext.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_ext$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_ext.c"

$(IntermediateDirectory)/freeglut_freeglut_cursor$(ObjectSuffix): ../../src/freeglut/freeglut_cursor.c $(IntermediateDirectory)/freeglut_freeglut_cursor$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_cursor.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_cursor$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_cursor$(DependSuffix): ../../src/freeglut/freeglut_cursor.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_cursor$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_cursor$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_cursor.c"

$(IntermediateDirectory)/freeglut_freeglut_cursor$(PreprocessSuffix): ../../src/freeglut/freeglut_cursor.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_cursor$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_cursor.c"

$(IntermediateDirectory)/freeglut_freeglut_spaceball$(ObjectSuffix): ../../src/freeglut/freeglut_spaceball.c $(IntermediateDirectory)/freeglut_freeglut_spaceball$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_spaceball.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_spaceball$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_spaceball$(DependSuffix): ../../src/freeglut/freeglut_spaceball.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_spaceball$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_spaceball$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_spaceball.c"

$(IntermediateDirectory)/freeglut_freeglut_spaceball$(PreprocessSuffix): ../../src/freeglut/freeglut_spaceball.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_spaceball$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_spaceball.c"

$(IntermediateDirectory)/freeglut_freeglut_misc$(ObjectSuffix): ../../src/freeglut/freeglut_misc.c $(IntermediateDirectory)/freeglut_freeglut_misc$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_misc.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_misc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_misc$(DependSuffix): ../../src/freeglut/freeglut_misc.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_misc$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_misc$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_misc.c"

$(IntermediateDirectory)/freeglut_freeglut_misc$(PreprocessSuffix): ../../src/freeglut/freeglut_misc.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_misc$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_misc.c"

$(IntermediateDirectory)/freeglut_freeglut_input_devices$(ObjectSuffix): ../../src/freeglut/freeglut_input_devices.c $(IntermediateDirectory)/freeglut_freeglut_input_devices$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_input_devices.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_input_devices$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_input_devices$(DependSuffix): ../../src/freeglut/freeglut_input_devices.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_input_devices$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_input_devices$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_input_devices.c"

$(IntermediateDirectory)/freeglut_freeglut_input_devices$(PreprocessSuffix): ../../src/freeglut/freeglut_input_devices.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_input_devices$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_input_devices.c"

$(IntermediateDirectory)/freeglut_freeglut_font_data$(ObjectSuffix): ../../src/freeglut/freeglut_font_data.c $(IntermediateDirectory)/freeglut_freeglut_font_data$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_font_data.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_font_data$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_font_data$(DependSuffix): ../../src/freeglut/freeglut_font_data.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_font_data$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_font_data$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_font_data.c"

$(IntermediateDirectory)/freeglut_freeglut_font_data$(PreprocessSuffix): ../../src/freeglut/freeglut_font_data.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_font_data$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_font_data.c"

$(IntermediateDirectory)/freeglut_freeglut_stroke_mono_roman$(ObjectSuffix): ../../src/freeglut/freeglut_stroke_mono_roman.c $(IntermediateDirectory)/freeglut_freeglut_stroke_mono_roman$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_stroke_mono_roman.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_stroke_mono_roman$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_stroke_mono_roman$(DependSuffix): ../../src/freeglut/freeglut_stroke_mono_roman.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_stroke_mono_roman$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_stroke_mono_roman$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_stroke_mono_roman.c"

$(IntermediateDirectory)/freeglut_freeglut_stroke_mono_roman$(PreprocessSuffix): ../../src/freeglut/freeglut_stroke_mono_roman.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_stroke_mono_roman$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_stroke_mono_roman.c"

$(IntermediateDirectory)/freeglut_freeglut_structure$(ObjectSuffix): ../../src/freeglut/freeglut_structure.c $(IntermediateDirectory)/freeglut_freeglut_structure$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_structure.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_structure$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_structure$(DependSuffix): ../../src/freeglut/freeglut_structure.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_structure$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_structure$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_structure.c"

$(IntermediateDirectory)/freeglut_freeglut_structure$(PreprocessSuffix): ../../src/freeglut/freeglut_structure.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_structure$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_structure.c"

$(IntermediateDirectory)/freeglut_freeglut_geometry$(ObjectSuffix): ../../src/freeglut/freeglut_geometry.c $(IntermediateDirectory)/freeglut_freeglut_geometry$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_geometry.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_geometry$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_geometry$(DependSuffix): ../../src/freeglut/freeglut_geometry.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_geometry$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_geometry$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_geometry.c"

$(IntermediateDirectory)/freeglut_freeglut_geometry$(PreprocessSuffix): ../../src/freeglut/freeglut_geometry.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_geometry$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_geometry.c"

$(IntermediateDirectory)/freeglut_freeglut_teapot$(ObjectSuffix): ../../src/freeglut/freeglut_teapot.c $(IntermediateDirectory)/freeglut_freeglut_teapot$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_teapot.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_teapot$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_teapot$(DependSuffix): ../../src/freeglut/freeglut_teapot.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_teapot$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_teapot$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_teapot.c"

$(IntermediateDirectory)/freeglut_freeglut_teapot$(PreprocessSuffix): ../../src/freeglut/freeglut_teapot.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_teapot$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_teapot.c"

$(IntermediateDirectory)/freeglut_freeglut_font$(ObjectSuffix): ../../src/freeglut/freeglut_font.c $(IntermediateDirectory)/freeglut_freeglut_font$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_font.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_font$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_font$(DependSuffix): ../../src/freeglut/freeglut_font.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_font$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_font$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_font.c"

$(IntermediateDirectory)/freeglut_freeglut_font$(PreprocessSuffix): ../../src/freeglut/freeglut_font.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_font$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_font.c"

$(IntermediateDirectory)/freeglut_freeglut_xinput$(ObjectSuffix): ../../src/freeglut/freeglut_xinput.c $(IntermediateDirectory)/freeglut_freeglut_xinput$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_xinput.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_xinput$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_xinput$(DependSuffix): ../../src/freeglut/freeglut_xinput.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_xinput$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_xinput$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_xinput.c"

$(IntermediateDirectory)/freeglut_freeglut_xinput$(PreprocessSuffix): ../../src/freeglut/freeglut_xinput.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_xinput$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_xinput.c"

$(IntermediateDirectory)/freeglut_freeglut_state$(ObjectSuffix): ../../src/freeglut/freeglut_state.c $(IntermediateDirectory)/freeglut_freeglut_state$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_state.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_state$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_state$(DependSuffix): ../../src/freeglut/freeglut_state.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_state$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_state$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_state.c"

$(IntermediateDirectory)/freeglut_freeglut_state$(PreprocessSuffix): ../../src/freeglut/freeglut_state.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_state$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_state.c"

$(IntermediateDirectory)/freeglut_freeglut_joystick$(ObjectSuffix): ../../src/freeglut/freeglut_joystick.c $(IntermediateDirectory)/freeglut_freeglut_joystick$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_joystick.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_joystick$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_joystick$(DependSuffix): ../../src/freeglut/freeglut_joystick.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_joystick$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_joystick$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_joystick.c"

$(IntermediateDirectory)/freeglut_freeglut_joystick$(PreprocessSuffix): ../../src/freeglut/freeglut_joystick.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_joystick$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_joystick.c"

$(IntermediateDirectory)/freeglut_freeglut_menu$(ObjectSuffix): ../../src/freeglut/freeglut_menu.c $(IntermediateDirectory)/freeglut_freeglut_menu$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_menu.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_menu$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_menu$(DependSuffix): ../../src/freeglut/freeglut_menu.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_menu$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_menu$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_menu.c"

$(IntermediateDirectory)/freeglut_freeglut_menu$(PreprocessSuffix): ../../src/freeglut/freeglut_menu.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_menu$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_menu.c"

$(IntermediateDirectory)/freeglut_freeglut_overlay$(ObjectSuffix): ../../src/freeglut/freeglut_overlay.c $(IntermediateDirectory)/freeglut_freeglut_overlay$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_overlay.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_overlay$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_overlay$(DependSuffix): ../../src/freeglut/freeglut_overlay.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_overlay$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_overlay$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_overlay.c"

$(IntermediateDirectory)/freeglut_freeglut_overlay$(PreprocessSuffix): ../../src/freeglut/freeglut_overlay.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_overlay$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_overlay.c"

$(IntermediateDirectory)/freeglut_freeglut_videoresize$(ObjectSuffix): ../../src/freeglut/freeglut_videoresize.c $(IntermediateDirectory)/freeglut_freeglut_videoresize$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_videoresize.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freeglut_freeglut_videoresize$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freeglut_freeglut_videoresize$(DependSuffix): ../../src/freeglut/freeglut_videoresize.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freeglut_freeglut_videoresize$(ObjectSuffix) -MF$(IntermediateDirectory)/freeglut_freeglut_videoresize$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_videoresize.c"

$(IntermediateDirectory)/freeglut_freeglut_videoresize$(PreprocessSuffix): ../../src/freeglut/freeglut_videoresize.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/freeglut_freeglut_videoresize$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/freeglut/freeglut_videoresize.c"

$(IntermediateDirectory)/math_Affine$(ObjectSuffix): ../../src/math/Affine.cpp $(IntermediateDirectory)/math_Affine$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/math/Affine.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/math_Affine$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_Affine$(DependSuffix): ../../src/math/Affine.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/math_Affine$(ObjectSuffix) -MF$(IntermediateDirectory)/math_Affine$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/math/Affine.cpp"

$(IntermediateDirectory)/math_Affine$(PreprocessSuffix): ../../src/math/Affine.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_Affine$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/math/Affine.cpp"

$(IntermediateDirectory)/math_Matrix2x2$(ObjectSuffix): ../../src/math/Matrix2x2.cpp $(IntermediateDirectory)/math_Matrix2x2$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/math/Matrix2x2.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/math_Matrix2x2$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_Matrix2x2$(DependSuffix): ../../src/math/Matrix2x2.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/math_Matrix2x2$(ObjectSuffix) -MF$(IntermediateDirectory)/math_Matrix2x2$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/math/Matrix2x2.cpp"

$(IntermediateDirectory)/math_Matrix2x2$(PreprocessSuffix): ../../src/math/Matrix2x2.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_Matrix2x2$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/math/Matrix2x2.cpp"

$(IntermediateDirectory)/math_Vector2$(ObjectSuffix): ../../src/math/Vector2.cpp $(IntermediateDirectory)/math_Vector2$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/math/Vector2.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/math_Vector2$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_Vector2$(DependSuffix): ../../src/math/Vector2.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/math_Vector2$(ObjectSuffix) -MF$(IntermediateDirectory)/math_Vector2$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/math/Vector2.cpp"

$(IntermediateDirectory)/math_Vector2$(PreprocessSuffix): ../../src/math/Vector2.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_Vector2$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/math/Vector2.cpp"

$(IntermediateDirectory)/math_Matrix4x4$(ObjectSuffix): ../../src/math/Matrix4x4.cpp $(IntermediateDirectory)/math_Matrix4x4$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/math/Matrix4x4.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/math_Matrix4x4$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_Matrix4x4$(DependSuffix): ../../src/math/Matrix4x4.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/math_Matrix4x4$(ObjectSuffix) -MF$(IntermediateDirectory)/math_Matrix4x4$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/math/Matrix4x4.cpp"

$(IntermediateDirectory)/math_Matrix4x4$(PreprocessSuffix): ../../src/math/Matrix4x4.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_Matrix4x4$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/math/Matrix4x4.cpp"

$(IntermediateDirectory)/math_Vector3$(ObjectSuffix): ../../src/math/Vector3.cpp $(IntermediateDirectory)/math_Vector3$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/math/Vector3.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/math_Vector3$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_Vector3$(DependSuffix): ../../src/math/Vector3.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/math_Vector3$(ObjectSuffix) -MF$(IntermediateDirectory)/math_Vector3$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/math/Vector3.cpp"

$(IntermediateDirectory)/math_Vector3$(PreprocessSuffix): ../../src/math/Vector3.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_Vector3$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/math/Vector3.cpp"

$(IntermediateDirectory)/math_Projection$(ObjectSuffix): ../../src/math/Projection.cpp $(IntermediateDirectory)/math_Projection$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/math/Projection.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/math_Projection$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_Projection$(DependSuffix): ../../src/math/Projection.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/math_Projection$(ObjectSuffix) -MF$(IntermediateDirectory)/math_Projection$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/math/Projection.cpp"

$(IntermediateDirectory)/math_Projection$(PreprocessSuffix): ../../src/math/Projection.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_Projection$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/math/Projection.cpp"

$(IntermediateDirectory)/math_Matrix3x3$(ObjectSuffix): ../../src/math/Matrix3x3.cpp $(IntermediateDirectory)/math_Matrix3x3$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/math/Matrix3x3.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/math_Matrix3x3$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_Matrix3x3$(DependSuffix): ../../src/math/Matrix3x3.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/math_Matrix3x3$(ObjectSuffix) -MF$(IntermediateDirectory)/math_Matrix3x3$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/math/Matrix3x3.cpp"

$(IntermediateDirectory)/math_Matrix3x3$(PreprocessSuffix): ../../src/math/Matrix3x3.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_Matrix3x3$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/math/Matrix3x3.cpp"

$(IntermediateDirectory)/math_Vector4$(ObjectSuffix): ../../src/math/Vector4.cpp $(IntermediateDirectory)/math_Vector4$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/math/Vector4.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/math_Vector4$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_Vector4$(DependSuffix): ../../src/math/Vector4.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/math_Vector4$(ObjectSuffix) -MF$(IntermediateDirectory)/math_Vector4$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/math/Vector4.cpp"

$(IntermediateDirectory)/math_Vector4$(PreprocessSuffix): ../../src/math/Vector4.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_Vector4$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/math/Vector4.cpp"

$(IntermediateDirectory)/src_glu$(ObjectSuffix): ../../src/glu.cpp $(IntermediateDirectory)/src_glu$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/glu.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_glu$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_glu$(DependSuffix): ../../src/glu.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_glu$(ObjectSuffix) -MF$(IntermediateDirectory)/src_glu$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/glu.cpp"

$(IntermediateDirectory)/src_glu$(PreprocessSuffix): ../../src/glu.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_glu$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/glu.cpp"

$(IntermediateDirectory)/src_main$(ObjectSuffix): ../../src/main.cpp $(IntermediateDirectory)/src_main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main$(DependSuffix): ../../src/main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_main$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/main.cpp"

$(IntermediateDirectory)/src_main$(PreprocessSuffix): ../../src/main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/main.cpp"

$(IntermediateDirectory)/src_debug$(ObjectSuffix): ../../src/debug.cpp $(IntermediateDirectory)/src_debug$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/debug.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_debug$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_debug$(DependSuffix): ../../src/debug.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_debug$(ObjectSuffix) -MF$(IntermediateDirectory)/src_debug$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/debug.cpp"

$(IntermediateDirectory)/src_debug$(PreprocessSuffix): ../../src/debug.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_debug$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/debug.cpp"

$(IntermediateDirectory)/src_callbacks$(ObjectSuffix): ../../src/callbacks.cpp $(IntermediateDirectory)/src_callbacks$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jdups/sources/projects/ssgi/src/callbacks.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_callbacks$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_callbacks$(DependSuffix): ../../src/callbacks.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_callbacks$(ObjectSuffix) -MF$(IntermediateDirectory)/src_callbacks$(DependSuffix) -MM "/home/jdups/sources/projects/ssgi/src/callbacks.cpp"

$(IntermediateDirectory)/src_callbacks$(PreprocessSuffix): ../../src/callbacks.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_callbacks$(PreprocessSuffix) "/home/jdups/sources/projects/ssgi/src/callbacks.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/gl3w_gl3w$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/gl3w_gl3w$(DependSuffix)
	$(RM) $(IntermediateDirectory)/gl3w_gl3w$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwEventGLUT$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwEventGLUT$(DependSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwEventGLUT$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwBar$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwBar$(DependSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwBar$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_LoadOGL$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_LoadOGL$(DependSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_LoadOGL$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwOpenGLCore$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwOpenGLCore$(DependSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwOpenGLCore$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_LoadOGLCore$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_LoadOGLCore$(DependSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_LoadOGLCore$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwMgr$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwMgr$(DependSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwMgr$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwOpenGL$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwOpenGL$(DependSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwOpenGL$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwPrecomp$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwPrecomp$(DependSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwPrecomp$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwColors$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwColors$(DependSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwColors$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwFonts$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwFonts$(DependSuffix)
	$(RM) $(IntermediateDirectory)/anttweakbar_TwFonts$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_display$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_display$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_display$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_init$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_init$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_init$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_callbacks$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_callbacks$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_callbacks$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_stroke_roman$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_stroke_roman$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_stroke_roman$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_gamemode$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_gamemode$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_gamemode$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_window$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_window$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_window$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_glutfont_definitions$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_glutfont_definitions$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_glutfont_definitions$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_ext$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_ext$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_ext$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_cursor$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_cursor$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_cursor$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_spaceball$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_spaceball$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_spaceball$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_misc$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_misc$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_misc$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_input_devices$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_input_devices$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_input_devices$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_font_data$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_font_data$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_font_data$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_stroke_mono_roman$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_stroke_mono_roman$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_stroke_mono_roman$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_structure$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_structure$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_structure$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_geometry$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_geometry$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_geometry$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_teapot$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_teapot$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_teapot$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_font$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_font$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_font$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_xinput$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_xinput$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_xinput$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_state$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_state$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_state$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_joystick$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_joystick$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_joystick$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_menu$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_menu$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_menu$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_overlay$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_overlay$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_overlay$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_videoresize$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_videoresize$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freeglut_freeglut_videoresize$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_Affine$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_Affine$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_Affine$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_Matrix2x2$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_Matrix2x2$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_Matrix2x2$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_Vector2$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_Vector2$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_Vector2$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_Matrix4x4$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_Matrix4x4$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_Matrix4x4$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_Vector3$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_Vector3$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_Vector3$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_Projection$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_Projection$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_Projection$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_Matrix3x3$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_Matrix3x3$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_Matrix3x3$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/math_Vector4$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/math_Vector4$(DependSuffix)
	$(RM) $(IntermediateDirectory)/math_Vector4$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_glu$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_glu$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_glu$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_debug$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_debug$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_debug$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_callbacks$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_callbacks$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_callbacks$(PreprocessSuffix)
	$(RM) $(OutputFile)


