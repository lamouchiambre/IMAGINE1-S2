# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/new jeter de rayon/raytracer-template"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/new jeter de rayon/raytracer-template/build"

# Include any dependencies generated for this target.
include CMakeFiles/glad.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/glad.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glad.dir/flags.make

CMakeFiles/glad.dir/glfw-3.2/deps/glad.c.o: CMakeFiles/glad.dir/flags.make
CMakeFiles/glad.dir/glfw-3.2/deps/glad.c.o: ../glfw-3.2/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/new jeter de rayon/raytracer-template/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/glad.dir/glfw-3.2/deps/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glad.dir/glfw-3.2/deps/glad.c.o   -c "/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/new jeter de rayon/raytracer-template/glfw-3.2/deps/glad.c"

CMakeFiles/glad.dir/glfw-3.2/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glad.dir/glfw-3.2/deps/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/new jeter de rayon/raytracer-template/glfw-3.2/deps/glad.c" > CMakeFiles/glad.dir/glfw-3.2/deps/glad.c.i

CMakeFiles/glad.dir/glfw-3.2/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glad.dir/glfw-3.2/deps/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/new jeter de rayon/raytracer-template/glfw-3.2/deps/glad.c" -o CMakeFiles/glad.dir/glfw-3.2/deps/glad.c.s

# Object files for target glad
glad_OBJECTS = \
"CMakeFiles/glad.dir/glfw-3.2/deps/glad.c.o"

# External object files for target glad
glad_EXTERNAL_OBJECTS =

libglad.a: CMakeFiles/glad.dir/glfw-3.2/deps/glad.c.o
libglad.a: CMakeFiles/glad.dir/build.make
libglad.a: CMakeFiles/glad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/new jeter de rayon/raytracer-template/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libglad.a"
	$(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glad.dir/build: libglad.a

.PHONY : CMakeFiles/glad.dir/build

CMakeFiles/glad.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean.cmake
.PHONY : CMakeFiles/glad.dir/clean

CMakeFiles/glad.dir/depend:
	cd "/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/new jeter de rayon/raytracer-template/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/new jeter de rayon/raytracer-template" "/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/new jeter de rayon/raytracer-template" "/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/new jeter de rayon/raytracer-template/build" "/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/new jeter de rayon/raytracer-template/build" "/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/new jeter de rayon/raytracer-template/build/CMakeFiles/glad.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/glad.dir/depend

