#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
//Note: exit codes
//       Success = 0
//       Failure = 1

std::vector<std::string> full_justify(std::vector<std::string> &words, const int &width){
	//find # of total spaces
	//divide total # of spaces by # of words on the line - 1 to get spaces in between words
	//create new line with the desired spaces
	std::vector<std::string> new_words;
	for (int i = 0; i < words.size(); i++){
		if (i == words.size() -1) {
			std::string word_ = words[i];
			new_words.push_back(word_);
			break;

		}
		//find spaces
		int scount = 0;
		int wcount = 0;
		std::string tmp;
		std::vector<std::string> temp;
		int spaces_needed = width - words[i].size();
		for (int k = 0; k < words[i].size(); k++){
			if (words[i][k] == ' ') scount++;
		}
		scount+=spaces_needed;
		//count words
		std::stringstream stream(words[i]);
		while (stream >> tmp) {
			wcount++;
			temp.push_back(tmp);
		}
		int total_spaces;
		int remainder_spaces;
		//find total # of spaces
		if (wcount-1 > 0){
		 total_spaces = scount/(wcount-1);
		 remainder_spaces = scount%(wcount-1);
		}
		else{
			 total_spaces = 0;
			 remainder_spaces = 0;
		}
		//cout << total_spaces << " " << remainder_spaces << endl;


		//now lets get complicated
		//create new vector for words
		
		std::string new_word;
		for (int k = 0; k < temp.size(); k++){
			new_word.append(temp[k]);
			if (k == temp.size()-1) break;
			for (int s = 0; s < total_spaces; s++) new_word.append(" ");
			if (remainder_spaces > 0) {
				new_word.append(" ");
				remainder_spaces--;
			}
			
		}
		//cout << new_word << endl;
		new_words.push_back(new_word);
		
	}

	return new_words;	
	
}

std::vector<std::string> getLines_Needed(const int &width, std::ofstream &fout, const std::vector<std::string> &words){

	std::vector<std::string> formatted_words;
	std::string formatted_word;
	int line_count = 0;
	for (int i = 0; i < words.size(); i++){
		
		//handle words > size of width
		if (words[i].size() > width){
			std::string tmp_word(words[i]);
			while(tmp_word.size() > width){
				formatted_word=tmp_word.substr(0,width-1);
				formatted_word.append("-");
				tmp_word.erase(0,width-1);
				formatted_words.push_back(formatted_word);
				line_count=width;
			}
			if (tmp_word.size() >0){
				line_count = tmp_word.size();
				formatted_word=tmp_word;
				formatted_word.append(" ");
				std::cout<<formatted_word<<std::endl;
				line_count = formatted_word.size();
			}
		}

		//handle words < size of width
		else if (line_count + words[i].size() <= width){
			line_count += words[i].size();
			formatted_word.append(words[i]);
			formatted_word.append(" ");
		}
		else{
			formatted_word.erase(formatted_word.size()-1, 1);
			formatted_words.push_back(formatted_word);
			formatted_word = words[i] + ' ';
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
		int spaces=width-lines[i].size();
		for (int j=0; j<spaces; ++j){
			fout<<" ";
		}
		fout<<" |"<<std::endl;
	}

	//print the bottom line
	print_line(width, fout);
}

void print_right_just(const std::vector<std::string> &lines,const int &width,std::ofstream &fout){
	//print the top line
	print_line(width, fout);

	//print middle lines
	for(int i=0; i<lines.size();++i){
		fout<<"| ";
		int spaces=width-lines[i].size();
		for (int j=0; j<spaces; ++j){
			fout<<" ";
		}
		fout<<lines[i];
		fout<<" |"<<std::endl;
	}

	//print the bottom line
	print_line(width, fout);
}

void print_full_just(const std::vector<std::string> &lines,const int &width,std::ofstream &fout){
	//print the top line
	print_line(width, fout);

	//print middle lines
	for(int i=0; i<lines.size();++i){
		fout<<"| ";
		fout<<lines[i];
		int spaces=width-lines[i].size();
		for (int j=0; j<spaces; ++j){
			fout<<" ";
		}
		fout<<" |"<<std::endl;
	}

	//print the bottom line
	print_line(width, fout);
}


void implement_style( std::vector<std::string> &lines, const std::string &style, std::ofstream &fout, const int &width){
	if(style=="flush_left"){
		print_left_just(lines,width,fout);
	}
	else if(style=="flush_right"){
		print_right_just(lines,width,fout);
	} 
	else if(style=="full_justify"){
		std::vector<std::string> modified_lines = full_justify(lines,width);
		print_full_just(modified_lines,width,fout);
	}
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
	implement_style(lines,style,fout,width);

 	return 0;
}

