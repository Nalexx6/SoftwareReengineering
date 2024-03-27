//
// Created by Mykyta Oleksiienko on 26.03.2024.
//

#include "Commands.h"


ProductsService Commands::productsService = ProductsService();

void Commands::create_new_product() {

    cout << "Enter name\n";
    string Name_1;
    cin >> Name_1;

    cout << "Enter unit of measure (Press: k - kilos, l - litres , b - bunches,  p - pieces) \n";
    string Unit_1;
    char k;
    cin>>k;
    switch (k)  {
        case 'k' : Unit_1 = "kilos";
            break;
        case 'l' : Unit_1 = "litres";
            break;
        case 'b' : Unit_1 = "bunches";
            break;
        case 'p' : Unit_1 = "pieces";
            break;
        default: Unit_1 = "unknown";
    }


    cout << "Enter quantity\n";
    int Quantity_1;
    cin >> Quantity_1;

    cout<< "Press 0 if you want to use default date(defined by ctime), or 1 if you want to enter your own date\n";
    int key,Day, Month, Year, Hours, Mins, Seconds;
    cin>>key;

    time_t t;
    time(&t);
    tm *time = localtime(&t);
    if( key == 0) {
        Day = time->tm_mday;
        Month = time->tm_mon + 1;
        Year = time->tm_year + 1900;
    }
    else {
        cout<<"Enter date: day (1-31), month(1-12), year(2020-2029)\n";
        cin>>Day>>Month>>Year;
    }

    Hours = time->tm_hour;
    Mins = time->tm_min;
    Seconds = time->tm_sec;
    cout << "Date of production is " << asctime(time);
    cout << "Enter expiry period(days) \n";
    int Expiry_period_1;
    cin >> Expiry_period_1;


    auto *product = new Product (Product::getProductCounter(), Name_1, Unit_1, Quantity_1,
                                 Day, Month, Year, Hours, Mins, Seconds, Expiry_period_1, false);

    productsService.create_new_product(product);

}

void Commands::save_all_products_from_memory_to_file() {
    productsService.save_all_products_from_memory_to_file("store");
}

void Commands::print_all_data_from_file() {
    productsService.print_all_data_from_vector("store");
}

void Commands::print_all_data_from_binary_file() {
    productsService.print_all_data_from_file();
}

void Commands::print_all_data_from_vector() {
    productsService.print_all_data_from_binary_file();
}

void Commands::load_all_products_from_file() {
    productsService.load_all_products_from_file("store");
}

void Commands::load_all_products_from_binary_file() {
    productsService.load_all_products_from_binary_file("store");
}

void Commands::create_N_random_products_and_append_them_to_memory() {
    cout << "Enter N - quantity of random products\n";
    int N;
    cin >> N;
    productsService.create_N_random_products_and_append_them_to_memory(N);
}

void Commands::delete_all_products_from_files() {
    productsService.delete_all_products_from_files();
}

void Commands::delete_all_products_from_memory() {
    productsService.delete_all_products_from_memory();
}

void Commands::delete_certain_product() {
    char key_1 = 'y';

    productsService.load_all_products_from_file("delete");
    cout<<"Choose where you want to find element to delete: m - memory, f - file\n";
    char ch;
    cin>>ch;
    if(ch == 'f')
        productsService.print_all_data_from_vector("delete");
    if(ch == 'm')
        productsService.print_all_data_from_vector("store");

    while (key_1 == 'y') {
        cout << "Choose the product which you want to delete(enter idV of it)\n";
        int id_1;
        cin >> id_1;
        productsService.delete_certain_product(ch, id_1);
        cout << "Press y if you want to continue deleting, n - if you don`t\n";
        char k;
        cin >> k;
        key_1 = k;
    }

    productsService.save_changes_to_files();

}

void Commands::update_certain_product() {
    productsService.load_all_products_from_file("update");
    cout << "Choose where you want to find element to delete: m - memory, f - file\n";
    char ch;
    cin >> ch;
    if (ch == 'f')
        productsService.print_all_data_from_vector("update");
    if (ch == 'm')
        productsService.print_all_data_from_vector("store");

    char key_1 = 'y';

    while (key_1 == 'y') {

        cout << "Please enter the idV of product which you want to update\n";
        int id_1;
        cin >> id_1;
        productsService.update_certain_product(ch, id_1);
        cout << "Press y if you want to update another element, or n if you don`t\n";
        char k;
        cin >> k;
        key_1 = k;
    }

    productsService.save_changes_to_files();
}

void Commands::update_for_demo(char &source, int &idv, string &name, string &unit, int &quantity,
                                      int &day, int &month, int &year, int &exp_per) {

    productsService.update_for_demo(source, idv, name, unit, quantity,
                    day, month, year, exp_per);
}

void Commands::search_interactive() {

    productsService.load_all_products_from_file("search");
    productsService.print_all_data_from_vector("search");

    char response = 'y';
    char key;

    while(response == 'y') {

        cout<< "Please choose parameter (n - name, q - quantity, d - date of production)\n";

        cin>>key;
        if(key == 'n') {
            string name;
            cout << "Please enter the filter - beginning of name of products wanted to be found\n";
            cin >> name;
            productsService.search_by_name(name);
        }
        if(key == 'q') {
            char unit;
            cout << "Please enter the first filter - unit of measure of products wanted to be found\n"
                    "(k - kilos, l - litres, b - bunches, p - pieces)\n";
            cin >> unit;
            int top, bottom;
            cout
                    << "Please enter the second filter - bottom and upper bound of quantity of products wanted to be found\n";
            cin >> bottom >> top;
            productsService.search_by_quantity(unit, bottom, top);
        }
        if(key == 'd'){
            int day, month, year;
            cout<<"Please enter date: day (1-31), month(1-12), year(2020-2029)\n";
            cin>>day>>month>>year;
            productsService.search_by_date(day, month, year);
        }

        cout<<"Do you want to continue searching? (Press y to continue, or n to reset filters)\n";
        char k;
        cin>>k;
        response = k;
    }

    productsService.clear_search_memory();

}


void Commands::search_for_demo(string &name, char &unit, int &bottom, int &top, int &day, int &month, int &year) {

    productsService.load_all_products_from_file("search");
    productsService.print_all_data_from_vector("search");

    string cont;
    productsService.search_by_name(name);
    cout<<"cin anything to continue\n";
    cin>>cont;
    productsService.search_by_quantity(unit, bottom, top);
    cout<<"cin anything to continue\n";
    cin>>cont;
    productsService.search_by_date(day, month, year);
    cout<<"cin anything to continue\n";
    cin>>cont;

    productsService.clear_search_memory();
}


void Commands::search_by_name_for_bm(string &name) {
    productsService.search_by_name_only(name);
}

void Commands::search_by_quantity_for_bm(char &unit, int &bottom, int &top) {
    productsService.search_by_quantity_only(unit, bottom, top);
}

void Commands::search_by_date_for_bm(int &day, int &month, int &year) {
    productsService.search_by_date_only(day, month, year);
}

void Commands::sort_interactive() {
    productsService.sort_interactive();
}

void Commands::sort_demo(string &key_1 , string& key_2) {
    productsService.sort_demo(key_1, key_2);

}

clock_t Commands::sort_benchmark(string &key) {
    return productsService.sort_benchmark(key);
}