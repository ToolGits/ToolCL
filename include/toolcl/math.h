#ifndef TOOLCL_MATH_H
#define TOOLCL_MATH_H

float toolcl_addf(float a, float b);
float toolcl_subf(float a, float b);
float toolcl_mulf(float a, float b);

/*
 * Returns 0.0f when b is zero.
 * This is the defined ToolCL behavior for invalid division.
 */
float toolcl_divf(float a, float b);

#endif
