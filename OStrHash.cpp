#include "stdafx.h"

#include "../OInclude/Math/OStrHash.h"
#include "../OInclude/Math/OMathUtil.h"

#include <cstdio>

const OStrHash OStrHash::ZERO;

OStrHash::OStrHash(const char* str) : value(Calculate(str)){}

OStrHash::OStrHash(const OString& str):value(Calculate(str.c_str())){}

unsigned OStrHash::Calculate(const char* str)
{
	unsigned hash = 0;

	if (!str)
		return hash;

	while (*str)
	{
		// Perform the actual hashing as case-insensitive
		char c = *str;
		hash = SDBMHash(hash, tolower(c));
		++str;
	}

	return hash;
}

const char* OStrHash::ToCString() const
{
	char *buf = new char[128];
	memset(buf, 0 , 128);
	sprintf_s(buf, 128, "%08X", value);
	return buf;
}

const wchar_t* OStrHash::ToWString() const
{
	wchar_t *buf = new wchar_t[128];
	memset(buf, 0 , 128);
	swprintf_s(buf, 128, L"%08X", value);
	return buf;
}
