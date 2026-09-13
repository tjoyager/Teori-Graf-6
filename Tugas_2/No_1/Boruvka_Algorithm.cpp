#include <bits/stdc++.h>
using namespace std;

long vertexCount, edgeCount;
vector<array<long,3>> edges;

long find_parent(vector<long> &parent, long i){
    if(parent[i] == i) return i;
    return parent[i] = find_parent(parent, parent[i]);
}

void union_set(vector<long> &parent, vector<long> &rank_, long x, long y){
    long xroot = find_parent(parent, x);
    long yroot = find_parent(parent, y);
    if(rank_[xroot] < rank_[yroot]) parent[xroot] = yroot;
    else if(rank_[xroot] > rank_[yroot]) parent[yroot] = xroot;
    else { parent[yroot] = xroot; rank_[xroot]++; }
}

void boruvka(vector<array<long,3>> &result, long &totalWeight){
    vector<long> parent(vertexCount + 1), rank_(vertexCount + 1, 0);
    for(long i = 1; i <= vertexCount; i++) parent[i] = i;

    long numComponents = vertexCount;
    totalWeight = 0;

    while(numComponents > 1){
        vector<long> cheapest(vertexCount + 1, -1);

        for(long i = 0; i < edgeCount; i++){
            long u = edges[i][0], v = edges[i][1], w = edges[i][2];
            long setU = find_parent(parent, u);
            long setV = find_parent(parent, v);

            if(setU == setV) continue;

            if(cheapest[setU] == -1 || edges[cheapest[setU]][2] > w) cheapest[setU] = i;
            if(cheapest[setV] == -1 || edges[cheapest[setV]][2] > w) cheapest[setV] = i;
        }

        for(long i = 1; i <= vertexCount; i++){
            if(cheapest[i] != -1){
                long u = edges[cheapest[i]][0];
                long v = edges[cheapest[i]][1];
                long w = edges[cheapest[i]][2];
                long setU = find_parent(parent, u);
                long setV = find_parent(parent, v);

                if(setU != setV){
                    totalWeight += w;
                    result.push_back({u, v, w});
                    union_set(parent, rank_, setU, setV);
                    numComponents--;
                }
            }
        }
    }
}

int main(){
    cin >> vertexCount >> edgeCount;

    for(long i = 0; i < edgeCount; i++){
        long u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<array<long,3>> result;
    long totalWeight;
    boruvka(result, totalWeight);

    cout << "\nBORUVKA\n";
    for(auto &e : result){
        cout << "v" << e[0] << " - v" << e[1] << " : " << e[2] << "\n";
    }
    cout << "bobot spanning tree terkecil: " << totalWeight << "\n";

    return 0;
}
