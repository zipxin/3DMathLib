#include "O3DMath.h"
#include "OMathUtil.h"

OMatrix4x4 ORMatrixLookAtRH(OVector4 eye, OVector4 look, OVector4 up)
{
	OVector4 UpNormarlize = Vec4_Normalize(up);
	OVector4 zAxis = eye - look;
	zAxis.Nomarlize();
	OVector4 xAxis = Vec4_CrossProduct(zAxis, up);
	OVector4 yAxis = Vec4_CrossProduct(zAxis, xAxis);

	OMatrix4x4 viewMatrix = OMatrix4x4::GetIdentityMatrix();
	viewMatrix.SetColumn(0,xAxis);
	viewMatrix.SetColumn(1,yAxis);
	viewMatrix.SetColumn(2,zAxis);

	viewMatrix[3][0] = -Vec4_Dotf(xAxis, eye);
	viewMatrix[3][1] = -Vec4_Dotf(yAxis, eye);
	viewMatrix[3][2] = -Vec4_Dotf(zAxis, eye);
	return viewMatrix;
}

OMatrix4x4 ORMatrixLookAtLH(OVector4 eye, OVector4 look, OVector4 up)
{
	OVector4 UpNormarlize = Vec4_Normalize(up);
	OVector4 zAxis = look - eye;
	zAxis.Nomarlize();
	OVector4 xAxis = Vec4_CrossProduct(zAxis, up);
	OVector4 yAxis = Vec4_CrossProduct(zAxis, xAxis);

	OMatrix4x4 viewMatrix = OMatrix4x4::GetIdentityMatrix();
	viewMatrix.SetColumn(0,xAxis);
	viewMatrix.SetColumn(1,yAxis);
	viewMatrix.SetColumn(2,zAxis);

	viewMatrix[3][0] = -Vec4_Dotf(xAxis, eye);
	viewMatrix[3][1] = -Vec4_Dotf(yAxis, eye);
	viewMatrix[3][2] = -Vec4_Dotf(zAxis, eye);
	return viewMatrix;
}

OMatrix4x4 ORMatrixOrthoRH_OpenGL(float32 w, float32 h,float32 near,float32 far)
{
	OMatrix4x4 orthoMatrix;
	orthoMatrix.Identity();
	float32 dist = near - far;
	orthoMatrix[0][0] = 2 / w;
	orthoMatrix[1][1] = 2 / h;
	orthoMatrix[2][2] = 2 / dist;
	orthoMatrix[3][2] = (far + near) / dist;
	orthoMatrix[3][3] = 1.0f;
	return orthoMatrix;
}


OMatrix4x4 ORMatrixOrthoLH_DirectX(float32 w, float32 h,float32 near,float32 far)
{
	OMatrix4x4 orthoMatrix;
	orthoMatrix.Identity();
	float32 dist = far - near;
	orthoMatrix[0][0] = 2 / w;
	orthoMatrix[1][1] = 2 / h;
	orthoMatrix[2][2] = 1 / dist;
	orthoMatrix[3][2] = near / dist;
	orthoMatrix[3][3] = 1.0f;
	return orthoMatrix;
}

//注意OpenGL与DirectX都是使用z y 平面进行投影计算的
OMatrix4x4 ORMatrixPerspectiveRH_OpenGL(float32 fov, float32 aspect, float32 near, float32 far)
{
	OMatrix4x4 perspectiveMatrix;
	perspectiveMatrix.Identity();
	float32 fovRad  = fov * DEG_TO_RAD;
	float32 yscale = OCot(fovRad * 0.5f);
	float32 xscale = yscale * aspect;

	float32 dist = near - far;
	perspectiveMatrix[0][0] = xscale;
	perspectiveMatrix[1][1] = yscale;
	perspectiveMatrix[2][2] = (far + near)/( dist );
	perspectiveMatrix[2][3] = -1.0f;
	perspectiveMatrix[3][2] = 2.0f * far * near / ( dist );
	perspectiveMatrix[3][3] = 0.0f;
	return perspectiveMatrix;
}

OMatrix4x4 ORMatrixPerspectiveLH_OpenGL(float32 fov, float32 aspect, float32 near, float32 far)
{
	OMatrix4x4 perspectiveMatrix;
	perspectiveMatrix.Identity();
	float32 fovRad  = fov * DEG_TO_RAD;
	float32 yscale = OCot(fovRad * 0.5f);
	float32 xscale = yscale * aspect;

	float32 dist = far - near;
	perspectiveMatrix[0][0] = xscale;
	perspectiveMatrix[1][1] = yscale;
	perspectiveMatrix[2][2] = (far + near)/( dist );
	perspectiveMatrix[2][3] = 1.0f;
	perspectiveMatrix[3][2] = 2.0f * far * near / ( dist );
	perspectiveMatrix[3][3] = 0.0f;
	return perspectiveMatrix;
}


OMatrix4x4 ORMatrixPerspectiveLH_DirectX(float32 fovy, float32 aspect, float32 near, float32 far)
{
	OMatrix4x4 perspectiveMatrix;
	perspectiveMatrix.Identity();

	float fovy_radian = DEG_TO_RAD * (fovy);
	float yscale = OCot(fovy_radian/2.0f);
	float xscale = yscale * aspect;

	float32 dist = far - near;

	perspectiveMatrix[0][0] = xscale;
	perspectiveMatrix[1][1] = yscale;
	perspectiveMatrix[2][2] = far / ( dist );
	perspectiveMatrix[2][3] = 1.0f;
	perspectiveMatrix[3][2] = -(near * far) /( dist );
	perspectiveMatrix[3][3] = 0.0f;

	return perspectiveMatrix;
}


OMatrix4x4 ORMatrixPerspectiveRH_DirectX(float32 fovy, float32 aspect,  float32 near, float32 far)
{
	OMatrix4x4 perspectiveMatrix;
	perspectiveMatrix.Identity();

	float fovy_radian =  DEG_TO_RAD * (fovy);
	float yscale = OCot(fovy_radian/2.0f);
	float xscale = yscale * aspect;

	float32 dist = near - far;
	perspectiveMatrix[0][0] = xscale;
	perspectiveMatrix[1][1] = yscale;
	perspectiveMatrix[2][2] = far / ( dist );
	perspectiveMatrix[2][3] = -1.0f;
	perspectiveMatrix[3][2] = (near * far) /( dist );
	perspectiveMatrix[3][3] = 0.0f;

	return perspectiveMatrix;
}
