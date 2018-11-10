#include <iostream>
#include <string>
using namespace std;

#define INF 10000
#include "Graph_FlowNetWorks.h"

int main(){
    Graph_FlowNetWorks g11(8);

    g11.AddEdge(0, 1, INF);g11.AddEdge(0, 2, INF);g11.AddEdge(0, 3, INF);
    g11.AddEdge(1, 4, 1);g11.AddEdge(2, 5, 1);g11.AddEdge(3, 6, 1);
    g11.AddEdge(4, 7, INF);g11.AddEdge(5, 7, INF);g11.AddEdge(6, 7, INF);
    std::vector<std::vector<int>> Res_ret;
    Res_ret = g11.FordFulkerson(0, 7);    // 指定source為vertex(0), termination為vertex(5)
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(j <= i)
            	Res_ret[i][j] = 0;
        }
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(j <= i)
            	Res_ret[i][j] = Res_ret[j][i];
        }
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(j > i)
            	Res_ret[i][j] = 0;
        }
    }
    std::vector<bool> visited;
    visited = g11.BFS(Res_ret,7);
    
    for(int i = 0; i < 8; i++){
    	std::cout << visited[i] << " ";
    }
    std::cout << std::endl;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            std::cout << Res_ret[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}