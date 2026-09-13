#include <bits/stdc++.h>
using namespace std;

struct Edge { long u, v, w; };

bool bellmanFord(vector<Edge> &edges, long start, vector<long> &dist, long V){
    dist.assign(V + 1, LONG_MAX);
    dist[start] = 0;

    for(long i = 1; i <= V - 1; i++){
        for(auto &e : edges){
            if(dist[e.u] != LONG_MAX && dist[e.u] + e.w < dist[e.v])
                dist[e.v] = dist[e.u] + e.w;
            if(dist[e.v] != LONG_MAX && dist[e.v] + e.w < dist[e.u])
                dist[e.u] = dist[e.v] + e.w;
        }
    }

    for(auto &e : edges){
        if(dist[e.u] != LONG_MAX && dist[e.u] + e.w < dist[e.v]) return false;
        if(dist[e.v] != LONG_MAX && dist[e.v] + e.w < dist[e.u]) return false;
    }
    return true;
}


int main(void){
    long vertexCount, edgeCount;
    cin >> vertexCount >> edgeCount;

    vector<Edge> edges(edgeCount);
    for(long i = 0; i < edgeCount; i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    long start, end;
    cin >> start >> end;

    vector<long> dist;
    bool noNegativeCycle = bellmanFord(edges, start, dist, vertexCount);
    if(!noNegativeCycle){
        cout << "Graph mengandung negative cycle\n";
        return 0;
    }

    cout << "\nJarak terpendek v-" << start << " -> v-" << end << " = " << dist[end] << "\n";

    return 0;
}
