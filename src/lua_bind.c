#include <lua_bind.h>
#include <stdio.h>
#include <assert.h>

void lua_bind_stackdump(lua_State* L, const char* func, const int line){
    int top = lua_gettop(L);
    printf("(%s,%d) top=%d\n", func, line, top);
    for (int i = 0; i < top; i++) {
        int positive = top - i;
        int negative = -(i + 1);
        int type = lua_type(L, positive);
        int typeN = lua_type(L, negative);
        assert(type == typeN);
        const char* typeName = lua_typename(L, type);
        printf("%d/%d: type=%s", positive, negative, typeName);
        switch (type) {
            case LUA_TNUMBER:
                printf(" value=%f", lua_tonumber(L, positive));
                break;
            case LUA_TSTRING:
                printf(" value=%s", lua_tostring(L, positive));
                break;
            case LUA_TFUNCTION:
                if (lua_iscfunction(L, positive)) {
                    printf(" C:%p", lua_tocfunction(L, positive));
                }
                break;
        }
        printf("\n");
    }
}