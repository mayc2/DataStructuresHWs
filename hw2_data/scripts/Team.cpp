#include <iostream>
#include <string>
#include <cmath>
#include "Team.h"

/*
//Class Variables
const std::string team_name
int wins
int losses
int ties
float win_percentage
int goals
int penalties
int games_played
*/

void Team::addWins(){
	++wins;
}
void Team::addLosses(){
	++losses;
}
void Team::addTies(){
	++ties;
}
void Team::addGoals(){
	++goals;
}
void Team::addPenalties(){
	++penalties;
}
void Team::addGP(){
	++games_played;
}
void Team::addWins(const int &w){
	wins+=w;
}
void Team::addLosses(const int &l){
	losses+=l;
}
void Team::addTies(const int &t){
	ties+=t;
}
void Team::addGoals(const int &g){
	goals+=g;
}
void Team::addPenalties(const int &p){
	penalties+=p;
}
void Team::addGP(const int &gp){
	games_played+=gp;
}
float Team::calc_win_perc(){
	win_percentage=(float)float(wins)/float(games_played);
}
