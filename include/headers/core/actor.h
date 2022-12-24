#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "renderwindow.h"
#include "mathutils.h"

#include "broadcasterinterface.h"
#include "basecomponent.h"
#include "transformcomponent.h"
#include "renderercomponent.h"

#include "collision.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

namespace Core
{
    class Stage;
    class Actor : public BroadcasterInterface
    {
        protected:
            Stage &stage;
            int m_id;

            std::unordered_map<std::size_t, std::shared_ptr<BaseComponent>> _components;
            std::shared_ptr<TransformComponent> _transform = nullptr;

        public:
            ~Actor()
            {}

            /**
             * @brief Construct a new Actor object with a transform component
             * 
             * @param pos Vector that represents the position of the actor
             * @param id Id of the actor
             */
            Actor(Stage &r_stage, const int id, const Vector2 pos)
            : stage(r_stage), m_id(id)
            {
                _transform = std::make_shared<TransformComponent>(*this, pos, Vector2(1, 1));
            }
            Actor(Stage &r_stage, const int id, const Vector2 pos, const Vector2 scale) : stage(r_stage), m_id(id)
            {
                _transform = std::make_shared<TransformComponent>(*this, pos, scale);
            }
            

            // Returns the id of this actor
            int getID();

            virtual void init();

            virtual void start()
            {
                
            }
            virtual void update(double dt)
            {
                for (auto component : _components)
                {
                    component.second->update(dt, stage);
                }
            }
            virtual void render(RenderWindow *window)
            {
                for (auto component : _components)
                {
                    std::weak_ptr<RendererComponent> renderer = std::dynamic_pointer_cast<RendererComponent>(component.second);
                    if (renderer.expired()) continue;
                    if (auto sharedPtr = renderer.lock())
                    {
                        sharedPtr->render(window->getRenderer(), _transform->getPosition(), _transform->getScale());
                    }
                }
                
            }
            // virtual void OnDelete();
            
            /**
             * @brief Attaches a component to the actor and adds it to the _components unordered map.
             * 
             * @tparam T The type of the component
             * @param cmpt The component to add
             */
            template <class T>
            void addComponent(T &&cmpt)
            {
                if (_components.find(T::Type) != _components.end())
                {
                    std::cout << "This component ALREADY exists" << std::endl;
                    return;
                }
                // else std::cout << "Adding new component..." << std::endl;
                auto component = std::make_shared<T>(std::forward<T>(cmpt));
                _components.emplace(T::Type, component);
            }
            /**
             * @brief Attaches a component to the actor and adds it to the _components unordered map.
             * 
             * @tparam T The type of the component
             * @param cmpt The component to add
             */
            template <class T>
            void addComponent(std::shared_ptr<T> cmpt)
            {
                if (_components.find(T::Type) != _components.end())
                {
                    std::cout << "This component ALREADY exists" << std::endl;
                    return;
                }
                // else std::cout << "Adding new component..." << std::endl;
                _components.emplace(T::Type, cmpt);
            }
            /**
             * @brief Get a Component object by its type.
             * 
             * @tparam T The type of the component we're looking for.
             * @return T* The a pointer to the component if found or nullptr.
             */
            template <class T>
            std::shared_ptr<T> getComponent()
            {
                std::shared_ptr<T> sharedPtr = nullptr;
                if (_components.find(T::Type) != _components.end())
                {
                    // std::cout << "This component exists" << std::endl;
                    sharedPtr = std::static_pointer_cast<T>(_components.at(T::Type));
                }
                // else std::cout << "This component does NOT exist" << std::endl;

                return sharedPtr;
            }

            // Getters and setters
            #pragma region 
            void setParent(Actor* parent);
            Actor* getParent();

            #pragma endregion

            /**
             * @brief Broadcasts a message to all the components attached to this Actor object.
             * 
             * @param msg A string containing the message to be broadcasted
             * @param size_t The type of the message sender
             */
            void broadcastMessage(const std::string& msg, const size_t sender) const override
            {
                for (auto it = _components.begin(); it != _components.end(); it++)
                {
                    it->second->OnMessage(msg, sender);
                }
            }
    };
}