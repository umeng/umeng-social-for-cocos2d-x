#include "HelloWorldScene.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <string>
#include <stdio.h>
#include "UMLog.h"
#include "UmengSocial/CCUMTypeDef.h"
#include "UmengSocial/CCUMSocialSDK.h"
#include "UmengSocial/Android/CCUMSocialController.h"
#include <iostream>
 
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
    
    
    // add a "share" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pShareItem = CCMenuItemImage::create(
                                                          "share.png",
                                                          "share.png",
                                                          this,
                                                          menu_selector(HelloWorld::menuShareCallback));
    pShareItem->setPosition(ccp(50,50));
    CCAction* action = CCMoveTo::create(3.0f, ccp(300, 50));
    pShareItem->runAction(action);

    // add a "close" icon to exit the progress. it's an autorelease object
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
    pMenu->addChild(pCloseItem , 2);
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
void authCallback(const char* platform, int stCode)
{
    UMLog::D("#shareCallback", "#### authCallback");
}

/*
 * 分享回调
 */
void shareCallback(const char* platform, int stCode)
{
      UMLog::D("#shareCallback", "#### shareCallback");
}


void HelloWorld::menuShareCallback(CCObject* pSender)
{
    CCUMSocialSDK *sdk = CCUMSocialSDK::create();
    sdk->setShareContent("This is COCOS2D-X test.");
    sdk->directShare("qzone", share_selector(shareCallback));
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
    UMLog::D("### path", imagePath.c_str());
     //保存为png  
    bool result = texture->saveToFile("screenshot.png", kCCImageFormatPNG); 
    if ( result ) 
    {
        imagePath += "screenshot.png";
        UMLog::D("#save scrshot", imagePath.c_str());
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
