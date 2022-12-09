#include "spritesheetasset.h"
using namespace Core;

void SpritesheetAsset::setTexture(SDL_Texture *p_tex)
{
    p_texture = p_tex;
    initTexture();
}

void SpritesheetAsset::initTexture()
{
    // std::cout << "initiating texture..." << std::endl;
    // The width and the height of the texture
    int w, h;
    if (SDL_QueryTexture(p_texture, NULL, NULL, &w, &h))
    {
        std::cout << SDL_GetError() << std::endl;
        return;
    }
    
    m_sprites.clear();

    // TODO create another method that makes it prettier

    if (m_vertical)
    {
        for (int x = 0; x < (w / m_width); x++)
        {
            for (int y = 0; y < (h / m_height); y++)
            {
                std::cout << "adding sprite..." << std::endl;
                SDL_Rect rect = {x * m_width, y * m_height, m_width, m_height};
                auto sprite = std::make_shared<Sprite>(p_texture, rect);
                m_sprites.push_back(sprite);
            }

            if (m_limit != 0)
            {
                if (m_sprites.size() >= m_limit)
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
                auto sprite = std::make_shared<Sprite>(p_texture, rect);
                m_sprites.push_back(sprite);
            }

            if (m_limit != 0)
            {
                if (m_sprites.size() >= m_limit)
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
    return p_texture;
}

std::shared_ptr<Sprite> SpritesheetAsset::getSpriteAt(const uint16_t& index)
{
    if (index < m_sprites.size() && index >= 0)
        return m_sprites.at(index);
    else 
    {
        std::cout << "The index: '" << index << "' is invalid" << std::endl;
        return nullptr;
    }
}
std::shared_ptr<Sprite> SpritesheetAsset::getCurrentSprite()
{
    if (m_currentSprite < m_sprites.size() && m_currentSprite >= 0)
        return m_sprites.at(m_currentSprite);
    else return nullptr;
}
std::vector<Sprite*> SpritesheetAsset::getAllSprites()
{
    std::vector<Sprite*> sprites;

    for (auto i = 0; i < m_sprites.size(); i++)
    {
        sprites.emplace_back(m_sprites.at(i).get());
    }
    
    return sprites;
}
uint16_t SpritesheetAsset::getCurrentSpriteID()
{
    return m_currentSprite;
}
uint16_t SpritesheetAsset::getSpriteCount()
{
    return m_sprites.size();
}
void SpritesheetAsset::setCurrentSprite(const uint16_t& index)
{
    if (index < m_sprites.size() && index >= 0)
        m_currentSprite = index;
    else std::cout << "The index: '" << index << "' is invalid" << std::endl;
}