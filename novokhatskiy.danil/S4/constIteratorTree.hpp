#ifndef CONST_ITERATOR_AVL
#define CONST_ITERATOR_AVL

#include <cassert>
#include <iterator>
#include <functional>
#include <utility>
#include "AVLtreeNode.hpp"

namespace novokhatskiy
{
  template< class Key, class Value, class Compare >
  class Tree;

  template< class Key, class Value, class Compare  = std::less< Key > >
  struct ConstIteratorTree : public std::iterator< std::bidirectional_iterator_tag, Value >
  {
    friend class Tree< Key, Value,Compare >;
    using node_t = detail::NodeTree< Key, Value >;
    using constIter = ConstIteratorTree< Key, Value, Compare >;

    ConstIteratorTree(node_t* node):
      node_(node)
    {}
    constIter& operator=(const constIter& other) = default;

    bool operator!=(const constIter& other) const
    {
      assert(node_ != nullptr);
      return !(*this == other);
    }

    bool operator==(const constIter& other) const
    {
      assert(node_ != nullptr);
      return *this == other;
    }

    constIter& operator++()
    {
      if (node_->right)
      {
        // node_ = node_->right;
        goLastLeft();
        return *this;
      }
      while (node_->parent && node_->parent->right == node_)
      {
        node_ = node_->parent;
      }
      node_ = node_->parent;
      return *this;
    }

    constIter& operator--()
    {

    }

    const std::pair< Key, Value > operator*() const
    {
      assert(node_ != nullptr);
      return node_->value;
    }

    const std::pair< Key, Value >* operator->() const
    {
      assert(node_ != nullptr);
      return std::addressof(node_->value);
    }

    void goLastRight()
    {
      auto tmp = node_->right;
      while (tmp->right)
      {
        tmp = tmp->right;
      }
      node_ = tmp;
    }

    void goLastLeft()
    {
      auto tmp = node_->left;
      while (tmp->left)
      {
        tmp = tmp->left;
      }
      node_ = tmp;
    }

  private:
    node_t* node_;
  };
}

#endif
