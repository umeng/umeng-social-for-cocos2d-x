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


// 
void UMShareButton::shareCallback(CCNode* pSender)
{
    CCUMSocialSDK* mShareSDK = CCUMSocialSDK::create() ;
    mShareSDK->setAppKey("507fcab25270157b37000010") ;
    mShareSDK->openShare("share button", "", NULL) ;
    CCLog("这就是回调了.");
}