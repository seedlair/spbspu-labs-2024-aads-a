#ifndef COMMANDS_HANDLER_HPP
#define COMMANDS_HANDLER_HPP

#include <ostream>
#include <binary_tree.hpp>
#include "key_summer.hpp"

namespace poleleyko
{
    void ascendTraversal(std::ostream& outputStream, const Tree<int, std::string>& tree, KeySummer& keySummer);
    void descendTraversal(std::ostream& outputStream, const Tree<int, std::string>& tree, KeySummer& keySummer);
    void breadthTraversal(std::ostream& outputStream, const Tree<int, std::string>& tree, KeySummer& keySummer);
}

#endif
