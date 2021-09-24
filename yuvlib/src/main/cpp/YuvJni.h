#include <jni.h>

//
// Created by Hello on 2021/9/24.
//

#ifndef TDYLIB_YUVJNI_H
#define TDYLIB_YUVJNI_H

#define YUV_JNI_METHOD(METHOD_NAME) Java_com_example_yuvlib_YUVUtil_##METHOD_NAME
extern "C" {
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertRGB24ToARGB)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertARGBMacToI420)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertRGB24ToI420)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertUYVYToI420)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertYUY2ToI420)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertYV12ToI420)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertNV12ToI420)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertNV12ToI420AndRotate)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint,jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertNV12ToRGB565)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertNV21ToBitmap)(JNIEnv *, jclass , jbyteArray ,jobject , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertNV21ToI420AndRotate)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertNV21ToRGB565)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToNV12)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToNV12AndRotate)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToNV21)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToNV21AndRotate)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToRGB24)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToARGB)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToARGBMac)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToRGBAMac)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint,jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToRGBA)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToRGBAIPhone)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToARGB4444)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToRGB565)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToRGB565Android)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToARGB1555)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToYUY2)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToUYVY)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToYV12)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(convertI420ToBitmap)(JNIEnv *, jclass , jbyteArray ,jobject , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(copyI420)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(cropI420)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint ,jint,jint,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(mirrorI420)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint  );
JNIEXPORT void JNICALL YUV_JNI_METHOD(mirrorI420upDown)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(mirrorI420LeftRight)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );
JNIEXPORT void JNICALL YUV_JNI_METHOD(scaleI420)(JNIEnv *, jclass , jbyteArray , jbyteArray ,jint , jint , jint , jint ,jint ) ;
JNIEXPORT void JNICALL YUV_JNI_METHOD(rotateI420)(JNIEnv *, jclass , jbyteArray ,jbyteArray , jint , jint ,jint );


}


#endif //TDYLIB_YUVJNI_H
