#pragma once

#include <iostream>
#include "vec3.h"
#include "vec2.h"

namespace gc {
	const std::string resourceFolderPath = "xxx";
}

namespace GlobalWorldSettings {
	const vec3 WorldUpVector(0, 1, 0);
}

namespace GlobalMathConstants {
	const long double PIld = 3.141592653589793238L;
	const double PId = 3.141592653589793;
	const float PIf = 3.1415927f;
}

//can be moced into a class 
namespace GlobalMathFunctions {
	static bool floatComparison(float a, float b, float accuracy = 0.005f) {
		return std::fabs(a - b) < accuracy;
	}
}

