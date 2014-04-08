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


            void setTargetUrl(const char* targetUrl);
            
            
        };
    }

}

#endif
