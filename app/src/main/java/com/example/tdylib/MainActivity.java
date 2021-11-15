package com.example.tdylib;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.TextView;

import com.example.tdylib.databinding.ActivityMainBinding;
import com.tdy.ffmpeg.NativeLib;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'tdylib' library on application startup.
    static {
        System.loadLibrary("tdylib");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(NativeLib.stringFromJNI());

    }

    /**
     * A native method that is implemented by the 'tdylib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}