package com.example.tdylib;

import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import com.example.cameralib.camera1.Camera1Helper;
import com.example.cameralib.listener.CameraListener;
import com.example.cameralib.view.AutoFitTextureView;

public class Camera1Activity extends AppCompatActivity implements View.OnClickListener {

    private String TAG = "Camera1Activity";
    private AutoFitTextureView textureView;
    private Camera1Helper camera1Helper;
    private CameraListener cameraListener;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera1);
        initView();
        initListener();
        initDate();
    }

    private void initView() {
        textureView = findViewById(R.id.texture_view);
    }

    private void initListener() {
        cameraListener = new CameraListener() {
            @Override
            public void onCameraOpened(int i, int i1, int i2) {

            }

            @Override
            public void onCameraPreview(byte[] bytes, int i, int i1, int i2) {

            }
        };
    }

    private void initDate() {
        camera1Helper = new Camera1Helper(this, textureView, cameraListener);

    }

    @Override
    public void onPause() {
        super.onPause();
        if (camera1Helper != null) {
            camera1Helper.onPause();
        }

    }


    @Override
    public void onResume() {
        if (camera1Helper != null) {
            camera1Helper.onResume();
        }
        super.onResume();

    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        if (camera1Helper != null) {
            camera1Helper.onDestroy();
        }
    }


    @Override
    public void onClick(View view) {
        switch (view.getId()) {

        }
    }
}