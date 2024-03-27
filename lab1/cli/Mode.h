//
// Created by Win10Pro on 04.02.2020.
//

#ifndef LAB_1_DATA_BASE_IN_FILES__MODE_H
#define LAB_1_DATA_BASE_IN_FILES__MODE_H

#include "commands/Commands.h"
#include "../db/service/ProductsService.h"

class Mode {

private:

    unordered_map <int, function<void()>> commands_mapping = {
            {1, Commands::create_new_product},
            {2, Commands::save_all_products_from_memory_to_file},
            {3, Commands::print_all_data_from_vector},
            {4, Commands::print_all_data_from_file},
            {5, Commands::print_all_data_from_binary_file},
            {6, Commands::load_all_products_from_file},
            {7, Commands::load_all_products_from_binary_file},
            {8, Commands::create_N_random_products_and_append_them_to_memory},
            {9, Commands::delete_all_products_from_memory},
            {10, Commands::delete_all_products_from_files},
            {11, Commands::delete_certain_product},
            {12, Commands::update_certain_product},
            {13, Commands::search_interactive},
            {14, Commands::sort_interactive},
    };

public:
    //Modes

    void interactive();
    void demo();
    void benchmark();


};


#endif //LAB_1_DATA_BASE_IN_FILES__MODE_H
