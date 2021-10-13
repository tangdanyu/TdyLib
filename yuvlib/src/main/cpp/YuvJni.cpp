//
// Created by Hello on 2021/9/24.
//

#include <libyuv.h>
#include <android/bitmap.h>
#include "YuvJni.h"
#include "YuvConvert.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertRGB24ToARGB(JNIEnv *env, jclass clazz, jbyteArray src,
                                                   jbyteArray dst, jint width, jint height,
                                                   jint dst_stride) {
    jbyte *src_rgb24_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_argb_data = env->GetByteArrayElements(dst, NULL);
    RGB24ToARGB(src_rgb24_data, width, height, dst_stride, dst_argb_data);
    env->ReleaseByteArrayElements(src, src_rgb24_data, 0);
    env->ReleaseByteArrayElements(dst, dst_argb_data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertARGBMacToI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                                     jbyteArray dst, jint width, jint height) {
    jbyte *src_argb_mac_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    ARGBMacToI420(src_argb_mac_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(src, src_argb_mac_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertRGB24ToI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                                   jbyteArray dst, jint width, jint height) {
    jbyte *src_rgb24_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    RGB24ToI420(src_rgb24_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(src, src_rgb24_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertUYVYToI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {
    jbyte *src_uyvy_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    UYVYToI420(src_uyvy_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(src, src_uyvy_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertYUY2ToI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {
    jbyte *src_yuy2_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    YUY2ToI420(src_yuy2_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(src, src_yuy2_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertYV12ToI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {
    jbyte *src_yv12_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    YV12ToI420(src_yv12_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(src, src_yv12_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertNV12ToI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {
    jbyte *src_nv12_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    NV12ToI420(src_nv12_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(src, src_nv12_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertNV12ToI420AndRotate(JNIEnv *env, jclass clazz,
                                                           jbyteArray src,
                                                           jbyteArray dst, jint width, jint height,
                                                           jint degree) {
    jbyte *src_nv12_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    switch (degree) {
        case libyuv::kRotate0:
            NV12ToI420(src_nv12_data, width, height, dst_i420_data);
            break;
        case libyuv::kRotate90:
            NV12ToI420AndRotateClockwise(src_nv12_data, width, height, dst_i420_data);
            break;
        case libyuv::kRotate180:
            NV12ToI420AndRotate180(src_nv12_data, width, height, dst_i420_data);
            break;
        case libyuv::kRotate270:
            NV12ToI420AndRotateAntiClockwise(src_nv12_data, width, height, dst_i420_data);
            break;
    }
    env->ReleaseByteArrayElements(src, src_nv12_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertNV12ToRGB565(JNIEnv *env, jclass clazz, jbyteArray src,
                                                    jbyteArray dst, jint width, jint height) {
    jbyte *src_nv12_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_rgb565_data = env->GetByteArrayElements(dst, NULL);
    NV12ToRGB565(src_nv12_data, width, height, dst_rgb565_data);
    env->ReleaseByteArrayElements(src, src_nv12_data, 0);
    env->ReleaseByteArrayElements(dst, dst_rgb565_data, 0);
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
    jbyte *src_nv21_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    NV21ToI420(src_nv21_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(src, src_nv21_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertNV21ToI420AndRotate(JNIEnv *env, jclass clazz,
                                                           jbyteArray src, jbyteArray dst,
                                                           jint width, jint height, jint degree) {
    jbyte *src_nv21_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    switch (degree) {
        case libyuv::kRotate0:
            NV21ToI420(src_nv21_data, width, height, dst_i420_data);
            break;
        case libyuv::kRotate90:
            NV21ToI420AndRotateClockwise(src_nv21_data, width, height, dst_i420_data);
            break;
        case libyuv::kRotate180:
            NV21ToI420AndRotate180(src_nv21_data, width, height, dst_i420_data);
            break;
        case libyuv::kRotate270:
            NV21ToI420AndRotateAntiClockwise(src_nv21_data, width, height, dst_i420_data);
            break;
    }
    env->ReleaseByteArrayElements(src, src_nv21_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
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
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_nv12_data = env->GetByteArrayElements(dst, NULL);

    I420ToNv12(src_i420_data, width, height, dst_nv12_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_nv12_data, 0);

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

    jbyte *src_i420_data = env->GetByteArrayElements(src, JNI_FALSE);
    jbyte *dst_nv21_data = env->GetByteArrayElements(dst, JNI_FALSE);

    I420ToNv21(src_i420_data, width, height, dst_nv21_data);
    // 释放资源
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_nv21_data, 0);

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
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_rgb24_data = env->GetByteArrayElements(dst, NULL);
    I420ToRGB24(src_i420_data, width, height, dst_rgb24_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_rgb24_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToARGB(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height,
                                                  jint dst_stride) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_argb_data = env->GetByteArrayElements(dst, NULL);
    I420ToARGB(src_i420_data, width, height, dst_stride, dst_argb_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_argb_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToARGBMac(JNIEnv *env, jclass clazz, jbyteArray src,
                                                     jbyteArray dst, jint width, jint height,
                                                     jint dst_stride) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_argb_mac_data = env->GetByteArrayElements(dst, NULL);
    I420ToARGBMac(src_i420_data, width, height, dst_stride, dst_argb_mac_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_argb_mac_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToRGBAMac(JNIEnv *env, jclass clazz, jbyteArray src,
                                                     jbyteArray dst, jint width, jint height,
                                                     jint dst_stride) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_rgba_mac_data = env->GetByteArrayElements(dst, NULL);
    I420ToRGBAMac(src_i420_data, width, height, dst_stride, dst_rgba_mac_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_rgba_mac_data, 0);
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
Java_com_example_yuvlib_YUVUtil_convertI420ToRGBAIPhone(JNIEnv *env, jclass clazz, jbyteArray src,
                                                        jbyteArray dst, jint width, jint height,
                                                        jint dst_stride) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_rgba_data = env->GetByteArrayElements(dst, NULL);
    I420ToRGBAIPhone(src_i420_data, width, height, dst_stride, dst_rgba_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_rgba_data, 0);

}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToARGB4444(JNIEnv *env, jclass clazz, jbyteArray src,
                                                      jbyteArray dst, jint width, jint height,
                                                      jint dst_stride) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_argb4444_data = env->GetByteArrayElements(dst, NULL);
    I420ToARGB4444(src_i420_data, width, height, dst_stride, dst_argb4444_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_argb4444_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToRGB565(JNIEnv *env, jclass clazz, jbyteArray src,
                                                    jbyteArray dst, jint width, jint height) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_rgb565_data = env->GetByteArrayElements(dst, NULL);
    I420ToRGB565(src_i420_data, width, height, dst_rgb565_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_rgb565_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToRGB565Android(JNIEnv *env, jclass clazz,
                                                           jbyteArray src, jbyteArray dst,
                                                           jint width, jint height) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_rgb565_data = env->GetByteArrayElements(dst, NULL);
    I420ToRGB565Android(src_i420_data, width, height, dst_rgb565_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_rgb565_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToARGB1555(JNIEnv *env, jclass clazz, jbyteArray src,
                                                      jbyteArray dst, jint width, jint height,
                                                      jint dst_stride) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_argb1555_data = env->GetByteArrayElements(dst, NULL);
    I420ToARGB1555(src_i420_data, width, height, dst_stride, dst_argb1555_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_argb1555_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToYUY2(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height,
                                                  jint dst_stride) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_yuy2_data = env->GetByteArrayElements(dst, NULL);
    I420ToYUY2(src_i420_data, width, height, dst_stride, dst_yuy2_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_yuy2_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToUYVY(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height,
                                                  jint dst_stride) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_uyvy_data = env->GetByteArrayElements(dst, NULL);
    I420ToUYVY(src_i420_data, width, height, dst_stride, dst_uyvy_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_uyvy_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToYV12(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height,
                                                  jint dst_stride) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_yv12_data = env->GetByteArrayElements(dst, NULL);
    I420ToYV12(src_i420_data, width, height, dst_stride, dst_yv12_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_yv12_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToBitmap(JNIEnv *env, jclass clazz, jbyteArray src,
                                                    jobject dst, jint width, jint height) {


    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    // 锁定画布
    void *dst_argb;
    AndroidBitmap_lockPixels(env, dst, &dst_argb);
    // 获取 bitmap 的信息
    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env, dst, &info);
    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
//        i420ToABGR(src_i420_data, width, height, dst_argb, info.stride);
    } else {
        // ignore.
    }
    // 解锁画布
    AndroidBitmap_unlockPixels(env, dst);
    // 释放通过 jbyteArray 创建的 jbyte*
    env->ReleaseByteArrayElements(src, src_i420_data, 0);

}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_copyI420(JNIEnv *env, jclass clazz, jbyteArray src, jbyteArray dst,
                                         jint width, jint height, jint dst_stride) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    I420Copy(src_i420_data, width, height, dst_stride, dst_i420_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_cropI420(JNIEnv *env, jclass clazz, jbyteArray src, jbyteArray dst,
                                         jint width, jint height, jint dst_width, jint dst_height,
                                         jint left, jint top) {
    //裁剪的区域大小不对
    if (left + dst_width > width || top + dst_height > height) {
        return;
    }
    //left和top必须为偶数，否则显示会有问题
    if (left % 2 != 0 || top % 2 != 0) {
        return;
    }
    jint src_length = env->GetArrayLength(src);
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    CropI420(src_i420_data, src_length, width, height, dst_i420_data, dst_width, dst_height, left,
             top);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);

}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_mirrorI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                           jbyteArray dst, jint width, jint height) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    // i420数据镜像
    MirrorI420(src_i420_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_mirrorI420upDown(JNIEnv *env, jclass clazz, jbyteArray src,
                                                 jbyteArray dst, jint width, jint height,
                                                 jint degree) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    MirrorI420UpDown(src_i420_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_mirrorI420LeftRight(JNIEnv *env, jclass clazz, jbyteArray src,
                                                    jbyteArray dst, jint width, jint height,
                                                    jint degree) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    MirrorI420LeftRight(src_i420_data, width, height, dst_i420_data);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_scaleI420(JNIEnv *env, jclass clazz, jbyteArray src, jbyteArray dst,
                                          jint width, jint height, jint dst_width, jint dst_height,
                                          jint mode) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    // i420数据缩放
    scaleI420(src_i420_data, width, height, dst_i420_data, dst_width, dst_height, mode);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_rotateI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                           jbyteArray dst, jint width, jint height, jint degree) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    rotateI420(src_i420_data, width, height, dst_i420_data, degree);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_rotateNV21(JNIEnv *env, jclass clazz, jbyteArray src,
                                           jbyteArray dst, jint width, jint height, jint degree) {
    jbyte *src_i420_data = env->GetByteArrayElements(src, NULL);
    jbyte *dst_i420_data = env->GetByteArrayElements(dst, NULL);
    rotateNV21(src_i420_data, width, height, dst_i420_data, degree);
    env->ReleaseByteArrayElements(src, src_i420_data, 0);
    env->ReleaseByteArrayElements(dst, dst_i420_data, 0);
}
