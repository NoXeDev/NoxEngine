NAME = NoxEngine
WINDOWSSDK := ${ProgramFiles(x86)}\Microsoft SDKs\Windows\v7.1A\Lib

INCLUDES := libs/GLEW/include/GL libs/GLFW/include/GLFW libs/GLM libs/SOIL2
INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir))

CXXFLAGS := $(INCLUDE) -std=c++17
CPPFLAGS :=
LDFLAGS := 

ifndef config
  config=debug
endif

ifeq ($(config),debug)
  CXXFLAGS += -g
endif
CLEAN :=
ifeq ($(config),release)
  CLEAN := clean
endif

SRCDIR := src
OBJDIR := out
DIST := dist

LIBS	:=	-lglew32 -lglfw3dll -lopengl32 -lsoil2

LIBPATHS	:=	-Llibs/GLEW/lib/Release/Win32 -Llibs/GLFW/lib-static-ucrt -Llibs/SOIL2/lib

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)          
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

all: $(CLEAN) $(OBJS) link prepare

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@ echo !==== COMPILING ====!
	@ mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $^ -o $@

link: 
	@ echo !==== LINKING ====!
	@ mkdir -p $(DIST)
	$(CXX) $(OBJS) $(LIBPATHS) $(LIBS) -o $(DIST)/$(NAME).exe

prepare:
	@ echo !==== PREPARE DIST ====!
	@ mkdir -p $(DIST)
# copy dll in dist directory
	@ cp libs/GLEW/bin/Release/Win32/glew32.dll dist/glew32.dll
	@ cp libs/GLFW/lib-static-ucrt/glfw3.dll dist/glfw3.dll
	@ cp libs/SOIL2/lib/soil2.dll dist/soil2.dll
# copy res folder into dist directory
	@ cp -r test/res dist/res
# copy shaders into dist directory
	@ cp -r $(SRCDIR)/shaders/glsl dist/res/shaders

clean:
	@ rm -r dist
	@ rm -r out