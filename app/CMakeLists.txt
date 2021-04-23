#apps/CMakeLists.txt
if(WIN32)
add_executable(
	QtApp
	WIN32
	main.cpp
)
else()
add_executable(
	QtApp
	main.cpp
)
endif()

target_link_libraries(
	QtApp
	PRIVATE
	#Mint::Library(Alias Optional)
	QtAppLibrary
)

# TODO: Add tests and install targets if needed.
