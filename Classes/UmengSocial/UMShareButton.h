//
//  UMShareButton.h
//  UMShareButton, 封装了CCUMSocialSDK的分享功能 ( 通过分享面板分享 ). 没有使用Cocos2d-x的内存管理策略，开发者自行管理该Button的内存释放.
//
//  Created by mrsimple on 3/18/14.
//
//

#ifndef __crossdemo__UMShareButton__
#define __crossdemo__UMShareButton__

#include <iostream>
#include "cocos2d.h"
#include "CCUMSocialSDK.h"
#include <vector>

USING_NS_CC;
using namespace std;


namespace umeng
{
    namespace social 
    {
        #ifdef CC_CALLBACK_1
            class UMShareButton : public cocos2d::MenuItemImage 
            {
        #else
            class UMShareButton : public cocos2d::CCMenuItemImage 
            {
        #endif
        public:
            virtual  ~UMShareButton() ;

            // 参数1为正常情况下的图片, 参数2为用户点击后的图片, 参数3为友盟app key, 参数四为分享回调.
            static UMShareButton* create(const char *normalImage, const char *selectedImage, const char* umAppKey, ShareEventHandler callback);
            
            // 设置文本内容
            void setShareContent(const char* text);
            // 可以设置本地图片和url图片, url图片必须以http://开头
            void setShareImage(const char* imgName);
            // 设置分享回调
            void setShareCallback(ShareEventHandler callback);
            // 设置分享面板上的平台
            void setPlatforms(vector<int>* platforms);
            // 获取CCUMSocialSDK对象
            CCUMSocialSDK* getSocialSDK();

        private:
            UMShareButton();
            // 构造函数
            UMShareButton(const char *normalImage, const char *selectedImage, const char* umAppKey);
            // 打开分享面板
            void openShareBoard();
        #ifdef CC_CALLBACK_1
            // 分享按钮回调, 打开友盟分享面板
            void shareCallback(cocos2d::Ref* pSender);
        #else 
             // 分享按钮回调, 打开友盟分享面板
            void shareCallback(CCNode* pSender);
        #endif
           
        private:
            // 友盟分享组件SDK
            CCUMSocialSDK* mSocialSDK;
            // 要添加支持的平台
            vector<int>* mPlatforms;
            // 要分享的文本内容
            string mShareText;
            // 要分享的图片本地路径或者url
            string mImageName;
            // 分享回调
            ShareEventHandler mCallback ;
        };
    }
}

#endif /* defined(__crossdemo__UMShareButton__) */
