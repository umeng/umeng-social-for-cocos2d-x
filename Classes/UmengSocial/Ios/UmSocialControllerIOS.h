//
//  UmSocialControllerIOS.h
//  UmengGame
//
//  Created by 张梓琦 on 14-3-16.
//
//

#ifndef __UmengGame__UmSocialControllerIOS__
#define __UmengGame__UmSocialControllerIOS__

#include "CCUMTypeDef.h"
#include <string>
#include <vector>

#define CC_ShareToWechat       1
#define CC_ShareToQQOrQzone    1
#define CC_ShareToLaiWang      1
#define CC_ShareToYiXin        1
#define CC_ShareToFacebook     1
#define CC_ShareToTwitter      1
#define CC_ShareToInstagram    1

using namespace std;
using namespace umeng::social;

class UmSocialControllerIOS {
public:
    static void setAppKey(const char* appKey);
    static void initCocos2dxSDK(const char *sdkType, const char *version);

    static void setTargetUrl(const char * targetUrl);
    
    static void authorize(int platform, AuthEventHandler callback);
    static void deleteAuthorization(int platform,AuthEventHandler callback);
    static bool isAuthorized(int platform);
    static void openShareWithImagePath(vector<int>* platform, const char* text, const char* imagePath,ShareEventHandler callback);
    static void directShare(const char* text, const char* imagePath, int platform, ShareEventHandler callback);
    
#ifdef CC_ShareToQQOrQzone
    //设置QQ互联appid，appkey
    static void setQQAppIdAndAppKey(const char *appId,const char *appKey);
#endif
    
#ifdef CC_ShareToWechat
    //设置微信appid
    static void setWechatAppId(const char *appId);
#endif
    
#ifdef CC_ShareToLaiWang
    //设置来往appid，appkey
    static void setLaiwangAppInfo(const char *appId, const char *appKey, const char * appName);
#endif
    
#ifdef CC_ShareToYiXin
    //设置易信appid
    static void setYiXinAppKey(const char *appKey);
#endif
    
#ifdef CC_ShareToFacebook
    //设置Facebook的appid
    static void setFacebookAppId(const char *appId);
#endif
    
#ifdef CC_ShareToTwitter
    //打开Twitter的开关
    static void openTwitter();
#endif
    
#ifdef CC_ShareToInstagram
    //打开Instagram的开关
    static void openInstagram();
#endif
    
private:
    static string m_appKey;
};

#endif /* defined(__UmengGame__UmSocialControllerIOS__) */
