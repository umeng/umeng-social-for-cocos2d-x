
/*
 * FileName : CCUMScoialSDK.cpp
 * Author   : hehonghui
 * Company  : umeng.com
 * Android 平台实现的代码参考UmengSocial/Android目录下的实现, IOS平台的参考UmengSocial/IOS目录下的实现。
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
// 使用友盟命令空间 
USING_NS_UM_SOCIAL;

CCUMSocialSDK* CCUMSocialSDK::_instance = NULL;


CCUMSocialSDK::CCUMSocialSDK()
{

}


/*
 * 创建CCUMSocialSDK对象, 单例模式
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
 * @param appKey 友盟app key
 */
void CCUMSocialSDK::setAppKey(const char* appkey)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    if ( appkey == NULL ) {
        CCLog("CCUMSocialSDK::setAppKey, key == null");
    }
    // 授权某平台
    setUmengAppkey(appkey);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    UmSocialControllerIOS::setAppKey(appkey);
    
#endif
}


/*
 * 对某平台进行授权
 * @param platfrom 要授权的平台, 参考CCUMTypeDef.h中的Platform枚举定义
 * @param  callback 授权回调, 具体参考CCUMTypeDef.h中的定义
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


/*
 * 删除某平台的授权信息
 * @param platform 要删除授权的平台
 * @param   callback 删除授权的回调, 具体参考CCUMTypeDef.h中的定义
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


/*
 * 判断某平台是否已经授权
 * @param platform 要判定的平台, 参考CCUMTypeDef.h中的Platform枚举定义
 */
bool CCUMSocialSDK::isAuthorized(int platform)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    return isPlatformAuthorized(platform);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    return UmSocialControllerIOS::isAuthorized(platform) ;
    
#endif
}



/*
 * 打开分享面板
 * @param platforms 显示在分享面板上的所有平台,平台的定义参考CCUMTypeDef.h中的Platform枚举
 * @param text 要分享的文字内容
 * @param imgName 要分享的图片的本地路径或者url, 如果是url必须则必须以http://或者https://开头
 * @param callback 分享回调,具体参考CCUMTypeDef.h中的定义
 */
void CCUMSocialSDK::openShare(vector<int>* platforms, const char* text, const char* imgName, ShareEventHandler callback)
{

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    // 设置分享内容
    setShareTextContent(text);
    // 设置图片内容
    setShareImageName(imgName);
    // 设置平台
    setSocialPlatforms(platforms);
    // 打开分享面板
    doOpenShare(callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    UmSocialControllerIOS::openShareWithImagePath(platforms, text, imgName, callback);
#endif
}


 /*
 * 直接分享到某个平台，不打开分享面板和内容编辑页面
 * @param platform 要分享到的目标平台， 参考CCUMTypeDef.h中的Platform枚举定义
 * @param text 要分享的文字内容
 * @param imgName 要分享的图片的本地路径或者url, 如果是url必须则必须以http://开头
 * @param callback 分享回调，具体参考CCUMTypeDef.h中的定义
 */
void CCUMSocialSDK::directShare(int platform,const char* text, const char* imgName, ShareEventHandler callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    setShareTextContent(text);
    setShareImageName(imgName);
    doDirectShare(platform, callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    UmSocialControllerIOS::directShare(text, imgName, platform, callback) ;
    //TODO: iOS
    
#endif
}


/*
* 设置SDK的target url, 即用户点击某条分享时跳转到的目标页面
* @param url 用户点击某条分享时跳转到的目标页面通常为app的主页或者下载链接等
*/
void CCUMSocialSDK::setTargetUrl(const char* targetUrl)
{
    #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    setShareTargetUrl(targetUrl);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
 
    //TODO: iOS
    
#endif
}

