# libs/CMakeLists.txt

add_library(
	QtAppLibrary
	STATIC
)

#Putting alias is optional to force CMake to treat Mint as target not as lib
#add_library(
	#Mint::Library
	#ALIAS
	#MintLibrary
#)

target_sources(
	QtAppLibrary
	PRIVATE
	src/MainWindow.cpp
	#Resources
	res/resources.qrc
)

target_include_directories(
	QtAppLibrary
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
  QtAppLibrary
  PUBLIC
  Qt5::Widgets
)

set_target_properties(
	QtAppLibrary
	PROPERTIES
	AUTOMOC ON
	AUTORCC ON
)

if(ENABEL_TESTING)
#add_subdirectory
endif()

if(ENABEL_SPIKES)
#add_subdirectory
endif()
