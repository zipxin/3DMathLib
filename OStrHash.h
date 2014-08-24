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

//返回string 类型的 32bit hash值
class OStrHash
{
private:
	/// Hash value.
	uint32 value;
public:
	OStrHash() : value(0){}

	OStrHash(const OStrHash& rhs) : value(rhs.value){}

	//禁止uint32 到 StrHash的隐式转换
	explicit OStrHash(uint32 value) : value(value){}

	//允许CString系列到OStrHash之间的隐式转换
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
	
	/// 如果hash值不为0 返回为真
	operator bool () const { return value != 0; }
	
	/// Return hash value.
	unsigned Value() const { return value; }
	
	/// 调试使用
	const wchar_t* ToWString() const;
	const char* ToCString() const;

	/// return value值
	unsigned ToHash() const { return value; }

	//计算str的hash值
	static unsigned Calculate(const char* str);

	/// HASH值为0
	static const OStrHash ZERO;

};

#endif/*File Is Over*/