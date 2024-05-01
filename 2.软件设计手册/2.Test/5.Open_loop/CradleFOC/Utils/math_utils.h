//
// Created by User on 2024/4/29.
//

#ifndef CRADLEFOC_MATH_UTILS_H
#define CRADLEFOC_MATH_UTILS_H

#define _2PI 6.283185307f
#define _PI 3.14159265359f
#define _PI_2 1.57079632679f
#define _3PI_2 4.71238898038f

#define _constrain(amt, low, high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

float _normalizeAngle(float angle);
float findMax(const float *a, const float *b, const float *c);
float findMin(const float *a, const float *b, const float *c);
void map_constraint(float *a);

#endif //CRADLEFOC_MATH_UTILS_H
