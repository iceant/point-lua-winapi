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
        lua_pushlightuserdata(L, hwnd);
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
        lua_pushlightuserdata(L, hwnd);
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
    HWND hwnd = NULL;
    if(!lua_isnil(L, 1)){
        hwnd = lua_touserdata(L, 1);
        luaL_argcheck(L, hwnd!=NULL, 1, "invalid HWND");
    }
    int nMaxCount = 256;
    if(top>1){
        luaL_checkany(L, 2);
        int nMaxCount = luaL_checkinteger(L, 2);
        luaL_argcheck(L, nMaxCount>0, 2, "length<0");
    }
    char * lpString = malloc(nMaxCount);
    memset(lpString, 0, nMaxCount);
    int ret = GetWindowText(hwnd, lpString, nMaxCount);
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
    HWND hwnd = NULL;
    if(!lua_isnil(L, 1)){
        hwnd = lua_touserdata(L, 1);
        luaL_argcheck(L, hwnd!=NULL, 1, "invalid HWND");
    }
    int ret = GetWindowTextLength(hwnd);
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
    if(hwnd==NULL){
        lua_pushnil(L);
    }else{
        SetProp(hwnd, PLW_WINDOW_PROP_LUA_STATE, L);
        lua_pushlightuserdata(L, hwnd);
    }
    return 1;
}

static int plw_window_ShowWindow(lua_State* L){
    int top = lua_gettop(L);
    HWND hwnd = NULL;
    if(!lua_isnil(L, 1)){
        hwnd = lua_touserdata(L, 1);
        luaL_argcheck(L, hwnd!=NULL, 1, "invalid HWND");
    }
    int nCmdShow = SW_NORMAL;
    if(top>1){
        luaL_checkany(L, 2);
        nCmdShow = luaL_checkinteger(L, 2);
    }
    BOOL ret = ShowWindow(hwnd, nCmdShow);
    lua_pushboolean(L, ret);
    return 1;
}

static int plw_window_UpdateWindow(lua_State* L){
    HWND hwnd = NULL;
    if(!lua_isnil(L, 1)){
        hwnd = lua_touserdata(L, 1);
        luaL_argcheck(L, hwnd!=NULL, 1, "invalid HWND");
    }

    BOOL ret = UpdateWindow(hwnd);
    lua_pushboolean(L, ret);
    return 1;
}


///////////////////////////////////////////////////////////////////////////////
//// extra
static int plw_window_MessageLoop(lua_State* L){
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}


///////////////////////////////////////////////////////////////////////////////
////
#define X(f) {#f, plw_window_##f}
static const struct luaL_Reg plw_window_libf[] = {
        X(FindWindow),
        X(GetWindowText),
        X(GetWindowTextLength),
        X(CreateWindow),
        X(ShowWindow),
        X(UpdateWindow),
        X(MessageLoop),
        {NULL, NULL}
};
#undef X

static void plw_window_openlib(lua_State* L){
    luaL_setfuncs(L, plw_window_libf, 0);
}

#endif //INCLUDED_PWL_WINDOWS_H
