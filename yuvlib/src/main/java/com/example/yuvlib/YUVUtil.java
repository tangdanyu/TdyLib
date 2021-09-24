package com.example.yuvlib;

import android.graphics.Bitmap;

public class YUVUtil {

    // Used to load the 'yuvlib' library on application startup.
    static {
        System.loadLibrary("yuvlib");
    }

    private String TAG = getClass().getSimpleName();

    /**
     * A native method that is implemented by the 'yuvlib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    /**
     * 将 RGB24 转 ARGB
     * dst_stride 跨距，可传入0或width
     */
    public static native void convertRGB24ToARGB(byte[] src, byte[] dst, int width, int height, int dst_stride);

    /**
     * 将 ARGB 转 I420
     */
    public static native void convertARGBToI420(byte[] src, byte[] dst, int width, int height);

    /**
     * 将 RGB24 转 I420
     */
    public static native void convertRGB24ToI420(byte[] src, byte[] dst, int width, int height);

    /**
     * 将 UYVY 转 I420
     */
    public static native void convertUYVYToI420 (byte[] src, byte[] dst, int width, int height);

    /**
     * 将 YUY2 转 I420
     */
    public static native void convertYUY2ToI420(byte[] src, byte[] dst, int width, int height);

    /**
     * 将 NV12 转 I420
     */
    public static native void convertNV12ToI420(byte[] src, byte[] dst, int width, int height);

    /**
     * 将 NV12 转 RGB565
     */
    public static native void convertNV12ToRGB565(byte[] src, byte[] dst, int width, int height);

    /**
     * 将 NV21 数据注入到 Bitmap 中
     */
    public static native void convertNV21ToBitmap(byte[] src, Bitmap dst, int width, int height);

    /**
     * 将 NV21 转 I420
     */
    public static native void convertNV21ToI420(byte[] src, byte[] dst, int width, int height);

    /**
     * 将 NV21 转 I420 , 同时旋转
     */
    public static native void convertNV21ToI420AndRotate(byte[] src, byte[] dst, int width, int height, int degree);

    /**
     * 将 NV21 转 RGB565
     */
    public static native void convertNV21ToRGB565(byte[] src, byte[] dst, int width, int height);


    /**
     * 将 I420 转 NV12
     */
    public static native void convertI420ToNV12(byte[] src, byte[] dst, int width, int height);

    /**
     * 将 I420 转 NV12 , 同时旋转
     */
    public static native void convertI420ToNV12AndRotate(byte[] src, byte[] dst, int width, int height, int degree);

    /**
     * 将 I420 转 NV21
     */
    public static native void convertI420ToNV21(byte[] src, byte[] dst, int width, int height);

    /**
     * 将 I420 转 NV21 , 同时旋转
     */
    public static native void convertI420ToNV21AndRotate(byte[] src, byte[] dst, int width, int height, int degree);

    /**
     * 将 I420 转 RGB24
     */
    public static native void convertI420ToRGB24(byte[] src, byte[] dst, int width, int height);

    /**
     * 将 I420 转 ARGB
     */
    public static native void convertI420ToARGB(byte[] src, byte[] dst, int width, int height);

    /**
     * 将 I420 转 ARGB
     */
    public static native void convertI420ToARGBMac(byte[] src, byte[] dst, int width, int height);

    /**
     * 将 I420 转 RGBA
     * dst_stride 跨距，可传入0或width
     */
    public static native void convertI420ToRGBA(byte[] src, byte[] dst, int width, int height, int dst_stride);

    /**
     * 将 I420 转 RGBA
     * dst_stride 跨距，可传入0或width
     */
    public static native void convertI420ToRGBAPhone(byte[] src, byte[] dst, int width, int height, int dst_stride);

    /**
     * 将 I420 转 ARGB4444
     * dst_stride 跨距，可传入0或width
     */
    public static native void convertI420ToARGB4444(byte[] src, byte[] dst, int width, int height, int dst_stride);

    /**
     * 将 I420 转 RGB565
     */
    public static native void convertI420ToRGB565(byte[] src, byte[] dst, int width, int height);

    /**
     * 将 I420 转 RGB565
     */
    public static native void convertI420ToRGB565Android(byte[] src, byte[] dst, int width, int height);

    /**
     * 将 I420 转 ARGB1555
     * dst_stride 跨距，可传入0或width
     */
    public static native void convertI420ToARGB1555(byte[] src, byte[] dst, int width, int height, int dst_stride);

    /**
     * 将 I420 转 YUY2
     * dst_stride 跨距，可传入0或width
     */
    public static native void convertI420ToYUY2(byte[] src, byte[] dst, int width, int height, int dst_stride);

    /**
     * 将 I420 转 UYVY
     * dst_stride 跨距，可传入0或width
     */
    public static native void convertI420ToUYVY(byte[] src, byte[] dst, int width, int height, int dst_stride);

    /**
     * 将 I420 转 YV12
     * dst_stride 跨距，可传入0或width
     */
    public static native void convertI420ToYV12(byte[] src, byte[] dst, int width, int height, int dst_stride);

    /**
     * 将 I420 数据注入到 Bitmap 中
     */
    public static native void convertI420ToBitmap(byte[] src, Bitmap dst, int width, int height);

    /**
     * I420 复制
     * dst_stride 跨距，可传入0或width
     */
    public static native void copyI420(byte[] src, byte[] dst, int width, int height, int dst_stride);


    /**
     * I420 裁剪
     * left 裁剪的x的开始位置，必须为偶数，否则显示会有问题
     * top  裁剪的y的开始位置，必须为偶数，否则显示会有问题
     */
    public static native void cropI420(byte[] src, byte[] dst, int width, int height, int dst_width, int dst_height, int left, int top);

    /**
     * I420 镜像
     */
    public static native void mirrorI420(byte[] src, byte[] dst, int width, int height);

    /**
     * I420 上下镜像
     */
    public static native void mirrorI420upDown(byte[] src, byte[] dst, int width, int height, int degree);

    /**
     * I420 左右镜像
     */
    public static native void mirrorI420LeftRight(byte[] src, byte[] dst, int width, int height, int degree);

    /**
     * I420 缩放
     * mode 压缩模式 ，0~3，质量由低到高，一般传入0
     */
    public static native void scaleI420(byte[] src, byte[] dst, int width, int height, int dst_width, int dst_height, int mode);

    /**
     * I420 旋转
     */
    public static native void rotateI420(byte[] src, byte[] dst, int width, int height, int degree);

}


