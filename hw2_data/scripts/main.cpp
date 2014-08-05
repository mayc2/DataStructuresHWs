#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>
#include "Player.h"
#include "Team.h"

void parse_file(){
	int i=0;
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

	std::vector<Player> players;
	std::vector<Team> teams;

	parse_file();

	std::cout<<"gets to end of main"<<std::endl;
	return 0;
}