//
// Created by Hello on 2021/9/24.
//

#include "YuvJni.h"
extern "C" {
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertRGB24ToARGB(JNIEnv *env, jclass clazz, jbyteArray src,
                                                   jbyteArray dst, jint width, jint height,
                                                   jint dst_stride) {
    // TODO: implement convertRGB24ToARGB()
}

}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertARGBToI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {
    // TODO: implement convertARGBToI420()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertRGB24ToI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                                   jbyteArray dst, jint width, jint height) {
    // TODO: implement convertRGB24ToI420()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertUYVYToI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {
    // TODO: implement convertUYVYToI420()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertYUY2ToI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {
    // TODO: implement convertYUY2ToI420()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertNV12ToI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {
    // TODO: implement convertNV12ToI420()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertNV12ToRGB565(JNIEnv *env, jclass clazz, jbyteArray src,
                                                    jbyteArray dst, jint width, jint height) {
    // TODO: implement convertNV12ToRGB565()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertNV21ToBitmap(JNIEnv *env, jclass clazz, jbyteArray src,
                                                    jobject dst, jint width, jint height) {
    // TODO: implement convertNV21ToBitmap()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertNV21ToI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {
    // TODO: implement convertNV21ToBitmap()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertNV21ToI420AndRotate(JNIEnv *env, jclass clazz,
                                                           jbyteArray src, jbyteArray dst,
                                                           jint width, jint height, jint degree) {
    // TODO: implement convertNV21ToI420AndRotate()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertNV21ToRGB565(JNIEnv *env, jclass clazz, jbyteArray src,
                                                    jbyteArray dst, jint width, jint height) {
    // TODO: implement convertNV21ToRGB565()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToNV12(JNIEnv *env, jclass clazz, jbyteArray src,
                                                    jbyteArray dst, jint width, jint height) {
    // TODO: implement convertNV21ToRGB565()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToNV12AndRotate(JNIEnv *env, jclass clazz,
                                                           jbyteArray src, jbyteArray dst,
                                                           jint width, jint height, jint degree) {
    // TODO: implement convertI420ToNV12AndRotate()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToNV21(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {
    // TODO: implement convertI420ToNV12AndRotate()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToNV21AndRotate(JNIEnv *env, jclass clazz,
                                                           jbyteArray src, jbyteArray dst,
                                                           jint width, jint height, jint degree) {
    // TODO: implement convertI420ToNV21AndRotate()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToRGB24(JNIEnv *env, jclass clazz, jbyteArray src,
                                                   jbyteArray dst, jint width, jint height) {
    // TODO: implement convertI420ToRGB24()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToARGB(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {
    // TODO: implement convertI420ToARGB()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToARGBMac(JNIEnv *env, jclass clazz, jbyteArray src,
                                                     jbyteArray dst, jint width, jint height) {
    // TODO: implement convertI420ToARGBMac()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToRGBA(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height,
                                                  jint dst_stride) {
    // TODO: implement convertI420ToRGBA()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToRGBAPhone(JNIEnv *env, jclass clazz, jbyteArray src,
                                                       jbyteArray dst, jint width, jint height,
                                                       jint dst_stride) {
    // TODO: implement convertI420ToRGBAPhone()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToARGB4444(JNIEnv *env, jclass clazz, jbyteArray src,
                                                      jbyteArray dst, jint width, jint height,
                                                      jint dst_stride) {
    // TODO: implement convertI420ToARGB4444()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToRGB565(JNIEnv *env, jclass clazz, jbyteArray src,
                                                    jbyteArray dst, jint width, jint height) {
    // TODO: implement convertI420ToRGB565()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToRGB565Android(JNIEnv *env, jclass clazz,
                                                           jbyteArray src, jbyteArray dst,
                                                           jint width, jint height) {
    // TODO: implement convertI420ToRGB565Android()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToARGB1555(JNIEnv *env, jclass clazz, jbyteArray src,
                                                      jbyteArray dst, jint width, jint height,
                                                      jint dst_stride) {
    // TODO: implement convertI420ToARGB1555()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToYUY2(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height,
                                                  jint dst_stride) {
    // TODO: implement convertI420ToYUY2()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToUYVY(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height,
                                                  jint dst_stride) {
    // TODO: implement convertI420ToUYVY()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToYV12(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height,
                                                  jint dst_stride) {
    // TODO: implement convertI420ToYV12()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToBitmap(JNIEnv *env, jclass clazz, jbyteArray src,
                                                    jobject dst, jint width, jint height) {
    // TODO: implement convertI420ToYV12()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_copyI420(JNIEnv *env, jclass clazz, jbyteArray src, jbyteArray dst,
                                         jint width, jint height, jint dst_stride) {
    // TODO: implement copyI420()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_cropI420(JNIEnv *env, jclass clazz, jbyteArray src, jbyteArray dst,
                                         jint width, jint height, jint dst_width, jint dst_height,
                                         jint left, jint top) {
    // TODO: implement cropI420()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_mirrorI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                           jbyteArray dst, jint width, jint height) {
    // TODO: implement mirrorI420()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_mirrorI420upDown(JNIEnv *env, jclass clazz, jbyteArray src,
                                                 jbyteArray dst, jint width, jint height,
                                                 jint degree) {
    // TODO: implement mirrorI420upDown()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_mirrorI420LeftRight(JNIEnv *env, jclass clazz, jbyteArray src,
                                                    jbyteArray dst, jint width, jint height,
                                                    jint degree) {
    // TODO: implement mirrorI420LeftRight()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_scaleI420(JNIEnv *env, jclass clazz, jbyteArray src, jbyteArray dst,
                                          jint width, jint height, jint dst_width, jint dst_height,
                                          jint mode) {
    // TODO: implement scaleI420()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_rotateI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                           jbyteArray dst, jint width, jint height, jint degree) {
    // TODO: implement rotateI420()
}