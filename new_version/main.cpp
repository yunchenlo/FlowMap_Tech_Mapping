#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <sstream>
#include <list> 
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

#define INF 10000

void read_aag(const string infile_name);
void topologicalSort();
int* BFS(int Start);
void labeling();



// global variable
int M=0, I=0, O=0, K=0;
list<int> *adj = NULL, *rev_adj = NULL, *kLUT_list = NULL; 
bool *input = NULL, *output = NULL;
stack<int> topo_Stack; 
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

    topologicalSort();

    labeling();

}

int* BFS(int Start){
	int *color,             // 0:白色, 1:灰色, 2:黑色
        *distance,          // 0:起點, 無限大:從起點走不到的vertex
        *predecessor;       // -1:沒有predecessor, 表示為起點vertex
    color = new int[M+1];
    predecessor = new int[M+1];
    distance = new int[M+1];

    for (int i = 0; i < M+1; i++) {  // 初始化，如圖二(b)
        color[i] = 0;              // 0:白色;
        predecessor[i] = -1;       // -1表示沒有predecessor
        distance[i] = M+2;         // M個vertex, 
    }                              // 最長距離 distance = M -1條edge

    std::queue<int> q;
    int i = Start;

    for (int j = 0; j < M+1; j++) {  // j從0數到M-1, 因此j會走過graph中所有vertex
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
  
    // Push current vertex to stack which stores result (except primary input)
    
    if(!input[v] && v!=0)
	    topo_Stack.push(v); 
} 

void topologicalSort() 
{
    // Mark all the vertices as not visited 
    bool *visited = new bool[M+1]; 
    for (int i = 0; i < M+1; i++) 
        visited[i] = false; 
  
    // Call the recursive helper function to store Topological 
    // Sort starting from all vertices one by one 
    for (int i = 0; i < M+1; i++) 
      if (visited[i] == false) 
        topologicalSortUtil(i, visited, topo_Stack); 
    /*
    while (topo_Stack.empty() == false) 
    { 
    	cout << "current_node" << topo_Stack.top() << " "; 
	    cout << endl;

	    topo_Stack.pop(); 
    }
    */

} 

void labeling()
{
	// initializing label array to -1, PI to 0
	for(int i = 0; i < M; i++){
		if(input[i])
			label[i] = 0;
		else
			label[i] = -1;
	}

	while (topo_Stack.empty() == false) 
    { 
    	cout << "=================" << endl;
        cout << "current_node" << topo_Stack.top() << " "; 
	    cout << endl;
	    topo_Stack.pop(); 

	    int p = 0;

	    
	    int current_node = topo_Stack.top();
	    int *pred_ret;
		pred_ret = BFS(current_node);

	    for(int i = 0; i < M; i++){
			if(pred_ret[i]>=0){
				p = (p < label[i]) ? label[i] : p;
			}
		}
    }

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
		adj = new list<int>[M+1];
		rev_adj = new list<int>[M+1];
		kLUT_list = new list<int>[M+1];
		input = new bool[M+1];
		output = new bool[M+1];
		label = new int[M+1];

		for (int i = 0; i < M; i++){
			input[i] = false;
			output[i] = false;
		}

		// fill in the input table
		for (int i = 0; i < I; i++){
			getline (myfile,line);
			input[stoi(line)] = true;
		}
		// fill in the output table
		for (int i = 0; i < O; i++){
			getline (myfile,line);
			output[stoi(line)] = true;
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
					case 0: temp[0] = stoi(s); break;
					case 1: temp[1] = stoi(s); break;
					case 2: temp[2] = stoi(s); break;
					default: cout << "default" << endl; break;
				}
				index ++;
			}
			adj[temp[1]].push_back(temp[0]);
			adj[temp[2]].push_back(temp[0]);
			rev_adj[temp[0]].push_back(temp[1]);
			rev_adj[temp[0]].push_back(temp[2]);
		}

		myfile.close();
	}
	else cout << "Unable to open file";
}