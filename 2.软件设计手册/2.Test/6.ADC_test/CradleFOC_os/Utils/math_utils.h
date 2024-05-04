//
// Created by User on 2024/5/3.
//

#ifndef CRADLEFOC_OS_MATH_UTILS_H
#define CRADLEFOC_OS_MATH_UTILS_H

#define _2PI 6.283185307f
#define _PI 3.14159265359f
#define _PI_2 1.57079632679f
#define _3PI_2 4.71238898038f
#define _sqrt3 1.7320508f
#define _sqrt3_2 0.866025403784f

#define _constrain(amt, low, high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

float _normalizeAngle(float angle);
float findMax(const float *a, const float *b, const float *c);
float findMin(const float *a, const float *b, const float *c);
void map_constraint(float *a);

#endif //CRADLEFOC_OS_MATH_UTILS_H
