package com.umeng.social;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.text.TextUtils;

import com.umeng.socialize.bean.CustomPlatform;
import com.umeng.socialize.bean.SHARE_MEDIA;
import com.umeng.socialize.bean.SocializeConfig;
import com.umeng.socialize.bean.SocializeEntity;
import com.umeng.socialize.bean.StatusCode;
import com.umeng.socialize.common.SocializeConstants;
import com.umeng.socialize.controller.RequestType;
import com.umeng.socialize.controller.UMFacebookHandler;
import com.umeng.socialize.controller.UMFacebookHandler.PostType;
import com.umeng.socialize.controller.UMInstagramHandler;
import com.umeng.socialize.controller.UMServiceFactory;
import com.umeng.socialize.controller.UMSocialService;
import com.umeng.socialize.controller.UMYXHandler;
import com.umeng.socialize.controller.listener.SocializeListeners.SnsPostListener;
import com.umeng.socialize.controller.listener.SocializeListeners.SocializeClientListener;
import com.umeng.socialize.controller.listener.SocializeListeners.UMAuthListener;
import com.umeng.socialize.db.OauthHelper;
import com.umeng.socialize.exception.SocializeException;
import com.umeng.socialize.media.UMImage;
import com.umeng.socialize.net.utils.SocializeNetUtils;
import com.umeng.socialize.sso.QZoneSsoHandler;
import com.umeng.socialize.sso.UMSsoHandler;
import com.umeng.socom.Log;

/**
 * 友盟Social Android SDK的控制器, cocos2d-x sdk 通过jni代码调用相关的静态函数实现对应的功能.
 * 该sdk目前提供的功能有授权、分享(打开分享面板来分享、底层api分享)、删除授权、判断某个平台是否授权、设置文字分享内容、设置图片分享内容的功能,
 * 并且将结果回调给cocos2d-x sdk.
 * 
 * @author mrsimple
 * 
 */
public class CCUMSocialController {

	/**
	 * 友盟社会化组件控制器
	 */
	private static UMSocialService mController;
	/**
	 * Social SDK 配置类, 单例
	 */
	private static SocializeConfig mSocializeConfig = SocializeConfig
			.getSocializeConfig();
	// Cocos2dxActivity对象
	private static Cocos2dxActivity mActivity;
	/**
	 * log tag
	 */
	private static final String TAG = CCUMSocialController.class
			.getSimpleName();

	/**
	 * 主线程的消息Handler
	 */
	private static Handler mSDKHandler = new Handler(Looper.getMainLooper());;
	private static final int DELAY_MS = 50;
	private static String DESCRIPTOR;

	// ******* 以下字段的调用都在supportPlatfrom函数中 *********
	/**
	 * QQ和QQ空间app id
	 */
	private static String QQ_QZONE_APP_ID = "";
	/**
	 * QQ和QQ空间app key
	 */
	private static String QQ_QZONE_APP_KEY = "";

	/**
	 * 微信或者微信朋友圈 app id
	 */
	private static String WEIXIN_APP_ID = "";

	/**
	 * facebook app id
	 */
	private static String FACEBOOK_APP_ID = "";
	/**
	 * 易信或者易信朋友圈app id, 需要添加易信或者易信朋友圈平台的支持, 请参考线上文档
	 */
	private static String YIXIN_APPKEY = "";
	/**
	 * 来往和来往动态的app id, 需要添加来往或者来往动态平台的支持, 请参考线上文档
	 */
	private static String LAIWANG_APPID = "";
	/**
	 * 来往和来往动态的app key, 需要添加来往或者来往动态平台的支持, 请参考线上文档
	 */
	private static String LAIWANG_APPKEY = "";
	/**
	 * 当前应用名称,用于显示在来往分享来源上
	 */
	private static String LAIWANG_APP_NAME = "";
	/**
	 * 在某些平台的分享中， 希望用户点击该分享内容跳转到的目标平台, 一般为app的官网或者下载地址
	 */
	private static String TARGET_URL = "http://www.umeng.com/social";

	/**
	 * 初始化SDK
	 * 
	 * @param activity
	 *            游戏的Cocos2dxActivity类型
	 * @param descriptor
	 *            SDK的字符串描述符
	 */
	public static void initSocialSDK(Activity activity, String descriptor) {

		if (mController == null) {
			synchronized (CCUMSocialController.class) {
				if (mController == null) {
					DESCRIPTOR = descriptor;
					mController = UMServiceFactory.getUMSocialService(
							DESCRIPTOR, RequestType.SOCIAL);
					mSocializeConfig = mController.getConfig();
				}
			}
		}

		if (activity instanceof Cocos2dxActivity) {
			mActivity = (Cocos2dxActivity) activity;
		} else {
			throw new IllegalArgumentException(
					"initSocialSDK函数的activity参数必须设置为Cocos2dxActivity类型, 且不为null. ");
		}
		// mController.getConfig().closeToast();
	}

	/**
	 * 授权回调
	 * 
	 * @param requestCode
	 * @param resultCode
	 * @param data
	 */
	public static void onActivityResult(int requestCode, int resultCode,
			Intent data) {
		UMSsoHandler ssoHandler = mSocializeConfig.getSsoHandler(requestCode);
		if (ssoHandler != null) {
			ssoHandler.authorizeCallBack(requestCode, resultCode, data);
		}
	}

	/**
	 * 授权某个平台
	 * 
	 * @param platform
	 *            授权平台的字符串表示
	 */
	public static void doAuthorize(final int platform) {
		// 检测平台的有效性
		if (!isPlatformValid(platform)) {
			return;
		}

		checkActivity();

		// 在UI线程执行授权操作
		runOnMainThread(new Runnable() {

			@Override
			public void run() {
				mController.doOauthVerify(mActivity, getPlatform(platform),
						mAuthListener);
			}
		});

	}

	/**
	 * 删除平台授权
	 * 
	 * @param platform
	 *            授权平台的字符串表示
	 */
	public static void deleteAuthorization(final int platform) {

		// 检测平台的有效性
		if (!isPlatformValid(platform)) {
			return;
		}

		checkActivity();

		// 在UI线程执行授权操作
		runOnMainThread(new Runnable() {

			@Override
			public void run() {
				// 删除授权
				mController.deleteOauth(mActivity, getPlatform(platform),
						new SocializeClientListener() {

							@Override
							public void onStart() {

							}

							@Override
							public void onComplete(final int status,
									SocializeEntity entity) {
								// 运行在gl线程
								runOnOpenGLThread(new Runnable() {

									@Override
									public void run() {
										// 删除授权的回调, 开发者可以通过字符串来判断
										OnAuthorizeComplete(platform, status,
												new String[] { "deleteOauth" });
									}
								});

							}
						});
			}
		});

		Log.d(TAG, "@@@@ deleteAuthorization");

	}

	/**
	 * 打开分享面板
	 * 
	 * @param registerCallback
	 *            是否注册回调接口
	 */
	public static void openShare() {
		// 注册回调接口, 默认将分享回调注册要sdk
		mController.registerListener(mSocialShareListener);

		checkActivity();

		// 在UI线程执行打开分享面板操作
		runOnMainThread(new Runnable() {
			@Override
			public void run() {
				// 打开分享面板
				mController.openShare(mActivity, false);
			}
		});

		Log.d(TAG, "@@@@ openShare");

	}

	/**
	 * 直接分享到某个平台, 不打开分享面板, 直接底层分享
	 * 
	 * @param platform
	 *            平台对应的字符串
	 */
	public static void directShare(final int platform) {

		// 检测平台的有效性
		if (!isPlatformValid(platform)) {
			return;
		}

		checkActivity();

		// 在UI线程执行底层分享操作
		runOnMainThread(new Runnable() {

			@Override
			public void run() {
				mController.directShare(mActivity, getPlatform(platform),
						mSocialShareListener);
			}
		});

		Log.d(TAG, "@@@@ directShare");
	}

	/**
	 * 判断某个平台是否授权
	 * 
	 * @param platform
	 *            平台的字符串表示
	 * @return 返回true则表示该平台已经授权, 否则为未授权.
	 */
	public static boolean isAuthorized(int platform) {
		SHARE_MEDIA target = getPlatform(platform);
		if (target != null && target != SHARE_MEDIA.GENERIC) {
			return OauthHelper.isAuthenticated(mActivity, target);
		}

		Log.d(TAG, "@@@@ isAuthorized");
		return false;

	}

	/**
	 * 设置友盟的app key, 也可以通过manifest指定
	 * 
	 * @param text
	 */
	public static void setUmengAppkey(String appkey) {
		Log.d(TAG, "#### 设置umeng appkey :" + appkey);
		if (!TextUtils.isEmpty(appkey)) {
			SocializeConstants.APPKEY = appkey;
		}
	}

	/**
	 * 设置要分享的文字内容
	 * 
	 * @param text
	 */
	public static void setShareContent(String text) {
		Log.d(TAG, "#### 设置分享文字内容 :" + text);
		mController.setShareContent(text);
	}

	/**
	 * 设置要分享的图片路径或者url
	 * 
	 * @param imgName
	 *            图片的本地路径或者url, 如果是url则必须以http://或者https://开头
	 */
	public static void setShareImageName(String imgName) {
		Log.d(TAG, "#### 设置图片路径 :" + imgName);
		// 网络图片
		if (imgName.startsWith("http://") || imgName.startsWith("https://")) {
			mController.setShareMedia(new UMImage(mActivity, imgName));
		} else {
			// 本地图片
			File imgFile = new File(imgName);
			if (!imgFile.exists()) {
				Log.e(TAG, "### 要分享的本地图片不存在");
				mController.setShareMedia(null);
			} else {
				mController.setShareMedia(new UMImage(mActivity, imgFile));
			}
		}
	}

	/**
	 * 设置是否开启log
	 * 
	 * @param flag
	 */
	protected static void setAndroidLogEnable(boolean flag) {
		Log.LOG = flag;
		Log.e(TAG, "### 是否开启log : " + Log.LOG);
	}

	/**
	 * 初始化Cocos2d-x SDK版本信息
	 */
	protected static void initCocos2dxSDKInfo(String type, String sdkVersion) {
		Log.d(TAG, "### initCocos2dxSDKInfo, type = " + type + ", version = "
				+ sdkVersion);
		// 设置cocos2dx sdk版本号
		mController.getEntity().setAdapterSDKInfo(type, sdkVersion);
	}

	/**
	 * 设置用户点击某条分享时跳转到的目标页面
	 * 
	 * @param targetUrl
	 */
	public static void setTargetUrl(String targetUrl) {
		if (!TextUtils.isEmpty(targetUrl)
				&& SocializeNetUtils.startWithHttp(targetUrl)) {
			TARGET_URL = targetUrl;
		}
		Log.d(TAG, "### target url : " + TARGET_URL);
	}

	/**
	 * 要支持的新平台, 可以添加的平台主要有微信,微信朋友圈,QQ,易信,来往等. 具体参考线上文档
	 * http://dev.umeng.com/social/android /share/specific-integration
	 * 
	 * @param platform
	 *            平台的字符串表示
	 * @param appkey
	 *            平台的appkey或者称为appid
	 * @param targetUrl
	 *            用户点击分享内容时跳转的页面, 一般为APP主页或者下载页
	 */
	public static void supportPlatfrom(int platform) {
		final SHARE_MEDIA target = getPlatform(platform);
		// 判断target
		if (target == null || target == SHARE_MEDIA.GENERIC) {
			return;
		}
		checkActivity();

		if (target == SHARE_MEDIA.QQ) {
			// 添加QQ平台支持
			mSocializeConfig.supportQQPlatform(mActivity, QQ_QZONE_APP_ID,
					QQ_QZONE_APP_KEY, TARGET_URL);
		} else if (target == SHARE_MEDIA.QZONE) {
			// Social Android sdk 3.3.6 及其以后的版本, 添加QQ空间的支持方式
			mSocializeConfig.setSsoHandler(new QZoneSsoHandler(mActivity,
					QQ_QZONE_APP_ID, QQ_QZONE_APP_KEY));
			QZoneSsoHandler.setTargetUrl(TARGET_URL);
			// Social Android sdk 3.3.6之前的版本添加QQ空间的支持方式
			// mSocializeConfig.setSsoHandler(new
			// QZoneSsoHandler(mActivity));
		} else if (target == SHARE_MEDIA.WEIXIN) {
			// 微信平台
			mSocializeConfig.supportWXPlatform(mActivity, WEIXIN_APP_ID,
					TARGET_URL);
		} else if (target == SHARE_MEDIA.WEIXIN_CIRCLE) {
			// 微信朋友圈平台
			mSocializeConfig.supportWXCirclePlatform(mActivity, WEIXIN_APP_ID,
					TARGET_URL);
		} else if (target == SHARE_MEDIA.YIXIN) {
			// 创建易信的handler, 参数2为你的app id, 参数3为是否是易信朋友圈平台, false为易信,
			// true为易信朋友圈,
//			UMYXHandler yxHandler = new UMYXHandler(mActivity, YIXIN_APPKEY,
//					false);
//			yxHandler.setTargetUrl(TARGET_URL);
//			// 添加易信平台到SDK
//			yxHandler.addToSocialSDK();

		} else if (target == SHARE_MEDIA.YIXIN_CIRCLE) {
			// 创建易信的handler, 参数2为你的app id, 参数3为是否是易信朋友圈平台, false为易信,
			// true为易信朋友圈,
//			UMYXHandler yxHandler = new UMYXHandler(mActivity, YIXIN_APPKEY,
//					true);
//			yxHandler.setTargetUrl(TARGET_URL);
//			// 添加易信朋友圈平台到SDK
//			yxHandler.addToSocialSDK();
		} else if (target == SHARE_MEDIA.LAIWANG) {
			// 添加来往平台的支持
			// UMLWHandler umLWHandler =
			// UMLWService.supportLWPlatform(mActivity,
			// LAIWANG_APPID, LAIWANG_APPKEY, TARGET_URL);
			// umLWHandler.setTitle("友盟社会化分享组件-来往动态");
			// umLWHandler.setMessageFrom(LAIWANG_APP_NAME);
			// umLWHandler.addToSocialSDK();
		} else if (target == SHARE_MEDIA.LAIWANG_DYNAMIC) {
			// 添加来往动态平台的支持
			// UMLWHandler umlwDynamicHandler = UMLWService
			// .supportLWDynamicPlatform(mActivity, LAIWANG_APPID,
			// LAIWANG_APPKEY, TARGET_URL);
			// umlwDynamicHandler.setTitle("友盟社会化分享组件-来往");
			// // 设置消息来源
			// umlwDynamicHandler.setMessageFrom(LAIWANG_APP_NAME);
			// umlwDynamicHandler.addToSocialSDK();
		} else if (target == SHARE_MEDIA.FACEBOOK) {
			// facebook的支持
//			UMFacebookHandler mFacebookHandler = new UMFacebookHandler(
//					mActivity, FACEBOOK_APP_ID, PostType.FEED);
//			mFacebookHandler.setTargetUrl(TARGET_URL);
//			mFacebookHandler.addToSocialSDK();
		} else if (target == SHARE_MEDIA.INSTAGRAM) {
			// 构建Instagram的Handler
//			UMInstagramHandler instagramHandler = new UMInstagramHandler(
//					mActivity);
//			instagramHandler.addToSocialSDK();
		} else if (target == SHARE_MEDIA.TWITTER) {
			mSocializeConfig.supportAppPlatform(mActivity, target, DESCRIPTOR,
					true);
		} else if (target == SHARE_MEDIA.GOOGLEPLUS) {
			mSocializeConfig.supportAppPlatform(mActivity, target, DESCRIPTOR,
					true);
		} else {
			Log.e(TAG,
					target
							+ "平台暂不支持该集成方式, 请参考 : http://dev.umeng.com/social/android /share/specific-integration");
		}

		Log.d(TAG, "@@@@ supportPlatfrom");

	}

	/**
	 * 设置平台顺序, 没有的平台则添加, 内置的但是没有给出的则移除.
	 * 
	 * @param platforms
	 *            平台的顺序数组
	 */
	public static void setPlatforms(final int[] platforms) {

		// 运行在主线程
		runOnMainThread(new Runnable() {

			@Override
			public void run() {
				if (platforms != null && platforms.length > 0) {
					int length = platforms.length;
					//
					List<SHARE_MEDIA> cacheList = new ArrayList<SHARE_MEDIA>();
					// 迭代
					for (int i = 0; i < length; i++) {
						int index = platforms[i];
						SHARE_MEDIA target = getPlatform(index);
						Log.d(TAG, "### 平台 " + target);
						if (target != null && target != SHARE_MEDIA.GENERIC) {
							// 如果没有添加到SDK则添加到里面, 支持的平台有QQ,微信,微信朋友圈
							// QQ空间为内置平台, 但是它必须使用客户端进行授权.
							if (!isPlatformConfiged(target)
									|| target == SHARE_MEDIA.QZONE) {
								supportPlatfrom(index);
							}
							// 先将有效的平台缓存到列表中, 最后再转换为数组
							cacheList.add(target);
						}
					}

					SHARE_MEDIA[] platformsMedias = new SHARE_MEDIA[cacheList
							.size()];
					cacheList.toArray(platformsMedias);

					// 设置平台
					mSocializeConfig.setPlatforms(platformsMedias);
					// 设置显示顺序
					mSocializeConfig.setPlatformOrder(platformsMedias);
				}
			}
		});

	}

	/**
	 * 平台是否配置在SDK了
	 * 
	 * @param target
	 * @return
	 */
	private static boolean isPlatformConfiged(SHARE_MEDIA target) {
		// 内置平台
		List<SHARE_MEDIA> internalList = mSocializeConfig.getPlatforms();
		// 如果是内置平台, 找到以后直接返回
		if (internalList.contains(target)) {
			return true;
		}

		// 自定义平台
		List<CustomPlatform> customPlatforms = mSocializeConfig
				.getCustomPlatforms();
		// 在自定义平台查找
		for (CustomPlatform cs : customPlatforms) {
			if (cs != null && cs.mKeyword.equals(target.toString())) {
				return true;
			}
		}
		return false;
	}

	/**
	 * 使得runnable中的代码运行在opengl线程, 即cocos2d-x的opengl线程
	 * 
	 * @param runnable
	 */
	private static void runOnOpenGLThread(Runnable runnable) {
		if (mActivity != null) {
			// Cocos2dxGLSurfaceView.getInstance().queueEvent(runnable);
			mActivity.runOnGLThread(runnable);
		}
	}

	/**
	 * 将操作封装在Runnable中, 使之运行在Android主线程
	 * 
	 * @param runnable
	 */
	private static void runOnMainThread(Runnable runnable) {
		mSDKHandler.postDelayed(runnable, DELAY_MS);
	}

	/**
	 * 
	 * @param platform
	 *            要检测的平台
	 * @return
	 */
	private static boolean isPlatformValid(int platform) {
		final SHARE_MEDIA target = getPlatform(platform);
		if (target == null || target == SHARE_MEDIA.GENERIC) {
			Log.e(TAG, "### 设置的目标平台无效.   platform = " + target);
			return false;
		}
		return true;
	}

	/**
	 * 设置QQ和QQ空间的app id
	 * 
	 * @param appid
	 */
	public static void setQQAndQzoneAppIdWithAppKey(String appid, String appKey) {
		QQ_QZONE_APP_ID = appid;
		QQ_QZONE_APP_KEY = appKey;
		Log.d(TAG, "### QQ or qzone app id = " + appid + ", app key = "
				+ appKey);
	}

	/**
	 * 设置微信和微信朋友圈的app id
	 * 
	 * @param appid
	 */
	public static void setWeiXinAppId(String appid) {
		WEIXIN_APP_ID = appid;
		Log.d(TAG, "### 微信 app id = " + appid);
	}

	/**
	 * 设置facebook app id
	 * 
	 * @param appid
	 */
	public static void setFacebookAppId(String appid) {
		FACEBOOK_APP_ID = appid;
		Log.d(TAG, "### facebook appid = " + appid);
	}

	/**
	 * 设置易信和易信朋友圈的app id
	 * 
	 * @param appid
	 */
	public static void setYiXinAppKey(String appid) {
		YIXIN_APPKEY = appid;
		Log.d(TAG, "### 易信 app id = " + appid);
	}

	/**
	 * 设置来往和来往动态的app id
	 * 
	 * @param appid
	 */
	public static void setLaiwangAppId(String appid) {
		LAIWANG_APPID = appid;
		Log.d(TAG, "### 来往 app id = " + appid);
	}

	/**
	 * 设置来往和来往动态的app key
	 * 
	 * @param appid
	 */
	public static void setLaiwangAppKey(String appkey) {
		LAIWANG_APPKEY = appkey;
		Log.d(TAG, "### 来往 app key = " + appkey);
	}

	/**
	 * 设置来往和来往动态的app name
	 * 
	 * @param appName
	 */
	public static void setLaiwangAppName(String appName) {
		LAIWANG_APP_NAME = appName;
		Log.d(TAG, "### 来往 app name = " + appName);
	}

	/**
	 * 检查mActivity的合法性
	 */
	private static void checkActivity() {
		assert mActivity != null : "在CCUMSocialController类中, mActivity为null.";
	}

	/**
	 * 清空SDK
	 */
	public static void cleanup() {
		mController = null;
		mSDKHandler = null;
		mActivity = null;
		Log.d(TAG, "@@@@ cleanup");
	}

	/*******************************************************************************
	 * 授权回调接口, 会调用native层对应的回调方法, 开发者可以在Java或者native层进行相应的处理
	 ******************************************************************************/
	private static UMAuthListener mAuthListener = new UMAuthListener() {

		@Override
		public void onStart(final SHARE_MEDIA platform) {
			// 运行在gl线程
			runOnOpenGLThread(new Runnable() {

				@Override
				public void run() {
					OnAuthorizeStart(getPlatformInt(platform));
				}
			});

		}

		@Override
		public void onError(final SocializeException e,
				final SHARE_MEDIA platform) {

			// 运行在gl线程
			runOnOpenGLThread(new Runnable() {

				@Override
				public void run() {
					OnAuthorizeComplete(getPlatformInt(platform), 0,
							new String[] { e.getLocalizedMessage() });
				}
			});
		}

		@Override
		public void onComplete(final Bundle value, final SHARE_MEDIA platform) {

			// 运行在gl线程
			runOnOpenGLThread(new Runnable() {

				@Override
				public void run() {
					OnAuthorizeComplete(getPlatformInt(platform),
							StatusCode.ST_CODE_SUCCESSED, getAuthData(value));
				}
			});
		}

		@Override
		public void onCancel(final SHARE_MEDIA platform) {
			// 运行在gl线程
			runOnOpenGLThread(new Runnable() {

				@Override
				public void run() {
					OnAuthorizeComplete(getPlatformInt(platform), -1,
							new String[] { "cancel" });
				}
			});

		}

		/**
		 * 
		 * @param data
		 *            授权的数据
		 * @return 如果含有access_token则获取access_token和过期时间, 传递到native层
		 */
		private String[] getAuthData(Bundle data) {
			if (data != null
					&& (data.containsKey("access_token") || data
							.containsKey("access_secret"))) {
				String[] authData = new String[3];
				// 有的字段为secret
				if (data.containsKey("access_secret")) {
					authData[0] = data.getString("access_secret");
				} else {
					authData[0] = data.getString("access_token");
				}
				if (data.containsKey("uid")) {
					authData[1] = data.getString("uid");
				} else {
					authData[1] = "";
				}

				return authData;
			} else {
				return new String[] {};
			}
		}
	};

	/**
	 * 回调授权的OnStart方法到native层
	 */
	private native static void OnAuthorizeStart(int platform);

	/**
	 * 回调授权的onComplete方法到native层
	 * 
	 * @param value
	 *            授权信息, 包含token等, 包含access_token, 过期时间expires_in
	 * @param platform
	 *            平台
	 */
	private native static void OnAuthorizeComplete(int platform, int stCode,
			String[] value);

	/******************************************************************************
	 * 分享回调接口,会调用native层对应的回调方法, 开发者可以在Java或者native层进行相应的处理
	 *****************************************************************************/
	private static SnsPostListener mSocialShareListener = new SnsPostListener() {

		/*
		 * 分享开始 (non-Javadoc)
		 * 
		 * @see com.umeng.socialize.controller.listener.SocializeListeners.
		 * SnsPostListener#onStart()
		 */
		@Override
		public void onStart() {
			runOnOpenGLThread(new Runnable() {

				@Override
				public void run() {
					OnShareStart();
				}
			});

		}

		/*
		 * 分享完成 (non-Javadoc)
		 * 
		 * @see com.umeng.socialize.controller.listener.SocializeListeners.
		 * SnsPostListener#onComplete(com.umeng.socialize.bean.SHARE_MEDIA, int,
		 * com.umeng.socialize.bean.SocializeEntity)
		 */
		@Override
		public void onComplete(final SHARE_MEDIA platform, final int eCode,
				final SocializeEntity entity) {
			runOnOpenGLThread(new Runnable() {

				@Override
				public void run() {
					OnShareComplete(getPlatformInt(platform), eCode,
							entity.mDescriptor);
				}
			});

		}
	};

	/**
	 * 回调分享的OnStart方法到native层
	 */
	private native static void OnShareStart();

	/**
	 * 回调分享的onComplete方法到native层
	 * 
	 * @param platform
	 *            平台
	 * @param eCode
	 *            错误码, 200为授权成功
	 * @param entity
	 *            UMSocialService的属性容器
	 */
	private native static void OnShareComplete(int platform, int eCode,
			String descriptor);

	/**
	 * 通过整型获取对应的平台, C++中使用enum常量来代表平台
	 * 
	 * @param location
	 * @return
	 */
	private static SHARE_MEDIA getPlatform(int location) {
		int length = mPlatformsList.size();
		if (location < 0 || location >= length) {
			return null;
		}
		return mPlatformsList.get(location);
	}

	/**
	 * 获取平台对应的整型号码
	 * 
	 * @param platform
	 *            对应的平台
	 * @return the index of the first occurrence of the object or -1 if the
	 *         object was not found.
	 */
	private static int getPlatformInt(SHARE_MEDIA platform) {
		return mPlatformsList.indexOf(platform);
	}

	/*
	 * 
	 */
	private static List<SHARE_MEDIA> mPlatformsList = new ArrayList<SHARE_MEDIA>();
	/*
	 * 
	 */
	static {
		mPlatformsList.add(0, SHARE_MEDIA.SINA);
		mPlatformsList.add(1, SHARE_MEDIA.WEIXIN);
		mPlatformsList.add(2, SHARE_MEDIA.WEIXIN_CIRCLE);
		mPlatformsList.add(3, SHARE_MEDIA.QQ);
		mPlatformsList.add(4, SHARE_MEDIA.QZONE);
		mPlatformsList.add(5, SHARE_MEDIA.RENREN);
		mPlatformsList.add(6, SHARE_MEDIA.DOUBAN);
		mPlatformsList.add(7, SHARE_MEDIA.LAIWANG);
		mPlatformsList.add(8, SHARE_MEDIA.LAIWANG_DYNAMIC);
		mPlatformsList.add(9, SHARE_MEDIA.YIXIN);
		mPlatformsList.add(10, SHARE_MEDIA.YIXIN_CIRCLE);
		mPlatformsList.add(11, SHARE_MEDIA.FACEBOOK);
		mPlatformsList.add(12, SHARE_MEDIA.TWITTER);
		mPlatformsList.add(13, SHARE_MEDIA.INSTAGRAM);
		mPlatformsList.add(14, SHARE_MEDIA.SMS);
		mPlatformsList.add(15, SHARE_MEDIA.EMAIL);
		mPlatformsList.add(16, SHARE_MEDIA.TENCENT);
	}

}
