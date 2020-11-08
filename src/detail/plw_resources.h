#ifndef INCLUDED_PLW_RESOURCES_H
#define INCLUDED_PLW_RESOURCES_H

#ifndef INCLUDED_PLW_DETAIL_H
#include "./plw_detail.h"
#endif //INCLUDED_PLW_DETAIL_H

///////////////////////////////////////////////////////////////////////////////
//// functions

// LoadIcon(nil, iconName)
// LoadIcon(iconName)
// LoadIcon(IDC_APPLICATION) -- int
static int plw_LoadIcon(lua_State* L){
    HINSTANCE hInstance;
    void* lpIconName;
    int top = lua_gettop(L);
    if(top==1){
        luaL_checkany(L, 1);
        hInstance = NULL;
        switch(lua_type(L, 1)){
            case LUA_TNUMBER:
                lpIconName = (void*)luaL_checkinteger(L, 1);
                break;
            case LUA_TSTRING:
                lpIconName = (char*)luaL_checkstring(L, 1);
                break;
            default:
                lpIconName = NULL;
        }
    }else if(top>1){
        switch(lua_type(L, 1)){
            case LUA_TLIGHTUSERDATA:
            case LUA_TUSERDATA:
                hInstance = lua_touserdata(L, 1);
                break;
            default:
                hInstance = NULL;
        }
        luaL_checkany(L, 2);
        switch(lua_type(L, 2)){
            case LUA_TNUMBER:
                lpIconName = (void*)luaL_checkinteger(L, 2);
                break;
            case LUA_TSTRING:
                lpIconName = (char*)luaL_checkstring(L, 2);
                break;
            default:
                lpIconName = NULL;
        }
    }
    HICON hIcon = LoadIcon(hInstance, lpIconName);
    if(hIcon==NULL){
        lua_pushnil(L);
    }else{
        lua_pushlightuserdata(L, hIcon);
    }
    return 1;
}


// LoadCursor(nil, iconName)
// LoadCursor(iconName)
// LoadCursor(IDC_ARROW) -- int
static int plw_LoadCursor(lua_State* L){
    HINSTANCE hInstance;
    void* lpName;
    int top = lua_gettop(L);
    if(top==1){
        luaL_checkany(L, 1);
        hInstance = NULL;
        switch(lua_type(L, 1)){
            case LUA_TNUMBER:
                lpName = (void*)luaL_checkinteger(L, 1);
                break;
            case LUA_TSTRING:
                lpName = (char*)luaL_checkstring(L, 1);
                break;
            default:
                lpName = NULL;
        }
    }else if(top>1){
        switch(lua_type(L, 1)){
            case LUA_TLIGHTUSERDATA:
            case LUA_TUSERDATA:
                hInstance = lua_touserdata(L, 1);
                break;
            default:
                hInstance = NULL;
        }
        luaL_checkany(L, 2);
        switch(lua_type(L, 2)){
            case LUA_TNUMBER:
                lpName = (void*)luaL_checkinteger(L, 2);
                break;
            case LUA_TSTRING:
                lpName = (char*)luaL_checkstring(L, 2);
                break;
            default:
                lpName = NULL;
        }
    }
    HCURSOR hCursor = LoadCursor(hInstance, lpName);
    if(hCursor==NULL){
        lua_pushnil(L);
    }else{
        lua_pushlightuserdata(L, hCursor);
    }
    return 1;
}

///////////////////////////////////////////////////////////////////////////////
////
#define X(f) {#f, plw_##f}
static const struct luaL_Reg plw_resource_libf[] = {
        X(LoadIcon),
        X(LoadCursor),
        {NULL, NULL}
};
#undef X

static void plw_resource_openlib(lua_State* L){
    luaL_setfuncs(L, plw_resource_libf, 0);
}

#endif //INCLUDED_PLW_RESOURCES_H
