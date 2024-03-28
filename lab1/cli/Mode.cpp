//
// Created by Win10Pro on 04.02.2020.
//

#include "Commands.h"

void Commands::interactive() {

    char response = 'y';

    while(response == 'y') {

        short key;
        cout << "Please choose the mode\n"
                "1 - create new product and append it to the memory\n"
                "2 - save all products from memory to txt file and binary file\n"
                "3 - print all data from memory\n"
                "4 - print all data from txt file\n"
                "5 - print all data from binary file\n"
                "6 - load all data from txt file to memory\n"
                "7 - load all data from binary file to memory\n"
                "8 - create N random products and append them to the memory\n"
                "9 - delete all data from the memory\n"
                "10 - delete all products from the files\n"
                "11 - delete certain product\n"
                "12 - update certain product\n"
                "13 - search which provided for all products (in memory and files) simultaneously by 3 filters:\n"
                "beginning of name, range of quantity in exact unit, date of production no later than determined\n"
                "14 - sort products by any parameter in non-decreasing order\n";

        cin >> key;
        this->commands_mapping[key]();
        cout << "Do you want to continue? Press y or n\n";
        cin >> response;
    }

}

void Commands::demo() {

    /*create random - save to files - print all from files - save to show no duplicates -
     * delete all from memory - print -load from txt - print - delete all from memory - load from bin - print
     * - load to show no duplicates -delete all from files - save all - delete certain(f&m) - print(x2)
     * - update certain(f&m) - print(x2) - search
     */

     ifstream f("../files/Demo default parameters.txt");
     int N, del_1, del_2, idv_1,  quant_1, day_1, month_1, year_1, exp_per_1,
             idv_2,  quant_2, day_2, month_2, year_2, exp_per_2, search_b, search_t, search_d, search_m, search_y;
     string name_1, unit_1, name_2, unit_2, search_n, sort_key_1, sort_key_2;
     char source_d_1, source_d_2, source_u_1, source_u_2, search_u;

     f >> N >> source_d_1 >> del_1 >> source_d_2 >> del_2 >>
                source_u_1 >> idv_1 >> name_1 >> unit_1 >> quant_1 >> day_1 >> month_1 >> year_1 >> exp_per_1 >>
                source_u_2 >> idv_2 >> name_2 >> unit_2 >> quant_2 >> day_2 >> month_2 >> year_2 >> exp_per_2>>
                search_n >> search_u >> search_b >> search_t >> search_d >> search_m >> search_y >>
                sort_key_1 >> sort_key_2;

    Commands::productsService.delete_all_products_from_files();

    string cont;
    cout<<"Firstly we will create "<< N <<" random elements, "
                                          "cin anything to continue\n";
    cin>>cont;
    Commands::productsService.create_N_random_products_and_append_them_to_memory(N);

    cout<<"Now we will save all this products from memory to txt file and binary file, "
          "cin anything to continue\n";
    cin>>cont;
    Commands::productsService.save_all_products_from_memory_to_file("store");
    cout<<"Now we will print all data from txt and binary file to be sure that save function is correct, "
          "cin anything to continue\n ";
    cin>>cont;
    Commands::productsService.print_all_data_from_file();
    Commands::productsService.print_all_data_from_binary_file();
    cout<<"As we can see data in all files is identical, now we delete all data from memory, "
          "cin anything to continue\n";
    cin>>cont;
    Commands::productsService.delete_all_products_from_memory();
    Commands::productsService.print_all_data_from_vector("store");
    cout<<"Now we will load all data from files to memory, firstly from txt, then from binary,"
          "cin anything to continue\n";
    cin>>cont;
    Commands::productsService.load_all_products_from_file("store");
    Commands::productsService.print_all_data_from_vector("store");
    cout<<"This is data from txt file, now we will clear memory and load data from binary, "
          "cin anything to continue\n";
    cin>>cont;
    Commands::productsService.delete_all_products_from_memory();
    Commands::productsService.load_all_products_from_binary_file("store");
    Commands::productsService.print_all_data_from_vector("store");
    cout<<"As we can see data is identical, now we will repeatedly load data from txt to "
          "show that we won`t have duplicates in memory, "
          "cin anything to continue\n";
    cin>>cont;
    Commands::productsService.load_all_products_from_file("store");
    Commands::productsService.print_all_data_from_vector("store");
    cout<<"Now we will do the same test but with files "
          "cin anything to continue\n";
    cin>>cont;
    Commands::productsService.save_all_products_from_memory_to_file("store");
    Commands::productsService.print_all_data_from_file();
    cout<<"Now we will delete all data from file and save all from memory again,"
          "cin anything to continue\n";
    cin>>cont;
    Commands::productsService.delete_all_products_from_files();
    Commands::productsService.print_all_data_from_file();
    cout<<"As we can see file is empty,"
          "cin anything to continue\n";
    cin>>cont;
    Commands::productsService.save_all_products_from_memory_to_file("store");
    Commands::productsService.print_all_data_from_file();
    cout<<"As we can see all data is again accessible in file, "
          "now we will delete certain products, "
          "firstly from memory then from file to show that they both are working correctly, "
          "cin anything to continue\n";
    cin>>cont;
    Commands::productsService.load_all_products_from_file("delete");
    Commands::productsService.print_all_data_from_vector("store");
    cout<<"Now we will delete element from memory that has idv = "<< del_1 <<
          " cin anything to continue\n";
    cin>>cont;
    Commands::productsService.delete_certain_product(source_d_1, del_1);
    Commands::productsService.save_changes_to_files();
    cout<<"Printing all data..\n";
    Commands::productsService.print_all_data_from_file();
    Commands::productsService.print_all_data_from_vector("store");
    cout<<"As we can see element disappeared from memory and files,"
          "now we will do the same but we will find element for deleting in file, "
          "cin anything to continue\n";
    cin>>cont;

    Commands::productsService.load_all_products_from_file("delete");
    Commands::productsService.print_all_data_from_vector("delete");
    cout<<"Now we will delete element from file that has idv = "<< del_2 <<
        " cin anything to continue\n";
    cin>>cont;
    Commands::productsService.delete_certain_product(source_d_2, del_2);
    Commands::productsService.save_changes_to_files();
    cout<<"Printing all data..\n";
    Commands::productsService.print_all_data_from_file();
    Commands::productsService.print_all_data_from_vector("store");
    cout<<"As we can see element disappeared from memory and files,"
          "now we will update certain products, "
          "firstly from memory then from file to show that they both are working correctly, "
          "cin anything to continue\n";
    cin>>cont;
    Commands::productsService.load_all_products_from_file("update");
    Commands::productsService.print_all_data_from_vector("store");
    cout<<"Now we will update element from memory that has idv = "<< idv_1 <<
        " cin anything to continue\n";
    cin>>cont;
    Commands::update_for_demo(source_u_1, idv_1, name_1, unit_1, quant_1,
            day_1, month_1, year_1, exp_per_1);
    Commands::productsService.save_changes_to_files();
    cout<<"Printing data...\n";
    Commands::productsService.print_all_data_from_file();
    Commands::productsService.print_all_data_from_vector("store");
    cout<<"As we can see element updated both in memory and files,"
          "now we will do the same but we will find element for updating in file, "
          "cin anything to continue\n";
    cin>>cont;
    Commands::productsService.load_all_products_from_file("update");
    Commands::productsService.print_all_data_from_vector("update");
    cout<<"Now we will update element from file that has idv = "<< idv_2 <<
        " cin anything to continue\n";
    cin>>cont;
    Commands::update_for_demo(source_u_2, idv_2, name_2, unit_2, quant_2,
                             day_2, month_2, year_2, exp_per_2);
    Commands::productsService.save_changes_to_files();
    cout<<"Printing data...\n";
    Commands::productsService.print_all_data_from_file();
    Commands::productsService.print_all_data_from_vector("store");
    cout<<"As we can see element updated both in memory and files,"
              "now we will do the search , by turns in 3 filters: \n"
              "beginning of name, range of quantity in exact unit, date of production no later than determined, "
              "cin anything to continue\n";
    cin>>cont;
    Commands::search_for_demo(search_n, search_u, search_b, search_t,
            search_d, search_m, search_y);

    Commands::sort_demo(sort_key_1, sort_key_2);

    cout<<"This is the end of demo mode\n";





}

void Commands::benchmark() {

    ifstream f("../files/Benchmark default parameters.txt");
    string name, count_sort_key, radix_sort_key, sort_key_1, sort_key_2;
    char unit;
    int top, bottom, day, month, year;
    f >> name >> unit >> bottom >> top >> day >> month >> year >>
    count_sort_key >> radix_sort_key >> sort_key_1 >> sort_key_2;
    f.close();
    //N = 400000 is 10 seconds time

    ofstream f_b("../files/Benchmark data.txt");

    for(int N = 4; N <= 400000; N*=10) {

        f_b<<"Amount of products = "<< N<<'\n';

        clock_t start = clock();
        Commands::productsService.delete_all_products_from_files();
        clock_t end = clock();
        f_b << "Clearing files: "<< (end - start)<<" ms\n";

        clock_t start_1 = clock();
        Commands::productsService.delete_all_products_from_memory();
        clock_t end_1 = clock();
        f_b << "Clearing memory: "<< (end_1 - start_1)<<" ms\n";


        start_1 = clock();
        Commands::productsService.create_N_random_products_and_append_them_to_memory(N);
        end_1 = clock();
        f_b << "Creating products: "<< (end_1 - start_1)<<" ms\n";

        start_1 = clock();
        Commands::productsService.save_all_products_from_memory_to_file("store");
        end_1 = clock();
        f_b << "Saving all products to files: "<< (end_1 - start_1)<<" ms\n";

        start_1 = clock();
        Commands::productsService.delete_all_products_from_memory();
        end_1 = clock();
        f_b << "Clearing memory: "<< (end_1 - start_1)<<" ms\n";

        start_1 = clock();
        Commands::productsService.load_all_products_from_file("store");
        end_1 = clock();
        f_b << "Loading all products from txt file: "<< (end_1 - start_1)<<" ms\n";

        start_1 = clock();
        Commands::productsService.delete_all_products_from_memory();
        end_1 = clock();
        f_b << "Clearing memory: "<< (end_1 - start_1)<<" ms\n";

        start_1 = clock();
        Commands::productsService.load_all_products_from_binary_file("store");
        end_1 = clock();
        f_b << "Loading all products from binary file: "<< (end_1 - start_1)<<" ms\n";

        start_1 = clock();
        Commands::productsService.search_by_name_only(name);
        end_1 = clock();
        Commands::productsService.clear_search_memory();
        f_b << "Searching by name: "<< (end_1 - start_1)<<" ms\n";

        start_1 = clock();
        Commands::productsService.search_by_quantity_only(unit, bottom, top);
        end_1 = clock();
        Commands::productsService.clear_search_memory();
        f_b << "Searching by unit and quantity: "<< (end_1 - start_1)<<" ms\n";

        start_1 = clock();
        Commands::productsService.search_by_date_only(day, month, year);
        end_1 = clock();
        Commands::productsService.clear_search_memory();
        f_b << "Searching by date of production: "<< (end_1 - start_1)<<" ms\n";

        f_b << "Counting sort by unit: "<< Commands::sort_benchmark(count_sort_key)<<" ms\n";

        f_b << "Radix sort by expiry period: "<< Commands::sort_benchmark(radix_sort_key)<<" ms\n";

        f_b << "Sort by one parameter: "<< Commands::sort_benchmark(sort_key_1)<<" ms\n";

        f_b << "Sort by combination of parameters: "<< Commands::sort_benchmark(sort_key_2)<<" ms\n";

        end = clock();
        f_b << "Time for 1 iteration: "<< (end - start)<<" ms\n";

        ifstream f_bin("../files/Products_bin.txt");
        f_bin.seekg(0, ios::end);
        int size_b = f_bin.tellg();
        f_b<<"Size of binary file in bytes: "<< size_b<<" bytes\n";
        f_bin.close();

        ifstream f_t("../files/Products.txt");
        f_t.seekg(0, ios::end);
        int size_t = f_t.tellg();
        f_b<<"Size of txt file in bytes: "<< size_t<<" bytes\n\n";
        f_t.close();

    }

    cout<<"\nResults of benchmark mode you can in file: ../files/Benchmark data.txt\n";
    f_b.close();

}
