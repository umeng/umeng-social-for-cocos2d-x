/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package com.umeng.game;

import java.io.ByteArrayOutputStream;
import java.util.Random;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.AlertDialog;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.text.TextUtils;
import android.util.Log;
import android.widget.ImageView;
import android.widget.Toast;

import com.umeng.scrshot.adapter.UMBaseAdapter;
import com.umeng.social.CCUMSocialController;
import com.umeng.socialize.bean.SHARE_MEDIA;
import com.umeng.socialize.bean.SocializeEntity;
import com.umeng.socialize.controller.RequestType;
import com.umeng.socialize.controller.UMServiceFactory;
import com.umeng.socialize.controller.UMSocialService;
import com.umeng.socialize.controller.listener.SocializeListeners.SnsPostListener;
import com.umeng.socom.util.BitmapUtils;

public class UmengGame extends Cocos2dxActivity {

	/**
	 * Handler, 用于包装友盟的openShare方法，保证openShare方法在UI线程执行
	 */
	public static Handler mHandler = null;
	/**
	 * 保存当前Activity实例， 静态变量
	 */
	private static Activity mActivity = null;
	/**
	 * 友盟Social SDK实例，整个SDK的Controller
	 */
	private static UMSocialService mController = UMServiceFactory
			.getUMSocialService("com.umeng.cocos2dx", RequestType.SOCIAL);
	//
	// private static UMShakeService mShakeService = UMShakeServiceFactory
	// .getShakeService("com.umeng.cocos2dx");
	/**
	 * 
	 */
	private static final int DELAY = 100;

	private static String mImagePath;

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.cocos2dx.lib.Cocos2dxActivity#onCreate(android.os.Bundle)
	 */
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		mActivity = this;
		mHandler = new Handler(Looper.getMainLooper());
		//
		mController.setShareContent("COCOS2D-X HACKATHON.");

	}

	@Override
	protected void onResume() {
		super.onResume();

		CCUMSocialController.initSocialSDK(mActivity, "com.umeng.social");

		// List<SHARE_MEDIA> platforms = new ArrayList<SHARE_MEDIA>();
		// platforms.add(SHARE_MEDIA.SINA);
		// platforms.add(SHARE_MEDIA.QZONE);
		// mShakeService.registerShakeListender(mActivity, Cocos2dxAdapter,
		// platforms, null);
	}

	@Override
	protected void onStop() {
		super.onStop();

		// mShakeService.unregisterShakeListener(mActivity);
	}

	/**
	 * 
	 */
	private static UMBaseAdapter Cocos2dxAdapter = new UMBaseAdapter() {

		@Override
		public Bitmap getBitmap() {
			mImagePath = getCocos2dxScrShot();
			System.gc();
			Log.d(TAG, "### 图片路径为  : " + mImagePath);
			if (!TextUtils.isEmpty(mImagePath)
					&& (mImagePath.endsWith(".png") || mImagePath
							.endsWith(".jpg"))) {
				Bitmap scrShot = BitmapUtils.getBitmapFromFile(mImagePath, 200,
						300);
				mImagePath = "";
				showDialog(scrShot);
				return compressBitmap(scrShot);
			} else {
				return null;
			}
		}

		/**
		 * 使用Vitamio获取截图，分享到社交平台时会出现条纹，目前不知道是什么原因. 如果您的截图分享没有任何问题， 则不需要做这一步.
		 * 
		 * @param bmp
		 * @return
		 */
		@SuppressLint("NewApi")
		private Bitmap compressBitmap(Bitmap bmp) {
			if (bmp == null) {
				return null;
			}

			// 将Vitamio获取截图压缩到outStream
			ByteArrayOutputStream outStream = new ByteArrayOutputStream();
			// 考虑到用户的网络速度,建议将图片压缩至70kb以下，保证图片上传的成功率.
			byte[] data = outStream.toByteArray();
			if (data != null && data.length > 0) {
				Log.d(TAG, "### 图片大小 : " + data.length / 1024 + " KB");
			}

			bmp.compress(CompressFormat.JPEG, 80, outStream);
			// if (bmp != null && !bmp.isRecycled()) {
			// bmp.recycle();
			// bmp = null;
			// }

			// 再从outStream解析一张图片
			Bitmap scrshot = BitmapFactory
					.decodeByteArray(data, 0, data.length);

			return scrshot;
		}
	};

	private static void showDialog(Bitmap bmp) {
		ImageView imageView = new ImageView(mActivity);
		imageView.setImageBitmap(bmp);
		AlertDialog dialog = new AlertDialog.Builder(mActivity)
				.setTitle("Title").setView(imageView).create();
		dialog.show();
	}

	/**
	 * 打开分享面板
	 */
	public static void openShare() {
		mHandler.postDelayed(new Runnable() {

			@Override
			public void run() {
				mController.registerListener(mPostListener);
				// 打开友盟的分享平台选择面板
				mController.openShare(mActivity, false);
			}
		}, DELAY);
	}

	/**
	 * 
	 */
	public static SnsPostListener mPostListener = new SnsPostListener() {

		@Override
		public void onStart() {
			onNativeStart();
		}

		@Override
		public void onComplete(SHARE_MEDIA platform, int eCode,
				SocializeEntity entity) {
			Toast.makeText(mActivity, platform + ", " + eCode,
					Toast.LENGTH_SHORT).show();
			onNativeComplete(platform.toString(), eCode, entity.mDescriptor);
		}

	};

	public native static void onNativeStart();

	public native static void onNativeComplete(String platform, int eCode,
			String descriptor);

	private native static String getCocos2dxScrShot();

	/**
	 * 
	 * @param imgPath
	 */
	public static void setImagePath(String imgPath) {
		mImagePath = imgPath;
		Log.d("", "#### 设置Cocos2d-x截屏路径 : " + imgPath);
	}

	/*
	 * * (non-Javadoc)
	 * 
	 * @see org.cocos2dx.lib.Cocos2dxActivity#onCreateView()
	 */
	public Cocos2dxGLSurfaceView onCreateView() {
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		// UmengGame should create stencil buffer
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

		return glSurfaceView;
	}

	/**
	 * 
	 */
	public int cppCallJava(String className) {
		Log.d("", "##### This is Cpp Call Java's Member Method.     CPP : "
				+ className);
		return new Random().nextInt(100);
	}

	/**
	 * load lib
	 */
	static {
		System.loadLibrary("cocos2dcpp");
	}
}
