#include "com_umeng_game_UmengGame.h"
#include <android/log.h>
#include <string.h>
#include <stdio.h>
#include "UMLog.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "cocos2d.h"

USING_NS_CC;


// share onStart
JNIEXPORT void JNICALL Java_com_umeng_game_UmengGame_onNativeStart
  (JNIEnv *env, jclass obj)
  {
  	printf("%s\n", "Share onStart");
    //__android_log_print(ANDROID_LOG_DEBUG, "JNIMsg", " ##### FUCK -- > onStart ");
    UMLog::D("Cocos2d-x Hackathon", " ##### FUCK -- > onStart ");
  }




// share onComplate
  // @param
  JNIEXPORT void JNICALL Java_com_umeng_game_UmengGame_onNativeComplete
  (JNIEnv *env, jclass obj, jstring platform, jint ecode, jstring descriptor)
  {
	   printf("%s\n", "Share onComplate");
     UMLog::D("Cocos2d-x Hackathon", " ##### FUCK -- > onComplate ");
    //__android_log_print(ANDROID_LOG_DEBUG, "JNIMsg", " ##### FUCK -- > onComplate ");
  }


JNIEXPORT jstring JNICALL Java_com_umeng_game_UmengGame_getCocos2dxScrShot
  (JNIEnv *env, jclass clz) 
  {
  
    static int index = 0 ;
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCLog("Window Size, width = %d, height = %d.", (int)size.width, (int)size.height );
    CCRenderTexture* texture = CCRenderTexture::create((int)size.width, (int)size.height, kCCTexture2DPixelFormat_RGBA8888);    
    texture->setPosition(ccp(size.width/2, size.height/2));    
    texture->begin();
    CCDirector::sharedDirector()->getRunningScene()->visit();
    texture->end();

    string imagePath = CCFileUtils::sharedFileUtils()->getWritablePath() ;
    if ( imagePath.length() == 0 )
    {
      return env->NewStringUTF("");
    }

    imagePath = imagePath.c_str() ;
    UMLog::D("### writable path", imagePath.c_str());
    char imgName[20] ;
    sprintf(imgName, "screenshot-%d.jpg", index++);
    UMLog::D("### Image File Name", imgName);
     //保存为png  
    bool result = texture->saveToFile(imgName, kCCImageFormatJPEG); 
    if ( result ) 
    {
        // imagePath += "screenshot.png";
        imagePath += imgName ;
        UMLog::D("#save scrshot", "#### COCOS2D-X截图成功");
        return env->NewStringUTF(imagePath.c_str());
    } 
    else 
    {
       UMLog::D("### write image failed.", "### write image failed.");
      return env->NewStringUTF("");
    } 

/*
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCRenderTexture* texture = CCRenderTexture::create((int)size.width, (int)size.height);    
    texture->setPosition(ccp(size.width/2, size.height/2));    
    CCScene* curScene = CCDirector::sharedDirector()->getRunningScene() ;

    texture->begin();
    curScene->visit();
    texture->end();

    string imagePath = CCFileUtils::sharedFileUtils()->getWritablePath().c_str();
    imagePath +=  + "screenshot.png" ;
    UMLog::D("### writable path", imagePath.c_str());

    CCImage* pImage = texture->newCCImage();
    imagePath = "/sdcard/cocos2d.png";
    if ( pImage && pImage->saveToFile(imagePath.c_str(), true) ) 
    {

        UMLog::D("#save scrshot", "#### COCOS2D-X截图成功");
        return env->NewStringUTF(imagePath.c_str());
    }
    else 
    {
       UMLog::D("### write image failed.", "### write image failed.");
       return env->NewStringUTF("");
    }

     CC_SAFE_DELETE(pImage);
    CC_SAFE_DELETE(texture);
      */
  } // end of  getCocos2dxScrShot


