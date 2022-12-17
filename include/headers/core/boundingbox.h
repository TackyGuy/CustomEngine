#pragma once

#include <vector>
#include "math.h"

namespace Core
{
    class BoundingBox
    {
        private:
            // Coordinates of the center point
            Vector2 m_center;
            // How far the bounding box extends from its center point in the x and y dimensions. 
            // This is also half of the size of the bounding box.
            Vector2 m_extents;
            // The size of the box
            Vector2 m_size;
            // The coordinates of the left-bottom corner of the box
            Vector2 m_min;
            // The coordinates of the top-right corner of the box
            Vector2 m_max;
        public:
            ~BoundingBox(){};

            /**
             * @brief Construct a new BoundingBox object.
             * 
             * @param center The coordinates of the center of the box.
             * @param extents The extents (or wingspan) of the box from its center.
             */
            BoundingBox(const Vector2& center, const Vector2& extents) : m_center(center), m_extents(extents)
            {
                m_min = center - extents;
                m_max = center + extents;

                m_size = extents * 2;
            }
            BoundingBox(){}

            /**
             * @brief Set the center of the BoundingBox to a new Vector2 and recalculates the minimums and maximums vectors.
             * 
             * @param center The new position of the center
             */
            void setCenter(const Vector2& center);
            /**
             * @brief Get the center of the BoundingBox as a Vector2.
             * 
             * @return Vector2& A reference to the Vector2 representing the center
             */
            const Vector2& getCenter() const;

            /**
             * @brief Expands the BoundingBox in all directions equally.
             * 
             * @param val The amount by which the BoundingBox should be expanded
             */
            void expand(float val);
            /**
             * @brief Expands the BoundingBox in both directions.
             * 
             * @param x The amount by which the BoundingBox should be expanded horizontally
             * @param y The amount by which the BoundingBox should be expanded vertically
             */
            void expand(float x, float y);
            void expand(Vector2 vec2);
            /**
             * @brief Set the Extents(wingspan) of the BoundingBox as a Vector2.
             * 
             * @param vec2 
             */
            void setExtents(Vector2 vec2);
            /**
             * @brief Get the extents(wingspan) of the BoundingBox as a Vector2.
             * 
             * @return Vector2& A reference to the Vector2 representing its extents
             */
            const Vector2& getExtents() const;
            /**
             * @brief Get the size of the BoundingBox as a Vector2.
             * 
             * @return Vector2& A reference to the Vector2 representing its size
             */
            const Vector2& getSize() const;

            /**
             * @brief Get the Min object.
             * 
             * @return Vector2& 
             */
            const Vector2& getMin() const;
            /**
             * @brief Get the Max object.
             * 
             * @return Vector2& 
             */
            const Vector2& getMax() const;
    };
}