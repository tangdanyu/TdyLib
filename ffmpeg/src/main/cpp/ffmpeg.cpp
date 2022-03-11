#include <jni.h>
#include <string>
#include <android/log.h>
#include "jni/VideoRecordParams.h"
#include "jni/VideoRecorder.h"

#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"cpp",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"cpp",FORMAT,##__VA_ARGS__);
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <jni.h>
#include <jni.h>
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_tdy_ffmpeg_NativeLib_stringFromJNI(
        JNIEnv* env,
        jclass clazz) {
    std::string config = avcodec_configuration();

    LOGE("configuration %s\n",config.c_str());

    return env->NewStringUTF(config.c_str());
}

//
// Created by Hello on 2022/1/7.
//

extern "C"
JNIEXPORT jlong JNICALL
Java_com_tdy_ffmpeg_NativeLib_startRecord(JNIEnv *env, jclass clazz,
                                           jobject videoRecordParamsObj) {
    VideoRecordParams videoRecordParams;

    jclass videoRecordParamsClass = env->GetObjectClass(videoRecordParamsObj);
    jstring output_path_ = (jstring) env->GetObjectField(videoRecordParamsObj,
                                                         env->GetFieldID(videoRecordParamsClass,
                                                                         "outputPath",
                                                                         "Ljava/lang/String;"));
    const char *output_path = NULL;
    if (NULL != output_path_) {
        output_path = env->GetStringUTFChars(output_path_, 0);
        videoRecordParams.output_path = output_path;
        LOGE("output_path=%s", output_path);
    } else {
        LOGE("output_path is NULL");
        return -1;
    }
    jint srcWidth = env->GetIntField(videoRecordParamsObj,
                                     env->GetFieldID(videoRecordParamsClass, "inputWidth", "I"));
    videoRecordParams.inputWidth = srcWidth;
    LOGE("inputWidth=%d", srcWidth);

    jint srcHeight = env->GetIntField(videoRecordParamsObj,
                                      env->GetFieldID(videoRecordParamsClass, "inputHeight", "I"));
    videoRecordParams.inputHeight = srcHeight;
    LOGE("inputHeight=%d", srcHeight);

    jint targetWidth = env->GetIntField(videoRecordParamsObj,
                                        env->GetFieldID(videoRecordParamsClass, "targetWidth",
                                                        "I"));
    videoRecordParams.targetWidth = targetWidth;
    LOGE("targetWidth=%d", targetWidth);

    jint targetHeight = env->GetIntField(videoRecordParamsObj,
                                         env->GetFieldID(videoRecordParamsClass, "targetHeight",
                                                         "I"));
    videoRecordParams.targetHeight = targetHeight;
    LOGE("targetHeight=%d", targetHeight);

    jint videoRate = env->GetIntField(videoRecordParamsObj,
                                      env->GetFieldID(videoRecordParamsClass, "videoFrameRate",
                                                      "I"));
    videoRecordParams.videoFrameRate = videoRate;
    LOGE("videoFrameRate=%d", videoRate);
    jint nbSamples = env->GetIntField(videoRecordParamsObj,
                                      env->GetFieldID(videoRecordParamsClass, "nbSamples", "I"));
    videoRecordParams.nbSamples = nbSamples;
    LOGE("nbSamples=%d", nbSamples);

    jint sampleRate = env->GetIntField(videoRecordParamsObj,
                                       env->GetFieldID(videoRecordParamsClass, "sampleRate", "I"));
    videoRecordParams.sampleRate = sampleRate;
    LOGE("sampleRate=%d", sampleRate);

    jint videoRotate = env->GetIntField(videoRecordParamsObj,
                                        env->GetFieldID(videoRecordParamsClass, "videoRotate",
                                                        "I"));
    videoRecordParams.videoRotate = videoRotate;
    LOGE("videoRotate=%d", videoRotate);

    jint pixelFormat = env->GetIntField(videoRecordParamsObj,
                                        env->GetFieldID(videoRecordParamsClass, "pixelFormat",
                                                        "I"));
    videoRecordParams.pixelFormat = pixelFormat;
    LOGE("pixelFormat=%d", pixelFormat);

    jboolean hasAudio = env->GetBooleanField(videoRecordParamsObj,
                                             env->GetFieldID(videoRecordParamsClass, "hasAudio",
                                                             "Z"));
    videoRecordParams.hasAudio = hasAudio;
    LOGE("hasAudio=%d", hasAudio);

    jboolean synEncode = env->GetBooleanField(videoRecordParamsObj,
                                              env->GetFieldID(videoRecordParamsClass, "synEncode",
                                                              "Z"));
    videoRecordParams.synEncode = synEncode;
    LOGE("synEncode=%d", synEncode);


    jboolean avPacketFromMediaCodec = env->GetBooleanField(videoRecordParamsObj,
                                                           env->GetFieldID(videoRecordParamsClass,
                                                                           "avPacketFromMediaCodec",
                                                                           "Z"));
    videoRecordParams.avPacketFromMediaCodec = avPacketFromMediaCodec;
    LOGE("avPacketFromMediaCodec=%d", avPacketFromMediaCodec);


    jboolean needFlipVertical = env->GetBooleanField(videoRecordParamsObj,
                                                     env->GetFieldID(videoRecordParamsClass,
                                                                     "needFlipVertical",
                                                                     "Z"));
    videoRecordParams.needFlipVertical = needFlipVertical;
    LOGE("needFlipVertical=%d", needFlipVertical);


    jboolean allFrameIsKey = env->GetBooleanField(videoRecordParamsObj,
                                                  env->GetFieldID(videoRecordParamsClass,
                                                                  "allFrameIsKey",
                                                                  "Z"));
    videoRecordParams.allFrameIsKey = allFrameIsKey;
    LOGE("allFrameIsKey=%d", needFlipVertical);


    jlong bitRate = env->GetLongField(videoRecordParamsObj,
                                      env->GetFieldID(videoRecordParamsClass, "bitRate",
                                                      "J"));
    videoRecordParams.bit_rate = bitRate;
    LOGE("bitRate=%lld", bitRate);

    VideoRecorder *videoRecorder = new VideoRecorder();
    int64_t ret = videoRecorder->startRecord(videoRecordParams);
    if (ret < 0) {
        LOGE("startRecord fail");
        videoRecorder->setStopRecordFlag();
        videoRecorder->stopRecord();
        delete (videoRecorder);
        return 0;
    }
    if (NULL != output_path_ && NULL != output_path)
        env->ReleaseStringUTFChars(output_path_, output_path);

    env->DeleteLocalRef(videoRecordParamsObj);
    env->DeleteLocalRef(videoRecordParamsClass);

    return reinterpret_cast<int64_t>(videoRecorder);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_tdy_ffmpeg_NativeLib_stopRecord(JNIEnv *env, jclass clazz, jlong nativeHandle) {
    if (nativeHandle == 0) {
        return -1;
    }
    VideoRecorder *videoRecorder = reinterpret_cast<VideoRecorder *>(nativeHandle);
    int ret = videoRecorder->stopRecord();
    delete (videoRecorder);
    return ret;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_tdy_ffmpeg_NativeLib_addYUV420Data(JNIEnv *env, jclass clazz, jlong native_handle,
                                             jbyteArray data_, jlong pts) {
    if (native_handle == 0) {
        return -1;
    }
    unsigned char *buffer = (unsigned char *) env->GetByteArrayElements(data_, NULL);
    VideoRecorder *videoRecorder = reinterpret_cast<VideoRecorder *>(native_handle);
    long ret = videoRecorder->addVideoData(buffer, pts);
    env->ReleaseByteArrayElements(data_, reinterpret_cast<jbyte *>(buffer), 0);
    return ret;
}

