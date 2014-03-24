//
//  UMShareButton.h
//  crossdemo
//
//  Created by mrsimple on 3/18/14.
//
//

#ifndef __crossdemo__UMShareButton__
#define __crossdemo__UMShareButton__

#include <iostream>
#include "cocos2d.h"
#include "CCUMSocialSDK.h"

USING_NS_CC;
using namespace std;

class UMShareButton : public cocos2d::CCMenuItemImage
{
public:
    
    UMShareButton(){}
   virtual  ~UMShareButton(){}
    
    /** creates a menu item with a normal and selected image*/
    static UMShareButton* create(const char *normalImage, const char *selectedImage, CCObject* target);
    
private:
    void shareCallback(CCNode* pSender);
    
};

#endif /* defined(__crossdemo__UMShareButton__) */
