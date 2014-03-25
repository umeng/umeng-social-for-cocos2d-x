/*
 * FileName : CCUMScoialSDK.h
 * Author   : hehonghui
 * Company  : umeng.com
 *
 */

#ifndef __CCUMSOCIALSDK__
#define __CCUMSOCIALSDK__
 
#include "cocos2d.h"
#include "CCUMTypeDef.h"
#include <vector>

USING_NS_CC;
using namespace std;

/**
 *	Umeng Social SDK Native Controller.
 */
class CCUMSocialSDK
{
    
private:
    static CCUMSocialSDK *_instance ;
    
private:
    CCUMSocialSDK();
public:
    
    static CCUMSocialSDK* create() ;

    void setAppKey(const char* appkey);
    
    /*
     * 对某平台进行授权
     * @param 	platform 要授权的平台
     *
     */
    void authorize(int platform, AuthEventHandler callback);
    /*
     * 删除某平台的授权信息
     *@param 	platform 要删除授权的平台
     */
    void deleteAuthorization(int platform, AuthEventHandler callback);
    
    /*
     * 判断某平台是否已经授权
     *@param 	platform 判断某平台是否已经授权
     */
    bool isAuthorized(int platform);
    
    /*
     * 打开分享面板
     */
    // void openShare();
    /*
     * 打开分享面板
     *@param 	callback 注册回调
     */
    void openShare(const char* text, const char* imgName, ShareEventHandler callback);
    
    /*
     * 直接分享, 底层分享
     *@param 	platform 要分享到的目标平台
     */
    void directShare(int platform, const char* text, const char* imgName, ShareEventHandler callback);
    
    
    // /*
    //  * 添加平台支持
    //  *@param 	platform 要添加的平台
    //  *@param 	appkey   相关平台的app key
    //  *@param 	targetUrl 用户点击某个分享时跳转到的目标页面
    //  */
    // void supportPlatform(int platform, const char* appkey, const char* targetUrl);
    
    
    //  * 设置平台顺序呢
    //  * @param 	platformOrders 平台显示在分享面板上的顺序
     
    // void setPlatformsOrder(int platformOrders[]);
    // /*
    //  * 移除某些平台
    //  *@param 	platforms 要移除的平台
    //  */
    // void removePlatforms(int platforms[]);
    // /*
    //  * 清空sdk
    //  */
    // void cleanup();
    
};


#endif
