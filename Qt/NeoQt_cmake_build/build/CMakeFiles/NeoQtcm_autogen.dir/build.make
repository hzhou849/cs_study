# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_SOURCE_DIR = /home/howardz/Documents/cs_study/Qt/NeoQt_cmake_build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/howardz/Documents/cs_study/Qt/NeoQt_cmake_build/build

# Utility rule file for NeoQtcm_autogen.

# Include the progress variables for this target.
include CMakeFiles/NeoQtcm_autogen.dir/progress.make

CMakeFiles/NeoQtcm_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/howardz/Documents/cs_study/Qt/NeoQt_cmake_build/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC, UIC and RCC for target NeoQtcm"
	/usr/bin/cmake -E cmake_autogen /home/howardz/Documents/cs_study/Qt/NeoQt_cmake_build/build/CMakeFiles/NeoQtcm_autogen.dir/ ""

NeoQtcm_autogen: CMakeFiles/NeoQtcm_autogen
NeoQtcm_autogen: CMakeFiles/NeoQtcm_autogen.dir/build.make

.PHONY : NeoQtcm_autogen

# Rule to build all files generated by this target.
CMakeFiles/NeoQtcm_autogen.dir/build: NeoQtcm_autogen

.PHONY : CMakeFiles/NeoQtcm_autogen.dir/build

CMakeFiles/NeoQtcm_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NeoQtcm_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NeoQtcm_autogen.dir/clean

CMakeFiles/NeoQtcm_autogen.dir/depend:
	cd /home/howardz/Documents/cs_study/Qt/NeoQt_cmake_build/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/howardz/Documents/cs_study/Qt/NeoQt_cmake_build /home/howardz/Documents/cs_study/Qt/NeoQt_cmake_build /home/howardz/Documents/cs_study/Qt/NeoQt_cmake_build/build /home/howardz/Documents/cs_study/Qt/NeoQt_cmake_build/build /home/howardz/Documents/cs_study/Qt/NeoQt_cmake_build/build/CMakeFiles/NeoQtcm_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NeoQtcm_autogen.dir/depend
