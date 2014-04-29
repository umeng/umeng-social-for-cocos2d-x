#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    // 打开分享面板的按钮回调
    void menuShareCallback(CCObject* pSender);
    // 直接分享的按钮回调
    void directShareCallback(CCObject* pSender);
    // 授权某个平台的按钮回调
    void authorizeCallback(CCObject* pSender);
    // 删除某个平台的按钮回调
    void deleteAuthorizeCallback(CCObject* pSender);
    // 判断某个平台的按钮回调
    void isAuthorizedShareCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
private:
	// void openUmengShare();
    void saveScreenshot();
};

#endif // __HELLOWORLD_SCENE_H__
