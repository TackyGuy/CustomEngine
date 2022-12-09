#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "renderwindow.h"
#include "math.h"

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
            int m_id;

            std::unordered_map<std::size_t, BaseComponent*> _components;
            TransformComponent *_transform = nullptr;

            Actor *_parent = nullptr;
            std::vector<Actor*> m_children;

        public:
            ~Actor()
            {}

            /**
             * @brief Construct a new Actor object with a transform component
             * 
             * @param pos Vector that represents the position of the actor
             * @param id Id of the actor
             */
            Actor(const Vector2 pos, const int id)
            : m_id(id)
            {
                _transform = new TransformComponent(this, pos, Vector2(1, 1));
                init();
            }
            Actor(const Vector2 pos, const Vector2 scale, const int id) : m_id(id)
            {
                _transform = new TransformComponent(this, pos, scale);
                init();
            }

            // Returns the id of this actor
            int getID();

            void init();

            virtual void start(Stage& stage){}
            virtual void update(double dt, Stage& stage)
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
                    RendererComponent *renderer = dynamic_cast<RendererComponent*>(component.second);
                    if (renderer == nullptr) continue;

                    renderer->render(window->getRenderer(), _transform->getPosition(), _transform->getScale());
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
            void addComponent(T cmpt)
            {
                // std::cout << "address: " << &cmpt << std::endl;
                if (_components.find(T::Type) != _components.end())
                {
                    std::cout << "This component ALREADY exists" << std::endl;
                    return;
                }
                // else std::cout << "Adding new component..." << std::endl;
                T* c = new T(cmpt);
                _components.emplace(T::Type, c);
            }
            /**
             * @brief Get a Component object by its type.
             * 
             * @tparam T The type of the component we're looking for.
             * @return T* The a pointer to the component if found or nullptr.
             */
            template <class T> 
            T* getComponent()
            {
                if (_components.find(T::Type) != _components.end())
                {
                    // std::cout << "This component exists" << std::endl;
                    return static_cast<T*>(_components.at(T::Type));
                }
                // else std::cout << "This component does NOT exist" << std::endl;

                return nullptr;
            }

            // Getters and setters
            #pragma region 
            void setParent(Actor* parent);
            Actor* getParent();

            void setRenderer(RendererComponent *renderer);
            RendererComponent *getRenderer();
            #pragma endregion

            /**
             * @brief Broadcasts a message to all the components attached to this Actor object.
             * 
             * @param msg A string containing the message to be broadcasted
             * @param size_t The type of the message sender
             */
            void broadcastMessage(const std::string& msg, const size_t sender) override
            {
                std::unordered_map<size_t, BaseComponent*>::iterator it;
                for (it = _components.begin(); it != _components.end(); it++)
                {
                    it->second->OnMessage(msg, sender);
                }
            }
    };
}