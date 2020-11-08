#ifndef INCLUDED_PLW_SYSTEM_SERVICES_H
#define INCLUDED_PLW_SYSTEM_SERVICES_H

#ifndef INCLUDED_PLW_DETAIL_H
#include "./plw_detail.h"
#endif //INCLUDED_PLW_DETAIL_H

///////////////////////////////////////////////////////////////////////////////
//// functions
static int plw_GetModuleHandle(lua_State* L){
    int top = lua_gettop(L);
    HMODULE hModule;
    if(top==0 || lua_isnil(L, 1)){
        hModule = GetModuleHandle(NULL);
    }else{
        luaL_checkany(L, 1);
        LPCSTR lpModuleName = luaL_checkstring(L, 1);
        hModule = GetModuleHandle(lpModuleName);
    }
    if(hModule==NULL){
        lua_pushnil(L);
    }else{
        lua_pushlightuserdata(L, hModule);
    }
    return 1;

}

///////////////////////////////////////////////////////////////////////////////
////
#define X(f) {#f, plw_##f}
static const struct luaL_Reg plw_system_service_libf[] = {
        X(GetModuleHandle),
        {NULL, NULL}
};
#undef X

static void plw_system_service_openlib(lua_State* L){
    luaL_setfuncs(L, plw_system_service_libf, 0);
}
#endif //INCLUDED_PLW_SYSTEM_SERVICES_H
