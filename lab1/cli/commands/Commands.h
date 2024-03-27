//
// Created by Mykyta Oleksiienko on 26.03.2024.
//

#ifndef LAB_1_DATA_BASE_IN_FILES__COMMANDS_H
#define LAB_1_DATA_BASE_IN_FILES__COMMANDS_H


#include "../../db/models/Product.h"
#include "../../db/service/ProductsService.h"
//3b Lab
#include "../../utils/Sorts.h"

class Commands {

private:

public:
    ProductsService static productsService;


    Commands();

    //data operations
    void static create_new_product();
    void static save_all_products_from_memory_to_file();
    void static print_all_data_from_file();
    void static print_all_data_from_binary_file();
    void static print_all_data_from_vector();
    void static load_all_products_from_file();
    void static load_all_products_from_binary_file();
    void static create_N_random_products_and_append_them_to_memory();
    void static delete_all_products_from_files();
    void static delete_all_products_from_memory();
    void static delete_certain_product();
    void static update_certain_product();
    void static generate_update_properties(char &source, int &idv);

    //interactive
    void static search_interactive();

    //demo
    void static search_for_demo(string &name, char &unit, int &bottom, int &top, int &day, int &month, int &year);
    void static update_for_demo(char &source, int &idv, string &name, string &unit, int &quantity,
                         int &day, int &month, int &year, int &exp_per);

    //benchmark
    void static search_by_name_for_bm(string &name);
    void static search_by_quantity_for_bm(char &unit, int &bottom, int &top);
    void static search_by_date_for_bm(int &day, int &month, int &year);

    //additional functionality with sorting in-memory data
    void static sort_interactive();
    void static sort_demo(string& key_1, string& key_2);
    clock_t static sort_benchmark(string& key);

};


#endif //LAB_1_DATA_BASE_IN_FILES__COMMANDS_H
