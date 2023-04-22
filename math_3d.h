#pragma once
#ifndef MATH_3D_H
#define MATH_3D_H

#define _USE_MATH_DEFINES
#include <math.h>

struct Vector3f { // Вектор в 3-мерном пространстве
	float x, y, z;

	Vector3f() = default;
	Vector3f(float x, float y, float z) : x(x), y(y), z(z) { }
	Vector3f Cross(const Vector3f& v) const;
	Vector3f& Normalize();

	Vector3f& operator+=(const Vector3f& r) {
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}

	Vector3f& operator-=(const Vector3f& r) {
		x -= r.x;
		y -= r.y;
		z -= r.z;

		return *this;
	}

	Vector3f& operator*=(float f) {
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}
};

inline Vector3f operator-(const Vector3f& l, const Vector3f& r)
{
	Vector3f Ret(l.x - r.x,
		l.y - r.y,
		l.z - r.z);

	return Ret;
}

inline Vector3f operator*(const Vector3f& l, float f)
{
	Vector3f Ret(l.x * f,
		l.y * f,
		l.z * f);

	return Ret;
}

#define ToRadian(x) ((x) * M_PI / 180.0f) // Из градусов в радианы
#define ToDegree(x) ((x) * 180.0f / M_PI) // Из радианов в градусы

struct Matrix4f { // Матрица размера 4 на 4
	float m[4][4];

	Matrix4f() = default; // Конструктор без параметров
	inline void InitIdentity() { // Установка параметров единичной матрицы
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}
	inline Matrix4f operator*(const Matrix4f& other) const { // Перегрузка оператора умножения м/у матрицами
		Matrix4f result;

		for (unsigned i = 0; i < 4; i++) {
			for (unsigned j = 0; j < 4; j++) {
				result.m[i][j] = m[i][0] * other.m[0][j] +
								 m[i][1] * other.m[1][j] +
								 m[i][2] * other.m[2][j] +
								 m[i][3] * other.m[3][j];
			}
		}
		return result;
	}

	void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ);
	void InitRotateTransform(float RotateX, float RotateY, float RotateZ);
	void InitTranslationTransform(float x, float y, float z);
	void InitCameraTransform(const Vector3f& Target, const Vector3f& Up);
	void InitPersProjTransform(float FOV, float Width, float Height, float zNear, float zFar);
};

#endif /* MATH_3D_H */