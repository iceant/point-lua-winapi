#ifndef INCLUDED_PLW_WINDOW_MESSAGE_H
#define INCLUDED_PLW_WINDOW_MESSAGE_H

#ifndef INCLUDED_PLW_DETAIL_H
#include "./plw_detail.h"
#endif //INCLUDED_PLW_DETAIL_H

///////////////////////////////////////////////////////////////////////////////
////
static int plw_PostQuitMessage(lua_State* L){
    int code = luaL_checkinteger(L, 1);
    PostQuitMessage(code);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////
////
#define X(f) {#f, plw_##f}
static const struct luaL_Reg plw_window_message_libf[] = {
        X(PostQuitMessage),
        {NULL, NULL}
};
#undef X

static void plw_window_message_openlib(lua_State* L){
    luaL_setfuncs(L, plw_window_message_libf, 0);
}

#endif //INCLUDED_PLW_WINDOW_MESSAGE_H
