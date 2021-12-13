package com.example.tdylib.opencv;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.example.tdylib.R;
import com.example.tdylib.opencv.cameracalibration.OpencvCameraCalibrationActivity;
import com.example.tdylib.opencv.colorblobdetect.OpencvColorBlobDetectionActivity;
import com.example.tdylib.opencv.facedetect.OpencvFaceDetectionActivity;
import com.example.tdylib.opencv.imagemanipulations.OpencvImageManipulationsActivity;
import com.example.tdylib.opencv.puzzle15.OpencvPuzzle15Activity;
import com.example.tdylib.opencv.tutorial1.OpencvTutorial1CamerapreviewActivity;
import com.example.tdylib.opencv.tutorial2.OpencvTutorial2MixedprocessingActivity;
import com.example.tdylib.opencv.tutorial3.OpencvTutorial3CameracontrolActivity;

public class OpencvSamplesActivity extends AppCompatActivity implements View.OnClickListener {

    private Button puzzle15Btn;
    private Button cameraCalibrationBtn;
    private Button colorBlobDetectionBtn;
    private Button faceDetectionBtn;
    private Button imageManipulationsBtn;
    private Button tutorial1CameraPreviewBtn;
    private Button tutorial2MixedProcessingBtn;
    private Button tutorial3CameraControlBtn;

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
        colorBlobDetectionBtn = findViewById(R.id.btn_color_blob_detection);
        faceDetectionBtn = findViewById(R.id.btn_face_detection);
        imageManipulationsBtn = findViewById(R.id.btn_image_manipulations);
        tutorial1CameraPreviewBtn = findViewById(R.id.btn_tutorial1_camerapreview);
        tutorial2MixedProcessingBtn = findViewById(R.id.btn_tutorial2_mixedprocessing);
        tutorial3CameraControlBtn = findViewById(R.id.btn_tutorial3_cameracontrol);
    }

    private void initListener() {
        puzzle15Btn.setOnClickListener(this);
        cameraCalibrationBtn.setOnClickListener(this);
        colorBlobDetectionBtn.setOnClickListener(this);
        faceDetectionBtn.setOnClickListener(this);
        imageManipulationsBtn.setOnClickListener(this);
        tutorial1CameraPreviewBtn.setOnClickListener(this);
        tutorial2MixedProcessingBtn.setOnClickListener(this);
        tutorial3CameraControlBtn.setOnClickListener(this);
    }

    private void initData() {

    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.btn_puzzle15:
                startActivity(new Intent(this, OpencvPuzzle15Activity.class));
                break;
            case R.id.btn_camera_calibration:
                startActivity(new Intent(this, OpencvCameraCalibrationActivity.class));
                break;
            case R.id.btn_color_blob_detection:
                startActivity(new Intent(this, OpencvColorBlobDetectionActivity.class));
                break;
            case R.id.btn_face_detection:
                startActivity(new Intent(this, OpencvFaceDetectionActivity.class));
                break;
            case R.id.btn_image_manipulations:
                startActivity(new Intent(this, OpencvImageManipulationsActivity.class));
                break;

            case R.id.btn_tutorial1_camerapreview:
                startActivity(new Intent(this, OpencvTutorial1CamerapreviewActivity.class));
                break;

            case R.id.btn_tutorial2_mixedprocessing:
                startActivity(new Intent(this, OpencvTutorial2MixedprocessingActivity.class));
                break;
            case R.id.btn_tutorial3_cameracontrol:
                startActivity(new Intent(this, OpencvTutorial3CameracontrolActivity.class));
                break;
        }
    }
}