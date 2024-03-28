//
// Created by Mykyta Oleksiienko on 26.03.2024.
//

#include "Commands.h"


ProductsService Commands::productsService = ProductsService();

Commands::Commands() {

}

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
        Product product = productsService.select_product_for_update(ch, id_1);

        productsService.update_certain_product(ch, id_1, update_selected_product(product));
        cout << "Press y if you want to update another element, or n if you don`t\n";
        char k;
        cin >> k;
        key_1 = k;
    }

    productsService.save_changes_to_files();
}

Product Commands::update_selected_product(Product &product) {
    char key_1;
    string new_par;
    int new_p, day, month, year;
    cout << "Please enter parameter which you want to update:\n"
            "n - name, u - unit, q - quantity, d - date, e - expiry period\n";
    cin >> key_1;

    switch (key_1) {
        case 'n' :
            cout << "Enter new name:\n";
            cin >> new_par;
            product.setName(new_par);
            break;
        case 'u' :
            cout << "Enter new unit of measure "
                    "(Press: k - kilos, l - litres , b - bunches,  p - pieces) \n";
            char k;
            cin >> k;
            switch (k) {
                case 'k' :
                    new_par = "kilos";
                    break;
                case 'l' :
                    new_par = "litres";
                    break;
                case 'b' :
                    new_par = "bunches";
                    break;
                case 'p' :
                    new_par = "pieces";
                    break;
                default: new_par = "unknown";

            }
            product.setUnit(new_par);
            break;
        case 'q' :
            cout << "Enter new quantity\n";
            cin >> new_p;
            product.setQuantity(new_p);
            break;
        case 'd' :
            cout << "Enter date: day (1-31), month(1-12), year(2020-2029)\n";
            cin >> day >> month >> year;
            product.setDay(day);
            product.setMonth(month);
            product.setYear(year);
            break;
        case 'e' :
            cout << "Enter new expiry period(days)\n";
            cin >> new_p;
            product.setExpiryPeriod(new_p);
            break;
        default:
            break;
    }

    return product;
}

void Commands::update_for_demo(char &source, int &idv, string &name, string &unit, int &quantity,
                                      int &day, int &month, int &year, int &exp_per) {

    productsService.load_all_products_from_file("update");
    productsService.print_all_data_from_vector("update");
    Product product = productsService.select_product_for_update(source, idv);
    
    product.setName(name);
    product.setUnit(unit);
    product.setQuantity(quantity);
    product.setDay(day);
    product.setMonth(month);
    product.setYear(year);
    product.setExpiryPeriod(exp_per);

    productsService.update_certain_product(source, idv, product);
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

void Commands::sort_interactive() {
    string combination;
    productsService.prepare_search_memory();

    char response = 'y';
    while (response == 'y') {
        cout << "Please enter the combination of parameters by which you want to sort\n"
                "(enter your parameters without SPACE, and when you finish press ENTER)\n"
                "keys: n - name, u - unit, q - quantity, d - date, e - expiry period\n";
        cin >> combination;
        productsService.sort_by_combination(combination);
        cout<<"This is result of sorting\n";
        productsService.print_all_data_from_vector("sort");
        cout<<"If you want to sort by another key, press 'y', press 'n' if you don`t\n";
        cin>>response;
    }
    productsService.clear_search_memory();
}

void Commands::sort_demo(string &key_1 , string& key_2) {
    string breakpoint;
    productsService.prepare_search_memory();

    cout<<"Now we will sort our elements by key: "<<key_1<<"\n"
                                                           "cin any to continue\n";
    cin>>breakpoint;
    productsService.sort_by_combination(key_1);
    productsService.print_all_data_from_vector("sort");
    cout<<"As we can see our memory is sorted by our key\n"
          "cin any to continue\n";
    cin>>breakpoint;
    cout<<"Now we will sort our elements by combination of keys: "<<key_2<<"\n"
                                                                           "cin any to continue\n";
    cin>>breakpoint;
    productsService.sort_by_combination(key_2);
    productsService.print_all_data_from_vector("sort");
    cout<<"As we can see our memory is sorted by our combination\n"
          "cin any to continue\n";
    cin>>breakpoint;

    productsService.clear_search_memory();
}

clock_t Commands::sort_benchmark(string &key) {
    productsService.prepare_search_memory();
    clock_t start = clock();
    productsService.sort_by_combination(key);
    clock_t end = clock();
    productsService.clear_search_memory();
    cout<<"Memory was sorted by key: "<<key<<"\n";
    return end - start;
}
