#pragma once

#include "sprite.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

namespace Core
{
    class AnimationSequence
    {
        private:
            const std::string name;
            std::vector<std::shared_ptr<Sprite>> _frames;
            std::unordered_map<std::shared_ptr<Sprite>, std::string> m_frameEvents;
            std::shared_ptr<Sprite> _currentFrame = nullptr;
            uint16_t m_currentID = 0;
            // The number of times the current frame repeated (starts at 1)
            uint16_t m_frameRepeats = 1;
            
            double m_speed = 1.0f;
            std::string m_currentEvent;

            /**
             * @brief Set m_currentEvent to a new value
             * 
             * @param strEvent The new event
             */
            void setEvent(const std::string& strEvent);
            /**
             * @brief Sets the current frame to the the next frame in this animation
             * 
             */
            void getNextFrame();
        public:
            /**
             * @brief Construct a new Animation Sequence object.
             * 
             * @param str The name of the animation
             */
            AnimationSequence(const std::string& pName): name(pName){}
            /**
             * @brief Construct a new Animation Sequence object.
             * 
             * @param pName The name of the animation
             * @param frames A vector holding all the frames the animation should have
             */
            AnimationSequence(const std::string& pName, const std::vector<std::shared_ptr<Sprite>> frames)
            : name(pName), _frames(frames)
            {}
            
            /**
             * @brief Construct a new Animation Sequence object.
             * 
             * @param pName The name of the animation
             * @param frames A vector holding all the frames the animation should have
             * @param speed The speed at which this animation should play at
             */
            AnimationSequence(const std::string& pName, const std::vector<std::shared_ptr<Sprite>> frames, double speed)
            : name(pName), _frames(frames), m_speed(speed)
            {}

            /**
             * @brief Get the name of this animation.
             * 
             * @return const std::string& 
             */
            const std::string& getName() const;

            std::shared_ptr<Sprite> getCurrentFrame();
            
            /**
             * @brief Adds a sprite x times to this animation.
             * 
             * @param p_sprite The sprite to add to this animation
             * @param num The number of times the sprite should be added, no parameter means to only add it once
             * @param event The animation event the frame will send
             */
            void addFrameToSequence(std::shared_ptr<Sprite> sprite, uint16_t count = 1, const std::string& event = "");
            /**
             * @brief Remove a frame from the animation based of its index.
             * 
             * @param id The index of the frame to remove
             */
            void deleteFrameFromSequence(uint16_t id);
            /**
             * @brief Get the number of frames in this animation.
             * 
             * @return uint16_t size of _frames
             */
            uint16_t getSize();

            void setSpeed(double speed);
            /**
             * @brief Get the Speed of this animation.
             * 
             * @return double speed
             */
            double getSpeed();

            /**
             * @brief Get the Event of the current frame.
             * 
             * @return std::string& event
             */
            std::string& getEvent();

            /**
             * @brief Restarts the animation to its first frame.
             * 
             */
            void reset();
    };
}