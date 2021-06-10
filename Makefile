NAME = NoxEngine

INCLUDES := libs/GLEW/include/GL libs/GLFW/include/GLFW libs/GLM libs/SOIL2
INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir))

CXXFLAGS := $(INCLUDE) -std=c++17
CPPFLAGS :=
LDFLAGS := 

ifndef config
  config=debug
endif

ifeq ($(config),release)
  LDFLAGS += -Wl,--subsystem,windows
  CXXFLAGS += -O3
endif

ifeq ($(config),debug)
  CXXFLAGS += -g
  CPPFLAGS += -Ddebug
endif

SRCDIR := src
OBJDIR := out
DIST := dist

LIBS	:=	-lglew32 -lglfw3dll -lopengl32 -lsoil2

LIBPATHS	:=	-Llibs/GLEW/lib/Release/Win32 -Llibs/GLFW/lib-static-ucrt -Llibs/SOIL2/lib

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)          
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

all: $(OBJS) link prepare

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@ echo !==== COMPILING ====!
	@ mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $^ -o $@

link: 
	@ echo !==== LINKING ====!
	@ mkdir -p $(DIST)
	$(CXX) $(OBJS) $(LDFLAGS) $(LIBPATHS) $(LIBS) -o $(DIST)/$(NAME).exe

prepare:
	@ echo !==== PREPARE DIST ====!
	@ mkdir -p $(DIST)
# copy dll in dist directory
	@ cp libs/GLEW/bin/Release/Win32/glew32.dll dist/glew32.dll
	@ cp libs/GLFW/lib-static-ucrt/glfw3.dll dist/glfw3.dll
	@ cp libs/SOIL2/lib/soil2.dll dist/soil2.dll
	@ cp libs/mingw/libgcc_s_dw2-1.dll dist/libgcc_s_dw2-1.dll
	@ cp libs/mingw/libstdc++-6.dll dist/libstdc++-6.dll
# copy res folder into dist directory and root
	@ cp -r test/res dist/
	@ cp -r test/res .
# copy shaders into dist directory and root
	@ cp -r $(SRCDIR)/shaders/glsl dist/res/
	@ cp -r $(SRCDIR)/shaders/glsl res/

clean:
	@ rm -r dist
	@ rm -r out
	@ rm -r res