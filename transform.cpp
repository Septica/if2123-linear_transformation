#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include "transform.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

void Transform(float M[16], char input[10]) {
	if (strcmp(input, "translate") == 0)
	{
		float dx, dy;
		scanf(" %f %f", &dx, &dy);
		Translate(M, dx, dy);
	}
	else if (strcmp(input, "dilate") == 0)
	{
		float k;
		scanf(" %f", &k);
		Dilate(M, k);
	}
	else if (strcmp(input, "rotate") == 0)
	{
		float deg, a, b;
		scanf(" %f %f %f", &deg, &a, &b);
		Rotate(M, deg, a, b);
	}
	else if (strcmp(input, "reflect") == 0)
	{
		char param[5];
		scanf(" %[^\n(]", param);
		Reflect(M, param);
	}
	else if (strcmp(input, "shear") == 0)
	{
		char param;
		float k;
		scanf(" %c %f", &param, &k);
		Shear(M, param, k);
	}
	else if (strcmp(input, "stretch") == 0)
	{
		char param;
		float k;
		scanf(" %c %f", &param, &k);
		Stretch(M, param, k);
	}
	else if (strcmp(input, "custom") == 0)
	{
		float a, b, c, d;
		scanf(" %f %f %f %f", &a, &b, &c, &d);
		Custom(M, a, b, c, d);
	}
}

void CreateIdentity(float M[16])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				M[i * 4 + j] = 1;
			else
				M[i * 4 + j] = 0;
		}
	}
}

void Compose(float A[16], float B[16])
{
	float C[16];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0;
			for (int k = 0; k < 4; k++) {
				sum += B[i * 4 + k] * A[k * 4 + j];
			}
			C[i * 4 + j] = sum;
		}
	}
	for (int i = 0; i < 16; i++) {
		A[i] = C[i];
	}
}

void Translate(float M[16], float dx, float dy)
{
	float MTranslate[16];

	CreateIdentity(MTranslate);
	MTranslate[3] = dx;
	MTranslate[7] = dy;

	Compose(M, MTranslate);
}
void Dilate(float M[16], float k)
{
	float MDilate[16];

	CreateIdentity(MDilate);
	MDilate[0] = k;
	MDilate[5] = k;
	MDilate[10] = k;

	Compose(M, MDilate);
}
void Rotate(float M[16], float deg, float a, float b)
{
	float MRotate[16];
	double r = deg * M_PI / 180, s = sin(r), c = cos(r);

	CreateIdentity(MRotate);
	MRotate[0] = (float)c;
	MRotate[1] = (float)-s;
	MRotate[3] = (float)a * (1 - c) + (b * s);
	MRotate[4] = (float)s;
	MRotate[5] = (float)c;
	MRotate[7] = (float)b * (1 - c) - (a * s);

	Compose(M, MRotate);
}
void Reflect(float M[16], char param[])
{
	float MReflect[16];
	float a, b;

	CreateIdentity(MReflect);
	if (strcmp(param, "x") == 0)
	{
		MReflect[5] = -1;
	}
	else if (strcmp(param, "y") == 0)
	{
		MReflect[0] = -1;
	}
	else if (strcmp(param, "y=x") == 0)
	{
		MReflect[0] = 0;
		MReflect[1] = 1;
		MReflect[4] = 1;
		MReflect[5] = 0;
	}
	else if (strcmp(param, "y=-x") == 0)
	{
		MReflect[0] = 0;
		MReflect[1] = -1;
		MReflect[4] = -1;
		MReflect[5] = 0;
	}
	else
	{
		scanf("(%f,%f)", &a, &b);
		MReflect[0] = -1;
		MReflect[1] = 0;
		MReflect[3] = 2 * a;
		MReflect[5] = -1;
		MReflect[4] = 0;
		MReflect[7] = 2 * b;
	}

	Compose(M, MReflect);
}
void Shear(float M[16], char param, float k)
{
	float MShear[16];

	CreateIdentity(MShear);
	if (param == 'x')
	{
		MShear[1] = k;
		MShear[2] = k;
	}
	else if (param == 'y')
	{
		MShear[4] = k;
		MShear[6] = k;
	}

	Compose(M, MShear);
}
void Stretch(float M[16], char param, float k)
{
	float MStretch[16];

	CreateIdentity(MStretch);
	if (param == 'x')
	{
		MStretch[0] = k;
	}
	else if (param == 'y')
	{
		MStretch[5] = k;
	}

	Compose(M, MStretch);
}
void Custom(float M[16], float a, float b, float c, float d)
{
	float MCustom[16];

	CreateIdentity(MCustom);
	MCustom[0] = a;
	MCustom[1] = b;
	MCustom[4] = c;
	MCustom[5] = d;

	Compose(M, MCustom);
}
void Multiple(float M[16], unsigned int n)
{
	for (int i = 0; i < n; i++)
	{
		char input[10];
		scanf("%s", input);
		Transform(M, input);
	}
}
void Reset(float M[16])
{
	CreateIdentity(M);
}