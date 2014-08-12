// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//
#include <string>
#include <cassert>
#include <iomanip>
#include <vector>
#include <cmath>
#include "traincar.h"

using namespace std;

void PushBack(TrainCar * &simple, TrainCar *car);
void DeleteAllCars(TrainCar * &train);
void sortFreight(TrainCar* &freight);
void CountEnginesAndTotalWeight(TrainCar * train, int &total_weight, int &num_engines, int &num_freight_cars, int &num_passenger_cars, int &num_dining_cars,int &num_sleeping_cars);
float CalculateSpeed(TrainCar * train);
int findWeight(TrainCar* &train);
int getLength(TrainCar* &train);
int enginesNeeded(TrainCar* &train, const int &min_speed);
int enginesNeeded2(TrainCar* &train, TrainCar* &freight, const int &min_speed);
int differenceofEngines(TrainCar* &train, TrainCar* &freight, const int &min_speed);
int superFunction(TrainCar* &train1, TrainCar* &train2, const int &min_speed);
vector<TrainCar*> ShipFreight(TrainCar *&engines, TrainCar *&freight, const int &min_speed, const int &limit); 
void Separate(TrainCar* &train1, TrainCar* &train2, TrainCar* &train3);