#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/dlib/android.h>

#include "def_country_getter.h"

namespace dmCountryGetter {

struct CountryGetter
{
    jobject         m_CountryGetterJNI;
    jmethodID       m_GetCountry;
};

static CountryGetter g_CountryGetter;

static void InitJNIMethods(JNIEnv* env, jclass cls)
{
    g_CountryGetter.m_GetCountry = env->GetMethodID(cls, "GetCountry", "()Ljava/lang/String;");//https://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/types.html
}

void Initialize_Ext()
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    jclass cls = dmAndroid::LoadClass(env, "com.defold.hgpoint.CountryGetterJNI");
    InitJNIMethods(env, cls);
    jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");
    g_CountryGetter.m_CountryGetterJNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, threadAttacher.GetActivity()->clazz));
}

const char* GetCountry()
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    jstring s = (jstring)  env->CallObjectMethod
         (g_CountryGetter.m_CountryGetterJNI, g_CountryGetter.m_GetCountry);
 
    const char *str = env->GetStringUTFChars(s, 0);
    
    env->DeleteLocalRef(s);
    
    return str;  
 }

} // namespace

#endif // platform
