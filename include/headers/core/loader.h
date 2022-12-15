#pragma once

#include <iostream>
#include <string>
#include <map>

#include "renderwindow.h"
#include "SDL_ttf.h"
#include "audiomixer.h"
#include "SDL_mixer.h"
#include "asset.h"
#include "spritesheetasset.h"
#include "audioasset.h"
#include "fontasset.h"

namespace Core
{
    class Loader
    {
        private:
            static Loader instance;
            std::map<std::string, std::shared_ptr<Asset>> _loadedAssets;
            bool m_isInitialized = false;
            RenderWindow m_window;

            Loader(){};

            bool loadAssetInternal(const std::string& key, Asset *p_assetToLoad)
            {
                if (!m_isInitialized) return false;
                if (p_assetToLoad == nullptr) return false;
                
                if (p_assetToLoad->getType() == Asset::SpritesheetType)
                {
                    SpritesheetAsset *sheet = dynamic_cast<SpritesheetAsset*>(p_assetToLoad);
                    sheet->setTexture(m_window.loadTexture(sheet->getPath()));

                    p_assetToLoad = sheet;
                }
                else if (p_assetToLoad->getType() == Asset::FontAssetType)
                {
                    FontAsset *font = dynamic_cast<FontAsset*>(p_assetToLoad);
                    font->setFont(TTF_OpenFont(font->getPath(), font->getSize()));

                    p_assetToLoad = font;
                }
                else if (p_assetToLoad->getType() == Asset::AudioAssetType)
                {
                    AudioAsset *audio = dynamic_cast<AudioAsset*>(p_assetToLoad);
                    if (audio->isMusic()) audio->setAudio(nullptr, Mix_LoadMUS(audio->getPath()));
                    else audio->setAudio(Mix_LoadWAV(audio->getPath()), nullptr);
                    

                    p_assetToLoad = audio;
                }

                p_assetToLoad->setLoaded(true);
                std::cout << p_assetToLoad->getPath() << ": " << (bool)p_assetToLoad->isLoaded() << std::endl;

                _loadedAssets.emplace(key, p_assetToLoad);

                return p_assetToLoad->isLoaded();
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

            static Loader& get()
            {
                static Loader instance;
                return instance;
            }

            static void init(RenderWindow& window)
            {
                get().m_window = window;
                get().m_isInitialized = true;
            }

            static bool loadAsset(const std::string& key, Asset *p_assetToLoad)
            {
                return get().loadAssetInternal(key, p_assetToLoad);
            }

            template <class T> 
            static std::shared_ptr<T> getAsset(const std::string& key)
            {
                return get().getAssetInternal<T>(key);
            }
    };
}