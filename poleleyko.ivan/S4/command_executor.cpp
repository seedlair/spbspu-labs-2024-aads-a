#include "command_executor.hpp"
#include <iostream>

void poleleyko::display(std::ostream& output, const std::string& dataset_name, const data_map_t& data_map) {
    const tree_structure result = data_map.at(dataset_name);

    if (result.empty()) {
        output << "<EMPTY>";
    } else {
        output << dataset_name;
        for (const auto& [key, value] : result) {
            output << ' ' << key << ' ' << value;
        }
    }
    output << '\n';
}

void poleleyko::createComplement(data_map_t& data_map, const std::string& new_dataset_name, const std::string& left_name, const std::string& right_name) {
    const tree_structure right_tree = data_map.at(right_name);
    const tree_structure left_tree = data_map.at(left_name);
    auto right_it = right_tree.cbegin();
    tree_structure new_tree;

    for (const auto& [key, value] : left_tree) {
        if (right_it->first < key) {
            new_tree.insert({key, value});
            while (right_it != right_tree.cend() && right_it->first < key) {
                ++right_it;
            }
        } else if (right_it->first > key) {
            new_tree.insert({key, value});
        } else {
            ++right_it;
        }
    }

    data_map[new_dataset_name] = new_tree;
}

void poleleyko::createUnion(data_map_t& data_map, const std::string& new_dataset_name, const std::string& left_name, const std::string& right_name) {
    const tree_structure left_tree = data_map.at(left_name);
    const tree_structure right_tree = data_map.at(right_name);
    tree_structure new_tree = left_tree;

    for (const auto& [key, value] : right_tree) {
        new_tree.insert({key, value});
    }

    data_map[new_dataset_name] = new_tree;
}

void poleleyko::createIntersection(data_map_t& data_map, const std::string& new_dataset_name, const std::string& left_name, const std::string& right_name) {
    const tree_structure left_tree = data_map.at(left_name);
    const tree_structure right_tree = data_map.at(right_name);
    auto right_it = right_tree.cbegin();
    tree_structure new_tree;

    for (const auto& [key, value] : left_tree) {
        if (right_it->first == key) {
            new_tree.insert({key, value});
            ++right_it;
        } else if (right_it->first < key) {
            while (right_it != right_tree.cend() && right_it->first < key) {
                ++right_it;
            }
        }
    }

    data_map[new_dataset_name] = new_tree;
}
