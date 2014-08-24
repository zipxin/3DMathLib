#include "stdafx.h"
#include "../OInclude/Math/OMatrix3x4.h"

const OMatrix3x4 OMatrix3x4::ZERO(
								0.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f, 0.0f);

const OMatrix3x4 OMatrix3x4::IDENTITY(
									1.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 1.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 1.0f, 0.0f);