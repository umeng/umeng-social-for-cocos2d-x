# 友盟社会化组件Cocos2d-x SDK -- 集成文档

* 1.[下载SDK](#social_cocos2dx)
* 2.[Cocos2d-x集成分享组件](#cocos2dx_integration)
    * 2.1 [Android平台集成](#cocos2dx_integration_android)
    * 2.2 [iOS平台集成](#cocos2dx_integration_ios)
* 3.[授权接口说明](#cocos2dx_integration_auth)
* 4.[添加更多平台](#cocos2dx_integration_more_platforms)
	* 4.1 [集成来往和来往动态](#laiwang_platforms)
	* 4.2 [集成易信和易信朋友圈](#yixin_platforms)
	* 4.3 [集成facebook](#facebook_platforms)
	* 4.4 [集成instagram](#instagram_platforms)
* 5.[Android混淆问题](#proguard)
* 6.[技术支持](#support)  

------------
     
## 概述
   友盟社会化组件，可以让移动应用快速具备社会化分享、登录、评论、喜欢等功能，并提供实时、全面的社会化数据统计分析服务。   
   本指南将会手把手教你使用友盟社会化组件Cocos2d-x SDK，用5分钟为APP增加新浪微博、微信、QQ空间等国内外十几个主流平台的分享功能。
   该Cocos2d-x SDK目前支持ios和android平台。
 
<b id=social_cocos2dx></b>
## 1 下载和拷贝Cocos2d-x所需文件 
   首先您需要下载友盟社会化组件 Cocos2d-x SDK,然后将该sdk解压。
         

<b id=cocos2dx_integration></b>   
## 2 Cocos2d-x集成友盟分享组件
<b id=cocos2dx_integration_android></b>
### 2.1 Android平台集成 
#### 2.1.1 拷贝所需的jar包和资源文件          
  解压Cocos2d-x SDK压缩包，将proj.android文件夹下的'libs'和'res'文件夹复制到你的项目工程根目录下（如使用'ADT 17'以下用户需要手动添加'libs'下的jar文件到工程Path中）, 如图所示 :    
  ![alt text](http://dev.umeng.com/images/android/social_sdk_quick_guide_step2.jpg "drag_sdk")
  
#### 2.1.2 拷贝类文件
   将UmengGame的proj.android项目中的com.umeng.social包拷贝到您的项目Android平台的src目录下, 如图所示 :
   
#### 2.1.3 配置AndroidManifest.xml
```xml
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="com.umeng.example"
    android:versionCode="1"
    android:versionName="1.0" >

    <application
        android:debuggable="true"
        android:icon="@drawable/icon"
        android:label="@string/app_name"
        android:theme="@android:style/Theme.Black.NoTitleBar" >
        <activity
            android:name=".UmengHome"
            android:label="@string/app_name" >
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />

                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>

        <!-- ###################注册SDK使用的Activity###################### -->
        <!--分享编辑页-->
        <activity
            android:name="com.umeng.socialize.view.ShareActivity"
            android:configChanges="orientation|keyboard"
            android:launchMode="singleTask"
            android:noHistory="true"
            android:theme="@style/Theme.UMDialog"
            android:windowSoftInputMode="stateVisible|adjustResize" >
        </activity>

        <!-- ############ QQ空间和QQ SSO授权的Activity注册 ############ -->
        <activity
            android:name="com.tencent.tauth.AuthActivity"
            android:launchMode="singleTask"
            android:noHistory="true" >
            <intent-filter>
                <action android:name="android.intent.action.VIEW" />

                <category android:name="android.intent.category.DEFAULT" />
                <category android:name="android.intent.category.BROWSABLE" />
                <!-- 100424468，如果你使用的公用账号，则不需要修改；否则修改成你在QQ开放平台申请的 APP ID-->
                <data android:scheme="tencent100424468" /> 
            </intent-filter>
        </activity>
        <activity android:name="com.tencent.plus.ImageActivity" />
        <activity android:name="com.tencent.connect.common.AssistActivity"
            android:theme="@android:style/Theme.Translucent.NoTitleBar"
            android:screenOrientation="portrait">
        </activity>
        
        <!-- facebook相关 -->
        <activity
            android:name="com.facebook.LoginActivity"
            android:label="@string/app_name"
            android:theme="@android:style/Theme.Translucent.NoTitleBar" />

        <!-- 这里填写你的facebook app id,必须声明在string.xml中 -->
        <meta-data
            android:name="com.facebook.sdk.ApplicationId"
            android:value="@string/facebook_app_id" />

<!-- ###################添加UmengAppkey###################### -->
        <meta-data
            android:name="UMENG_APPKEY"
            android:value="xxxxxxxxxxxxxxxxxxxxxx" >
        </meta-data>

    </application>

    <uses-sdk android:minSdkVersion="8" />

    <!-- ###################声明SDK使用的相关权限###################### -->
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />  <!-- 检测网络状态 -->
    <uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />     <!-- 获取mac地址作为用户的备用唯一标识 -->
    <uses-permission android:name="android.permission.READ_PHONE_STATE" />      <!-- 获取用户手机的IMEI，用来唯一的标识用户。 -->
    <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" /><!-- 缓存资源优先存入SDcard -->
    <uses-permission android:name="android.permission.INTERNET" />              <!-- 允许应用程序联网，以便向我们的服务器端发送数据。 -->
    <uses-permission android:name="android.permission.ACCESS_FINE_LOCATION" />  <!-- 用于评论模块分享位置信息 -->
    <uses-permission android:name="android.permission.ACCESS_COARSE_LOCATION" /><!-- 用于评论模块分享位置信息 -->
</manifest>
```
   
#### 添加Android平台的初始化代码
  在您的Cocos2dxActivity子类的onCreate方法下添加如下代码:    
```java         
// this为Cocos2dxActivity类型, 参数2为描述符,可随意修改.
CCUMSocialController.initSocialSDK(this, "com.umeng.social.share");
```   
#### 覆写Cocos2dxActivity子类的onActivityResult方法
   在onActivityResult添加如下代码 : 
```java
// 授权回调    
CCUMSocialController.onActivityResult(requestCode, resultCode, data);    	  
super.onActivityResult(requestCode, resultCode, data);
``` 

<b id=cocos2dx_integration_ios></b>  
### 2.2 iOS平台集成   
#### 2.2.1 加入iOS SDK
   解压SDK压缩包，将UmengGame/Classes目录下的形如umeng_ios_social_sdk_xxx的文件夹拖入工程目录：

![alt text](http://dev.umeng.com/images/ios/social_drag_sdk.png "drag_sdk") 

确认勾选了“Copy items to destination's group folder”选项，并选择你要添加到的Target: 

![alt text](http://dev.umeng.com/images/ios/social_check_tip.png "check_tip") 

现在应该是这样的效果：

![alt text](http://dev.umeng.com/images/ios/social_project_structure.png "project_structure") 

UMSocial_Sdk_x.x.x 文件夹的目录结构

文件或文件夹|含义
---|---
libUMSocial_Sdk_x.x.x.a, libUMSocial_Sdk_Comment_3.0.a | 库文件
Header| 头文件
SocialSDKXib| xib文件
en.lproj，zh-Hans.lproj | 英文和中文语言文件
frameworks|使用的第三方SDK，里面的Wechat 代表微信SDK

UMSocial_Sdk_Extra_Frameworks 文件夹的目录结构

文件或文件夹|含义
---|---
TencentOpenAPI|QQ互联SDK
Facebook|Facebook SDK
LaiWang|来往 SDK
UMSocialYiXin.framework|易信 SDK
UMSocial_ScreenShot_Sdk|截屏 SDK
UMSocial_Shake_Sdk|摇一摇 SDK

>注意：  
>1. 若你的工程设置了all_load，需要添加手机QQ SDK需要的系统framework:Security.framework,libiconv.dylib,SystemConfiguration.framework,CoreGraphics.framework，libsqlite3.dylib，CoreTelephony.framework,libstdc++.dylib,libz.dylib。详情请参考<a http://dev.umeng.com/social/ios/share/specific-integration#binding_config" style="text-decoration:none">SSO（免登录）和新平台的设置</a>  


#### 2.3 在Cocos2d-x游戏中添加分享功能
   将android和ios所需的资源添加到对应的工程以后(也可以是某一个平台), 您就可以在cocos2d-x中使用该友盟社会化组件的分享、登录功能了。   
  首先将UmengGame项目Classes目录下的UmengSocial文件夹拷贝到您的工程的Classes目录下，UmengSocial包括：   
> * Android平台的调用实现 ( Android文件夹 )；   
> * IOS平台的调用实现 ( iOS文件夹 )；  
> * 针对Cocos2d-x的统一接口 ( CCUMSocialSDK )；     
> * 针对Cocos2d-x封装的分享按钮,点击按钮即可打开分享面板  ( UMShareButton )；    
> * 平台以及分享、授权回调函数的定义   ( CCUMTypeDef.h ) 。

   然后添加用于分享的代码, 友盟提供了两种方式来方便开发者使用分享功能， 示例如下 :    
   ***方式一 :***     
   开发者可以通过UMShareButton类来快速的实现分享功能，UMShareButton是CCMenuItemImage的子类，当用户点击该按钮时将会打开友盟的分享面板。
   集成代码如下 :
```cpp
// 引入相关的头文件
#include "UmengSocial/CCUMTypeDef.h"
#include "UmengSocial/UMShareButton.h"
// ...... 代码省略

// HelloWorld为cocos2d::CCLayer的子类
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	// 创建分享按钮, 参数1为按钮正常情况下的图片, 参数2为按钮选中时的图片,参数3为分享回调
	UMShareButton *shareButton = UMShareButton::create("shareNormal.png","shareSelected.png", share_selector(shareCallback)) ;
	// 设置您的友盟appkey
	shareButton->setUmengAppkey("507fcab25270157b37000010") ;
	// 设置文本分享内容
	shareButton->setShareContent("umeng social cocos2d-x sdk.") ;
	// 设置要分享的图片, 图片支持本地图片和url图片, 但是url图片必须以http://或者https://开头
	shareButton->setShareImage("/sdcard/header.jpeg") ;
	// 设置按钮的位置
	shareButton->setPosition(ccp(150, 180));
	// 然后开发者需要将该按钮添加到游戏场景中
	this->addChild( shareButton );
    
    return true;
}
```     

***方式二 :***    
    开发者可以使用CCUMSocialSDK类来完成分享、授权、删除授权等操作， 实际上UMShareButton就是包装了CCUMSocialSDK以实现相关的功能。具体功能请参考CCUMSocialSDK中的注释。
    开发者可以自行定义某个按钮，然后在该按钮的点击事件中通过CCUMSocialSDK来进行相应的操作，示例代码如下 :   
```cpp
// 引入相关的头文件
#include "UmengSocial/CCUMTypeDef.h"
#include "UmengSocial/CCUMSocialSDK.h"
// ...... 代码省略


// HelloWorld为cocos2d::CCLayer的子类, shareButtonClick为某个按钮点击事件的处理函数
void HelloWorld::shareButtonClick()
{
	// 获取一个CCUMSocialSDK实例
    CCUMSocialSDK *sdk = CCUMSocialSDK::create();
    // 设置友盟appkey
    sdk->setAppKey("4eaee02c527015373b000003");
    // 设置友盟分享面板上显示的平台
    vector<int>* platforms = new vector<int>();
    platforms->push_back(SINA);
    platforms->push_back(RENREN) ;
    platforms->push_back(DOUBAN) ;
    platforms->push_back(QZONE) ;
    platforms->push_back(QQ) ;

	// 授权函数
   sdk->authorize(SINA, auth_selector(authCallback));
    // 打开分享面板, 注册分享回调, 参数1为分享面板上的平台, 参数2为要分享的文字内容, 参数3为要分享的图片路径, 参数4为分享回调.
   sdk->openShare(platforms, "要分享的文字内容","/sdcard/image.png", share_selector(shareCallback));
```    
    
   **分享回调的为如下形式 :**    
```cpp
/*
 * 分享回调, 该回调不是某个类的成员函数， 而是一个普通的函数, 具体使用参考HelloWorldScene的例子
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
```   
   点击对应的按钮则会弹出如下界面 : 



**微信精确回调使用说明**
> * 将SDK包中weixin目录下的wxapi文件夹拷贝到您的工程的包目录下，然后修改WXEntryActivity的完整路径即可。例如social_sdk_example的包名为com.umeng.soexample,
因此将wxapi文件夹拷贝到com.umeng.soexample下即可。最终WXEntryActivity的完整路径为com.umeng.soexample.wxapi.WXEntryActivity。     
* 其中分享回调接口SnsPostListener中的onComplete方法的第二个参数代表分享的状态码，当值为200时表示分享成功;其余的值则为分享失败。   


<b id=cocos2dx_integration_auth></b>
### 3 授权接口使用说明
#### 3.1 授权接口说明   
   CCUMSocialSDK类中还提供了授权相关的接口，接口使用说明如下 : 
```cpp
CCUMSocialSDK *sdk = CCUMSocialSDK::create();
// 对某个平台授权, 参数二为授权回调
sdk->authorize(RENREN, auth_selector(authCallback));

// 判断某个平台是否授权
// sdk->isAuthorized(RENREN);

// 删除某个平台的授权
// sdk->deleteAuthorization(RENREN, auth_selector(authCallback));
```     

#### 3.2 授权回调说明
   授权回调类型定义在CCUMTypeDef.h中，当授权成功时, 会将授权信息返回给开发者, 开发者可以通过遍历map来获取数据；   
当授权失败, 会返回一个字段的数据, key为"msg", 值为错误的信息。如果是删除授权, 也是返回一个字段的数据, key为"msg", 值为"deleteOauth"。开发者可以通过判断返回码和map中的数据来进行相应的处理。
   授权回调函数示例如下 :   
```cpp
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
```   

<b id=cocos2dx_integration_more_platforms></b>
## 4 添加更多平台
<b id=laiwang_platforms></b> 
### 4.1 集成来往和来往动态
#### 4.1.1 Android平台 
   添加所需jar和资源，将sdk包中laiwang文件夹下的libs、res目录下的文件拷贝到工程中对应的文件夹中。        
   	在com.umeng.social.CCUMSocialController中修改LAIWANG_APPID和LAIWANG_APPKEY为您再来往开放平台申请到的app id和app key，然后在该类的supportPlatfrom函数中找到添加来往或者来往动态平台的代码段，将相应的注释去掉，示例如下 :    
   ***添加来往平台***       
```java
UMLWHandler umLWHandler = UMLWService.supportLWPlatform(
			mActivity, LAIWANG_APPID,
LAIWANG_APPKEY, TARGET_URL);
umLWHandler.setTitle("友盟社会化分享组件-来往动态");
umLWHandler.setMessageFrom("友盟分享组件");
// 添加来往平台到sdk中
umLWHandler.addToSicalSDK();
```
   
   ***添加来往动态平台***    
```java
UMLWHandler umlwDynamicHandler =
UMLWService.supportLWDynamicPlatform(
		mActivity, LAIWANG_APPID,
LAIWANG_APPKEY, TARGET_URL);
umlwDynamicHandler.setTitle("友盟社会化分享组件-来往");
// 设置消息来源
umlwDynamicHandler.setMessageFrom("友盟分享组件");
// 添加来往动态到sdk中
umlwDynamicHandler.addToSicalSDK();
```   
   
#### 4.1.2 IOS平台
   ***添加来往平台***   
   
   
   ***添加来往动态平台***   

<b id=yixin_platforms></b>
### 4.2 集成易信和易信朋友圈
#### 4.2.1 Android平台   
   添加所需jar和资源，将sdk包中yixin文件夹下的libs、res目录下的文件拷贝到工程中对应的文件夹中。         
   在com.umeng.social.CCUMSocialController中修改YIXIN_APPKEY为您在易信开放平台申请到的app id，然后在该类的supportPlatfrom函数中找到添加易信或者易信朋友圈平台的代码段，将相应的注释去掉，示例如下 :        
   ***添加易信平台***  
```java
UMYXHandler yxHandler = new UMYXHandler(mActivity, YIXIN_APPKEY,
			 false);
// 添加易信平台到SDK
// yxHandler.addToSicalSDK();
```    

   ***添加易信朋友圈平台***    
```java
UMYXHandler yxHandler = new UMYXHandler(mActivity, YIXIN_APPKEY,
			 true);
// 添加易信朋友圈平台到SDK
yxHandler.addToSicalSDK();
```   

**易信精确回调使用说明**
> * 将SDK包中yixin目录下的yxapi文件夹拷贝到您的工程的包目录下，然后修改YXEntryActivity的完整路径即可。例如social_sdk_example的包名为com.umeng.soexample,
因此将yxapi文件夹拷贝到com.umeng.soexample下即可。最终YXEntryActivity的完整路径为com.umeng.soexample.yxapi.YXEntryActivity。     
* 其中分享回调接口SnsPostListener中的onComplete方法的第二个参数代表分享的状态码，当值为200时表示分享成功;其余的值则为分享失败。
   
#### 4.2.2 IOS平台
   ***添加易信平台***   
   
   
   ***添加易信朋友圈平台***  
   
 <b id=facebook_platforms></b>
### 4.3 集成Facebook
#### 4.3.1 Android平台    
   添加所需jar和资源，将sdk包中facebook文件夹下的libs、res目录下的文件拷贝到工程中对应的文件夹中。         
   在com.umeng.social.CCUMSocialController中的supportPlatfrom函数中找到添加facebook平台的代码段，将相应的注释去掉，示例如下 :     
   ***添加Facebook平台***   
```java
UMFacebookHandler mFacebookHandler = new UMFacebookHandler(
			 mActivity, PostType.FEED);
// 添加facebook平台 
mFacebookHandler.addToSocialSDK();
```     
   
#### 4.3.2 IOS平台
   ***添加Facebook平台***
   
<b id=instagram_platforms></b>
### 4.4 集成Instagram
#### 4.4.1 Android平台    
   添加所需jar和资源，将sdk包中instagram文件夹下的libs、res目录下的文件拷贝到工程中对应的文件夹中。         
   在com.umeng.social.CCUMSocialController中的supportPlatfrom函数中找到添加instagram平台的代码段，将相应的注释去掉，示例如下 :     
   ***添加Instagram平台***   
```java
UMInstagramHandler instagramHandler = new UMInstagramHandler(
			 mActivity);
// 添加instagram平台 
instagramHandler.addToSocialSDK();
```      
   
#### 4.4.2 IOS平台
   ***添加Instagram平台***

<b id=proguard></b>
## 5. Android混淆         
  为了保证引用友盟Social SDK jar文件以及腾讯jar文件被混淆，请在proguard.cfg文件中添加以下代码避免被混淆.。   
```text
-dontwarn com.google.android.maps.**
-dontwarn android.webkit.WebView
-dontwarn com.umeng.**
-dontwarn com.tencent.weibo.sdk.**
-dontwarn com.facebook.**

-libraryjars libs/SocialSDK_QQZone_2.jar

-keep enum com.facebook.**
-keepattributes Exceptions,InnerClasses,Signature
-keepattributes *Annotation*
-keepattributes SourceFile,LineNumberTable

-keep public interface com.facebook.**
-keep public interface com.tencent.**
-keep public interface com.umeng.socialize.**
-keep public interface com.umeng.socialize.sensor.**
-keep public interface com.umeng.scrshot.**

-keep public class com.umeng.socialize.* {*;}
-keep public class javax.**
-keep public class android.webkit.**

-keep class com.facebook.**
-keep class com.umeng.scrshot.**
-keep public class com.tencent.** {*;}
-keep class com.umeng.socialize.sensor.**

-keep class com.tencent.mm.sdk.openapi.WXMediaMessage {*;}

-keep class com.tencent.mm.sdk.openapi.** implements com.tencent.mm.sdk.openapi.WXMediaMessage$IMediaObject {*;}

-keep class im.yixin.sdk.api.YXMessage {*;}
-keep class im.yixin.sdk.api.** implements im.yixin.sdk.api.YXMessage$YXMessageData{*;}

-keep public class [your_pkg].R$*{
    public static final int *;
}                                 
```

混淆过程中遇到的问题,请联系我们.

<b id=support></b>
## 6 技术支持        

请发邮件至social-support@umeng.com。如果您出现的问题和SDK相关，请说明您使用的是Android的SDK，我们会尽快回复您。
