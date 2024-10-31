#ifndef INPUT_FILE_HANDLER_HPP
#define INPUT_FILE_HANDLER_HPP

#include <istream>
#include <binary_tree.hpp>

namespace poleleyko
{
    using BinaryTree = Tree<int, std::string>;
    using StringTreeMap = Tree<std::string, BinaryTree>;

    void readInput(std::istream& inputStream, StringTreeMap& stringMap);
}

#endif
