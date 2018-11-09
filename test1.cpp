// C++ code
#include <iostream>
#include <vector>
#include <list>
#include <queue>

class Graph{
private:
    int num_vertex;
    std::vector< std::list<int> > AdjList;
    int *color,             // 0:白色, 1:灰色, 2:黑色
        *distance,          // 0:起點, 無限大:從起點走不到的vertex
        *predecessor;       // -1:沒有predecessor, 表示為起點vertex
public:
    Graph():num_vertex(0){};           // default constructor
    Graph(int N):num_vertex(N){        // constructor with input: number of vertex
        // initialize Adjacency List
        AdjList.resize(num_vertex);
    };
    void AddEdge(int from, int to);
    void BFS(int Start);
};

void Graph::AddEdge(int from, int to){
    AdjList[to].push_back(from);
}

void Graph::BFS(int Start){

    color = new int[num_vertex];
    predecessor = new int[num_vertex];
    distance = new int[num_vertex];

    for (int i = 0; i < num_vertex; i++) {  // 初始化，如圖二(b)
        color[i] = 0;                       // 0:白色;
        predecessor[i] = -1;                // -1表示沒有predecessor
        distance[i] = num_vertex+1;         // num_vertex個vertex, 
    }                                       // 最長距離 distance = num_vertex -1條edge

    std::queue<int> q;
    int i = Start;

    for (int j = 0; j < num_vertex; j++) {  // j從0數到num_vertex-1, 因此j會走過graph中所有vertex
        if (color[i] == 0) {                // 第一次i會是起點vertex, 如圖二(c)
            color[i] = 1;                   // 1:灰色
            distance[i] = 0;                // 每一個connected component的起點之距離設成0
            predecessor[i] = -1;            // 每一個connected component的起點沒有predecessor
            q.push(i);
            while (!q.empty()) {
                int u = q.front();                  // u 為新的搜尋起點
                for (std::list<int>::iterator itr = AdjList[u].begin();        // for loop 太長
                     itr != AdjList[u].end(); itr++) {                         // 分成兩段
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
    for (int j = 0; j < num_vertex; j++) {
        std::cout << predecessor[j] << " ";
    }
    std::cout << std::endl;
}

int main(){
    /*
    Graph g1(9);    
    // 建立出圖二(a)的Adjacency List
    g1.AddEdgeList(0, 1);g1.AddEdgeList(0, 2);g1.AddEdgeList(0, 3);
    g1.AddEdgeList(1, 0);g1.AddEdgeList(1, 4);
    g1.AddEdgeList(2, 0);g1.AddEdgeList(2, 4);g1.AddEdgeList(2, 5);g1.AddEdgeList(2, 6);g1.AddEdgeList(2, 7);
    g1.AddEdgeList(3, 0);g1.AddEdgeList(3, 7);
    g1.AddEdgeList(4, 1);g1.AddEdgeList(4, 2);g1.AddEdgeList(4, 5);
    g1.AddEdgeList(5, 2);g1.AddEdgeList(5, 4);g1.AddEdgeList(5, 8);
    g1.AddEdgeList(6, 2);g1.AddEdgeList(6, 7);g1.AddEdgeList(6, 8);
    g1.AddEdgeList(7, 2);g1.AddEdgeList(7, 3);g1.AddEdgeList(7, 6);
    g1.AddEdgeList(8, 5);g1.AddEdgeList(8, 6);
    */
    Graph g(18); 
    g.AddEdge(0, 13); 
    g.AddEdge(0, 10);
    g.AddEdge(1, 6);  
    g.AddEdge(2, 6);
    g.AddEdge(2, 7);
    g.AddEdge(3, 7);
    g.AddEdge(4, 8);
    g.AddEdge(5, 8);

    g.AddEdge(6, 17);
    g.AddEdge(6, 9);
    g.AddEdge(7, 9);
    g.AddEdge(7, 12);
    g.AddEdge(8, 11);
    g.AddEdge(8, 15);

    g.AddEdge(9, 10);
    g.AddEdge(9, 11);

    g.AddEdge(10, 14);
    g.AddEdge(11, 13);
    g.AddEdge(11, 12);
    g.AddEdge(12, 14);
    g.AddEdge(12, 15);

    g.AddEdge(13, 16);
    g.AddEdge(14, 16);
    g.AddEdge(15, 17);

    g.BFS(6);    

    return 0;
}