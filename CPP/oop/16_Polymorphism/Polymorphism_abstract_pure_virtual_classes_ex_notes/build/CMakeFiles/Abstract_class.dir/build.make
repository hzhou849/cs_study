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
CMAKE_SOURCE_DIR = /home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes/build

# Include any dependencies generated for this target.
include CMakeFiles/Abstract_class.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Abstract_class.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Abstract_class.dir/flags.make

CMakeFiles/Abstract_class.dir/main.cpp.o: CMakeFiles/Abstract_class.dir/flags.make
CMakeFiles/Abstract_class.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Abstract_class.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Abstract_class.dir/main.cpp.o -c /home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes/main.cpp

CMakeFiles/Abstract_class.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abstract_class.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes/main.cpp > CMakeFiles/Abstract_class.dir/main.cpp.i

CMakeFiles/Abstract_class.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abstract_class.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes/main.cpp -o CMakeFiles/Abstract_class.dir/main.cpp.s

CMakeFiles/Abstract_class.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Abstract_class.dir/main.cpp.o.requires

CMakeFiles/Abstract_class.dir/main.cpp.o.provides: CMakeFiles/Abstract_class.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Abstract_class.dir/build.make CMakeFiles/Abstract_class.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Abstract_class.dir/main.cpp.o.provides

CMakeFiles/Abstract_class.dir/main.cpp.o.provides.build: CMakeFiles/Abstract_class.dir/main.cpp.o


CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o: CMakeFiles/Abstract_class.dir/flags.make
CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o: ../Abstract_class.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o -c /home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes/Abstract_class.cpp

CMakeFiles/Abstract_class.dir/Abstract_class.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abstract_class.dir/Abstract_class.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes/Abstract_class.cpp > CMakeFiles/Abstract_class.dir/Abstract_class.cpp.i

CMakeFiles/Abstract_class.dir/Abstract_class.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abstract_class.dir/Abstract_class.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes/Abstract_class.cpp -o CMakeFiles/Abstract_class.dir/Abstract_class.cpp.s

CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o.requires:

.PHONY : CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o.requires

CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o.provides: CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o.requires
	$(MAKE) -f CMakeFiles/Abstract_class.dir/build.make CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o.provides.build
.PHONY : CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o.provides

CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o.provides.build: CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o


# Object files for target Abstract_class
Abstract_class_OBJECTS = \
"CMakeFiles/Abstract_class.dir/main.cpp.o" \
"CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o"

# External object files for target Abstract_class
Abstract_class_EXTERNAL_OBJECTS =

Abstract_class: CMakeFiles/Abstract_class.dir/main.cpp.o
Abstract_class: CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o
Abstract_class: CMakeFiles/Abstract_class.dir/build.make
Abstract_class: CMakeFiles/Abstract_class.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Abstract_class"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Abstract_class.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Abstract_class.dir/build: Abstract_class

.PHONY : CMakeFiles/Abstract_class.dir/build

CMakeFiles/Abstract_class.dir/requires: CMakeFiles/Abstract_class.dir/main.cpp.o.requires
CMakeFiles/Abstract_class.dir/requires: CMakeFiles/Abstract_class.dir/Abstract_class.cpp.o.requires

.PHONY : CMakeFiles/Abstract_class.dir/requires

CMakeFiles/Abstract_class.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Abstract_class.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Abstract_class.dir/clean

CMakeFiles/Abstract_class.dir/depend:
	cd /home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes /home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes /home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes/build /home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes/build /home/howardz/Documents/cs_study/CPP/oop/16_Polymorphism/Polymorphism_abstract_pure_virtual_classes_ex_notes/build/CMakeFiles/Abstract_class.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Abstract_class.dir/depend

