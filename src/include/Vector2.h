#pragma once
#include <SFML/Graphics.hpp>

#define PI 3.14159265

namespace ast
{
    class Vector2
    {
    public:
        float x, y;
    public:
        Vector2();
        Vector2(float x, float y);
        void set(float x, float y);
        sf::Vector2f toSfVector2f();

        // Overloading basic operators
        Vector2 operator+(const Vector2& vector) const;
        Vector2 operator-(const Vector2& vector) const;
        float operator*(const Vector2& vector) const;
        Vector2 operator*(const float& scalar) const;
        Vector2 operator/(const float& scalar) const;
        Vector2& operator+=(const Vector2& vector);
        Vector2& operator-=(const Vector2& vector);
        Vector2& operator*=(const float& scalar);
        Vector2& operator/=(const float& scalar);

        static Vector2 zero();
        static Vector2 one();

        float length();
        void normalize();
        void setLength(float m);
        void clamp(float max);
        static float distance(Vector2 a, Vector2 b);
    };
}