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
// 使用友盟命令空间 
USING_NS_UM_SOCIAL;

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


    // 打开分享面板
    CCMenuItemFont *shareTextButton = CCMenuItemFont::create("打开分享面板",this , menu_selector(HelloWorld::menuShareCallback));
    shareTextButton->setPosition(ccp(150,480));

    // 底层API分享
    CCMenuItemFont *directTextButton = CCMenuItemFont::create("底层分享",this , menu_selector(HelloWorld::directShareCallback));
    directTextButton->setPosition(ccp(150,400));

    // 授权某平台
    CCMenuItemFont *authTextButton = CCMenuItemFont::create("授权某平台",this , menu_selector(HelloWorld::authorizeCallback));
    authTextButton->setPosition(ccp(150,320));

    // 删除某平台授权
    CCMenuItemFont *delAuthTextButton = CCMenuItemFont::create("删除某平台删除",this , menu_selector(HelloWorld::deleteAuthorizeCallback));
    delAuthTextButton->setPosition(ccp(150,240));

    // 判断某平台是否授权
    CCMenuItemFont *isAuthTextButton = CCMenuItemFont::create("判断某平台是否授权",this , menu_selector(HelloWorld::isAuthorizedShareCallback));
    isAuthTextButton->setPosition(ccp(150,160));


    // ********************  设置友盟的app key以及相关的信息  ***********************************
    // 获取CCUMSocialSDK对象, 如果使用的UMShareButton, 则通过UMShareButton对象的getSocialSDK()方法获取.
    CCUMSocialSDK *sdk = CCUMSocialSDK::create();
    // 设置友盟app key
    sdk->setAppKey("507fcab25270157b37000010");
    sdk->setQQAppIdAndAppKey("设置QQ的app id", "appkey");
    // sdk->setWeiXinAppId("设置微信和朋友圈的app id");
    // sdk->setYiXinAppKey("设置易信和易信朋友圈的app id");
    sdk->setLaiwangAppInfo("设置来往和来往动态的app id", "设置来往和来往动态的app key", "我的应用名");
    sdk->setFacebookAppId("你的facebook appid");
    // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
    sdk->setTargetUrl("http://www.umeng.com/social");
    // ********************************************************************************


    // 关闭按钮
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    

    // 友盟share button.
    UMShareButton *shareButton = UMShareButton::create("share.png","CloseSelected.png", share_selector(shareCallback)) ;
    shareButton->setUmengAppkey("507fcab25270157b37000010") ;
    shareButton->setShareContent("umeng social cocos2d-x sdk.") ;
    shareButton->setShareImage("/sdcard/header.jpeg") ;
    // 设置分享回调
    // shareButton->setShareCallback(share_selector(shareCallback));
    shareButton->setPosition(ccp(480, 150));


    CCMenuItemFont *umshareTextButton = CCMenuItemFont::create("友盟ShareButton");
    umshareTextButton->setPosition(ccp(480,60));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create();
    pMenu->addChild(pCloseItem , 1);
    // 友盟share button
    pMenu->addChild(shareButton , 1);
    pMenu->addChild(umshareTextButton, 1);

    // 文字按钮
    pMenu->addChild(shareTextButton, 1);
    pMenu->addChild(directTextButton, 1) ;
    pMenu->addChild(authTextButton, 1);
    pMenu->addChild(delAuthTextButton, 1) ;
    pMenu->addChild(isAuthTextButton, 1);

    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Umeng Social Cocos2d-x SDK", "Arial", 34);
    
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


// 直接分享的按钮回调
void HelloWorld::directShareCallback(CCObject* pSender)
{

    CCUMSocialSDK *sdk = CCUMSocialSDK::create();
    sdk->directShare(SINA, "COCOS2D-X HACKATHON -->  directShare   testing", "/sdcard/image.png", share_selector(shareCallback)) ;
}


// 授权某个平台的按钮回调
void HelloWorld::authorizeCallback(CCObject* pSender)
{
   CCUMSocialSDK *sdk = CCUMSocialSDK::create();
   CCLog("授权");
   sdk->authorize(SINA, auth_selector(authCallback));

}

// 删除某个平台的按钮回调
void HelloWorld::deleteAuthorizeCallback(CCObject* pSender)
{
    CCUMSocialSDK *sdk = CCUMSocialSDK::create();
    CCLog("删除腾讯微博授权");
    sdk->deleteAuthorization(SINA, auth_selector(authCallback));
}

// 判断某个平台的按钮回调
void HelloWorld::isAuthorizedShareCallback(CCObject* pSender)
{
    CCUMSocialSDK *sdk = CCUMSocialSDK::create();
    CCLog("@@@@ 判断新浪微博是否授权");
    bool isAuthorized = sdk->isAuthorized(SINA);
    if ( isAuthorized ) 
    {
        CCLog("@@ 新浪微博已经授权");
    } 
    else 
    {
        CCLog("@@ 新浪微博还没有授权");
    }
}


// 直接分享
void HelloWorld::menuShareCallback(CCObject* pSender)
{
    CCUMSocialSDK *sdk = CCUMSocialSDK::create();
    vector<int>* platforms = new vector<int>();
    platforms->push_back(SINA);
    platforms->push_back(RENREN) ;
    platforms->push_back(DOUBAN) ;
    platforms->push_back(QZONE) ;
    platforms->push_back(QQ) ;
    platforms->push_back(SMS) ;
    platforms->push_back(EMAIL) ;
    CCLog("COCOS2D-X openshare");

    // 打开分享面板, 注册分享回调
    sdk->openShare(platforms, "COCOS2D-X HACKATHON -->  openShare","/sdcard/image.png", share_selector(shareCallback));

}

/**
 * 截图功能
 */ 
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
