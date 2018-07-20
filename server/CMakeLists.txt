cmake_minimum_required (VERSION 3.1.0 FATAL_ERROR)

set (PROJECT IqMeteoServer)
set (VERSION 1.0.0)
string (TOLOWER ${PROJECT} TARGET)

project (${PROJECT})

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)

find_package (Qt5Widgets REQUIRED)
find_package (Qt5Network REQUIRED)

file (GLOB_RECURSE SOURCES . src/*.cpp)
source_group ("Source Files" FILES ${SOURCES})
file (GLOB HEADERS . src/*.h)
file(GLOB RESOURCES . src/*.qrc)

qt5_add_resources(RESOURCES_HEADERS ${RESOURCES})

set (ICON_RES_FILE "")
if(MINGW)
    file (GLOB ICON_RES_FILE . src/icon.rc)
    SET (CMAKE_RC_COMPILE_OBJECT
            "<CMAKE_RC_COMPILER> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
endif(MINGW)


add_executable (${TARGET} WIN32 ${SOURCES} ${RESOURCES_HEADERS} ${ICON_RES_FILE})

target_link_libraries (${TARGET} Qt5::Widgets Qt5::Network ${IqOrm_LIBRARIES} ${IqWamp_LIBRARIES})

set_target_properties (${TARGET} PROPERTIES
                       VERSION ${VERSION})

if (MINGW)
    add_definitions(-std=c++11)
else (MINGW)
    target_compile_features (${TARGET} PRIVATE cxx_range_for)
endif ()

if (MSVC)
    add_definitions (/W4)
elseif (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    add_definitions (-Wall -pedantic)
else ()
    message ("Unknown compiler")
endif ()
