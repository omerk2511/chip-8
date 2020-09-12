#pragma once

#include <string>
#include <sstream>

enum class reg
{
	v0,
	v1,
	v2,
	v3,
	v4,
	v5,
	v6,
	v7,
	v8,
	v9,
	va,
	vb,
	vc,
	vd,
	ve,
	vf
};

std::ostream& operator<<(std::ostream& os, const reg reg);