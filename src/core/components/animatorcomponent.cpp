#include "animatorcomponent.h"
using namespace Core;


const size_t AnimatorComponent::Type = std::hash<std::string>{}("Animator");

bool AnimatorComponent:: isValid(const std::string& key)
{
    if (m_sequences.find(key) == m_sequences.end())
    {
        std::cout << "The key '" << key << "' doesn't exist" << std::endl;
        return false;
    }

    return true;
}

void AnimatorComponent::addSequence(const AnimationSequence& sequence)
{
    m_sequences.emplace(sequence.getName(), sequence);
}

void AnimatorComponent::playSequence(const std::string& key)
{
    if (!isValid(key)) return;

    if (m_currentSequence == &m_sequences.at(key)) return;

    m_currentSequence = &m_sequences.at(key);
    m_currentSequence->reset();
}

AnimationSequence *AnimatorComponent::getSequence(const std::string& key)
{
    if (!isValid(key)) return nullptr;

    return &m_sequences.at(key);
}
AnimationSequence *AnimatorComponent::getCurrentSequence()
{
    return m_currentSequence;
}

void AnimatorComponent::flipRenderer(bool val)
{
    _spriteRenderer->flip(val);
}