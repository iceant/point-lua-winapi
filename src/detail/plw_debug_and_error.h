#ifndef INCLUDED_PLW_DEBUG_AND_ERROR_H
#define INCLUDED_PLW_DEBUG_AND_ERROR_H

#ifndef INCLUDED_PLW_DETAIL_H
#include "./plw_detail.h"
#endif //INCLUDED_PLW_DETAIL_H

#ifndef INCLUDED_STRSAFE_H
#define INCLUDED_STRSAFE_H
#include <strsafe.h>
#endif // INCLUDED_STRSAFE_H

///////////////////////////////////////////////////////////////////////////////
////
static int plw_dbgerr_GetLastError(lua_State* L){
    DWORD dw = GetLastError();
    lua_pushinteger(L, dw);
    return 1;
}

static int plw_dbgerr_GetLastErrorMsg(lua_State* L){

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    LPCSTR lpszFunction = luaL_checkstring(L, 1);

    FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpMsgBuf,
            0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
                                      (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
                    LocalSize(lpDisplayBuf) / sizeof(TCHAR),
                    TEXT("%s failed with error %d: %s"),
                    lpszFunction, dw, lpMsgBuf);

    lua_pushstring(L, (LPCTSTR)lpDisplayBuf);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);

    return 1;
}

///////////////////////////////////////////////////////////////////////////////
////
#define X(f) {#f, plw_dbgerr_##f}
static const struct luaL_Reg plw_dbgerr_libf[] = {
        X(GetLastError),
        X(GetLastErrorMsg),
        {NULL, NULL}
};
#undef X

static void plw_dbgerr_openlib(lua_State* L){
    luaL_setfuncs(L, plw_dbgerr_libf, 0);
}

#endif //INCLUDED_PLW_DEBUG_AND_ERROR_H
