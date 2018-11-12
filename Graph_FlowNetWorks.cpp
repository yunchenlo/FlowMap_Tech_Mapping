#include "Graph_FlowNetWorks.h"

Graph_FlowNetWorks::Graph_FlowNetWorks(int n):num_vertex(n){
    // constructor
    AdjMatrix.resize(num_vertex);
    for (int i = 0; i < num_vertex; i++)
        AdjMatrix[i].resize(num_vertex);
}

std::vector<bool> Graph_FlowNetWorks::BFS(std::vector<std::vector<int> > matrix, int start){
    std::vector<bool> visited(matrix.size(), false);
    std::queue<int> Q;
    Q.push(start);

    Q.push(start);
    visited[start] = true;
    int count = 1;

    while(!Q.empty()){
        int top = Q.front(); Q.pop();

        for (int i = 0; i < matrix.size(); ++i){
            if(matrix[top][i] != 0 && (! visited[i]) ){
                Q.push(i);
                visited[i] = true;
                count++;
            }
        }
    }
    return visited;
}

bool Graph_FlowNetWorks::BFSfindExistingPath(std::vector<std::vector<int> > graph, 
                                             int *predecessor, int s, int t){
    int visited[num_vertex];

    for (int i = 0; i < num_vertex; i++){
        visited[i] = 0;     // 0 表示還沒有被找到
        predecessor[i] = -1;
    }

    std::queue<int> queue;
    // BFS 從 s 開始, 也可以規定s一律訂成vertex(0)
    queue.push(s);
    visited[s] = 1;
    while (!queue.empty()) {
        int exploring = queue.front();
        for (int j = 0; j < num_vertex; j++) {
            if (graph[exploring][j]!=0 && visited[j]==0) {
                queue.push(j);
                visited[j] = 1;
                predecessor[j] = exploring;
            }
        }
        queue.pop();
    }
    return (visited[t] == 1);   // 若t有被visited, 表示有path從s到t
                                // 也可以用 if (predecessor[t] != -1) 判斷
}

int Graph_FlowNetWorks::MinCapacity(std::vector<std::vector<int>> graph, 
                                    int *predecessor, int t){
    int min = 100;      // 確保min會更新, 假設graph上的capacity都小於100

    // 用predecessor[idx] 和 idx 表示一條edge
    // 找到在從s到t的path上, capacity最小的值, 存入min
    for (int idx = t; predecessor[idx] != -1; idx = predecessor[idx]){
        if (graph[predecessor[idx]][idx]!=0 && graph[predecessor[idx]][idx] < min) {
            min = graph[predecessor[idx]][idx];
        }
    }
    return min;
}

std::vector<int> Graph_FlowNetWorks::FordFulkerson(int source, int termination){

    // residual networks的初始狀態等於AdjMatrix, 見圖五(a)
    std::vector<std::vector<int>> graphResidual(AdjMatrix);    
                                              
    int predecessor[num_vertex];

    // BFS finds augmenting path,
    while (BFSfindExistingPath(graphResidual, predecessor, source, termination)) {
        int mincapacity = MinCapacity(graphResidual, predecessor, termination);
        maxflow = maxflow + mincapacity;
        for (int Y = termination; Y != source; Y = predecessor[Y]){
            // 更新 residual graph
            int X = predecessor[Y];
            graphResidual[X][Y] -= mincapacity;
            graphResidual[Y][X] += mincapacity;
        }
    }

    //traverse node, and push index into vector
    vector<int> answer(0, 0);
    vector<int> visit(num_vertex, 0); 

    queue<int> q;
    q.push(0);
    visit[0] = 1;

    while(!q.empty())
    {
    int i = q.front(); q.pop();
      
    for(int j=0; j<num_vertex; j++)
    {
      if(graphResidual[i][j] && !visit[j])
      {
        q.push(j);
        visit[j] = 1;
      }
    }
    }

    for(int i=0; i<num_vertex; i++)
    {
        if(!visit[i]){
            //std::cout << i << " ";
            answer.push_back(i);
        }
    } 
    //std::cout << std::endl;

    //std::cout << "Possible Maximum Flow: " << maxflow << std::endl;
    return answer;
}
void Graph_FlowNetWorks::AddEdge(int from, int to, int capacity){

    AdjMatrix[from][to] = capacity;
}