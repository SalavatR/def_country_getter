#define EXTENSION_NAME CountryGetterExt
#define LIB_NAME "CountryGetter"
#define MODULE_NAME "def_country_getter"

#define DLIB_LOG_DOMAIN LIB_NAME

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID)

#include <stdlib.h>
#include "def_country_getter.h"

namespace dmCountryGetter
{

    static int Lua_GetCountry(lua_State *L)
    {
        DM_LUA_STACK_CHECK(L, 1);
        lua_pushstring(L, GetCountry());
        return 1;
    }

    static const luaL_reg Module_methods[] =
        {
            {"get_country", Lua_GetCountry},
            {0, 0}};

    static void LuaInit(lua_State *L)
    {
        DM_LUA_STACK_CHECK(L, 0);
        luaL_register(L, MODULE_NAME, Module_methods);
        lua_pop(L, 1);
    }

    static dmExtension::Result AppInitializeCountryGetter(dmExtension::AppParams *params)
    {
        Initialize_Ext();
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result InitializeCountryGetter(dmExtension::Params *params)
    {
        LuaInit(params->m_L);
        dmLogInfo("Registered extension CountryGetter");
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result UpdateCountryGetter(dmExtension::Params *params)
    {
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result AppFinalizeCountryGetter(dmExtension::AppParams *params)
    {
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result FinalizeCountryGetter(dmExtension::Params *params)
    {
        return dmExtension::RESULT_OK;
    }

} // namespace

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, dmCountryGetter::AppInitializeCountryGetter, dmCountryGetter::AppFinalizeCountryGetter, dmCountryGetter::InitializeCountryGetter, dmCountryGetter::UpdateCountryGetter, 0, dmCountryGetter::FinalizeCountryGetter)

#else // platform

static dmExtension::Result InitializeCountryGetter(dmExtension::Params *params)
{
    dmLogInfo("Registered extension CountryGetter (null)");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeCountryGetter(dmExtension::Params *params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeCountryGetter, 0, 0, FinalizeCountryGetter)

#endif // platform