# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.1.1\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.1.1\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\ANre\c\pb071\hw04

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\ANre\c\pb071\hw04\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/poker.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/poker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/poker.dir/flags.make

CMakeFiles/poker.dir/main.c.obj: CMakeFiles/poker.dir/flags.make
CMakeFiles/poker.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\ANre\c\pb071\hw04\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/poker.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\poker.dir\main.c.obj   -c C:\ANre\c\pb071\hw04\main.c

CMakeFiles/poker.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/poker.dir/main.c.i"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\ANre\c\pb071\hw04\main.c > CMakeFiles\poker.dir\main.c.i

CMakeFiles/poker.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/poker.dir/main.c.s"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\ANre\c\pb071\hw04\main.c -o CMakeFiles\poker.dir\main.c.s

CMakeFiles/poker.dir/main.c.obj.requires:

.PHONY : CMakeFiles/poker.dir/main.c.obj.requires

CMakeFiles/poker.dir/main.c.obj.provides: CMakeFiles/poker.dir/main.c.obj.requires
	$(MAKE) -f CMakeFiles\poker.dir\build.make CMakeFiles/poker.dir/main.c.obj.provides.build
.PHONY : CMakeFiles/poker.dir/main.c.obj.provides

CMakeFiles/poker.dir/main.c.obj.provides.build: CMakeFiles/poker.dir/main.c.obj


CMakeFiles/poker.dir/hash_helper.c.obj: CMakeFiles/poker.dir/flags.make
CMakeFiles/poker.dir/hash_helper.c.obj: ../hash_helper.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\ANre\c\pb071\hw04\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/poker.dir/hash_helper.c.obj"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\poker.dir\hash_helper.c.obj   -c C:\ANre\c\pb071\hw04\hash_helper.c

CMakeFiles/poker.dir/hash_helper.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/poker.dir/hash_helper.c.i"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\ANre\c\pb071\hw04\hash_helper.c > CMakeFiles\poker.dir\hash_helper.c.i

CMakeFiles/poker.dir/hash_helper.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/poker.dir/hash_helper.c.s"
	C:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\ANre\c\pb071\hw04\hash_helper.c -o CMakeFiles\poker.dir\hash_helper.c.s

CMakeFiles/poker.dir/hash_helper.c.obj.requires:

.PHONY : CMakeFiles/poker.dir/hash_helper.c.obj.requires

CMakeFiles/poker.dir/hash_helper.c.obj.provides: CMakeFiles/poker.dir/hash_helper.c.obj.requires
	$(MAKE) -f CMakeFiles\poker.dir\build.make CMakeFiles/poker.dir/hash_helper.c.obj.provides.build
.PHONY : CMakeFiles/poker.dir/hash_helper.c.obj.provides

CMakeFiles/poker.dir/hash_helper.c.obj.provides.build: CMakeFiles/poker.dir/hash_helper.c.obj


# Object files for target poker
poker_OBJECTS = \
"CMakeFiles/poker.dir/main.c.obj" \
"CMakeFiles/poker.dir/hash_helper.c.obj"

# External object files for target poker
poker_EXTERNAL_OBJECTS =

poker.exe: CMakeFiles/poker.dir/main.c.obj
poker.exe: CMakeFiles/poker.dir/hash_helper.c.obj
poker.exe: CMakeFiles/poker.dir/build.make
poker.exe: CMakeFiles/poker.dir/linklibs.rsp
poker.exe: CMakeFiles/poker.dir/objects1.rsp
poker.exe: CMakeFiles/poker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\ANre\c\pb071\hw04\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable poker.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\poker.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/poker.dir/build: poker.exe

.PHONY : CMakeFiles/poker.dir/build

CMakeFiles/poker.dir/requires: CMakeFiles/poker.dir/main.c.obj.requires
CMakeFiles/poker.dir/requires: CMakeFiles/poker.dir/hash_helper.c.obj.requires

.PHONY : CMakeFiles/poker.dir/requires

CMakeFiles/poker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\poker.dir\cmake_clean.cmake
.PHONY : CMakeFiles/poker.dir/clean

CMakeFiles/poker.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\ANre\c\pb071\hw04 C:\ANre\c\pb071\hw04 C:\ANre\c\pb071\hw04\cmake-build-debug C:\ANre\c\pb071\hw04\cmake-build-debug C:\ANre\c\pb071\hw04\cmake-build-debug\CMakeFiles\poker.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/poker.dir/depend
