#include <jni.h>
#include <string>
#include "libyuv/include/libyuv.h"
#include "YuvJni.h"

#include <android/bitmap.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_yuvlib_YUVUtil_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

//nv21转i420
void nv21ToI420(jbyte *src_nv21_data, jint width, jint height, jbyte *dst_i420_data) {

    jint src_nv21_y_size = width * height;
    //jint src_u_size = src_y_size >> 2;
    jint src_nv21_u_size = (width >> 1) * (height >> 1);

    // NV21 参数
    jbyte *src_nv21_y_data = src_nv21_data;
    jbyte *src_nv21_vu_data = src_nv21_data + src_nv21_y_size;
    // I420 参数
    jbyte *dst_i420_y_data = dst_i420_data;
    jbyte *dst_i420_u_data = dst_i420_data + src_nv21_y_size;
    jbyte *dst_i420_v_data = dst_i420_data + src_nv21_y_size + src_nv21_u_size;

    libyuv::NV21ToI420((uint8_t *) src_nv21_y_data, width,
                       (uint8_t *) src_nv21_vu_data, width,
                       (uint8_t *) dst_i420_y_data, width,
                       (uint8_t *) dst_i420_u_data, width >> 1,
                       (uint8_t *) dst_i420_v_data, width >> 1,
                       width, height);
}

//i420转NV12
void i420ToNV12(jbyte *src_i420_data, jint width, jint height, jbyte *dst_nv12_data) {
    jint src_i420_y_size = width * height;
    jint src_i420_u_size = (width >> 1) * (height >> 1);
    // I420 参数
    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_i420_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_i420_y_size + src_i420_u_size;

    // NV12 参数
    jbyte *dst_nv12_y_data = dst_nv12_data;
    jbyte *dst_nv12_vu_data = dst_nv12_data + src_i420_y_size;

    libyuv::I420ToNV12((uint8_t *) src_i420_y_data, width,
                       (uint8_t *) src_i420_u_data, width >> 1,
                       (uint8_t *) src_i420_v_data, width >> 1,
                       (uint8_t *) dst_nv12_y_data, width,
                       (uint8_t *) dst_nv12_vu_data, width,
                       width, height);
}

//i420转NV21
void i420ToNV21(jbyte *src_i420_data, jint width, jint height, jbyte *dst_nv21_data) {
    jint src_i420_y_size = width * height;
    jint src_i420_u_size = (width >> 1) * (height >> 1);
    // I420 参数
    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_i420_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_i420_y_size + src_i420_u_size;

    // NV12 参数
    jbyte *dst_nv21_y_data = dst_nv21_data;
    jbyte *dst_nv21_vu_data = dst_nv21_data + src_i420_y_size;

    libyuv::I420ToNV21((uint8_t *) src_i420_y_data, width,
                       (uint8_t *) src_i420_u_data, width >> 1,
                       (uint8_t *) src_i420_v_data, width >> 1,
                       (uint8_t *) dst_nv21_y_data, width,
                       (uint8_t *) dst_nv21_vu_data, width,
                       width, height);
}

//i420缩放
void i420Scale(jbyte *src_i420_data, jint src_width, jint src_height, jbyte *dst_i420_data,
               jint dst_width, jint dst_height) {
    //缩放的模式,0，1，2，3,0的缩放速度是最快的
    jint src_i420_y_size = src_width * src_height;
    jint src_i420_u_size = (src_width >> 1) * (src_height >> 1);
    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_i420_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_i420_y_size + src_i420_u_size;

    jint dst_i420_y_size = dst_width * dst_height;
    jint dst_i420_u_size = (dst_width >> 1) * (dst_height >> 1);
    jbyte *dst_i420_y_data = dst_i420_data;
    jbyte *dst_i420_u_data = dst_i420_data + dst_i420_y_size;
    jbyte *dst_i420_v_data = dst_i420_data + dst_i420_y_size + dst_i420_u_size;

    libyuv::I420Scale(
            (uint8_t *) src_i420_y_data, src_width,
            (uint8_t *) src_i420_u_data, src_width >> 1,
            (uint8_t *) src_i420_v_data, src_width >> 1,
            src_width, src_height,
            (uint8_t *) dst_i420_y_data, dst_width,
            (uint8_t *) dst_i420_u_data, dst_width >> 1,
            (uint8_t *) dst_i420_v_data, dst_width >> 1,
            dst_width, dst_height,
            libyuv::FilterMode::kFilterNone
    );

}

//i420旋转 旋转之后width和height相反
void i420Rotate(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data, jint degree) {
    jint src_i420_y_size = width * height;
    jint src_i420_u_size = src_i420_y_size >> 2;
    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_i420_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_i420_y_size + src_i420_u_size;

    jbyte *dst_i420_y_data = dst_i420_data;
    jbyte *dst_i420_u_data = dst_i420_data + src_i420_y_size;
    jbyte *dst_i420_v_data = dst_i420_data + src_i420_y_size + src_i420_u_size;

    if (degree == libyuv::kRotate90 || degree == libyuv::kRotate270) {
        libyuv::I420Rotate(
                (uint8_t *) src_i420_y_data, width,
                (uint8_t *) src_i420_u_data, width >> 1,
                (uint8_t *) src_i420_v_data, width >> 1,
                (uint8_t *) dst_i420_y_data, height,
                (uint8_t *) dst_i420_u_data, height >> 1,
                (uint8_t *) dst_i420_v_data, height >> 1,
                width, height,
                (libyuv::RotationMode) degree);
    }
}

//i420镜像
void i420Mirror(jbyte *src, jbyte *dst, int width, int height) {
    jint src_y_size = width * height;
    jint src_u_size = src_y_size >> 2;
    jbyte *src_y = src;
    jbyte *src_u = src + src_y_size;
    jbyte *src_v = src + src_y_size + src_u_size;

    jbyte *dst_y = dst;
    jbyte *dst_u = dst + src_y_size;
    jbyte *dst_v = dst + src_y_size + src_u_size;

    libyuv::I420Mirror((uint8_t *) src_y, width,
                       (uint8_t *) src_u, width >> 1,
                       (uint8_t *) src_v, width >> 1,
                       (uint8_t *) dst_y, width,
                       (uint8_t *) dst_u, width >> 1,
                       (uint8_t *) dst_v, width >> 1,
                       width, height);
}

//i420裁剪
void i420Crop(jbyte *src, int src_width, int src_height, jbyte *dst, int dst_width, int dst_height,
              int left, int top) {
    jint dst_y_size = dst_width * dst_height;
    jint dst_u_size = dst_y_size >> 2;
    jbyte *dst_y = dst;
    jbyte *dst_u = dst + dst_y_size;
    jbyte *dst_v = dst + dst_y_size + dst_u_size;

    libyuv::ConvertToI420(
            (uint8_t *) src, (size_t) src_width * src_height * 3 / 2,
            (uint8_t *) dst_y, dst_width,
            (uint8_t *) dst_u, dst_width >> 1,
            (uint8_t *) dst_v, dst_width >> 1,
            left, top,
            src_width, src_height,
            dst_width, dst_height,
            libyuv::kRotate0, libyuv::FOURCC_I420
    );

}

//
void i420ToABGR(jbyte *src_i420_data, jint width, jint height, void *dst, jint dst_stride) {
    jint src_y_size = width * height;
    jint src_u_size = src_y_size >> 2;
    jbyte *src_y = src_i420_data;
    jbyte *src_u = src_i420_data + src_y_size;
    jbyte *src_v = src_i420_data + src_y_size + src_u_size;
    libyuv::I420ToABGR(
            (uint8_t *) src_y, width,
            (uint8_t *) src_u, width >> 1,
            (uint8_t *) src_v, width >> 1,
            (uint8_t *) dst, dst_stride,
            width, height
    );
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertNV21ToI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {

    jbyte *nv21_src = env->GetByteArrayElements(src, NULL);
    jbyte *i420_dst = env->GetByteArrayElements(dst, NULL);

    nv21ToI420(nv21_src, width, height, i420_dst);

    // 释放通过 jbyteArray 创建的 jbyte*
    env->ReleaseByteArrayElements(src, nv21_src, 0);
    env->ReleaseByteArrayElements(dst, i420_dst, 0);


}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToNV12(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {
    jbyte *i420_src = env->GetByteArrayElements(src, NULL);
    jbyte *nv12_dst = env->GetByteArrayElements(dst, NULL);

    i420ToNV12(i420_src, width, height, nv12_dst);
    // 释放资源
    env->ReleaseByteArrayElements(src, i420_src, 0);
    env->ReleaseByteArrayElements(dst, nv12_dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToNV21(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {
    jbyte *i420_src = env->GetByteArrayElements(src, NULL);
    jbyte *nv21_dst = env->GetByteArrayElements(dst, NULL);

    i420ToNV21(i420_src, width, height, nv21_dst);
    // 释放资源
    env->ReleaseByteArrayElements(src, i420_src, 0);
    env->ReleaseByteArrayElements(dst, nv21_dst, 0);
}



extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToBitmap(JNIEnv *env, jclass clazz, jbyteArray src,
                                                    jobject bitmap, jint width, jint height) {


    jbyte *i420_src = env->GetByteArrayElements(src, NULL);
    // 锁定画布
    void *dst_argb;
    AndroidBitmap_lockPixels(env, bitmap, &dst_argb);
    // 获取 bitmap 的信息
    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env, bitmap, &info);
    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        i420ToABGR(i420_src, width, height, dst_argb, info.stride);
    } else {
        // ignore.
    }
    // 解锁画布
    AndroidBitmap_unlockPixels(env, bitmap);
    // 释放通过 jbyteArray 创建的 jbyte*
    env->ReleaseByteArrayElements(src, i420_src, 0);
}

void
Java_com_example_yuvlib_YUVUtil_convertRGB24ToARGB(JNIEnv *, jclass, jbyteArray, jbyteArray, jint,
                                                   jint, jint) {

}

