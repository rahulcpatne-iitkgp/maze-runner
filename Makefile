# Compiler settings
CXX       ?= g++
CXXFLAGS  := -W -Wall -Wno-unused-result -O3 -std=c++17 \
             -Iinclude/algorithms -Iinclude/maze

# Directories
SRCDIR    := src
BUILDDIR  := build
INCDIR    := include
RESULTDIR := result

# Source files
SRC_ALG   := $(wildcard $(SRCDIR)/algorithms/*.cpp)
SRC_MAZE  := $(wildcard $(SRCDIR)/maze/*.cpp)
SRC_MAIN  := main.cpp

# Object files (mirror src/ subdirs under build/)
OBJ_ALG   := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC_ALG))
OBJ_MAZE  := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC_MAZE))
OBJ_MAIN  := $(BUILDDIR)/main.o

OBJECTS   := $(OBJ_ALG) $(OBJ_MAZE) $(OBJ_MAIN)

# Default target
.PHONY: all
all: mazegen

# Link executable
mazegen: $(OBJECTS)
	@echo "Building $@"
	@$(CXX) $(OBJECTS) -o $@ $(CXXFLAGS)

# Compile .cpp → .o
# this rule covers both src/algorithms/*.cpp and src/maze/*.cpp
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

# Compile main.cpp
$(BUILDDIR)/main.o: $(SRC_MAIN)
	@mkdir -p $(BUILDDIR)
	@echo "Compiling $<"
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

# Clean up everything
.PHONY: clean
clean:
	@echo "Cleaning build, executable, and results…"
	@rm -rf $(BUILDDIR) mazegen
	@find $(RESULTDIR) -maxdepth 1 -type f -name '*.svg' -exec rm -f {} +