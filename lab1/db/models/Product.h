//
// Created by Win10Pro on 25.01.2020.
//

#ifndef LAB_1_DATA_BASE_IN_FILES__PRODUCTS_H
#define LAB_1_DATA_BASE_IN_FILES__PRODUCTS_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <chrono>
#include <thread>


using namespace std;
class Product {

private:

    int static product_counter;

    string Name;
    string Unit;
    int Quantity{};
    int Day{};
    int Month{};
    int Year{};
    int Hours{};
    int Mins{};
    int Seconds{};
    int Expiry_period{};
    int Id{};
    bool Been_saved{};
public:
    static int getProductCounter();
    //Variables



    const string &getName() const;
    void setName(const string &name);
    const string &getUnit() const;
    void setUnit(const string &unit);
    int getQuantity() const;
    void setQuantity(int quantity);
    int getDay() const;
    void setDay(int day);
    int getMonth() const;
    void setMonth(int month);
    int getYear() const;
    void setYear(int year);
    int getHours() const;
    void setHours(int hours);
    int getMins() const;
    void setMins(int mins);
    int getSeconds() const;
    void setSeconds(int seconds);
    int getExpiryPeriod() const;
    void setExpiryPeriod(int expiryPeriod);
    int getId() const;
    bool isBeenSaved() const;
    void setBeenSaved(bool beenSaved);

    Product (int Id, string &Name, string &Unit, int Quantity,
             int Day, int Month, int Year, int Hours, int Mins, int Seconds, int Expiry_period, bool Been_saved);

    //ProductsService

    static void define_id();
    void save_to_file(ofstream &f, bool empty);
    void save_to_bin_file(ofstream &f);

};


#endif //LAB_1_DATA_BASE_IN_FILES__PRODUCTS_H
