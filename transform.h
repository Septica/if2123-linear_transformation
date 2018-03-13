#ifndef TRANSFORM_H
#define TRANSFORM_H

void Transform(float M[16], char input[10]);

void CreateIdentity(float M[16]);
void Compose(float A[16], float B[16]);

void Translate(float M[16], float dx, float dy);
void Dilate(float M[16], float k);
void Rotate(float M[16], float deg, float a, float b);
void Reflect(float M[16], char param[]);
void Shear(float M[16], char param, float k);
void Stretch(float M[16], char param, float k);

void Custom(float M[16], float a, float b, float c, float d);
void Multiple(float M[16], unsigned int n);
void Reset(float M[16]);

#endif
