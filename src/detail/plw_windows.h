#ifndef INCLUDED_PWL_WINDOWS_H
#define INCLUDED_PWL_WINDOWS_H

#ifndef INCLUDED_PLW_DETAIL_H
#include "./plw_detail.h"
#endif //INCLUDED_PLW_DETAIL_H

///////////////////////////////////////////////////////////////////////////////
//// types
typedef struct {
    DWORD dwExStyle;
    LPCTSTR lpClassName;
    LPCTSTR lpWindowName;
    DWORD dwStyle;
    int x;
    int y;
    int nWidth;
    int nHeight;
    HWND hWndParent;
    HMENU hMenu;
    HINSTANCE hInstance;
    LPVOID lpParam;
}plw_window_CreateWindow_t;

///////////////////////////////////////////////////////////////////////////////
//// functions

/*
 HWND FindWindowA(
  LPCSTR lpClassName,
  LPCSTR lpWindowName
);

Lua:
    FindWindow(className, windowName)
    FindWindow(nil, windowName)
    FindWindow(className, nil)
    FindWindow()
 */
static int plw_window_FindWindow(lua_State* L){
    int top = lua_gettop(L);
    if(top==0){
        HWND hwnd = FindWindow(NULL, NULL);
        PLW_PUSH_THWND(L, hwnd);
        return 1;
    }else if(top==2){
        char* lpClassName = NULL;
        char* lpWindowName = NULL;
        if(!lua_isnil(L, 1)){
            lpClassName = (char*)luaL_checkstring(L, 1);
        }
        if(!lua_isnil(L, 2)){
            lpWindowName = (char*)luaL_checkstring(L, 2);
        }
        HWND hwnd = FindWindow(lpClassName, lpWindowName);
        PLW_PUSH_THWND(L, hwnd);
        return 1;
    }
    lua_pushnil(L);
    return 1;
}

/*
 * GetWindowText(hwnd, GetWindowTextLength(hwnd))
 * GetWindowText(hwnd)
 * */
static int plw_window_GetWindowText(lua_State* L){
    int top = lua_gettop(L);
    plw_HWND_t * hwnd;
    PLW_CHECK_HWND(L, 1, hwnd);
    int nMaxCount = 256;
    if(top>1){
        luaL_checkany(L, 2);
        int nMaxCount = luaL_checkinteger(L, 2);
        luaL_argcheck(L, nMaxCount>0, 2, "length<0");
    }
    char * lpString = malloc(nMaxCount);
    memset(lpString, 0, nMaxCount);
    int ret = GetWindowText(hwnd->hwnd, lpString, nMaxCount);
    if(ret!=0){
        lua_pushlstring(L, lpString, ret);
    }else{
        lua_pushnil(L);
    }
    free(lpString);
    return 1;
}

/*
 * GetWindowTextLength(hwnd)
 * */
static int plw_window_GetWindowTextLength(lua_State* L){
    plw_HWND_t * hwnd = NULL;
    PLW_CHECK_HWND(L, 1, hwnd);
    int ret = GetWindowTextLength(hwnd->hwnd);
    lua_pushinteger(L, ret);
    return 1;
}

static int plw_window_CreateWindow(lua_State* L){
    plw_window_CreateWindow_t p;
    memset(&p, 0, sizeof(p));
    LUA_BIND_2OBJ_STR(L, 1, p, ., lpClassName);
    LUA_BIND_2OBJ_STR(L, 1, p, ., lpWindowName);
    LUA_BIND_2OBJ_INT(L, 1, p, ., dwStyle);
    LUA_BIND_2OBJ_INT(L, 1, p, ., x);
    LUA_BIND_2OBJ_INT(L, 1, p, ., y);
    LUA_BIND_2OBJ_INT(L, 1, p, ., nWidth);
    LUA_BIND_2OBJ_INT(L, 1, p, ., nHeight);
    LUA_BIND_2OBJ_PTR(L, 1, p, ., hWndParent);
    LUA_BIND_2OBJ_PTR(L, 1, p, ., hMenu);
    LUA_BIND_2OBJ_PTR(L, 1, p, ., hInstance);
    LUA_BIND_2OBJ_PTR(L, 1, p, ., lpParam);

    HWND hwnd = CreateWindow(p.lpClassName, p.lpWindowName, p.dwStyle,
                 p.x, p.y, p.nWidth, p.nHeight,
                 p.hWndParent, p.hMenu, p.hInstance, p.lpParam);
    PLW_PUSH_THWND(L, hwnd);
    return 1;
}

static int plw_window_ShowWindow(lua_State* L){
    int top = lua_gettop(L);
    plw_HWND_t * hwnd = NULL;
    if(!lua_isnil(L, 1)){
        hwnd = luaL_checkudata(L, 1, PLW_THWND);
        luaL_argcheck(L, hwnd!=NULL, 1, "invalid HWND");
    }
    int nCmdShow = SW_NORMAL;
    if(top>1){
        luaL_checkany(L, 2);
        nCmdShow = luaL_checkinteger(L, 2);
    }
    BOOL ret = ShowWindow(hwnd->hwnd, nCmdShow);
    lua_pushboolean(L, ret);
    return 1;
}

static int plw_window_UpdateWindow(lua_State* L){
    plw_HWND_t * hwnd = NULL;
    PLW_CHECK_HWND(L, 1, hwnd);

    BOOL ret = UpdateWindow(hwnd->hwnd);
    lua_pushboolean(L, ret);
    return 1;
}


///////////////////////////////////////////////////////////////////////////////
//// macros
static int plw_window_GET_X_LPARAM(lua_State*L){
    LPARAM lParam = (LPARAM)luaL_checkinteger(L, 1);
    int ret = GET_X_LPARAM(lParam);
    lua_pushinteger(L, ret);
    return 1;
}

static int plw_window_GET_Y_LPARAM(lua_State*L){
    LPARAM lParam = (LPARAM)luaL_checkinteger(L, 1);
    int ret = GET_Y_LPARAM(lParam);
    lua_pushinteger(L, ret);
    return 1;
}

static int plw_window_HIBYTE(lua_State*L){
    DWORD_PTR w = (DWORD_PTR)luaL_checkinteger(L, 1);
    int ret = HIBYTE(w);
    lua_pushinteger(L, ret);
    return 1;
}

static int plw_window_HIWORD(lua_State*L){
    DWORD_PTR w = (DWORD_PTR)luaL_checkinteger(L, 1);
    int ret = HIWORD(w);
    lua_pushinteger(L, ret);
    return 1;
}

static int plw_window_LOBYTE(lua_State*L){
    DWORD_PTR w = (DWORD_PTR)luaL_checkinteger(L, 1);
    int ret = LOBYTE(w);
    lua_pushinteger(L, ret);
    return 1;
}

static int plw_window_LOWORD(lua_State*L){
    DWORD_PTR w = (DWORD_PTR)luaL_checkinteger(L, 1);
    int ret = LOWORD(w);
    lua_pushinteger(L, ret);
    return 1;
}

static int plw_window_MAKELONG(lua_State*L){
    DWORD_PTR a = (DWORD_PTR)luaL_checkinteger(L, 1);
    DWORD_PTR b = (DWORD_PTR)luaL_checkinteger(L, 2);
    int ret = MAKELONG(a, b);
    lua_pushinteger(L, ret);
    return 1;
}

static int plw_window_MAKELPARAM(lua_State*L){
    DWORD_PTR a = (DWORD_PTR)luaL_checkinteger(L, 1);
    DWORD_PTR b = (DWORD_PTR)luaL_checkinteger(L, 2);
    LPARAM ret = MAKELPARAM(a, b);
    lua_pushinteger(L, ret);
    return 1;
}


static int plw_window_MAKELRESULT(lua_State*L){
    DWORD_PTR a = (DWORD_PTR)luaL_checkinteger(L, 1);
    DWORD_PTR b = (DWORD_PTR)luaL_checkinteger(L, 2);
    LRESULT ret = MAKELRESULT(a, b);
    lua_pushinteger(L, ret);
    return 1;
}

static int plw_window_MAKEWORD(lua_State*L){
    DWORD_PTR a = (DWORD_PTR)luaL_checkinteger(L, 1);
    DWORD_PTR b = (DWORD_PTR)luaL_checkinteger(L, 2);
    WORD ret = MAKEWORD(a, b);
    lua_pushinteger(L, ret);
    return 1;
}

static int plw_window_MAKEWPARAM(lua_State*L){
    DWORD_PTR a = (DWORD_PTR)luaL_checkinteger(L, 1);
    DWORD_PTR b = (DWORD_PTR)luaL_checkinteger(L, 2);
    WPARAM ret = MAKEWPARAM(a, b);
    lua_pushinteger(L, ret);
    return 1;
}

///////////////////////////////////////////////////////////////////////////////
////
static int plw_window_HWND(lua_State* L){
    plw_HWND_t * hwnd;
    PLW_CHECK_HWND(L, 1, hwnd);
    return 1;
}

///////////////////////////////////////////////////////////////////////////////
//// metatable
static int plw_hwnd_tostring(lua_State* L){
    plw_HWND_t * hwnd;
    PLW_CHECK_HWND(L, 1, hwnd);
    if(hwnd!=NULL) {
        lua_pushfstring(L, "hwnd(%p)", hwnd->hwnd);
    }else{
        lua_pushstring(L, "nil");
    }
    return 1;
}

static int plw_hwnd_gc(lua_State* L){
    plw_HWND_t * hwnd;
    PLW_CHECK_HWND(L, 1, hwnd);
    if(hwnd!=NULL && hwnd->hwnd!=NULL) {
        int ret = GetProp(hwnd->hwnd, "plw_Sendasyncproc");
        if(ret>0){
            luaL_unref(L, LUA_REGISTRYINDEX, ret);
        }
    }
    return 0;
}

static const struct luaL_Reg plw_hwnd_m[] = {
        {"__tostring", plw_hwnd_tostring},
        {"__gc", plw_hwnd_gc},
        {NULL, NULL}
};


///////////////////////////////////////////////////////////////////////////////
////

#define X(f) {#f, plw_window_##f}
static const struct luaL_Reg plw_window_libf[] = {
        X(HWND),
        X(FindWindow),
        X(GetWindowText),
        X(GetWindowTextLength),
        X(CreateWindow),
        X(ShowWindow),
        X(UpdateWindow),
        X(GET_X_LPARAM),
        X(GET_Y_LPARAM),
        X(HIBYTE),
        X(HIWORD),
        X(LOBYTE),
        X(LOWORD),
        X(MAKELONG),
        X(MAKELPARAM),
        X(MAKELRESULT),
        X(MAKEWORD),
        X(MAKEWPARAM),
        {NULL, NULL}
};
#undef X

static void plw_window_openlib(lua_State* L){
    luaL_setfuncs(L, plw_window_libf, 0);
}

#endif //INCLUDED_PWL_WINDOWS_H
