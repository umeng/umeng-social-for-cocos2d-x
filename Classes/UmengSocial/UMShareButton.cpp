//
//  UMShareButton.cpp
//  crossdemo
//
//  Created by mrsimple on 3/18/14.
//
//

#include "UMShareButton.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


//
UMShareButton::UMShareButton()
{
    socialSDK =  CCUMSocialSDK::create();
    // 平台初始化
    mPlatforms = new vector<int>();
    mPlatforms->push_back(SINA) ;
    mPlatforms->push_back(QZONE) ;
    mPlatforms->push_back(RENREN) ;
    mPlatforms->push_back(DOUBAN) ;
    mPlatforms->push_back(SMS);

    CCLog("构造函数");
    
}

//
UMShareButton::~UMShareButton()
{
    
}


/** creates a menu item with a normal and selected image*/
UMShareButton* UMShareButton::create(const char *normalImage, const char *selectedImage, CCObject* target)
{
    UMShareButton *pRet = new UMShareButton();
    if (pRet && pRet->initWithNormalImage(normalImage, selectedImage, "", target, menu_selector(UMShareButton::shareCallback)) )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

// 设置友盟app key
void UMShareButton::setUmengAppkey(const char* appkey)
{
    mAppKey = appkey ;
    socialSDK->setAppKey(appkey) ;
    CCLog("设置app key : %s .", appkey);
}

// 设置文本内容
void UMShareButton::setShareContent(const char* text)
{
    mShareText = text ;
    CCLog("UMShareButton::setShareContent 设置文字内容 : %s .", mShareText);
}

// 可以设置本地图片和url图片, url图片必须以http://开头
void UMShareButton::setShareImage(const char* imgName)
{
    mImageName = imgName ;
    CCLog("设置图片地址 : %s .", mImageName);
}

// 设置回调
void UMShareButton::setShareCallback(ShareEventHandler callback)
{
    mCallback = callback ;
}


//
void UMShareButton::shareCallback(CCNode* pSender)
{

      CCLog("========== UMShareButton::shareCallback      ============ ");
//      mAppKey = "507fcab25270157b37000010";
//      mShareText = "fucking cocos2dx";
//      mImageName = "/sdcard/header.jpeg";
      // CCLog("@@@@@@   appkey = %s.    text = %s, imageName = %s.", mAppKey, mShareText, mImageName);

      // for (int i = 0; i < mPlatforms->size(); ++i)
      // {
      //     CCLog("平台 : %d.", mPlatforms->front());
      // }

      if ( mPlatforms == NULL ) {

   // 平台初始化
    mPlatforms = new vector<int>();
    mPlatforms->push_back(SINA) ;
    mPlatforms->push_back(QZONE) ;
    mPlatforms->push_back(RENREN) ;
    mPlatforms->push_back(DOUBAN) ;
    mPlatforms->push_back(SMS);
      }

      if ( socialSDK == NULL ) {
        socialSDK = CCUMSocialSDK::create() ;
        CCLog("========== socialSDK == NULL. ");
      }
       // controller初始化
    if ( socialSDK != NULL && mPlatforms != NULL) {
        CCLog("========== UMShareButton::shareCallback");
        socialSDK->setAppKey(mAppKey);
        socialSDK->openShare(mPlatforms, mShareText, mImageName, NULL) ;
    }
}