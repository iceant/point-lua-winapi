#ifndef INCLUDED_PLW_WINDOW_MESSAGE_H
#define INCLUDED_PLW_WINDOW_MESSAGE_H

#ifndef INCLUDED_PLW_DETAIL_H
#include "./plw_detail.h"
#endif //INCLUDED_PLW_DETAIL_H

///////////////////////////////////////////////////////////////////////////////
//// extra functions
static int plw_MessageLoop(lua_State* L){
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

static int plw_MSG_new(lua_State* L){
    LPMSG lpMsg = lua_newuserdata(L, sizeof(*lpMsg));
    memset(lpMsg, 0, sizeof(*lpMsg));
    luaL_getmetatable(L, PLW_TMSG);
    lua_setmetatable(L, -2);
    return 1;
}

///////////////////////////////////////////////////////////////////////////////
//// macros



///////////////////////////////////////////////////////////////////////////////
////
// BroadcastSystemMessage(BSF_IGNORECURRENTTASK, BSM_APPLICATIONS, PM_MYMSG, 0, 0)
static int plw_BroadcastSystemMessage(lua_State* L){
    DWORD dwFlags;
    DWORD dwInfo;
    UINT msg;
    WPARAM wParam;
    LPARAM lParam;

    dwFlags=luaL_checkinteger(L, 1);
    dwInfo = luaL_checkinteger(L, 2);
    msg = luaL_checkinteger(L, 3);
    LUA_BIND_CHK_PTR(L, 4, wParam);
    LUA_BIND_CHK_PTR(L, 5, lParam);

    long ret = BroadcastSystemMessage(dwFlags, &dwInfo, msg, wParam, lParam);
    lua_pushinteger(L, ret);
    return 1;
}

static int plw_BroadcastSystemMessageEx(lua_State* L){
    DWORD dwFlags;
    DWORD dwInfo;
    UINT msg;
    WPARAM wParam;
    LPARAM lParam;
    BSMINFO bsmInfo;

    memset(&bsmInfo, 0, sizeof(bsmInfo));

    dwFlags=luaL_checkinteger(L, 1);
    dwInfo = luaL_checkinteger(L, 2);
    msg = luaL_checkinteger(L, 3);
    LUA_BIND_CHK_PTR(L, 4, wParam);
    LUA_BIND_CHK_PTR(L, 5, lParam);

    long ret = BroadcastSystemMessageEx(dwFlags, &dwInfo, msg, wParam, lParam, &bsmInfo);
    lua_pushinteger(L, ret);

    lua_newtable(L);
    LUA_BIND_OBJ_INT(L, bsmInfo, ., cbSize);
    LUA_BIND_OBJ_UD(L, bsmInfo, ., hdesk);
    LUA_BIND_OBJ_UD(L, bsmInfo, ., hwnd);

    lua_newtable(L);
    LUA_BIND_OBJ_INT(L, bsmInfo.luid, ., LowPart);
    LUA_BIND_OBJ_INT(L, bsmInfo.luid, ., HighPart);

    lua_pushliteral(L, "luid");
    lua_rotate(L, -2, 1);
    lua_settable(L, -3);

    return 2;
}

// local msg = winapi.MSG_new();
// winapi.GetMessage(msg, NULL, 0, 0)
// winapi.TranslateMessage(msg)
// winapi.DispatchMessage(msg)
//
// local msg2 = winapi.MSG_new();
// msg2:Get(NULL, 0, 0)
// msg2:Translate()
// msg2:Dispatch()

static int plw_GetMessage(lua_State* L){
    LPMSG lpMsg;
    HWND hwnd;
    UINT wMsgFilterMin;
    UINT wMsgFilterMax;

    lpMsg = PLW_CHECK_MSG(L, 1);
    LUA_BIND_CHK_PTR(L, 2, hwnd);
    wMsgFilterMin = (UINT)luaL_checkinteger(L, 3);
    wMsgFilterMax = (UINT)luaL_checkinteger(L, 4);

    BOOL ret = GetMessage(lpMsg, hwnd, wMsgFilterMin, wMsgFilterMax);
    lua_pushboolean(L, ret);
    return 1;
}

static int plw_DispatchMessage(lua_State* L){
    LPMSG lpMsg;
    lpMsg = PLW_CHECK_MSG(L, 1);
    LRESULT ret = DispatchMessage(lpMsg);
    lua_pushinteger(L, ret);
    return 1;
}

static int plw_TranslateMessage(lua_State* L){
    LPMSG lpMsg;
    lpMsg = PLW_CHECK_MSG(L, 1);
    BOOL ret = TranslateMessage(lpMsg);
    lua_pushboolean(L, ret);
    return 1;
}

static int plw_GetMessageExtraInfo(lua_State* L){
    LPARAM lParam = GetMessageExtraInfo();
    lua_pushinteger(L, lParam);
    return 1;
}

static int plw_GetMessagePos(lua_State* L){
    DWORD dwPos = GetMessagePos();
    lua_pushinteger(L, dwPos);
    return 1;
}

static int plw_GetMessageTime(lua_State* L){
    LONG lMsgTime = GetMessageTime();
    lua_pushinteger(L, lMsgTime);
    return 1;
}

static int plw_GetQueueStatus(lua_State* L){
    UINT flags = (UINT)luaL_checkinteger(L, 1);
    DWORD dwRet = GetQueueStatus(flags);
    lua_pushinteger(L, dwRet);
    return 1;
}

static int plw_InSendMessage(lua_State* L){
    BOOL ret = InSendMessage();
    lua_pushboolean(L, ret);
    return 1;
}

static int plw_InSendMessageEx(lua_State* L){
    int top = lua_gettop(L);
    LPVOID lReserved = NULL;
    if(top>0){
        LUA_BIND_CHK_PTR(L, 1, lReserved);
    }
    DWORD ret = InSendMessageEx(lReserved);
    lua_pushinteger(L,ret);
    return 1;
}

static int plw_PeekMessage(lua_State* L){
    LPMSG lpMsg = PLW_CHECK_MSG(L, 1);
    plw_HWND_t * hwnd = NULL;
    PLW_CHECK_HWND(L, 2, hwnd);
    UINT wMsgFilterMin = luaL_checkinteger(L, 3);
    UINT wMsgFilterMax = luaL_checkinteger(L, 4);
    UINT wRemoveMsg = luaL_checkinteger(L, 5);

    BOOL ret = PeekMessage(lpMsg, hwnd->hwnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
    lua_pushboolean(L, ret);
    return 1;
}

static int plw_PostMessage(lua_State* L){
    plw_HWND_t * hwnd = NULL;
    PLW_CHECK_HWND(L, 1, hwnd);
    UINT msg = luaL_checkinteger(L, 2);
    WPARAM wParam = (WPARAM)luaL_checkinteger(L, 3);
    LPARAM lParam = (LPARAM)luaL_checkinteger(L, 4);

    BOOL ret = PostMessage(hwnd->hwnd, msg, wParam, lParam);
    lua_pushboolean(L, ret);
    return 1;
}

static int plw_PostQuitMessage(lua_State* L){
    int code = luaL_checkinteger(L, 1);
    PostQuitMessage(code);
    return 0;
}

static int plw_PostThreadMessage(lua_State* L){
    DWORD idThread = (DWORD)luaL_checkinteger(L, 1);
    UINT msg = (UINT)luaL_checkinteger(L, 2);
    WPARAM wParam = (WPARAM)luaL_checkinteger(L, 3);
    LPARAM lParam = (LPARAM)luaL_checkinteger(L, 4);

    BOOL ret = PostThreadMessage(idThread, msg, wParam, lParam);
    lua_pushboolean(L, ret);
    return 1;
}

static int plw_GetInputState(lua_State* L){
    BOOL ret = GetInputState();
    lua_pushboolean(L, ret);
    return 1;
}

static int plw_RegisterWindowMessage(lua_State* L){
    LPCSTR lpString = luaL_checkstring(L, 1);
    UINT ret = RegisterWindowMessage(lpString);
    lua_pushinteger(L, ret);
    return 1;
}

static int plw_ReplyMessage(lua_State* L){
    LRESULT lResult = (LRESULT)luaL_checkinteger(L, 1);
    BOOL ret = ReplyMessage(lResult);
    lua_pushboolean(L, ret);
    return 1;
}

static int plw_SendMessage(lua_State* L){
    plw_HWND_t * hwnd = NULL;
    PLW_CHECK_HWND(L, 1, hwnd);
    UINT msg = luaL_checkinteger(L, 2);
    WPARAM wParam = (WPARAM)luaL_checkinteger(L, 3);
    LPARAM lParam = (LPARAM)luaL_checkinteger(L, 3);
    LRESULT ret = SendMessage(hwnd->hwnd, msg, wParam, lParam);
    lua_pushinteger(L, ret);
    return 1;
}

static void plw_window_message_Sendasyncproc(HWND hwnd, UINT msg, ULONG_PTR arg3, LRESULT lResult){
    lua_State* L = (lua_State*)GetProp(hwnd, "plw_lua_State");
    int top = lua_gettop(L);
    int ref = GetProp(hwnd, "plw_Sendasyncproc");
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    luaL_checktype(L, -1, LUA_TFUNCTION);
    PLW_PUSH_THWND(L, hwnd);
    lua_pushinteger(L, msg);
    lua_pushinteger(L, arg3);
    lua_pushinteger(L, lResult);

    if(lua_pcall(L, 4, 0, 0)!=0){
        printf("error:%s\n", luaL_checkstring(L, -1));
    }

//    luaL_unref(L, LUA_REGISTRYINDEX, ref); //TODO: unref when destroy Window
    lua_settop(L, top);
}

static int plw_SendMessageCallback(lua_State* L){
    plw_HWND_t * hwnd = NULL;
    PLW_CHECK_HWND(L, 1, hwnd);
    UINT msg = luaL_checkinteger(L, 2);
    WPARAM wParam = (WPARAM)luaL_checkinteger(L, 3);
    LPARAM lParam = (LPARAM)luaL_checkinteger(L, 4);
    ULONG_PTR dwData = (ULONG_PTR)luaL_checkinteger(L, 6);

    luaL_checktype(L, 5, LUA_TFUNCTION);
    lua_pushvalue(L, 5);
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    SetProp(hwnd->hwnd, "plw_Sendasyncproc", ref);
    SetProp(hwnd->hwnd, "plw_lua_State", L);

    BOOL ret = SendMessageCallback(hwnd->hwnd, msg, wParam, lParam, plw_window_message_Sendasyncproc, dwData);
    lua_pushboolean(L, ret);
    return 1;
}

// local status,dwResult = SendMessageTimeout(hwnd, msg, wParam, lParam, fuFlags, uTimeout)
static int plw_SendMessageTimeout(lua_State* L){
    plw_HWND_t * hwnd = NULL;
    PLW_CHECK_HWND(L, 1, hwnd);
    UINT msg = luaL_checkinteger(L, 2);
    WPARAM wParam = (WPARAM)luaL_checkinteger(L, 3);
    LPARAM lParam = (LPARAM)luaL_checkinteger(L, 4);
    UINT fuFlags = luaL_checkinteger(L, 5);
    UINT uTimeout = luaL_checkinteger(L, 6);
    DWORD dwResult;
    LRESULT result = SendMessageTimeout(hwnd->hwnd, msg, wParam, lParam, fuFlags, uTimeout, &dwResult);
    lua_pushboolean(L, result!=0);
    lua_pushinteger(L, dwResult);
    return 2;
}

// local status = SendNotifyMessage（hwnd, msg, wPram, lParam)
static int plw_SendNotifyMessage(lua_State* L){
    plw_HWND_t * hwnd = NULL;
    PLW_CHECK_HWND(L, 1, hwnd);
    UINT msg = luaL_checkinteger(L, 2);
    WPARAM wParam = (WPARAM)luaL_checkinteger(L, 3);
    LPARAM lParam = (LPARAM)luaL_checkinteger(L, 4);
    BOOL ret = SendNotifyMessage(hwnd, msg, wParam, lParam);
    lua_pushboolean(L, ret);
    return 1;
}

// local newLParam = SetMessageExtraInfo(lParam)
static int plw_SetMessageExtraInfo(lua_State* L){
    LPARAM lParam = luaL_checkinteger(L, 1);
    LPARAM ret = SetMessageExtraInfo(lParam);
    lua_pushinteger(L, ret);
    return 1;
}


// local status = WaitMessage()
static int plw_WaitMessage(lua_State* L){
    BOOL ret = WaitMessage();
    lua_pushboolean(L, ret);
    return 1;
}


///////////////////////////////////////////////////////////////////////////////
////
#define X(f) {#f, plw_##f}
static const struct luaL_Reg plw_window_message_libf[] = {
        X(MSG_new),
        X(MessageLoop),
        X(BroadcastSystemMessage),
        X(BroadcastSystemMessageEx),
        X(DispatchMessage),
        X(GetInputState),
        X(GetMessage),
        X(GetMessageExtraInfo),
        X(GetMessagePos),
        X(GetMessageTime),
        X(GetQueueStatus),
        X(InSendMessage),
        X(InSendMessageEx),
        X(PeekMessage),
        X(PostMessage),
        X(PostQuitMessage),
        X(PostThreadMessage),
        X(RegisterWindowMessage),
        X(ReplyMessage),
        X(SendMessage),
        X(SendMessageCallback),
        X(SendMessageTimeout),
        X(SendNotifyMessage),
        X(SetMessageExtraInfo),
        X(TranslateMessage),
        X(WaitMessage),
        {NULL, NULL}
};
#undef X

static void plw_window_message_openlib(lua_State* L){
    luaL_setfuncs(L, plw_window_message_libf, 0);
}

#endif //INCLUDED_PLW_WINDOW_MESSAGE_H
