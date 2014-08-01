#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>
#include "Player.h"
#include "Team.h"

int main(int argc, char const *argv[])
{
	//check to ensure correct number of arguments
	if (argc != 3){
		std::cerr<<"Usage: ./file_name.exe input_file output_file"<<std::endl;
		return 1;
	}	

	parse_file();

	return 0;
}