#################################################
# Projeto Elo Maluco
#################################################

project(Elo_Maluco)
cmake_minimum_required(VERSION 2.8)

################################################################################
# COMPILER
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

################################################################################
# CMake variables
set(${PROJECT_NAME}_ROOT_DIR         ${CMAKE_SOURCE_DIR})

SET(CMAKE_MODULE_PATH                ${${PROJECT_NAME}_ROOT_DIR}/cmake)
SET(CMAKE_CURRENT_BINARY_DIR         ${${PROJECT_NAME}_ROOT_DIR}/build)
SET(CMAKE_INSTALL_PREFIX             ${${PROJECT_NAME}_ROOT_DIR}/bin)

################################################################################
# OpenGL

find_package(OpenGL REQUIRED)

include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
        message(Error "OpenGL not found")
endif(NOT OPENGL_FOUND)

################################################################################
# GLUT

find_package(GLUT REQUIRED)

include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

if(NOT GLUT_FOUND)
        message(Error "GLUT not found")
endif(NOT GLUT_FOUND)

################################################################################
# SOIL

set(SOIL_INCLUDE_DIR "/usr/include/SOIL")    # Caminho para os cabeçalhos
set(SOIL_LIBRARY "/usr/lib/libSOIL.so")      # Caminho para a biblioteca

include_directories(${SOIL_INCLUDE_DIR})     # Incluir o diretório de cabeçalhos
link_directories("/usr/lib")                 # Diretório da biblioteca

# Verifique se a biblioteca SOIL foi encontrada
if(NOT EXISTS ${SOIL_LIBRARY})
    message(FATAL_ERROR "SOIL library not found in ${SOIL_LIBRARY}")
endif()

################################################################################
# FILES
set(HDRS
    src/application.hpp
    src/tinyxml2.h
    src/square.hpp
    src/cube.hpp
    src/XMLManager.hpp
    src/translator.hpp
    src/textureManager.hpp
)

set(SRCS
    src/main.cpp
    src/application.cpp
    src/tinyxml2.cpp
    src/square.cpp
    src/cube.cpp
    src/XMLManager.cpp
    src/translator.cpp
    src/textureManager.cpp
)

################################################################################
# EXEC
add_executable(${PROJECT_NAME} ${HDRS} ${SRCS})

# LIBS
set(LIBS
    ${OPENGL_LIBRARIES} 
    ${GLUT_LIBRARIES}
    ${GLM_LIBRARIES}
    ${SOIL_LIBRARY}
)

# LINK
target_link_libraries(${PROJECT_NAME} ${LIBS})

#Install