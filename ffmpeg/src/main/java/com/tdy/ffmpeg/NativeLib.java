package com.tdy.ffmpeg;

import android.content.Context;
import android.os.Build;

public class NativeLib {

    // Used to load the 'ffmpeg' library on application startup.

    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("avutil");
        System.loadLibrary("swresample");
        System.loadLibrary("avcodec");
        System.loadLibrary("avformat");
        System.loadLibrary("swscale");
        System.loadLibrary("avfilter");
        System.loadLibrary("avdevice");
    }

    /**
     * A native method that is implemented by the 'ffmpeg' native library,
     * which is packaged with this application.
     */
    public static native String stringFromJNI();

    /**
     * @param videoRecordParams 录制参数
     * @return 录制的时间, 单位毫秒, 小于0启动录制失败
     */
    public native static long startRecord(VideoRecordParams videoRecordParams);

    public static native int stopRecord(long nativeHandle);

    public static native long addYUV420Data(long nativeHandle, byte[] data, long pts);
    public static enum PixelFormat {
        YUVI420, YV12, TEXTURE
    }
}