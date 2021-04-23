# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.9)

project(
	QtApp
	VERSION 0.1.0
	LANGUAGES CXX
)

#Find Qt
find_package(Qt5 COMPONENTS Widgets REQUIRED)

#Enable Testing - Spikes
option(ENABEL_TESTING "Enable Testing" OFF)
option(ENABEL_SPIKES  "Enable Spikes"  OFF)

if(ENABEL_TESTING)
	enable_testing()
	#find_package()
endif()

# Add Static Library
add_subdirectory(libs)
# Add Binary EXE
add_subdirectory(app)
