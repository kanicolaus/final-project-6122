# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.3.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.3.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project\cmake-build-debug"

# Include any dependencies generated for this target.
include lib/glm/CMakeFiles/glm_dummy.dir/depend.make

# Include the progress variables for this target.
include lib/glm/CMakeFiles/glm_dummy.dir/progress.make

# Include the compile flags for this target's objects.
include lib/glm/CMakeFiles/glm_dummy.dir/flags.make

lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj: lib/glm/CMakeFiles/glm_dummy.dir/flags.make
lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj: lib/glm/CMakeFiles/glm_dummy.dir/includes_CXX.rsp
lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj: ../lib/glm/detail/dummy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj"
	cd /d C:\Users\TYLERB~1\DOCUME~1\ECE412~1\ty\final-project-6122\final_project\CMAKE-~1\lib\glm && C:\PROGRA~2\MINGW-~1\I686-7~1.0-P\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\glm_dummy.dir\detail\dummy.cpp.obj -c "C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project\lib\glm\detail\dummy.cpp"

lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glm_dummy.dir/detail/dummy.cpp.i"
	cd /d C:\Users\TYLERB~1\DOCUME~1\ECE412~1\ty\final-project-6122\final_project\CMAKE-~1\lib\glm && C:\PROGRA~2\MINGW-~1\I686-7~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project\lib\glm\detail\dummy.cpp" > CMakeFiles\glm_dummy.dir\detail\dummy.cpp.i

lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glm_dummy.dir/detail/dummy.cpp.s"
	cd /d C:\Users\TYLERB~1\DOCUME~1\ECE412~1\ty\final-project-6122\final_project\CMAKE-~1\lib\glm && C:\PROGRA~2\MINGW-~1\I686-7~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project\lib\glm\detail\dummy.cpp" -o CMakeFiles\glm_dummy.dir\detail\dummy.cpp.s

lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj.requires:

.PHONY : lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj.requires

lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj.provides: lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj.requires
	$(MAKE) -f lib\glm\CMakeFiles\glm_dummy.dir\build.make lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj.provides.build
.PHONY : lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj.provides

lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj.provides.build: lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj


lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj: lib/glm/CMakeFiles/glm_dummy.dir/flags.make
lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj: lib/glm/CMakeFiles/glm_dummy.dir/includes_CXX.rsp
lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj: ../lib/glm/detail/glm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj"
	cd /d C:\Users\TYLERB~1\DOCUME~1\ECE412~1\ty\final-project-6122\final_project\CMAKE-~1\lib\glm && C:\PROGRA~2\MINGW-~1\I686-7~1.0-P\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\glm_dummy.dir\detail\glm.cpp.obj -c "C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project\lib\glm\detail\glm.cpp"

lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glm_dummy.dir/detail/glm.cpp.i"
	cd /d C:\Users\TYLERB~1\DOCUME~1\ECE412~1\ty\final-project-6122\final_project\CMAKE-~1\lib\glm && C:\PROGRA~2\MINGW-~1\I686-7~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project\lib\glm\detail\glm.cpp" > CMakeFiles\glm_dummy.dir\detail\glm.cpp.i

lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glm_dummy.dir/detail/glm.cpp.s"
	cd /d C:\Users\TYLERB~1\DOCUME~1\ECE412~1\ty\final-project-6122\final_project\CMAKE-~1\lib\glm && C:\PROGRA~2\MINGW-~1\I686-7~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project\lib\glm\detail\glm.cpp" -o CMakeFiles\glm_dummy.dir\detail\glm.cpp.s

lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj.requires:

.PHONY : lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj.requires

lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj.provides: lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj.requires
	$(MAKE) -f lib\glm\CMakeFiles\glm_dummy.dir\build.make lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj.provides.build
.PHONY : lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj.provides

lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj.provides.build: lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj


# Object files for target glm_dummy
glm_dummy_OBJECTS = \
"CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj" \
"CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj"

# External object files for target glm_dummy
glm_dummy_EXTERNAL_OBJECTS =

lib/glm/glm_dummy.exe: lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj
lib/glm/glm_dummy.exe: lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj
lib/glm/glm_dummy.exe: lib/glm/CMakeFiles/glm_dummy.dir/build.make
lib/glm/glm_dummy.exe: lib/glm/CMakeFiles/glm_dummy.dir/linklibs.rsp
lib/glm/glm_dummy.exe: lib/glm/CMakeFiles/glm_dummy.dir/objects1.rsp
lib/glm/glm_dummy.exe: lib/glm/CMakeFiles/glm_dummy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable glm_dummy.exe"
	cd /d C:\Users\TYLERB~1\DOCUME~1\ECE412~1\ty\final-project-6122\final_project\CMAKE-~1\lib\glm && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\glm_dummy.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/glm/CMakeFiles/glm_dummy.dir/build: lib/glm/glm_dummy.exe

.PHONY : lib/glm/CMakeFiles/glm_dummy.dir/build

lib/glm/CMakeFiles/glm_dummy.dir/requires: lib/glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj.requires
lib/glm/CMakeFiles/glm_dummy.dir/requires: lib/glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj.requires

.PHONY : lib/glm/CMakeFiles/glm_dummy.dir/requires

lib/glm/CMakeFiles/glm_dummy.dir/clean:
	cd /d C:\Users\TYLERB~1\DOCUME~1\ECE412~1\ty\final-project-6122\final_project\CMAKE-~1\lib\glm && $(CMAKE_COMMAND) -P CMakeFiles\glm_dummy.dir\cmake_clean.cmake
.PHONY : lib/glm/CMakeFiles/glm_dummy.dir/clean

lib/glm/CMakeFiles/glm_dummy.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project" "C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project\lib\glm" "C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project\cmake-build-debug" "C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project\cmake-build-debug\lib\glm" "C:\Users\Tyler Brown\Documents\ECE 4122\ty\final-project-6122\final_project\cmake-build-debug\lib\glm\CMakeFiles\glm_dummy.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : lib/glm/CMakeFiles/glm_dummy.dir/depend
