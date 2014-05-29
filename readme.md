# 友盟社会化组件Cocos2d-x SDK -- 集成文档

* 1.[下载SDK](#social_cocos2dx)
* 2.[Cocos2d-x集成分享组件](#cocos2dx_integration)
    * 2.1 [Android平台集成](#cocos2dx_integration_android)
    * 2.2 [iOS平台集成](#cocos2dx_integration_ios)
    * 2.3 [在Cocos2d-x游戏中添加分享功能](#cocos2dx_integration_cocos2dx)
* 3.[授权接口使用说明](#cocos2dx_integration_auth)
* 4.[添加更多平台  ( 按需集成 )](#cocos2dx_integration_more_platforms)
	* 4.1 [Android平台集成](#cocos2dx_platforms_integration_android)
	* 4.2 [iOS平台集成](#cocos2dx_platforms_integration_ios)
* 5.[Android混淆问题](#proguard)
* 6.[技术支持](#support)  

------------
     
## 概述
   友盟社会化组件，可以让移动应用快速具备社会化分享、登录、评论、喜欢等功能，并提供实时、全面的社会化数据统计分析服务。   
   本指南将会手把手教你使用友盟社会化组件Cocos2d-x SDK，用5分钟为APP增加新浪微博、微信、QQ空间等国内外十几个主流平台的分享功能。
   该Cocos2d-x SDK目前支持ios和android平台。
 
## 前提   
   如果你之前已经在友盟注册了应用，并获取到了Appkey，可以继续使用它。如果你尚未在友盟[友盟](http://www.umeng.com/)注册开发者账号，需要先注册，注册之后登录你的账号，点击**添加新应用**，填写完应用基本信息后，将进入"下载SDK并添加代码"页面，此页面即可得到Umeng Appkey。进入到"组件"一栏，选择左边的“社会化分享”，然后选择“设置”--“自定义设置”， 将你在各个平台获取到的app id和app secret填写到其中，并且保存。    

<b id=social_cocos2dx></b>
## 1 下载和拷贝Cocos2d-x所需文件 
   首先您需要下载友盟社会化组件 Cocos2d-x SDK (<a href="http://dev.umeng.com/social/cocos2d-x/sdk-download" target="_blank">下载链接</a>),然后将该sdk压缩包解压。
>压缩包目录说明：  
>**1. Cocos2dx**    
	实现cocos2d-x中跨平台分享功能,需拷贝到您项目的Classes文件夹中;    
>**2. Platforms**    
	原生的Android和iOS社会化组件SDK,需要您将库和资源拷贝到对应平台的项目中;    
>**3. doc**    
	Cocos2d-x SDK集成文档。   
	   
   **SDK中默认的添加的平台为新浪微博、腾讯微博、人人网、豆瓣、短信、邮件，其他的平台需要按[添加更多平台  ( 按需集成 )](#cocos2dx_integration_more_platforms)提供的方式手动添加。**
	
<b id=cocos2dx_integration></b>   
## 2 Cocos2d-x集成友盟分享组件
<b id=cocos2dx_integration_android></b>
### 2.1 Android平台集成 
#### 2.1.1 拷贝所需的jar包和资源文件          
  解压Cocos2d-x SDK压缩包，进入到Platforms/Android文件夹下，将'libs'文件夹中的所有jar文件拷贝到工程中的libs目录中，并且将所有jar文件添加到build path中；将Platforms/Android/res目录下的所有文件夹拷贝到你的项目工程res目录下对应的文件夹中, 如图所示 :    
  <img src="http://dev.umeng.com/system/resources/W1siZiIsIjIwMTQvMDUvMjkvMTZfMTZfNDJfMjg1X2NvY29zMmRfeF9kaXIucG5nIl1d/cocos2d-x-dir.png" width="500" height="400" style="border:1px solid black">   
  
#### 2.1.2 拷贝类文件
   将Platforms/Android/controller目录下的com文件夹拷贝到您的Cocos2d-x项目Android平台的src目录下(<font color="red">所有文件的编码为utf-8，如有乱码，请开发者自行进行转码。</font>), 如图所示 :    
     <img src="http://dev.umeng.com/system/images/W1siZiIsIjIwMTQvMDQvMDkvMTVfNTdfMTVfODc2X2NvY29zMmR4X2NvbnRyb2xsZXIucG5nIl1d/cocos2dx-controller.png" width="400" height="160" style="border:1px solid black">        
   在jni/Android.mk中的LOCAL_SRC_FILES下添加如下配置 (注意格式,否则会编译出错) :    
```xml
../../Classes/Cocos2dx/Android/CCUMSocialController.cpp  \
../../Classes/Cocos2dx/ShareButton/UMShareButton.cpp \
../../Classes/Cocos2dx/Common/CCUMSocialSDK.cpp
```   
   
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
        
        <!-- 如果使用，则必须添加以下activity和facebook_app_id
        <activity
            android:name="com.facebook.LoginActivity"
            android:label="@string/app_name"
            android:theme="@android:style/Theme.Translucent.NoTitleBar" />

        <meta-data
            android:name="com.facebook.sdk.ApplicationId"
            android:value="@string/facebook_app_id" />  -->

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
   
#### 2.1.4 添加Android平台的初始化代码
  在您的Cocos2dxActivity子类的onCreate方法下添加如下代码:    
```java         
// this为Cocos2dxActivity类型, 参数2为描述符,可随意修改.
CCUMSocialController.initSocialSDK(this, "com.umeng.social.share");
```   
#### 2.1.5 覆写Cocos2dxActivity子类的onActivityResult方法
   在onActivityResult添加如下代码 : 
```java
// 授权回调    
CCUMSocialController.onActivityResult(requestCode, resultCode, data);    	  
super.onActivityResult(requestCode, resultCode, data);
```   
   完成以上步骤以后，并且您不需要集成分享到ios平台，您就可以到[在Cocos2d-x游戏中添加分享功能](#cocos2dx_integration_cocos2dx)章节添加分享代码到cocos2d-x游戏中。

<b id=cocos2dx_integration_ios></b>  
### 2.2 iOS平台集成   

#### 2.2.1 修改 Xcode 编译选项(cocos2d-x 3.x版本)

使用cocos2d-x 3.x（发行版）版本新建的工程，需要修改应用编译架构，修改方法为：将Xcode中Build Settings的Architectures修改为`$(ARCHS_STANDARD_32_BIT)`，Valid Architectures删除arm64。另外你使用的cocos2d-x的SDK，应该使用带有32位版本的库文件。   

若要编译64位版本应用，可以到[SDK下载页面](http://dev.umeng.com/social/ios/sdk-download)，选择64位包下载。并替换Platforms目录下的iOS文件夹的内容。

**使用cocos2d-x 3.0以下版本新建的工程，默认编译成32位架构，忽略此步骤。**

#### 2.2.2 加入iOS SDK

解压SDK压缩包，将Platforms/iOS文件夹和Cocos2dx文件夹拖入工程目录，并删除Cocos2dx/Android文件夹.   


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

UMSocial_Sdk_Extra_Frameworks 文件夹的目录结构

文件或文件夹|含义
---|---
Wechat|微信
TencentOpenAPI|QQ互联SDK
Facebook|Facebook SDK
LaiWang|来往 SDK
YiXin|易信 SDK

#### 2.2.3 添加下面的系统framework
Security.framework,libiconv.dylib,SystemConfiguration.framework,CoreGraphics.framework，libsqlite3.dylib，CoreTelephony.framework,libstdc++.dylib,libz.dylib,Social.framework,Accounts.framework。

#### 2.2.4 按需设置各个平台的URL Scheme
<table border="1">
  <tr>
    <th> 平台 </th>
    <th>url scheme设置格式</th>
  </tr>
   <tr>
    <td>微信</td>
    <td>微信应用appId，例如“wxd9a39c7122aa6516”,微信详细集成步骤参考<a href="#social_wechat" style="text-decoration:none">微信集成方法</a></td>
  </tr>
   <tr>
    <td>分享到手机QQ、QQ空间</td>
    <td>“QQ”+腾讯QQ互联应用appId转换成十六进制（不足8位前面补0），例如“QQ05FA957C”。生成十六进制方法：在命令行输入<div>echo 'ibase=10;obase=16;您的腾讯QQ互联应用Id'|bc</div>，并在QQ互联后台的URL schema中填入此字符串保持一致，手机QQ详细集成步骤参考<a href="#social_qq" style="text-decoration:none">手机QQ集成方法</a></td>
  </tr>
  <tr>
    <td>单独登录到QQ、QQ空间（不分享）</td>
    <td>“tencent“+腾讯QQ互联应用Id，例如“tencent100308348”</td>
  </tr>
  <tr>
    <td>来往</td>
    <td>Identifier填“Laiwang”，URL Schemes填来往AppId.注意使用来往SDK后，Xcode工程other linker flags需要添加-ObjC参数</td>
  </tr>
  <tr>
    <td>易信</td>
    <td>易信Appkey，例如“yx35664bdff4db42c2b7be1e29390c1a06”</td>
  </tr>
  <tr>
    <td>Facebook</td>
    <td>默认使用iOS自带的Facebook分享framework，在iOS 6以上有效，若要使用我们提供的facebook分享需要设置“fb”+facebook AppID，例如“fb1440390216179601”，详细集成方法见[集成facebook](#social_facebook)</td>
  </tr>
</table> 

#### 2.2.5 在AppDelegate实现系统回调方法
在Xcode工程中的ios文件夹下的AppController.mm文件，实现下面的系统回调

```
#import "UMSocial.h"
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    return [UMSocialSnsService handleOpenURL:url];
}
```
     
   然后您就可以到[在Cocos2d-x游戏中添加分享功能](#cocos2dx_integration_cocos2dx)章节添加分享代码到cocos2d-x游戏中。

<b id=cocos2dx_integration_cocos2dx></b>
#### 2.3 在Cocos2d-x游戏中添加分享功能
   将所需的资源添加到对应的工程以后, 您就可以在cocos2d-x中使用该友盟社会化组件的分享、登录功能了。   
  首先将sdk压缩包下的根目录下的Cocos2dx文件夹拷贝到您的工程的Classes目录下，Cocos2dx包括：   
> * Android文件夹，Android平台的调用实现；   
> * iOS文件夹，iOS平台的调用实现；  
> * Common文件夹，针对Cocos2d-x的统一接口和类型定义 ；     
> * ShareButton文件夹，针对Cocos2d-x封装的分享按钮,点击按钮即可打开分享面板；    

   针对Android平台， 如果开发者需要使用facebook、易信、易信朋友圈、来往、来往动态、twitter、instagram平台则需要到[添加更多平台  ( 按需集成 )](#cocos2dx_integration_more_platforms)章节添加相应的平台。    
   友盟提供了三种方式来方便开发者使用分享功能，示例如下 :    
   ***方式一 :***     
   开发者可以通过UMShareButton类来快速的实现分享功能，UMShareButton是CCMenuItemImage的子类，当用户点击该按钮时将会打开友盟的分享面板。
   集成代码如下 :
```cpp
// 引入相关的头文件
#include "Cocos2dx/Common/CCUMSocialSDK.h"
#include "Cocos2dx/ShareButton/UMShareButton.h"
// 使用友盟命令空间
USING_NS_UM_SOCIAL;
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
    
	// 创建分享按钮, 参数1为按钮正常情况下的图片, 参数2为按钮选中时的图片,参数3为友盟appkey, 参数4为分享回调
	UMShareButton *shareButton = UMShareButton::create("shareNormal.png","shareSelected.png", "你的友盟appkey", share_selector(shareCallback)) ;
	// 显示在友盟分享面板上的平台
    vector<int>* platforms = new vector<int>();
    platforms->push_back(SINA);
    platforms->push_back(RENREN) ;
    platforms->push_back(DOUBAN) ;
    platforms->push_back(QZONE) ;
    platforms->push_back(QQ) ;
    // 设置友盟分享面板上显示的平台
    shareButton->setPlatforms(platforms);
	// 设置文本分享内容
	shareButton->setShareContent("umeng social cocos2d-x sdk.") ;
	// 设置要分享的图片, 图片支持本地图片和url图片, 但是url图片必须以http://或者https://开头
	shareButton->setShareImage("/sdcard/header.jpeg") ;
	// 设置按钮的位置
	shareButton->setPosition(ccp(150, 180));
	// 然后开发者需要将该按钮添加到游戏场景中
    CCMenu* pMenu = CCMenu::create(shareButton, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
	
	// ********************** 设置平台信息 ***************************
	// CCUMSocialSDK *sdk = shareButton->getSocialSDK();
    // sdk->setQQAppIdAndAppKey("设置QQ的app id", "appkey");
    // sdk->setWeiXinAppId("设置微信和朋友圈的app id");
    // sdk->setYiXinAppKey("设置易信和易信朋友圈的app id");
    // sdk->setLaiwangAppInfo("设置来往和来往动态的app id", 
    //					"设置来往和来往动态的app key", "我的应用名");
    // sdk->setFacebookAppId("你的facebook appid");
    // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
    // sdk->setTargetUrl("http://www.umeng.com/social");
    //     // 打开或者关闭log
    // sdk->setLogEnable(true) ;
    // **********************	END	***************************
    
    return true;
}
```     

***方式二 :***    
    开发者可以使用CCUMSocialSDK类来完成分享、授权、删除授权等操作， 实际上UMShareButton就是包装了CCUMSocialSDK以实现相关的功能。具体功能请参考CCUMSocialSDK中的注释。
    开发者可以自行定义某个按钮，然后在该按钮的点击事件中通过CCUMSocialSDK来进行相应的操作，示例代码如下 :   
```cpp
// 引入相关的头文件
#include "Cocos2dx/Common/CCUMSocialSDK.h"
// 使用友盟命令空间
USING_NS_UM_SOCIAL;
// ...... 代码省略


// HelloWorld为cocos2d::CCLayer的子类, shareButtonClick为某个按钮点击事件的处理函数
void HelloWorld::shareButtonClick()
{
	// 获取一个CCUMSocialSDK实例
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("你的友盟appkey");
    // 设置友盟appkey,如果create中设置了不用调用该函数
    // sdk->setAppKey("4eaee02c527015373b000003");
    // **********************	设置平台信息	***************************
    // sdk->setQQAppIdAndAppKey("设置QQ的app id", "appkey");
    // sdk->setWeiXinAppId("设置微信和朋友圈的app id");
    // sdk->setYiXinAppKey("设置易信和易信朋友圈的app id");
    // sdk->setLaiwangAppInfo("设置来往和来往动态的app id", 
    //				"设置来往和来往动态的app key", "我的应用名");
    // sdk->setFacebookAppId("你的facebook appid");
    //     // 打开或者关闭log
    // sdk->setLogEnable(true) ;
    // **********************	END	***************************
    
    // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
    sdk->setTargetUrl("http://www.umeng.com/social");
    // 设置友盟分享面板上显示的平台
    vector<int>* platforms = new vector<int>();
    platforms->push_back(SINA);
    platforms->push_back(RENREN) ;
    platforms->push_back(DOUBAN) ;
    platforms->push_back(QZONE) ;
    platforms->push_back(QQ) ;
	// 设置平台, 在调用分享、授权相关的函数前必须设置SDK支持的平台
	sdk->setPlatforms(platforms) ;

    // 打开分享面板, 注册分享回调, 参数1为分享面板上的平台, 参数2为要分享的文字内容，
    // 参数3为要分享的图片路径(android和IOS的图片地址格式不一致，因此分平台设置), 参数4为分享回调.
   #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    	sdk->openShare("要分享的文字内容", "/sdcard/image.png", share_selector(shareCallback));
	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    	sdk->openShare("要分享的文字内容","share.png", share_selector(shareCallback));
	#endif
}

```      

***方式三 :***    
    开发者也可以自行定义某个按钮，然后在该按钮的点击事件中通过CCUMSocialSDK的directShare函数来进行直接分享到某个平台的操作，该接口为api分享接口，不会弹出分享面板和内容编辑界面，用户授权之后直接分享。示例代码如下 :   
```cpp
// 引入相关的头文件
#include "Cocos2dx/Common/CCUMSocialSDK.h"
// 使用友盟命令空间
USING_NS_UM_SOCIAL;
// ...... 代码省略


// HelloWorld为cocos2d::CCLayer的子类, shareButtonClick为某个按钮点击事件的处理函数
void HelloWorld::shareButtonClick()
{
	// 获取一个CCUMSocialSDK实例
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("你的友盟appkey");
    // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
    sdk->setTargetUrl("http://www.umeng.com/social");   
    // **********************	设置平台信息	***************************
    // sdk->setQQAppIdAndAppKey("设置QQ的app id", "appkey");
    // sdk->setWeiXinAppId("设置微信和朋友圈的app id");
    // sdk->setYiXinAppKey("设置易信和易信朋友圈的app id");
    // sdk->setLaiwangAppInfo("设置来往和来往动态的app id", 
    //				"设置来往和来往动态的app key", "我的应用名");
    // sdk->setFacebookAppId("你的facebook appid");
    //     // 打开或者关闭log
    // sdk->setLogEnable(true) ;
    // **********************	END	***************************

    // 直接分享，参数1为要分享到的目标平台, 参数2为要分享的文字内容, 
    // 参数3为要分享的图片路径(android和IOS的图片地址格式不一致，因此分平台设置), 参数4为分享回调.
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		sdk->directShare(SINA, "要分享的文字内容","/sdcard/image.png", share_selector(shareCallback));
	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    	sdk->directShare(SINA, "要分享的文字内容","image.png", share_selector(shareCallback));
	#endif
```      

***特别说明 :***     
   使用CCUMSocialSDK对象设置各个平台的app id或者app key.CCUMSocialSDK对象可以通过CCUMSocialSDK::create("umeng appkey")函数获取，如果使用UMShareButton可以通过getSocialSDK()函数获取.          
>1.如果集成了QQ或者QQ空间平台,则必须通过CCUMSocialSDK类的setQQAppIdAndAppKey("appid","appkey")函数来设置QQ或者QQ空间的AppId、AppKey;           
>2.如果集成了微信或者微信朋友圈平台,则必须通过CCUMSocialSDK类的setWeiXinAppId("")函数来设置微信或者朋友圈的App id;        
>3.如果集成了易信或者易信朋友圈平台,则必须通过CCUMSocialSDK类的setYiXinAppKey("")函数来设置微信的App key;        
>4.如果集成了来往或者来往动态平台,则必须通过CCUMSocialSDK类的setLaiwangAppInfo("app id ", "app key", "app Name")来设置来往和来往动态的App id、App key、App Name(应用名).
   在设置完平台的app id或者app key之后，需要调用CCUMSocialSDK对象的setPlatforms函数将所需的平台添加到sdk中，这样该平台才会在sdk得到支持。    
   最后,点击对应的按钮则会弹出如下界面 :    
  <img src="http://dev.umeng.com/system/images/W1siZiIsIjIwMTQvMDQvMDkvMTVfNTdfNTVfMjk5X2NvY29zMmR4X29wZW5TaGFyZS5wbmciXV0/cocos2dx-openShare.png" width="450" height="300" style="border:1px solid black">      
         
**分享回调的为如下形式 :**    
   请不要在该回调中更新UI，友盟社会化组件Cocos2d-x SDK不保证在分享回调中更新UI一定会被顺利执行。      
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
          
**微信精确回调使用说明**     
    如果在您的项目中集成了微信或者微信朋友圈，并且您需要准确的分享回调，则需要在AndroidManifest.xml中下注册下面的回调Activity。
```xml
<activity
   android:name=".wxapi.WXEntryActivity"
   android:theme="@android:style/Theme.Translucent.NoTitleBar"
   android:configChanges="keyboardHidden|orientation|screenSize"
   android:exported="true"
   android:screenOrientation="portrait" />
```    
> * 将SDK包中weixin目录下的wxapi文件夹拷贝到您的工程的包目录下，然后修改WXEntryActivity的完整路径即可。例如social_sdk_example的包名为com.umeng.soexample,
因此将wxapi文件夹拷贝到com.umeng.soexample下即可。最终WXEntryActivity的完整路径为com.umeng.soexample.wxapi.WXEntryActivity。     
* 其中分享回调接口SnsPostListener中的onComplete方法的第二个参数代表分享的状态码，当值为200时表示分享成功;其余的值则为分享失败。   


<b id=cocos2dx_integration_auth></b>
### 3 授权接口使用说明
#### 3.1 授权接口说明   
   CCUMSocialSDK类中还提供了授权相关的接口，支持授权的平台有新浪微博、QQ空间、QQ、人人网、豆瓣、腾讯微博、facebook。授权接口使用说明如下 : 
```cpp
CCUMSocialSDK *sdk = CCUMSocialSDK::create("你的友盟appkey");
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
   请不要在该回调中更新UI，友盟社会化组件Cocos2d-x SDK不保证在分享回调中更新UI一定会被顺利执行。    
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
## 4 添加更多平台 ( 按需集成 )
<b id=cocos2dx_platforms_integration_android></b> 
### 4.1 Android平台 

#### 4.1.1 集成来往和来往动态
   添加所需jar和资源，将sdk包中laiwang文件夹下的libs、res目录下的文件拷贝到工程中对应的文件夹中。        
   	通过CCUMSocialSDK类的setLaiwangAppId("")和setLaiwangAppKey()函数来分别设置来往和来往动态的App id、app key，然后在该类的supportPlatfrom函数中找到添加来往或者来往动态平台的代码段，将相应的注释去掉，并且导入(import)所需的类, 示例如下 :    
   ***添加来往平台***       
```java
UMLWHandler umLWHandler = UMLWService.supportLWPlatform(mActivity,
 	LAIWANG_APPID, LAIWANG_APPKEY, TARGET_URL);
umLWHandler.setTitle("友盟社会化分享组件-来往动态");
umLWHandler.setMessageFrom(LAIWANG_APP_NAME);
// 添加来往平台到sdk中
umLWHandler.addToSocialSDK();
```
   
   ***添加来往动态平台***    
```java
UMLWHandler umlwDynamicHandler =
UMLWService.supportLWDynamicPlatform(
		mActivity, LAIWANG_APPID,
LAIWANG_APPKEY, TARGET_URL);
umlwDynamicHandler.setTitle("友盟社会化分享组件-来往");
// 设置消息来源
umlwDynamicHandler.setMessageFrom(LAIWANG_APP_NAME);
// 添加来往动态到sdk中
umlwDynamicHandler.addToSocialSDK();
```   
   
<b id=yixin_platforms></b>
### 4.1.2 集成易信和易信朋友圈
   
   添加所需jar和资源，将sdk包中yixin文件夹下的libs、res目录下的文件拷贝到工程中对应的文件夹中。         
   通过CCUMSocialSDK类的setYiXinAppKey("")函数来设置微信的App key，然后在该类的supportPlatfrom函数中找到添加易信或者易信朋友圈平台的代码段，将相应的注释去掉，并且导入(import)所需的类, 示例如下 :        
   ***添加易信平台***  
```java
UMYXHandler yxHandler = new UMYXHandler(mActivity, YIXIN_APPKEY,
			 false);
yxHandler.setTargetUrl(TARGET_URL);
// 添加易信平台到SDK
yxHandler.addToSocialSDK();
```    

   ***添加易信朋友圈平台***    
```java
UMYXHandler yxHandler = new UMYXHandler(mActivity, YIXIN_APPKEY,
			 true);
yxHandler.setTargetUrl(TARGET_URL);
// 添加易信朋友圈平台到SDK
yxHandler.addToSocialSDK();
```   

**易信精确回调使用说明**    
如果在您的项目中集成了易信或者易信朋友圈，并且您需要准确的分享回调，则需要在AndroidManifest.xml中下注册下面的回调Activity。
```xml
<activity
   android:name=".yxapi.YXEntryActivity"
   android:theme="@android:style/Theme.Translucent.NoTitleBar"
   android:configChanges="keyboardHidden|orientation|screenSize"
   android:exported="true"
   android:screenOrientation="portrait" />
```    
> * 将SDK包中yixin目录下的yxapi文件夹拷贝到您的工程的包目录下，然后修改YXEntryActivity的完整路径即可。例如social_sdk_example的包名为com.umeng.soexample,
因此将yxapi文件夹拷贝到com.umeng.soexample下即可。最终YXEntryActivity的完整路径为com.umeng.soexample.yxapi.YXEntryActivity。     
* 其中分享回调接口SnsPostListener中的onComplete方法的第二个参数代表分享的状态码，当值为200时表示分享成功;其余的值则为分享失败。
      
 <b id=facebook_platforms></b>
### 4.1.3 集成Facebook

   添加所需jar和资源，将sdk包中facebook文件夹下的libs、res目录下的文件拷贝到工程中对应的文件夹中。并且在AndroidManifest.xml中添加facebook相关支持，见上文AndroidManifest.xml。        
   在com.umeng.social.CCUMSocialController中的supportPlatfrom函数中找到添加facebook平台的代码段，将相应的注释去掉，并且导入(import)所需的类, 示例如下 :     
   ***添加Facebook平台***   
```java
UMFacebookHandler mFacebookHandler = new UMFacebookHandler(
			 mActivity, PostType.FEED);
mFacebookHandler.setTargetUrl(TARGET_URL);
// 添加facebook平台 
mFacebookHandler.addToSocialSDK();
```     
      
<b id=instagram_platforms></b>
### 4.1.4 集成Instagram
 
   添加所需jar和资源，将sdk包中instagram文件夹下的libs、res目录下的文件拷贝到工程中对应的文件夹中。         
   在com.umeng.social.CCUMSocialController中的supportPlatfrom函数中找到添加instagram平台的代码段，将相应的注释去掉，并且导入(import)所需的类,示例如下 :     
   ***添加Instagram平台***   
```java
UMInstagramHandler instagramHandler = new UMInstagramHandler(
			 mActivity);
// 添加instagram平台 
instagramHandler.addToSocialSDK();
```      

<b id=cocos2dx_platforms_integration_ios></b> 
### 4.2 iOS平台

iOS提供的包默认已经包含了QQ空间、手机QQ、微信、来往、易信、Facebook、Twitter、Instagram这些平台的库文件。
集成各个平台，只需要分别对各个平台进行设置.各平台的设置代码如下

#### 4.2.1 集成来往和来往动态

集成来往平台需要将Xcode的other linker flag设置为-all_load 

设置应用信息
```
CCUMSocialSDK *sdk = shareButton->getSocialSDK();
sdk->setLaiwangAppInfo("设置来往和来往动态的app id", "设置来往和来往动态的app key", "我的应用名");
```

若不需要集成来往，可以在Xcode中把UMSocial_Sdk_Extra_Frameworks下把LaiWang文件夹删除。并把UmSocialControllerIOS.h 头文件中把宏CC_ShareToLaiWang设置为0。

#### 4.2.2 集成易信和易信动态

设置应用信息
```
CCUMSocialSDK *sdk = shareButton->getSocialSDK();
sdk->setYiXinAppKey("设置易信和易信朋友圈的app id");
```

若不需要集成易信，可以在Xcode中把UMSocial_Sdk_Extra_Frameworks下把YiXin文件夹删除。并把UmSocialControllerIOS.h 头文件中把宏CC_ShareToYiXin设置为0。

#### 4.2.3 集成Facebook

设置应用信息
```
CCUMSocialSDK *sdk = shareButton->getSocialSDK();
sdk->setFacebookAppId("你的facebook appid");
```

若不需要集成Facebook，可以在Xcode中把UMSocial_Sdk_Extra_Frameworks下把Facebook文件夹删除。并把UmSocialControllerIOS.h 头文件中把宏CC_ShareToFacebook设置为0。

#### 4.2.4 集成Twitter

设置应用信息
```
CCUMSocialSDK *sdk = shareButton->getSocialSDK();
sdk->openTwitterForiOS();
```

若不需要集成Twitter，可以在Xcode中把UMSocial_Sdk_Extra_Frameworks下把Twitter文件夹删除。并把UmSocialControllerIOS.h 头文件中把宏CC_ShareToTwitter设置为0。

#### 4.2.4 集成Instagram

设置应用信息
```
CCUMSocialSDK *sdk = shareButton->getSocialSDK();
sdk->openInstagramForiOS();
```

若不需要集成Instagram，可以在Xcode中把UMSocial_Sdk_Extra_Frameworks下把Instagram文件夹删除。并把UmSocialControllerIOS.h 头文件中把宏CC_ShareToInstagram设置为0。


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

请发邮件至social-support@umeng.com。如果您出现的问题和SDK相关，请说明您使用的是Android的SDK或者是iOS的SDK，我们会尽快回复您。
