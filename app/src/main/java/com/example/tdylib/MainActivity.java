package com.example.tdylib;

import android.Manifest;
import android.app.Activity;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import com.example.cameralib.MyLogUtil;
import com.example.tdylib.opencv.OpencvSamplesActivity;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private String TAG = "MainActivity";
    //动态申请相机权限
    private String[] PERMISSIONS = {
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.CAMERA,
            Manifest.permission.RECORD_AUDIO};

    // Used to load the 'tdylib' library on application startup.
    static {
        System.loadLibrary("tdylib");
    }


    private TextView tv;
    private Button camera1Btn;
    private Button opencvBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
        initListener();
        initData();
    }

    private void initView() {
        tv = findViewById(R.id.sample_text);
        camera1Btn = findViewById(R.id.btn_camera1);
        opencvBtn = findViewById(R.id.btn_opencv);
    }

    private void initListener() {
        camera1Btn.setOnClickListener(this);
        opencvBtn.setOnClickListener(this);
    }

    private void initData() {
        tv.setText( stringFromJNI());
    }

    @Override
    public void onClick(View view) {

        switch (view.getId()) {
            case R.id.btn_camera1:
                if (checkAndRequestPermissions(PERMISSIONS, 100)) {
                    startActivity(new Intent(this, Camera1Activity.class));
                }
                break;
            case R.id.btn_opencv:
                startActivity(new Intent(this, OpencvSamplesActivity.class));
                break;
        }
    }

    //动态申请权限
    public boolean checkAndRequestPermissions(String[] permissions, int requestCode) {
        List<String> requestPermission = new ArrayList<>();
        for (String permission : permissions) {
            if (ContextCompat.checkSelfPermission(this, permission) != PackageManager.PERMISSION_GRANTED) {//检查是否有了权限
                //没有权限即动态申请
                requestPermission.add(permission);
            }
        }
        if (requestPermission.size() == 0) {
            return true;
        }

        ActivityCompat.requestPermissions((Activity) this, requestPermission.toArray(new String[requestPermission.size()]), requestCode);
        return false;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        boolean isAllGrant = true;

        for (int i = 0; i < grantResults.length; i++) {
            if (grantResults[i] != PackageManager.PERMISSION_GRANTED) {
                AlertDialog dialog = new AlertDialog.Builder(this).setTitle("提示").setMessage("权限被禁止。\n请在【设置-应用信息-权限】中重新授权").setPositiveButton("确定", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                        onPermissionReject(requestCode);
                    }
                }).setNegativeButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                        onPermissionReject(requestCode);
                    }
                }).create();
                dialog.setCancelable(false);
                dialog.setCanceledOnTouchOutside(false);
                dialog.show();

                isAllGrant = false;
                break;
            }
        }

        if (isAllGrant) {
            onPermissionGranted(requestCode);
        }
    }

    //获得全部权限
    public void onPermissionGranted(int requestCode) {
        MyLogUtil.e(TAG, "已经获得权限");
    }

    //权限被拒绝
    public void onPermissionReject(int requestCode) {
        finish();
    }
    /**
     * A native method that is implemented by the 'tdylib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}