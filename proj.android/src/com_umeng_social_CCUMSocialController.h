/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_umeng_social_CCUMSocialController */

#ifndef _Included_com_umeng_social_CCUMSocialController
#define _Included_com_umeng_social_CCUMSocialController
#ifdef __cplusplus
extern "C" {
#endif
#undef com_umeng_social_CCUMSocialController_DELAY_MS
#define com_umeng_social_CCUMSocialController_DELAY_MS 100L
/*
 * Class:     com_umeng_social_CCUMSocialController
 * Method:    OnAuthorizeStart
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_umeng_social_CCUMSocialController_OnAuthorizeStart
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_umeng_social_CCUMSocialController
 * Method:    OnAuthorizeComplete
 * Signature: (II[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_umeng_social_CCUMSocialController_OnAuthorizeComplete
  (JNIEnv *, jclass, jint, jint, jobjectArray);

/*
 * Class:     com_umeng_social_CCUMSocialController
 * Method:    OnShareStart
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_umeng_social_CCUMSocialController_OnShareStart
  (JNIEnv *, jclass);

/*
 * Class:     com_umeng_social_CCUMSocialController
 * Method:    OnShareComplete
 * Signature: (IILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_umeng_social_CCUMSocialController_OnShareComplete
  (JNIEnv *, jclass, jint, jint, jstring);

/*
 * Class:     com_umeng_social_CCUMSocialController
 * Method:    getCocos2dxScrShot
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_umeng_social_CCUMSocialController_getCocos2dxScrShot
  (JNIEnv *, jclass);

/*
 * Class:     com_umeng_social_CCUMSocialController
 * Method:    onShakeComplete
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_umeng_social_CCUMSocialController_onShakeComplete
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
