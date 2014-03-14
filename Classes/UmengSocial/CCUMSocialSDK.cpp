
/*
 * FileName : CCUMScoialSDK.cpp
 * Author   : hehonghui
 * Company  : umeng.com
 *
 */

#include "CCUMSocialSDK.h"
 
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

// #include "CCUMSocialControllerIOS.h"

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "Android/CCUMSocialController.h"

#endif

USING_NS_CC;

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
    
    //TODO: iOS
    
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
    
    //TODO: iOS
    
#endif
}



/**
 *设置要分享的图片的本地路径
 *	@param 	text 要设置的分享文字内容
 */
void CCUMSocialSDK::setShareContent(const char* text)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    setShareTextContent(text);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}


/**
 *设置要分享的图片的本地路径
 *	@param 	path 要设置的图片的本地路径
 */
void CCUMSocialSDK::setShareImagePath(const char* path)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    setShareImageFilePath(path);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

/**
 * 设置要分享的图片的url
 *  @param 	url 要设置的图片的url
 */
void CCUMSocialSDK::setShareImageUrl(const char* url)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    setShareImagesUrl(url);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
    
}


/**
 * 打开分享面板, 不注册分享回调
 */
void CCUMSocialSDK::openShare()
{
    #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    // 打开分享面板
    doOpenShare(false, NULL);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

/**
 * 打开分享面板, 并且注册分享回调
 *@param 	callback 分享回调
 */
void CCUMSocialSDK::openShare(ShareEventHandler callback)
{

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    // 打开分享面板
    doOpenShare(true, callback);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

/**
 * 直接分享, 底层分享
 *@param 	platform 要分享到的目标平台
 */
void CCUMSocialSDK::directShare(int platform, ShareEventHandler callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    doDirectShare(platform, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

/**
 * 添加平台支持
 *@param 	platform 要添加的平台
 *@param 	appkey   相关平台的app key
 *@param 	targetUrl 用户点击某个分享时跳转到的目标页面
 */
void CCUMSocialSDK::supportPlatform(int platform, const char* appkey, const char* targetUrl)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    doSupportPlatform(platform, appkey, targetUrl);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS

    
#endif
}

/**
 * 设置平台顺序呢
 * @param 	platformOrders 平台显示在分享面板上的顺序
 */
void CCUMSocialSDK::setPlatformsOrder(int platformOrders[])
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
//    setPlatformsOrder(platformOrders);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}


/**
 * 移除某些平台
 *@param 	platforms 要移除的平台
 */
void CCUMSocialSDK::removePlatforms(int platforms[])
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

//    removePlatforms(platforms);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

/**
 * 清空sdk
 */
void CCUMSocialSDK::cleanup()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    cleanupSDK();
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}
