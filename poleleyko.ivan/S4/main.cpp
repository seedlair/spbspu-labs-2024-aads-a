#include <iostream>
#include <fstream>
#include "file_input.hpp"
#include "command_executor.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect file input\n";
        return 1;
    }

    using namespace poleleyko;
    data_map_t data_map;
    std::ifstream file_stream(argv[1]);
    
    if (!file_stream.is_open()) {
        std::cerr << "Unable to open the file\n";
        return 2;
    }

    loadData(file_stream, data_map);

    Tree<std::string, std::function<void(std::ostream&, const std::string&, const data_map_t&)>> output_commands;
    output_commands["print"] = display;
    
    Tree<std::string, std::function<void(data_map_t&, const std::string&, const std::string&, const std::string&)>> set_commands;
    set_commands["complement"] = createComplement;
    set_commands["union"] = createUnion;
    set_commands["intersect"] = createIntersection;

    std::string command_name, dataset_name;
    
    while (std::cin >> command_name) {
        std::cin >> dataset_name;

        try {
            output_commands.at(command_name)(std::cout, dataset_name, data_map);
        } catch (const std::out_of_range&) {
            try {
                std::string left_set, right_set;
                std::cin >> left_set >> right_set;
                set_commands.at(command_name)(data_map, dataset_name, left_set, right_set);
            } catch (const std::out_of_range&) {
                std::cout << "<INVALID COMMAND>\n";
            } catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
                return 1;
            }
        }
    }

    return 0;
}
