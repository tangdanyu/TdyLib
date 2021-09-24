package com.example.tdylib.listener;


import android.graphics.Bitmap;

public interface CameraListener {
    //相机启动
    void onCameraOpened(int width, int height,int displayOrientation);
    //相机关闭
    default void onCameraClosed(){}
    //相机数据
    void onCameraPreview(byte[] data, int width, int height , int displayOrientation);
    //拍照
    default void onPictureTaken(byte[] data){}

    default void onBitmap(Bitmap bitmap,int displayOrientation){}
}
