NAME = NoxEngine

WINDOWSSDK := ${ProgramFiles(x86)}\Microsoft SDKs\Windows\v7.1A\Lib

INCLUDES := libs/GLEW/include/GL libs/GLFW/include/GLFW libs/GLM libs/SOIL2
INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir))

CXXFLAGS := $(INCLUDE) -std=c++17
CPPFLAGS :=
LDFLAGS := 

SRCDIR := src
OBJDIR := out
DIST := dist

LIBS	:=	-lglew32 -lglfw3dll -lopengl32 -lsoil2

LIBPATHS	:=	-Llibs/GLEW/lib/Release/Win32 -Llibs/GLFW/lib-static-ucrt -Llibs/SOIL2/lib

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)          
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

all: $(OBJS) link

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@ echo !==== COMPILING ====!
	@ mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $^ -o $@

link: 
	@ echo !==== LINKING ====!
	@ mkdir -p $(DIST)
	$(CXX) $(OBJS) $(LIBPATHS) $(LIBS) -o $(DIST)/$(NAME).exe

clean:
	@ rm -r dist
	@ rm -r out