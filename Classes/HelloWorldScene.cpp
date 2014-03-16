#include "HelloWorldScene.h"
#include <string>
#include "UmengSocial/CCUMTypeDef.h"
#include "UmengSocial/CCUMSocialSDK.h"

#include <iostream>
 
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
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
    // CCAction* action = CCMoveTo::create(3.0f, ccp(300, 50));
    // pShareItem->runAction(action);

        // 授权按钮
    CCMenuItemImage *pAuthItem = CCMenuItemImage::create(
                                                          "login.png",
                                                          "login.png",
                                                          this,
                                                          menu_selector(HelloWorld::doAuthorize));
    pAuthItem->setPosition(ccp(100,200));

    // 关闭按钮
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create();
    pMenu->addChild(pShareItem , 1);
    pMenu->addChild(pCloseItem , 1);
    pMenu->addChild(pAuthItem, 1);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("COCOS2D-X HACKATHON", "Arial", 34);
    
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

void HelloWorld::openUmengShare()
{

    JniMethodInfo methodInfo ;

    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数 
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"com/umeng/game/UmengGame","openShare", "()V");  
  
    if (!isHave) { 
        CCLog("jni:此函数不存在"); 
    }else{ 
        CCLog("jni:此函数存在"); 
        //调用此函数 
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID); 
    } 
}

/*
 *授权回调, 还需要传递一个State
 */
void authCallback(int platform, int stCode)
{
    CCLog("#### authCallback");
}

/*
 * 分享回调
 */
void shareCallback(int platform, int stCode)
{
      CCLog("#### shareCallback");
      CCLog("platform num is : %d.", platform);
}


// 直接分享
void HelloWorld::menuShareCallback(CCObject* pSender)
{
    CCUMSocialSDK *sdk = CCUMSocialSDK::create();
    static int shareCount = 1 ;
    int num = shareCount % 3 ;
    if ( num == 1 ) {
        // 打开分享面板, 注册分享回调
        sdk->openShare("COCOS2D-X HACKATHON -->  openShare","/sdcard/image.png", share_selector(shareCallback));
    } else {
        sdk->directShare(SINA, "COCOS2D-X HACKATHON  -->  directShare","/sdcard/image.png",share_selector(shareCallback));
    }

    ++shareCount;
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
