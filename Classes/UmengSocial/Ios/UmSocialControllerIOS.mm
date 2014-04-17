//
//  UmSocialControllerIOS.cpp
//  UmengGame
//
//  Created by 张梓琦 on 14-3-16.
//
//

#include "UmSocialControllerIOS.h"
#import "UMSocial.h"
#import "UMSocialUIObject.h"
#import <UIKit/UIKit.h>

#ifdef CC_ShareToQQOrQzone
#import "UMSocialQQHandler.h"
#endif

#ifdef CC_ShareToWechat
#import "UMSocialWechatHandler.h"
#endif

#ifdef CC_ShareToLaiWang
#import "UMSocialLaiwangHandler.h"
#endif

#ifdef CC_ShareToYiXin
#import "UMSocialYiXinHandler.h"
#endif

#ifdef CC_ShareToFacebook
#import "UMSocialFacebookHandler.h"
#endif

#ifdef CC_ShareToTwitter
#import "UMSocialTwitterHandler.h"
#endif

#ifdef CC_ShareToInstagram
#import "UMSocialInstagramHandler.h"
#endif

string UmSocialControllerIOS::m_appKey = "";
//UMSocialUIDelegateObject * UmSocialControllerIOS::m_socialDelegate = nil;

NSString* getPlatformString(int platform){
    NSString *const platforms[17] = {
        UMShareToSina
        , UMShareToWechatSession
        , UMShareToWechatTimeline
        , UMShareToQQ
        , UMShareToQzone
        , UMShareToRenren
        , UMShareToDouban
        , UMShareToLWSession
        , UMShareToLWTimeline
        , UMShareToYXSession
        , UMShareToYXTimeline
        , UMShareToFacebook
        , UMShareToTwitter
        , UMShareToInstagram
        , UMShareToSms
        , UMShareToEmail
        , UMShareToTencent};
    
    return platforms[platform];
}

NSString* getNSStringFromCString(const char* cstr){
    if (cstr) {
        return [NSString stringWithUTF8String:cstr];
    }
    return nil;
}

UIViewController* getViewController(){
    UIViewController* ctrol = nil;
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        NSArray* array=[[UIApplication sharedApplication]windows];
        UIWindow* win=[array objectAtIndex:0];
        
        UIView* ui=[[win subviews] objectAtIndex:0];
        ctrol=(UIViewController*)[ui nextResponder];
    }
    else
    {
        // use this method on ios6
        ctrol=[UIApplication sharedApplication].keyWindow.rootViewController;
    }
    return ctrol;
}

void UmSocialControllerIOS::setAppKey(const char* appKey){
    [UMSocialData setAppKey:[NSString stringWithUTF8String:appKey]];
    m_appKey = appKey;
}

void UmSocialControllerIOS::initCocos2dxSDK(const char *sdkType, const char *version){
    [[UMSocialData defaultData] performSelector:@selector(setSdkType:version:) withObject:getNSStringFromCString(sdkType) withObject:getNSStringFromCString(version)];
}

void UmSocialControllerIOS::setTargetUrl(const char *targetUrl){
    [UMSocialData defaultData].extConfig.wechatSessionData.url = getNSStringFromCString(targetUrl);
    [UMSocialData defaultData].extConfig.wechatTimelineData.url = getNSStringFromCString(targetUrl);
    [UMSocialData defaultData].extConfig.wechatFavoriteData.url = getNSStringFromCString(targetUrl);
    [UMSocialData defaultData].extConfig.qqData.url = getNSStringFromCString(targetUrl);
    [UMSocialData defaultData].extConfig.qzoneData.url = getNSStringFromCString(targetUrl);
    [UMSocialData defaultData].extConfig.lwsessionData.url =getNSStringFromCString(targetUrl);
    [UMSocialData defaultData].extConfig.lwtimelineData.url =getNSStringFromCString(targetUrl);
    [UMSocialData defaultData].extConfig.yxsessionData.url =getNSStringFromCString(targetUrl);
    [UMSocialData defaultData].extConfig.yxtimelineData.url =getNSStringFromCString(targetUrl);
    [UMSocialData defaultData].extConfig.facebookData.urlString =getNSStringFromCString(targetUrl);
}

#ifdef CC_ShareToQQOrQzone
void UmSocialControllerIOS::setQQAppIdAndAppKey(const char *appId,const char *appKey){
    [UMSocialQQHandler setQQWithAppId:getNSStringFromCString(appId) appKey:getNSStringFromCString(appKey) url:@"http://www.umeng.com/social"];
}
#endif

#ifdef CC_ShareToWechat
void UmSocialControllerIOS::setWechatAppId(const char *appId){
    [UMSocialWechatHandler setWXAppId:getNSStringFromCString(appId) url:@"http://www.umeng.com/social"];
}
#endif

#ifdef CC_ShareToLaiWang
void UmSocialControllerIOS::setLaiwangAppInfo(const char *appId, const char *appKey, const char *appName){
    [UMSocialLaiwangHandler setLaiwangAppId:getNSStringFromCString(appId) appSecret:getNSStringFromCString(appKey) appDescription:getNSStringFromCString(appName) urlStirng:@"http://www.umeng.com/social"];
}
#endif

#ifdef CC_ShareToYiXin
void UmSocialControllerIOS::setYiXinAppKey(const char *appKey){
    [UMSocialYixinHandler  setYixinAppKey:getNSStringFromCString(appKey) url:@"http://www.umeng.com/social"];
}
#endif

#ifdef CC_ShareToFacebook
void UmSocialControllerIOS::setFacebookAppId(const char *appId){
    [UMSocialFacebookHandler setFacebookAppID:getNSStringFromCString(appId) shareFacebookWithURL:@"http://www.umeng.com/social"];
}
#endif

#ifdef CC_ShareToTwitter
void UmSocialControllerIOS::openTwitter(){
    [UMSocialTwitterHandler openTwitter];
}
#endif

#ifdef CC_ShareToInstagram
void UmSocialControllerIOS::openInstagram()
{
    [UMSocialInstagramHandler openInstagramWithScale:YES paddingColor:[UIColor blackColor]];
}
#endif

void UmSocialControllerIOS::authorize(int platform, AuthEventHandler callback){
    
    UMSocialSnsPlatform *snsPlatform = [UMSocialSnsPlatformManager getSocialPlatformWithName:getPlatformString(platform)];
    
    
    auto ctrol = getViewController();
    [UMSocialConfig setSupportedInterfaceOrientations:UIInterfaceOrientationMaskLandscape];
    snsPlatform.loginClickHandler(ctrol,[UMSocialControllerService defaultControllerService],YES,^(UMSocialResponseEntity *response)
                                  {
                                      if (callback) {
                                          map<string,string> loginData;
                                          if (response.responseCode == UMSResponseCodeSuccess) {
                                              
                                              UMSocialAccountEntity *snsAccount = [[UMSocialAccountManager socialAccountDictionary] valueForKey:snsPlatform.platformName];
                                              string *tokenValue = new string([snsAccount.accessToken UTF8String]);
                                              string *uid = new string([snsAccount.usid UTF8String]);
                                              loginData.insert(pair<string, string>("token",*tokenValue));
                                              loginData.insert(pair<string, string>("uid",*uid));
                                              callback(platform, (int)response.responseCode,loginData);
                                          } else {
                                              loginData.insert(pair<string, string>("msg","fail"));
                                              callback(platform, (int)response.responseCode,loginData);
                                          }
                                      }
                                  });
}

void UmSocialControllerIOS::deleteAuthorization(int platform, AuthEventHandler callback){
    [[UMSocialDataService defaultDataService] requestUnOauthWithType:getPlatformString(platform)  completion:^(UMSocialResponseEntity *response){
        if (callback) {
            map<string,string> loginData;
            loginData.insert(pair<string,string>("msg","deleteOauth"));
            callback(platform, (int)response.responseCode,loginData);
        }
    }];
}

bool UmSocialControllerIOS::isAuthorized(int platform){
    BOOL isOauth = [UMSocialAccountManager isOauthWithPlatform:getPlatformString(platform)];
    
    return isOauth == YES;
}

void UmSocialControllerIOS::openShareWithImagePath(vector<int>* platforms, const char* text, const char* imagePath,ShareEventHandler callback){
    
    NSMutableArray* array = [NSMutableArray array];
    if (platforms) {
        for (unsigned int i = 0; i < platforms->size(); i++) {
            [array addObject:getPlatformString(platforms->at(i))];
        }
    }
    
    UIImage* image = nil;
    if(imagePath){
        NSString *imageString = getNSStringFromCString(imagePath);
        NSLog(@"imageString is %@",imageString);
        if ([imageString hasPrefix:@"http://"] || [imageString hasPrefix:@"https://"]) {
            [[UMSocialData defaultData].urlResource setResourceType:UMSocialUrlResourceTypeImage url:imageString];
        } else {
            image = [UIImage imageNamed:getNSStringFromCString(imagePath)];
        }
    }
    
    UMSocialUIObject * delegate = [[UMSocialUIObject alloc] initWithCallback:callback];
    [UMSocialSnsService presentSnsIconSheetView:getViewController()
                                         appKey:[NSString stringWithUTF8String:m_appKey.c_str() ]
                                      shareText:[NSString stringWithUTF8String:text ]
                                     shareImage:image
                                shareToSnsNames:array
                                       delegate:delegate];
    [UMSocialConfig setSupportedInterfaceOrientations:UIInterfaceOrientationMaskLandscape];

}

void UmSocialControllerIOS::directShare(const char* text, const char* imagePath,int platform, ShareEventHandler callback){
    UIImage* image = nil;
    if(imagePath){
        NSString *imageString = [NSString stringWithUTF8String:imagePath];
        if ([imageString hasPrefix:@"http:://"] || [imageString hasPrefix:@"https://"]) {
            [[UMSocialData defaultData].urlResource setResourceType:UMSocialUrlResourceTypeImage url:imageString];
        } else {
            image = [UIImage imageNamed:getNSStringFromCString(imagePath)];
        }
    }
    [[UMSocialDataService defaultDataService]  postSNSWithTypes:@[getPlatformString(platform)] content:[NSString stringWithUTF8String:text] image:image location:nil urlResource:nil presentedController:getViewController() completion:^(UMSocialResponseEntity *response){
        if (callback) {
            callback(platform, (int)response.responseCode,string([response.message UTF8String]));
        }
    }];
}