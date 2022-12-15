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

void AnimatorComponent::addSequence(const AnimationSequence sequence)
{
    m_sequences.emplace(sequence.getName(), sequence);
}

void AnimatorComponent::playSequence(const std::string& key)
{
    if (!isValid(key)) return;

    if (_currentSequence == &m_sequences.at(key)) return;

    _currentSequence = &m_sequences.at(key);
    _currentSequence->reset();
}

std::shared_ptr<AnimationSequence> AnimatorComponent::getSequence(const std::string& key)
{
    if (!isValid(key)) return nullptr;

    return std::make_shared<AnimationSequence>(m_sequences.at(key));
}
std::shared_ptr<AnimationSequence> AnimatorComponent::getCurrentSequence()
{
    if (!_currentSequence) return nullptr;
    
    return std::make_shared<AnimationSequence>(*_currentSequence);
}

void AnimatorComponent::flipRenderer(bool val)
{
    spriteRenderer.flip(val);
}