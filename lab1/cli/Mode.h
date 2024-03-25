//
// Created by Win10Pro on 04.02.2020.
//

#ifndef LAB_1_DATA_BASE_IN_FILES__MODE_H
#define LAB_1_DATA_BASE_IN_FILES__MODE_H

#include "../db/Functions.h"
class Mode {

private:
//
//    unordered_map <int, function<void()>> options_mapping = {
//            {1, Functions::create_new_product},
//            {2, Functions::save_all_products_from_memory_to_file},
//    };

public:

    //Modes

    static void interactive();
    static void demo();
    static void benchmark();


};


#endif //LAB_1_DATA_BASE_IN_FILES__MODE_H
