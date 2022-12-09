#pragma once

#include "asset.h"
#include "SDL_ttf.h"


namespace Core
{
    class FontAsset: public Asset
    {
        private:
            const char *p_textPath;
            uint16_t m_size;
            TTF_Font *p_font;

        public:
            ~FontAsset(){};

            FontAsset(const char *p_path, int size)
            : Asset(p_path), m_size(size)
            {}
            
            size_t getType()
            {
                return std::hash<std::string>{}("Font");
            };

            void setSize(uint16_t size);
            uint16_t getSize();

            void setFont(TTF_Font *font);
            TTF_Font *getFont();
    };
}