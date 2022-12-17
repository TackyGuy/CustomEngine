#pragma once

#include "asset.h"
#include "SDL_ttf.h"


namespace Core
{
    class FontAsset: public Asset
    {
        private:
            TTF_Font *_font;
            const int size;

        public:
            ~FontAsset()
            {
                TTF_CloseFont(_font);
            };

            /**
             * @brief Construct a new Font Asset object.
             * 
             * @param path The path of this Asset
             */
            FontAsset(const char *path, int p_size)
            : Asset(path), size(p_size)
            {}
            
            /**
             * @brief Returns the Type of this Asset.
             * 
             * @return size_t 
             */
            size_t getType()
            {
                return std::hash<std::string>{}("Font");
            };

            /**
             * @brief Set the Font of this FontAsset.
             * 
             * @param font a pointer to font
             */
            void setFont(TTF_Font *font);
            /**
             * @brief Returns the Font object
             * 
             * @return TTF_Font* 
             */
            TTF_Font *getFont();
            /**
             * @brief Returns the size of this Font
             * 
             */
            const int getSize() const;
    };
}