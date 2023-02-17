#pragma once

#include <iostream>
#include <string>
#include <map>
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "renderwindow.hpp"
#include "audiomixer.hpp"
#include "asset.hpp"
#include "fontasset.hpp"
#include "audioasset.hpp"
#include "spritesheetasset.hpp"

namespace Core
{
    class Loader
    {
        private:
            static Loader s_instance;
            std::map<std::string, std::shared_ptr<Asset>> _loadedAssets;
            bool m_debug = false;
            bool m_isInitialized = false;
            RenderWindow m_window;

            Loader(){};

            bool loadAssetInternal(const std::string& key, Asset *assetToLoad)
            {
                if (!m_isInitialized) return false;
                if (!assetToLoad) return false;
                if (_loadedAssets.find(key) != _loadedAssets.end()) return false;

                std::string path;
                if (m_debug) path = "../";
                
                if (assetToLoad->getType() == Asset::SpritesheetType)
                {
                    auto sheet = dynamic_cast<SpritesheetAsset*>(assetToLoad);
                    path.append(sheet->getPath());
                    sheet->setTexture(m_window.loadTexture(path.c_str()));

                    assetToLoad = sheet;
                }
                else if (assetToLoad->getType() == Asset::FontAssetType)
                {
                    auto font = dynamic_cast<FontAsset*>(assetToLoad);
                    path.append(font->getPath());
                    font->setFont(TTF_OpenFont(path.c_str(), font->getSize()));

                    assetToLoad = font;
                }
                else if (assetToLoad->getType() == Asset::AudioAssetType)
                {
                    auto audio = dynamic_cast<AudioAsset*>(assetToLoad);
                    if (audio->isMusic()) audio->setAudio(nullptr, Mix_LoadMUS(audio->getPath()));
                    else 
                    {
                        std::string path = "../";
                        path.append(audio->getPath());
                        audio->setAudio(Mix_LoadWAV(path.c_str()), nullptr);
                    }
                    
                    assetToLoad = audio;
                }

                if (!assetToLoad) return false;

                assetToLoad->setLoaded(true);
                std::cout << assetToLoad->getPath() << ": " << (bool)assetToLoad->isLoaded() << std::endl;

                _loadedAssets.emplace(key, assetToLoad);

                return assetToLoad->isLoaded();
            }

            template <class T> 
            std::shared_ptr<T> getAssetInternal(const std::string& key)
            {
                auto asset = _loadedAssets[key];

                if (!asset)
                {
                    std::cout << "Couldn't fetch the asset '" << key << "' as it doesn't exist." << std::endl;
                    return nullptr;
                }
                
                if (asset->getType() == Asset::getTypeByClass<T>()) return std::static_pointer_cast<T>(asset);
                else 
                {
                    std::cout << "Couldn't fetch the asset '" << key << "'. Type is invalid." << std::endl;
                    return nullptr;
                }
            }
            
        public:
            Loader(Loader &other) = delete;

            void operator=(const Loader&) = delete;

            static Loader& instance()
            {
                static Loader s_instance;
                return s_instance;
            }

            /**
             * @brief Initializes the Asset Loader
             * 
             * @param window The RenderWindow object
             */
            static void init(RenderWindow& window)
            {
                instance().m_window = window;
                instance().m_isInitialized = true;
            }

            /**
             * @brief Loads and cache a new asset in the map of loaded assets
             * 
             * @param key The key to assign to the newly created Asset
             * @param assetToLoad A pointer to the Asset
             * @return true if the asset was loaded successfully
             * @return false if the asset could not be loaded
             */
            static bool loadAsset(const std::string& key, Asset *assetToLoad)
            {
                return instance().loadAssetInternal(key, assetToLoad);
            }

            /**
             * @brief Get the Asset of type <T> if it exists in the map of loaded assets
             * 
             * @tparam T The type of the Asset
             * @param key The key of the Asset
             * @return std::shared_ptr<T> shared_ptr to the Asset
             */
            template <class T> 
            static std::shared_ptr<T> getAsset(const std::string& key)
            {
                return instance().getAssetInternal<T>(key);
            }
    };
}