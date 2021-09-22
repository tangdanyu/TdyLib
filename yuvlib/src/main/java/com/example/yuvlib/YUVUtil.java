package com.example.yuvlib;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.Image;
import android.os.Build;
import android.util.Log;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;

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
     * 将 NV21 转 I420
     */
    public static native void convertNV21ToI420(byte[] src, byte[] dst, int width, int height);

    /**
     * 压缩 I420 数据
     * <p>
     * 执行顺序为:缩放->旋转->镜像
     *
     * @param src       原始数据
     * @param srcWidth  原始宽度
     * @param srcHeight 原始高度
     * @param dst       输出数据
     * @param dstWidth  输出宽度
     * @param dstHeight 输出高度
     * @param degree    旋转(90, 180, 270)
     * @param isMirror  镜像(镜像在旋转之后)
     */
    public static native void compressI420(byte[] src, int srcWidth, int srcHeight,
                                           byte[] dst, int dstWidth, int dstHeight,
                                           int degree, boolean isMirror);

    /**
     * 将 I420 数据注入到 Bitmap 中
     */
    public static native void convertI420ToBitmap(byte[] src, Bitmap dst, int width, int height);

    /**
     * 将 I420 转 NV12
     */
    public static native void convertI420ToNV12(byte[] src, byte[] dst, int width, int height);

    /**
     * 将 I420 转 NV21
     */
    public static native void convertI420ToNV21(byte[] src, byte[] dst, int width, int height);


}


