#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "src/include/Vector2.h"

namespace ast
{
    Vector2::Vector2() { }

    Vector2::Vector2(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    void Vector2::set(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    sf::Vector2f Vector2::toSfVector2f() { return sf::Vector2f(this->x, this->y); }

    #pragma region Operator Overloads
    Vector2 Vector2::operator+(const Vector2& vector) const
    {
        ast::Vector2 temp = ast::Vector2(this->x + vector.x, this->y + vector.y);
        return temp;
    }

    Vector2 Vector2::operator-(const Vector2& vector) const
    {
        ast::Vector2 temp = ast::Vector2(this->x - vector.x, this->y - vector.y);
        return temp;
    }

    float Vector2::operator*(const Vector2& vector) const
    {
        //float dot = this->x * vector.x + this->y + vector.y;
        return this->x * vector.x + this->y * vector.y;
    }

    Vector2 Vector2::operator*(const float& scalar) const
    {
        ast::Vector2 temp = ast::Vector2(this->x * scalar, this->y * scalar);
        return temp;
    }

    Vector2 Vector2::operator/(const float& scalar) const
    {
        ast::Vector2 temp = ast::Vector2(this->x / scalar, this->y / scalar);
        return temp;
    }

    Vector2& Vector2::operator+=(const Vector2& vector)
    {
        this->x += vector.x;
        this->y += vector.y;
        return *this;
    }

    Vector2& Vector2::operator-=(const Vector2& vector)
    {
        this->x -= vector.x;
        this->y -= vector.y;
        return *this;
    }

    Vector2& Vector2::operator*=(const float& scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }

    Vector2& Vector2::operator/=(const float& scalar)
    {
        this->x /= scalar;
        this->y /= scalar;
        return *this;
    }
    #pragma endregion Operator Overloads

    Vector2 Vector2::zero()
    {
        return ast::Vector2(0.f, 0.f);
    }

    Vector2 Vector2::one()
    {
        return ast::Vector2(1.f, 1.f);
    }

    float Vector2::length()
    {
        return std::sqrt(x*x + y*y);
    }
    
    void Vector2::normalize()
    {
        *this /= this->length();
        //std::cout << this->x << " " << this->y << std::endl;
    }

    void Vector2::setLength(float m)
    {
        *this *= (m / this->length());
        //*this *= m / this->length();
    }

    void Vector2::clamp(float max)
    {
        if(this->length() > max)
        {
            this->setLength(max);
        }
    }

    float Vector2::distance(Vector2 a, Vector2 b)
    {
        return std::sqrt((b.x - a.x)*(b.x - a.x)
                            +(b.y - a.y)*(b.y - a.y));
    }
}
