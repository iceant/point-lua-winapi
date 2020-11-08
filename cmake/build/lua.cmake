cmake_minimum_required(VERSION 2.8)
project(lua C)

set(LUA_SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/lua-5.4.1/src)
set(LUA_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/deps/lua-5.4.1/src)

message(STATUS "LUA_SOURCE_DIR" ${LUA_SOURCE_DIR})
include_directories(${LUA_INCLUDE_DIR})

if (MINGW)
    add_definitions(-D_WIN32_WINNT=0x0600)
endif (MINGW)

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

set(LUA_SRC
        ${LUA_SOURCE_DIR}/lapi.c
        ${LUA_SOURCE_DIR}/lcode.c
        ${LUA_SOURCE_DIR}/lctype.c
        ${LUA_SOURCE_DIR}/ldebug.c
        ${LUA_SOURCE_DIR}/ldo.c
        ${LUA_SOURCE_DIR}/ldump.c
        ${LUA_SOURCE_DIR}/lfunc.c
        ${LUA_SOURCE_DIR}/lgc.c
        ${LUA_SOURCE_DIR}/llex.c
        ${LUA_SOURCE_DIR}/lmem.c
        ${LUA_SOURCE_DIR}/lobject.c
        ${LUA_SOURCE_DIR}/lopcodes.c
        ${LUA_SOURCE_DIR}/lparser.c
        ${LUA_SOURCE_DIR}/lstate.c
        ${LUA_SOURCE_DIR}/lstring.c
        ${LUA_SOURCE_DIR}/ltable.c
        ${LUA_SOURCE_DIR}/ltm.c
        ${LUA_SOURCE_DIR}/lundump.c
        ${LUA_SOURCE_DIR}/lvm.c
        ${LUA_SOURCE_DIR}/lzio.c
        ${LUA_SOURCE_DIR}/lauxlib.c
        ${LUA_SOURCE_DIR}/lbaselib.c
        ${LUA_SOURCE_DIR}/lcorolib.c
        ${LUA_SOURCE_DIR}/ldblib.c
        ${LUA_SOURCE_DIR}/liolib.c
        ${LUA_SOURCE_DIR}/lmathlib.c
        ${LUA_SOURCE_DIR}/loadlib.c
        ${LUA_SOURCE_DIR}/loslib.c
        ${LUA_SOURCE_DIR}/lstrlib.c
        ${LUA_SOURCE_DIR}/ltablib.c
        ${LUA_SOURCE_DIR}/lutf8lib.c
        ${LUA_SOURCE_DIR}/linit.c
        )


if(WIN32)
    add_library(liblua SHARED ${LUA_SRC})
    set_target_properties(liblua PROPERTIES PREFIX "" OUTPUT_NAME "lua541")
    set(LUA_LIBRARY lua541)
    add_definitions(-DLUA_BUILD_AS_DLL)
else()
    add_library(liblua STATIC ${LUA_SRC})
    add_definitions(-DLUA_USE_POSIX -DLUA_USE_DLOPEN)
    set(LUA_LIBRARY liblua)
endif()

add_executable(lua ${LUA_SOURCE_DIR}/lua.c)
target_link_libraries(lua liblua)

add_executable(luac ${LUA_SOURCE_DIR}/luac.c ${LUA_SRC})