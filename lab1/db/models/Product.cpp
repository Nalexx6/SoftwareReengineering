//
// Created by Win10Pro on 25.01.2020.
//

#include "Product.h"

int Product::product_counter = 0;

Product::Product(int Id, string &Name, string &Unit, int Quantity, int Day, int Month, int Year,
         int Hours, int Mins, int Seconds, int Expiry_period, bool Been_saved) {

    if(Been_saved){
        this->Id = Id;
    }
    else {
        this->Id = product_counter;
        Product::product_counter++;
    }
    this->Name = Name;
    this->Unit = Unit;
    this->Quantity = Quantity;
    this->Day = Day;
    this->Month = Month;
    this->Year = Year;
    this->Hours = Hours;
    this->Mins = Mins;
    this->Seconds = Seconds;
    this->Expiry_period = Expiry_period;
    this->Been_saved = Been_saved;

}

void Product::define_id() {

    ifstream f ("../files/Products.txt");

    f.seekg(-1, std::ios_base::end);
    bool keepLooping = true;
    string line;

    while (keepLooping) {

        char ch = 0;

        f.get(ch);

        if(f.tellg() <= 1)
            f.seekg(0), keepLooping = false;
        else if (ch == '\n')
            keepLooping = false;
        else
            f.seekg(-2, std::ios_base::cur);

    }
    f >> product_counter;

    f.close();
}

void Product::save_to_file(ofstream &f, bool empty)  {

    if(!empty)
        f<<'\n';
    f <<  this->Id << "\t";
    f <<  this->Name << "\t" ;
    f <<  this->Unit << "\t" ;
    f <<  this->Quantity << "\t" ;
    f <<  this->Day << " " << this->Month << " " << this->Year << "\t";
    f <<  this->Hours << " " << this->Mins << " "<< this->Seconds << "\t";
    f <<  this->Expiry_period ;

    this->Been_saved = true;

}

void Product::save_to_bin_file(ofstream &f) {

    f.write((char*)&this->Id, sizeof(this->Id));
    int name_length = Name.size();
    f.write((char*)&name_length, sizeof(name_length));
    f << this->Name;
    int unit_length = Unit.size();
    f.write((char*)&unit_length, sizeof(unit_length));
    f << this->Unit;
    f.write((char*)&this->Quantity, sizeof(this->Quantity));
    f.write((char*)&this->Day, sizeof(this->Day));
    f.write((char*)&this->Month, sizeof(this->Month));
    f.write((char*)&this->Year, sizeof(this->Year));
    f.write((char*)&this->Hours, sizeof(this->Hours));
    f.write((char*)&this->Mins, sizeof(this->Mins));
    f.write((char*)&this->Seconds, sizeof(this->Seconds));
    f.write((char*)&this->Expiry_period, sizeof(this->Expiry_period));

}

const string &Product::getName() const {
    return Name;
}

void Product::setName(const string &name) {
    Name = name;
}

const string &Product::getUnit() const {
    return Unit;
}

void Product::setUnit(const string &unit) {
    Unit = unit;
}

int Product::getQuantity() const {
    return Quantity;
}

void Product::setQuantity(int quantity) {
    Quantity = quantity;
}

int Product::getDay() const {
    return Day;
}

void Product::setDay(int day) {
    Day = day;
}

int Product::getMonth() const {
    return Month;
}

void Product::setMonth(int month) {
    Month = month;
}

int Product::getYear() const {
    return Year;
}

void Product::setYear(int year) {
    Year = year;
}

int Product::getHours() const {
    return Hours;
}

void Product::setHours(int hours) {
    Hours = hours;
}

int Product::getMins() const {
    return Mins;
}

void Product::setMins(int mins) {
    Mins = mins;
}

int Product::getSeconds() const {
    return Seconds;
}

void Product::setSeconds(int seconds) {
    Seconds = seconds;
}

int Product::getExpiryPeriod() const {
    return Expiry_period;
}

void Product::setExpiryPeriod(int expiryPeriod) {
    Expiry_period = expiryPeriod;
}

int Product::getId() const {
    return Id;
}

void Product::setId(int id) {
    Id = id;
}

bool Product::isBeenSaved() const {
    return Been_saved;
}

void Product::setBeenSaved(bool beenSaved) {
    Been_saved = beenSaved;
}

int Product::getProductCounter() {
    return product_counter;
}
