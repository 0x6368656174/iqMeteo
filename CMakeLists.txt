cmake_minimum_required (VERSION 3.1.0 FATAL_ERROR)

set (PROJECT IqMeteo)
set (VERSION 1.0.0)

project (${PROJECT})

set (IqWamp_DEBUG_MODE ON)
add_subdirectory (IqWamp)
if (${IqWamp_FOUND})
    include_directories (${IqWamp_INCLUDE_DIRS})
endif ()

set (IqOrm_DEBUG_MODE ON)
add_subdirectory (IqOrm)
if (${IqOrm_FOUND})
    include_directories (${IqOrm_INCLUDE_DIRS})
endif ()

add_subdirectory(server)
add_subdirectory(client)
