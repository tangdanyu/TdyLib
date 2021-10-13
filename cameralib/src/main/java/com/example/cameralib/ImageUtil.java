package com.example.cameralib;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.ImageFormat;
import android.graphics.Rect;
import android.media.Image;
import android.renderscript.Allocation;
import android.renderscript.Element;
import android.renderscript.RenderScript;
import android.renderscript.ScriptIntrinsicYuvToRGB;
import android.renderscript.Type;

import java.nio.ByteBuffer;

public class ImageUtil {
    /*************************yuv分离得到nv21**********************/
//                Image.Plane[] planes = image.getPlanes();
//                // 重复使用同一批byte数组，减少gc频率
//                if (y == null) {
//                    y = new byte[planes[0].getBuffer().limit() - planes[0].getBuffer().position()];
//                    u = new byte[planes[1].getBuffer().limit() - planes[1].getBuffer().position()];
//                    v = new byte[planes[2].getBuffer().limit() - planes[2].getBuffer().position()];
//                }
//                if (image.getPlanes()[0].getBuffer().remaining() == y.length) {
//                    planes[0].getBuffer().get(y);
//                    planes[1].getBuffer().get(u);
//                    planes[2].getBuffer().get(v);
//                }
//                int stride = image.getPlanes()[0].getRowStride();
//                image.close();
//                if (arcSoftImageInfo == null) {
//                    arcSoftImageInfo = new ArcSoftImageInfo(width, height, FaceEngine.CP_PAF_NV21);
//                }
//                // 回传数据是YUV422
//                if (y.length / u.length == 2) {
//                    ImageUtil.yuv422ToNv21ImageInfo(y, u, v, arcSoftImageInfo, stride, height);
//                }
//                // 回传数据是YUV420
//                else if (y.length / u.length == 4) {
//                    ImageUtil.yuv420ToNv21ImageInfo(y, u, v, arcSoftImageInfo, stride, height);
//                }
    /************************yuv分离得到nv21**********************/

    /************************image转nv21**************************/
//                if(nv21==null){
//                    nv21 = new byte[width*height*3/2];
//                }
//                nv21 = ImageUtil.yuv420ToNv21(image);
    /************************image转nv21**************************/

    /***********************yuv分离组成nv21**************/
//                Image.Plane[] planes = image.getPlanes();
//                // 重复使用同一批byte数组，减少gc频率
//                if (y == null) {
//                    y = new byte[planes[0].getBuffer().limit() - planes[0].getBuffer().position()];
//                    u = new byte[planes[1].getBuffer().limit() - planes[1].getBuffer().position()];
//                    v = new byte[planes[2].getBuffer().limit() - planes[2].getBuffer().position()];
//                }
//                if (image.getPlanes()[0].getBuffer().remaining() == y.length) {
//                    planes[0].getBuffer().get(y);
//                    planes[1].getBuffer().get(u);
//                    planes[2].getBuffer().get(v);
//                }
//                int stride = image.getPlanes()[0].getRowStride();
//                image.close();
//                if (arcSoftImageInfo == null) {
//                    arcSoftImageInfo = new ArcSoftImageInfo(width, height, FaceEngine.CP_PAF_NV21);
//                }
//                if(nv21==null){
//                    nv21 = new byte[width*height*3/2];
//                }
//                // 回传数据是YUV422
//                if (y.length / u.length == 2) {
//                    ImageUtil.yuv422ToYuv420sp(y, u, v, nv21, stride,height);
//                }
//                // 回传数据是YUV420
//                else if (y.length / u.length == 4) {
//                    ImageUtil.yuv420ToYuv420sp(y, u, v, nv21, stride, height);
//                }
    /***********************yuv分离组成nv21**************/

    /***********************i420 nv21************************/
//                if (nv21 == null) {
//                    nv21 = new byte[width * height * 3 / 2];
//                }
//                nv21 = ImageUtil.getDataFromImage(image,2);
    /***********************i420 nv21************************/

    /**************************mYuvbuffer cpp**************************/
//                if (nv21 == null) {
//                    nv21 = new byte[width * height * 3 / 2];
//                }
//                if (mYuvBytes == null) {
//                    // YUV420 大小总是 width * height * 3 / 2
//                    mYuvBytes = new byte[width * height * 3 / 2];
//                }
//                // Y通道，对应planes[0]
//                // Y size = width * height
//                // yBuffer.remaining() = width * height;
//                // pixelStride = 1
//                yBuffer = image.getPlanes()[0].getBuffer();
//                int yLen = width * height;
//                yBuffer.get(mYuvBytes, 0, yLen);
//                // U通道，对应planes[1]
//                // U size = width * height / 4;
//                // uBuffer.remaining() = width * height / 2;
//                // pixelStride = 2
//                uBuffer = image.getPlanes()[1].getBuffer();
//                int pixelStride = image.getPlanes()[1].getPixelStride(); // pixelStride = 2
//                for (int i = 0; i < uBuffer.remaining(); i += pixelStride) {
//                    mYuvBytes[yLen++] = uBuffer.get(i);
//                }
//                // V通道，对应planes[2]
//                // V size = width * height / 4;
//                // vBuffer.remaining() = width * height / 2;
//                // pixelStride = 2
//                vBuffer = image.getPlanes()[2].getBuffer();
//                pixelStride = image.getPlanes()[2].getPixelStride(); // pixelStride = 2
//                for (int i = 0; i < vBuffer.remaining(); i += pixelStride) {
//                    mYuvBytes[yLen++] = vBuffer.get(i);
//                }
////                lastTime = System.currentTimeMillis();
//                YUVUtil.convertI420ToNV21(mYuvBytes,nv21,width,height);
    /**************************mYuvbuffer cpp**************************/










    /**
     * 将Y:U:V == 4:2:2的数据转换为nv21
     *
     * @param y      Y 数据
     * @param u      U 数据
     * @param v      V 数据
     * @param nv21   生成的nv21，需要预先分配内存
     * @param stride 步长
     * @param height 图像高度
     */
    public static void yuv422ToYuv420sp(byte[] y, byte[] u, byte[] v, byte[] nv21, int stride, int height) {
        System.arraycopy(y, 0, nv21, 0, y.length);
        // 注意，若length值为 y.length * 3 / 2 会有数组越界的风险，需使用真实数据长度计算
        int length = y.length + u.length / 2 + v.length / 2;
        int uIndex = 0, vIndex = 0;
        for (int i = stride * height; i < length; i += 2) {
            nv21[i] = v[vIndex];
            nv21[i + 1] = u[uIndex];
            vIndex += 2;
            uIndex += 2;
        }
    }

    /**
     * 将Y:U:V == 4:1:1的数据转换为nv21
     *
     * @param y      Y 数据
     * @param u      U 数据
     * @param v      V 数据
     * @param nv21   生成的nv21，需要预先分配内存
     * @param stride 步长
     * @param height 图像高度
     */
    public static void yuv420ToYuv420sp(byte[] y, byte[] u, byte[] v, byte[] nv21, int stride, int height) {
        System.arraycopy(y, 0, nv21, 0, y.length);
        // 注意，若length值为 y.length * 3 / 2 会有数组越界的风险，需使用真实数据长度计算
        int length = y.length + u.length + v.length;
        int uIndex = 0, vIndex = 0;
        for (int i = stride * height; i < length; i++) {
            nv21[i] = v[vIndex++];
            nv21[i + 1] = u[uIndex++];
        }
    }

    /**
     * YUV_420_888转NV21
     * camera2
     * 耗时12-17ms
     */
    public static byte[] yuv420ToNv21(Image image) {
        Image.Plane[] planes = image.getPlanes();
        ByteBuffer yBuffer = planes[0].getBuffer();
        ByteBuffer uBuffer = planes[1].getBuffer();
        ByteBuffer vBuffer = planes[2].getBuffer();

        int ySize = yBuffer.remaining();
        int uSize = uBuffer.remaining();
        int vSize = vBuffer.remaining();
        int size = image.getWidth() * image.getHeight();
        byte[] nv21 = new byte[size * 3 / 2];
        yBuffer.get(nv21, 0, ySize);
        vBuffer.get(nv21, ySize, vSize);

        byte[] u = new byte[uSize];
        uBuffer.get(u);

        //每隔开一位替换V，达到VU交替
        int pos = ySize + 1;
        for (int i = 0; i < uSize; i++) {
            if (i % 2 == 0) {
                nv21[pos] = u[i];
                pos += 2;
            }
        }
        return nv21;
    }

//    /**
//     * YUV_420_888转NV21
//     * camerax
//     */
//    public static byte[] yuv420ToNv21(ImageProxy image) {
//        ImageProxy.PlaneProxy[] planes = image.getPlanes();
//        ByteBuffer yBuffer = planes[0].getBuffer();
//        ByteBuffer uBuffer = planes[1].getBuffer();
//        ByteBuffer vBuffer = planes[2].getBuffer();
//        int ySize = yBuffer.remaining();
//        int uSize = uBuffer.remaining();
//        int vSize = vBuffer.remaining();
//        int size = image.getWidth() * image.getHeight();
//        byte[] nv21 = new byte[size * 3 / 2];
//        yBuffer.get(nv21, 0, ySize);
//        vBuffer.get(nv21, ySize, vSize);
//
//        byte[] u = new byte[uSize];
//        uBuffer.get(u);
//
//        //每隔开一位替换V，达到VU交替
//        int pos = ySize + 1;
//        for (int i = 0; i < uSize; i++) {
//            if (i % 2 == 0) {
//                nv21[pos] = u[i];
//                pos += 2;
//            }
//        }
//        return nv21;
//    }

//    /**
//     * YUV420数据转换为NV21格式的ArcSoftImageInfo
//     *
//     * @param y                YUV420数据的y分量
//     * @param u                YUV420数据的u分量
//     * @param v                YUV420数据的v分量
//     * @param arcSoftImageInfo NV21格式的ArcSoftImageInfo
//     * @param stride           y分量的步长，一般情况下，由于YUV数据的对应关系，Y分量步长确定了，U和V也随之确定
//     * @param height           图像高度
//     * 耗时7-15ms
//     */
//    public static void yuv420ToNv21ImageInfo(byte[] y, byte[] u, byte[] v, ArcSoftImageInfo arcSoftImageInfo, int stride, int height) {
//        if (arcSoftImageInfo.getPlanes() == null) {
//            arcSoftImageInfo.setPlanes(new byte[][]{new byte[stride * height], new byte[stride * height / 2]});
//            arcSoftImageInfo.setStrides(new int[]{stride, stride});
//        }
//        System.arraycopy(y, 0, arcSoftImageInfo.getPlanes()[0], 0, y.length);
//        // 注意，vuLength 不能直接通过步长和高度计算，实测发现Camera2 API回传的数据有数据丢失，需要使用真实数据长度
//        byte[] vu = arcSoftImageInfo.getPlanes()[1];
//        int vuLength = u.length / 2 + v.length / 2;
//        int uIndex = 0, vIndex = 0;
//        for (int i = 0; i < vuLength; i++) {
//            vu[i] = v[vIndex++];
//            vu[i + 1] = u[uIndex++];
//        }
//    }

//    /**
//     * YUV422数据转换为NV21格式的ArcSoftImageInfo
//     *
//     * @param y                YUV422数据的y分量
//     * @param u                YUV422数据的u分量
//     * @param v                YUV422数据的v分量
//     * @param arcSoftImageInfo NV21格式的ArcSoftImageInfo
//     * @param stride           y分量的步长，一般情况下，由于YUV数据的对应关系，Y分量步长确定了，U和V也随之确定
//     * @param height           图像高度
//     */
//    public static void yuv422ToNv21ImageInfo(byte[] y, byte[] u, byte[] v, ArcSoftImageInfo arcSoftImageInfo, int stride, int height) {
//        if (arcSoftImageInfo.getPlanes() == null) {
//            arcSoftImageInfo.setPlanes(new byte[][]{new byte[stride * height], new byte[stride * height / 2]});
//            arcSoftImageInfo.setStrides(new int[]{stride, stride});
//        }
//        System.arraycopy(y, 0, arcSoftImageInfo.getPlanes()[0], 0, y.length);
//        byte[] vu = arcSoftImageInfo.getPlanes()[1];
//        // 注意，vuLength 不能直接通过步长和高度计算，实测发现Camera2 API回传的数据有数据丢失，需要使用真实数据长度
//        int vuLength = u.length / 2 + v.length / 2;
//        int uIndex = 0, vIndex = 0;
//        for (int i = 0; i < vuLength; i += 2) {
//            vu[i] = v[vIndex];
//            vu[i + 1] = u[uIndex];
//            vIndex += 2;
//            uIndex += 2;
//        }
//    }


    public static byte[] getDataFromImage(Image image, int colorFormat) {
        int COLOR_FormatI420 = 1;
        int COLOR_FormatNV21 = 2;

        Rect crop = image.getCropRect();
        int format = image.getFormat();
        int width = crop.width();
        int height = crop.height();
        Image.Plane[] planes = image.getPlanes();
        byte[] data = new byte[width * height * ImageFormat.getBitsPerPixel(format) / 8];
        byte[] rowData = new byte[planes[0].getRowStride()];
        int channelOffset = 0;
        int outputStride = 1;
        for (int i = 0; i < planes.length; i++) {
            switch (i) {
                case 0:
                    channelOffset = 0;
                    outputStride = 1;
                    break;
                case 1:
                    if (colorFormat == COLOR_FormatI420) {
                        channelOffset = width * height;
                        outputStride = 1;
                    } else if (colorFormat == COLOR_FormatNV21) {
                        channelOffset = width * height + 1;
                        outputStride = 2;
                    }
                    break;
                case 2:
                    if (colorFormat == COLOR_FormatI420) {
                        channelOffset = (int) (width * height * 1.25);
                        outputStride = 1;
                    } else if (colorFormat == COLOR_FormatNV21) {
                        channelOffset = width * height;
                        outputStride = 2;
                    }
                    break;
            }
            ByteBuffer buffer = planes[i].getBuffer();
            int rowStride = planes[i].getRowStride();
            int pixelStride = planes[i].getPixelStride();
           /* if (VERBOSE) {
                Log.v(TAG, "pixelStride " + pixelStride);
                Log.v(TAG, "rowStride " + rowStride);
                Log.v(TAG, "width " + width);
                Log.v(TAG, "height " + height);
                Log.v(TAG, "buffer size " + buffer.remaining());
            }*/
            int shift = (i == 0) ? 0 : 1;
            int w = width >> shift;
            int h = height >> shift;
            buffer.position(rowStride * (crop.top >> shift) + pixelStride * (crop.left >> shift));
            for (int row = 0; row < h; row++) {
                int length;
                if (pixelStride == 1 && outputStride == 1) {
                    length = w;
                    buffer.get(data, channelOffset, length);
                    channelOffset += length;
                } else {
                    length = (w - 1) * pixelStride + 1;
                    buffer.get(rowData, 0, length);
                    for (int col = 0; col < w; col++) {
                        data[channelOffset] = rowData[col * pixelStride];
                        channelOffset += outputStride;
                    }
                }
                if (row < h - 1) {
                    buffer.position(buffer.position() + rowStride - length);
                }
            }
        }
        return data;
    }

    public static Bitmap nv21ToBitmap(byte[] nv21, int width, int height, Context context) {
        RenderScript rs = RenderScript.create(context);
        ScriptIntrinsicYuvToRGB yuvToRgbIntrinsic = ScriptIntrinsicYuvToRGB.create(rs, Element.U8_4(rs));
        Type.Builder yuvType = null, rgbaType;
        Allocation in = null, out = null;
        if (yuvType == null) {
            yuvType = new Type.Builder(rs, Element.U8(rs)).setX(nv21.length);
            in = Allocation.createTyped(rs, yuvType.create(), Allocation.USAGE_SCRIPT);
            rgbaType = new Type.Builder(rs, Element.RGBA_8888(rs)).setX(width).setY(height);
            out = Allocation.createTyped(rs, rgbaType.create(), Allocation.USAGE_SCRIPT);
        }
        in.copyFrom(nv21);
        yuvToRgbIntrinsic.setInput(in);
        yuvToRgbIntrinsic.forEach(out);
        Bitmap bmpout = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        out.copyTo(bmpout);
        return bmpout;
    }




//            synchronized (mImageReaderLock) {
//                if(!mImageReaderLock.equals(1)){
//                    MyLogUtil.e(TAG, "--- image not available,just return!!!");
//                    image.close();
//                    return;
//                }
//                if (ImageFormat.YUV_420_888 == image.getFormat()) {
//                    Image.Plane[] planes = image.getPlanes();
//
//                    lock.lock();
//                    if (y == null) {
//                        y = new byte[planes[0].getBuffer().limit() - planes[0].getBuffer().position()];
//                        u = new byte[planes[1].getBuffer().limit() - planes[1].getBuffer().position()];
//                        v = new byte[planes[2].getBuffer().limit() - planes[2].getBuffer().position()];
//                    }
//
//                    if (image.getPlanes()[0].getBuffer().remaining() == y.length) {
//                        planes[0].getBuffer().get(y);
//                        planes[1].getBuffer().get(u);
//                        planes[2].getBuffer().get(v);
//
//                        if (nv21 == null) {
//                            nv21 = new byte[planes[0].getRowStride() * mPreviewSize.getHeight() * 3 / 2];
//                        }
//
//                        if(nv21 != null && (nv21.length != planes[0].getRowStride() * mPreviewSize.getHeight() *3/2)){
//                            return;
//                        }
//
//                        // 回传数据是YUV422
//                        if (y.length / u.length == 2) {
//                            ImageUtil.yuv422ToYuv420sp(y, u, v, nv21, planes[0].getRowStride(), mPreviewSize.getHeight());
//                        }
//                        // 回传数据是YUV420
//                        else if (y.length / u.length == 4) {
//                            ImageUtil.yuv420ToYuv420sp(y, u, v, nv21, planes[0].getRowStride(), mPreviewSize.getHeight());
////                            nv21 = ImageUtil.yuv420ToNv21(image);
//                        }
//                    }
//                    lock.unlock();
//                }
//            }
    byte[] y;
    byte[] u;
    byte[] v;
    byte[] mYuvBytes, nv21;

    public void getYUV(Image image) {
        // 实际结果一般是 Y:U:V == 4:2:2
        if (image.getFormat() == ImageFormat.YUV_420_888) {
            Image.Plane[] planes = image.getPlanes();
//                // 重复使用同一批byte数组，减少gc频率
            if (y == null) {
                y = new byte[planes[0].getBuffer().limit() - planes[0].getBuffer().position()];
                u = new byte[planes[1].getBuffer().limit() - planes[1].getBuffer().position()];
                v = new byte[planes[2].getBuffer().limit() - planes[2].getBuffer().position()];
            }
            if (image.getPlanes()[0].getBuffer().remaining() == y.length) {
                planes[0].getBuffer().get(y);
                planes[1].getBuffer().get(u);
                planes[2].getBuffer().get(v);
            }
            if (nv21 == null) {
                nv21 = new byte[planes[0].getRowStride() * image.getHeight() * 3 / 2];
            }
            int stride = image.getPlanes()[0].getRowStride();
            image.close();
        }
//        if (arcSoftImageInfo == null) {
//            arcSoftImageInfo = new ArcSoftImageInfo(width, height, FaceEngine.CP_PAF_NV21);
//        }
//        // 回传数据是YUV422
//        if (y.length / u.length == 2) {
//            ImageUtil.yuv422ToNv21ImageInfo(y, u, v, arcSoftImageInfo, stride, height);
//        }
//        // 回传数据是YUV420
//        else if (y.length / u.length == 4) {
//            ImageUtil.yuv420ToNv21ImageInfo(y, u, v, arcSoftImageInfo, stride, height);
//        }
//        // 此时的arcSoftImageInfo数据即可传给SDK使用
//        if (faceDetectorAdapter.isDetecting()) {
//            MyLogUtil.e(TAG, "正在识别");
//            faceDetectorAdapter.faceDetection(arcSoftImageInfo);//width=720height=960
//        }

    }

    public void getYUVbyte(Image image) {

        int width = image.getWidth();
        int height = image.getHeight();

        if (mYuvBytes == null) {
            // YUV420 大小总是 width * height * 3 / 2
            mYuvBytes = new byte[width * height * 3 / 2];
        }
        // Y通道，对应planes[0]
        // Y size = width * height
        // yBuffer.remaining() = width * height;
        // pixelStride = 1
        ByteBuffer yBuffer = image.getPlanes()[0].getBuffer();
        int yLen = width * height;
        yBuffer.get(mYuvBytes, 0, yLen);
        // U通道，对应planes[1]
        // U size = width * height / 4;
        // uBuffer.remaining() = width * height / 2;
        // pixelStride = 2
        ByteBuffer uBuffer = image.getPlanes()[1].getBuffer();
        int pixelStride = image.getPlanes()[1].getPixelStride(); // pixelStride = 2
        for (int i = 0; i < uBuffer.remaining(); i += pixelStride) {
            mYuvBytes[yLen++] = uBuffer.get(i);
        }
        // V通道，对应planes[2]
        // V size = width * height / 4;
        // vBuffer.remaining() = width * height / 2;
        // pixelStride = 2
        ByteBuffer vBuffer = image.getPlanes()[2].getBuffer();
        pixelStride = image.getPlanes()[2].getPixelStride(); // pixelStride = 2
        for (int i = 0; i < vBuffer.remaining(); i += pixelStride) {
            mYuvBytes[yLen++] = vBuffer.get(i);
        }
    }
}
