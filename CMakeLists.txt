cmake_minimum_required(VERSION 3.17)
project(point_lua_winapi C)

set(CMAKE_C_STANDARD 99)

include_directories(src/)

option(BUILD_AS_SHARED "Build library as shared lib" ON)

if (WIN32)
    # replace /MD to /MT to avoid link msvcr*.dll
    # this needs to be before add_subdirectory calls so that they inherit the modified flags
    set(CompilerFlags
            CMAKE_C_FLAGS
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_MINSIZEREL
            CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_C_FLAGS_RELEASE)
    foreach(CompilerFlag ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
endif ()

include(cmake/build/lua.cmake)

if(BUILD_AS_SHARED)
    set(LIBRARY_TYPE SHARED)
else()
    set(LIBRARY_TYPE STATIC)
endif()

message(STATUS "LIBRARY_TYPE:" ${LIBRARY_TYPE})

add_library(point_lua_winapi
        ${LIBRARY_TYPE}
        src/plw_winapi_lib.c
        src/lua_bind.c )
set_target_properties(point_lua_winapi PROPERTIES OUTPUT_NAME "winapi")
target_link_libraries(point_lua_winapi ${LUA_LIBRARY})

add_subdirectory(tools)