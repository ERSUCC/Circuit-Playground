#include "../include/tree.h"

TreeNode::TreeNode(Object* object, const Axis axis) :
    object(object), axis(axis) {}

TreeIterator::TreeIterator(const TreeNode* root) :
    nodes({ root }) {}

Object* TreeIterator::next()
{
    if (nodes.empty())
    {
        return nullptr;
    }

    const TreeNode* node = nodes.top();

    nodes.pop();

    if (node->right)
    {
        nodes.push(node->right);
    }

    if (node->left)
    {
        nodes.push(node->left);
    }

    return node->object;
}

void Tree::add(Object* object)
{
    if (root)
    {
        TreeNode* current = root;

        while (current)
        {
            if (current->axis == Axis::X)
            {
                if (object->getPosition().y < current->object->getPosition().y)
                {
                    if (current->left)
                    {
                        current = current->left;
                    }

                    else
                    {
                        current->left = new TreeNode(object, Axis::Y);

                        break;
                    }
                }

                else
                {
                    if (current->right)
                    {
                        current = current->right;
                    }

                    else
                    {
                        current->right = new TreeNode(object, Axis::Y);

                        break;
                    }
                }
            }

            else
            {
                if (object->getPosition().x < current->object->getPosition().x)
                {
                    if (current->left)
                    {
                        current = current->left;
                    }

                    else
                    {
                        current->left = new TreeNode(object, Axis::X);

                        break;
                    }
                }

                else
                {
                    if (current->right)
                    {
                        current = current->right;
                    }

                    else
                    {
                        current->right = new TreeNode(object, Axis::X);

                        break;
                    }
                }
            }
        }
    }

    else
    {
        root = new TreeNode(object, Axis::Y);
    }

    count++;
}

void Tree::remove(Object* object)
{
    TreeNode* prev = nullptr;
    TreeNode* current = root;

    while (current)
    {
        prev = current;

        if (current->axis == Axis::X)
        {
            if (object->getPosition().y < current->object->getPosition().y)
            {
                current = current->left;
            }

            else
            {
                current = current->right;
            }
        }

        else
        {
            if (object->getPosition().x < current->object->getPosition().x)
            {
                current = current->left;
            }

            else
            {
                current = current->right;
            }
        }
    }

    if (prev->axis == Axis::X)
    {
        if (object->getPosition().y < prev->object->getPosition().y)
        {
            prev->left = nullptr;
        }

        else
        {
            prev->right = nullptr;
        }
    }

    else
    {
        if (object->getPosition().x < prev->object->getPosition().x)
        {
            prev->left = nullptr;
        }

        else
        {
            prev->right = nullptr;
        }
    }

    count--;
}

Object* Tree::find(const SDL_FPoint& point) const
{
    TreeNode* current = root;

    while (current)
    {
        if (current->object->getPosition().x == point.x && current->object->getPosition().y == point.y)
        {
            return current->object;
        }

        if (current->axis == Axis::X)
        {
            if (point.y < current->object->getPosition().y)
            {
                current = current->left;
            }

            else
            {
                current = current->right;
            }
        }

        else
        {
            if (point.x < current->object->getPosition().x)
            {
                current = current->left;
            }

            else
            {
                current = current->right;
            }
        }
    }

    return nullptr;
}

TreeIterator* Tree::iterator() const
{
    return new TreeIterator(root);
}
