/*
 * FileName : CCUMScoialSDK.h
 * Author   : hehonghui
 * Company  : umeng.com
 *
 */

#ifndef __CCUMSOCIALSDK__
#define __CCUMSOCIALSDK__
 
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

/**
 *	Umeng Social SDK Native Controller.
 */
class CCUMSocialSDK
{
    
// private:
//     static CCUMSocialSDK* _instance ;
    
// private:
//     CCUMSocialSDK(){}
public:
    
    // static CCUMSocialSDK* create() ;
    /*
     * 设置要分享的文字内容
     *	@param 	text 要设置的分享内容
     *
     */
    void setShareContent(const char* text);
    /*
     *设置要分享的图片的本地路径
     *	@param 	path 要设置的图片的本地路径
     *
     */
    void setShareImagePath(const char* path);
    /*
     * 设置要分享的图片的url
     *  @param 	url 要设置的图片的url
     */
    void setShareImageUrl(const char* url);
    
    /*
     * 对某平台进行授权
     * @param 	platform 要授权的平台
     *
     */
    void doAuthorize(const char* platform);
    /*
     * 删除某平台的授权信息
     *@param 	platform 要删除授权的平台
     */
    void deleteAuthorization(const char* platform);
    
    /*
     * 判断某平台是否已经授权
     *@param 	platform 判断某平台是否已经授权
     */
    bool isAuthorized(const char* platform);
    
    /*
     * 打开分享面板
     *@param 	registerListener 是否注册分享监听器     (考虑使用模板类, 函数指针)
     */
    void openShare(bool registerListener);
    
    /*
     * 直接分享, 底层分享
     *@param 	platform 要分享到的目标平台
     */
    void directShare(const char* platform);
    
    
    /*
     * 添加平台支持
     *@param 	platform 要添加的平台
     *@param 	appkey   相关平台的app key
     *@param 	targetUrl 用户点击某个分享时跳转到的目标页面
     */
    void supportPlatform(const char* platform, const char* appkey, const char* targetUrl);
    
    /*
     * 设置平台顺序呢
     * @param 	platformOrders 平台显示在分享面板上的顺序
     */
    void setPlatformsOrder(int platformOrders[]);
    /*
     * 移除某些平台
     *@param 	platforms 要移除的平台
     */
    void removePlatforms(int platforms[]);
    /*
     * 清空sdk
     */
    void cleanup();
    
};


#endif
