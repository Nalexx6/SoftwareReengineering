//
// Created by Win10Pro on 26.01.2020.
//

#include "ProductsService.h"


ProductsService::ProductsService() {
    Product::define_id();
}

vector<Product> ProductsService::getVector(const string &op){

    if (op == "store")
        return store;
    else if (op == "delete" || op == "update")
        return for_delete_update;
    else if (op == "search")
        return searched_1;
    else
        return for_sort;
}


void ProductsService::updateVector(const string &op, const vector<Product> &vector1){

    if (op == "store")
        store = vector1;
    else if (op == "delete" || op == "update")
        for_delete_update = vector1;
    else if (op == "search")
        searched_1 = vector1;
    else
        for_sort = vector1;
}

void ProductsService::create_new_product(Product *product) {
    store.push_back(*product);
}

void ProductsService::save_all_products_from_memory_to_file(const string& op) {

    vector<Product> vector1 = getVector(op);
    
    ofstream f_w("../files/Products.txt", ios::app);
    ofstream f_b("../files/Products_bin.txt", ios::binary | ios::app);
    ifstream f_r("../files/Products.txt");
    string line;
    bool empty_file = true;
    if(getline(f_r, line))
        empty_file = false;
    f_r.close();
    int k =0;
    for(auto & i : vector1){

        if( !i.isBeenSaved()) {

            i.save_to_file(f_w, empty_file);
            i.save_to_bin_file(f_b);
            empty_file = false;
            k++;

        }
    }

    cout << "All " << k << " unsaved products successfuly saved to files\n";

    f_w.close();
    f_b.close();
}

void ProductsService::print_all_data_from_file() {

    string line;
    ifstream f("../files/Products.txt");
    cout<<"id\tName\tUnit\tQuantity\tDate\tTime\tExpiry period\n";
    while (!f.eof()) {

        getline(f, line);
        cout << line << '\n';

    }

    f.close();

}

void ProductsService::print_all_data_from_vector(const string& op) {
    vector<Product> vector1 = getVector(op);

    cout<<"idV\tid\tName\tUnit\tQuantity\tDate\tTime\tExpiry period\n";

    for(unsigned int i = 0; i < vector1.size(); i++){

        cout<< i << '\t' << vector1[i].getId()  << "\t" << vector1[i].getName()  << "\t" << vector1[i].getUnit()  << "\t"
        << vector1[i].getQuantity()  << "\t" << vector1[i].getDay()  << "." << vector1[i].getMonth()  << "." << vector1[i].getYear()  << "\t" <<
        vector1[i].getHours()  << ":" << vector1[i].getMins()  << ":" << vector1[i].getSeconds()  << "\t"
            << vector1[i].getExpiryPeriod()  << "\n";

    }


}

void ProductsService::load_all_products_from_file(const string& op){
    vector<Product> vector1 = getVector(op);

    ifstream f("../files/Products.txt");
    string name, unit;
    int i = 0, id, quant, day, month, year, hours, mins, secs, exp_per;
    if(f.is_open()) {

        while (!f.eof() && Product::getProductCounter() > 0) {


            f >> id >> name >> unit >> quant >> day >> month >> year >> hours >> mins >> secs >> exp_per;

            if (find_exact_pos_in_vector(vector1, id) != -1) {
                i++;
                vector1.insert(vector1.begin() + find_exact_pos_in_vector(vector1, id),
                        Product(id, name, unit, quant, day, month, year, hours, mins, secs, exp_per, true));

            }
        }

    }

    updateVector(op, vector1);
    f.close();
    cout<< "All " << i << " unloaded products loaded to memory\n";

}

void ProductsService::load_all_products_from_binary_file(const string& op) {
    vector<Product> vector1 = getVector(op);

    ifstream f ("../files/Products_bin.txt", ios::binary);

    string name, unit;
    char ch;
    int i = 0, id, name_l, unit_l, quant, day, month, year, hours, mins, secs, exp_per, end_file;
    if(f.is_open()) {
        f.seekg(0, ios::end);
        end_file = f.tellg();
        f.seekg(0, ios::beg);
        while (f.tellg() != end_file) {
            f.read((char *) &id, sizeof(id));
            f.read((char *) &name_l, sizeof(name_l));
            for (int j = 0; j < name_l; j++) {

                f.get(ch);
                name += ch;

            }
            f.read((char *) &unit_l, sizeof(unit_l));
            for(int j = 0; j < unit_l; j++) {

                f.get(ch);
                unit += ch;

            }
            f.read((char *) &quant, sizeof(quant));
            f.read((char *) &day, sizeof(day));
            f.read((char *) &month, sizeof(month));
            f.read((char *) &year, sizeof(year));
            f.read((char *) &hours, sizeof(hours));
            f.read((char *) &mins, sizeof(mins));
            f.read((char *) &secs, sizeof(secs));
            f.read((char *) &exp_per, sizeof(exp_per));

            if (find_exact_pos_in_vector(vector1,id) != -1) {

                i++;
                vector1.insert(vector1.begin() + find_exact_pos_in_vector(vector1,id),Product(id, name, unit, quant,
                                           day, month, year, hours, mins, secs, exp_per, true));

            }

            name = "";
            unit = "";

        }
    }
    f.close();

    updateVector(op, vector1);

    cout<< "All " << i << " unloaded products loaded to memory\n";

}

void ProductsService::print_all_data_from_binary_file() {

    ifstream f ("../files/Products_bin.txt", ios::binary);

    string name, unit;
    char ch;
    int id, name_l, unit_l, quant, day, month, year, hours, mins, secs, exp_per, end_file;

    f.seekg(0, ios::end);
    end_file = f.tellg();
    f.seekg(0, ios::beg);
    cout<<"idV\tid\tName\tUnit\tQuantity\tDate\tTime\tExpiry period\n";
    while (f.tellg() != end_file) {
        f.read((char *) &id, sizeof(id));
        f.read((char *) &name_l, sizeof(name_l));
        for (int i = 0; i < name_l; i++) {

            f.get(ch);
            name += ch;

        }
        f.read((char *) &unit_l, sizeof(unit_l));
        for (int i = 0; i < unit_l; i++) {

            f.get(ch);
            unit += ch;

        }
        f.read((char *) &quant, sizeof(quant));
        f.read((char *) &day, sizeof(day));
        f.read((char *) &month, sizeof(month));
        f.read((char *) &year, sizeof(year));
        f.read((char *) &hours, sizeof(hours));
        f.read((char *) &mins, sizeof(mins));
        f.read((char *) &secs, sizeof(secs));
        f.read((char *) &exp_per, sizeof(exp_per));

        cout<< id << "\t" << name << "\t" << unit << "\t" << quant << "\t"
            << day << "." << month << "." << year << "\t" <<
            hours << ":" << mins << ":" << secs << "\t" << exp_per << "\n";

        name = "";
        unit = "";

    }

    f.close();

}

void ProductsService::create_N_random_products_and_append_them_to_memory(int &N) {

    int Id = 0;

    char alphabet[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    for(int i = 1; i <= N; i++){

        string Name;
        int length = rand() % 3 + 4;
        for(int i = 0; i < length; i++){

            Name += alphabet[rand() % 52];
        }

        string Unit_1;
        short key = rand() % 4;
        //cout<< key <<'\t';
        switch (key)  {
            case 0 : Unit_1 = units_mapping['k'];
                    break;
            case 1 : Unit_1 = units_mapping['l'];
                    break;
            case 2 : Unit_1 = units_mapping['b'];
                    break;
            case 3 : Unit_1 = units_mapping['p'];
                    break;
        }

        int Quantity = rand() % 51;

        time_t t;
        time (&t);
        tm* time = localtime(&t);
        int Day = rand() % 31 + 1;
        int Month = rand() % 12 + 1;
        int Year = rand() % 2 + 2019;
        int Hours = time->tm_hour;
        int Mins = time->tm_min;
        int Seconds = time->tm_sec;

        int Exp_per = rand() % 999 + 1;

        auto *product = new Product (Id, Name, Unit_1, Quantity,
                Day, Month, Year, Hours, Mins, Seconds, Exp_per, false);

        store.push_back(*product);

    }
    cout<<"\nAll " << N << " random products successfully created\n";
}

void ProductsService::delete_all_products_from_files() {

    ofstream f_1( "../files/Products_bin.txt", ofstream::trunc);
    f_1.close();

    ofstream f( "../files/Products.txt", ofstream::trunc);
    f.close();
    for(auto & i : store){

        i.setBeenSaved(false);
    }

}

void ProductsService::search_by_name(string &name) {

    for(int j = 0; j < searched_1.size(); j++){

            for(int k = 0; k < name.size(); k++) {

                if (searched_1[j].getName()[k] != name[k]) {
                    searched_1.erase(searched_1.begin() + j);
                    j--;
                    break;

                }
            }

        }


    cout<<"There are all products which names begin from: "<< name<< '\n';
    print_all_data_from_vector("search");

}

void ProductsService::search_by_name_only(string &name) {

    for(int j = 0; j < store.size(); j++){
        int i = 0;
        for(int k = 0; k < name.size(); k++) {
            if (store[j].getName()[k] != name[k]) {
                i++;
                break;
            }
        }
        if(i == 0)
            searched_1.push_back(store[j]);
    }

    cout<<"Number of products which names begin from: "<< name<<" is: "<<searched_1.size()<<'\n';
    searched_1.clear();

}

void ProductsService::search_by_quantity_only(char &unit, int &bottom, int &top) {
    string filter = units_mapping[unit];

    for(int i = 0; i < store.size(); i++){
        int j = 0;
        if(store[i].getUnit()[0] != filter[0] || store[i].getQuantity() > top || store[i].getQuantity() < bottom){

            j++;

        }
        if(j == 0)
            searched_1.push_back(store[i]);
    }

    cout<< "Number of products which have quantity: " << bottom << '-'<< top <<
        " in unit of measure "<<unit<<" is: "<<searched_1.size()<<'\n' ;

    searched_1.clear();

}

void ProductsService::search_by_date_only(int &day, int &month, int &year) {
    for(int i = 0; i < store.size(); i++){
        int j = 0;
        if(store[i].getYear() > year) {
            j++;
        }
        else{
            if(store[i].getYear() == year && store[i].getMonth() > month){
                j++;
            } else{
                if(store[i].getYear() == year && store[i].getMonth() == month && store[i].getDay() > day){
                    j++;
                }
            }
        }
        if(j == 0)
            searched_1.push_back(store[i]);
    }

    cout<< "Number of products which have been done before: "
        << day<<':'<<month<<':'<<year<<" is: "<< searched_1.size()<<'\n';

    searched_1.clear();

}


void ProductsService::search_by_quantity(char &unit, int &bottom, int &top) {
    string filter = units_mapping[unit];

    for(int i = 0; i < searched_1.size(); i++){

        if(searched_1[i].getUnit()[0] != filter[0] || searched_1[i].getQuantity() > top || searched_1[i].getQuantity() < bottom){

            searched_1.erase(searched_1.begin() + i);
            i--;

        }

    }

    cout<< "There are all products which have quantity: " << bottom << '-'<< top << " in unit of measure"<<unit<<'\n';
    print_all_data_from_vector("search");


}

void ProductsService::search_by_date(int &day, int &month, int &year) {

    for(unsigned int i = 0; i < searched_1.size(); i++){
        if(searched_1[i].getYear() > year){
            searched_1.erase(searched_1.begin() + i);
            i--;
        }
        else{
            if(searched_1[i].getYear() == year && searched_1[i].getMonth() > month){

                searched_1.erase(searched_1.begin() + i);
                i--;

            } else{
                if(searched_1[i].getYear() == year && searched_1[i].getMonth() == month && searched_1[i].getDay() > day){

                    searched_1.erase(searched_1.begin() + i);
                    i--;

                }
            }
        }
    }

    cout<< "There are all products which have been done before: "<< day<<':'<<month<<':'<<year<<'\n';
    print_all_data_from_vector("search");

}

void ProductsService::clear_search_memory() {

    this->searched_1.clear();
}

void ProductsService::delete_all_products_from_memory() {

    store.clear();
    cout<<"Memory is successfully cleared\n";

}

void ProductsService::delete_certain_product(char &source, int &idv) {

    if(source == 'f') {
        store.erase(store.begin() + bin_search(store, for_delete_update[idv].getId()));
        for_delete_update.erase(for_delete_update.begin() + idv);
        cout << "Product successfully deleted\n";
    }
    if(source == 'm'){
        for_delete_update.erase(for_delete_update.begin() + bin_search(for_delete_update, store[idv].getId()));
        store.erase(store.begin() + idv);
        cout << "Product successfully deleted\n";
    }

}

Product ProductsService::select_product_for_update(const char &source, const int &idV) {
    if (source == 'f'){
        return for_delete_update[idV];
    } else {
        return store[idV];
    }
}


void ProductsService::update_certain_product(char &source, int &idv, const Product &product) {
    if(source == 'm'){
        store[idv] = product;
        for_delete_update[bin_search(for_delete_update, product.getId())] = product;
    }
    if(source == 'f'){
        for_delete_update[idv] = product;
        store[bin_search(store, product.getId())] = product;
    }

    cout << "Product successfully updated\n";

}

void ProductsService::save_changes_to_files() {

    delete_all_products_from_files();
    for (auto & i : for_delete_update) {
        i.setBeenSaved(false);
    }
    save_all_products_from_memory_to_file("delete");
    for_delete_update.clear();
}

int ProductsService::find_exact_pos_in_vector(vector <Product> &vector1, int &id) {

    if(vector1.empty()){
        return 0;
    }
    int a = 0, b = vector1.size() - 1;
    int middle = 0;
    while(a <= b){
        middle = (a + b) / 2;
        if(vector1[middle].getId() == id)
            return -1;
        if(vector1[middle].getId() < id) {
            a = middle + 1;

        } else{
            b = middle - 1;

        }

    }
    if(middle + 1 == vector1.size()){
        return middle + 1;
    }
     return middle;


}

int ProductsService::bin_search(vector <Product> &vector1, const int &id) {


    if(vector1.empty()){
        return -1;
    }
    int a = 0, b = vector1.size() - 1;
    int middle = 0;
    while(a <= b){
        middle = (a + b) / 2;
        if(vector1[middle].getId() == id)
            return middle;
        if(vector1[middle].getId() < id) {
            a = middle + 1;

        } else{
            b = middle - 1;

        }

    }
    return -1;
}

void ProductsService::sort_by_combination(const string &combination) {
    Sorts::sort_by_any_par(combination, for_sort, 0, for_sort.size() - 1);
}








