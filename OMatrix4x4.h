//////////////////////////////////////////////////////////////////////////
//File : Only Matrix4x4 ( Only Math Lib)
//Author : Zipxin  [China]
//Project : OnlyGameEngine
//E-mail: zipxin@163.com
//Note:   使用行向量
//////////////////////////////////////////////////////////////////////////
#ifndef _ONLY_MATRIX4X4_H_
#define _ONLY_MATRIX4X4_H_

#include "../OInclude/Common/OnlyGameDefine.h"

//Declare/////////////////////////////////////////////////////////////////
class OMatrix4x4;
class OVector4;
class OVector3;
class OMatrix3x3;


#include "../OInclude/Math/OVector4.h"
#include "../OInclude/Math/OVector3.h"
#include "../OInclude/Math/OMatrix3x3.h"

//////////////////////////////////////////////////////////////////////////
//Construct
//////////////////////////////////////////////////////////////////////////
//Getter Setter
//////////////////////////////////////////////////////////////////////////
//Store
//////////////////////////////////////////////////////////////////////////
//Function
//////////////////////////////////////////////////////////////////////////
//Operator 
//////////////////////////////////////////////////////////////////////////
//static Function
//////////////////////////////////////////////////////////////////////////


//Global//////////////////////////////////////////////////////////////////
extern OMatrix4x4 g_Matrix4x4_Identity;
extern OMatrix4x4 g_Matrix4x4_Zero;

//Define
class OMatrix4x4
{
public:

	union 
	{
		float32 ele_f[4][4];
		int32 ele_i[4][4];
		struct 
		{
			float32 m11, m12, m13, m14;
			float32 m21, m22, m23, m24;
			float32 m31, m32, m33, m34;
			float32 m41, m42, m43, m44;
		};
		struct
		{
			OVector4 vec1;
			OVector4 vec2;
			OVector4 vec3;
			OVector4 vec4;
		};
	};

public:
	static const OMatrix4x4 ZERO;
    static const OMatrix4x4 IDENTITY;

    /** Useful little matrix which takes 2D clipspace {-1, 1} to {0,1}
        and inverts the Y. */
    static const OMatrix4x4 CLIPSPACE2DTOIMAGESPACE;

	inline OMatrix4x4(){}
	inline OMatrix4x4(
		float32 f00, float32 f01, float32 f02, float32 f03,
		float32 f10, float32 f11, float32 f12, float32 f13,
		float32 f20, float32 f21, float32 f22, float32 f23,
		float32 f30, float32 f31, float32 f32, float32 f33
		)
	{
		m11 = f00; m12 = f01; m13 = f02; m14 = f03;
		m21 = f10; m22 = f11; m23 = f12; m24 = f13;
		m31 = f20; m32 = f21; m33 = f22; m34 = f23;
		m41 = f30; m42 = f31; m43 = f32; m44 = f33;
	}

	inline OMatrix4x4
		(OVector4 &v1, OVector4 &v2, OVector4 &v3, OVector4 &v4 = g_Vector4f_Zero)
		:vec1(v1),vec2(v2),vec3(v3),vec4(v4){}

	inline OMatrix4x4(const OMatrix4x4 &m) {
		vec1 = m.vec1;
		vec2 = m.vec2;
		vec3 = m.vec3;
		vec4 = m.vec4;
	}

	explicit OMatrix4x4(const OMatrix3x3& matrix) :
		m11(matrix.m11),
		m12(matrix.m12),
		m13(matrix.m13),
		m14(0.0f),
		m21(matrix.m21),
		m22(matrix.m22),
		m23(matrix.m23),
		m24(0.0f),
		m31(matrix.m31),
		m32(matrix.m32),
		m33(matrix.m33),
		m34(0.0f),
		m41(0.0f),
		m42(0.0f),
		m43(0.0f),
		m44(1.0f)
	{
	}
	explicit OMatrix4x4(const float32* data) :
		m11(data[0]),
		m12(data[1]),
		m13(data[2]),
		m14(data[3]),
		m21(data[4]),
		m22(data[5]),
		m23(data[6]),
		m24(data[7]),
		m31(data[8]),
		m32(data[9]),
		m33(data[10]),
		m34(data[11]),
		m41(data[12]),
		m42(data[13]),
		m43(data[14]),
		m44(data[15])
	{
	}

	~OMatrix4x4(){};

//////////////////////////////////////////////////////////////////////////
	inline void SetZero()
	{
		m11 = m12 = m13 = m14 = 0.0f;
		m21 = m22 = m23 = m24 = 0.0f;
		m31 = m32 = m33 = m34 = 0.0f;
		m41 = m42 = m43 = m44 = 0.0f;
	}

	inline void SetRow(const int32 row, OVector4 &vec)
	{
		assert( row>=0 && row<4 );
		OVector4 *rows = &vec1;
		rows[row] = vec;
	}

	inline void SetColumn(const int32 column, OVector4 &vec)
	{
		assert( column>=0 && column<4 );
		float *p = &m11 + column;
		p[0] =  vec.GetXf(); 
		p[4] =  vec.GetYf(); 
		p[8] =  vec.GetZf(); 
		p[12] = vec.GetWf(); 
	}

	inline OVector4 &GetRow(const int32 row)
	{
		assert( row>=0 && row<4 );
		OVector4 *rows = &vec1;
		return rows[row];
	}

	inline const OVector4 &GetRow(const int32 row) const
	{
		assert( row>=0 && row<4 );
		const OVector4 *rows = &vec1;
		return rows[row];
	}

	inline OVector4 GetColumn(const int32 column)
	{
		assert(column>=0 && column<4);
		OVector4 vec;
		float *p = &m11 + column;

		vec.SetXf(p[0]);
		vec.SetYf(p[4]);
		vec.SetZf(p[8]);
		vec.SetWf(p[12]);
		return vec;
	}

	inline const OVector4 GetColumn(const int32 column) const
	{
		assert(column>=0 && column<4);
		OVector4 vec;
		const float *p = &m11 + column;

		vec.SetXf(p[0]);
		vec.SetYf(p[4]);
		vec.SetZf(p[8]);
		vec.SetWf(p[12]);
		return vec;
	}

	/** 得到4*4矩阵右方向的标准基,结果是个单位向量 */
	OVector3 GetRight() const { return OVector3(ele_f[0][0], ele_f[0][1], ele_f[0][2]).Nomarlized(); }
	/** 得到4*4矩阵上方向的标准基,结果是个单位向量 */
	OVector3 GetUp() const { return OVector3(ele_f[1][0], ele_f[1][1], ele_f[1][2]).Nomarlized(); }
	/** 得到4*4矩阵前方向的标准基,结果是个单位向量 */
	OVector3 GetDir() const { return OVector3(ele_f[2][0], ele_f[2][1], ele_f[2][2]).Nomarlized(); }


	/** 得到4*4矩阵右方向的非标准基,结果未被单位化 */
	OVector3 GetRightUnnormalized() const { return OVector3(ele_f[0][0], ele_f[0][1], ele_f[0][2]); }
	/** 得到4*4矩阵上方向的非标准基,结果未被单位化 */
	OVector3 GetUpUnnormalized() const { return OVector3(ele_f[1][0], ele_f[1][1], ele_f[1][2]); }
	/** 得到4*4矩阵前方向的非标准基,结果未被单位化 */
	OVector3 GetDirUnnormalized() const { return OVector3(ele_f[2][0], ele_f[2][1], ele_f[2][2]); }

	/** 得到这样一个4*4矩阵：它乘以对象矩阵后，让对象矩阵得到分别绕XYZ三轴旋转参数弧度后的效果 */
	OMatrix4x4 RotaieXYZ_Replace(float radianX, float radianY,  float radianZ);

//////////////////////////////////////////////////////////////////////////

	inline OMatrix4x4 &Transpose(void)
	{
		OSwap<float32>(m12,m21);
		OSwap<float32>(m13,m31);
		OSwap<float32>(m14,m41);
		OSwap<float32>(m23,m32);
		OSwap<float32>(m24,m42);
		OSwap<float32>(m34,m43);
		return *this;
	}

	inline void Identity(void)
	{
		*this = g_Matrix4x4_Identity;
	}

	//之所以是快速转置是又原因的
	//正交矩阵
	inline OMatrix4x4 &FastInvert(void)
	{
		OVector4 pos = Vec4_InvertSign(vec4);
		vec4 =  g_Matrix4x4_Identity.vec4;

		Transpose();
		Translate(pos);

		return *this;
	}

	void NoTranslate(void)
	{
		vec4 = GetIdentityMatrix()[3];
	}

	/** 用一个3维向量来设定4*4矩阵的投影变换的值（即设定[0][3]、[1][3]、[2][3]位置的值） */
	inline OMatrix4x4 SetProj( const OVector3& v )
	{
		ele_f[0][3] = v.x;
		ele_f[1][3] = v.y;
		ele_f[2][3] = v.z;
		return *this;
	}

	/** 用一个3维向量来设定4*4矩阵的位移变换的值（即设定[3][0]、[3][1]、[3][2]位置的值） */
	inline OMatrix4x4 SetOffset( const OVector3& v )
	{
		ele_f[3][0] = v.x;
		ele_f[3][1] = v.y;
		ele_f[3][2] = v.z;
		return *this;
	}

	/** 获得4*4矩阵的投影变换的值（即[0][3]、[1][3]、[2][3]位置的值） */
	inline OVector3 GetProj() const
	{
		return OVector3(ele_f[0][3], ele_f[1][3], ele_f[2][3]);
	}


	/** 求4*4矩阵的伴随矩阵，并作为函数返回值返回 */
	OMatrix4x4 Adjoint() const;

	/** 对4*4矩阵求其行列式值 */
	float32 Determinant() const;

	/** 对4*4矩阵求逆矩阵，返回值为逆矩阵 */
	OMatrix4x4 Inverse() const;

	/** 获得4*4矩阵的位移变换的值（即[0][3]、[1][3]、[2][3]位置的值） */
	inline OVector3 GetOffset() const
	{
		return OVector3(ele_f[3][0], ele_f[3][1], ele_f[3][2]);
	}


	void NoRotate(void)
	{
		vec1 = GetIdentityMatrix()[0];
		vec2 = GetIdentityMatrix()[1];
		vec3 = GetIdentityMatrix()[2];
	}

/*
	inline OVector4 Transform_Vec4(OVector4 &vec)
	{
		OVector4 result = vec * (*this);
		return result;
	}
*/
//Scale
	void Scale(const OVector4 &scale)
	{
		Scale(scale[0], scale[1], scale[2]);
	}

	void Scale(float32 x, float32 y, float32 z)
	{
		vec1 *= x;
		vec2 *= y;
		vec3 *= z;
	}

	void Scale_Replace(const OVector4 &scale)
	{
		Scale_Replace(scale[0], scale[1], scale[2]);
	}

	void Scale_Replace(float32 x, float32 y, float32 z)
	{
		vec1.Setf(x,    0.0f, 0.0f, 0.0f);
		vec2.Setf(0.0f, y,    0.0f, 0.0f);
		vec3.Setf(0.0f, 0.0f, z,    0.0f);
		vec4.Setf(0.0f, 0.0f, 0.0f, 1);
	}

	/** 整体缩放（[3][3]位置的值）    */
	inline void Scale( const float32& scale )
	{
		assert(scale != 0.0f&&"除数为0！");
		ele_f[3][3] = 1.0f / scale;
	}

	/** 用3个float变量把调用对象矩阵（无论矩阵原来是怎么样的）变成一个投影的转换矩阵，并把这个矩阵作为函数返回值 */
	inline OMatrix4x4 Project_Replace( float t_x, float t_y, float t_z )
	{
		OMatrix4x4 r;

		r.ele_f[0][0] = 1.0; r.ele_f[0][1] = 0.0; r.ele_f[0][2] = 0.0; r.ele_f[0][3] = t_x;
		r.ele_f[1][0] = 0.0; r.ele_f[1][1] = 1.0; r.ele_f[1][2] = 0.0; r.ele_f[1][3] = t_y;
		r.ele_f[2][0] = 0.0; r.ele_f[2][1] = 0.0; r.ele_f[2][2] = 1.0; r.ele_f[2][3] = t_z;
		r.ele_f[3][0] = 0.0; r.ele_f[3][1] = 0.0; r.ele_f[3][2] = 0.0; r.ele_f[3][3] = 1.0;

		return r;
	}

	inline void Project( float tx, float ty, float tz )
	{
		ele_f[0][0] = 1.0; ele_f[0][1] = 0.0; ele_f[0][2] = 0.0; ele_f[0][3] = tx;
		ele_f[1][0] = 0.0; ele_f[1][1] = 1.0; ele_f[1][2] = 0.0; ele_f[1][3] = ty;
		ele_f[2][0] = 0.0; ele_f[2][1] = 0.0; ele_f[2][2] = 1.0; ele_f[2][3] = tz;
		ele_f[3][0] = 0.0; ele_f[3][1] = 0.0; ele_f[3][2] = 0.0; ele_f[3][3] = 1.0;
	}


//translate
	void Translate(float32 x, float32 y, float32 z)
	{
		vec4 += vec1 * x + vec2 * y + vec3 * z;
	}

	void Translate(OVector4 &v)
	{
		vec4 += vec1 * v.GetXf() + vec2 * v.GetYf() + vec3 * v.GetZf();
	}

	void Translate_Replace(const float32 x, const float32 y, const float32 z)
	{
		Identity();
		vec4[0] = x;
		vec4[1] = y;
		vec4[2] = z;
	}

	void Translate_Replace(OVector4 &v)
	{
		Identity();
		vec4 = v;
	}

//rotate
	OMatrix4x4& RotateX_Replace( const float radian )
	{
		float32 fSin = sinf(radian);
		float32 fCos = cosf(radian);

		vec1.Setf(1.0f,  0.0f,  0.0f, 0.0f);
		vec2.Setf(0.0f,  fCos,  fSin, 0.0f);
		vec3.Setf(0.0f, -fSin,  fCos, 0.0f);
		vec4.Setf(0.0f,  0.0f,  0.0f, 1.0f);
		return *this;
	}

	void RotateX( const float radian )
	{
		float32 Sin = OSin(radian);
		float32 Cos = OCos(radian);

		float Temp10, Temp11, Temp12, Temp13;
		float Temp20, Temp21, Temp22, Temp23;

		Temp10 = m21 * Cos + m31 * Sin;
		Temp11 = m22 * Cos + m32 * Sin;
		Temp12 = m23 * Cos + m33 * Sin;
		Temp13 = m24 * Cos + m34 * Sin;

		Temp20 = m21 *-Sin + m31 * Cos;
		Temp21 = m22 *-Sin + m32 * Cos;
		Temp22 = m23 *-Sin + m33 * Cos;
		Temp23 = m24 *-Sin + m34 * Cos;

		m21 = Temp10;
		m22 = Temp11;
		m23 = Temp12;
		m24 = Temp13;
		m31 = Temp20;
		m32 = Temp21;
		m33 = Temp22;
		m34 = Temp23;
	}


	void RotateY( const float radian )
	{
		float Temp00, Temp01, Temp02, Temp03;
		float Temp20, Temp21, Temp22, Temp23;
		
		float32 Sin = sinf(radian);
		float32 Cos = cosf(radian);

		Temp00 = m11 * Cos - m31 * Sin;
		Temp01 = m12 * Cos - m32 * Sin;
		Temp02 = m13 * Cos - m33 * Sin;
		Temp03 = m14 * Cos - m34 * Sin;

		Temp20 = m11 * Sin + m31 * Cos;
		Temp21 = m12 * Sin + m32 * Cos;
		Temp22 = m13 * Sin + m33 * Cos;
		Temp23 = m14 * Sin + m34 * Cos;

		m11 = Temp00;
		m12 = Temp01;
		m13 = Temp02;
		m14 = Temp03;
		m31 = Temp20;
		m32 = Temp21;
		m33 = Temp22;
		m34 = Temp23;
	}

	OMatrix4x4& RotateY_Replace( const float radian )
	{
		float32 fSin = OSin(radian);
		float32 fCos = OCos(radian);

		vec1.Setf( fCos,  0.0f, -fSin, 0.0f);
		vec2.Setf( 0.0f,  1.0f,  0.0f, 0.0f);
		vec3.Setf(-fSin,  0.0f,  fCos, 0.0f);
		vec4.Setf( 0.0f,  0.0f,  0.0f, 1.0f);
		return *this;
	}

	void RotateZ( const float radian )
	{
		float Temp00, Temp01, Temp02, Temp03;
		float Temp10, Temp11, Temp12, Temp13;

		float32 Sin = sinf(radian);
		float32 Cos = cosf(radian);

		Temp00 = m11 * Cos + m21 * Sin;
		Temp01 = m12 * Cos + m22 * Sin;
		Temp02 = m13 * Cos + m23 * Sin;
		Temp03 = m14 * Cos + m24 * Sin;

		Temp10 = m11 *-Sin + m21 * Cos;
		Temp11 = m12 *-Sin + m22 * Cos;
		Temp12 = m13 *-Sin + m23 * Cos;
		Temp13 = m14 *-Sin + m24 * Cos;

		m11 = Temp00;
		m12 = Temp01;
		m13 = Temp02;
		m14 = Temp03;
		m21 = Temp10;
		m22 = Temp11;
		m23 = Temp12;
		m24 = Temp13;
	}

	OMatrix4x4& RotateZ_Replace( const float radian )
	{
		float32 fSin = sinf(radian);
		float32 fCos = cosf(radian);

		vec1.Setf( fCos,  fSin, 0.0f, 0.0f);
		vec2.Setf(-fSin,  fCos, 0.0f, 0.0f);
		vec3.Setf( 0.0f,  0.0f, 1.0f, 0.0f);
		vec4.Setf( 0.0f,  0.0f, 0.0f, 1.0f);

		return *this;
	}

 /** 输出4维矩阵中表示旋转,缩放的那个三维矩阵 
     *	@param [Matrix3&] : 输出矩阵,Matrix3
     */
    inline void Extract3x3Matrix(OMatrix3x3& m3x3) const
    {
        m3x3.ele_f[0][0] = ele_f[0][0];
        m3x3.ele_f[0][1] = ele_f[0][1];
        m3x3.ele_f[0][2] = ele_f[0][2];
        m3x3.ele_f[1][0] = ele_f[1][0];
        m3x3.ele_f[1][1] = ele_f[1][1];
        m3x3.ele_f[1][2] = ele_f[1][2];
        m3x3.ele_f[2][0] = ele_f[2][0];
        m3x3.ele_f[2][1] = ele_f[2][1];
        m3x3.ele_f[2][2] = ele_f[2][2];

    }

	/// Bulk transpose matrices.
	static void BulkTranspose(float* dest, const float* src, unsigned count)
	{
		for (unsigned i = 0; i < count; ++i)
		{
			dest[0] = src[0];
			dest[1] = src[4];
			dest[2] = src[8];
			dest[3] = src[12];
			dest[4] = src[1];
			dest[5] = src[5];
			dest[6] = src[9];
			dest[7] = src[13];
			dest[8] = src[2];
			dest[9] = src[6];
			dest[10] = src[10];
			dest[11] = src[14];
			dest[12] = src[3];
			dest[13] = src[7];
			dest[14] = src[11];
			dest[15] = src[15];

			dest += 16;
			src += 16;
		}
	}

	/** <<操作符重载，按行输出4*4矩阵 */
	inline friend std::ostream& operator <<
		( std::ostream& o, const OMatrix4x4& m )
	{
		o << "Matrix4x4(";
		for (int i = 0; i < 4; ++i)
		{
			o << " row" << (unsigned)i << "{";
			for(int j = 0; j < 4; ++j)
			{
				o << m[i][j] << " ";
			}
			o << "}";
		}
		o << ")";
		return o;
	}

	/// Return float data
	const float* Data() const { return &m11; }

//////////////////////////////////////////////////////////////////////////
//static
	static OMatrix4x4 &GetIdentityMatrix(void)
	{
		return g_Matrix4x4_Identity;
	}

//////////////////////////////////////////////////////////////////////////
//Operator

	inline OMatrix4x4 &operator-=(const OMatrix4x4 &rhs)
	{
		vec1 -= rhs.vec1;
		vec2 -= rhs.vec2;
		vec3 -= rhs.vec3;
		vec4 -= rhs.vec4;
		return *this;
	}

	inline OMatrix4x4 &operator*=(const float32 f)
	{
		vec1 *= f;
		vec2 *= f;
		vec3 *= f;
		vec4 *= f;
		return *this;
	}

	/** *操作符重载，4*4矩阵的每个值都与参数标量相乘，返回相乘后的结果矩阵 */
	inline OMatrix4x4 operator*(const float32 scalar)
	{
		return OMatrix4x4(
			scalar*ele_f[0][0], scalar*ele_f[0][1], scalar*ele_f[0][2], scalar*ele_f[0][3],
			scalar*ele_f[1][0], scalar*ele_f[1][1], scalar*ele_f[1][2], scalar*ele_f[1][3],
			scalar*ele_f[2][0], scalar*ele_f[2][1], scalar*ele_f[2][2], scalar*ele_f[2][3],
			scalar*ele_f[3][0], scalar*ele_f[3][1], scalar*ele_f[3][2], scalar*ele_f[3][3]);
	}

	OVector3 operator * (const OVector3& rhs) const
	{
		float invW = 1.0f / (m41 * rhs.x + m42 * rhs.y + m43 * rhs.z + m44);

		return OVector3(
			(m11 * rhs.x + m12 * rhs.y + m13 * rhs.z + m14) * invW,
			(m21 * rhs.x + m22 * rhs.y + m23 * rhs.z + m24) * invW,
			(m31 * rhs.x + m32 * rhs.y + m33 * rhs.z + m34) * invW
			);
	}


	inline OVector4 &operator[](const int32 row)
	{
		return GetRow(row);
	}

	inline const OVector4 &operator[](const int32 row) const
	{
		return GetRow(row);
	}

	inline OMatrix4x4 &operator+=(OMatrix4x4 &rhs)
	{
		vec1 += rhs.vec1;
		vec2 += rhs.vec2;
		vec3 += rhs.vec3;
		vec4 += rhs.vec4;

		return *this;
	}

	inline float32 &operator()(int32 x, int32 y)
	{
		assert(x>=0 && x<4);
		assert(y>=0 && y<4);
		return GetRow(x)[y];
	}

	inline OMatrix4x4 &operator=(const OMatrix4x4 &rhs)
	{
		vec1 = rhs.vec1;
		vec2 = rhs.vec2;
		vec3 = rhs.vec3;
		vec4 = rhs.vec4;

		return *this;
	}

	inline OMatrix4x4 &operator-=(const float32 f)
	{
		vec1 -= f;
		vec2 -= f;
		vec3 -= f;
		vec4 -= f;
		return *this;
	}

	inline OMatrix4x4 &operator=(const float32 f)
	{
		OVector4 temp(f);

		vec1 = temp;
		vec2 = temp;
		vec3 = temp;
		vec4 = temp;

		return *this;
	}

	/** ＝操作符重载，把参数3*3矩阵赋值给4*4矩阵，结果为4*4单位矩阵的前三行三列加上参数3*3矩阵 */
	inline void operator = ( const OMatrix3x3& mat3 )
	{
		ele_f[0][0] = mat3.ele_f[0][0]; ele_f[0][1] = mat3.ele_f[0][1]; ele_f[0][2] = mat3.ele_f[0][2]; ele_f[0][3] = 0.0f;
		ele_f[1][0] = mat3.ele_f[1][0]; ele_f[1][1] = mat3.ele_f[1][1]; ele_f[1][2] = mat3.ele_f[1][2]; ele_f[1][3] = 0.0f;
		ele_f[2][0] = mat3.ele_f[2][0]; ele_f[2][1] = mat3.ele_f[2][1]; ele_f[2][2] = mat3.ele_f[2][2]; ele_f[2][3] = 0.0f;
		ele_f[3][0] = 0.0f;			    ele_f[3][1] = 0.0f	;		    ele_f[3][2] = 0.0f;  		    ele_f[3][3] = 1.0f;
	}

	inline OMatrix4x4 &operator/=(const float32 f)
	{
		assert(f != 0.0f && "非法除数");
		vec1 /= f;
		vec2 /= f;
		vec3 /= f;
		vec4 /= f;

		return *this;
	}
};

inline bool operator==(const OMatrix4x4 &a, const OMatrix4x4 &b)
{
	bool result = a.vec1==b.vec1 && a.vec2==b.vec2 && a.vec3==b.vec3 && a.vec4==b.vec4;
	return result;
}

inline bool operator!=(const OMatrix4x4 &a, const OMatrix4x4 &b)
{
	bool result = a.vec1!=b.vec1 || a.vec2!=b.vec2 || a.vec3!=b.vec3 || a.vec4!=b.vec4;
	return result;
}




/*
inline OMatrix4x4 operator+(float f, OMatrix4x4 &a)
{
	//OMatrix4x4 result = a;
	//result += f;
	//return result;
}*/


inline OMatrix4x4 operator+(const OMatrix4x4 &a, const OMatrix4x4 &b)
{
	OMatrix4x4 result;

	result.vec1 = a.vec1 + b.vec1;
	result.vec2 = a.vec2 + b.vec2;
	result.vec3 = a.vec3 + b.vec3;
	result.vec4 = a.vec4 + b.vec4;

	return result;
}

inline OMatrix4x4 operator-(OMatrix4x4 &a, float f)
{
	OMatrix4x4 result = a;
	result -= f;
	return result;
}



inline OMatrix4x4 operator-(float f, OMatrix4x4 &a)
{
	OMatrix4x4 result = a;
	result -= f;
	return result;
}

inline OMatrix4x4 operator-(const OMatrix4x4 &a, const OMatrix4x4 &b)
{
	OMatrix4x4 result;

	result.vec1 = a.vec1 - b.vec1;
	result.vec2 = a.vec2 - b.vec2;
	result.vec3 = a.vec3 - b.vec3;
	result.vec4 = a.vec4 - b.vec4;

	return result;
}

inline OVector4 operator*(OVector4 &v, OMatrix4x4 &m)
{
	OVector4 result;

	result.x = v.x*m.m11 + v.y*m.m12 + v.z*m.m13 + v.w*m.m14;
	result.y = v.x*m.m12 + v.y*m.m22 + v.z*m.m23 + v.w*m.m42;
	result.z = v.x*m.m13 + v.y*m.m23 + v.z*m.m33 + v.w*m.m43;
	result.w = v.x*m.m14 + v.y*m.m24 + v.z*m.m34 + v.w*m.m44;

	return result;
}
/*
|1  2  3  4 | |1|
|5  6  7  8 | |2|
|9  10 11 12|*|3|
|13 14 15 16| |4|
*/
inline OVector4 operator*(OMatrix4x4 &matrix, OVector4 &vec)
{
	OVector4 result;

	result[0] = Vec4_Dotf(vec, matrix[0]);
	result[1] = Vec4_Dotf(vec, matrix[1]);
	result[2] = Vec4_Dotf(vec, matrix[2]);
	result[3] = Vec4_Dotf(vec, matrix[3]);

	return result;
}



inline OMatrix4x4 operator*(OMatrix4x4 &a, OMatrix4x4 &b)
{
	OMatrix4x4 result;

	result.vec1 = a.vec1 * b;
	result.vec2 = a.vec2 * b;
	result.vec3 = a.vec3 * b;
	result.vec4 = a.vec4 * b;

	return result;
}

inline OMatrix4x4 operator * (const float32 lhs, const OMatrix4x4& rhs) 
{
	return OMatrix4x4(
		lhs*rhs.ele_f[0][0], lhs*rhs.ele_f[0][1], lhs*rhs.ele_f[0][2], lhs*rhs.ele_f[0][3],
		lhs*rhs.ele_f[1][0], lhs*rhs.ele_f[1][1], lhs*rhs.ele_f[1][2], lhs*rhs.ele_f[1][3],
		lhs*rhs.ele_f[2][0], lhs*rhs.ele_f[2][1], lhs*rhs.ele_f[2][2], lhs*rhs.ele_f[2][3],
		lhs*rhs.ele_f[3][0], lhs*rhs.ele_f[3][1], lhs*rhs.ele_f[3][2], lhs*rhs.ele_f[3][3]);

}


#endif/* File Is Over */