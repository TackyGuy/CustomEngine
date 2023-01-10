#pragma once

#include <iostream>
#include <sstream>
#include <cmath>

namespace Core
{
    class Vector2
    {
        private:
            float m_x, m_y;
        public:
            ~Vector2(){};
            
            Vector2() : m_x(0.0f), m_y(0.0f){}

            Vector2(float x, float y) : m_x(x), m_y(y){}
            

            float getX() const
            {
                return m_x;
            }
            float getY() const
            {
                return m_y;
            }

            void set(float x, float y)
            {
                m_x = x;
                m_y = y;
            }

            void set(Vector2 vec2)
            {
                m_x = vec2.getX();
                m_y = vec2.getY();
            }

            void add(Vector2 vec2)
            {
                m_x += vec2.getX();
                m_y += vec2.getY();
            }
            void add(float x, float y)
            {
                m_x += x;
                m_y += y;
            }
            void add(float value)
            {
                m_x += value;
                m_y += value;
            }

            // Remove from the vector
            void substract(Vector2 vec2)
            {
                m_x -= vec2.getX();
                m_y -= vec2.getY();
            }
            void substract(float x, float y)
            {
                m_x -= x;
                m_y -= y;
            }
            void substract(float value)
            {
                m_x -= value;
                m_y -= value;
            }

            void multiply(Vector2 vec2)
            {
                m_x *= vec2.getX();
                m_y *= vec2.getY();
            }
            void multiply(float multiplier)
            {
                m_x *= multiplier;
                m_y *= multiplier;
            }

            void pow(float power)
            {
                m_x = std::pow(m_x, power);
                m_y = std::pow(m_y, power);
            }
            Vector2 getPow(float power) const
            {
                Vector2 res(std::pow(m_x, power), std::pow(m_y, power));
                return res;
            }

            // The distance between this and another vector2
            float distance(Vector2 other) const
            {
                float d;
                d = std::sqrt((std::pow((m_x - other.getX()), 2) + std::pow((m_y - other.getY()), 2)));

                return d;
            }

            // Normalize the vector
            void normalize()
            {
                m_x = (m_x == 0) ? 0 : (m_x > 0) ? 1 : -1;
                m_y = (m_y == 0) ? 0 : (m_y > 0) ? 1 : -1;
            }

            friend std::ostream& operator<<(std::ostream& os, const Vector2& vec2)
            {
                std::ostringstream s;
                s << "Vector2(" << vec2.m_x << ", " << vec2.m_y << ")";
                std::string res = s.str();

                os << res;

                return os;
            }
            void print()
            {
                std::cout << m_x << ", " << m_y << std::endl;
            }

            bool operator ==(Vector2 const& other) const
            {
                if (m_x == other.getX() && m_y == other.getY()) return true;

                return false;
            }
            bool operator !=(Vector2 const& other) const
            {
                if (m_x == other.getX() && m_y == other.getY()) return false;
                
                return true;
            }
            Vector2 operator +(Vector2 const& other) const
            {
                Vector2 res(m_x + other.m_x, m_y + other.m_y);
                return res;
            }
            Vector2 operator -(Vector2 const& other) const
            {
                Vector2 res(m_x - other.m_x, m_y - other.m_y);
                return res;
            }
            Vector2 operator *(Vector2 const& other) const
            {
                Vector2 res(m_x * other.getX(), m_y * other.m_x);
                return res;
            }
            Vector2 operator *(float const& multiplier) const
            {
                Vector2 res(m_x * multiplier, m_y * multiplier);
                return res;
            }
    };
}