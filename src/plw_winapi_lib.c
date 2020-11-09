#include <plw_winapi_lib.h>
#include <lua_bind.h>
#include <detail/plw_common.h>
#include <detail/plw_debug_and_error.h>
#include <detail/plw_windows.h>
#include <detail/plw_window_class.h>
#include <detail/plw_window_message.h>
#include <detail/plw_system_services.h>
#include <detail/plw_resources.h>


///////////////////////////////////////////////////////////////////////////////
////
static const struct luaL_Reg winapilib_f[] = {
        {NULL, NULL}
};

///////////////////////////////////////////////////////////////////////////////
//// assembly
LUALIB_API int luaopen_winapi(lua_State* L){
    s_tlsL = L;

    luaL_newmetatable(L, PLW_TMSG);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    luaL_newmetatable(L, PLW_THWND);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, plw_hwnd_m, 0);

    luaL_newlib(L, winapilib_f);
    plw_common_openlib(L);
    plw_dbgerr_openlib(L);
    plw_window_openlib(L);
    plw_window_class_openlib(L);
    plw_system_service_openlib(L);
    plw_window_message_openlib(L);
    plw_resource_openlib(L);
    return 1;
}