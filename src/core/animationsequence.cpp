#include "animationsequence.h"
using namespace Core;

const std::string& AnimationSequence::getName() const
{
    return name;
}

Sprite *AnimationSequence::getCurrentFrame()
{
    Sprite *frame = m_currentFrame;

    getNextFrame();
    return frame;
}

void AnimationSequence::getNextFrame()
{
    double replays = (1.0f / m_speed);
    if (m_frameRepeats >= replays)
    {
        if (m_currentID < (m_frames.size() - 1)) 
        {
            if (m_currentID == 0) 
            {
                if (m_currentEvent.empty()) setEvent("animationStart");
                else setEvent(m_currentEvent);
            }
            else setEvent(m_currentEvent);

            m_currentID++;
        }
        else
        {
            m_currentID = 0;
            if (m_currentEvent.empty()) setEvent("animationEnd");
            else setEvent(m_currentEvent);
        }

        m_frameRepeats = 1;
    }
    else m_frameRepeats++;

    m_currentFrame = m_frames.at(m_currentID);
    m_currentEvent = m_frameEvents[m_currentFrame];
    // std::cout<< "frame: " << m_currentID << std::endl;
}
void AnimationSequence::addFrameToSequence(Sprite *sprite, uint16_t count, const std::string& event)
{
    // We substract 1 to the counter to make the use of this service more readable and convenient
    auto max = count - 1;
    if (max > 0)
    {
        for (auto i = 0; i < max; i++) m_frames.emplace_back(sprite);
    }
    else m_frames.emplace_back(sprite);

    m_frameEvents[sprite] = event;
}

uint16_t AnimationSequence::getSize()
{
    return m_frames.size();
}

void AnimationSequence::setSpeed(double speed)
{
    m_speed = speed;
}
double AnimationSequence::getSpeed()
{
    return m_speed;
}

void AnimationSequence::setEvent(const std::string& strEvent)
{
    if (m_currentEvent != strEvent) m_currentEvent = strEvent;
}
std::string& AnimationSequence::getEvent()
{
    return m_currentEvent;
}

void AnimationSequence::reset()
{
    m_currentFrame = m_frames.at(0);
    m_currentID = 0;
    m_frameRepeats = 1;
}