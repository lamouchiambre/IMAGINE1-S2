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
CMAKE_SOURCE_DIR = "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build"

# Include any dependencies generated for this target.
include pngdecode/CMakeFiles/pngdecode.dir/depend.make

# Include the progress variables for this target.
include pngdecode/CMakeFiles/pngdecode.dir/progress.make

# Include the compile flags for this target's objects.
include pngdecode/CMakeFiles/pngdecode.dir/flags.make

pngdecode/CMakeFiles/pngdecode.dir/png.cpp.o: pngdecode/CMakeFiles/pngdecode.dir/flags.make
pngdecode/CMakeFiles/pngdecode.dir/png.cpp.o: ../pngdecode/png.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object pngdecode/CMakeFiles/pngdecode.dir/png.cpp.o"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pngdecode.dir/png.cpp.o -c "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/png.cpp"

pngdecode/CMakeFiles/pngdecode.dir/png.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pngdecode.dir/png.cpp.i"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/png.cpp" > CMakeFiles/pngdecode.dir/png.cpp.i

pngdecode/CMakeFiles/pngdecode.dir/png.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pngdecode.dir/png.cpp.s"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/png.cpp" -o CMakeFiles/pngdecode.dir/png.cpp.s

pngdecode/CMakeFiles/pngdecode.dir/pngdec.cpp.o: pngdecode/CMakeFiles/pngdecode.dir/flags.make
pngdecode/CMakeFiles/pngdecode.dir/pngdec.cpp.o: ../pngdecode/pngdec.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object pngdecode/CMakeFiles/pngdecode.dir/pngdec.cpp.o"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pngdecode.dir/pngdec.cpp.o -c "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/pngdec.cpp"

pngdecode/CMakeFiles/pngdecode.dir/pngdec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pngdecode.dir/pngdec.cpp.i"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/pngdec.cpp" > CMakeFiles/pngdecode.dir/pngdec.cpp.i

pngdecode/CMakeFiles/pngdecode.dir/pngdec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pngdecode.dir/pngdec.cpp.s"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/pngdec.cpp" -o CMakeFiles/pngdecode.dir/pngdec.cpp.s

pngdecode/CMakeFiles/pngdecode.dir/pngenc.cpp.o: pngdecode/CMakeFiles/pngdecode.dir/flags.make
pngdecode/CMakeFiles/pngdecode.dir/pngenc.cpp.o: ../pngdecode/pngenc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object pngdecode/CMakeFiles/pngdecode.dir/pngenc.cpp.o"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pngdecode.dir/pngenc.cpp.o -c "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/pngenc.cpp"

pngdecode/CMakeFiles/pngdecode.dir/pngenc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pngdecode.dir/pngenc.cpp.i"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/pngenc.cpp" > CMakeFiles/pngdecode.dir/pngenc.cpp.i

pngdecode/CMakeFiles/pngdecode.dir/pngenc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pngdecode.dir/pngenc.cpp.s"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/pngenc.cpp" -o CMakeFiles/pngdecode.dir/pngenc.cpp.s

pngdecode/CMakeFiles/pngdecode.dir/zdec.cpp.o: pngdecode/CMakeFiles/pngdecode.dir/flags.make
pngdecode/CMakeFiles/pngdecode.dir/zdec.cpp.o: ../pngdecode/zdec.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object pngdecode/CMakeFiles/pngdecode.dir/zdec.cpp.o"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pngdecode.dir/zdec.cpp.o -c "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/zdec.cpp"

pngdecode/CMakeFiles/pngdecode.dir/zdec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pngdecode.dir/zdec.cpp.i"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/zdec.cpp" > CMakeFiles/pngdecode.dir/zdec.cpp.i

pngdecode/CMakeFiles/pngdecode.dir/zdec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pngdecode.dir/zdec.cpp.s"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/zdec.cpp" -o CMakeFiles/pngdecode.dir/zdec.cpp.s

pngdecode/CMakeFiles/pngdecode.dir/zenc.cpp.o: pngdecode/CMakeFiles/pngdecode.dir/flags.make
pngdecode/CMakeFiles/pngdecode.dir/zenc.cpp.o: ../pngdecode/zenc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object pngdecode/CMakeFiles/pngdecode.dir/zenc.cpp.o"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pngdecode.dir/zenc.cpp.o -c "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/zenc.cpp"

pngdecode/CMakeFiles/pngdecode.dir/zenc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pngdecode.dir/zenc.cpp.i"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/zenc.cpp" > CMakeFiles/pngdecode.dir/zenc.cpp.i

pngdecode/CMakeFiles/pngdecode.dir/zenc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pngdecode.dir/zenc.cpp.s"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/zenc.cpp" -o CMakeFiles/pngdecode.dir/zenc.cpp.s

pngdecode/CMakeFiles/pngdecode.dir/zss.cpp.o: pngdecode/CMakeFiles/pngdecode.dir/flags.make
pngdecode/CMakeFiles/pngdecode.dir/zss.cpp.o: ../pngdecode/zss.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object pngdecode/CMakeFiles/pngdecode.dir/zss.cpp.o"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pngdecode.dir/zss.cpp.o -c "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/zss.cpp"

pngdecode/CMakeFiles/pngdecode.dir/zss.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pngdecode.dir/zss.cpp.i"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/zss.cpp" > CMakeFiles/pngdecode.dir/zss.cpp.i

pngdecode/CMakeFiles/pngdecode.dir/zss.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pngdecode.dir/zss.cpp.s"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode/zss.cpp" -o CMakeFiles/pngdecode.dir/zss.cpp.s

# Object files for target pngdecode
pngdecode_OBJECTS = \
"CMakeFiles/pngdecode.dir/png.cpp.o" \
"CMakeFiles/pngdecode.dir/pngdec.cpp.o" \
"CMakeFiles/pngdecode.dir/pngenc.cpp.o" \
"CMakeFiles/pngdecode.dir/zdec.cpp.o" \
"CMakeFiles/pngdecode.dir/zenc.cpp.o" \
"CMakeFiles/pngdecode.dir/zss.cpp.o"

# External object files for target pngdecode
pngdecode_EXTERNAL_OBJECTS =

pngdecode/libpngdecode.a: pngdecode/CMakeFiles/pngdecode.dir/png.cpp.o
pngdecode/libpngdecode.a: pngdecode/CMakeFiles/pngdecode.dir/pngdec.cpp.o
pngdecode/libpngdecode.a: pngdecode/CMakeFiles/pngdecode.dir/pngenc.cpp.o
pngdecode/libpngdecode.a: pngdecode/CMakeFiles/pngdecode.dir/zdec.cpp.o
pngdecode/libpngdecode.a: pngdecode/CMakeFiles/pngdecode.dir/zenc.cpp.o
pngdecode/libpngdecode.a: pngdecode/CMakeFiles/pngdecode.dir/zss.cpp.o
pngdecode/libpngdecode.a: pngdecode/CMakeFiles/pngdecode.dir/build.make
pngdecode/libpngdecode.a: pngdecode/CMakeFiles/pngdecode.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libpngdecode.a"
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && $(CMAKE_COMMAND) -P CMakeFiles/pngdecode.dir/cmake_clean_target.cmake
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pngdecode.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
pngdecode/CMakeFiles/pngdecode.dir/build: pngdecode/libpngdecode.a

.PHONY : pngdecode/CMakeFiles/pngdecode.dir/build

pngdecode/CMakeFiles/pngdecode.dir/clean:
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" && $(CMAKE_COMMAND) -P CMakeFiles/pngdecode.dir/cmake_clean.cmake
.PHONY : pngdecode/CMakeFiles/pngdecode.dir/clean

pngdecode/CMakeFiles/pngdecode.dir/depend:
	cd "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template" "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/pngdecode" "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build" "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode" "/home/e20160018322/Téléchargements/Lancer de rayon-20210126/raytracer-template/build/pngdecode/CMakeFiles/pngdecode.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : pngdecode/CMakeFiles/pngdecode.dir/depend
