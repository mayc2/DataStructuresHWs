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


std::vector<std::string> getLines_Needed(const int &width, std::ofstream &fout, const std::vector<std::string> &words){

	int lines_needed=1;
	std::vector<std::string> formatted_words;
	std::string formatted_word;
	int line_count = 0;
	for (int i = 0; i < words.size(); i++){
		if (line_count + words[i].size() <= width){
			line_count += words[i].size();
			formatted_word.append(words[i]);
			formatted_word.append(" ");
		}
		else{
			formatted_word.erase(formatted_word.size()-1, 1);
			formatted_words.push_back(formatted_word);
			formatted_word = words[i] + ' ';
			lines_needed++;
			line_count = words[i].size();
			
		}
		// to get the last line in the text
		if (i == words.size()-1) {
			formatted_word.erase(formatted_word.size()-1, 1);
			formatted_words.push_back(formatted_word);
		}
		line_count++;
		
	}
	return formatted_words;
}


//check that style exists
int check_style(std::string style){
	if(style=="flush_left")			{return 0;}
	else if(style=="flush_right")	{return 0;} 
	else if(style=="full_justify")	{return 0;}
	else 							{return 1;}
}

//reads input file into a vector using fstream
void read_input_file(std::ifstream& fin, const char * input_file, std::vector<std::string>& words){
	if (!fin){
		std::cerr<<"Could not open input_file, "<<input_file<<std::endl;
		exit(1);
	}
	std::string temp;
	while(fin>>temp){
		words.push_back(temp);
	}
}

void implement_style(const std::vector<std::string> &lines, const std::string &style, std::ofstream &fout){

}

void print_line(const int &width,std::ofstream &fout){
	fout<<"----";
	for (int i=0; i<width; ++i) { fout<<"-"; }
	fout<<std::endl;
}

void print_left_just(const std::vector<std::string> &lines,const int &width,std::ofstream &fout){
	//print the top line
	print_line(width, fout);

	//print middle lines
	for(int i=0; i<lines.size();++i){
		fout<<"| ";
		fout<<lines[i];
		fout<<" |"<<std::endl;
	}

	//print the bottom line
	print_line(width, fout);
}


int main(int argc, char *argv[])
{
	if (argc != 5){
		std::cerr<<"Usage: file_name input_file output_file width style"<<std::endl;
		return 1;
	}
	
	//CLI arguments implementation
	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);
	std::string style=argv[4];
	int width=atoi(argv[3]);
	
	//check style
	if(check_style(style)!=0){
		std::cerr<<"Usage: Argument 5 (formatting style) options: flush_left, flush_right, full_justify"<<std::endl;
		return 1;
	}

	//vector holding each word of the input text file
	std::vector<std::string> words;

	//read input file into words vector
	read_input_file(fin,argv[1],words);

	//quick check to confirm words were added to vector properly
	std::cout<<std::endl<<"Checking initial vector of parse from file"<<std::endl;
	for(int i=0; i<words.size(); ++i){
		std::cout<<words[i]<<std::endl;
	}
	std::cout<<std::endl<<std::endl;

	//vector holding proper words per line
	std::vector<std::string> lines=getLines_Needed(width, fout, words);

	//selects proper style functions and executes
	implement_style(lines,style,fout);

	print_left_just(lines,width,fout);

 	return 0;
}

