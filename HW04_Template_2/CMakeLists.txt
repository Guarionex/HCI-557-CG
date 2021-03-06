# Main cmake file 
# Texture example

cmake_minimum_required(VERSION 2.6)

# policy for relative subfolders
cmake_policy(SET CMP0015 NEW)

# Main project name
project(Assignment_04)


set(CFILE_PATH  "${CMAKE_SOURCE_DIR}/../SDK/cmake/")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../SDK/cmake/")

message(STATUS "Source directory ${CMAKE_SOURCE_DIR}")
#message(STATUS "SDK directory ${CMAKE_SOURCE_DIR}/../SDK")


# Find packages
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(glew REQUIRED)
FIND_PACKAGE(glm REQUIRED)
FIND_PACKAGE(GLFW3 REQUIRED)


if (GLEW_FOUND)
message(STATUS "Found GLEW ${GLEW_INCLUDE_DIR} and ${GLEW_LIBRARIES}")
endif()

if (OPENGL_FOUND)
message(STATUS "Found OPENGL ${OPENGL_INCLUDE_DIR} and ${OPENGL_LIBRARIES}")
endif()

if (GLFW_FOUND)
message(STATUS "Found GLEW ${GLFW_INCLUDE_DIRS} and ${GLFW3_LIBRARY}")
else()
IF(WIN32)
ELSE(WIN32)
include_directories("/usr/local/Cellar/glfw/3.2.1/include")
include_directories("/usr/local/Cellar/glfw/1.11.0/include")
set( GLFW3_LIBRARY glfw)
ENDIF(WIN32)
endif()

# Include dirs
include_directories(./gl_common_ext)
include_directories(./../../gl_common_ext)
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLFW3_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})


# Add all files to the configuration
file(GLOB HCI557_SRC
	HW4_Textures.cpp
	./gl_common_ext/OpenGLDefaults.h
	./gl_common_ext/OpenGLDefaults.cpp
	./gl_common_ext/VertexBuffers.h
	./gl_common_ext/VertexBuffers.cpp
	./gl_common_ext/ShaderProgram.h
	./gl_common_ext/ShaderProgram.cpp
	./gl_common_ext/TrackballControls.h
	./gl_common_ext/TrackballControls.cpp
	./gl_common_ext/ModelCoordinateSystem.cpp
	./gl_common_ext/ModelCoordinateSystem.h
	./gl_common_ext/Window.cpp
	./gl_common_ext/Window.h
	./gl_common_ext/ModelPlane.h
	./gl_common_ext/ModelPlane.cpp
    	./gl_common_ext/Texture2D.h
	./gl_common_ext/Texture2D.cpp
	./gl_common_ext/BMPLoader.h
	./gl_common_ext/BMPLoader.cpp
)


add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)


# Create an executable
add_executable(Assignment_04 ${HCI557_SRC} )


# Add link directories
# Note required for this project
IF(WIN32)
	link_directories(${CMAKE_SOURCE_DIR}/../SDK/lib)
ELSE(WIN32)
	link_directories(${CMAKE_SOURCE_DIR}/../SDK/lib)
	link_directories(/usr/local/lib)
	link_directories(/usr/local/Cellar/glfw3/3.0.4/lib)
	link_directories(/usr/local/Cellar/glfw3/3.0.4/lib)
	link_directories(/usr/local/Cellar/glew/1.11.0/lib)
	link_directories(/usr/local/Cellar/glfw/3.2.1/lib)
ENDIF(WIN32)


# Add libraries
target_link_libraries(Assignment_04  ${GLEW_LIBRARIES} ${GLEW_LIBRARY} ${GLFW3_LIBRARY} ${OPENGL_LIBRARIES} ${OPENGL_LIBRARIES} )
