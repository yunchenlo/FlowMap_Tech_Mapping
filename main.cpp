#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <sstream>
#include <list> 
#include <stack>
#include <queue>

using namespace std;

#define INF 100

// register funtions
void read_aag(const string infile_name);
void topologicalSort();
int* BFS(int Start);
void labeling();
void printArray();
void delete_mem();

// global variable
int M=0, I=0, O=0, K=0;
int *adjacent_matrix = NULL;
list<int> *adj = NULL, *rev_adj = NULL; 
bool *input = NULL, *output = NULL;
stack<int> topo_Stack; // remember to eliminate PI nodes 
int *label = NULL;

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
	 cout << 
	     "usage: ./FlowMap.exe <input_file_name> <K> <output_file_name>" << endl;
	 return 1;
    }
    // Preprocessing
    read_aag(argv[1]);
    K = stoi(argv[2]);
    cout << "Input File: " << argv[1] << endl;
    cout << "K: " << argv[2] << endl;
    cout << "Output File: " << argv[3] << endl; 

    /*
    == Labeling Phase ==
    */
    topologicalSort();
    labeling();
    //BFS(6);

    /*
    == Mapping Phase ==
    */

    // Postprocessing


    printArray();
    delete_mem();
	return 0;
}
/*
void AddEdge(int from, int to, int capacity){

    
}
*/

void labeling()
{
	int p = 0;
	// initializing label array to -1, PI to 0
	for(int i = 0; i < M; i++){
		if(input[i])
			label[i] = 0;
		else
			label[i] = -1;	
		cout << label[i] << " ";
	}
	cout << endl;

	// by topological order, ommit one node for connecting network
	// debug :: using node(7) index(6)
	int current_node = 6;
	int *pred_ret;
	pred_ret = BFS(current_node);

	// find p by searching all parent of current node
	for(int i = 0; i < M; i++){
		if(pred_ret[i]>=0){
			p = (p < label[i]) ? label[i] : p;
		}
	}
	
	// Nt -> Nt' -> Nt''
	for(int i = 0; i < M; i++){
		if(p == label[i] && pred_ret[i]>=0)
			pred_ret[i] = -10;
	}

	int num_node = 0;
	bool set = false;
	for(int i = 0; i < M; i++){
		if(pred_ret[i] == -10 || pred_ret[i] > 0){
			if(pred_ret[i] == -10 && set == false){
				num_node ++;
				set = true;
			}
			else if (pred_ret[i] > 0){
				num_node ++;
			}
		}
	}

	cout << "num of nodes: "<< num_node << endl;
	int num_vertex = 2 * (num_node-1) + 2;
	cout << "num of vertices: "<< num_vertex << endl;
	std::vector<std::vector<int> > AdjMatrix;
	AdjMatrix.resize(M);
    for (int i = 0; i < M; i++)
        AdjMatrix[i].resize(M);

	// s:0, t(PO): num_vertex -1
	for (int i = 0; i < num_vertex-1; i++){
		// start from s to PI with INF
		if (i == 0){
			for (int j = 0; j < M; j++){
				if (input[j])
					AdjMatrix[i][j] = INF; // from i to j
			}
		}
		else if(i == num_vertex - 2 ){
			for (int j = 0; j < M; j++){
				//AddEdge(i, j, INF);
			}
		}
		//AddEdge(i, i + 1, INF);
	}

	cout << AdjMatrix[0][num_vertex-1] << endl;


	// debug print
	cout << "p: "<< p << endl;
	for (int j = 0; j < M; j++) {
        std::cout << pred_ret[j] << " ";
    }
    std::cout << std::endl;


}

void topologicalSortUtil(int v, bool visited[], stack<int> &topo_Stack) 
{ 
    // Mark the current node as visited. 
    visited[v] = true; 
  
    // Recur for all the vertices adjacent to this vertex 
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visited[*i]) 
            topologicalSortUtil(*i, visited, topo_Stack); 
  
    // Push current vertex to stack which stores result 
    topo_Stack.push(v); 
} 

void topologicalSort() 
{
    // Mark all the vertices as not visited 
    bool *visited = new bool[M]; 
    for (int i = 0; i < M; i++) 
        visited[i] = false; 
  
    // Call the recursive helper function to store Topological 
    // Sort starting from all vertices one by one 
    for (int i = 0; i < M; i++) 
      if (visited[i] == false) 
        topologicalSortUtil(i, visited, topo_Stack); 
  
    // Print contents of stack 
    while (topo_Stack.empty() == false) 
    { 
        cout << topo_Stack.top()+1 << " "; 
        topo_Stack.pop(); 
    } 
    cout << endl;
} 

int* BFS(int Start){
	int *color,             // 0:白色, 1:灰色, 2:黑色
        *distance,          // 0:起點, 無限大:從起點走不到的vertex
        *predecessor;       // -1:沒有predecessor, 表示為起點vertex
    color = new int[M];
    predecessor = new int[M];
    distance = new int[M];

    for (int i = 0; i < M; i++) {  // 初始化，如圖二(b)
        color[i] = 0;              // 0:白色;
        predecessor[i] = -1;       // -1表示沒有predecessor
        distance[i] = M+1;         // M個vertex, 
    }                              // 最長距離 distance = M -1條edge

    std::queue<int> q;
    int i = Start;

    for (int j = 0; j < M; j++) {  // j從0數到M-1, 因此j會走過graph中所有vertex
        if (color[i] == 0) {       // 第一次i會是起點vertex, 如圖二(c)
            color[i] = 1;          // 1:灰色
            distance[i] = 0;       // 每一個connected component的起點之距離設成0
            predecessor[i] = -1;    // 每一個connected component的起點沒有predecessor
            q.push(i);
            while (!q.empty()) {
                int u = q.front();                  // u 為新的搜尋起點
                for (std::list<int>::iterator itr = rev_adj[u].begin();        // for loop 太長
                     itr != rev_adj[u].end(); itr++) {                         // 分成兩段
                    if (color[*itr] == 0) {                // 若被「找到」的vertex是白色
                        color[*itr] = 1;                   // 塗成灰色, 表示已經被「找到」
                        distance[*itr] = distance[u] + 1;  // 距離是predecessor之距離加一
                        predecessor[*itr] = u;             // 更新被「找到」的vertex的predecessor
                        q.push(*itr);                      // 把vertex推進queue
                    }
                }
                q.pop();        // 把u移出queue
                color[u] = 2;   // 並且把u塗成黑色
            }
        }
        // 若一次回圈沒有把所有vertex走過, 表示graph有多個connected component
        // 就把i另成j, 繼續檢查graph中的其他vertex是否仍是白色, 若是, 重複while loop
        i = j;
    }

    // set the start point to -10
    predecessor[Start] = -10;
    
    return predecessor;

    /*
    for (int j = 0; j < M; j++) {
        std::cout << predecessor[j] << " ";
    }
    std::cout << std::endl;
	*/
}

void printArray(){
	for(int i = 0; i < M; i++){
    	for(int j = 0; j < M; j++){
    		cout << adjacent_matrix[i*M + j] << " ";
    	}
    	cout << endl;
    }
    cout << endl;
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
				case 0: break;
				case 1: M = stoi(s); break;
				case 2: I = stoi(s); break;
				case 3: O = stoi(s); break;
				default: cout << "default" << endl; break;
			}
			index ++;
		}
		
		// malloc adjacent matrix + input table + output table
		adjacent_matrix = new int[M*M];
		adj = new list<int>[M];
		rev_adj = new list<int>[M];
		input = new bool[M];
		output = new bool[M];
		label = new int[M];

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
		int *temp = new int[3]; //temp[0]:root|temp[1,2]:child
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
			adj[temp[1]].push_back(temp[0]);
			adj[temp[2]].push_back(temp[0]);
			rev_adj[temp[0]].push_back(temp[1]);
			rev_adj[temp[0]].push_back(temp[2]);
		}

		myfile.close();
	}
	else cout << "Unable to open file";
}

void delete_mem(){
	delete adjacent_matrix;
	delete input;
	delete output;
}
