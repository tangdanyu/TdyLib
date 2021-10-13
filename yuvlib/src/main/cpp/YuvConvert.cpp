//
// Created by Jared on 2021/9/24.
//

#include <jni.h>
#include <libyuv.h>
#include "YuvConvert.h"

//i420缩放
void scaleI420(jbyte *src_i420_data, jint src_width, jint src_height, jbyte *dst_i420_data,
               jint dst_width, jint dst_height, jint mode) {
    //缩放的模式,0，1，2，3,0的缩放速度是最快的
    jint src_i420_y_size = src_width * src_height;
    jint src_i420_u_size = (src_width >> 1) * (src_height >> 1);
    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_i420_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_i420_y_size + src_i420_u_size;

    jint dst_i420_y_size = dst_width * dst_height;
    jint dst_i420_u_size = (dst_width >> 1) * (dst_height >> 1);
    jbyte *dst_i420_y_data = dst_i420_data;
    jbyte *dst_i420_u_data = dst_i420_data + dst_i420_y_size;
    jbyte *dst_i420_v_data = dst_i420_data + dst_i420_y_size + dst_i420_u_size;

    libyuv::I420Scale(
            (uint8_t *) src_i420_y_data, src_width,
            (uint8_t *) src_i420_u_data, src_width >> 1,
            (uint8_t *) src_i420_v_data, src_width >> 1,
            src_width, src_height,
            (uint8_t *) dst_i420_y_data, dst_width,
            (uint8_t *) dst_i420_u_data, dst_width >> 1,
            (uint8_t *) dst_i420_v_data, dst_width >> 1,
            dst_width, dst_height,
            (libyuv::FilterMode) mode);

}

//i420旋转 旋转之后width和height相反
void rotateI420(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data, jint degree) {
    jint src_i420_y_size = width * height;
    jint src_i420_u_size = (width >> 1) * (height >> 1);

    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_i420_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_i420_y_size + src_i420_u_size;

    jbyte *dst_i420_y_data = dst_i420_data;
    jbyte *dst_i420_u_data = dst_i420_data + src_i420_y_size;
    jbyte *dst_i420_v_data = dst_i420_data + src_i420_y_size + src_i420_u_size;
    //要注意这里的width和height在旋转之后是相反的
    if (degree == libyuv::kRotate90 || degree == libyuv::kRotate270) {
        libyuv::I420Rotate(
                (uint8_t *) src_i420_y_data, width,
                (uint8_t *) src_i420_u_data, width >> 1,
                (uint8_t *) src_i420_v_data, width >> 1,
                (uint8_t *) dst_i420_y_data, height,
                (uint8_t *) dst_i420_u_data, height >> 1,
                (uint8_t *) dst_i420_v_data, height >> 1,
                width, height,
                (libyuv::RotationMode) degree);
    } else {
        libyuv::I420Rotate(
                (uint8_t *) src_i420_y_data, width,
                (uint8_t *) src_i420_u_data, width >> 1,
                (uint8_t *) src_i420_v_data, width >> 1,
                (uint8_t *) dst_i420_y_data, width,
                (uint8_t *) dst_i420_u_data, width >> 1,
                (uint8_t *) dst_i420_v_data, width >> 1,
                width, height,
                (libyuv::RotationMode) degree);
    }
}

//nv21旋转 旋转之后width和height相反
void rotateNV21(jbyte *src_nv21_data, jint width, jint height, jbyte *dst_nv21_data, jint degree) {
    jint src_nv21_y_size = width * height;
    jint src_nv21_u_size = (width >> 1) * (height >> 1);

    jbyte *src_nv21_y_data = src_nv21_data;
    jbyte *src_nv21_u_data = src_nv21_data + src_nv21_y_size;
    jbyte *src_nv21_v_data = src_nv21_data + src_nv21_y_size + src_nv21_u_size;

    jbyte *dst_nv21_y_data = dst_nv21_data;
    jbyte *dst_nv21_u_data = dst_nv21_data + src_nv21_y_size;
    jbyte *dst_nv21_v_data = dst_nv21_data + src_nv21_y_size + src_nv21_u_size;
    //要注意这里的width和height在旋转之后是相反的

    int halfwidth = (width + 1) >> 1;
    int halfheight = (height + 1) >> 1;

    int src_stride_y;
    int src_stride_u;
    int src_stride_v;
    int dst_stride_y;
    int dst_stride_u;
    int dst_stride_v;
    if (degree == libyuv::kRotate90 || degree == libyuv::kRotate270) {
        src_stride_y = width;
        src_stride_u = width >> 1;
        src_stride_v = width >> 1;
        dst_stride_y = height;
        dst_stride_u = height >> 1;
        dst_stride_v = height >> 1;
    } else {
        src_stride_y = width;
        src_stride_u = width >> 1;
        src_stride_v = width >> 1;
        dst_stride_y = width;
        dst_stride_u = width >> 1;
        dst_stride_v = width >> 1;
    }

//    libyuv::RotatePlane((uint8_t *) src_nv21_data, width, (uint8_t *) dst_nv21_data, width, width,
//                        height, (libyuv::RotationMode) degree);
    switch (degree) {
        case libyuv::kRotate0:
            // copy frame
            break;
        case libyuv::kRotate90:
            libyuv::RotatePlane90((uint8_t *) src_nv21_y_data, src_stride_y, (uint8_t *) dst_nv21_y_data,
                                  dst_stride_y, width, height);
            libyuv::RotatePlane90((uint8_t *) src_nv21_u_data, src_stride_u,
                                  (uint8_t *) dst_nv21_u_data, dst_stride_u, halfwidth,
                                  halfheight);
            libyuv::RotatePlane90((uint8_t *) src_nv21_v_data, src_stride_v,
                                  (uint8_t *) dst_nv21_v_data, dst_stride_v, halfwidth,
                                  halfheight);
            break;
        case libyuv::kRotate270:
            libyuv::RotatePlane270((uint8_t *) src_nv21_y_data, src_stride_y, (uint8_t *) dst_nv21_y_data,
                                   dst_stride_y, width, height);
            libyuv::RotatePlane270((uint8_t *) src_nv21_u_data, src_stride_u,
                                   (uint8_t *) dst_nv21_u_data, dst_stride_u, halfwidth,
                                   halfheight);
            libyuv::RotatePlane270((uint8_t *) src_nv21_v_data, src_stride_v,
                                   (uint8_t *) dst_nv21_v_data, dst_stride_v, halfwidth,
                                   halfheight);
            break;
        case libyuv::kRotate180:
            libyuv::RotatePlane180((uint8_t *) src_nv21_y_data, src_stride_y, (uint8_t *) dst_nv21_y_data,
                                   dst_stride_y, width, height);
            libyuv::RotatePlane180((uint8_t *) src_nv21_u_data, src_stride_u,
                                   (uint8_t *) dst_nv21_u_data, dst_stride_u, halfwidth,
                                   halfheight);
            libyuv::RotatePlane180((uint8_t *) src_nv21_v_data, src_stride_v,
                                   (uint8_t *) dst_nv21_v_data, dst_stride_v, halfwidth,
                                   halfheight);
            break;
        default:
            break;
    }

}

void RotateI420fff(jbyte *src_i420_data, jint width, jint height,
                   jbyte *dst_i420_data, jint degree) {
    jint I420_Y_Size = width * height;
    jint I420_U_Size = (width >> 1) * (height >> 1);
    jint I420_V_Size = I420_U_Size;

    // src: buffer address of  Y channel、U channel and V channel
    jbyte *Y_data_Src = src_i420_data;
    jbyte *U_data_Src = src_i420_data + I420_Y_Size;
    jbyte *V_data_Src = src_i420_data + I420_Y_Size + I420_U_Size;
    jint src_stride_y = width;
    jint src_stride_u = width >> 1;
    jint src_stride_v = src_stride_u;

    //dst: buffer address of Y channel、U channel and V channel
    jbyte *Y_data_Dst = dst_i420_data;
    jbyte *U_data_Dst = dst_i420_data + I420_Y_Size;
    jbyte *V_data_Dst = dst_i420_data + I420_Y_Size + I420_U_Size;
    jint Dst_Stride_Y;
    jint Dst_Stride_U;
    jint Dst_Stride_V;
    if (degree == libyuv::kRotate90 || degree == libyuv::kRotate270) {
        Dst_Stride_Y = height;
        Dst_Stride_U = height >> 1;
        Dst_Stride_V = Dst_Stride_U;
    } else {
        Dst_Stride_Y = width;
        Dst_Stride_U = width >> 1;
        Dst_Stride_V = Dst_Stride_U;
    }

    libyuv::I420Rotate(
            (uint8_t *) Y_data_Src, src_stride_y,
            (uint8_t *) U_data_Src, src_stride_u,
            (uint8_t *) V_data_Src, src_stride_v,
            (uint8_t *) Y_data_Dst, Dst_Stride_Y,
            (uint8_t *) U_data_Dst, Dst_Stride_U,
            (uint8_t *) V_data_Dst, Dst_Stride_V,
            width, height,
            (libyuv::RotationMode) degree);
}

void MirrorI420(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data) {
    jint src_i420_y_size = width * height;
    // jint src_i420_u_size = (width >> 1) * (height >> 1);
    jint src_i420_u_size = src_i420_y_size >> 2;

    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_i420_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_i420_y_size + src_i420_u_size;

    jbyte *dst_i420_y_data = dst_i420_data;
    jbyte *dst_i420_u_data = dst_i420_data + src_i420_y_size;
    jbyte *dst_i420_v_data = dst_i420_data + src_i420_y_size + src_i420_u_size;

    libyuv::I420Mirror((uint8_t *) src_i420_y_data, width,
                       (uint8_t *) src_i420_u_data, width >> 1,
                       (uint8_t *) src_i420_v_data, width >> 1,
                       (uint8_t *) dst_i420_y_data, width,
                       (uint8_t *) dst_i420_u_data, width >> 1,
                       (uint8_t *) dst_i420_v_data, width >> 1,
                       width, height);
}

void CropI420(jbyte *src_i420_data, jint src_length, jint width, jint height,
              jbyte *dst_i420_data, jint dst_width, jint dst_height, jint left, jint top) {
    jint dst_i420_y_size = dst_width * dst_height;
    jint dst_i420_u_size = (dst_width >> 1) * (dst_height >> 1);

    jbyte *dst_i420_y_data = dst_i420_data;
    jbyte *dst_i420_u_data = dst_i420_data + dst_i420_y_size;
    jbyte *dst_i420_v_data = dst_i420_data + dst_i420_y_size + dst_i420_u_size;

    libyuv::ConvertToI420((uint8_t *) src_i420_data, src_length,
                          (uint8_t *) dst_i420_y_data, dst_width,
                          (uint8_t *) dst_i420_u_data, dst_width >> 1,
                          (uint8_t *) dst_i420_v_data, dst_width >> 1,
                          left, top,
                          width, height,
                          dst_width, dst_height,
                          libyuv::kRotate0, libyuv::FOURCC_I420);
}

//void NV21ToI420(jbyte *src_nv21_data, jint width, jint height, jbyte *src_i420_data) {
//    jint src_y_size = width * height;
//    jint src_u_size = (width >> 1) * (height >> 1);
//
//    jbyte *src_nv21_y_data = src_nv21_data;
//    jbyte *src_nv21_vu_data = src_nv21_data + src_y_size;
//
//    jbyte *src_i420_y_data = src_i420_data;
//    jbyte *src_i420_u_data = src_i420_data + src_y_size;
//    jbyte *src_i420_v_data = src_i420_data + src_y_size + src_u_size;
//
//
//    libyuv::NV21ToI420( (uint8_t *) src_nv21_y_data, width,
//                        (uint8_t *) src_nv21_vu_data, width,
//                       (uint8_t *)src_i420_y_data, width,
//                       (uint8_t *)src_i420_u_data, width >> 1,
//                       (uint8_t *)src_i420_v_data, width >> 1,
//                       width, height);
//}

//void NV12ToI420(jbyte *Src_data, jint src_width, jint src_height, jbyte *Dst_data) {
//    // NV12 video size
//    jint NV12_Size = src_width * src_height * 3 / 2;
//    jint NV12_Y_Size = src_width * src_height;
//
//    // YUV420 video size
//    jint I420_Size = src_width * src_height * 3 / 2;
//    jint I420_Y_Size = src_width * src_height;
//    jint I420_U_Size = (src_width >> 1) * (src_height >> 1);
//    jint I420_V_Size = I420_U_Size;
//
//    // src: buffer address of Y channel and UV channel
//    jbyte *Y_data_Src = Src_data;
//    jbyte *UV_data_Src = Src_data + NV12_Y_Size;
//    jint src_stride_y = src_width;
//    jint src_stride_uv = src_width;
//
//    //dst: buffer address of Y channel、U channel and V channel
//    jbyte *Y_data_Dst = Dst_data;
//    jbyte *U_data_Dst = Dst_data + I420_Y_Size;
//    jbyte *V_data_Dst = Dst_data + I420_Y_Size + I420_U_Size;
//    jint Dst_Stride_Y = src_width;
//    jint Dst_Stride_U = src_width >> 1;
//    jint Dst_Stride_V = Dst_Stride_U;
//
//    libyuv::NV12ToI420( (uint8_t *) Y_data_Src, src_stride_y,
//                        (uint8_t *) UV_data_Src, src_stride_uv,
//                       (uint8_t *)Y_data_Dst, Dst_Stride_Y,
//                       (uint8_t *)U_data_Dst, Dst_Stride_U,
//                       (uint8_t *)V_data_Dst, Dst_Stride_V,
//                       src_width, src_height);
//}

void I420ToNv12(jbyte *src_i420_data, jint width, jint height, jbyte *src_nv12_data) {
    jint src_y_size = width * height;
    jint src_u_size = (width >> 1) * (height >> 1);

    jbyte *src_nv12_y_data = src_nv12_data;
    jbyte *src_nv12_uv_data = src_nv12_data + src_y_size;

    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_y_size + src_u_size;


    libyuv::I420ToNV12(
            (uint8_t *) src_i420_y_data, width,
            (uint8_t *) src_i420_u_data, width >> 1,
            (uint8_t *) src_i420_v_data, width >> 1,
            (uint8_t *) src_nv12_y_data, width,
            (uint8_t *) src_nv12_uv_data, width,
            width, height);
}

void I420ToRGB24(jbyte *src_i420_data, jint width, jint height, jbyte *dst_rgb24_data) {

    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);

    libyuv::I420ToRGB24(
            (uint8_t *) yplane, width,
            (uint8_t *) uplane, width / 2,
            (uint8_t *) vplane, width / 2,
            (uint8_t *) dst_rgb24_data, width * 3,
            width, height);
}

void I420ToARGB(jbyte *src_i420_data, jint width, jint height,
                jint dst_stride, jbyte *dst_argb_data) {

    if (dst_stride == 0 || dst_stride == width)
        dst_stride = width * 4;
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);

    libyuv::I420ToARGB(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_argb_data, dst_stride,
            width, height);
}

void I420ToRGBAMac(jbyte *src_i420_data, jint width, jint height, jint dst_stride,
                   jbyte *dst_rgba_mac_data) {
    // Equivalent to Convert YV12ToBGRA.
    // YV12 same as I420 with U and V swapped.
    if (dst_stride == 0 || dst_stride == width) dst_stride = 4 * width;
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    libyuv::I420ToBGRA(
            (const uint8_t *) yplane, width,
            (const uint8_t *) vplane, width / 2,
            (const uint8_t *) uplane, width / 2,
            (uint8_t *) dst_rgba_mac_data, dst_stride,
            width, height);
}

void I420ToARGB4444(jbyte *src_i420_data, jint width, jint height, jint dst_stride,
                    jbyte *dst_argb4444_data) {
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = 2 * width;
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    libyuv::I420ToARGB4444(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_argb4444_data, dst_stride,
            width, height);
}

void I420ToRGB565(jbyte *src_i420_data, jint width, jint height, jbyte *dst_rgb565_data) {
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    libyuv::I420ToRGB565(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_rgb565_data, width,
            width, height);
}

void I420ToRGB565Android(jbyte *src_i420_data, jint width, jint height, jbyte *dst_rgb565_data) {
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    // Same as RGB565 + inversion - set negative height.
    height = -height;
    libyuv::I420ToRGB565(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_rgb565_data, width,
            width, height);
}

void I420ToARGB1555(jbyte *src_i420_data, jint width, jint height, jint dst_stride,
                    jbyte *dst_argb1555_data) {
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = 2 * width;
    else if (dst_stride < 2 * width)
        return;
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    libyuv::I420ToARGB1555(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_argb1555_data, dst_stride,
            width, height);
}

void I420ToYUY2(jbyte *src_i420_data, jint width, jint height,
                jint dst_stride, jbyte *dst_yuy2_data) {
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = 2 * width;
    libyuv::I420ToYUY2(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_yuy2_data, dst_stride,
            width, height);
}

void I420ToUYVY(jbyte *src_i420_data, jint width, jint height,
                jint dst_stride, jbyte *dst_uyvy_data) {
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = 2 * width;
    else if (dst_stride < width)
        return;
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    libyuv::I420ToUYVY(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_uyvy_data, dst_stride,
            width, height);
}

void I420ToYV12(jbyte *src_i420_data, jint width, jint height,
                jint dst_stride, jbyte *dst_yv12_data) {
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = width;
    else if (dst_stride < width)
        return;
    jbyte *src_yplane = src_i420_data;
    jbyte *src_uplane = src_i420_data + width * height;
    jbyte *src_vplane = src_uplane + (width * height / 4);
    jbyte *dst_yplane = dst_yv12_data;
    jbyte *dst_uplane = dst_yv12_data + width * height;

    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    // YV12 is YVU => Use I420(YUV) copy and flip U and V.
    libyuv::I420Copy((const uint8_t *) src_yplane, width,
                     (const uint8_t *) src_vplane, width / 2,
                     (const uint8_t *) src_uplane, width / 2,
                     (uint8_t *) dst_yplane, dst_stride,
                     (uint8_t *) dst_uplane, dst_stride / 2,
                     (uint8_t *) dst_vplane, dst_stride / 2,
                     width, height);
}

void YV12ToI420(jbyte *src_yv12_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_yv12_data;
    jbyte *src_uplane = src_yv12_data + width * height;
    jbyte *src_vplane = src_uplane + (width * height / 4);
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    // YV12 is YVU => Use I420(YUV) copy and flip U and V.
    libyuv::I420Copy(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_vplane, width / 2,
            (const uint8_t *) src_uplane, width / 2,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height);
}

void NV12ToI420(jbyte *src_nv21_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_nv21_data;
    jbyte *src_uvplane = src_nv21_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height);
}

void I420ToNv21(jbyte *src_i420_data, jint width, jint height, jbyte *dst_nv21_data) {
    jint src_y_size = width * height;
    jint src_u_size = (width >> 1) * (height >> 1);

    jbyte *dst_nv21_y_data = dst_nv21_data;
    jbyte *dst_nv21_uv_data = dst_nv21_data + src_y_size;

    jbyte *src_i420_y_data = src_i420_data;
    jbyte *src_i420_u_data = src_i420_data + src_y_size;
    jbyte *src_i420_v_data = src_i420_data + src_y_size + src_u_size;


    libyuv::I420ToNV21(
            (uint8_t *) src_i420_y_data, width,
            (uint8_t *) src_i420_u_data, width >> 1,
            (uint8_t *) src_i420_v_data, width >> 1,
            (uint8_t *) dst_nv21_y_data, width,
            (uint8_t *) dst_nv21_uv_data, width,
            width, height);
}

void NV12ToI420AndRotate180(jbyte *src_nv12_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_nv12_data;
    jbyte *src_uvplane = src_nv12_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420Rotate(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height,
            libyuv::kRotate180);
}

void NV12ToI420AndRotateClockwise(jbyte *src_nv12_data, jint width, jint height,
                                  jbyte *dst_i420_data) {
    jbyte *src_yplane = src_nv12_data;
    jbyte *src_uvplane = src_nv12_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420Rotate(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height,
            libyuv::kRotate90);
}

void NV12ToI420AndRotateAntiClockwise(jbyte *src_nv12_data, jint width, jint height,
                                      jbyte *dst_i420_data) {
    jbyte *src_yplane = src_nv12_data;
    jbyte *src_uvplane = src_nv12_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420Rotate(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height,
            libyuv::kRotate270);
}

void NV12ToRGB565(jbyte *src_nv12_data, jint width, jint height, jbyte *dst_rgb565_data) {
    jbyte *yplane = src_nv12_data;
    jbyte *uvInterlaced = src_nv12_data + (width * height);
    libyuv::NV12ToRGB565(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uvInterlaced, width / 2,
            (uint8_t *) dst_rgb565_data, width,
            width, height);
}

void NV21ToI420(jbyte *src_nv21_data, jint width, jint height, jbyte *dst_i420_data) {
    // NV21 = y plane followed by an interleaved V/U plane, i.e. same as NV12
    // but the U and the V are switched. Use the NV12 function and switch the U
    // and V planes.
    jbyte *src_yplane = src_nv21_data;
    jbyte *src_uvplane = src_nv21_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_vplane, width / 2,
            (uint8_t *) dst_uplane, width / 2,
            width, height);
}

void NV21ToI420AndRotate180(jbyte *src_nv21_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_nv21_data;
    jbyte *src_uvplane = src_nv21_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420Rotate(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_vplane, width / 2,
            (uint8_t *) dst_uplane, width / 2,
            width, height,
            libyuv::kRotate180);
}

void NV21ToI420AndRotateClockwise(jbyte *src_nv21_data, jint width,
                                  jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_nv21_data;
    jbyte *src_uvplane = src_nv21_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420Rotate(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_vplane, width / 2,
            (uint8_t *) dst_uplane, width / 2,
            width, height,
            libyuv::kRotate90);
}

void NV21ToI420AndRotateAntiClockwise(jbyte *src_nv21_data, jint width,
                                      jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_nv21_data;
    jbyte *src_uvplane = src_nv21_data + width * height;
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::NV12ToI420Rotate(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uvplane, width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_vplane, width / 2,
            (uint8_t *) dst_uplane, width / 2,
            width, height,
            libyuv::kRotate270);
}

void I420ToRGBAIPhone(jbyte *src_i420_data, jint width, jint height,
                      jint dst_stride, jbyte *dst_rgba_data) {
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = 4 * width;
    else if (dst_stride < 4 * width)
        return;
    jbyte *yplane = src_i420_data;
    jbyte *uplane = src_i420_data + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    // RGBAIPhone = ABGR
    libyuv::I420ToABGR(
            (const uint8_t *) yplane, width,
            (const uint8_t *) uplane, width / 2,
            (const uint8_t *) vplane, width / 2,
            (uint8_t *) dst_rgba_data, dst_stride,
            width, height);
}

void I420Copy(jbyte *src_i420_data, jint width, jint height,
              jint dst_stride, jbyte *dst_i420_data) {

    if (dst_stride == 0)
        dst_stride = width;
    jbyte *src_yplane = src_i420_data;
    jbyte *src_uplane = src_i420_data + width * height;
    jbyte *src_vplane = src_uplane + (width * height / 4);
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::I420Copy(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uplane, width / 2,
            (const uint8_t *) src_vplane, width / 2,
            (uint8_t *) dst_yplane, dst_stride,
            (uint8_t *) dst_uplane, dst_stride / 2,
            (uint8_t *) dst_vplane, dst_stride / 2,
            width, height);
}

void UYVYToI420(jbyte *src_uyvy_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::UYVYToI420(
            (const uint8_t *) src_uyvy_data, 2 * width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height);
}

void YUY2ToI420(jbyte *src_yuy2_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::YUY2ToI420(
            (const uint8_t *) src_yuy2_data, 2 * width,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height);
}

void RGB24ToARGB(jbyte *src_rbg24_data, jint width, jint height,
                 jint dst_stride, jbyte *dst_argb_data) {
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = width;
    // Stride - currently webrtc style
    libyuv::RGB24ToARGB(
            (const uint8_t *) src_rbg24_data, width,
            (uint8_t *) dst_argb_data, dst_stride,
            width, height);
}

void RGB24ToI420(jbyte *src_rbg24_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *yplane = dst_i420_data;
    jbyte *uplane = yplane + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    // WebRtc expects a vertical flipped image.
    libyuv::RGB24ToI420(
            (const uint8_t *) src_rbg24_data, width * 3,
            (uint8_t *) yplane, width,
            (uint8_t *) uplane, width / 2,
            (uint8_t *) vplane, width / 2,
            width, -height);
}

void I420ToARGBMac(jbyte *src_i420_data, jint width, jint height,
                   jint dst_stride, jbyte *dst_argb_mac_data) {
    // Equivalent to YV12ToARGB.
    // YV12 = YVU => use I420 and interchange U and V.
    jbyte *yplane = src_i420_data;
    jbyte *uplane = yplane + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    if (dst_stride == 0 || dst_stride == width)
        dst_stride = 4 * width;
    else if (dst_stride < 4 * width)
        return;
    libyuv::I420ToARGB(
            (const uint8_t *) yplane, width,
            (const uint8_t *) vplane, width / 2,
            (const uint8_t *) uplane, width / 2,
            (uint8_t *) dst_argb_mac_data, dst_stride,
            width, height);
}

void ARGBMacToI420(jbyte *src_argb_mac_data, jint width, jint height, jbyte *dst_i420_data) {
    // Equivalent to BGRAToI420
    jbyte *yplane = dst_i420_data;
    jbyte *uplane = yplane + width * height;
    jbyte *vplane = uplane + (width * height / 4);
    libyuv::BGRAToI420(
            (const uint8_t *) src_argb_mac_data, width * 4,
            (uint8_t *) yplane, width,
            (uint8_t *) uplane, width / 2,
            (uint8_t *) vplane, width / 2,
            width, height);
}

void MirrorI420LeftRight(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_i420_data;
    jbyte *src_uplane = src_yplane + width * height;
    jbyte *src_vplane = src_uplane + (width * height / 4);
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_yplane + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);
    libyuv::I420Mirror(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uplane, width / 2,
            (const uint8_t *) src_vplane, width / 2,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, height);
}

void MirrorI420UpDown(jbyte *src_i420_data, jint width, jint height, jbyte *dst_i420_data) {
    jbyte *src_yplane = src_i420_data;
    jbyte *src_uplane = src_i420_data + width * height;
    jbyte *src_vplane = src_uplane + (width * height / 4);
    jbyte *dst_yplane = dst_i420_data;
    jbyte *dst_uplane = dst_i420_data + width * height;
    jbyte *dst_vplane = dst_uplane + (width * height / 4);

    // Inserting negative height flips the frame.
    libyuv::I420Copy(
            (const uint8_t *) src_yplane, width,
            (const uint8_t *) src_uplane, width / 2,
            (const uint8_t *) src_vplane, width / 2,
            (uint8_t *) dst_yplane, width,
            (uint8_t *) dst_uplane, width / 2,
            (uint8_t *) dst_vplane, width / 2,
            width, -height);
}