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

///////////////////////////////////////////////////////////////////////////////
//// static variables
static __declspec( thread ) lua_State* s_tlsL;

///////////////////////////////////////////////////////////////////////////////
//// types

#define PLW_TMSG "winapi_msg_t"
#define PLW_THWND "winapi_hwnd_t"

///////////////////////////////////////////////////////////////////////////////
////
typedef struct{
    HWND hwnd;
}plw_HWND_t;

///////////////////////////////////////////////////////////////////////////////
//// macros
#define PLW_CHECK_MSG(L, idx) (LPMSG)luaL_checkudata(L, (idx), PLW_TMSG)

#define PLW_PUSH_THWND(L, hwnd)                                             \
do{                                                                         \
    if(hwnd==NULL){                                                         \
        lua_pushnil(L);                                                     \
    }else{                                                                  \
        plw_HWND_t* lpHwnd = lua_newuserdata(L, sizeof(*lpHwnd));           \
        lpHwnd->hwnd = (hwnd);                                              \
        luaL_getmetatable(L, PLW_THWND);                                    \
        lua_setmetatable(L, -2);                                            \
    }                                                                       \
}while(0)

#define PLW_CHECK_HWND(L, idx, hwnd_t)                                          \
do{                                                                             \
    if(!lua_isnil(L, (idx))){                                                   \
        HWND __hwnd = NULL;                                                     \
        switch(lua_type(L, (idx))){                                             \
            case LUA_TUSERDATA:                                                 \
                (hwnd_t) = luaL_checkudata(L, (idx), PLW_THWND);                \
                break;                                                          \
            case LUA_TLIGHTUSERDATA:                                            \
                __hwnd = (HWND)lua_touserdata(L, (idx));                        \
                (hwnd_t) = lua_newuserdata(L, sizeof(*hwnd_t));                 \
                (hwnd_t)->hwnd = __hwnd;                                        \
                luaL_getmetatable(L, PLW_THWND);                                \
                lua_setmetatable(L, -2);                                        \
                break;                                                          \
            case LUA_TNUMBER:                                                   \
                __hwnd = (HWND)luaL_checkinteger(L, (idx));                     \
                (hwnd_t) = lua_newuserdata(L, sizeof(*hwnd_t));                 \
                (hwnd_t)->hwnd = __hwnd;                                        \
                luaL_getmetatable(L, PLW_THWND);                                \
                lua_setmetatable(L, -2);                                        \
                break;                                                          \
            default:                                                            \
                (hwnd_t)=NULL;                                                  \
        }                                                                       \
        luaL_argcheck(L, (hwnd_t)!=NULL, (idx), "invalid plw_HWND_t");          \
    }else{                                                                      \
        (hwnd_t)=NULL;                                                          \
    }                                                                           \
}while(0)

#endif //INCLUDED_PLW_DETAIL_H
