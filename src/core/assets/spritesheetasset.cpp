#include "spritesheetasset.hpp"
using namespace Core;

void SpritesheetAsset::setTexture(SDL_Texture *tex)
{
    _texture = tex;
    initTexture();
}

void SpritesheetAsset::initTexture()
{
    int w, h;
    if (SDL_QueryTexture(_texture, NULL, NULL, &w, &h))
    {
        std::cout << SDL_GetError() << std::endl;
        return;
    }
    
    _sprites.clear();

    // TODO create another method that makes it prettier

    if (m_vertical)
    {
        for (int x = 0; x < (w / m_width); x++)
        {
            for (int y = 0; y < (h / m_height); y++)
            {
                std::cout << "adding sprite..." << std::endl;
                SDL_Rect rect = {x * m_width, y * m_height, m_width, m_height};
                auto sprite = std::make_shared<Sprite>(_texture, rect);
                _sprites.push_back(sprite);
            }

            if (m_limit != 0)
            {
                if (_sprites.size() >= m_limit)
                {
                    break;
                }
            }
        }
    }
    else
    {
        for (int y = 0; y < (h / m_height); y++)
        {
            for (int x = 0; x < (w / m_width); x++)
            {
                // std::cout << "adding sprite..." << std::endl;
                SDL_Rect rect = {x * m_width, y * m_height, m_width, m_height};
                auto sprite = std::make_shared<Sprite>(_texture, rect);
                _sprites.push_back(sprite);
            }

            if (m_limit != 0)
            {
                if (_sprites.size() >= m_limit)
                {
                    break;
                }
            }
        }
    }

    

    
    // std::cout << "There are " << m_frames.size() << " frame(s) in the sprite '" << p_textPath << "'" << std::endl;
}
SDL_Texture *SpritesheetAsset::getTexture()
{
    return _texture;
}

std::shared_ptr<Sprite> SpritesheetAsset::getSpriteAt(const uint16_t& index)
{
    if (index < _sprites.size() && index >= 0)
        return _sprites.at(index);
    else 
    {
        std::cout << "The sprite at index: '" << index << "' is invalid" << std::endl;
        return nullptr;
    }
}
std::vector<std::shared_ptr<Sprite>> SpritesheetAsset::getAllSprites()
{
    std::vector<std::shared_ptr<Sprite>> sprites;

    for (auto i = 0; i < _sprites.size(); i++)
    {
        sprites.emplace_back(_sprites.at(i));
    }
    
    return sprites;
}