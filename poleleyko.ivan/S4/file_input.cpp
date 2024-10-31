#include "file_input.hpp"

void poleleyko::loadData(std::istream& input_stream, data_map_t& data_map) {
    std::string dataset_name;

    while (input_stream >> dataset_name) {
        long long key;
        std::string value;
        tree_structure tree;

        while (input_stream >> key >> value) {
            if (input_stream.fail()) {
                input_stream.clear();
                break;
            }
            tree.insert({key, value});
        }
        data_map.insert({dataset_name, tree});
    }
}
