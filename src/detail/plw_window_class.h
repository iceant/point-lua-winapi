#ifndef INCLUDED_PWL_WINDOW_CLASS_H
#define INCLUDED_PWL_WINDOW_CLASS_H

#ifndef INCLUDED_PLW_DETAIL_H
#include "./plw_detail.h"
#endif //INCLUDED_PLW_DETAIL_H

///////////////////////////////////////////////////////////////////////////////
//// structure and lua table map

static int plw_push_WNDCLASS(lua_State* L, LPWNDCLASS lpWndClass){
    assert(L);
    assert(lpWndClass);
    lua_newtable(L);
    LUA_BIND_OBJ_INT(L, lpWndClass, ->, style);
    LUA_BIND_OBJ_UD(L, lpWndClass, ->, lpfnWndProc);
    LUA_BIND_OBJ_INT(L, lpWndClass, ->, cbClsExtra);
    LUA_BIND_OBJ_INT(L, lpWndClass, ->, cbWndExtra);
    LUA_BIND_OBJ_UD(L, lpWndClass, ->, hInstance);
    LUA_BIND_OBJ_UD(L, lpWndClass, ->, hIcon);
    LUA_BIND_OBJ_UD(L, lpWndClass, ->, hCursor);
    LUA_BIND_OBJ_UD(L, lpWndClass, ->, hbrBackground);
    LUA_BIND_OBJ_STR(L, lpWndClass, ->, lpszMenuName);
    LUA_BIND_OBJ_STR(L, lpWndClass, ->, lpszClassName);
    return 1;
}

static void plw_check_WNDCLASS(lua_State* L, int nargs, LPWNDCLASS lpWndClass){
    assert(L);
    assert(lpWndClass);

    luaL_checktype(L, nargs, LUA_TTABLE);
    lua_gettable(L, nargs);

    memset(lpWndClass, 0, sizeof(WNDCLASS));

    LUA_BIND_2OBJ_INT(L, nargs, lpWndClass, ->, style);
    LUA_BIND_2OBJ_UD(L, nargs, lpWndClass, ->, lpfnWndProc);
    LUA_BIND_2OBJ_INT(L, nargs, lpWndClass, ->, cbClsExtra);
    LUA_BIND_2OBJ_INT(L, nargs, lpWndClass, ->, cbWndExtra);
    LUA_BIND_2OBJ_UD(L, nargs, lpWndClass, ->, hInstance);
    LUA_BIND_2OBJ_UD(L, nargs, lpWndClass, ->, hIcon);
    LUA_BIND_2OBJ_UD(L, nargs, lpWndClass, ->, hCursor);
    LUA_BIND_2OBJ_UD(L, nargs, lpWndClass, ->, hbrBackground);
    LUA_BIND_2OBJ_STR(L, nargs, lpWndClass, ->, lpszMenuName);
    LUA_BIND_2OBJ_STR(L, nargs, lpWndClass, ->, lpszClassName);

    lua_pop(L, 1);
}


static int plw_push_WNDCLASSEX(lua_State* L, LPWNDCLASSEX lpWndClass){
    assert(L);
    assert(lpWndClass);
    lua_newtable(L);
    LUA_BIND_OBJ_INT(L, lpWndClass, ->, cbSize);
    LUA_BIND_OBJ_INT(L, lpWndClass, ->, style);
    LUA_BIND_OBJ_UD(L, lpWndClass, ->, lpfnWndProc);
    LUA_BIND_OBJ_INT(L, lpWndClass, ->, cbClsExtra);
    LUA_BIND_OBJ_INT(L, lpWndClass, ->, cbWndExtra);
    LUA_BIND_OBJ_UD(L, lpWndClass, ->, hInstance);
    LUA_BIND_OBJ_UD(L, lpWndClass, ->, hIcon);
    LUA_BIND_OBJ_UD(L, lpWndClass, ->, hCursor);
    LUA_BIND_OBJ_UD(L, lpWndClass, ->, hbrBackground);
    LUA_BIND_OBJ_STR(L, lpWndClass, ->, lpszMenuName);
    LUA_BIND_OBJ_STR(L, lpWndClass, ->, lpszClassName);
    LUA_BIND_OBJ_UD(L, lpWndClass, ->, hIconSm);
    return 1;
}

static LPWNDCLASSEX plw_pop_WNDCLASSEX(lua_State* L, int nargs){
    assert(L);
    luaL_checktype(L, nargs, LUA_TTABLE);
    lua_gettable(L, nargs);

    LPWNDCLASSEX lpWndClass = malloc(sizeof(*lpWndClass));
    memset(lpWndClass, 0, sizeof(*lpWndClass));
    assert(lpWndClass);

    LUA_BIND_2OBJ_INT(L, nargs, lpWndClass, ->, cbSize);
    LUA_BIND_2OBJ_INT(L, nargs, lpWndClass, ->, style);
    LUA_BIND_2OBJ_UD(L, nargs, lpWndClass, ->, lpfnWndProc);
    LUA_BIND_2OBJ_INT(L, nargs, lpWndClass, ->, cbClsExtra);
    LUA_BIND_2OBJ_INT(L, nargs, lpWndClass, ->, cbWndExtra);
    LUA_BIND_2OBJ_UD(L, nargs, lpWndClass, ->, hInstance);
    LUA_BIND_2OBJ_UD(L, nargs, lpWndClass, ->, hIcon);
    LUA_BIND_2OBJ_UD(L, nargs, lpWndClass, ->, hCursor);
    LUA_BIND_2OBJ_UD(L, nargs, lpWndClass, ->, hbrBackground);
    LUA_BIND_2OBJ_STR(L, nargs, lpWndClass, ->, lpszMenuName);
    LUA_BIND_2OBJ_STR(L, nargs, lpWndClass, ->, lpszClassName);
    LUA_BIND_2OBJ_UD(L, nargs, lpWndClass, ->, hIconSm);

    return lpWndClass;
}

///////////////////////////////////////////////////////////////////////////////
//// functions

/*BOOL GetClassInfoA(
  HINSTANCE   hInstance,
  LPCSTR      lpClassName,
  LPWNDCLASSA lpWndClass
);*/

//  local wndClass = GetClassInfo(nil, className)
//  local wndClass = GetClassInfo(className)
static int plw_GetClassInfo(lua_State* L){
    int top = lua_gettop(L);
    luaL_checkany(L, 1);
    if(top==2){
        HINSTANCE hInstance = NULL;
        if(!lua_isnil(L, 1)){
            hInstance = lua_touserdata(L, 1);
        }
        LPCSTR lpClassName = luaL_checkstring(L, 2);
        WNDCLASS wndClass;
        memset(&wndClass, 0, sizeof(WNDCLASS));
        BOOL ret = GetClassInfo(hInstance, lpClassName, &wndClass);
        lua_pushboolean(L, ret);
        plw_push_WNDCLASS(L, &wndClass);
        return 2;
    }else if(top==1){
        HINSTANCE hInstance = NULL;
        LPCSTR lpClassName = luaL_checkstring(L, 1);
        WNDCLASS wndClass;
        memset(&wndClass, 0, sizeof(WNDCLASS));
        BOOL ret = GetClassInfo(hInstance, lpClassName, &wndClass);
        lua_pushboolean(L, ret);
        plw_push_WNDCLASS(L, &wndClass);
        return 2;
    }
    return 0;
}

/*
BOOL GetClassInfoExA(
  HINSTANCE     hInstance,
  LPCSTR        lpszClass,
  LPWNDCLASSEXA lpwcx
);
*/

//  local wndClass = GetClassInfoEx(nil, className)
//  local wndClass = GetClassInfoEx(className)
static int plw_GetClassInfoEx(lua_State* L){
    int top = lua_gettop(L);
    luaL_checkany(L, 1);
    if(top==2){
        HINSTANCE hInstance = NULL;
        if(!lua_isnil(L, 1)){
            hInstance = lua_touserdata(L, 1);
        }
        LPCSTR lpClassName = luaL_checkstring(L, 2);
        WNDCLASSEXA wndClass;
        memset(&wndClass, 0, sizeof(WNDCLASSEXA));
        BOOL ret = GetClassInfoEx(hInstance, lpClassName, &wndClass);
        lua_pushboolean(L, ret);
        plw_push_WNDCLASSEX(L, &wndClass);
        return 2;
    }else if(top==1){
        HINSTANCE hInstance = NULL;
        LPCSTR lpClassName = luaL_checkstring(L, 1);
        WNDCLASSEXA wndClass;
        memset(&wndClass, 0, sizeof(WNDCLASSEXA));
        BOOL ret = GetClassInfoEx(hInstance, lpClassName, &wndClass);
        lua_pushboolean(L, ret);
        plw_push_WNDCLASSEX(L, &wndClass);
        return 2;
    }
    return 0;
}

static int plw_GetClassLong(lua_State *L){
    HWND hwnd = NULL;
    if(!lua_isnil(L, 1)){
        hwnd = lua_touserdata(L, 1);
    }
    luaL_checkany(L, 2);
    int nIndex = luaL_checkinteger(L, 2);
    DWORD ret = GetClassLong(hwnd, nIndex);
    lua_pushinteger(L, ret);
    return 1;
}

// GetClassLongPtr(hwnd, GCL_STYLE)
static int plw_GetClassLongPtr(lua_State* L){
    int top = lua_gettop(L);
    HWND hwnd = NULL;
    int nIndex = GCL_STYLE;

    luaL_checkany(L, 1);

    if(!lua_isnil(L, 1)){
        hwnd = lua_touserdata(L, 1);
        luaL_argcheck(L, hwnd!=NULL, 1, "invalid HWND");
    }

    if(top>1){
        luaL_checkany(L, 2);
        nIndex = luaL_checkinteger(L, 2);
    }

    WORD ret = GetClassLongPtr(hwnd, nIndex);
    if(ret==0){
        lua_pushnil(L);
    }else{
        lua_pushinteger(L, ret);
    }
    return 1;
}

/*
 * GetClassName(hwnd, nMaxCount)
 * GetClassName(hwnd)
 * */
static int plw_GetClassName(lua_State* L){
    int top = lua_gettop(L);
    HWND hwnd = NULL;
    int nMaxCount = 256;

    luaL_checkany(L, 1);

    if(!lua_isnil(L, 1)){
        hwnd = lua_touserdata(L, 1);
        luaL_argcheck(L, hwnd!=NULL, 1, "invalid HWND");
    }

    if(top>1){
        luaL_checkany(L, 2);
        nMaxCount = luaL_checkinteger(L, 2);
        luaL_argcheck(L, nMaxCount>0, 2, "length<0");
    }

    char* lpClassName = malloc(nMaxCount);
    memset(lpClassName, 0, nMaxCount);
    int ret = GetClassName(hwnd, lpClassName, nMaxCount);
    if(ret!=0){
        lua_pushlstring(L, lpClassName, ret);
    }else{
        lua_pushnil(L);
    }
    free(lpClassName);
    return 1;
}

// GetClassWord(hwnd)
// GetClassWord(hwnd, GCW_ATOM)
static int plw_GetClassWord(lua_State* L){
    int top = lua_gettop(L);
    HWND hwnd = NULL;
    int nIndex = GCW_ATOM;

    luaL_checkany(L, 1);

    if(!lua_isnil(L, 1)){
        hwnd = lua_touserdata(L, 1);
        luaL_argcheck(L, hwnd!=NULL, 1, "invalid HWND");
    }

    if(top>1){
        luaL_checkany(L, 2);
        nIndex = luaL_checkinteger(L, 2);
    }

    WORD ret = GetClassWord(hwnd, nIndex);
    if(ret==0){
        lua_pushnil(L);
    }else{
        lua_pushinteger(L, ret);
    }
    return 1;
}

static int plw_GetWindowLong(lua_State* L){
    int top = lua_gettop(L);
    HWND hwnd = NULL;
    int nIndex = GCL_STYLE;

    luaL_checkany(L, 1);

    if(!lua_isnil(L, 1)){
        hwnd = lua_touserdata(L, 1);
        luaL_argcheck(L, hwnd!=NULL, 1, "invalid HWND");
    }

    if(top>1){
        luaL_checkany(L, 2);
        nIndex = luaL_checkinteger(L, 2);
    }

    WORD ret = GetWindowLong(hwnd, nIndex);
    if(ret==0){
        lua_pushnil(L);
    }else{
        lua_pushinteger(L, ret);
    }
    return 1;
}

static int plw_GetWindowLongPtr(lua_State* L){
    HWND hwnd = NULL;
    if(!lua_isnil(L, 1)){
        hwnd = lua_touserdata(L, 1);
    }
    luaL_checkany(L, 2);
    int nIndex = luaL_checkinteger(L, 2);
    ULONG_PTR ret = GetWindowLongPtr(hwnd, nIndex);
    lua_pushinteger(L, ret);
    return 1;
}

static LRESULT CALLBACK plw_window_wndproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    lua_State* L = s_tlsL;
    assert(L);
    int top = lua_gettop(L);
    char buf[256];
    int ret = GetClassName(hwnd, buf, 256);

    lua_pushlstring(L, buf, ret);
    lua_gettable(L, LUA_REGISTRYINDEX);

//    lua_pushlightuserdata(L, hwnd);
    PLW_PUSH_THWND(L, hwnd);
    lua_pushinteger(L, message);
    lua_pushinteger(L, wParam);
    lua_pushinteger(L, lParam);
    if(lua_pcall(L, 4, 1, 0)==0){
        if(!lua_isnil(L, -1)){
            if(lua_isboolean(L, -1)){
                int b = lua_toboolean(L, -1);
                lua_pop(L, 1);
                return b?TRUE:FALSE;
            }else if(lua_isnumber(L, -1)){
                lua_pop(L, 1);
                return lua_tointeger(L, -1);
            }
        }
    }
    lua_settop(L, top);

    return DefWindowProc(hwnd, message, wParam, lParam);
}

/*
 RegisterClass({
    style=CS_HREDRAW|CS_VREDRAW,
    lpfnWndProc=function()

    end,
    cbClsExtra=0,
    cbWndExtra=0,
    hInstance=GetModuleHandle(),
    hIcon=nil,
    hCursor=nil,
    hbrBackground=nil,
    lpszMenuName=nil,
    lpszClassName="my-class"
 });
 * */
static int plw_RegisterClass(lua_State* L){
    luaL_checktype(L, 1, LUA_TTABLE);

    WNDCLASS w;
    memset(&w, 0, sizeof(w));

    LUA_BIND_2OBJ_INT(L, 1, w, ., style);
    LUA_BIND_2OBJ_INT(L, 1, w, ., cbClsExtra);
    LUA_BIND_2OBJ_INT(L, 1, w, ., cbWndExtra);
    LUA_BIND_2OBJ_PTR(L, 1, w, ., hInstance);
    LUA_BIND_2OBJ_PTR(L, 1, w, ., hIcon);
    LUA_BIND_2OBJ_PTR(L, 1, w, ., hCursor);
    LUA_BIND_2OBJ_PTR(L, 1, w, ., hbrBackground);
    LUA_BIND_2OBJ_STR(L, 1, w, ., lpszMenuName);
    LUA_BIND_2OBJ_STR(L, 1, w, ., lpszClassName);

    w.lpfnWndProc = plw_window_wndproc;

//    printf("WNDCLASS:{\n"
//           "\tstyle:%d\n"
//           "\tcbClsExtra:%d\n"
//           "\tcbWndExtra:%d\n"
//           "\thInstance:%p\n"
//           "\thIcon:%p\n"
//           "\thCursor:%p\n"
//           "\thBrBackground:%p\n"
//           "\tlpszMenuName:%s\n"
//           "\tlpszClassName:%s\n"
//           "}", w.style, w.cbClsExtra, w.cbWndExtra, w.hInstance, w.hIcon, w.hCursor, w.hbrBackground, w.lpszMenuName==NULL?"":w.lpszMenuName, w.lpszClassName==NULL?"":w.lpszClassName);

    ATOM atom = RegisterClass(&w);
    if(atom==0){
        lua_pushnil(L);
    }else{
        lua_getfield(L, 1, "lpszClassName"); /*key=lpszClassName*/
        lua_getfield(L, 1, "lpfnWndProc");
        luaL_checktype(L, -1, LUA_TFUNCTION);
        lua_settable(L, LUA_REGISTRYINDEX); /*registry[key]=lpfnWndProc*/
        lua_pushinteger(L, atom);
    }
    return 1;
}



///////////////////////////////////////////////////////////////////////////////
////
#define X(f) {#f, plw_##f}
static const struct luaL_Reg plw_window_class_libf[] = {
    X(GetClassInfo),
    X(GetClassInfoEx),
    X(GetClassLong),
    X(GetWindowLongPtr),
    X(GetClassName),
    X(GetClassWord),
    X(GetWindowLong),
    X(GetClassLongPtr),
    X(RegisterClass),
    {NULL, NULL}
};
#undef X

static void plw_window_class_openlib(lua_State* L){
    luaL_setfuncs(L, plw_window_class_libf, 0);
}

#endif //INCLUDED_PWL_WINDOW_CLASS_H
