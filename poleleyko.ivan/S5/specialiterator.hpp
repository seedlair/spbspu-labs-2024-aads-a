#ifndef SPECIAL_ITERATOR_HPP
#define SPECIAL_ITERATOR_HPP

#include <iterator>
#include "stack.hpp"
#include "queue.hpp"

namespace poleleyko
{
    template<typename Key, typename Value, typename Compare>
    class Tree;

    template<typename Key, typename Value, typename Compare>
    class ConstTreeIterator;

    template<typename Key, typename Value, typename Compare>
    class ConstRnlIterator;

    template<typename Key, typename Value, typename Compare = std::less<Key>>
    class ConstLnrIterator : public std::iterator<std::bidirectional_iterator_tag, std::pair<Key, Value>>
    {
        using val_type = std::pair<Key, Value>;
        friend class Tree<Key, Value, Compare>;
        friend class ConstTreeIterator<Key, Value, Compare>;
        friend class ConstRnlIterator<Key, Value, Compare>;

    public:
        using reference = const val_type&;
        using pointer = const val_type*;

        ConstLnrIterator() = default;
        ConstLnrIterator(const ConstLnrIterator<Key, Value, Compare>&) = default;
        ConstLnrIterator<Key, Value, Compare>& operator=(const ConstLnrIterator<Key, Value, Compare>&) = default;
        ~ConstLnrIterator() = default;

        ConstLnrIterator<Key, Value, Compare>& operator++()
        {
            auto node = stack_.top();
            if (node->right_)
            {
                node = node->right_;
                stack_.push(node);
                while (node->left_)
                {
                    node = node->left_;
                    stack_.push(node);
                }
            }
            else
            {
                stack_.pop();
                auto parent = stack_.top();
                while (parent && parent->right_ == node)
                {
                    node = parent;
                    stack_.pop();
                    parent = stack_.top();
                }
            }
            return *this;
        }

        ConstLnrIterator<Key, Value, Compare>& operator--()
        {
            auto node = stack_.top();
            if (node->left_)
            {
                node = node->left_;
                stack_.push(node);
                while (node->right_)
                {
                    node = node->right_;
                    stack_.push(node);
                }
            }
            else
            {
                stack_.pop();
                auto parent = stack_.top();
                while (parent && parent->left_ == node)
                {
                    node = parent;
                    stack_.pop();
                    parent = stack_.top();
                }
            }
            return *this;
        }

        ConstLnrIterator<Key, Value, Compare> operator++(int)
        {
            ConstLnrIterator<Key, Value, Compare> temp(*this);
            ++(*this);
            return temp;
        }

        ConstLnrIterator<Key, Value, Compare> operator--(int)
        {
            ConstLnrIterator<Key, Value, Compare> temp(*this);
            --(*this);
            return temp;
        }

        bool operator==(const ConstLnrIterator<Key, Value, Compare>& other) const
        {
            return stack_ == other.stack_;
        }

        bool operator!=(const ConstLnrIterator<Key, Value, Compare>& other) const
        {
            return !(*this == other);
        }

        pointer operator->() const
        {
            return std::addressof(stack_.top()->value);
        }

        reference operator*() const
        {
            return stack_.top()->value;
        }

    private:
        Stack<detail::TreeNode<Key, Value>*> stack_;
        
        ConstLnrIterator(detail::TreeNode<Key, Value>* root, detail::TreeNode<Key, Value>* node, bool isEnd)
        {
            Compare cmp;
            if (isEnd)
            {
                while (root)
                {
                    stack_.push(root);
                    root = root->right_;
                }
            }
            else
            {
                while (root)
                {
                    if (cmp(root->value.first, node->value.first))
                    {
                        stack_.push(root);
                        root = root->right_;
                    }
                    else
                    {
                        if (!cmp(node->value.first, root->value.first))
                        {
                            stack_.push(root);
                            break;
                        }
                        stack_.push(root);
                        root = root->left_;
                    }
                }
            }
        }
    };

    template<typename Key, typename Value, typename Compare = std::less<Key>>
    class ConstRnlIterator : public std::iterator<std::bidirectional_iterator_tag, std::pair<Key, Value>>
    {
        using val_type = std::pair<Key, Value>;
        friend class Tree<Key, Value, Compare>;
        friend class ConstTreeIterator<Key, Value, Compare>;

    public:
        ConstRnlIterator() = default;
        ConstRnlIterator(const ConstRnlIterator<Key, Value, Compare>&) = default;
        ConstRnlIterator<Key, Value, Compare>& operator=(const ConstRnlIterator<Key, Value, Compare>&) = default;
        ~ConstRnlIterator() = default;

        ConstRnlIterator<Key, Value, Compare>& operator--()
        {
            ++iterator_;
            return *this;
        }

        ConstRnlIterator<Key, Value, Compare>& operator++()
        {
            --iterator_;
            return *this;
        }

        ConstRnlIterator<Key, Value, Compare> operator++(int)
        {
            ConstRnlIterator<Key, Value, Compare> temp(*this);
            ++(*this);
            return temp;
        }

        ConstRnlIterator<Key, Value, Compare> operator--(int)
        {
            ConstRnlIterator<Key, Value, Compare> temp(*this);
            --(*this);
            return temp;
        }

        bool operator==(const ConstRnlIterator<Key, Value, Compare>& other) const
        {
            return iterator_ == other.iterator_;
        }

        bool operator!=(const ConstRnlIterator<Key, Value, Compare>& other) const
        {
            return !(iterator_ == other.iterator_);
        }

        const val_type* operator->() const
        {
            return std::addressof(iterator_.stack_.top()->value);
        }

        const val_type& operator*() const
        {
            return iterator_.stack_.top()->value;
        }

    private:
        ConstLnrIterator<Key, Value, Compare> iterator_;

        ConstRnlIterator(detail::TreeNode<Key, Value>* root, detail::TreeNode<Key, Value>* node, bool isStart)
        {
            Compare cmp;
            if (isStart)
            {
                while (root)
                {
                    iterator_.stack_.push(root);
                    root = root->left_;
                }
            }
            else
            {
                while (root)
                {
                    if (cmp(root->value.first, node->value.first))
                    {
                        iterator_.stack_.push(root);
                        root = root->right_;
                    }
                    else
                    {
                        if (!cmp(node->value.first, root->value.first))
                        {
                            iterator_.stack_.push(root);
                            break;
                        }
                        iterator_.stack_.push(root);
                        root = root->left_;
                    }
                }
            }
        }
    };

    template<typename Key, typename Value, typename Compare = std::less<Key>>
    class ConstBreadthIterator : public std::iterator<std::bidirectional_iterator_tag, std::pair<Key, Value>>
    {
        using val_type = std::pair<Key, Value>;
        friend class Tree<Key, Value, Compare>;
        friend class ConstTreeIterator<Key, Value, Compare>;

    public:
        ConstBreadthIterator() = default;
        ConstBreadthIterator(const ConstBreadthIterator<Key, Value, Compare>&) = default;
        ConstBreadthIterator<Key, Value, Compare>& operator=(const ConstBreadthIterator<Key, Value, Compare>&) = default;
        ~ConstBreadthIterator() = default;

        ConstBreadthIterator<Key, Value, Compare>& operator++()
        {
            if (queue_.empty())
            {
                stack_.push(nullptr);
                return *this;
            }
            auto node = queue_.front();
            queue_.pop();
            stack_.push(node);
            if (node->left_)
            {
                queue_.push(node->left_);
            }
            if (node->right_)
            {
                queue_.push(node->right_);
            }
            return *this;
        }

        ConstBreadthIterator<Key, Value, Compare>& operator--()
        {
            auto node = stack_.top();
            stack_.pop();
            queue_.push(node);
            return *this;
        }

        ConstBreadthIterator<Key, Value, Compare> operator++(int)
        {
            ConstBreadthIterator<Key, Value, Compare> temp(*this);
            ++(*this);
            return temp;
        }

        ConstBreadthIterator<Key, Value, Compare> operator--(int)
        {
            ConstBreadthIterator<Key, Value, Compare> temp(*this);
            --(*this);
            return temp;
        }

        bool operator==(const ConstBreadthIterator<Key, Value, Compare>& other) const
        {
            return stack_ == other.stack_;
        }

        bool operator!=(const ConstBreadthIterator<Key, Value, Compare>& other) const
        {
            return !(*this == other);
        }

        const val_type* operator->() const
        {
            return std::addressof(stack_.top()->value);
        }

        const val_type& operator*() const
        {
            return stack

#endif
