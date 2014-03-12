
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

// CCUMScoialSDK* CCUMScoialSDK::_instance = NULL;
// /*
//  *
//  */
// CCUMScoialSDK* CCUMScoialSDK::create()
// {
//     // if ( CCUMScoialSDK::_instance == NULL ) {
//     //     _instance = new CCUMScoialSDK();
//     // }
 
//     CCUMScoialSDK* _instance = new CCUMScoialSDK();
    
//     return _instance;
// }

/**
 * 对某平台进行授权
 * *@param 	platform 目标平台
 */
void CCUMSocialSDK::doAuthorize(const char* platform)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    // 授权某平台
    doAuthorize( platform );
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

/**
 * 删除某平台的授权
 * *@param 	platform 目标平台
 *
 */
void CCUMSocialSDK::deleteAuthorization(const char* platform)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    deleteAuthorization(platform);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

/**
 * 判断某平台是否授权
 * *@param 	platform 目标平台
 */
bool CCUMSocialSDK::isAuthorized(const char* platform)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    return isAuthorized(platform);
    
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

    setShareContent(text);
    
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
    
    setShareImagePath(path);
    
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
    
    setShareImageUrl(url);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
    
}


/**
 * 打开分享面板
 *@param 	registerListener 是否注册分享监听器     (考虑使用函数指针)
 */
void CCUMSocialSDK::openShare(bool registerListener)
{

     CCLog("      ------FUCK------- CCUMSocialSDK::openShare");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

      CCLog("      ------android------- CCUMSocialSDK::openShare");
    // 打开分享面板
    openShare(registerListener);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

/**
 * 直接分享, 底层分享
 *@param 	platform 要分享到的目标平台
 */
void CCUMSocialSDK::directShare(const char* platform)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    directShare(platform);
    
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
void CCUMSocialSDK::supportPlatform(const char* platform, const char* appkey, const char* targetUrl)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    supportPlatform(platform, appkey, targetUrl);
    
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
    
    cleanup();
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}
