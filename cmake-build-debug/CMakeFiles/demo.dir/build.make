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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cameron/demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cameron/demo/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo.dir/flags.make

CMakeFiles/demo.dir/src/bitmask.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/bitmask.cpp.o: ../src/bitmask.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/demo.dir/src/bitmask.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/bitmask.cpp.o -c /Users/cameron/demo/src/bitmask.cpp

CMakeFiles/demo.dir/src/bitmask.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/bitmask.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/bitmask.cpp > CMakeFiles/demo.dir/src/bitmask.cpp.i

CMakeFiles/demo.dir/src/bitmask.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/bitmask.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/bitmask.cpp -o CMakeFiles/demo.dir/src/bitmask.cpp.s

CMakeFiles/demo.dir/src/camera.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/camera.cpp.o: ../src/camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/demo.dir/src/camera.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/camera.cpp.o -c /Users/cameron/demo/src/camera.cpp

CMakeFiles/demo.dir/src/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/camera.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/camera.cpp > CMakeFiles/demo.dir/src/camera.cpp.i

CMakeFiles/demo.dir/src/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/camera.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/camera.cpp -o CMakeFiles/demo.dir/src/camera.cpp.s

CMakeFiles/demo.dir/src/engine.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/engine.cpp.o: ../src/engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/demo.dir/src/engine.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/engine.cpp.o -c /Users/cameron/demo/src/engine.cpp

CMakeFiles/demo.dir/src/engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/engine.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/engine.cpp > CMakeFiles/demo.dir/src/engine.cpp.i

CMakeFiles/demo.dir/src/engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/engine.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/engine.cpp -o CMakeFiles/demo.dir/src/engine.cpp.s

CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_glfw.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_glfw.cpp.o: ../src/imgui/bindings/imgui_impl_glfw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_glfw.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_glfw.cpp.o -c /Users/cameron/demo/src/imgui/bindings/imgui_impl_glfw.cpp

CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_glfw.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/imgui/bindings/imgui_impl_glfw.cpp > CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_glfw.cpp.i

CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_glfw.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/imgui/bindings/imgui_impl_glfw.cpp -o CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_glfw.cpp.s

CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_opengl3.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_opengl3.cpp.o: ../src/imgui/bindings/imgui_impl_opengl3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_opengl3.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_opengl3.cpp.o -c /Users/cameron/demo/src/imgui/bindings/imgui_impl_opengl3.cpp

CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_opengl3.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/imgui/bindings/imgui_impl_opengl3.cpp > CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_opengl3.cpp.i

CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_opengl3.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/imgui/bindings/imgui_impl_opengl3.cpp -o CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_opengl3.cpp.s

CMakeFiles/demo.dir/src/imgui/imgui.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/imgui/imgui.cpp.o: ../src/imgui/imgui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/demo.dir/src/imgui/imgui.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/imgui/imgui.cpp.o -c /Users/cameron/demo/src/imgui/imgui.cpp

CMakeFiles/demo.dir/src/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/imgui/imgui.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/imgui/imgui.cpp > CMakeFiles/demo.dir/src/imgui/imgui.cpp.i

CMakeFiles/demo.dir/src/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/imgui/imgui.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/imgui/imgui.cpp -o CMakeFiles/demo.dir/src/imgui/imgui.cpp.s

CMakeFiles/demo.dir/src/imgui/imgui_demo.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/imgui/imgui_demo.cpp.o: ../src/imgui/imgui_demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/demo.dir/src/imgui/imgui_demo.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/imgui/imgui_demo.cpp.o -c /Users/cameron/demo/src/imgui/imgui_demo.cpp

CMakeFiles/demo.dir/src/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/imgui/imgui_demo.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/imgui/imgui_demo.cpp > CMakeFiles/demo.dir/src/imgui/imgui_demo.cpp.i

CMakeFiles/demo.dir/src/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/imgui/imgui_demo.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/imgui/imgui_demo.cpp -o CMakeFiles/demo.dir/src/imgui/imgui_demo.cpp.s

CMakeFiles/demo.dir/src/imgui/imgui_draw.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/imgui/imgui_draw.cpp.o: ../src/imgui/imgui_draw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/demo.dir/src/imgui/imgui_draw.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/imgui/imgui_draw.cpp.o -c /Users/cameron/demo/src/imgui/imgui_draw.cpp

CMakeFiles/demo.dir/src/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/imgui/imgui_draw.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/imgui/imgui_draw.cpp > CMakeFiles/demo.dir/src/imgui/imgui_draw.cpp.i

CMakeFiles/demo.dir/src/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/imgui/imgui_draw.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/imgui/imgui_draw.cpp -o CMakeFiles/demo.dir/src/imgui/imgui_draw.cpp.s

CMakeFiles/demo.dir/src/imgui/imgui_widgets.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/imgui/imgui_widgets.cpp.o: ../src/imgui/imgui_widgets.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/demo.dir/src/imgui/imgui_widgets.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/imgui/imgui_widgets.cpp.o -c /Users/cameron/demo/src/imgui/imgui_widgets.cpp

CMakeFiles/demo.dir/src/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/imgui/imgui_widgets.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/imgui/imgui_widgets.cpp > CMakeFiles/demo.dir/src/imgui/imgui_widgets.cpp.i

CMakeFiles/demo.dir/src/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/imgui/imgui_widgets.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/imgui/imgui_widgets.cpp -o CMakeFiles/demo.dir/src/imgui/imgui_widgets.cpp.s

CMakeFiles/demo.dir/src/input_processor.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/input_processor.cpp.o: ../src/input_processor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/demo.dir/src/input_processor.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/input_processor.cpp.o -c /Users/cameron/demo/src/input_processor.cpp

CMakeFiles/demo.dir/src/input_processor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/input_processor.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/input_processor.cpp > CMakeFiles/demo.dir/src/input_processor.cpp.i

CMakeFiles/demo.dir/src/input_processor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/input_processor.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/input_processor.cpp -o CMakeFiles/demo.dir/src/input_processor.cpp.s

CMakeFiles/demo.dir/src/main.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/demo.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/main.cpp.o -c /Users/cameron/demo/src/main.cpp

CMakeFiles/demo.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/main.cpp > CMakeFiles/demo.dir/src/main.cpp.i

CMakeFiles/demo.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/main.cpp -o CMakeFiles/demo.dir/src/main.cpp.s

CMakeFiles/demo.dir/src/rendering/cube_map.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/rendering/cube_map.cpp.o: ../src/rendering/cube_map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/demo.dir/src/rendering/cube_map.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/rendering/cube_map.cpp.o -c /Users/cameron/demo/src/rendering/cube_map.cpp

CMakeFiles/demo.dir/src/rendering/cube_map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/rendering/cube_map.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/rendering/cube_map.cpp > CMakeFiles/demo.dir/src/rendering/cube_map.cpp.i

CMakeFiles/demo.dir/src/rendering/cube_map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/rendering/cube_map.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/rendering/cube_map.cpp -o CMakeFiles/demo.dir/src/rendering/cube_map.cpp.s

CMakeFiles/demo.dir/src/rendering/mesh.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/rendering/mesh.cpp.o: ../src/rendering/mesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/demo.dir/src/rendering/mesh.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/rendering/mesh.cpp.o -c /Users/cameron/demo/src/rendering/mesh.cpp

CMakeFiles/demo.dir/src/rendering/mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/rendering/mesh.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/rendering/mesh.cpp > CMakeFiles/demo.dir/src/rendering/mesh.cpp.i

CMakeFiles/demo.dir/src/rendering/mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/rendering/mesh.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/rendering/mesh.cpp -o CMakeFiles/demo.dir/src/rendering/mesh.cpp.s

CMakeFiles/demo.dir/src/rendering/mesh_repository.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/rendering/mesh_repository.cpp.o: ../src/rendering/mesh_repository.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/demo.dir/src/rendering/mesh_repository.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/rendering/mesh_repository.cpp.o -c /Users/cameron/demo/src/rendering/mesh_repository.cpp

CMakeFiles/demo.dir/src/rendering/mesh_repository.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/rendering/mesh_repository.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/rendering/mesh_repository.cpp > CMakeFiles/demo.dir/src/rendering/mesh_repository.cpp.i

CMakeFiles/demo.dir/src/rendering/mesh_repository.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/rendering/mesh_repository.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/rendering/mesh_repository.cpp -o CMakeFiles/demo.dir/src/rendering/mesh_repository.cpp.s

CMakeFiles/demo.dir/src/rendering/rendering_system.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/rendering/rendering_system.cpp.o: ../src/rendering/rendering_system.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/demo.dir/src/rendering/rendering_system.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/rendering/rendering_system.cpp.o -c /Users/cameron/demo/src/rendering/rendering_system.cpp

CMakeFiles/demo.dir/src/rendering/rendering_system.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/rendering/rendering_system.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/rendering/rendering_system.cpp > CMakeFiles/demo.dir/src/rendering/rendering_system.cpp.i

CMakeFiles/demo.dir/src/rendering/rendering_system.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/rendering/rendering_system.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/rendering/rendering_system.cpp -o CMakeFiles/demo.dir/src/rendering/rendering_system.cpp.s

CMakeFiles/demo.dir/src/rendering/texture.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/rendering/texture.cpp.o: ../src/rendering/texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/demo.dir/src/rendering/texture.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/rendering/texture.cpp.o -c /Users/cameron/demo/src/rendering/texture.cpp

CMakeFiles/demo.dir/src/rendering/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/rendering/texture.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/rendering/texture.cpp > CMakeFiles/demo.dir/src/rendering/texture.cpp.i

CMakeFiles/demo.dir/src/rendering/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/rendering/texture.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/rendering/texture.cpp -o CMakeFiles/demo.dir/src/rendering/texture.cpp.s

CMakeFiles/demo.dir/src/rendering/texture_repository.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/rendering/texture_repository.cpp.o: ../src/rendering/texture_repository.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/demo.dir/src/rendering/texture_repository.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/rendering/texture_repository.cpp.o -c /Users/cameron/demo/src/rendering/texture_repository.cpp

CMakeFiles/demo.dir/src/rendering/texture_repository.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/rendering/texture_repository.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/rendering/texture_repository.cpp > CMakeFiles/demo.dir/src/rendering/texture_repository.cpp.i

CMakeFiles/demo.dir/src/rendering/texture_repository.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/rendering/texture_repository.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/rendering/texture_repository.cpp -o CMakeFiles/demo.dir/src/rendering/texture_repository.cpp.s

CMakeFiles/demo.dir/src/stb_image.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/stb_image.cpp.o: ../src/stb_image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/demo.dir/src/stb_image.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/stb_image.cpp.o -c /Users/cameron/demo/src/stb_image.cpp

CMakeFiles/demo.dir/src/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/stb_image.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/stb_image.cpp > CMakeFiles/demo.dir/src/stb_image.cpp.i

CMakeFiles/demo.dir/src/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/stb_image.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/stb_image.cpp -o CMakeFiles/demo.dir/src/stb_image.cpp.s

CMakeFiles/demo.dir/src/window.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/window.cpp.o: ../src/window.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building CXX object CMakeFiles/demo.dir/src/window.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/window.cpp.o -c /Users/cameron/demo/src/window.cpp

CMakeFiles/demo.dir/src/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/window.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cameron/demo/src/window.cpp > CMakeFiles/demo.dir/src/window.cpp.i

CMakeFiles/demo.dir/src/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/window.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cameron/demo/src/window.cpp -o CMakeFiles/demo.dir/src/window.cpp.s

# Object files for target demo
demo_OBJECTS = \
"CMakeFiles/demo.dir/src/bitmask.cpp.o" \
"CMakeFiles/demo.dir/src/camera.cpp.o" \
"CMakeFiles/demo.dir/src/engine.cpp.o" \
"CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_glfw.cpp.o" \
"CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_opengl3.cpp.o" \
"CMakeFiles/demo.dir/src/imgui/imgui.cpp.o" \
"CMakeFiles/demo.dir/src/imgui/imgui_demo.cpp.o" \
"CMakeFiles/demo.dir/src/imgui/imgui_draw.cpp.o" \
"CMakeFiles/demo.dir/src/imgui/imgui_widgets.cpp.o" \
"CMakeFiles/demo.dir/src/input_processor.cpp.o" \
"CMakeFiles/demo.dir/src/main.cpp.o" \
"CMakeFiles/demo.dir/src/rendering/cube_map.cpp.o" \
"CMakeFiles/demo.dir/src/rendering/mesh.cpp.o" \
"CMakeFiles/demo.dir/src/rendering/mesh_repository.cpp.o" \
"CMakeFiles/demo.dir/src/rendering/rendering_system.cpp.o" \
"CMakeFiles/demo.dir/src/rendering/texture.cpp.o" \
"CMakeFiles/demo.dir/src/rendering/texture_repository.cpp.o" \
"CMakeFiles/demo.dir/src/stb_image.cpp.o" \
"CMakeFiles/demo.dir/src/window.cpp.o"

# External object files for target demo
demo_EXTERNAL_OBJECTS =

demo: CMakeFiles/demo.dir/src/bitmask.cpp.o
demo: CMakeFiles/demo.dir/src/camera.cpp.o
demo: CMakeFiles/demo.dir/src/engine.cpp.o
demo: CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_glfw.cpp.o
demo: CMakeFiles/demo.dir/src/imgui/bindings/imgui_impl_opengl3.cpp.o
demo: CMakeFiles/demo.dir/src/imgui/imgui.cpp.o
demo: CMakeFiles/demo.dir/src/imgui/imgui_demo.cpp.o
demo: CMakeFiles/demo.dir/src/imgui/imgui_draw.cpp.o
demo: CMakeFiles/demo.dir/src/imgui/imgui_widgets.cpp.o
demo: CMakeFiles/demo.dir/src/input_processor.cpp.o
demo: CMakeFiles/demo.dir/src/main.cpp.o
demo: CMakeFiles/demo.dir/src/rendering/cube_map.cpp.o
demo: CMakeFiles/demo.dir/src/rendering/mesh.cpp.o
demo: CMakeFiles/demo.dir/src/rendering/mesh_repository.cpp.o
demo: CMakeFiles/demo.dir/src/rendering/rendering_system.cpp.o
demo: CMakeFiles/demo.dir/src/rendering/texture.cpp.o
demo: CMakeFiles/demo.dir/src/rendering/texture_repository.cpp.o
demo: CMakeFiles/demo.dir/src/stb_image.cpp.o
demo: CMakeFiles/demo.dir/src/window.cpp.o
demo: CMakeFiles/demo.dir/build.make
demo: /usr/local/lib/libglfw.dylib
demo: libGLAD.a
demo: CMakeFiles/demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/cameron/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Linking CXX executable demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/demo.dir/build: demo

.PHONY : CMakeFiles/demo.dir/build

CMakeFiles/demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/demo.dir/clean

CMakeFiles/demo.dir/depend:
	cd /Users/cameron/demo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/cameron/demo /Users/cameron/demo /Users/cameron/demo/cmake-build-debug /Users/cameron/demo/cmake-build-debug /Users/cameron/demo/cmake-build-debug/CMakeFiles/demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/demo.dir/depend

