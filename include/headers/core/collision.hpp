#pragma once

#include <string>
#include <vector>
#include <map>

#include "collidercomponent.hpp"
#include "boundingbox.hpp"
#include "mathutils.hpp"

namespace Core
{
    struct Node
    {
        Node *Parent = nullptr;
        std::vector<Node*> Children;

        std::shared_ptr<ColliderComponent> Collider = nullptr;
        BoundingBox AABB;

        bool IsDirty = false;

        ~Node()
        {
            for (auto child : Children)
            {
                delete child;
            }
        }

        Node(Node *parent, std::shared_ptr<ColliderComponent> collider) : Parent(parent), Collider(collider), AABB(collider->getAABB())
        {}

        Node(Node *parent, const BoundingBox& box) : Parent(parent), AABB(box)
        {}

        void attachChild(Node *childNode)
        {
            Children.emplace_back(childNode);
        }
        Node *removeChildAt(int index)
        {
            Node *childNode = nullptr;
            if (index >= 0 && index < (int)Children.size()) 
            {
                childNode = Children[index];
                Children.erase(Children.begin()+index);
            }

            return childNode;
        }
        void removeChild(Node *childNode)
        {
            if (childNode == nullptr || Children.size() <= 0) return;

            std::vector<Node*>::iterator it;
            it = std::find(Children.begin(), Children.end(), childNode);

            if (it != Children.end()) Children.erase(it);
        }
        void printChildren(int depth)
        {
            depth++;

            for (int i = 0; i < depth; i++) std::cout << "\t";
            if (Children.size() > 0)
            {
                
                std::cout << "I have " << Children.size() << " branche(s): " << std::endl;
                
                for (int i = 0; i < (int)Children.size(); i++) Children[i]->printChildren(depth);
            }
            else 
            {
                if (Collider == nullptr) std::cout << "I have no branches." << std::endl;
                else std::cout << "Collider: " << Collider->getTag() << std::endl;
            }
        }
    };
    class Collision
    {
        private:
            ~Collision(){}
            Collision(){}

            inline static std::map<int, std::shared_ptr<ColliderComponent>> _colliders;
            inline static std::vector<Node*> dirtyNodes;

            inline static BoundingBox _worldAABB = BoundingBox(Vector2(1024/2, 720/2), Vector2(1024/2, 720/2));
            inline static Node _rootNode = Node(nullptr, _worldAABB);

            static void createNode(Node& node, std::shared_ptr<ColliderComponent> collider);
            static Node *getDeepestIntersectingNode(Node *root, std::shared_ptr<ColliderComponent> collider);
            static void updateNodeTree();
            static void updateNodes(Node *rootNode);
            static void handleDirtyNode(Node *dirtyNode);
            static void splitBranch(Node& branch, std::shared_ptr<ColliderComponent> collider);

            static std::vector<Node*> getIntersectingNodes(Node *node, std::shared_ptr<ColliderComponent> collider);
        public:
            /**
             * @brief Check if two BoundingBoxes overlap each other
             * 
             * @param boxA The first BoundingBox
             * @param boxB The second BoundingBox
             * @return true if the BoundingBoxes overlap
             * @return false if they don't overlap
             */
            static bool AABB(const BoundingBox& boxA, const BoundingBox& boxB);

            /**
             * @brief Get the all the ColliderComponents that collide with the specified ColliderComponent.
             * 
             * @param collider The ColliderComponent to check collision against
             * @return std::vector<ColliderComponent*> A vector holding all the found colliders.
             */
            static std::vector<std::shared_ptr<ColliderComponent>> getColliders(std::shared_ptr<ColliderComponent> collider);
            /**
             * @brief Get the Closest ColliderComponent object to the specified ColliderComponent.
             * 
             * @param collider The ColliderComponent to check collision against
             * @return ColliderComponent* A pointer to the closest ColliderComponent found.
             */
            static std::shared_ptr<ColliderComponent> getClosestCollider(std::shared_ptr<ColliderComponent> collider);
            

            /**
             * @brief Add a collider to the vector of registered ColliderComponents.
             * 
             * @param id The id of the ColliderComponent as an integer
             * @param col The ColliderComponent
             */
            static void addCollider(int id, std::shared_ptr<ColliderComponent> col);
            /**
             * @brief Remove a collider from the vector of ColliderComponents.
             * 
             * @param id The id of the ColliderComponent to remove
             */
            static void removeCollider(int id);
            /**
             * @brief Empty the vector of ColliderComponents.
             * 
             */
            static void removeAllColliders();
            /**
             * @brief Look for a specific ColliderComponent in the vector of ColliderComponents
             * 
             * @param id The id of the ColliderComponent
             * @return true if the ColliderComponent is found.
             * @return false if the ColliderComponent is not found.
             */
            static bool findCollider(int id);
    };
}