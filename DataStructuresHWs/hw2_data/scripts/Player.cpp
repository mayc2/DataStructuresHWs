#include <iostream>
#include <string>
#include <cmath>
#include "Player.h"

/*
//Class Variables
const std::string player_name
const std::string player_team
int goals
int assists
int penalties
*/

void Player::addGoals(){
	++goals;
}
void Player::addAssists(){
	++assists;
}
void Player::addPenalties(){
	++penalties;
}
void Player::addGoals(const int &g){
	goals+=g;
}
void Player::addAssists(const int &a){
	assists+=a;
}
void Player::addPenalties(const int &p){
	penalties+=p;
}
