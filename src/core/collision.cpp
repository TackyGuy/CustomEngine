#include "collision.hpp"
using namespace Core;

bool Collision::AABB(const BoundingBox& boxA, const BoundingBox& boxB)
{
    Vector2 minA = boxA.getMin();
    Vector2 maxA = boxA.getMax();

    Vector2 minB = boxB.getMin();
    Vector2 maxB = boxB.getMax();

    if 
    (
        maxA.getX() > minB.getX()
        && minA.getX() < maxB.getX()
        && maxA.getY() > minB.getY()
        && minA.getY() < maxB.getY()
    )
    {
        return true;
    }
    
    return false;
}

void Collision::createNode(Node& root, std::shared_ptr<ColliderComponent> collider)
{
    if (collider == nullptr) 
    {
        std::cout << "[Collision]: Collider is invalid" << std::endl;
        return;
    }

    // If our root has children nodes, we check the deepest intersecting one
    // And try to attach our collider to it
    if (!root.Children.empty())
    {
        // We get the deepest intersecting node in the tree
        auto connector = getDeepestIntersectingNode(&root, collider);

        // If there are no intersecting nodes we split the root node further
        if (connector == nullptr) splitBranch(root, collider);
        // If the intersecting node is the root, we try to split the root further
        else if (connector == &root) splitBranch(root, collider);
        // Otherwise we create a new node and add it to the connector
        else connector->attachChild(new Node(connector, collider));
    }
    // If our root doesn't have any branching nodes, we split it
    else 
    {
        // If there are no current branches in the tree
        splitBranch(root, collider);
    }
}

Node *Collision::getDeepestIntersectingNode(Node *root, std::shared_ptr<ColliderComponent> collider)
{
    Node *connector = nullptr;

    if (!root->Children.empty())
    {
        int intersectionCount = 0;
        std::vector<Node*>::iterator it;
        for (it = root->Children.begin(); it != root->Children.end(); it++)
        {
            // If our collider intersects with the current Node, we increase the count of intersections and assign the connector
            if (AABB((*it)->AABB, collider->getAABB()))
            {
                intersectionCount++;
                connector = *it;
            }
        }

        switch (intersectionCount)
        {
            case 0:
                // If there are no intersections we return nullptr
                connector = nullptr;
                break;
            case 1:
                // If there is only one intersection, we check if our collider intersects with a deeper node
                connector = getDeepestIntersectingNode(connector, collider);
                // If there are no deeper intersections found, it means that the deepest intersecting node is the root
                if (connector == nullptr) connector = root;
                break;

            default:
                // If there are 2 or more intersections, the node should be connected to the root
                connector = root;
                break;
        }
    }

    return connector;
}

void Collision::splitBranch(Node& branch, std::shared_ptr<ColliderComponent> collider)
{
    // std::cout << "...splitting branch..." << std::endl;

    bool isHorizontal = false;

    Vector2 center, extents;

    // We check which axis is the greatest and we divide by two
    if (branch.AABB.getSize().getX() >= branch.AABB.getSize().getY())
    {
        center = Vector2(branch.AABB.getCenter().getX() * 0.5f, branch.AABB.getCenter().getY());
        extents = Vector2(branch.AABB.getExtents().getX() * 0.5f, branch.AABB.getExtents().getY());

        isHorizontal = true;
    }
    else
    {
        center = Vector2(branch.AABB.getCenter().getX(), branch.AABB.getCenter().getY() * 0.5f);
        extents = Vector2(branch.AABB.getExtents().getX(), branch.AABB.getExtents().getY() * 0.5f);
    }

    BoundingBox leftBox;
    BoundingBox rightBox;
    // We create a new bounding box with the new values
    leftBox = BoundingBox(center, extents);
    Node *leftNode = new Node(&branch, leftBox);

    // We create another bounding box on the opposite side and check again
    Vector2 flippedCenter = (isHorizontal) ? 
        Vector2(center.getX() + leftNode->AABB.getSize().getX(), center.getY()) : 
        Vector2(center.getX(), center.getY() + leftNode->AABB.getSize().getY());

    rightBox = BoundingBox(flippedCenter, extents);
    Node *rightNode = new Node(&branch, rightBox);


    bool intersectsLeftBox = AABB(leftNode->AABB, collider->getAABB());
    bool intersectsRightBox = AABB(rightNode->AABB, collider->getAABB());
    // std::cout << "left: " << intersectsLeftBox << ", right: " << intersectsRightBox << std::endl;

    // If our bounding box intersects with both nodes, it means that we can't divide them more
    if (intersectsLeftBox && intersectsRightBox)
    {
        Node *newNode = new Node(&branch, collider);
        // std::cout << collider->getTag() << std::endl;
        branch.attachChild(newNode);
        // std::cout << "Finally added collider\n" << std::endl;

        return;
    }
    // ???
    else if (!intersectsLeftBox && !intersectsRightBox)
    {
        Node *newNode = new Node(&branch, collider);
        // std::cout << collider->getTag() << std::endl;
        branch.attachChild(newNode);
        // std::cout << "Finally added collider\n" << std::endl;

        return;
    }
    // Otherwise we add to the node with which it does intersect and check if we can add
    // our bounding box in a sub-branch
    else if (intersectsLeftBox) 
    {
        // std::cout << "attaching left node..." << std::endl;
        branch.attachChild(leftNode);
        splitBranch(*leftNode, collider);

        delete rightNode;
    }
    else if (intersectsRightBox)
    {
        // std::cout << "attaching right node..." << std::endl;
        branch.attachChild(rightNode);
        splitBranch(*rightNode, collider);
        
        delete leftNode;
    }
}

std::vector<Node*> Collision::getIntersectingNodes(Node *node, std::shared_ptr<ColliderComponent> collider)
{
    std::vector<Node*> res;

    std::vector<Node*>::iterator it;
    if (AABB(node->AABB, collider->getAABB()))
    {
        if (node->Children.size() > 0)
        {
            for (it = node->Children.begin(); it != node->Children.end(); it++)
            {
                auto vec = getIntersectingNodes(*it, collider);
                if (vec.size() > 0) res.insert(res.end(), vec.begin(), vec.end());
            }
        }
        if (node->Collider != nullptr && node->Collider != collider) res.emplace_back(node);
    }

    return res;
}

std::vector<std::shared_ptr<ColliderComponent>> Collision::getColliders(std::shared_ptr<ColliderComponent> col)
{
    std::vector<std::shared_ptr<ColliderComponent>> res;

    updateNodeTree();

    std::vector<Node*>::iterator it;
    auto intersectingNodes = getIntersectingNodes(&_rootNode, col);
    for (it = intersectingNodes.begin(); it != intersectingNodes.end(); it++)
    {
        res.emplace_back((*it)->Collider);
    }

    return res;
}
std::shared_ptr<ColliderComponent> Collision::getClosestCollider(std::shared_ptr<ColliderComponent> collider)
{
    std::shared_ptr<ColliderComponent> closestCollider = nullptr;
    Vector2 center = collider->getAABB().getCenter();

    std::vector<Node*>::iterator it;
    auto intersectingNodes = getIntersectingNodes(&_rootNode, collider);
    for (it = intersectingNodes.begin(); it != intersectingNodes.end(); it++)
    {
        if (closestCollider == nullptr || center.distance(closestCollider->getAABB().getCenter()) > center.distance((*it)->AABB.getCenter()))
        {
            closestCollider = (*it)->Collider;
        }
    }


    return closestCollider;
}

void Collision::updateNodeTree()
{
    dirtyNodes.clear();
    updateNodes(&_rootNode);
    // _rootNode.printChildren(0);

    std::vector<Node*>::iterator it;
    for (it = dirtyNodes.begin(); it != dirtyNodes.end(); it++)
    {
        handleDirtyNode(*it);
    }
}

void Collision::updateNodes(Node *rootNode)
{
    if (rootNode == nullptr) return;

    std::vector<Node*>::iterator it;
    for (it = rootNode->Children.begin(); it != rootNode->Children.end(); it++)
    {
        // If our current node has children we update them
        if ((*it)->Children.size() > 0) updateNodes(*it);
        // If our current node doesn't have children, we check if it has a collider and if it's flagged as dirty
        else if ((*it)->Collider != nullptr) 
        {
            if ((*it)->Collider->isDirty()) 
            {
                bool nodeNotFound = true;
                // If we can't find this node in the vector of dirty nodes, we add it
                auto sub_it = std::find(dirtyNodes.begin(), dirtyNodes.end(), (*it));
                if (sub_it != dirtyNodes.end()) nodeNotFound = false;

                if (nodeNotFound) dirtyNodes.emplace_back(*it);
            }
        }
        // If our current node doesn't have children and doesn't have a collider we flag this node as dirty
        else 
        {
            (*it)->IsDirty = true;
            dirtyNodes.emplace_back(*it);
        }
    }

}
void Collision::handleDirtyNode(Node *dirtyNode)
{
    auto oldParent = dirtyNode->Parent;
    if (oldParent != nullptr)
    {
        oldParent->removeChild(dirtyNode);
        dirtyNode->Parent = nullptr;
    }

    // If the node itself isn't dirty it means that only the collider is
    // allowing us to reattach it to another node and unflag it
    if (!dirtyNode->IsDirty)
    {
        auto newParent = getDeepestIntersectingNode(&_rootNode, dirtyNode->Collider);
        if (newParent != nullptr) 
        {
            newParent->attachChild(dirtyNode);
            dirtyNode->Parent = newParent;
        }
        dirtyNode->Collider->setDirty(false);

        // _rootNode.printChildren(0);
    }
}

void Collision::addCollider(int id, std::shared_ptr<ColliderComponent> col)
{
    std::cout << "adding new collider" << std::endl;
    _colliders.emplace(id, col);
    if (AABB(_rootNode.AABB, col->getAABB())) createNode(_rootNode, col);
}
void Collision::removeCollider(int id)
{
    if (_colliders.find(id) != _colliders.end()) _colliders.erase(id);
}
void Collision::removeAllColliders()
{
    for (auto &collider : _colliders)
    {
        collider.second = nullptr;
    }

    _colliders.clear();
}

bool Collision::findCollider(int id)
{
    if (_colliders.find(id) != _colliders.end()) return true;

    return false;
}