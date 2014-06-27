#ifndef ONLY_3D_MATH_H_
#define ONLY_3D_MATH_H_

/*
OR OnlyRender
Matrix 返回矩阵
RH 右手系
LH 左手系
*/
#include "OMatrix4x4.h"
#include "OVector4.h"

//一些同样渲染的全局函数

//返回世界矩阵到相机矩阵的变化矩阵
OMatrix4x4 ORMatrixLookAtRH(OVector4 eye, OVector4 look, OVector4 up);
OMatrix4x4 ORMatrixLookAtLH(OVector4 eye, OVector4 look, OVector4 up);


//返回正交投影矩阵
OMatrix4x4 ORMatrixOrthoRH_OpenGL(float32 w, float32 h,float32 near,float32 far);
OMatrix4x4 ORMatrixOrthoLH_DirectX(float32 w, float32 h,float32 near,float32 far);

//返回透视投影矩阵
OMatrix4x4 ORMatrixPerspectiveRH_OpenGL(float32 fov, float32 aspect, float32 near, float32 far);
OMatrix4x4 ORMatrixPerspectiveLH_OpenGL(float32 fov, float32 aspect, float32 near, float32 far);

OMatrix4x4 ORMatrixPerspectiveRH_DirectX(float32 fov, float32 aspect, float32 near, float32 far);
OMatrix4x4 ORMatrixPerspectiveLH_DirectX(float32 fov, float32 aspect, float32 near, float32 far);



#endif /* File is Over */