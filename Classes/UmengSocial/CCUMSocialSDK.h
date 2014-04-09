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
            static CCUMSocialSDK *_instance ;
            
        private:
            CCUMSocialSDK();
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
             * 设置QQ的app id
             * 
             * @param appid
             */
            void setQQAppId(const char* appid) ;

            /**
             * 设置QQ空间的app id
             * 
             * @param appid
             */
            void setQZoneAppId(const char* appid);

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
             * 设置来往和来往动态的app id
             * 
             * @param appid
             */
            void setLaiwangAppId(const char* appid);

            /**
             * 设置来往和来往动态的app key
             * 
             * @param appid
             */
            void setLaiwangAppKey(const char* appkey);
            
            
        };
    }

}

#endif
