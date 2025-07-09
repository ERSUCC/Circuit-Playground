#pragma once

#include <stack>

#include "object.h"

enum Axis
{
    X,
    Y
};

struct TreeNode
{
    TreeNode(Object* object, const Axis axis);

    Object* object;

    const Axis axis;

    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

class TreeIterator
{

public:
    TreeIterator(const TreeNode* root);

    Object* next();

private:
    std::stack<const TreeNode*> nodes;

};

class Tree
{

public:
    void add(Object* object);
    void remove(Object* object);

    Object* find(const SDL_FPoint& point) const;

    TreeIterator* iterator() const;

private:
    TreeNode* root = nullptr;

    unsigned int count = 0;

};
