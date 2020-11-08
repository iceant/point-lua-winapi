#ifndef INCLUDED_LUA_BIND_H
#define INCLUDED_LUA_BIND_H

#ifndef INCLUDED_LUA_H
#define INCLUDED_LUA_H
#include <lua.h>
#endif // INCLUDED_LUA_H

#ifndef INCLUDED_LUALIB_H
#define INCLUDED_LUALIB_H
#include <lualib.h>
#endif // INCLUDED_LUALIB_H

#ifndef INCLUDED_LAUXLIB_H
#define INCLUDED_LAUXLIB_H
#include <lauxlib.h>
#endif // INCLUDED_LAUXLIB_H

///////////////////////////////////////////////////////////////////////////////
//// functions
void lua_bind_stackdump(lua_State* L, const char* func, const int line);


///////////////////////////////////////////////////////////////////////////////
//// macros
#define LUA_BIND_OBJ_INT(L, obj, op,  field) \
    (lua_pushinteger(L, ##obj##op##field), lua_setfield(L, -2, #field))

#define LUA_BIND_OBJ_UD(L, obj, op,  field) \
    (lua_pushlightuserdata(L, ##obj##op##field), lua_setfield(L, -2, #field))

#define LUA_BIND_OBJ_STR(L, obj, op,  field) \
    (lua_pushstring(L, ##obj##op##field), lua_setfield(L, -2, #field))

#define LUA_BIND_2OBJ_INT(L, idx, obj, op, field)       \
    do{                                                 \
        lua_getfield(L, (idx), #field);                 \
        if(!lua_isnil(L, -1)){                          \
            ##obj##op##field=luaL_checkinteger(L, -1);  \
        }                                               \
        lua_pop(L, 1);                                  \
    }while(0)

#define LUA_BIND_2OBJ_PTR(L, idx, obj, op, field)                   \
    do{                                                             \
        lua_getfield(L, (idx), #field);                             \
        switch(lua_type(L, -1)){                                    \
            case LUA_TNUMBER:                                       \
                ##obj##op##field=(void*)luaL_checkinteger(L, -1);   \
                break;                                              \
            case LUA_TSTRING:                                       \
                ##obj##op##field=(void*)luaL_checkstring(L, -1);    \
                break;                                              \
            case LUA_TUSERDATA:                                     \
            case LUA_TLIGHTUSERDATA:                                \
                ##obj##op##field=(void*)lua_touserdata(L, -1);      \
                break;                                              \
            default:                                                \
                ##obj##op##field=NULL;                              \
        }                                                           \
        lua_pop(L, 1);                                              \
    }while(0)

#define LUA_BIND_2OBJ_UD(L, idx, obj, op, field) \
    do{                                                 \
        lua_getfield(L, (idx), #field);                 \
        if(!lua_isnil(L, -1)){                          \
            ##obj##op##field=lua_touserdata(L, -1);     \
        }                                               \
        lua_pop(L, 1);                                  \
    }while(0)

#define LUA_BIND_2OBJ_STR(L, idx, obj, op, field)       \
    do{                                                 \
        lua_getfield(L, (idx), #field);                 \
        if(!lua_isnil(L, -1)){                          \
            ##obj##op##field=luaL_checkstring(L, -1);   \
        }                                               \
        lua_pop(L, 1);                                  \
    }while(0)


#define LUA_BIND_STACKDUMP(L) lua_bind_stackdump(L, __FILE__, __LINE__)

#endif //INCLUDED_LUA_BIND_H
