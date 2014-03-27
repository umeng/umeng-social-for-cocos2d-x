#include "HelloWorldScene.h"
#include <string>
#include "UmengSocial/CCUMTypeDef.h"
#include "UmengSocial/CCUMSocialSDK.h"
#include "UmengSocial/UMShareButton.h"
#include <iostream>
#include <vector>
#include <map>
 
// #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
// #include "UmengSocial/Android/CCUMSocialController.h"
// #endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "UmengSocial/IOS/UmSocialControllerIOS.h"

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "UmengSocial/Android/CCUMSocialController.h"

#endif

// 环境变量PATH在windows下和linux下的分割符定义
#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif



USING_NS_CC;
using namespace std;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


/*
 *授权回调
 * @param platform 要授权的平台
 * @param stCode 返回码, 200代表授权成功, 100代表开始授权, 0代表授权出错, -1代表取消授权
 * @param data 授权时返回的数据
 */
void authCallback(int platform, int stCode, map<string, string>& data)
{
    if ( stCode == 100 ) 
    {
        CCLog("#### 授权开始");
    }
    else if ( stCode == 200 ) 
    {
        CCLog("#### 授权完成");
    } else if ( stCode == 0 ) 
    {
        CCLog("#### 授权出错");
    } else if ( stCode == -1 ) 
    {
        CCLog("#### 取消授权");
    }
 
    // 输入授权数据, 如果授权失败,则会输出错误信息
    map<string,string>::iterator it = data.begin();
    for (; it != data.end(); ++it) {
        CCLog("#### data  %s -> %s." , it->first.c_str(), it->second.c_str());
    }
}

/*
 * 分享回调
* @param platform 要分享到的目标平台
 * @param stCode 返回码, 200代表分享成功, 100代表开始分享
 * @param errorMsg 分享失败时的错误信息,android平台没有错误信息
 */
void shareCallback(int platform, int stCode, string& errorMsg)
{
    if ( stCode == 100 ) 
    {
        CCLog("#### HelloWorld 开始分享");
    }
    else if ( stCode == 200 ) 
    {
        CCLog("#### HelloWorld 分享成功");
    }
    else 
    {
        CCLog("#### HelloWorld 分享出错");
    }

    CCLog("platform num is : %d.", platform);
}



// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    
    // 分享按钮
     CCMenuItemImage *pShareItem = CCMenuItemImage::create(
                                                           "share.png",
                                                           "share.png",
                                                           this,
                                                           menu_selector(HelloWorld::menuShareCallback));
     pShareItem->setPosition(ccp(100,80));
     CCAction* action = CCMoveTo::create(2.0f, ccp(300, 50));
     pShareItem->runAction(action);

//        // 授权按钮
//    CCMenuItemImage *pAuthItem = CCMenuItemImage::create(
//                                                          "login.png",
//                                                          "login.png",
//                                                          this,
//                                                          menu_selector(HelloWorld::doAuthorize));
//    pAuthItem->setPosition(ccp(100,250));

    // 关闭按钮
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    

    // share button.
    // UMShareButton *shareButton = new UMShareButton("share.png","CloseSelected.png") ;

    UMShareButton *shareButton = UMShareButton::create("share.png","CloseSelected.png") ;
    shareButton->setUmengAppkey("507fcab25270157b37000010") ;
    shareButton->setShareContent("umeng social cocos2d-x sdk.") ;
    shareButton->setShareImage("/sdcard/header.jpeg") ;
    // 设置回调
    shareButton->setShareCallback(share_selector(shareCallback)) ;
    shareButton->setPosition(ccp(150, 180));


    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create();
    pMenu->addChild(pShareItem , 1);
    pMenu->addChild(pCloseItem , 1);
    pMenu->addChild(shareButton, 1) ;
//    pMenu->addChild(pAuthItem, 1);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("COCOS2D-X HACKATHON  -- Umeng.com ", "Arial", 34);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}


// 直接分享
void HelloWorld::menuShareCallback(CCObject* pSender)
{
    CCUMSocialSDK *sdk = CCUMSocialSDK::create();
    sdk->setAppKey("4eaee02c527015373b000003");
    vector<int>* platforms = new vector<int>();
    platforms->push_back(SINA);
    platforms->push_back(RENREN) ;
    platforms->push_back(DOUBAN) ;
    platforms->push_back(QZONE) ;
    platforms->push_back(QQ) ;
    CCLog("COCOS2D-X openshare");

    sdk->authorize(SINA, auth_selector(authCallback));
    // 打开分享面板, 注册分享回调
    // sdk->openShare(platforms, "COCOS2D-X HACKATHON -->  openShare","/sdcard/image.png", share_selector(shareCallback));

}

// 授权
void HelloWorld::doAuthorize(CCObject* pSender)
{

    static int count = 0 ;
    CCUMSocialSDK *sdk = CCUMSocialSDK::create();
    int num = count % 3 ;
    if (  num == 0 ) {
        CCLog("授权");
        sdk->authorize(RENREN, auth_selector(authCallback));
    }
    else if ( num == 1 ) {
               CCLog("判断人人网是否授权");
        sdk->isAuthorized(RENREN);
    } else {
           CCLog("删除人人网授权");
        sdk->deleteAuthorization(RENREN, auth_selector(authCallback));
    }
    ++count;
}

//截图功能
void HelloWorld::saveScreenshot()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCRenderTexture* texture = CCRenderTexture::create((int)size.width, (int)size.height);    
    texture->setPosition(ccp(size.width/2, size.height/2));    
    texture->begin();
    CCDirector::sharedDirector()->getRunningScene()->visit();
    texture->end();
    string imagePath = CCFileUtils::sharedFileUtils()->getWritablePath().c_str() ;
    CCLog(imagePath.c_str());
     //保存为png  
    bool result = texture->saveToFile("screenshot.png", kCCImageFormatPNG); 
    if ( result ) 
    {
        imagePath += "screenshot.png";
       CCLog(imagePath.c_str());
    }

}





void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
