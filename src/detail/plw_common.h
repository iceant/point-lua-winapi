#ifndef INCLUDED_PLW_COMMON_H
#define INCLUDED_PLW_COMMON_H

#ifndef INCLUDED_PLW_DETAIL_H
#include "./plw_detail.h"
#endif //INCLUDED_PLW_DETAIL_H

#ifndef INCLUDED_STRSAFE_H
#define INCLUDED_STRSAFE_H
#include <strsafe.h>
#endif // INCLUDED_STRSAFE_H


///////////////////////////////////////////////////////////////////////////////
//// functions
static int plw_common_ISNULL(lua_State* L){
    luaL_checkany(L, 1);
    if(lua_isnil(L, 1)){
        lua_pushboolean(L, 1);
        return 1;
    }
    int type = lua_type(L, 1);
    if(type==LUA_TUSERDATA || type==LUA_TLIGHTUSERDATA){
        void* p = lua_touserdata(L, 1);
        lua_pushboolean(L, p==NULL);
        return 1;
    }
    lua_pushboolean(L, 0);
    return 1;
}

///////////////////////////////////////////////////////////////////////////////
//// register

#define X(f) {#f, plw_common_##f}
static const struct luaL_Reg plw_common_libf[] = {
        X(ISNULL),
        {NULL, NULL}
};
#undef X

static void plw_common_openlib(lua_State* L){
    luaL_setfuncs(L, plw_common_libf, 0);
}

#endif //INCLUDED_PLW_COMMON_H
