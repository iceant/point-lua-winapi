#ifndef INCLUDED_PLW_DETAIL_H
#define INCLUDED_PLW_DETAIL_H

#ifndef INCLUDED_WINDOWS_H
#define INCLUDED_WINDOWS_H
#include <windows.h>
#endif // INCLUDED_WINDOWS_H

#ifndef INCLUDED_WINDOWSX_H
#define INCLUDED_WINDOWSX_H
#include <windowsx.h>
#endif // INCLUDED_WINDOWSX_H

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif // INCLUDED_ASSERT_H

#ifndef INCLUDED_LUA_BIND_H
#include <lua_bind.h>
#endif //INCLUDED_LUA_BIND_H

#define PLW_WINDOW_PROP_LUA_STATE "plw_window_lua_State"

static __declspec( thread ) lua_State* tlsL;

#endif //INCLUDED_PLW_DETAIL_H
