# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.28.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.28.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/adanmatute/Desktop/CSC-630-Fin/chess

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/adanmatute/Desktop/CSC-630-Fin/chess/build

# Include any dependencies generated for this target.
include CMakeFiles/P2B.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/P2B.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/P2B.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/P2B.dir/flags.make

CMakeFiles/P2B.dir/ext/glad/src/glad.c.o: CMakeFiles/P2B.dir/flags.make
CMakeFiles/P2B.dir/ext/glad/src/glad.c.o: /Users/adanmatute/Desktop/CSC-630-Fin/chess/ext/glad/src/glad.c
CMakeFiles/P2B.dir/ext/glad/src/glad.c.o: CMakeFiles/P2B.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/adanmatute/Desktop/CSC-630-Fin/chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/P2B.dir/ext/glad/src/glad.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/P2B.dir/ext/glad/src/glad.c.o -MF CMakeFiles/P2B.dir/ext/glad/src/glad.c.o.d -o CMakeFiles/P2B.dir/ext/glad/src/glad.c.o -c /Users/adanmatute/Desktop/CSC-630-Fin/chess/ext/glad/src/glad.c

CMakeFiles/P2B.dir/ext/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/P2B.dir/ext/glad/src/glad.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/adanmatute/Desktop/CSC-630-Fin/chess/ext/glad/src/glad.c > CMakeFiles/P2B.dir/ext/glad/src/glad.c.i

CMakeFiles/P2B.dir/ext/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/P2B.dir/ext/glad/src/glad.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/adanmatute/Desktop/CSC-630-Fin/chess/ext/glad/src/glad.c -o CMakeFiles/P2B.dir/ext/glad/src/glad.c.s

CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o: CMakeFiles/P2B.dir/flags.make
CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o: /Users/adanmatute/Desktop/CSC-630-Fin/chess/ext/tiny_obj_loader/tiny_obj_loader.cpp
CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o: CMakeFiles/P2B.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/adanmatute/Desktop/CSC-630-Fin/chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o -MF CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o.d -o CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o -c /Users/adanmatute/Desktop/CSC-630-Fin/chess/ext/tiny_obj_loader/tiny_obj_loader.cpp

CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/adanmatute/Desktop/CSC-630-Fin/chess/ext/tiny_obj_loader/tiny_obj_loader.cpp > CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.i

CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/adanmatute/Desktop/CSC-630-Fin/chess/ext/tiny_obj_loader/tiny_obj_loader.cpp -o CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.s

CMakeFiles/P2B.dir/src/GLSL.cpp.o: CMakeFiles/P2B.dir/flags.make
CMakeFiles/P2B.dir/src/GLSL.cpp.o: /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/GLSL.cpp
CMakeFiles/P2B.dir/src/GLSL.cpp.o: CMakeFiles/P2B.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/adanmatute/Desktop/CSC-630-Fin/chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/P2B.dir/src/GLSL.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/P2B.dir/src/GLSL.cpp.o -MF CMakeFiles/P2B.dir/src/GLSL.cpp.o.d -o CMakeFiles/P2B.dir/src/GLSL.cpp.o -c /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/GLSL.cpp

CMakeFiles/P2B.dir/src/GLSL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/P2B.dir/src/GLSL.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/GLSL.cpp > CMakeFiles/P2B.dir/src/GLSL.cpp.i

CMakeFiles/P2B.dir/src/GLSL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/P2B.dir/src/GLSL.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/GLSL.cpp -o CMakeFiles/P2B.dir/src/GLSL.cpp.s

CMakeFiles/P2B.dir/src/MatrixStack.cpp.o: CMakeFiles/P2B.dir/flags.make
CMakeFiles/P2B.dir/src/MatrixStack.cpp.o: /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/MatrixStack.cpp
CMakeFiles/P2B.dir/src/MatrixStack.cpp.o: CMakeFiles/P2B.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/adanmatute/Desktop/CSC-630-Fin/chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/P2B.dir/src/MatrixStack.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/P2B.dir/src/MatrixStack.cpp.o -MF CMakeFiles/P2B.dir/src/MatrixStack.cpp.o.d -o CMakeFiles/P2B.dir/src/MatrixStack.cpp.o -c /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/MatrixStack.cpp

CMakeFiles/P2B.dir/src/MatrixStack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/P2B.dir/src/MatrixStack.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/MatrixStack.cpp > CMakeFiles/P2B.dir/src/MatrixStack.cpp.i

CMakeFiles/P2B.dir/src/MatrixStack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/P2B.dir/src/MatrixStack.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/MatrixStack.cpp -o CMakeFiles/P2B.dir/src/MatrixStack.cpp.s

CMakeFiles/P2B.dir/src/Program.cpp.o: CMakeFiles/P2B.dir/flags.make
CMakeFiles/P2B.dir/src/Program.cpp.o: /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/Program.cpp
CMakeFiles/P2B.dir/src/Program.cpp.o: CMakeFiles/P2B.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/adanmatute/Desktop/CSC-630-Fin/chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/P2B.dir/src/Program.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/P2B.dir/src/Program.cpp.o -MF CMakeFiles/P2B.dir/src/Program.cpp.o.d -o CMakeFiles/P2B.dir/src/Program.cpp.o -c /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/Program.cpp

CMakeFiles/P2B.dir/src/Program.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/P2B.dir/src/Program.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/Program.cpp > CMakeFiles/P2B.dir/src/Program.cpp.i

CMakeFiles/P2B.dir/src/Program.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/P2B.dir/src/Program.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/Program.cpp -o CMakeFiles/P2B.dir/src/Program.cpp.s

CMakeFiles/P2B.dir/src/Shape.cpp.o: CMakeFiles/P2B.dir/flags.make
CMakeFiles/P2B.dir/src/Shape.cpp.o: /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/Shape.cpp
CMakeFiles/P2B.dir/src/Shape.cpp.o: CMakeFiles/P2B.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/adanmatute/Desktop/CSC-630-Fin/chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/P2B.dir/src/Shape.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/P2B.dir/src/Shape.cpp.o -MF CMakeFiles/P2B.dir/src/Shape.cpp.o.d -o CMakeFiles/P2B.dir/src/Shape.cpp.o -c /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/Shape.cpp

CMakeFiles/P2B.dir/src/Shape.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/P2B.dir/src/Shape.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/Shape.cpp > CMakeFiles/P2B.dir/src/Shape.cpp.i

CMakeFiles/P2B.dir/src/Shape.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/P2B.dir/src/Shape.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/Shape.cpp -o CMakeFiles/P2B.dir/src/Shape.cpp.s

CMakeFiles/P2B.dir/src/WindowManager.cpp.o: CMakeFiles/P2B.dir/flags.make
CMakeFiles/P2B.dir/src/WindowManager.cpp.o: /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/WindowManager.cpp
CMakeFiles/P2B.dir/src/WindowManager.cpp.o: CMakeFiles/P2B.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/adanmatute/Desktop/CSC-630-Fin/chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/P2B.dir/src/WindowManager.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/P2B.dir/src/WindowManager.cpp.o -MF CMakeFiles/P2B.dir/src/WindowManager.cpp.o.d -o CMakeFiles/P2B.dir/src/WindowManager.cpp.o -c /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/WindowManager.cpp

CMakeFiles/P2B.dir/src/WindowManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/P2B.dir/src/WindowManager.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/WindowManager.cpp > CMakeFiles/P2B.dir/src/WindowManager.cpp.i

CMakeFiles/P2B.dir/src/WindowManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/P2B.dir/src/WindowManager.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/WindowManager.cpp -o CMakeFiles/P2B.dir/src/WindowManager.cpp.s

CMakeFiles/P2B.dir/src/board.cpp.o: CMakeFiles/P2B.dir/flags.make
CMakeFiles/P2B.dir/src/board.cpp.o: /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/board.cpp
CMakeFiles/P2B.dir/src/board.cpp.o: CMakeFiles/P2B.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/adanmatute/Desktop/CSC-630-Fin/chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/P2B.dir/src/board.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/P2B.dir/src/board.cpp.o -MF CMakeFiles/P2B.dir/src/board.cpp.o.d -o CMakeFiles/P2B.dir/src/board.cpp.o -c /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/board.cpp

CMakeFiles/P2B.dir/src/board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/P2B.dir/src/board.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/board.cpp > CMakeFiles/P2B.dir/src/board.cpp.i

CMakeFiles/P2B.dir/src/board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/P2B.dir/src/board.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/board.cpp -o CMakeFiles/P2B.dir/src/board.cpp.s

CMakeFiles/P2B.dir/src/main.cpp.o: CMakeFiles/P2B.dir/flags.make
CMakeFiles/P2B.dir/src/main.cpp.o: /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/main.cpp
CMakeFiles/P2B.dir/src/main.cpp.o: CMakeFiles/P2B.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/adanmatute/Desktop/CSC-630-Fin/chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/P2B.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/P2B.dir/src/main.cpp.o -MF CMakeFiles/P2B.dir/src/main.cpp.o.d -o CMakeFiles/P2B.dir/src/main.cpp.o -c /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/main.cpp

CMakeFiles/P2B.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/P2B.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/main.cpp > CMakeFiles/P2B.dir/src/main.cpp.i

CMakeFiles/P2B.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/P2B.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/main.cpp -o CMakeFiles/P2B.dir/src/main.cpp.s

CMakeFiles/P2B.dir/src/piece.cpp.o: CMakeFiles/P2B.dir/flags.make
CMakeFiles/P2B.dir/src/piece.cpp.o: /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/piece.cpp
CMakeFiles/P2B.dir/src/piece.cpp.o: CMakeFiles/P2B.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/adanmatute/Desktop/CSC-630-Fin/chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/P2B.dir/src/piece.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/P2B.dir/src/piece.cpp.o -MF CMakeFiles/P2B.dir/src/piece.cpp.o.d -o CMakeFiles/P2B.dir/src/piece.cpp.o -c /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/piece.cpp

CMakeFiles/P2B.dir/src/piece.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/P2B.dir/src/piece.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/piece.cpp > CMakeFiles/P2B.dir/src/piece.cpp.i

CMakeFiles/P2B.dir/src/piece.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/P2B.dir/src/piece.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/adanmatute/Desktop/CSC-630-Fin/chess/src/piece.cpp -o CMakeFiles/P2B.dir/src/piece.cpp.s

# Object files for target P2B
P2B_OBJECTS = \
"CMakeFiles/P2B.dir/ext/glad/src/glad.c.o" \
"CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o" \
"CMakeFiles/P2B.dir/src/GLSL.cpp.o" \
"CMakeFiles/P2B.dir/src/MatrixStack.cpp.o" \
"CMakeFiles/P2B.dir/src/Program.cpp.o" \
"CMakeFiles/P2B.dir/src/Shape.cpp.o" \
"CMakeFiles/P2B.dir/src/WindowManager.cpp.o" \
"CMakeFiles/P2B.dir/src/board.cpp.o" \
"CMakeFiles/P2B.dir/src/main.cpp.o" \
"CMakeFiles/P2B.dir/src/piece.cpp.o"

# External object files for target P2B
P2B_EXTERNAL_OBJECTS =

P2B: CMakeFiles/P2B.dir/ext/glad/src/glad.c.o
P2B: CMakeFiles/P2B.dir/ext/tiny_obj_loader/tiny_obj_loader.cpp.o
P2B: CMakeFiles/P2B.dir/src/GLSL.cpp.o
P2B: CMakeFiles/P2B.dir/src/MatrixStack.cpp.o
P2B: CMakeFiles/P2B.dir/src/Program.cpp.o
P2B: CMakeFiles/P2B.dir/src/Shape.cpp.o
P2B: CMakeFiles/P2B.dir/src/WindowManager.cpp.o
P2B: CMakeFiles/P2B.dir/src/board.cpp.o
P2B: CMakeFiles/P2B.dir/src/main.cpp.o
P2B: CMakeFiles/P2B.dir/src/piece.cpp.o
P2B: CMakeFiles/P2B.dir/build.make
P2B: /usr/local/lib/libglfw3.a
P2B: CMakeFiles/P2B.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/adanmatute/Desktop/CSC-630-Fin/chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable P2B"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/P2B.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/P2B.dir/build: P2B
.PHONY : CMakeFiles/P2B.dir/build

CMakeFiles/P2B.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/P2B.dir/cmake_clean.cmake
.PHONY : CMakeFiles/P2B.dir/clean

CMakeFiles/P2B.dir/depend:
	cd /Users/adanmatute/Desktop/CSC-630-Fin/chess/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/adanmatute/Desktop/CSC-630-Fin/chess /Users/adanmatute/Desktop/CSC-630-Fin/chess /Users/adanmatute/Desktop/CSC-630-Fin/chess/build /Users/adanmatute/Desktop/CSC-630-Fin/chess/build /Users/adanmatute/Desktop/CSC-630-Fin/chess/build/CMakeFiles/P2B.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/P2B.dir/depend

