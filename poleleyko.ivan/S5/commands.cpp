#include "commands.hpp"

void poleleyko::ascendTraversal(std::ostream& outputStream, const Tree<int, std::string>& tree, KeySummer& keySummer)
{
    tree.traverseInOrder(keySummer);
    outputStream << keySummer.getKeySum() << keySummer.getValueString();
}

void poleleyko::descendTraversal(std::ostream& outputStream, const Tree<int, std::string>& tree, KeySummer& keySummer)
{
    tree.traverseReverseInOrder(keySummer);
    outputStream << keySummer.getKeySum() << keySummer.getValueString();
}

void poleleyko::breadthTraversal(std::ostream& outputStream, const Tree<int, std::string>& tree, KeySummer& keySummer)
{
    tree.traverseBreadthFirst(keySummer);
    outputStream << keySummer.getKeySum() << keySummer.getValueString();
}
