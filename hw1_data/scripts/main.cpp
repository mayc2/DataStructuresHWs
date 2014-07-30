#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>

//Function Declarations
void print_line(const int &width);
void print(const std::vector<std::string> &lines,const int &width);

int main(int argc, char const *argv[])
{
	if (argc != 5){
		std::cerr<<"Usage: file_name input_file output_file width style"<<std::endl;
		return -1;
	}

	//CLI variable value initialization
	std::string file_name=argv[0];
	std::string input_file=argv[1];
	std::string output_file=argv[2];
	std::string width=argv[3];
	std::string style=argv[4];
	
	//check variables were initialized properly
	std::cout<<"file_name="<<file_name<<"; input_file="<<input_file<<"; output_file="<<output_file<<"; width="<<width<<"; style="<<style<<std::endl;

 	return 0;
}

void print_line(const int &width){
	std::cout<<"----";
	for (int i=0; i<width; ++i) { std::cout<<"-"; }
	std::cout<<std::endl;
}

void print(const std::vector<std::string> &lines,const int &width){
	//print the top line
	print_line(width);



	//print the bottom line
	print_line(width);
}
