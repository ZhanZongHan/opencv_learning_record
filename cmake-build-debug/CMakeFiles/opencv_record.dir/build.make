# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /opt/JetBrains/apps/CLion/ch-0/183.4588.63/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/JetBrains/apps/CLion/ch-0/183.4588.63/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zzh/code/CLionProjects/opencv_record

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zzh/code/CLionProjects/opencv_record/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/opencv_record.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/opencv_record.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/opencv_record.dir/flags.make

CMakeFiles/opencv_record.dir/ex5/test1.cpp.o: CMakeFiles/opencv_record.dir/flags.make
CMakeFiles/opencv_record.dir/ex5/test1.cpp.o: ../ex5/test1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zzh/code/CLionProjects/opencv_record/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/opencv_record.dir/ex5/test1.cpp.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opencv_record.dir/ex5/test1.cpp.o -c /home/zzh/code/CLionProjects/opencv_record/ex5/test1.cpp

CMakeFiles/opencv_record.dir/ex5/test1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_record.dir/ex5/test1.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zzh/code/CLionProjects/opencv_record/ex5/test1.cpp > CMakeFiles/opencv_record.dir/ex5/test1.cpp.i

CMakeFiles/opencv_record.dir/ex5/test1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_record.dir/ex5/test1.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zzh/code/CLionProjects/opencv_record/ex5/test1.cpp -o CMakeFiles/opencv_record.dir/ex5/test1.cpp.s

CMakeFiles/opencv_record.dir/opencv_record_autogen/mocs_compilation.cpp.o: CMakeFiles/opencv_record.dir/flags.make
CMakeFiles/opencv_record.dir/opencv_record_autogen/mocs_compilation.cpp.o: opencv_record_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zzh/code/CLionProjects/opencv_record/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/opencv_record.dir/opencv_record_autogen/mocs_compilation.cpp.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opencv_record.dir/opencv_record_autogen/mocs_compilation.cpp.o -c /home/zzh/code/CLionProjects/opencv_record/cmake-build-debug/opencv_record_autogen/mocs_compilation.cpp

CMakeFiles/opencv_record.dir/opencv_record_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_record.dir/opencv_record_autogen/mocs_compilation.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zzh/code/CLionProjects/opencv_record/cmake-build-debug/opencv_record_autogen/mocs_compilation.cpp > CMakeFiles/opencv_record.dir/opencv_record_autogen/mocs_compilation.cpp.i

CMakeFiles/opencv_record.dir/opencv_record_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_record.dir/opencv_record_autogen/mocs_compilation.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zzh/code/CLionProjects/opencv_record/cmake-build-debug/opencv_record_autogen/mocs_compilation.cpp -o CMakeFiles/opencv_record.dir/opencv_record_autogen/mocs_compilation.cpp.s

# Object files for target opencv_record
opencv_record_OBJECTS = \
"CMakeFiles/opencv_record.dir/ex5/test1.cpp.o" \
"CMakeFiles/opencv_record.dir/opencv_record_autogen/mocs_compilation.cpp.o"

# External object files for target opencv_record
opencv_record_EXTERNAL_OBJECTS =

opencv_record: CMakeFiles/opencv_record.dir/ex5/test1.cpp.o
opencv_record: CMakeFiles/opencv_record.dir/opencv_record_autogen/mocs_compilation.cpp.o
opencv_record: CMakeFiles/opencv_record.dir/build.make
opencv_record: /usr/lib/libopencv_gapi.so.4.0.0
opencv_record: /usr/lib/libopencv_stitching.so.4.0.0
opencv_record: /usr/lib/libopencv_aruco.so.4.0.0
opencv_record: /usr/lib/libopencv_bgsegm.so.4.0.0
opencv_record: /usr/lib/libopencv_bioinspired.so.4.0.0
opencv_record: /usr/lib/libopencv_ccalib.so.4.0.0
opencv_record: /usr/lib/libopencv_dnn_objdetect.so.4.0.0
opencv_record: /usr/lib/libopencv_dpm.so.4.0.0
opencv_record: /usr/lib/libopencv_face.so.4.0.0
opencv_record: /usr/lib/libopencv_freetype.so.4.0.0
opencv_record: /usr/lib/libopencv_fuzzy.so.4.0.0
opencv_record: /usr/lib/libopencv_hdf.so.4.0.0
opencv_record: /usr/lib/libopencv_hfs.so.4.0.0
opencv_record: /usr/lib/libopencv_img_hash.so.4.0.0
opencv_record: /usr/lib/libopencv_line_descriptor.so.4.0.0
opencv_record: /usr/lib/libopencv_reg.so.4.0.0
opencv_record: /usr/lib/libopencv_rgbd.so.4.0.0
opencv_record: /usr/lib/libopencv_saliency.so.4.0.0
opencv_record: /usr/lib/libopencv_stereo.so.4.0.0
opencv_record: /usr/lib/libopencv_structured_light.so.4.0.0
opencv_record: /usr/lib/libopencv_superres.so.4.0.0
opencv_record: /usr/lib/libopencv_surface_matching.so.4.0.0
opencv_record: /usr/lib/libopencv_tracking.so.4.0.0
opencv_record: /usr/lib/libopencv_videostab.so.4.0.0
opencv_record: /usr/lib/libopencv_viz.so.4.0.0
opencv_record: /usr/lib/libopencv_xfeatures2d.so.4.0.0
opencv_record: /usr/lib/libopencv_xobjdetect.so.4.0.0
opencv_record: /usr/lib/libopencv_xphoto.so.4.0.0
opencv_record: /usr/lib/libQt5Widgets.so.5.11.2
opencv_record: /usr/lib/libopencv_shape.so.4.0.0
opencv_record: /usr/lib/libopencv_phase_unwrapping.so.4.0.0
opencv_record: /usr/lib/libopencv_optflow.so.4.0.0
opencv_record: /usr/lib/libopencv_ximgproc.so.4.0.0
opencv_record: /usr/lib/libopencv_datasets.so.4.0.0
opencv_record: /usr/lib/libopencv_plot.so.4.0.0
opencv_record: /usr/lib/libopencv_text.so.4.0.0
opencv_record: /usr/lib/libopencv_dnn.so.4.0.0
opencv_record: /usr/lib/libopencv_ml.so.4.0.0
opencv_record: /usr/lib/libopencv_photo.so.4.0.0
opencv_record: /usr/lib/libopencv_video.so.4.0.0
opencv_record: /usr/lib/libopencv_objdetect.so.4.0.0
opencv_record: /usr/lib/libopencv_calib3d.so.4.0.0
opencv_record: /usr/lib/libopencv_features2d.so.4.0.0
opencv_record: /usr/lib/libopencv_flann.so.4.0.0
opencv_record: /usr/lib/libopencv_highgui.so.4.0.0
opencv_record: /usr/lib/libopencv_videoio.so.4.0.0
opencv_record: /usr/lib/libopencv_imgcodecs.so.4.0.0
opencv_record: /usr/lib/libopencv_imgproc.so.4.0.0
opencv_record: /usr/lib/libopencv_core.so.4.0.0
opencv_record: /usr/lib/libQt5Gui.so.5.11.2
opencv_record: /usr/lib/libQt5Core.so.5.11.2
opencv_record: CMakeFiles/opencv_record.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zzh/code/CLionProjects/opencv_record/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable opencv_record"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opencv_record.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/opencv_record.dir/build: opencv_record

.PHONY : CMakeFiles/opencv_record.dir/build

CMakeFiles/opencv_record.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/opencv_record.dir/cmake_clean.cmake
.PHONY : CMakeFiles/opencv_record.dir/clean

CMakeFiles/opencv_record.dir/depend:
	cd /home/zzh/code/CLionProjects/opencv_record/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zzh/code/CLionProjects/opencv_record /home/zzh/code/CLionProjects/opencv_record /home/zzh/code/CLionProjects/opencv_record/cmake-build-debug /home/zzh/code/CLionProjects/opencv_record/cmake-build-debug /home/zzh/code/CLionProjects/opencv_record/cmake-build-debug/CMakeFiles/opencv_record.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/opencv_record.dir/depend

