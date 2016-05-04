cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(libmono)

INCLUDE(FindPkgConfig)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets 5.4.0 REQUIRED)
find_package(Qt5LinguistTools 5.4.0 REQUIRED)

get_target_property(QT_LRELEASE_EXECUTABLE Qt5::lrelease IMPORTED_LOCATION)

IF(QT_LRELEASE_EXECUTABLE)
MESSAGE(STATUS "Found lrelease executable: " ${QT_LRELEASE_EXECUTABLE})
ELSE(QT_LRELEASE_EXECUTABLE)
MESSAGE(FATAL_ERROR "Could NOT find lrelease executable")
ENDIF(QT_LRELEASE_EXECUTABLE)

include_directories(SYSTEM /usr/local/include)
pkg_check_modules(QMMP qmmp>=1.0.0 REQUIRED)
include_directories(${QMMP_INCLUDEDIR})

if(COMMAND cmake_policy)
cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# libqmmp
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../)
# link_directories(${CMAKE_CURRENT_BINARY_DIR}/../../../qmmp)

SET(LIB_DIR "lib${LIB_SUFFIX}" CACHE STRING "library path")

SET(libmono_SRCS
    monoplugin.cpp
    effectmonofactory.cpp
)

SET(libmono_HDRS
    monoplugin.h
)

# SET(libmono_RCCS translations/translations.qrc)

# QT5_ADD_RESOURCES(libmono_RCC_SRCS ${libmono_RCCS})

# user interface

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
include_directories(${CMAKE_CURRENT_BINARY_DIR})


ADD_LIBRARY(mono MODULE ${libmono_SRCS} ${libmono_RCC_SRCS} ${libmono_HDRS})
# add_dependencies(mono qmmp)
target_link_libraries(mono Qt5::Widgets -lqmmp)
install(TARGETS mono DESTINATION ${LIB_DIR}/qmmp/Effect)
