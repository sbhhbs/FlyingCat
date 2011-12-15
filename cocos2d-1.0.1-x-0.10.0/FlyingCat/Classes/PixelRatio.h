#ifndef __PixelRatio__H__
#define __PixelRatio__H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#define SCREEN_RATIO 2.0f

#endif  // CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#define SCREEN_RATIO 1.0f
// OpenGLView initialized in testsAppDelegate.mm on ios platform, nothing need to do here.

#endif  // CC_PLATFORM_IOS
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define SCREEN_RATIO 1.0f
// Android doesn't need to do anything.

#endif  // CC_PLATFORM_ANDROID

#endif //__PixelRatio__H__