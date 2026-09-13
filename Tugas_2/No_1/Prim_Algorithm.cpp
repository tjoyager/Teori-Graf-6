#include <bits/stdc++.h>
using namespace std;

long vertexCount, edgeCount;
vector<vector<pair<long,long>>> adjList;

void addEdge(long u, long v, long w){
    adjList[u].push_back(make_pair(v, w));
    adjList[v].push_back(make_pair(u, w));
}

typedef tuple<long,long,long> PQEntry;

void prim(long start, vector<tuple<long,long,long>> &result, long &totalWeight){
    vector<bool> visited(vertexCount + 1, false);
    priority_queue<PQEntry, vector<PQEntry>, greater<PQEntry>> pq;

    pq.push(make_tuple(0, start, -1));
    totalWeight = 0;

    while(!pq.empty()){
        PQEntry top = pq.top(); pq.pop();
        long w = get<0>(top);
        long u = get<1>(top);
        long parent = get<2>(top);

        if(visited[u]) continue;
        visited[u] = true;
        totalWeight += w;

        if(parent != -1) result.push_back(make_tuple(parent, u, w));

        for(size_t i = 0; i < adjList[u].size(); i++){
            long v = adjList[u][i].first;
            long weight = adjList[u][i].second;
            if(!visited[v]) pq.push(make_tuple(weight, v, u));
        }
    }
}

int main(){
    cin >> vertexCount >> edgeCount;
    adjList.assign(vertexCount + 1, vector<pair<long,long>>());

    for(long i = 0; i < edgeCount; i++){
        long u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }

    long start;
    cout << "Vertex pertama: ";
    cin >> start;

    vector<tuple<long,long,long>> result;
    long totalWeight;
    prim(start, result, totalWeight);

    cout << "\nPRIM\n";
    for(size_t i = 0; i < result.size(); i++){
        long u = get<0>(result[i]);
        long v = get<1>(result[i]);
        long w = get<2>(result[i]);
        cout << "v" << u << " - v" << v << " : " << w << "\n";
    }
    cout << "bobot spanning tree terkecil: " << totalWeight << "\n";

    return 0;
}
