#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <utility> // для std::pair

namespace detail
{
    template <class Key, class Value>
    struct TreeNode
    {
        std::pair<Key, Value> value;
        TreeNode* left_ = nullptr;
        TreeNode* right_ = nullptr;

        TreeNode(const std::pair<Key, Value>& val) : value(val) {}
    };
}

#endif
