//////////////////////////////////////////////////////////////////////////
//File : Only String Hash( Only Math Lib)
//Author : Zipxin  
//E-mail: zipxin@163.com
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef _ONLY_STRINGHASH_H_
#define _ONLY_STRINGHASH_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "../OInclude/Common/OnlyGameDefine.h"

//����string ���͵� 32bit hashֵ
class OStrHash
{
private:
	/// Hash value.
	uint32 value;
public:
	OStrHash() : value(0){}

	OStrHash(const OStrHash& rhs) : value(rhs.value){}

	//��ֹuint32 �� StrHash����ʽת��
	explicit OStrHash(uint32 value) : value(value){}

	//����CStringϵ�е�OStrHash֮�����ʽת��
	OStrHash(const char* str);
	OStrHash(const OString& str);

	OStrHash& operator = (const OStrHash& rhs)
	{
	  value = rhs.value;
	  return *this;
	}

	OStrHash operator + (const OStrHash& rhs) const
	{
	  OStrHash ret;
	  ret.value = value + rhs.value;
	  return ret;
	}

	OStrHash& operator += (const OStrHash& rhs)
	{
	  value += rhs.value;
	  return *this;
	}

	bool operator == (const OStrHash& rhs) const { return value == rhs.value; }
	bool operator != (const OStrHash& rhs) const { return value != rhs.value; }
	bool operator < (const OStrHash& rhs) const { return value < rhs.value; }
	bool operator > (const OStrHash& rhs) const { return value > rhs.value; }
	
	/// ���hashֵ��Ϊ0 ����Ϊ��
	operator bool () const { return value != 0; }
	
	/// Return hash value.
	unsigned Value() const { return value; }
	
	/// ����ʹ��
	const wchar_t* ToWString() const;
	const char* ToCString() const;

	/// return valueֵ
	unsigned ToHash() const { return value; }

	//����str��hashֵ
	static unsigned Calculate(const char* str);

	/// HASHֵΪ0
	static const OStrHash ZERO;

};

#endif/*File Is Over*/