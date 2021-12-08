package com.example.tdylib.opencv;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.example.tdylib.R;
import com.example.tdylib.opencv.camera_calibration.OpencvCameraCalibrationActivity;
import com.example.tdylib.opencv.puzzle15.OpencvPuzzle15Activity;

public class OpencvSamplesActivity extends AppCompatActivity implements View.OnClickListener {

    private Button puzzle15Btn;
    private Button cameraCalibrationBtn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_opencv_samples);

        initView();
        initListener();
        initData();
    }
    private void initView() {
        puzzle15Btn = findViewById(R.id.btn_puzzle15);
        cameraCalibrationBtn = findViewById(R.id.btn_camera_calibration);
    }

    private void initListener() {
        puzzle15Btn.setOnClickListener(this);
        cameraCalibrationBtn.setOnClickListener(this);
    }

    private void initData() {

    }

    @Override
    public void onClick(View view) {
        switch (view.getId()){
            case R.id.btn_puzzle15:
                startActivity(new Intent(this, OpencvPuzzle15Activity.class));
                break;
            case R.id.btn_camera_calibration:
                startActivity(new Intent(this, OpencvCameraCalibrationActivity.class));
                break;
        }
    }
}