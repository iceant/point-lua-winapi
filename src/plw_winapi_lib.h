#ifndef INCLUDED_PLW_WINAPI_LIB_H
#define INCLUDED_PLW_WINAPI_LIB_H

#define LUA_LIB

#ifndef INCLUDED_LUA_H
#define INCLUDED_LUA_H
#include <lua.h>
#endif // INCLUDED_LUA_H

#ifndef INCLUDED_LUALIB_H
#define INCLUDED_LUALIB_H
#include <lualib.h>
#endif // INCLUDED_LUALIB_H

#ifndef INCLUDED_LAUXLIB_H
#define INCLUDED_LAUXLIB_H
#include <lauxlib.h>
#endif // INCLUDED_LAUXLIB_H


///////////////////////////////////////////////////////////////////////////////
////
LUALIB_API int luaopen_winapi(lua_State* L);

#endif //INCLUDED_PLW_WINAPI_LIB_H
