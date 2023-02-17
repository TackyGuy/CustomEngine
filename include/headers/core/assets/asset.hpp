#pragma once

#include <memory>
#include <iostream>
#include <type_traits>

namespace Core
{
    class SpritesheetAsset;
    class AudioAsset;
    class FontAsset;
    class Asset
    {
        private:
            
        protected:
            bool m_loaded;
            const char *_textPath;
        public:
            static const size_t NullType;
            static const size_t SpritesheetType;
            static const size_t FontAssetType;
            static const size_t AudioAssetType;

            virtual ~Asset(){}
            /**
             * @brief Construct a new Asset object.
             * 
             * @param path The path of where this asset is stored
             */
            Asset(const char* path):_textPath(path){}

            /**
             * @brief Set the m_loaded boolean to the designated value.
             * 
             * @param value The new value of m_loaded
             */
            void setLoaded(bool value);
            /**
             * @brief Is this Asset loaded?
             * 
             * @return true if it has been loaded
             * @return false if it has not been loaded
             */
            bool isLoaded();

            /**
             * @brief Set the Path of this asset.
             * 
             * @param p_path the Path as a char*
             */
            void setPath(const char *path);
            /**
             * @brief Get the Path of this Asset.
             * 
             * @return const char* 
             */
            const char* getPath();

            /**
             * @brief Get the Type of this Asset.
             * 
             * @return size_t 
             */
            virtual size_t getType()
            {
                return NullType;
            }
            /**
             * @brief Get the Type of an Asset based of its class <T>.
             * 
             * @tparam T The class of the Asset
             * @return size_t The Type of the asset
             */
            template <class T>
            static size_t getTypeByClass()
            {
                if (std::is_same<T, SpritesheetAsset>::value)
                    return SpritesheetType;
                else if (std::is_same<T, FontAsset>::value)
                    return FontAssetType;
                else if (std::is_same<T, AudioAsset>::value)
                    return AudioAssetType;
                else return NullType;
            }
            
    };
}