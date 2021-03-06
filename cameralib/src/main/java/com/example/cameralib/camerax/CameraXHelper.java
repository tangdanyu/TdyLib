package com.example.cameralib.camerax;


import android.Manifest;
import android.annotation.SuppressLint;
import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.ImageFormat;
import android.graphics.Matrix;
import android.media.ExifInterface;
import android.media.Image;
import android.os.Build;
import android.os.Environment;
import android.util.Size;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.RequiresApi;

import androidx.camera.core.Camera;
import androidx.camera.core.CameraSelector;
import androidx.camera.core.ImageAnalysis;
import androidx.camera.core.ImageCapture;
import androidx.camera.core.ImageCaptureException;
import androidx.camera.core.ImageProxy;
import androidx.camera.core.Preview;
import androidx.camera.core.VideoCapture;
import androidx.camera.lifecycle.ProcessCameraProvider;
import androidx.camera.view.PreviewView;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.lifecycle.LifecycleOwner;


import com.example.cameralib.MyLogUtil;
import com.example.cameralib.listener.CameraListener;
import com.google.common.util.concurrent.ListenableFuture;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.concurrent.ExecutionException;


public class CameraXHelper {
    private String TAG = "CameraXHelper";
    private Context context;
    private ImageCapture imageCapture;
    private ImageAnalysis imageAnalysis;
    private VideoCapture mVideoCapture;

    private CameraListener cameraListener;
    private PreviewView previewView;

    private int mFacing = CameraSelector.LENS_FACING_FRONT;
    private byte[] y, u, v, i420, yv12, nv21, nv12;
    private int format = ImageFormat.NV21;                  //设置YUV420
    private boolean isRecording = false;
    private boolean isRecordVideo = false;


    public CameraXHelper(Context context, PreviewView previewView, CameraListener cameraListener) {
        this.context = context;
        this.previewView = previewView;
        this.cameraListener = cameraListener;
        init();
    }

    private void init() {
        ListenableFuture<ProcessCameraProvider> cameraProviderFuture = ProcessCameraProvider.getInstance(context);
        cameraProviderFuture.addListener(() -> {
            try {
                // 摄像机提供商现在保证可用
                ProcessCameraProvider cameraProvider = cameraProviderFuture.get();

                cameraProvider.unbindAll();
                // 设置取景器用例以显示相机预览
                Preview preview = new Preview.Builder()
                        .setTargetResolution(new Size(previewView.getWidth(), previewView.getHeight()))//需要跟imageAnalysis一致，否则会放大
                        .build();
                // 设置取景器用例以显示相机预览
                imageCapture = new ImageCapture.Builder()
                        .setCaptureMode(ImageCapture.CAPTURE_MODE_MINIMIZE_LATENCY)
                        .build();

                //通过要求镜头朝向来选择相机
                CameraSelector cameraSelector = new CameraSelector.Builder()
                        .requireLensFacing(mFacing)
                        .build();

                if (isRecordVideo) {
                    //录制视频
                    mVideoCapture = new VideoCapture.Builder().build();
                    // 将用例附加到具有相同生命周期所有者的相机
                    Camera camera = cameraProvider.bindToLifecycle(
                            (LifecycleOwner) context,
                            cameraSelector,
                            preview,
                            imageCapture,
                            mVideoCapture
                    );
                } else {
                    //分析视频帧
                    //  No supported surface combination is found for camera device - Id : 1.
                    //  May be attempting to bind too many use cases. Existing surfaces:
                    //  和 VideoCapture不能同时使用
                    imageAnalysis = new ImageAnalysis.Builder()
                            .setTargetResolution(new Size(previewView.getWidth(), previewView.getHeight()))
                            .setBackpressureStrategy(ImageAnalysis.STRATEGY_BLOCK_PRODUCER)//阻塞
                            .build();
                    imageAnalysis.setAnalyzer(ContextCompat.getMainExecutor(context), new ImageAnalysis.Analyzer() {

                        private long lastImageTime = System.currentTimeMillis();

                        @Override
                        public void analyze(@NonNull ImageProxy imageProxy) {

                            //获取最新的一帧的Image
                            @SuppressLint({"UnsafeOptInUsageError", "UnsafeExperimentalUsageError"})
                            Image image = imageProxy.getImage();
                            if (image == null) {
                                return;
                            }
                            if (cameraListener != null) {
                                cameraListener.onPreviewFrame(image, image.getWidth(), image.getHeight(),imageProxy.getImageInfo().getRotationDegrees());
                            }
//                            if (image.getFormat() == ImageFormat.YUV_420_888) {
//
////                            MyLogUtil.e(TAG, "width" + imageProxy.getWidth());//1920
////                            MyLogUtil.e(TAG, "height" + imageProxy.getHeight());//960
////                            MyLogUtil.e(TAG, "format" + imageProxy.getFormat());//35
////                            MyLogUtil.e(TAG, "timeStamp" + (imageProxy.getImageInfo().getTimestamp() / 1000000 - lastImageTime));//42
////                            MyLogUtil.e(TAG, "getImageInfo" + imageProxy.getImageInfo().getRotationDegrees());//270
//
//                                lastImageTime = image.getTimestamp() / 1000000;//33
//                                if (nv21 == null) {
//                                    nv21 = new byte[image.getWidth() * image.getHeight() * 3 / 2];
//                                    nv12 = new byte[image.getWidth() * image.getHeight() * 3 / 2];
//                                    i420 = new byte[image.getWidth() * image.getHeight() * 3 / 2];
//                                    yv12 = new byte[image.getWidth() * image.getHeight() * 3 / 2];
//                                }
//                                if (y == null) {
//                                    y = new byte[image.getPlanes()[0].getBuffer().remaining()];
//                                    u = new byte[image.getPlanes()[1].getBuffer().remaining()];
//                                    v = new byte[image.getPlanes()[2].getBuffer().remaining()];
//                                }
//                                // 从image里获取三个plane
//                                Image.Plane[] planes = image.getPlanes();
//                                for (int i = 0; i < planes.length; i++) {
//                                    ByteBuffer iBuffer = planes[i].getBuffer();
//                                    int iSize = iBuffer.remaining();
////                                MyLogUtil.e(TAG, "pixelStride  " + planes[i].getPixelStride());
////                                MyLogUtil.e(TAG, "rowStride   " + planes[i].getRowStride());
////                                MyLogUtil.e(TAG, "buffer Size  " + iSize);
////                                MyLogUtil.e(TAG, "Finished reading data from plane  " + i);
//                                }
////                            pixelStride  1
////                            rowStride 1920
////                            buffer Size 1843200
////                            Finished reading data from plane 0
////                            pixelStride 2
////                            rowStride 1920
////                            buffer Size 921599
////                            Finished reading data from plane 1
////                            pixelStride 2
////                            rowStride 1920
////                            buffer Size 921599
////                            Finished reading data from plane 2
//
//
//                                int width = image.getWidth();
//                                int height = image.getHeight();
//                                planes[0].getBuffer().get(y);
//                                planes[1].getBuffer().get(u);
//                                planes[2].getBuffer().get(v);
//
//                                if (cameraListener != null) {
//                                    cameraListener.onPreview(y, u, v, new Size(width, height), planes[0].getRowStride());
//                                }
//                                int pixelStride = planes[1].getPixelStride();
//                                if (pixelStride == 1) {//420p,i420/yv12
//                                    if (format == ImageFormat.YV12) {
//                                        //i420
//                                        System.arraycopy(y, 0, i420, 0, y.length);
//                                        System.arraycopy(u, 0, i420, y.length, u.length);
//                                        System.arraycopy(v, 0, i420, y.length + u.length, v.length);
//                                        YUVUtil.convertI420ToNV21(i420, nv21, width, height);
//                                    } else {
//                                        //yv12
//                                        System.arraycopy(y, 0, yv12, 0, y.length);
//                                        System.arraycopy(v, 0, yv12, y.length, v.length);
//                                        System.arraycopy(u, 0, yv12, y.length + v.length, u.length);
//                                        YUVUtil.convertYV12ToI420(yv12, i420, width, height);
//                                        YUVUtil.convertI420ToNV21(i420, nv21, width, height);
//                                    }
//
//                                } else if (pixelStride == 2) {//420sp,nv21/nv12
//                                    //nv21
//                                    if (format == ImageFormat.NV21) {
//                                        System.arraycopy(y, 0, nv21, 0, y.length);
//                                        System.arraycopy(v, 0, nv21, y.length, v.length);
//                                    } else {
//                                        //nv12
//                                        System.arraycopy(y, 0, nv12, 0, y.length);
//                                        System.arraycopy(u, 0, nv12, y.length, u.length);
//                                        YUVUtil.convertNV12ToI420(nv12, i420, width, height);
//                                        YUVUtil.convertI420ToNV21(i420, nv21, width, height);
//                                    }
//                                }
//                                if (cameraListener != null) {
//                                    cameraListener.onCameraPreview(nv21, width, height, imageProxy.getImageInfo().getRotationDegrees());
//                                }
//                            }
                            image.close(); // 这里一定要close，不然预览会卡死,否则不会收到新的Image回调。
                            imageProxy.close();
                        }
                    });
                    Camera camera = cameraProvider.bindToLifecycle(
                            (LifecycleOwner) context,
                            cameraSelector,
                            preview,
                            imageCapture,
                            imageAnalysis
                    );

                }


                // 将预览用例连接到previewView
                preview.setSurfaceProvider(
                        previewView.getSurfaceProvider());

            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
            }
        }, ContextCompat.getMainExecutor(context));
    }

    //拍照保存到文件
    private void cameraXCaptureToFile() {
        String path = context.getExternalFilesDir(Environment.DIRECTORY_PICTURES).getAbsolutePath() + File.separator + System.currentTimeMillis() + ".jpg";
        ImageCapture.OutputFileOptions outputFileOptions =
                new ImageCapture.OutputFileOptions.Builder(new File(path)).build();
        imageCapture.takePicture(outputFileOptions, ContextCompat.getMainExecutor(context),
                new ImageCapture.OnImageSavedCallback() {
                    @Override
                    public void onImageSaved(ImageCapture.OutputFileResults outputFileResults) {
                        MyLogUtil.e(TAG, "onImageSaved : " + path);
                        Bitmap bitmap = BitmapFactory.decodeFile(path);
                        Bitmap newImage = null;
                        if (mFacing == CameraSelector.LENS_FACING_FRONT) {
                            MyLogUtil.e(TAG, "前置");
                            //使用矩阵反转图像数据并保持其正常
                            Matrix mtx = new Matrix();
                            //这将防止镜像
                            mtx.preScale(-1.0f, 1.0f);
                            //将post rotate设置为90，因为图像可能位于横向
//                            mtx.postRotate(90.f);
                            //旋转位图，创建我们想要的真实图像
                            newImage = Bitmap.createBitmap(bitmap, 0, 0, bitmap.getWidth(), bitmap.getHeight(), mtx, true);
                        } else {// LANDSCAPE MODE
                            MyLogUtil.e(TAG, "后置");
                            //不需要反转宽度和高度
                            newImage = bitmap;
                        }
//                        previewIv.setVisibility(View.VISIBLE);
//                        previewIv.setImageBitmap(newImage);
                    }

                    @Override
                    public void onError(ImageCaptureException error) {
                    }
                });
    }

    public void takePicture() {
        cameraXCaptureToImage();
    }

    //拍照返回视频帧
    private void cameraXCaptureToImage() {

        imageCapture.takePicture(ContextCompat.getMainExecutor(context), new
                ImageCapture.OnImageCapturedCallback() {
                    @RequiresApi(api = Build.VERSION_CODES.N)
                    @Override
                    public void onCaptureSuccess(ImageProxy image) {
                        super.onCaptureSuccess(image);
                        MyLogUtil.e(TAG, "onCaptureSuccess : " + image);
                        // 将 imageProxy 转为 byte数组
                        ByteBuffer byteBuffer = image.getPlanes()[0].getBuffer();
                        // 新建指定长度数组
                        byte[] bytes = new byte[byteBuffer.remaining()];
//                        // 倒带到起始位置 0
//                        byteBuffer.rewind();
//                        // 数据复制到数组, 这个 byteArray 包含有 exif 相关信息，
//                        // 由于 bitmap 对象不会包含 exif 信息，所以转为 bitmap 需要注意保存 exif 信息
                        byteBuffer.get(bytes);
                        cameraListener.onPictureTaken(bytes);
                        // 获取照片 Exif 信息
                        ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(bytes);
                        ExifInterface exif = null;
                        try {
                            exif = new ExifInterface(byteArrayInputStream);
                            String direction = exif.getAttribute(ExifInterface.TAG_ORIENTATION);   //获取图片方向
                            MyLogUtil.e(TAG, "获取图片方向" + direction);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        //使用完image关闭
                        image.close();

                    }

                    @Override
                    public void onError(ImageCaptureException exception) {
                        super.onError(exception);

                    }
                });
    }

    //是否正在录制视频
    public boolean isRecording() {
        return isRecording;
    }

    public boolean isRecordVideo() {
        return isRecordVideo;
    }

    //开始录制
    @SuppressLint("RestrictedApi")
    public void startRecord() {
        MyLogUtil.e(TAG, "startRecord");
        if (isRecordVideo) {
            isRecording = true;
            String path = context.getExternalFilesDir(Environment.DIRECTORY_MOVIES).getAbsolutePath() + File.separator + System.currentTimeMillis() + ".mp4";
            MyLogUtil.e(TAG, "录制开始:" + path);
            VideoCapture.OutputFileOptions outputFileOptions = new VideoCapture.OutputFileOptions.Builder(new File(path)).build();

            if (ActivityCompat.checkSelfPermission(context, Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED) {
                return;
            }
            mVideoCapture.startRecording(outputFileOptions, ContextCompat.getMainExecutor(context),
                    new VideoCapture.OnVideoSavedCallback() {
                        /**
                         * Called when the video has been successfully saved.
                         *
                         * @param outputFileResults
                         */
                        @Override
                        public void onVideoSaved(@NonNull VideoCapture.OutputFileResults outputFileResults) {
                            MyLogUtil.e(TAG, "onVideoSaved 录制成功:" + path);
                        }

                        @Override
                        public void onError(int videoCaptureError, @NonNull String message, @Nullable Throwable cause) {
                            MyLogUtil.e(TAG, "onError 录制出错:" + message);
                            isRecording = false;
                        }
                    }
            );

        }
    }

    //结束录制
    @SuppressLint("RestrictedApi")
    public void stopRecord() {
        MyLogUtil.e(TAG, "stopRecord");
        if (isRecordVideo) {
            isRecording = false;
            if (mVideoCapture != null) {
                mVideoCapture.stopRecording();
            }
        }

    }

    //是否是前置相机
    public boolean isFrontCamera() {
        return mFacing == CameraSelector.LENS_FACING_FRONT;
    }

    //切换摄像头，要先停止再开启
    public void switchCamera() {
        MyLogUtil.e(TAG, "切换摄像头");
        mFacing = (mFacing == CameraSelector.LENS_FACING_FRONT) ?
                CameraSelector.LENS_FACING_BACK : CameraSelector.LENS_FACING_FRONT;
        init();
    }

    public void cameraDestroy() {
        MyLogUtil.e(TAG, "cameraDestroy");
        if (previewView != null) {
            previewView = null;
        }
    }
}
