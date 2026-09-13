#include <bits/stdc++.h>
using namespace std;

long vertexCount, edgeCount;
vector<pair<long, pair<long, long>>> edgeList;

long find_parent(vector<long> &parent, long vertex){
    if(parent[vertex] == vertex) return vertex;
    return parent[vertex] = find_parent(parent, parent[vertex]);
}

void union_set(vector<long> &parent, long vertex1, long vertex2){
    long root1 = find_parent(parent, vertex1);
    long root2 = find_parent(parent, vertex2);
    if(root1 != root2) parent[root1] = root2;
}

void kruskal(vector<pair<long, pair<long, long>>> &result){
    vector<long> parent(vertexCount + 1);
    for(long i = 1; i <= vertexCount; i++) parent[i] = i;

    sort(edgeList.begin(), edgeList.end());

    for(auto &edge : edgeList){
        long v1 = edge.second.first;
        long v2 = edge.second.second;
        if(find_parent(parent, v1) != find_parent(parent, v2)){
            result.push_back(edge);
            union_set(parent, v1, v2);
            if((long)result.size() == vertexCount - 1) return;
        }
    }
}

int main(){
    cin >> vertexCount >> edgeCount;

    for(long i = 0; i < edgeCount; i++){
        long u, v, w;
        cin >> u >> v >> w;
        edgeList.push_back({w, {u, v}});
    }

    vector<pair<long, pair<long, long>>> result;
    kruskal(result);

    long totalWeight = 0;
    cout << "\nKRUSKAL\n";
    for(auto &edge : result){
        cout << "v" << edge.second.first << " - v" << edge.second.second << " : " << edge.first << "\n";
        totalWeight += edge.first;
    }
    cout << "bobot spanning tree terkecil: " << totalWeight << "\n";

    return 0;
}