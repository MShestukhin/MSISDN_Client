# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /home/maxim/Downloads/CLion-2018.1.6/clion-2018.1.6/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/maxim/Downloads/CLion-2018.1.6/clion-2018.1.6/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maxim/Documents/MSISDN_Client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maxim/Documents/MSISDN_Client/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MNP_Client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MNP_Client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MNP_Client.dir/flags.make

CMakeFiles/MNP_Client.dir/dnsclient.cpp.o: CMakeFiles/MNP_Client.dir/flags.make
CMakeFiles/MNP_Client.dir/dnsclient.cpp.o: ../dnsclient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxim/Documents/MSISDN_Client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MNP_Client.dir/dnsclient.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MNP_Client.dir/dnsclient.cpp.o -c /home/maxim/Documents/MSISDN_Client/dnsclient.cpp

CMakeFiles/MNP_Client.dir/dnsclient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MNP_Client.dir/dnsclient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maxim/Documents/MSISDN_Client/dnsclient.cpp > CMakeFiles/MNP_Client.dir/dnsclient.cpp.i

CMakeFiles/MNP_Client.dir/dnsclient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MNP_Client.dir/dnsclient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maxim/Documents/MSISDN_Client/dnsclient.cpp -o CMakeFiles/MNP_Client.dir/dnsclient.cpp.s

CMakeFiles/MNP_Client.dir/dnsclient.cpp.o.requires:

.PHONY : CMakeFiles/MNP_Client.dir/dnsclient.cpp.o.requires

CMakeFiles/MNP_Client.dir/dnsclient.cpp.o.provides: CMakeFiles/MNP_Client.dir/dnsclient.cpp.o.requires
	$(MAKE) -f CMakeFiles/MNP_Client.dir/build.make CMakeFiles/MNP_Client.dir/dnsclient.cpp.o.provides.build
.PHONY : CMakeFiles/MNP_Client.dir/dnsclient.cpp.o.provides

CMakeFiles/MNP_Client.dir/dnsclient.cpp.o.provides.build: CMakeFiles/MNP_Client.dir/dnsclient.cpp.o


CMakeFiles/MNP_Client.dir/main.cpp.o: CMakeFiles/MNP_Client.dir/flags.make
CMakeFiles/MNP_Client.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxim/Documents/MSISDN_Client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MNP_Client.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MNP_Client.dir/main.cpp.o -c /home/maxim/Documents/MSISDN_Client/main.cpp

CMakeFiles/MNP_Client.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MNP_Client.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maxim/Documents/MSISDN_Client/main.cpp > CMakeFiles/MNP_Client.dir/main.cpp.i

CMakeFiles/MNP_Client.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MNP_Client.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maxim/Documents/MSISDN_Client/main.cpp -o CMakeFiles/MNP_Client.dir/main.cpp.s

CMakeFiles/MNP_Client.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/MNP_Client.dir/main.cpp.o.requires

CMakeFiles/MNP_Client.dir/main.cpp.o.provides: CMakeFiles/MNP_Client.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/MNP_Client.dir/build.make CMakeFiles/MNP_Client.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/MNP_Client.dir/main.cpp.o.provides

CMakeFiles/MNP_Client.dir/main.cpp.o.provides.build: CMakeFiles/MNP_Client.dir/main.cpp.o


# Object files for target MNP_Client
MNP_Client_OBJECTS = \
"CMakeFiles/MNP_Client.dir/dnsclient.cpp.o" \
"CMakeFiles/MNP_Client.dir/main.cpp.o"

# External object files for target MNP_Client
MNP_Client_EXTERNAL_OBJECTS =

MNP_Client: CMakeFiles/MNP_Client.dir/dnsclient.cpp.o
MNP_Client: CMakeFiles/MNP_Client.dir/main.cpp.o
MNP_Client: CMakeFiles/MNP_Client.dir/build.make
MNP_Client: ../lib/libocilib.a
MNP_Client: ../lib/libclntsh.so.11.1
MNP_Client: /usr/lib/x86_64-linux-gnu/libboost_system.a
MNP_Client: /usr/lib/x86_64-linux-gnu/libboost_thread.a
MNP_Client: /usr/lib/x86_64-linux-gnu/libboost_chrono.a
MNP_Client: /usr/lib/x86_64-linux-gnu/libboost_date_time.a
MNP_Client: /usr/lib/x86_64-linux-gnu/libboost_atomic.a
MNP_Client: ../lib/libconfig++.a
MNP_Client: CMakeFiles/MNP_Client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maxim/Documents/MSISDN_Client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable MNP_Client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MNP_Client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MNP_Client.dir/build: MNP_Client

.PHONY : CMakeFiles/MNP_Client.dir/build

CMakeFiles/MNP_Client.dir/requires: CMakeFiles/MNP_Client.dir/dnsclient.cpp.o.requires
CMakeFiles/MNP_Client.dir/requires: CMakeFiles/MNP_Client.dir/main.cpp.o.requires

.PHONY : CMakeFiles/MNP_Client.dir/requires

CMakeFiles/MNP_Client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MNP_Client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MNP_Client.dir/clean

CMakeFiles/MNP_Client.dir/depend:
	cd /home/maxim/Documents/MSISDN_Client/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maxim/Documents/MSISDN_Client /home/maxim/Documents/MSISDN_Client /home/maxim/Documents/MSISDN_Client/cmake-build-debug /home/maxim/Documents/MSISDN_Client/cmake-build-debug /home/maxim/Documents/MSISDN_Client/cmake-build-debug/CMakeFiles/MNP_Client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MNP_Client.dir/depend

