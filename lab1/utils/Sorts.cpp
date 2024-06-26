//
// Created by Win10Pro on 22.03.2020.
//

#include "Sorts.h"

int Sorts::limit = 10;

int Sorts::compare_string(const string& a, const string& b) {
    int temp_a;
    int temp_b;
    for(int i = 0; i < min(a.length(), b.length()); i++){
        if(int(a[i]) < 97)
            temp_a = int(a[i]) % 65;
        else
            temp_a = int(a[i]) % 97;
        if(int(b[i]) < 97)
            temp_b = int(b[i]) % 65;
        else
            temp_b = int(b[i]) % 97;
        if(temp_a > temp_b)
            return 1;
        if(temp_a < temp_b)
            return -1;
    }
    if(a.length() == b.length())
        return 0;
    if(a.length() > b.length())
        return 1;
    else
        return -1;
}

int Sorts::compare_int(const int &a, const int &b) {
    if(a > b)
        return 1;
    if(a < b)
        return -1;
    return 0;
}

int Sorts::compare_date(const Product& a, const Product& b) {

    if(a.getYear() > b.getYear())
        return 1;
    if(a.getYear() < b.getYear())
        return -1;
    if(a.getMonth() > b.getMonth())
        return 1;
    if(a.getMonth() < b.getMonth())
        return -1;
    if(a.getDay() > b.getDay())
        return 1;
    if(a.getDay() < b.getDay())
        return -1;
    return 0;

}

int Sorts::compare_product(const Product &a, const Product &b, const string& key) {

    for(int i = 0; i < key.length(); i++) {
        if (key[i] == 'n') {
            if (compare_string(a.getName(), b.getName()) != 0 || i == key.length() - 1)
                return compare_string(a.getName(), b.getName());
        } else if (key[i] == 'u') {
            if(compare_string(a.getUnit(), b.getUnit()) != 0 || i == key.length() - 1)
                return compare_string(a.getUnit(), b.getUnit());
        } else if (key[i] == 'q') {
            if(compare_int(a.getQuantity(), b.getQuantity()) != 0 || i == key.length() - 1)
                return compare_int(a.getQuantity(), b.getQuantity());
        } else if (key[i] == 'd') {
            if(compare_date(a, b) != 0 || i == key.length() - 1)
                return compare_date(a, b);
        } else if (key[i] == 'e') {
            if(compare_int(a.getExpiryPeriod(), b.getExpiryPeriod()) != 0 || i == key.length() - 1)
                return compare_int(a.getExpiryPeriod(), b.getExpiryPeriod());
        }
    }
    return 0;

}

void Sorts::counting_sort_for_unit(vector<Product> &vector1) {

    int count[4] = {0};
    for(auto & i : vector1){
        if(i.getUnit() == "bunches")
            count[0]++;
        if(i.getUnit() == "kilos")
            count[1]++;
        if(i.getUnit() == "litres")
            count[2]++;
        if(i.getUnit() == "pieces")
            count[3]++;
    }
    vector <Product> vector2;
    for(const auto & i : vector1){
        vector2.push_back(i);
    }
    int pos[4] = {0, count[0], count[0] + count[1], count[0] + count[1] + count[2]};
    for(auto & i : vector2){
        if(i.getUnit() == "bunches"){
            vector1[pos[0]] = i;
            pos[0]++;
        }
        if(i.getUnit() == "kilos"){
            vector1[pos[1]] = i;
            pos[1]++;
        }
        if(i.getUnit() == "litres"){
            vector1[pos[2]] = i;
            pos[2]++;
        }
        if(i.getUnit() == "pieces"){
            vector1[pos[3]] = i;
            pos[3]++;
        }

    }
}

void Sorts::radix_sort_for_exp_per(vector<Product> &vector1) {

    vector < vector <Product> > count(10);
    for(int base = 1; base <= 100; base *= 10) {
        for(int i = 0; i < 10; i++) {
            count[i].clear();
        }
        for (int i = 0; i < vector1.size(); i++) {
            count[(vector1[i].getExpiryPeriod() / base) % 10].push_back(vector1[i]);
        }
        vector1.clear();
        for(int j = 0; j < 10; j++){
            for(int k = 0; k < count[j].size(); k++){
                vector1.push_back(count[j][k]);
            }
        }

    }


}

void Sorts::insertion_sort(vector<Product> &vector1, int lo, int hi, const string &key) {

    for (int i = lo; i < hi + 1; i++) {
        Product temp = vector1[i];
        int j;
        for (j = i; j > lo && compare_product(vector1[j-1], temp, key) > 0;j--) {
            vector1[j] = vector1[j-1];
        }
        vector1[j] = temp;
    }

}

void Sorts::merge(vector<Product> &vector1, vector<Product> &for_merge, int lo, int mid, int hi, const string &key) {

    for(int i = lo; i <= hi; i++){
        for_merge[i] = vector1[i];
    }
    int i = lo, j = mid + 1;
    for(int k = lo; k <=hi; k++){
        if(i > mid){
            vector1[k] = for_merge[j];
            j++;
        } else if(j > hi ) {
            vector1[k] = for_merge[i];
            i++;
        } else if (compare_product(for_merge[i], for_merge[j], key) > 0){
            vector1[k] = for_merge[j];
            j++;
        } else{
            vector1[k] = for_merge[i];
            i++;
        }

    }

}

void Sorts::sort(vector<Product> &vector1, vector<Product> &for_merge, int lo, int hi, const string &key) {

    if(hi <= lo + limit - 1) {

        insertion_sort(vector1,lo, hi, key);
        return;
    }
    int mid = lo + (hi - lo) / 2;
    sort(vector1, for_merge, lo, mid, key);
    sort(vector1, for_merge, mid + 1, hi, key);
    merge(vector1, for_merge, lo, mid, hi, key);

}

void Sorts::smart_merge_sort_for_memory(vector<Product> &vector1, int lo, int hi, const string &key) {

    vector <Product> for_merge = vector1;
    sort(vector1, for_merge, lo, hi, key);
    //delete[] for_merge;

}

void Sorts::sort_by_any_par(const string &key, vector<Product> &vector1, int lo, int hi) {

    if(key == "u") {
        counting_sort_for_unit(vector1);
        return;
    }
    if(key == "e"){
        radix_sort_for_exp_per(vector1);
        return;
    }
    smart_merge_sort_for_memory(vector1, lo, hi, key);

}