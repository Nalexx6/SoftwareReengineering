//
// Created by Win10Pro on 26.01.2020.
//

#ifndef LAB_1_DATA_BASE_IN_FILES__PRODUCTSSERVICE_H
#define LAB_1_DATA_BASE_IN_FILES__PRODUCTSSERVICE_H

#include "../models/Product.h"
//3b Lab
#include "../../utils/Sorts.h"

class ProductsService {

private:

    unordered_map <char, string> units_mapping = {
            {'k', "kilos"},
            {'l', "litres"},
            {'b', "bunches"},
            {'p', "pieces"},
    };

    vector<Product> getVector(const string &op);

    //Memory
    vector <Product> store = {};
    vector <Product> searched_1 = {};
    vector <Product> for_delete_update = {};
    //3b lab (sort)
    vector <Product> for_sort = {};

public:

    ProductsService();



    void create_new_product(Product *product);
    void save_all_products_from_memory_to_file(const string& op);
    void print_all_data_from_file();
    void print_all_data_from_binary_file();
    void print_all_data_from_vector(const string& op);
    void load_all_products_from_file(const string& op);
    void load_all_products_from_binary_file(const string& op);
    void create_N_random_products_and_append_them_to_memory(int &N);

    void delete_all_products_from_files();
    void delete_all_products_from_memory();
    void delete_certain_product(char &source, int &idV);

    void update_certain_product_from_memory(char &source, const string& op, int &idv);
    void update_certain_product(char &source, int &idv);
    void update_for_demo(char &source, int &idv, string &name, string &unit, int &quantity,
                                int &day, int &month, int &year, int &exp_per);

    void save_changes_to_files();

    void search_by_name(string &name);
    void search_by_quantity(char &unit, int &bottom, int &top);
    void search_by_date(int &day, int &month, int &year);
    void clear_search_memory();

    //faster search, which does not consider multiple filters. Used for benchmark is not user-friendly
    void search_by_name_only(string& name);
    void search_by_quantity_only(char &unit, int &bottom, int &top);
    void search_by_date_only(int &day, int &month, int &year);

    int find_exact_pos_in_vector(vector <Product> &vector1, int &id);
    int bin_search(vector <Product> &vector1, int &id);

    void sort_interactive();
    void sort_demo(string& key_1, string& key_2);
    clock_t sort_benchmark(string& key);

};

/*Need to be fixed


 */


#endif //LAB_1_DATA_BASE_IN_FILES__PRODUCTSSERVICE_H
