# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.10.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.10.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/karlnico/project-links/final-project-6122/final_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/karlnico/project-links/final-project-6122/final_project/build

# Include any dependencies generated for this target.
include lib/glfw/tests/CMakeFiles/joysticks.dir/depend.make

# Include the progress variables for this target.
include lib/glfw/tests/CMakeFiles/joysticks.dir/progress.make

# Include the compile flags for this target's objects.
include lib/glfw/tests/CMakeFiles/joysticks.dir/flags.make

lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.o: lib/glfw/tests/CMakeFiles/joysticks.dir/flags.make
lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.o: ../lib/glfw/tests/joysticks.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/karlnico/project-links/final-project-6122/final_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.o"
	cd /Users/karlnico/project-links/final-project-6122/final_project/build/lib/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/joysticks.dir/joysticks.c.o   -c /Users/karlnico/project-links/final-project-6122/final_project/lib/glfw/tests/joysticks.c

lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/joysticks.dir/joysticks.c.i"
	cd /Users/karlnico/project-links/final-project-6122/final_project/build/lib/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/karlnico/project-links/final-project-6122/final_project/lib/glfw/tests/joysticks.c > CMakeFiles/joysticks.dir/joysticks.c.i

lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/joysticks.dir/joysticks.c.s"
	cd /Users/karlnico/project-links/final-project-6122/final_project/build/lib/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/karlnico/project-links/final-project-6122/final_project/lib/glfw/tests/joysticks.c -o CMakeFiles/joysticks.dir/joysticks.c.s

lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.o.requires:

.PHONY : lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.o.requires

lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.o.provides: lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.o.requires
	$(MAKE) -f lib/glfw/tests/CMakeFiles/joysticks.dir/build.make lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.o.provides.build
.PHONY : lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.o.provides

lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.o.provides.build: lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.o


lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.o: lib/glfw/tests/CMakeFiles/joysticks.dir/flags.make
lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.o: ../lib/glfw/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/karlnico/project-links/final-project-6122/final_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.o"
	cd /Users/karlnico/project-links/final-project-6122/final_project/build/lib/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/joysticks.dir/__/deps/glad.c.o   -c /Users/karlnico/project-links/final-project-6122/final_project/lib/glfw/deps/glad.c

lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/joysticks.dir/__/deps/glad.c.i"
	cd /Users/karlnico/project-links/final-project-6122/final_project/build/lib/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/karlnico/project-links/final-project-6122/final_project/lib/glfw/deps/glad.c > CMakeFiles/joysticks.dir/__/deps/glad.c.i

lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/joysticks.dir/__/deps/glad.c.s"
	cd /Users/karlnico/project-links/final-project-6122/final_project/build/lib/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/karlnico/project-links/final-project-6122/final_project/lib/glfw/deps/glad.c -o CMakeFiles/joysticks.dir/__/deps/glad.c.s

lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.o.requires:

.PHONY : lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.o.requires

lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.o.provides: lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.o.requires
	$(MAKE) -f lib/glfw/tests/CMakeFiles/joysticks.dir/build.make lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.o.provides.build
.PHONY : lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.o.provides

lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.o.provides.build: lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.o


# Object files for target joysticks
joysticks_OBJECTS = \
"CMakeFiles/joysticks.dir/joysticks.c.o" \
"CMakeFiles/joysticks.dir/__/deps/glad.c.o"

# External object files for target joysticks
joysticks_EXTERNAL_OBJECTS =

lib/glfw/tests/joysticks: lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.o
lib/glfw/tests/joysticks: lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.o
lib/glfw/tests/joysticks: lib/glfw/tests/CMakeFiles/joysticks.dir/build.make
lib/glfw/tests/joysticks: lib/glfw/src/libglfw3.a
lib/glfw/tests/joysticks: lib/glfw/tests/CMakeFiles/joysticks.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/karlnico/project-links/final-project-6122/final_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable joysticks"
	cd /Users/karlnico/project-links/final-project-6122/final_project/build/lib/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/joysticks.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/glfw/tests/CMakeFiles/joysticks.dir/build: lib/glfw/tests/joysticks

.PHONY : lib/glfw/tests/CMakeFiles/joysticks.dir/build

lib/glfw/tests/CMakeFiles/joysticks.dir/requires: lib/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.o.requires
lib/glfw/tests/CMakeFiles/joysticks.dir/requires: lib/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.o.requires

.PHONY : lib/glfw/tests/CMakeFiles/joysticks.dir/requires

lib/glfw/tests/CMakeFiles/joysticks.dir/clean:
	cd /Users/karlnico/project-links/final-project-6122/final_project/build/lib/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/joysticks.dir/cmake_clean.cmake
.PHONY : lib/glfw/tests/CMakeFiles/joysticks.dir/clean

lib/glfw/tests/CMakeFiles/joysticks.dir/depend:
	cd /Users/karlnico/project-links/final-project-6122/final_project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/karlnico/project-links/final-project-6122/final_project /Users/karlnico/project-links/final-project-6122/final_project/lib/glfw/tests /Users/karlnico/project-links/final-project-6122/final_project/build /Users/karlnico/project-links/final-project-6122/final_project/build/lib/glfw/tests /Users/karlnico/project-links/final-project-6122/final_project/build/lib/glfw/tests/CMakeFiles/joysticks.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/glfw/tests/CMakeFiles/joysticks.dir/depend
