//
//  UmSocialControllerIOS.h
//  UmengGame
//
//  Created by 张梓琦 on 14-3-16.
//
//

#ifndef __UmengGame__UmSocialControllerIOS__
#define __UmengGame__UmSocialControllerIOS__

#include "CCUMTypeDef.h"
#include <string>
#include <vector>

using namespace std;

class UmSocialControllerIOS {
public:
    static void setAppKey(const char* appKey);
    static void authorize(int platform, AuthEventHandler callback);
    static void deleteAuthorization(int platform, AuthEventHandler callback);
    static bool isAuthorized(int platform);
    static void openShareWithImagePath(vector<int>* platform, const char* text, const char* imagePath, ShareEventHandler callback);
    static void directShare(const char* text, const char* imagePath, int platform, ShareEventHandler callback);
    
private:
    static string m_appKey;
};

#endif /* defined(__UmengGame__UmSocialControllerIOS__) */
