PROJECT(eigenfaces)

CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
add_definitions(-std=c++11)

FIND_PACKAGE(VISP REQUIRED)
IF(VISP_FOUND)
  INCLUDE(${VISP_USE_FILE})
ENDIF(VISP_FOUND)

add_compile_options("$<$<CONFIG:DEBUG>:-Wall>")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET(SRC 
    main.cpp
    kvisp.cpp
    Eigenfaces.cpp
    )

SET(HDR
    kvisp.h
    Eigenfaces.h
    )

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC} ${HDR})
