package com.example.tdylib.camera1;

import android.os.Bundle;
import android.view.WindowManager;

import androidx.appcompat.app.AppCompatActivity;

import com.example.tdylib.R;
import com.example.tdylib.listener.CameraListener;
import com.example.tdylib.view.AutoFitTextureView;


public class Camera1Activity extends AppCompatActivity {
    private String TAG = "Camera1Activity";
    //相机控制
    private Camera1Helper camera1Helper;
    //相机数据回调
    private CameraListener cameraListener;
    //相机预览控件
    private AutoFitTextureView autoFitTextureView;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
                WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_camera1);
        initView();
        initListener();
        initData();
    }

    private void initView() {
        autoFitTextureView = findViewById(R.id.texture_view);
    }

    private void initListener() {
        cameraListener = new CameraListener() {
            @Override
            public void onCameraOpened(int width, int height, int displayOrientation) {

            }


            @Override
            public void onCameraPreview(byte[] data, int width, int height, int displayOrientation) {
                if (width <= 0 || height <= 0) {
                    return;
                }

            }
        };
    }

    private void initData() {
        camera1Helper = new Camera1Helper(this, cameraListener, autoFitTextureView);
    }

    @Override
    protected void onResume() {
        super.onResume();
        camera1Helper.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        camera1Helper.onPause();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (camera1Helper != null) {
            camera1Helper.onDestroy();
            camera1Helper = null;
        }
    }
}