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
            std::map<std::string, std::shared_ptr<Asset>> m_loadedAssets;
            bool m_isInitialized = false;
            RenderWindow m_window;
            AudioMixer m_mixer;

            Loader(){};

            bool loadAssetInternal(const std::string& key, Asset *p_assetToLoad)
            {
                if (!m_isInitialized) return false;
                if (p_assetToLoad == nullptr) return false;
                
                if (p_assetToLoad->getType() == Asset::SpritesheetType)
                {
                    SpritesheetAsset *sheet = dynamic_cast<SpritesheetAsset*>(p_assetToLoad);
                    SDL_Texture *p_tex = m_window.loadTexture(sheet->getPath());
                    sheet->setTexture(p_tex);

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
                    audio->setMusic(Mix_LoadMUS(audio->getPath()));

                    p_assetToLoad = audio;
                }

                p_assetToLoad->setLoaded(true);
                std::cout << p_assetToLoad->getPath() << ": " << (bool)p_assetToLoad->isLoaded() << std::endl;

                m_loadedAssets.emplace(key, p_assetToLoad);

                return p_assetToLoad->isLoaded();
            }

            template <class T> 
            T* getAssetInternal(const std::string& key)
            {
                Asset *asset = m_loadedAssets[key].get();

                if (asset == nullptr)
                {
                    std::cout << "Couldn't fetch the asset '" << key << "'. Key doesn't exist." << std::endl;
                    return nullptr;
                }
                else
                {
                    if (asset->getType() == Asset::getTypeByClass<T>())
                    return static_cast<T*>(asset);
                    else 
                    {
                        std::cout << "Couldn't fetch the asset '" << key << "'. Type is invalid." << std::endl;
                        return nullptr;
                    }
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
            static T* getAsset(const std::string& key)
            {
                return get().getAssetInternal<T>(key);
            }
    };
}