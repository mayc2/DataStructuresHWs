#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <cstdlib>
//Note: exit codes
//       Success = 0
//       Failure = 1

//Function Declarations
void print_line(const int &width);
void print(const std::vector<std::string> &lines,const int &width);
std::vector<std::string> read_input_file(std::ifstream istr, const char * input_file);

int main(int argc, char const *argv[])
{
	if (argc != 5){
		std::cerr<<"Usage: file_name input_file output_file width style"<<std::endl;
		return 1;
	}
	
	//CLI arguments implementation
	std::ifstream istr(argv[1]);
	std::ofstream ostr(argv[2]);
	std::string style=argv[4];
	const char * tmp=argv[3];
	float width=atof(tmp);

	std::vector<std::string> words = read_input_file(istr,argv[1]);
	for(int i=0; i<words.size(); ++i){
		std::cout<<words[i]<<std::endl;
	}

 	return 0;
}

//reads input file into a vector using fstream
std::vector<std::string> read_input_file(std::ifstream istr, const char * input_file){
	if (!istr){
		std::cerr<<"Could not open input_file, "<<input_file<<std::endl;
		return;
	}

	std::string temp;
	std::vector<std::string> words;
	while(istr>>temp){
		words.push_back(temp);
	}

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

