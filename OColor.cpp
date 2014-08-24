#include "stdafx.h"
#include "../OInclude/Math/OColor.h"


const OColor OColor::WHITE;
const OColor OColor::GRAY   (0.5f, 0.5f, 0.5f);
const OColor OColor::BLACK  (0.0f, 0.0f, 0.0f);
const OColor OColor::RED    (1.0f, 0.0f, 0.0f);
const OColor OColor::GREEN  (0.0f, 1.0f, 0.0f);
const OColor OColor::BLUE   (0.0f, 0.0f, 1.0f);
const OColor OColor::CYAN   (0.0f, 1.0f, 1.0f);
const OColor OColor::MAGENTA(1.0f, 0.0f, 1.0f);
const OColor OColor::YELLOW (1.0f, 1.0f, 0.0f);
const OColor OColor::TRANSPARENT(0.0f, 0.0f, 0.0f, 0.0f);

void OColor::Clip(bool clipAlpha)
{
	r = (r > 1.0f) ? 1.0f : ((r < 0.0f) ? 0.0f : r);
	g = (g > 1.0f) ? 1.0f : ((g < 0.0f) ? 0.0f : g);
	b = (b > 1.0f) ? 1.0f : ((b < 0.0f) ? 0.0f : b);

	if (clipAlpha)
		a = (a > 1.0f) ? 1.0f : ((a < 0.0f) ? 0.0f : a);
}

void OColor::Invert(bool invertAlpha)
{
	r = 1.0f - r;
	g = 1.0f - g;
	b = 1.0f - b;

	if (invertAlpha)
		a = 1.0f - a;
}

OColor OColor::Lerp(const OColor &rhs, float t) const
{
	float invT = 1.0f - t;
	return OColor(
		r * invT + rhs.r * t,
		g * invT + rhs.g * t,
		b * invT + rhs.b * t,
		a * invT + rhs.a * t
		);
}

RGBA OColor::GetRGBA() const
{
	uint8 val8;
	uint32 val32 = 0;

	// Convert to 32bit pattern
	// (RGBA = 8888)

	// Red
	val8 = static_cast<uint8>(r * 255);
	val32 = val8 << 24;

	// Green
	val8 = static_cast<uint8>(g * 255);
	val32 += val8 << 16;

	// Blue
	val8 = static_cast<uint8>(b * 255);
	val32 += val8 << 8;

	// Alpha
	val8 = static_cast<uint8>(a * 255);
	val32 += val8;

	return val32;
}
ARGB OColor::GetARGB() const
{
	uint8 val8;
	uint32 val32 = 0;

	// Convert to 32bit pattern
	// (ARGB = 8888)

	// Alpha
	val8 = static_cast<uint8>(a * 255);
	val32 = val8 << 24;

	// Red
	val8 = static_cast<uint8>(r * 255);
	val32 += val8 << 16;

	// Green
	val8 = static_cast<uint8>(g * 255);
	val32 += val8 << 8;

	// Blue
	val8 = static_cast<uint8>(b * 255);
	val32 += val8;


	return val32;
}

void OColor::SetFromRGBA(RGBA color)
{
	uint32 val32 = color;
	// Convert from 32bit pattern
	// (RGBA = 8888)

	// Red
	r = static_cast<uint8>(val32 >> 24) / 255.0f;

	// Green
	g = static_cast<uint8>(val32 >> 16) / 255.0f;

	// Blue
	b = static_cast<uint8>(val32 >> 8) / 255.0f;

	// Alpha
	a = static_cast<uint8>(val32) / 255.0f;

}
void OColor::SetFromARGB(ARGB color)
{
	uint32 val32 = color;

	// Convert from 32bit pattern
	// (ARGB = 8888)

	// Alpha
	a = static_cast<uint8>(val32 >> 24) / 255.0f;

	// Red
	r = static_cast<uint8>(val32 >> 16) / 255.0f;

	// Green
	g = static_cast<uint8>(val32 >> 8) / 255.0f;

	// Blue
	b = static_cast<uint8>(val32) / 255.0f;
}


// 
// D3DCOLORVALUE OColor::GetAsD3DCOLOR()
// {
// 	D3DCOLORVALUE color;
// 	color.r = r;
// 	color.g = g;
// 	color.b = b;
// 	color.a = a;
// 	return color;
// }
// 
// void OColor::SetASD3DCOLOR(D3DCOLORVALUE color)
// {
// 	r = color.r;
// 	g = color.g;
// 	b = color.b;
// 	a = color.a;	
// }

