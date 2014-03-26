//
//  UMShareButton.cpp
//  crossdemo
//
//  Created by mrsimple on 3/18/14.
//
//

#include "UMShareButton.h"
#include "cocos2d.h"
#include <iostream>
USING_NS_CC;
using namespace std;



/*
 * 设置文本内容
 * @param
 */
UMShareButton::UMShareButton()
{
    new (this)UMShareButton("","");
}


/*
 * 设置文本内容
 * @param
 */
UMShareButton::UMShareButton(const char *normalImage, const char *selectedImage)
:mPlatforms(NULL), mAppKey(NULL),mShareText(NULL),mImageName(NULL),mSocialSDK(NULL),mCallback(NULL)
{
    CCLog("UMShareButton图片: normalImage = %s, selectedImage = %s.", normalImage, selectedImage);

    initWithNormalImage(normalImage, selectedImage, "", this, menu_selector(UMShareButton::shareCallback)) ;
    // 构造CCUMSocialSDK对象
    mSocialSDK = CCUMSocialSDK::create() ;
}


/*
 * 设置文本内容
 * @param
 */
UMShareButton::~UMShareButton()
{
    delete mSocialSDK;
    delete mPlatforms;
}

/*
 * 设置友盟app key
 * @param
 */
void UMShareButton::setUmengAppkey(const char* appkey)
{
    // size_t length = strlen(appkey);
    // if ( this->mAppKey == NULL ) {
    //     this->mAppKey = (char*)malloc(sizeof(char) * length + 1);
    // }
    // memset(this->mAppKey, 0, sizeof(char) * length + 1);
    // strcpy(this->mAppKey, appkey);

     this->mAppKey = copyChars(appkey);

    // CCLog("设置app key : %s .", this->mAppKey);
}


/*
 * 设置文本内容
 * @param
 */
void UMShareButton::setShareContent(const char* text)
{
    // size_t length = strlen(text);
    // if ( mShareText == NULL ) {
    //     this->mShareText = (char*)malloc(sizeof(char) * length + 1);
    // }

    // memset(mShareText, 0, sizeof(char) * length + 1);
    // strcpy(mShareText, text);
    this->mShareText = copyChars(text);
}


/*
 * 设置本地图片和url图片, url图片必须以http://开头
 * @param 图片的本地路径或者url地址.
 */
void UMShareButton::setShareImage(const char* imgName)
{
    // size_t length = strlen(imgName);
    //     if ( mImageName == NULL ) {
    //     this->mImageName = (char*)malloc(sizeof(char) * length + 1);
    // }
    // memset(mImageName, 0, sizeof(char) * length + 1);
    // strcpy(mImageName, imgName);

      this->mImageName = copyChars(imgName);

}


/*
 *
 *
 */
char* UMShareButton::copyChars(const char* source)
{

    if ( source == NULL )
    {
        CCLog("UMShareButton::copyChars, the source chars is NULL.");
        return NULL;
    }

    size_t length = strlen(source);
    // 分配内存
    char* dest = (char*)malloc(sizeof(char) * length + 1);
    // 清内存
    memset(dest, 0, sizeof(char) * length + 1);
    strcpy(dest, source);
    return dest ;
}


/*
 * 设置回调
 * @param
 */
void UMShareButton::setShareCallback(ShareEventHandler callback)
{
    mCallback = callback ;
}


/*
 *
 * @param
 */
void UMShareButton::setPlatforms(vector<int>* platforms)
{
    mPlatforms = platforms ;
}


/*
 *
 * @param
 */
void UMShareButton::shareCallback(CCNode* pSender)
{

    if ( mPlatforms == NULL ) {
        mPlatforms = new vector<int>();
        mPlatforms->push_back(SINA) ;
        mPlatforms->push_back(QZONE) ;
        mPlatforms->push_back(RENREN) ;
        mPlatforms->push_back(DOUBAN) ;
        mPlatforms->push_back(TENCENT_WEIBO);
    }
    if ( mSocialSDK != NULL) {
        mSocialSDK->setAppKey(this->mAppKey);
        mSocialSDK->openShare(mPlatforms, mShareText, mImageName, mCallback) ;
    }
}
