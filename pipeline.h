#pragma once
#ifndef PIPELINE_H
#define	PIPELINE_H

#include "math_3d.h"

class Pipeline // Конвеер
{
public:
    Pipeline() // Конструктор конвеера
    {
        m_scale = Vector3f(1.0f, 1.0f, 1.0f);
        m_worldPos = Vector3f(0.0f, 0.0f, 0.0f);
        m_rotateInfo = Vector3f(0.0f, 0.0f, 0.0f);
    }

    void Scale(float ScaleX, float ScaleY, float ScaleZ) // Изменяем масштаб
    {
        m_scale.x = ScaleX;
        m_scale.y = ScaleY;
        m_scale.z = ScaleZ;
    }

    void WorldPos(float x, float y, float z) // Начало отчета нашей системы координат
    {
        m_worldPos.x = x;
        m_worldPos.y = y;
        m_worldPos.z = z;
    }

    void Rotate(float RotateX, float RotateY, float RotateZ) // Изменение параметров вращения
    {
        m_rotateInfo.x = RotateX;
        m_rotateInfo.y = RotateY;
        m_rotateInfo.z = RotateZ;
    }

    void SetPerspectiveProj(float FOV, float Width, float Height, float zNear, float zFar) // Установка проекции перспективы
    {
        m_persProj.FOV = FOV;
        m_persProj.Width = Width;
        m_persProj.Height = Height;
        m_persProj.zNear = zNear;
        m_persProj.zFar = zFar;
    }

    void SetCamera(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up) // Установить параметры камеры
    {
        m_camera.Pos = Pos;
        m_camera.Target = Target;
        m_camera.Up = Up;
    }

    const Matrix4f* GetTrans();

private:
    // Создание четырех матриц преобразования.
    // ScaleTrans - масштабирование.
    // RotateTrans - поворот.
    // TranslationTrans - перемещение.
    // PersProjTrans - перспективная проекция.
    void InitScaleTransform(Matrix4f& m) const;
    void InitRotateTransform(Matrix4f& m) const;
    void InitTranslationTransform(Matrix4f& m) const;
    void InitPerspectiveProj(Matrix4f& m) const;

private:
    Vector3f m_scale;
    Vector3f m_worldPos;
    Vector3f m_rotateInfo;

    // Стуктура перспективы проекции
    struct {
        float FOV;
        float Width;
        float Height;
        float zNear;
        float zFar;
    } m_persProj;

    // Структура камеры
    struct { 
        Vector3f Pos;
        Vector3f Target;
        Vector3f Up;
    } m_camera;

    Matrix4f m_transformation;
};

#endif	/* PIPELINE_H */