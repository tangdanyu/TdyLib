#include <jni.h>
#include <string>
#include "libyuv/include/libyuv.h"
#include <android/bitmap.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_yuvlib_YUVUtil_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
void I420ToABGR(jbyte *src, int width, int height, void *dst, int dst_stride) {
    jint src_y_size = width * height;
    jint src_u_size = src_y_size >> 2;
    jbyte *src_y = src;
    jbyte *src_u = src + src_y_size;
    jbyte *src_v = src + src_y_size + src_u_size;
    libyuv::I420ToABGR(
            (uint8_t *) src_y, width,
            (uint8_t *) src_u, width >> 1,
            (uint8_t *) src_v, width >> 1,
            (uint8_t *) dst, dst_stride,
            width, height
    );
}

void I420Scale(jbyte *src, int src_width, int src_height, jbyte *dst,
               int dst_width, int dst_height) {
    jint src_y_size = src_width * src_height;
    jint src_u_size = src_y_size >> 2;
    jbyte *src_y = src;
    jbyte *src_u = src + src_y_size;
    jbyte *src_v = src + src_y_size + src_u_size;

    jint dst_y_size = dst_width * dst_height;
    jint dst_u_size = dst_y_size >> 2;
    jbyte *dst_y = dst;
    jbyte *dst_u = dst + dst_y_size;
    jbyte *dst_v = dst + dst_y_size + dst_u_size;

    libyuv::I420Scale(
            (uint8_t *) src_y, src_width,
            (uint8_t *) src_u, src_width >> 1,
            (uint8_t *) src_v, src_width >> 1,
            src_width, src_height,
            (uint8_t *) dst_y, dst_width,
            (uint8_t *) dst_u, dst_width >> 1,
            (uint8_t *) dst_v, dst_width >> 1,
            dst_width, dst_height,
            libyuv::FilterMode::kFilterNone
    );

}

void I420Rotate(jbyte *src, jbyte *dst, int &width, int &height,
                int degree) {
    jint src_y_size = width * height;
    jint src_u_size = src_y_size >> 2;
    jbyte *src_y = src;
    jbyte *src_u = src + src_y_size;
    jbyte *src_v = src + src_y_size + src_u_size;

    jbyte *dst_y = dst;
    jbyte *dst_u = dst + src_y_size;
    jbyte *dst_v = dst + src_y_size + src_u_size;

    libyuv::I420Rotate(
            (uint8_t *) src_y, width,
            (uint8_t *) src_u, width >> 1,
            (uint8_t *) src_v, width >> 1,
            (uint8_t *) dst_y, height,
            (uint8_t *) dst_u, height >> 1,
            (uint8_t *) dst_v, height >> 1,
            width, height, (libyuv::RotationMode) degree
    );
    // 若为 90 / 270,  则翻转宽高
    if (degree == libyuv::kRotate90 || degree == libyuv::kRotate270) {
        width += height;
        height = width - height;
        width -= height;
    }
}

void I420Mirror(jbyte *src, jbyte *dst, int width, int height) {
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

void I420Crop(jbyte *src, int src_width, int src_height, jbyte *dst, int dst_width,
              int dst_height, int left, int top) {
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

extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertI420ToNV12(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {
    jbyte *i420_src = env->GetByteArrayElements(src, NULL);
    jbyte *nv12_dst = env->GetByteArrayElements(dst, NULL);
    // 执行转换 I420 -> NV12 的转换
    jint src_y_size = width * height;
    jint src_u_size = src_y_size >> 2;
    jbyte *src_y = i420_src;
    jbyte *src_u = i420_src + src_y_size;
    jbyte *src_v = i420_src + src_y_size + src_u_size;

    jint dst_y_size = width * height;
    jbyte *dst_y = nv12_dst;
    jbyte *dst_uv = nv12_dst + dst_y_size;

    libyuv::I420ToNV12(
            (uint8_t *) src_y, width,
            (uint8_t *) src_u, width >> 1,
            (uint8_t *) src_v, width >> 1,
            (uint8_t *) dst_y, width,
            (uint8_t *) dst_uv, width,
            width, height
    );
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
    jint src_y_size = width * height;
    jint src_u_size = src_y_size >> 2;
    jbyte *src_y = i420_src;
    jbyte *src_u = i420_src + src_y_size;
    jbyte *src_v = i420_src + src_y_size + src_u_size;

    jint dst_y_size = width * height;
    jbyte *dst_y = nv21_dst;
    jbyte *dst_vu = nv21_dst + dst_y_size;

    libyuv::I420ToNV21(
            (uint8_t *) src_y, width,
            (uint8_t *) src_u, width >> 1,
            (uint8_t *) src_v, width >> 1,
            (uint8_t *) dst_y, width,
            (uint8_t *) dst_vu, width,
            width, height
    );

    // 释放资源
    env->ReleaseByteArrayElements(src, i420_src, 0);
    env->ReleaseByteArrayElements(dst, nv21_dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_convertNV21ToI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                                  jbyteArray dst, jint width, jint height) {

    jbyte *nv21_src = env->GetByteArrayElements(src, NULL);
    jbyte *nv12_dst = env->GetByteArrayElements(dst, NULL);


    // NV21 参数
    jint src_y_size = width * height;
    jbyte *src_y = nv21_src;
    jbyte *src_vu = nv21_src + src_y_size;
    // I420 参数
    jint dst_y_size = width * height;
    jint dst_u_size = dst_y_size >> 2;
    jbyte *dst_y = nv12_dst;
    jbyte *dst_u = nv12_dst + dst_y_size;

    jbyte *dst_v = nv12_dst + dst_y_size + dst_u_size;

    libyuv::NV21ToI420(
            (uint8_t *) src_y, width,
            (uint8_t *) src_vu, width,
            (uint8_t *) dst_y, width,
            (uint8_t *) dst_u, width >> 1,
            (uint8_t *) dst_v, width >> 1,
            width, height
    );
    // 释放通过 jbyteArray 创建的 jbyte*
    env->ReleaseByteArrayElements(src, nv21_src, 0);
    env->ReleaseByteArrayElements(dst, nv12_dst, 0);


}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_yuvlib_YUVUtil_compressI420(JNIEnv *env, jclass clazz, jbyteArray src,
                                             jint src_width, jint src_height, jbyteArray dst,
                                             jint dst_width, jint dst_height, jint degree,
                                             jboolean is_mirror) {

    jbyte *i420_src = env->GetByteArrayElements(src, NULL);
    const int dst_size = dst_width * dst_height * 3 / 2;
    // step1: 缩放处理
    jbyte *scaled = i420_src;
    if (src_width != dst_width || src_height != dst_height) {
        scaled = new jbyte[dst_size];
        I420Scale(i420_src, src_width, src_height, scaled, dst_width,
                  dst_height);
    }
    // step2: 旋转处理
    jbyte *rotated = scaled;
    if (degree != 0) {
        rotated = new jbyte[dst_size];
        // 若为 90/270 旋转之后会反转 width 和 height
        I420Rotate(scaled, rotated, dst_width, dst_height, degree);
        if (scaled != i420_src) {
            delete[]scaled;
        }
    }
    // step3: 镜像处理
    jbyte *mirrored = rotated;
    if (is_mirror) {
        mirrored = new jbyte[dst_size];
        I420Mirror(rotated, mirrored, dst_width, dst_height);
        if (rotated != i420_src) {
            delete[]rotated;
        }
    }
    // step4: 将数据拷贝到 dst 中
    jbyte *i420_dst = env->GetByteArrayElements(dst, NULL);
    memcpy(dst, mirrored, (size_t) dst_size);
    // 释放资源
    if (mirrored != i420_src) {
        delete[]mirrored;
    }
    env->ReleaseByteArrayElements(src, i420_src, 0);
    env->ReleaseByteArrayElements(dst, i420_dst, 0);
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
        I420ToABGR(i420_src, width, height, dst_argb, info.stride);
    } else {
        // ignore.
    }
    // 解锁画布
    AndroidBitmap_unlockPixels(env, bitmap);
    // 释放通过 jbyteArray 创建的 jbyte*
    env->ReleaseByteArrayElements(src, i420_src, 0);
}





