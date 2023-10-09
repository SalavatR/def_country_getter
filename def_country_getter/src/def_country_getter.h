#if defined(DM_PLATFORM_ANDROID)

#pragma once

#include <dmsdk/sdk.h>

namespace dmCountryGetter
{

    void Initialize_Ext();
    const char* GetCountry();

} // namespace

#endif // platform