#ifndef COMMAND_EXECUTOR_HPP
#define COMMAND_EXECUTOR_HPP

#include <ostream>
#include <tree_structure.hpp>

namespace poleleyko {
    using tree_structure = Tree<int, std::string>;
    using data_map_t = Tree<std::string, tree_structure>;

    void display(std::ostream& output, const std::string& dataset_name, const data_map_t& data_map);
    void createComplement(data_map_t& data_map, const std::string& new_dataset_name, const std::string& left_name, const std::string& right_name);
    void createUnion(data_map_t& data_map, const std::string& new_dataset_name, const std::string& left_name, const std::string& right_name);
    void createIntersection(data_map_t& data_map, const std::string& new_dataset_name, const std::string& left_name, const std::string& right_name);
}

#endif
