
/*
 * FileName : CCUMScoialSDK.cpp
 * Author   : hehonghui
 * Company  : umeng.com
 *
 */

#include "CCUMSocialSDK.h"
#include <vector>
 
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "UmSocialControllerIOS.h"

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "Android/CCUMSocialController.h"

#endif

USING_NS_CC;
using namespace std;

CCUMSocialSDK* CCUMSocialSDK::_instance = NULL;


CCUMSocialSDK::CCUMSocialSDK()
{

}


/*
 *
 */
CCUMSocialSDK* CCUMSocialSDK::create()
{

    if ( _instance == NULL ) 
    {
        _instance = new CCUMSocialSDK();
    }
    return _instance;
}

/*
 * 设置友盟app key
 *
 */
void CCUMSocialSDK::setAppKey(const char* appkey)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    // 授权某平台
    setUmengAppkey(appkey);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    UmSocialControllerIOS::setAppKey(appkey);
    
#endif
}

/**
 * 对某平台进行授权
 * *@param 	platform 目标平台
 */
void CCUMSocialSDK::authorize(int platform, AuthEventHandler callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    // 授权某平台
    doAuthorize(platform, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    UmSocialControllerIOS::authorize(platform, callback);
    
#endif
}

/**
 * 删除某平台的授权
 * *@param 	platform 目标平台
 *
 */
void CCUMSocialSDK::deleteAuthorization(int platform, AuthEventHandler callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    deletePlatformAuthorization(platform, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    UmSocialControllerIOS::deleteAuthorization(platform, callback) ;
    //TODO: iOS
    
#endif
}

/**
 * 判断某平台是否授权
 * *@param 	platform 目标平台
 */
bool CCUMSocialSDK::isAuthorized(int platform)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    return isPlatformAuthorized(platform);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    return UmSocialControllerIOS::isAuthorized(platform) ;
    
#endif
}



/**
 * 打开分享面板, 并且注册分享回调
 *@param 	callback 分享回调
 */
void CCUMSocialSDK::openShare(const char* text, const char* imgName, ShareEventHandler callback)
{

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    // 打开分享面板
    doOpenShare(true, callback);
    setShareTextContent(text);
    setShareImageFilePath(imgName);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    vector<int> platforms ;
    platforms.push_back(SINA);
    platforms.push_back(QZONE);
    platforms.push_back(RENREN);
    platforms.push_back(DOUBAN);
    platforms.push_back(FACEBOOK);
    UmSocialControllerIOS::openShareWithImagePath(&platforms, text, imgName, callback);
#endif
}

/**
 * 直接分享, 底层分享
 *@param 	platform 要分享到的目标平台
 */
void CCUMSocialSDK::directShare(int platform,const char* text, const char* imgName, ShareEventHandler callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    doDirectShare(platform, callback);
    setShareTextContent(text);
    setShareImageFilePath(imgName);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    UmSocialControllerIOS::directShare(text, imgName, platform, callback) ;
    //TODO: iOS
    
#endif
}

