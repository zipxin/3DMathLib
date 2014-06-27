#ifndef ONLY_3D_MATH_H_
#define ONLY_3D_MATH_H_

/*
OR OnlyRender
Matrix ���ؾ���
RH ����ϵ
LH ����ϵ
*/
#include "OMatrix4x4.h"
#include "OVector4.h"

//һЩͬ����Ⱦ��ȫ�ֺ���

//������������������ı仯����
OMatrix4x4 ORMatrixLookAtRH(OVector4 eye, OVector4 look, OVector4 up);
OMatrix4x4 ORMatrixLookAtLH(OVector4 eye, OVector4 look, OVector4 up);


//��������ͶӰ����
OMatrix4x4 ORMatrixOrthoRH_OpenGL(float32 w, float32 h,float32 near,float32 far);
OMatrix4x4 ORMatrixOrthoLH_DirectX(float32 w, float32 h,float32 near,float32 far);

//����͸��ͶӰ����
OMatrix4x4 ORMatrixPerspectiveRH_OpenGL(float32 fov, float32 aspect, float32 near, float32 far);
OMatrix4x4 ORMatrixPerspectiveLH_OpenGL(float32 fov, float32 aspect, float32 near, float32 far);

OMatrix4x4 ORMatrixPerspectiveRH_DirectX(float32 fov, float32 aspect, float32 near, float32 far);
OMatrix4x4 ORMatrixPerspectiveLH_DirectX(float32 fov, float32 aspect, float32 near, float32 far);



#endif /* File is Over */