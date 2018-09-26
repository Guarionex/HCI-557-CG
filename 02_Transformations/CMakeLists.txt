# Main cmake file 
# Simple Model

cmake_minimum_required(VERSION 2.6)

# Main project name is ARMaker
project(HW2_Transformations)


set(CFILE_PATH  "${CMAKE_SOURCE_DIR}/../../SDK/cmake/")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../SDK/cmake/")

message(STATUS "Source directory ${CMAKE_SOURCE_DIR}")
message(STATUS "SDK directory ${CMAKE_SOURCE_DIR}/../../SDK")


# Find packages
FIND_PACKAGE(glew REQUIRED)
FIND_PACKAGE(glm REQUIRED)
FIND_PACKAGE(glfw3 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)


# Include dirs
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLFW3_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories("./dep")


# Add all files to the configuration
set(HW2_Transformations_SRC
	Assignment2_Transformations.cpp
    ShaderCode.h
)
set( Dependencies
    ./dep/ModelCoordinateSystem.h
	./dep/ModelCoordinateSystem.cpp
	./dep/OpenGLDefaults.h
	./dep/OpenGLDefaults.cpp
	./dep/TrackballControls.h
	./dep/TrackballControls.cpp
	./dep/TrackballControls.h
	./dep/TrackballControls.cpp
	./dep/Window.h
	./dep/Window.cpp
	./dep/VertexBuffers.h
	./dep/VertexBuffers.cpp
	./dep/ShaderProgram.h
	./dep/ShaderProgram.cpp

    
)


source_group( Source FILES ${Dependencies} )
source_group( dep FILES ${Dependencies} )

# Create an executable
add_executable(HW2_Transformations 
			${HW2_Transformations_SRC}
			${Dependencies}
			)


# Add link directories
# Note required for this project
IF(WIN32)
	link_directories(${CMAKE_SOURCE_DIR}/../SDK/lib)
ELSE(WIN32)
	link_directories(${CMAKE_SOURCE_DIR}/../SDK/lib)
	link_directories(/usr/local/lib)
	link_directories(/usr/local/Cellar/glfw3/3.0.4/lib)
	link_directories(/usr/local/Cellar/glew/1.11.0/lib)
ENDIF(WIN32)


# Add libraries
target_link_libraries(HW2_Transformations ${GLEW_LIBRARY} ${GLFW3_LIBRARY} ${OPENGL_LIBRARIES} ${OPENGL_LIBRARIES} )
