#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <sstream>

using namespace std;

void read_aag(const string infile_name);

int M=0, I=0, O=0;
int *adjacent_matrix = NULL;
bool *input = NULL, *output = NULL;

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
	 cout << 
	     "usage: ./kLUT <input_file_name> <K> <output_file_name>" << endl;
	 return 1;
    }

    read_aag(argv[1]);
    for(int i = 0; i < M; i++){
    	for(int j = 0; j < M; j++){
    		cout << adjacent_matrix[i*M + j] << " ";
    	}
    	cout << endl;
    }
    cout << endl;
	return 0;
}


void read_aag(const string infile_name)
{
	string line;
	ifstream myfile(infile_name);
	vector<string> tokens;
	if (myfile.is_open())
	{
		// read in m, i, o
		getline (myfile,line);
		istringstream buf(line);
		std::istream_iterator<std::string> beg(buf), end;
		std::vector<std::string> tokens(beg, end);
		int index = 0;
		for(auto& s: tokens){
			switch(index){
				case 0: cout << "0 " << s << endl; break;
				case 1: M = stoi(s); break;
				case 2: I = stoi(s); break;
				case 3: O = stoi(s); break;
				default: cout << "default" << endl; break;
			}
			index ++;
		}
		
		// malloc adjacent matrix + input table + output table
		adjacent_matrix = new int[M*M];
		input = new bool[M];
		output = new bool[M];

		for (int i = 0; i < M*M; i++){
			adjacent_matrix[i] = 0;
		}
		for (int i = 0; i < M; i++){
			input[i] = false;
			output[i] = false;
		}

		// fill in the input table
		for (int i = 0; i < I; i++){
			getline (myfile,line);
			input[stoi(line)-1] = true;
		}
		// fill in the output table
		for (int i = 0; i < O; i++){
			getline (myfile,line);
			output[stoi(line)-1] = true;
		}
		// fill in adjacent matrix
		int *temp = new int[3];
		while(getline (myfile,line)){
			//cout << line << '\n';
			istringstream buf(line);
			std::istream_iterator<std::string> beg(buf), end;
			std::vector<std::string> tokens(beg, end);
			index = 0;
			for(auto& s: tokens){
				switch(index){
					case 0: temp[0] = stoi(s)-1; break;
					case 1: temp[1] = stoi(s)-1; break;
					case 2: temp[2] = stoi(s)-1; break;
					default: cout << "default" << endl; break;
				}
				index ++;
			}
			adjacent_matrix[temp[0]*M + temp[1]] = 1;
			adjacent_matrix[temp[0]*M + temp[2]] = 1;
		}

		myfile.close();
	}
	else cout << "Unable to open file";
}