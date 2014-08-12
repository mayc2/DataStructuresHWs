// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
//    This file provides the code for ASCII art printing of trains.
//    You should implement all of the functions prototyped in
//    "traincar_prototypes.h" in this file.
//
// =======================================================================


#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "traincar.h"
#include <cmath>

// =======================================================================
// =======================================================================

// This helper function checks that the forward and backward pointers
// in a doubly-linked structure are correctly and consistently assigned.
void SanityCheck(TrainCar* train) {
  // an empty train is valid
  if (train == NULL) return;
  assert (train->prev == NULL);
  TrainCar *tmp = train;
  while (tmp->next != NULL) {
    // the next train better point back to me
    assert (tmp->next->prev == tmp);
    tmp = tmp->next;
  }
}


// This helper function prints one of the 5 rows of the TrainCar ASCII art
void PrintHelper(TrainCar* t, int which_row) {
  if (t == NULL) {
    // end of the line
    std::cout << std::endl;
    return;
  }

  if (which_row == 0) {
    // the top row only contains "smoke" for engine traincars
    if (t->isEngine()) {
      std::cout << "     ~~~~";
    } else {
      std::cout << "         ";
    }
  } else if (which_row == 1) {
    // the 2nd row only contains the smoke stack for engine traincars
    if (t->isEngine()) {
      std::cout << "    ||   ";
    } else {
      std::cout << "         ";
    }
  } else if (which_row == 2) {
    // the 3rd row contains the ID for each traincar
    // (and engine traincars are shaped a little differently)
    if (t->isEngine()) {
      std::cout << "   " << std::setw(6) << std::setfill('-') << t->getID();
    } else {
      std::cout << std::setw(9) << std::setfill('-') << t->getID();
    }
    std::cout << std::setfill(' ');
  } else if (which_row == 3) {
    // the 4th row is different for each TrainCar type
    if (t->isEngine()) {
      std::cout << " / ENGINE";
    } else if (t->isFreightCar()) {
      // freight cars display their weight
      std::cout << "|" << std::setw(5) << t->getWeight() << "  |";
    } else if (t->isPassengerCar()) {
      // passenger cars are simple empty boxes
      std::cout << "|       |";
    } else if (t->isDiningCar()) {
      std::cout << "|  dine |";
    } else {
      assert (t->isSleepingCar());
      std::cout << "| sleep |";
    }
  } else if (which_row == 4) {
    // final row is the same for all cars, just draw the wheels
    std::cout << "-oo---oo-";
  }

  // between cars display the '+' link symbol on the 5th row 
  // (only if there is a next car)
  if (t->next != NULL) {
    if (which_row == 4) {
      std::cout << " + ";
    } else {
      std::cout << "   ";
    }
  }

  // recurse to print the rest of the row
  PrintHelper(t->next, which_row);
}


void PrintTrain(TrainCar* train) {
  
  if (train == NULL) { 
    std::cout << "PrintTrain: empty train!" << std::endl; 
    return; 
  }

  // Print each of the 5 rows of the TrainCar ASCII art
  PrintHelper(train, 0);
  PrintHelper(train, 1);
  PrintHelper(train, 2);
  PrintHelper(train, 3);
  PrintHelper(train, 4);

  /*  
  // UNCOMMENT THESE ADDITIONAL STATISTICS AS YOU WORK

  int total_weight,num_engines,num_freight_cars,num_passenger_cars,num_dining_cars,num_sleeping_cars;
  CountEnginesAndTotalWeight
    (train, total_weight,
     num_engines, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars);
  int total_cars = num_engines+num_freight_cars+num_passenger_cars+num_dining_cars+num_sleeping_cars;
  float speed = CalculateSpeed(train);
  std::cout << "#cars = " << total_cars;
  std::cout << ", total weight = " << total_weight;
  std::cout << ", speed on 2% incline = " << std::setprecision(1) << std::fixed << speed;

  // If there is at least one passenger car, print the average
  // distance to dining car statistic
  if (num_passenger_cars > 0) {
    float dist_to_dining = AverageDistanceToDiningCar(train);
    if (dist_to_dining < 0) {
      // If one or more passenger cars are blocked from accessing the
      // dining car (by an engine car) then the distance is infinity!
      std::cout << ", avg distance to dining = inf";
    } else {
      std::cout << ", avg distance to dining = " << std::setprecision(1) << std::fixed << dist_to_dining;
    }
  }

  // If there is at least one sleeping car, print the closest engine
  // to sleeper car statistic
  if (num_sleeping_cars > 0) {
    int closest_engine_to_sleeper = ClosestEngineToSleeperCar(train);
    std::cout << ", closest engine to sleeper = " << closest_engine_to_sleeper;
  }

  std::cout << std::endl;
  */
}


// =======================================================================
// =======================================================================

void PushBack(TrainCar * &simple, TrainCar *car){
	if (simple == NULL) simple = car;
	else {
		TrainCar *tmp = simple;
		while (tmp->next != NULL) tmp = tmp->next;
		tmp->next = car;
		car->prev = tmp;
	}
}

void DeleteAllCars(TrainCar * &train){
	TrainCar *tmp = train;
	while (train != NULL){
		train = train->next;
		delete [] tmp;
		tmp = train;
	}
	delete train;
}

void CountEnginesAndTotalWeight(TrainCar * train, int &total_weight, int &num_engines, int &num_freight_cars, int &num_passenger_cars, int &num_dining_cars, int &num_sleeping_cars){
	total_weight = 0; num_engines = 0; num_freight_cars = 0; num_passenger_cars = 0; num_dining_cars = 0; num_sleeping_cars = 0;
	while (train != NULL){
		if (train->isEngine()) num_engines++;
		if (train->isDiningCar()) num_dining_cars++;
		if (train->isPassengerCar()) num_passenger_cars++;
		if (train->isSleepingCar()) num_sleeping_cars++;
		if (train->isFreightCar()) num_freight_cars++;
		total_weight+=train->getWeight();
		train = train->next;
	}
	int total_cars = num_engines+num_freight_cars+num_passenger_cars+num_dining_cars+num_sleeping_cars;
}

float CalculateSpeed(TrainCar * train){
	float TotalHP = 0;
	float TotalW = 0;
	while (train != NULL){
		if (train->isEngine()) TotalHP+=3000;
		TotalW+=train->getWeight();
		train = train->next;
	}

	float speed = (TotalHP * 550 * 3600)/(20 * 2 * 5280 * TotalW);
	return speed;
}

void sortFreight(TrainCar *&freight){
	//make if statement to check corner case
	TrainCar* curr = freight->next;
	
	
	while (curr != NULL){
		TrainCar* temp = curr;
		TrainCar* behind = curr->prev;
		TrainCar* after;
		TrainCar* two_behind;
		if (curr->getWeight() < behind->getWeight()){
		//find the spot to do insertion sort
			while (temp->prev != NULL&& temp->getWeight() < temp->prev->getWeight()) {
				behind = temp->prev;
				after = temp->next;
				two_behind = behind->prev;
				temp->next = behind;
				temp->prev = behind->prev;
				if (two_behind != NULL) two_behind->next = temp;
				behind->next = after;
				behind->prev = temp;
				if (after != NULL) after->prev = behind;
			}


		}
		curr = curr->next;
	}
	while (freight->prev != NULL){
		freight = freight->prev;
	}


}
int findWeight(TrainCar* &train){
	int total_weight = 0;
	TrainCar* tmp = train;
	while (tmp != NULL){
		total_weight = total_weight + tmp->getWeight();
		tmp = tmp->next;
	}
	return total_weight;
}
int getLength(TrainCar* &train){
	if (train == NULL) return 0;
	int total_length = 0;
	TrainCar* tmp = train;
	while (tmp != NULL){
		total_length++;
		tmp = tmp->next;
	}
	return total_length;
}

int enginesNeeded(TrainCar* &train, const int &min_speed){
	int horsepower = 0;
	int engine_weight = 0;
	int total_engines = 0;
	float weight_required;
	int total_weight = findWeight(train);
	//find # engines needed
	while (true){
		
		weight_required = (9.375*horsepower)/min_speed-engine_weight;
		if (total_weight > weight_required){
			horsepower+=3000;
			engine_weight+=150;
			total_engines++;
		}
		else
			break;

	}
	return total_engines;
}

int enginesNeeded2(TrainCar* &train, TrainCar* &freight, const int &min_speed){
	int horsepower = 0;
	int engine_weight = 0;
	int total_engines = 0;
	float weight_required;
	int total_weight = findWeight(train) + findWeight(freight);
	//find # engines needed
	while (true){
		
		weight_required = (9.375*horsepower)/min_speed-engine_weight;
		if (total_weight > weight_required){
			horsepower+=3000;
			engine_weight+=150;
			total_engines++;
		}
		else
			break;

	}
	return total_engines;
}
int differenceofEngines(TrainCar* &train, TrainCar* &freight, const int &min_speed){
	int engines1, total_engines;
	int weight1 = findWeight(train);
	//find the difference in the needed engines
	engines1 = enginesNeeded(train, min_speed);
	total_engines = enginesNeeded2(train, freight, min_speed);
	return total_engines-engines1;

}

int superFunction(TrainCar* &train1, TrainCar* &train2, const int &min_speed){
	// returns the length of trains w/ engines
	//float weight_required = (9.375*horsepower)/min_speed-engine_weight;
	int weight1 = findWeight(train1);
	int length1 = getLength(train1);
	int weight2 = findWeight(train2);
	int length2 = getLength(train2);
	
	int total_length = length1 + length2;
	int total_weight = weight1 + weight2;
	int horsepower = 0;
	int engine_weight = 0;
	int total_engines = 0;
	float weight_required;
	//find # engines needed
	while (true){
		
		weight_required = (9.375*horsepower)/min_speed-engine_weight;
		if (total_weight > weight_required){
			horsepower+=3000;
			engine_weight+=150;
			total_engines++;
		}
		else
			break;

	}
	return total_length + total_engines;

}
TrainCar* to_the_back(TrainCar* train){
	if (train->next == NULL) return train;
	to_the_back(train->next);

}

vector<TrainCar*> ShipFreight(TrainCar *&engines, TrainCar *&freight, const int &min_speed, const int &limit){
	vector<TrainCar*> trains;
	sortFreight(freight);

	// walk through all the freights
	// add values up
	// if the weight exceeds the weight required for one engine with required speed, disconnect; move onto next train
	// add one engine to previous train, link to the front
	
	float weight_required = (9.375*3000)/min_speed-150;
	TrainCar* tmp = freight;
	while (tmp != NULL){
		int total_weight = 0;
		int num_cars=0;
		
		//group freights by weights enough for 1 engine
		while (total_weight + tmp->getWeight() < weight_required){
			total_weight = total_weight + tmp->getWeight();
			num_cars++;
			if (tmp->next != NULL)
				if (total_weight + tmp->next->getWeight() > weight_required) break;
			tmp = tmp->next;
			if (tmp == NULL) break;


		}

		//push_back first train freight group
		if (trains.size() == 0) {
			trains.push_back(freight);
			freight = tmp->next;
			tmp->next = NULL;
			freight->prev = NULL;
			tmp = freight;
		}

		else{
			TrainCar* tmp2;
			if (tmp != NULL){
				tmp2 = tmp->next;
				tmp->next = NULL;
				tmp2->prev = NULL;
			}
				//find suitable train to append to, otherwise make new train if none suitable
				bool found = false;
				int max = limit;
				int the_one;
				for (int i = 0; i < trains.size(); i++){
					if (superFunction(freight, trains[i], min_speed) <= limit){
						found = true;
						if (differenceofEngines(trains[i],freight, min_speed) < max) {
							
							the_one = i;
							max = findWeight(trains[i]);
							continue;
						}
						
					}
					else continue;
					
					break;
				}
				if (!found) trains.push_back(freight);
				else {
					TrainCar *temp = trains[the_one];
					while (temp->next != NULL) temp = temp->next;
					temp->next = freight;
					freight->prev = temp;
				}
				if (tmp != NULL){
				freight = tmp2;
				tmp = tmp2;
				}
				else freight = NULL;
		}


	}

	// add engines
	for (int i = 0; i < trains.size(); i++){
		TrainCar* tmp = engines;
		for (int k = 1; k < enginesNeeded(trains[i], min_speed); k++){
			tmp = tmp->next;
		}
		engines = tmp->next;
		engines->prev = NULL;
		tmp->next = trains[i];
		trains[i]->prev = tmp;
		while ( trains[i]->prev != NULL) trains[i] = trains[i]->prev;

	}
	
	/*for (int i = 0; i < trains.size(); i++){
		while (trains[i]!=NULL){
			cout << trains[i]->getWeight() << " ";
			trains[i] = trains[i]->next;
		}
		cout << endl;
	}*/

	return trains;


}

void Separate(TrainCar* &train1, TrainCar* &train2, TrainCar* &train3){
	int length = getLength(train1) - 2;
	int half = length/2;
	int engine_count = 0;
	TrainCar* back = to_the_back(train1);
	TrainCar* front = train1;
	for (int i = 0; i < half; i++){
		
		//check for more than 1 engine
		if (engine_count == 1){
			if (train1->isEngine()){
				TrainCar* next_place_holder = train1->next;
				TrainCar* tmp_behind = train1->prev;
				tmp_behind->next = next_place_holder;
				tmp_behind->next->prev = tmp_behind;
				back->next = train1;
				train1->prev = back;
				train1->next = NULL;
				train1 = next_place_holder;
				i--;
				continue;
			}
		}

		//if at the end of the line, and still no engine, take one from other half, starting from back...UNLESS theres an engine right after
		if (i == half-1){
			if (engine_count == 0){
				if (train1->next->isEngine()){
					train1 = train1->next;
					break;
				}
				TrainCar* tmp = back;
				while (!tmp->isEngine()){
					tmp = tmp->prev;
				}
				TrainCar* tmp_behind = tmp->prev;
				TrainCar* tmp_after;
				if (tmp->next != NULL) tmp_after = tmp->next;
				else tmp_after = NULL;
				tmp->next = train1->next;
				tmp->next->prev = tmp;
				train1->next = tmp;
				tmp_behind->next = tmp_after;
				if (tmp_after != NULL) tmp_after->prev = tmp_behind;
				tmp->prev = train1;
				train1 = tmp;
				break;
			}
		}

		if (train1->isEngine()) engine_count++;
		train1 = train1->next;

	}
	TrainCar* next_place_holder = train1->next;
	train1->next = NULL;
	next_place_holder->prev = NULL;
	train2 = front;
	train3 = next_place_holder;
	train1 = NULL;
}