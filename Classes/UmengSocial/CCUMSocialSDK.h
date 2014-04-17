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

namespace umeng
{
    namespace social 
    {
        /**
         *  Umeng Social SDK Native Controller.
         */
        class CCUMSocialSDK
        {
        private:
            CCUMSocialSDK();
            void initSDK();
        public:
            
            static CCUMSocialSDK* create() ;

            /*
             * 设置友盟app key
             * @param appKey 友盟app key
             */
            void setAppKey(const char* appkey);
            
            /*
             * 对某平台进行授权
             * @param   platform 要授权的平台
             *
             */
            void authorize(int platform, AuthEventHandler callback);
            /*
             * 删除某平台的授权信息
             *@param    platform 要删除授权的平台
             */
            void deleteAuthorization(int platform, AuthEventHandler callback);
            
            /*
             * 判断某平台是否已经授权
             *@param    platform 判断某平台是否已经授权
             */
            bool isAuthorized(int platform);
            
            /*
             * 打开分享面板
             *@param    callback 注册回调
             */
            void openShare(vector<int>* platforms,const char* text, const char* imgName, ShareEventHandler callback);
            
            /*
             * 直接分享, 底层分享
             *@param    platform 要分享到的目标平台
             */
            void directShare(int platform, const char* text, const char* imgName, ShareEventHandler callback);

            /*
             * 设置SDK的target url, 即用户点击某条分享时跳转到的目标页面
             * @param url 用户点击某条分享时跳转到的目标页面通常为app的主页或者下载链接等
             */
            void setTargetUrl(const char* targetUrl);

            /**
             * 设置QQ和QQ空间的app id
             * 
             * @param appid
             */
            void setQQAppIdAndAppKey(const char* appid, const char* appkey) ;

            /**
             * 设置微信和微信朋友圈的app id
             * 
             * @param appid
             */
            void setWeiXinAppId(const char* appid);

            /**
             * 设置易信和易信朋友圈的app id
             * 
             * @param appid
             */
            void setYiXinAppKey(const char* appid) ;

            /**
             * 设置来往和来往动态的app id, app key, appName
             * 
             * @param appid   应用的app id
             * @param appKey  应用的app key
             * @param appName 应用吗
             */
            void setLaiwangAppInfo(const char* appid, const char* appkey, const char* appName);
            
            /**
             * 设置Facebook的appid
             *
             * @param appid   Facebook应用的app id
             */
            void setFacebookAppId(const char *appid);
            
            /**
             * 打开Twitter开关，只对iOS平台生效
             *
             */
            void openTwitterForiOS();
            
            /**
             * 打开Instagram开关，只对iOS平台生效
             *
             */
            void openInstagramForiOS();

        private:
            static CCUMSocialSDK *_instance ;
            char* _wrapperType;
            char* _wrapperVersion; 
            
        };
    }

}

#endif
