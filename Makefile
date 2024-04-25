# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alois/Desktop/projects/Fluid-Simulation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alois/Desktop/projects/Fluid-Simulation

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/opt/homebrew/Cellar/cmake/3.27.7/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/opt/homebrew/Cellar/cmake/3.27.7/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/alois/Desktop/projects/Fluid-Simulation/CMakeFiles /Users/alois/Desktop/projects/Fluid-Simulation//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/alois/Desktop/projects/Fluid-Simulation/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -P /Users/alois/Desktop/projects/Fluid-Simulation/CMakeFiles/VerifyGlobs.cmake
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named physics

# Build rule for target.
physics: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 physics
.PHONY : physics

# fast build rule for target.
physics/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/build
.PHONY : physics/fast

src/engine/compute.o: src/engine/compute.cpp.o
.PHONY : src/engine/compute.o

# target to build an object file
src/engine/compute.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/engine/compute.cpp.o
.PHONY : src/engine/compute.cpp.o

src/engine/compute.i: src/engine/compute.cpp.i
.PHONY : src/engine/compute.i

# target to preprocess a source file
src/engine/compute.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/engine/compute.cpp.i
.PHONY : src/engine/compute.cpp.i

src/engine/compute.s: src/engine/compute.cpp.s
.PHONY : src/engine/compute.s

# target to generate assembly for a file
src/engine/compute.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/engine/compute.cpp.s
.PHONY : src/engine/compute.cpp.s

src/engine/engine.o: src/engine/engine.cpp.o
.PHONY : src/engine/engine.o

# target to build an object file
src/engine/engine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/engine/engine.cpp.o
.PHONY : src/engine/engine.cpp.o

src/engine/engine.i: src/engine/engine.cpp.i
.PHONY : src/engine/engine.i

# target to preprocess a source file
src/engine/engine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/engine/engine.cpp.i
.PHONY : src/engine/engine.cpp.i

src/engine/engine.s: src/engine/engine.cpp.s
.PHONY : src/engine/engine.s

# target to generate assembly for a file
src/engine/engine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/engine/engine.cpp.s
.PHONY : src/engine/engine.cpp.s

src/engine/init.o: src/engine/init.cpp.o
.PHONY : src/engine/init.o

# target to build an object file
src/engine/init.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/engine/init.cpp.o
.PHONY : src/engine/init.cpp.o

src/engine/init.i: src/engine/init.cpp.i
.PHONY : src/engine/init.i

# target to preprocess a source file
src/engine/init.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/engine/init.cpp.i
.PHONY : src/engine/init.cpp.i

src/engine/init.s: src/engine/init.cpp.s
.PHONY : src/engine/init.s

# target to generate assembly for a file
src/engine/init.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/engine/init.cpp.s
.PHONY : src/engine/init.cpp.s

src/engine/utils.o: src/engine/utils.cpp.o
.PHONY : src/engine/utils.o

# target to build an object file
src/engine/utils.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/engine/utils.cpp.o
.PHONY : src/engine/utils.cpp.o

src/engine/utils.i: src/engine/utils.cpp.i
.PHONY : src/engine/utils.i

# target to preprocess a source file
src/engine/utils.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/engine/utils.cpp.i
.PHONY : src/engine/utils.cpp.i

src/engine/utils.s: src/engine/utils.cpp.s
.PHONY : src/engine/utils.s

# target to generate assembly for a file
src/engine/utils.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/engine/utils.cpp.s
.PHONY : src/engine/utils.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/objects/particle.o: src/objects/particle.cpp.o
.PHONY : src/objects/particle.o

# target to build an object file
src/objects/particle.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/objects/particle.cpp.o
.PHONY : src/objects/particle.cpp.o

src/objects/particle.i: src/objects/particle.cpp.i
.PHONY : src/objects/particle.i

# target to preprocess a source file
src/objects/particle.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/objects/particle.cpp.i
.PHONY : src/objects/particle.cpp.i

src/objects/particle.s: src/objects/particle.cpp.s
.PHONY : src/objects/particle.s

# target to generate assembly for a file
src/objects/particle.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/objects/particle.cpp.s
.PHONY : src/objects/particle.cpp.s

src/render/display.o: src/render/display.cpp.o
.PHONY : src/render/display.o

# target to build an object file
src/render/display.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/render/display.cpp.o
.PHONY : src/render/display.cpp.o

src/render/display.i: src/render/display.cpp.i
.PHONY : src/render/display.i

# target to preprocess a source file
src/render/display.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/render/display.cpp.i
.PHONY : src/render/display.cpp.i

src/render/display.s: src/render/display.cpp.s
.PHONY : src/render/display.s

# target to generate assembly for a file
src/render/display.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/physics.dir/build.make CMakeFiles/physics.dir/src/render/display.cpp.s
.PHONY : src/render/display.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... physics"
	@echo "... src/engine/compute.o"
	@echo "... src/engine/compute.i"
	@echo "... src/engine/compute.s"
	@echo "... src/engine/engine.o"
	@echo "... src/engine/engine.i"
	@echo "... src/engine/engine.s"
	@echo "... src/engine/init.o"
	@echo "... src/engine/init.i"
	@echo "... src/engine/init.s"
	@echo "... src/engine/utils.o"
	@echo "... src/engine/utils.i"
	@echo "... src/engine/utils.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/objects/particle.o"
	@echo "... src/objects/particle.i"
	@echo "... src/objects/particle.s"
	@echo "... src/render/display.o"
	@echo "... src/render/display.i"
	@echo "... src/render/display.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -P /Users/alois/Desktop/projects/Fluid-Simulation/CMakeFiles/VerifyGlobs.cmake
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

