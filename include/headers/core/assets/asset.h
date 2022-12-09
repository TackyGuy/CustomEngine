#pragma once

#include <memory>
#include <iostream>
#include <type_traits>

namespace Core
{
    class SpritesheetAsset;
    class FontAsset;
    class Asset
    {
        private:
            
        protected:
            bool m_loaded;
            const char *p_textPath;
        public:
            static const size_t NullType;
            static const size_t SpritesheetType;
            static const size_t FontAssetType;
            Asset(const char* p_path):p_textPath(p_path){}
            virtual ~Asset() = default;

            void setLoaded(bool value);
            bool isLoaded();

            void setPath(const char *p_path);
            const char* getPath();

            virtual size_t getType()
            {
                return NullType;
            }
            template <class T>
            static size_t getTypeByClass()
            {
                if (std::is_same<T, SpritesheetAsset>::value)
                    return SpritesheetType;
                else if (std::is_same<T, FontAsset>::value)
                    return FontAssetType;
                else return NullType;
            }
            
    };
}