#include "stdafx.h"
#include "../OInclude/Math/ORect.h"

const ORect ORect::FULL(-1.0f, -1.0f, 1.0f, 1.0f);
const ORect ORect::POSITIVE(0.0f, 0.0f, 1.0f, 1.0f);
const ORect ORect::ZERO(0.0f, 0.0f, 0.0f, 0.0f);


void ORect::Clip(const ORect& rect)
{
	if (rect.min.x > min.x)
		min.x = rect.min.x;
	if (rect.max.x < max.x)
		max.x = rect.max.x;
	if (rect.min.y > min.y)
		min.y = rect.min.y;
	if (rect.max.y < max.y)
		max.y = rect.max.y;

	if (min.x > max.x)
		OSwap(min.x, max.x);
	if (min.y > max.y)
		OSwap(min.y, max.y);
}