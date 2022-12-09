#include "stage.h"

using namespace Core;

InputProvider *Stage::getInputProvider()
{
    return &m_inputProvider;
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