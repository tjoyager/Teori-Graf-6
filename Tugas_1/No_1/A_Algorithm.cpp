#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<long,long>>> adjList;

void addEdge(long u, long v, long w){
    adjList[u].push_back({v, w});
    adjList[v].push_back({u, w});
}

double heuristic(int u, int end){
    return 0;
}

struct Node {
    long vertex;
    double f;
};

struct Compare {
    bool operator()(const Node &a, const Node &b){ return a.f > b.f; }
};

vector<long> aStar(long start, long end, long &pathCost, long vertexCount){
    vector<double> gScore(vertexCount + 1, DBL_MAX/2);
    vector<long> parent(vertexCount + 1, -1);
    vector<bool> closed(vertexCount + 1, false);

    priority_queue<Node, vector<Node>, Compare> open;
    gScore[start] = 0;
    open.push({start, heuristic((int)start, (int)end)});

    while(!open.empty()){
        Node cur = open.top(); open.pop();

        if(closed[cur.vertex]) continue;
        closed[cur.vertex] = true;

        if(cur.vertex == end) break;

        for(auto &edge : adjList[cur.vertex]){
            long next = edge.first;
            long w = edge.second;
            double tentativeG = gScore[cur.vertex] + w;

            if(tentativeG < gScore[next]){
                gScore[next] = tentativeG;
                parent[next] = cur.vertex;
                double f = tentativeG + heuristic((int)next, (int)end);
                open.push({next, f});
            }
        }
    }

    pathCost = (gScore[end] >= DBL_MAX/2) ? -1 : (long)gScore[end];

    vector<long> path;
    if(pathCost != -1){
        for(long v = end; v != -1; v = parent[v]) path.push_back(v);
        reverse(path.begin(), path.end());
    }
    return path;
}

int main(void){
    long vertexCount, edgeCount;
    cin >> vertexCount >> edgeCount;

    adjList.assign(vertexCount + 1, {});

    for(long i = 0; i < edgeCount; i++){
        long u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }

    long start, end;
    cin >> start >> end;

    long pathCost;
    vector<long> path = aStar(start, end, pathCost, vertexCount);

    if(pathCost == -1){
        cout << "\nTidak ada jalur dari v-" << start << " ke v-" << end << "\n";
    } else {
        cout << "\nJarak terpendek v-" << start << " -> v-" << end << " = " << pathCost << "\n";
    }

    return 0;
}