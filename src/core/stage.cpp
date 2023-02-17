#include "stage.hpp"

using namespace Core;

std::shared_ptr<InputProvider> Stage::getInputProvider()
{
    return _inputProvider;
}

std::shared_ptr<AudioMixer> Stage::getAudioMixer()
{
    return _audioMixer;
}


Vector2 Stage::center() const
{
    Vector2 vec2 = Vector2((stageWidth * 0.5f) - 1, (stageHeight * 0.5f) - 1);
    return vec2;
}

const double Stage::getTime() const
{
    return m_elapsedTime;
}