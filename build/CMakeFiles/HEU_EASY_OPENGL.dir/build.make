# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xhd0728/BallTracing/balls

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xhd0728/BallTracing/balls/build

# Include any dependencies generated for this target.
include CMakeFiles/HEU_EASY_OPENGL.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HEU_EASY_OPENGL.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HEU_EASY_OPENGL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HEU_EASY_OPENGL.dir/flags.make

CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.o: CMakeFiles/HEU_EASY_OPENGL.dir/flags.make
CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.o: /home/xhd0728/BallTracing/balls/RayTracing.cpp
CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.o: CMakeFiles/HEU_EASY_OPENGL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xhd0728/BallTracing/balls/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.o -MF CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.o.d -o CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.o -c /home/xhd0728/BallTracing/balls/RayTracing.cpp

CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xhd0728/BallTracing/balls/RayTracing.cpp > CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.i

CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xhd0728/BallTracing/balls/RayTracing.cpp -o CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.s

CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.o: CMakeFiles/HEU_EASY_OPENGL.dir/flags.make
CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.o: /home/xhd0728/BallTracing/balls/glad.c
CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.o: CMakeFiles/HEU_EASY_OPENGL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xhd0728/BallTracing/balls/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.o -MF CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.o.d -o CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.o -c /home/xhd0728/BallTracing/balls/glad.c

CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xhd0728/BallTracing/balls/glad.c > CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.i

CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xhd0728/BallTracing/balls/glad.c -o CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.s

# Object files for target HEU_EASY_OPENGL
HEU_EASY_OPENGL_OBJECTS = \
"CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.o" \
"CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.o"

# External object files for target HEU_EASY_OPENGL
HEU_EASY_OPENGL_EXTERNAL_OBJECTS =

HEU_EASY_OPENGL: CMakeFiles/HEU_EASY_OPENGL.dir/RayTracing.cpp.o
HEU_EASY_OPENGL: CMakeFiles/HEU_EASY_OPENGL.dir/glad.c.o
HEU_EASY_OPENGL: CMakeFiles/HEU_EASY_OPENGL.dir/build.make
HEU_EASY_OPENGL: /usr/lib/x86_64-linux-gnu/libGLEW.so
HEU_EASY_OPENGL: /usr/lib/x86_64-linux-gnu/libglfw.so
HEU_EASY_OPENGL: /usr/lib/x86_64-linux-gnu/libOpenGL.so
HEU_EASY_OPENGL: /usr/lib/x86_64-linux-gnu/libGLX.so
HEU_EASY_OPENGL: /usr/lib/x86_64-linux-gnu/libGLU.so
HEU_EASY_OPENGL: CMakeFiles/HEU_EASY_OPENGL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xhd0728/BallTracing/balls/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable HEU_EASY_OPENGL"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HEU_EASY_OPENGL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HEU_EASY_OPENGL.dir/build: HEU_EASY_OPENGL
.PHONY : CMakeFiles/HEU_EASY_OPENGL.dir/build

CMakeFiles/HEU_EASY_OPENGL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HEU_EASY_OPENGL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HEU_EASY_OPENGL.dir/clean

CMakeFiles/HEU_EASY_OPENGL.dir/depend:
	cd /home/xhd0728/BallTracing/balls/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xhd0728/BallTracing/balls /home/xhd0728/BallTracing/balls /home/xhd0728/BallTracing/balls/build /home/xhd0728/BallTracing/balls/build /home/xhd0728/BallTracing/balls/build/CMakeFiles/HEU_EASY_OPENGL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HEU_EASY_OPENGL.dir/depend
