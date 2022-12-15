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
            void setEvent(const std::string& strEvent);
        public:
            AnimationSequence(const std::string& str): name(str){}
            AnimationSequence(const std::string& str, const std::vector<std::shared_ptr<Sprite>> frames)
            : name(str), _frames(frames)
            {}
            
            AnimationSequence(const std::string& str, const std::vector<std::shared_ptr<Sprite>> frames, double speed)
            : name(str), _frames(frames), m_speed(speed)
            {}

            const std::string& getName() const;

            std::shared_ptr<Sprite> getCurrentFrame();
            void getNextFrame();
            /**
             * @brief Adds a sprite x times to this animation.
             * 
             * @param p_sprite The sprite to add to this animation
             * @param num The number of times the sprite should be added, no parameter means to only add it once
             * @param event The animation event the frame will send
             */
            void addFrameToSequence(std::shared_ptr<Sprite> sprite, uint16_t count = 1, const std::string& event = "");
            void deleteFrameFromSequence(uint16_t id);
            uint16_t getSize();

            void setSpeed(double speed);
            double getSpeed();
            
            std::string& getEvent();

            void reset();
    };
}