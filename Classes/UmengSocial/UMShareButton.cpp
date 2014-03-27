//
//  UMShareButton.cpp
//  Umeng Social SDK ShareButton
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
 * 构造函数
 */
UMShareButton::UMShareButton()
{
    new (this)UMShareButton("","");
}


/*
 * 设置文本内容
 * @param  normalImage  按钮正常情况下显示的图片
 * @param  selectedImage 按钮选中情况下显示的图片
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
 * 创建一个UMShareButton对象
 * @param  normalImage  按钮正常情况下显示的图片
 * @param  selectedImage 按钮选中情况下显示的图片
 */
UMShareButton* UMShareButton::create(const char *normalImage, const char *selectedImage)
{
    UMShareButton* shareButton = new UMShareButton(normalImage, selectedImage) ;
    return shareButton ;
}

/*
 * 析构函数,释放内存
 */
UMShareButton::~UMShareButton()
{
    delete mAppKey;
    delete mImageName;
    delete mShareText;
    delete mSocialSDK;
    delete mPlatforms;
}

/*
 * 设置友盟app key
 * @param
 */
void UMShareButton::setUmengAppkey(const char* appkey)
{
     this->mAppKey = copyChars(appkey);
}


/*
 * 设置文本内容
 * @param
 */
void UMShareButton::setShareContent(const char* text)
{
    this->mShareText = copyChars(text);
}


/*
 * 设置本地图片和url图片, url图片必须以http://或者https://开头
 * @param 图片的本地路径或者url地址.
 */
void UMShareButton::setShareImage(const char* imgName)
{
      this->mImageName = copyChars(imgName);
}


/*
 * 申请内存, 拷贝字符串到目标字符指针, 返回该指针.
 * @param source 要拷贝的字符指针
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
 * 设置分享回调回调
 * @param callback 分享回调
 */
void UMShareButton::setShareCallback(ShareEventHandler callback)
{
    mCallback = callback ;
}


/*
 * 设置友盟SDK支持的平台， 平台的申明参考CCUMTypeDef.h中的Platform枚举
 * @param platforms 友盟SDK支持的平台
 */
void UMShareButton::setPlatforms(vector<int>* platforms)
{
    mPlatforms = platforms ;
}


/*
 * 点击该按钮时的回调, 这里实现为调用打开分享面板
 * @param pSender 
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
