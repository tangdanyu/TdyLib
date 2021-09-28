package com.example.cameralib;

import android.graphics.ImageFormat;
import android.media.Image;

import java.nio.ByteBuffer;

public class ImageUtil {
//    // 实际结果一般是 Y:U:V == 4:2:2
//            if (image.getFormat() == ImageFormat.YUV_420_888) {
//        Image.Plane[] planes = image.getPlanes();
//        // 重复使用同一批byte数组，减少gc频率
//        if (y == null) {
//            y = new byte[planes[0].getBuffer().limit() - planes[0].getBuffer().position()];
//            u = new byte[planes[1].getBuffer().limit() - planes[1].getBuffer().position()];
//            v = new byte[planes[2].getBuffer().limit() - planes[2].getBuffer().position()];
//        }
//        if (image.getPlanes()[0].getBuffer().remaining() == y.length) {
//            planes[0].getBuffer().get(y);
//            planes[1].getBuffer().get(u);
//            planes[2].getBuffer().get(v);
//            mCameraListener.onPreview(y, u, v, mPreviewSize, planes[0].getRowStride());
//        }
//
//        int width = image.getWidth();
//        int height = image.getHeight();
//
//        if (mYuvBytes == null) {
//            // YUV420 大小总是 width * height * 3 / 2
//            mYuvBytes = new byte[width * height * 3 / 2];
//        }
//
//        // Y通道，对应planes[0]
//        // Y size = width * height
//        // yBuffer.remaining() = width * height;
//        // pixelStride = 1
//        ByteBuffer yBuffer = planes[0].getBuffer();
//        int yLen = width * height;
//        yBuffer.get(mYuvBytes, 0, yLen);
//        // U通道，对应planes[1]
//        // U size = width * height / 4;
//        // uBuffer.remaining() = width * height / 2;
//        // pixelStride = 2
//        ByteBuffer uBuffer = planes[1].getBuffer();
//        int pixelStride = planes[1].getPixelStride(); // pixelStride = 2
//        for (int i = 0; i < uBuffer.remaining(); i+=pixelStride) {
//            mYuvBytes[yLen++] = uBuffer.get(i);
//        }
//        // V通道，对应planes[2]
//        // V size = width * height / 4;
//        // vBuffer.remaining() = width * height / 2;
//        // pixelStride = 2
//        ByteBuffer vBuffer = planes[2].getBuffer();
//        pixelStride = planes[2].getPixelStride(); // pixelStride = 2
//        for (int i = 0; i < vBuffer.remaining(); i+=pixelStride) {
//            mYuvBytes[yLen++] = vBuffer.get(i);
//        }
//        if (mCameraListener != null) {
//            mCameraListener.onCameraPreview(mYuvBytes, mPreviewSize.getWidth(), mPreviewSize.getHeight(), mOrientation);
//        }
//    }

    private void getYuv(Image image){

        ByteBuffer bufferY = image.getPlanes()[0].getBuffer();
        ByteBuffer bufferU = image.getPlanes()[1].getBuffer();
        ByteBuffer bufferV = image.getPlanes()[2].getBuffer();

        ByteBuffer yuvbuffer = ByteBuffer.allocateDirect(bufferY.remaining() + bufferU.remaining() + bufferV.remaining());
        yuvbuffer.put(bufferY);
        yuvbuffer.put(bufferV);
        yuvbuffer.put(bufferU);
        image.close();

        byte[] cur_camera_yuv = yuvbuffer.array();
    }
}
