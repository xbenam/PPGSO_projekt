# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program files\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program files\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Skola\FIIT\3._semester\PPGSO_projekt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Skola\FIIT\3._semester\PPGSO_projekt\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PPGSO_projekt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PPGSO_projekt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PPGSO_projekt.dir/flags.make

CMakeFiles/PPGSO_projekt.dir/main.cpp.obj: CMakeFiles/PPGSO_projekt.dir/flags.make
CMakeFiles/PPGSO_projekt.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Skola\FIIT\3._semester\PPGSO_projekt\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PPGSO_projekt.dir/main.cpp.obj"
	"D:\Program files\CLion 2020.2.3\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\PPGSO_projekt.dir\main.cpp.obj -c D:\Skola\FIIT\3._semester\PPGSO_projekt\main.cpp

CMakeFiles/PPGSO_projekt.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PPGSO_projekt.dir/main.cpp.i"
	"D:\Program files\CLion 2020.2.3\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Skola\FIIT\3._semester\PPGSO_projekt\main.cpp > CMakeFiles\PPGSO_projekt.dir\main.cpp.i

CMakeFiles/PPGSO_projekt.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PPGSO_projekt.dir/main.cpp.s"
	"D:\Program files\CLion 2020.2.3\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Skola\FIIT\3._semester\PPGSO_projekt\main.cpp -o CMakeFiles\PPGSO_projekt.dir\main.cpp.s

# Object files for target PPGSO_projekt
PPGSO_projekt_OBJECTS = \
"CMakeFiles/PPGSO_projekt.dir/main.cpp.obj"

# External object files for target PPGSO_projekt
PPGSO_projekt_EXTERNAL_OBJECTS =

PPGSO_projekt.exe: CMakeFiles/PPGSO_projekt.dir/main.cpp.obj
PPGSO_projekt.exe: CMakeFiles/PPGSO_projekt.dir/build.make
PPGSO_projekt.exe: CMakeFiles/PPGSO_projekt.dir/linklibs.rsp
PPGSO_projekt.exe: CMakeFiles/PPGSO_projekt.dir/objects1.rsp
PPGSO_projekt.exe: CMakeFiles/PPGSO_projekt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Skola\FIIT\3._semester\PPGSO_projekt\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable PPGSO_projekt.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\PPGSO_projekt.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PPGSO_projekt.dir/build: PPGSO_projekt.exe

.PHONY : CMakeFiles/PPGSO_projekt.dir/build

CMakeFiles/PPGSO_projekt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\PPGSO_projekt.dir\cmake_clean.cmake
.PHONY : CMakeFiles/PPGSO_projekt.dir/clean

CMakeFiles/PPGSO_projekt.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Skola\FIIT\3._semester\PPGSO_projekt D:\Skola\FIIT\3._semester\PPGSO_projekt D:\Skola\FIIT\3._semester\PPGSO_projekt\cmake-build-debug D:\Skola\FIIT\3._semester\PPGSO_projekt\cmake-build-debug D:\Skola\FIIT\3._semester\PPGSO_projekt\cmake-build-debug\CMakeFiles\PPGSO_projekt.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PPGSO_projekt.dir/depend

