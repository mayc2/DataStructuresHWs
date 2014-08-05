#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <map>
#include "Player.h"
#include "Team.h"

void parse_file(std::map<std::string,Player> &players, std::map<std::string,Team> &teams, std::ifstream &fin){

	std::string temp;
	while(fin >> temp){
		std::map<std::string,Player>::iterator player_it;
		
		//handles team(wins,losses,games_played statistics)
		std::map<std::string,Team>::iterator team_it1;
		std::map<std::string,Team>::iterator team_it2;
		std::string team1,team2;
		int score1,score2;
		if(temp=="FINAL"){
			fin>>team1>>score1>>team2>>score2;
			team_it1=players.find(team1);
			team_it2=players.find(team2);
			//if team 1 won
			if(score1 > score2){
				team_it1->second.addWins();
				team_it2->second.addLosses();
				team_it1->second.addGP();
				team_it2->second.addGP();
			}
			//if team 1 lost
			else if (score1 < score2){
				team_it1->second.addLosses();
				team_it2->second.addWins();
				team_it1->second.addGP();
				team_it2->second.addGP();
			}
			//if tied
			else{
				team_it1->second.addTies();
				team_it2->second.addTies();
				team_it1->second.addGP();
				team_it2->second.addGP();
			}
		}
		//handle goals

		//handle penalties

		//handle 

	}
}

int main(int argc, char const *argv[])
{
	//check to ensure correct number of arguments
	if (argc != 3){
		std::cerr<<"Usage: ./file_name.exe input_file output_file"<<std::endl;
		return 1;
	}	

	//initialize i/o streams to/from files
	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);

	//check to confirm streams work
	if(!fin){
		std::cerr<<"Error: Unable to open input file."<<std::endl;
		return 1;
	}
	if(!fout){
		std::cerr<<"Error: unable to open output file."<<std::endl;
		return 1;
	}

	std::map<std::string,Player> players;
	std::map<std::string,Team> teams;

	parse_file(players,teams,fin);

	std::cout<<"gets to end of main"<<std::endl;
	return 0;
}