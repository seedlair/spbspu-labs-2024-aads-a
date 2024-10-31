#ifndef FILE_INPUT_HPP
#define FILE_INPUT_HPP

#include <istream>
#include <tree_structure.hpp>

namespace poleleyko {
    using tree_structure = Tree<int, std::string>;
    using data_map_t = Tree<std::string, tree_structure>;
    
    void loadData(std::istream& input_stream, data_map_t& data_map);
}

#endif
