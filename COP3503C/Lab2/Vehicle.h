#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>
class Vehicle {
    public:
        Vehicle();
        Vehicle(std::string make, std::string model, int year, float price, int mileage);
        void Display();
        std::string GetYearMakeModel();
        float GetPrice();

    private:
        std::string make;
        std::string model;
        unsigned int year;
        float price;
        unsigned int miles;
};
#endif