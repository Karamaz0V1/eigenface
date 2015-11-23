PROJECT(eigenfaces)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
add_definitions(-std=c++11)

FIND_PACKAGE(VISP REQUIRED)
IF(VISP_FOUND)
  INCLUDE(${VISP_USE_FILE})
ENDIF(VISP_FOUND)

SET(SRC 
    main.cpp
    kvisp.cpp
    )

SET(HDR
    kvisp.h
    )

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC} ${HDR})
