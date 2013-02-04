# GNU Make project makefile autogenerated by Premake
ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifeq ($(config),debug)
  OBJDIR     = obj/debug
  TARGETDIR  = ../../bin/debug
  TARGET     = $(TARGETDIR)/DEMOGL
  DEFINES   += -DDEBUG -D_UNIX
  INCLUDES  += -I../../src/anttweakbar -I../../src/gl3w -I../../src/freeglut -I../../src/math
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g -Wall
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += 
  LIBS      += -lX11 -lGL -lXext -lm
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/release
  TARGETDIR  = ../../bin/release
  TARGET     = $(TARGETDIR)/DEMOGL
  DEFINES   += -DNDEBUG -D_UNIX
  INCLUDES  += -I../../src/anttweakbar -I../../src/gl3w -I../../src/freeglut -I../../src/math
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O2
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -s
  LIBS      += -lX11 -lGL -lXext -lm
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/glu.o \
	$(OBJDIR)/main.o \
	$(OBJDIR)/debug.o \
	$(OBJDIR)/callbacks.o \
	$(OBJDIR)/gl3w.o \
	$(OBJDIR)/TwEventGLUT.o \
	$(OBJDIR)/freeglut_display.o \
	$(OBJDIR)/freeglut_init.o \
	$(OBJDIR)/freeglut_callbacks.o \
	$(OBJDIR)/freeglut_stroke_roman.o \
	$(OBJDIR)/freeglut_gamemode.o \
	$(OBJDIR)/freeglut_main.o \
	$(OBJDIR)/freeglut_window.o \
	$(OBJDIR)/freeglut_glutfont_definitions.o \
	$(OBJDIR)/freeglut_ext.o \
	$(OBJDIR)/freeglut_cursor.o \
	$(OBJDIR)/freeglut_spaceball.o \
	$(OBJDIR)/freeglut_misc.o \
	$(OBJDIR)/freeglut_input_devices.o \
	$(OBJDIR)/freeglut_font_data.o \
	$(OBJDIR)/freeglut_stroke_mono_roman.o \
	$(OBJDIR)/freeglut_structure.o \
	$(OBJDIR)/freeglut_geometry.o \
	$(OBJDIR)/freeglut_teapot.o \
	$(OBJDIR)/freeglut_font.o \
	$(OBJDIR)/freeglut_xinput.o \
	$(OBJDIR)/freeglut_state.o \
	$(OBJDIR)/freeglut_joystick.o \
	$(OBJDIR)/freeglut_menu.o \
	$(OBJDIR)/freeglut_overlay.o \
	$(OBJDIR)/freeglut_videoresize.o \
	$(OBJDIR)/TwBar.o \
	$(OBJDIR)/LoadOGL.o \
	$(OBJDIR)/TwOpenGLCore.o \
	$(OBJDIR)/LoadOGLCore.o \
	$(OBJDIR)/TwMgr.o \
	$(OBJDIR)/TwOpenGL.o \
	$(OBJDIR)/TwPrecomp.o \
	$(OBJDIR)/TwColors.o \
	$(OBJDIR)/TwFonts.o \
	$(OBJDIR)/Affine.o \
	$(OBJDIR)/Matrix2x2.o \
	$(OBJDIR)/Vector2.o \
	$(OBJDIR)/Matrix4x4.o \
	$(OBJDIR)/Vector3.o \
	$(OBJDIR)/Projection.o \
	$(OBJDIR)/Matrix3x3.o \
	$(OBJDIR)/Vector4.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking DEMOGL
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning DEMOGL
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/glu.o: ../../src/glu.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/main.o: ../../src/main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/debug.o: ../../src/debug.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/callbacks.o: ../../src/callbacks.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/gl3w.o: ../../src/gl3w/gl3w.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TwEventGLUT.o: ../../src/anttweakbar/TwEventGLUT.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_display.o: ../../src/freeglut/freeglut_display.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_init.o: ../../src/freeglut/freeglut_init.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_callbacks.o: ../../src/freeglut/freeglut_callbacks.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_stroke_roman.o: ../../src/freeglut/freeglut_stroke_roman.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_gamemode.o: ../../src/freeglut/freeglut_gamemode.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_main.o: ../../src/freeglut/freeglut_main.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_window.o: ../../src/freeglut/freeglut_window.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_glutfont_definitions.o: ../../src/freeglut/freeglut_glutfont_definitions.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_ext.o: ../../src/freeglut/freeglut_ext.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_cursor.o: ../../src/freeglut/freeglut_cursor.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_spaceball.o: ../../src/freeglut/freeglut_spaceball.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_misc.o: ../../src/freeglut/freeglut_misc.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_input_devices.o: ../../src/freeglut/freeglut_input_devices.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_font_data.o: ../../src/freeglut/freeglut_font_data.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_stroke_mono_roman.o: ../../src/freeglut/freeglut_stroke_mono_roman.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_structure.o: ../../src/freeglut/freeglut_structure.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_geometry.o: ../../src/freeglut/freeglut_geometry.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_teapot.o: ../../src/freeglut/freeglut_teapot.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_font.o: ../../src/freeglut/freeglut_font.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_xinput.o: ../../src/freeglut/freeglut_xinput.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_state.o: ../../src/freeglut/freeglut_state.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_joystick.o: ../../src/freeglut/freeglut_joystick.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_menu.o: ../../src/freeglut/freeglut_menu.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_overlay.o: ../../src/freeglut/freeglut_overlay.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/freeglut_videoresize.o: ../../src/freeglut/freeglut_videoresize.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TwBar.o: ../../src/anttweakbar/TwBar.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/LoadOGL.o: ../../src/anttweakbar/LoadOGL.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TwOpenGLCore.o: ../../src/anttweakbar/TwOpenGLCore.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/LoadOGLCore.o: ../../src/anttweakbar/LoadOGLCore.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TwMgr.o: ../../src/anttweakbar/TwMgr.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TwOpenGL.o: ../../src/anttweakbar/TwOpenGL.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TwPrecomp.o: ../../src/anttweakbar/TwPrecomp.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TwColors.o: ../../src/anttweakbar/TwColors.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TwFonts.o: ../../src/anttweakbar/TwFonts.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Affine.o: ../../src/math/Affine.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Matrix2x2.o: ../../src/math/Matrix2x2.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Vector2.o: ../../src/math/Vector2.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Matrix4x4.o: ../../src/math/Matrix4x4.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Vector3.o: ../../src/math/Vector3.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Projection.o: ../../src/math/Projection.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Matrix3x3.o: ../../src/math/Matrix3x3.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Vector4.o: ../../src/math/Vector4.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)