//////////////////////////////////////////////////////////////////////////
//File : Only Point2D ( Only Math Lib)
//Author : Zipxin  [China]
//Project : OnlyGameEngine
//E-mail: zipxin@163.com
//////////////////////////////////////////////////////////////////////////
#ifndef _ONLY_POINT2D_H_
#define _ONLY_POINT2D_H_

#if _MSC_VER > 1000
#pragma once
#endif 

/** ���Ͷ�ά��,��Ҫ����GUI,��Ļ�ϵĵ���� */
template<class T>
class Point2D
{
public:
	T x,y;

	/** ������ϵ������������X��Y������� */
	Point2D operator + (Point2D p) const 
	{
		Point2D result;
		result.x = x + p.x;
		result.y = y + p.y;
		return result;
	}

	/** ������ϵ������������X��Y������� */
	Point2D operator - (Point2D p) const
	{
		Point2D result;
		result.x = x - p.x;
		result.y = y - p.y;
		return result;
	}

	/** ������ϵ�еĵ㸳ֵ */
	void operator = (Point2D p)
	{
		x = p.x;
		y = p.y;
	}

	/** �Ƚ���������ϵ�еĵ��Ƿ���� */
	bool operator == (Point2D p) const
	{
		if (x == p.x && y == p.y)
			return true;
		else
			return false;
	}

	/** �Ƚ����������еĵ��Ƿ���� */
	bool operator != (Point2D p) const
	{
		if (x != p.x || y != p.y)
			return true;
		else
			return false;
	}
};


#endif