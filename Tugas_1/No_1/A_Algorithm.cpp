#include <bits/stdc++.h>
using namespace std;

typedef pair<double, long> pPair;

struct cell {
    long parent;
    double f, g, h;
};

vector<vector<pair<long,long>>> adjList;
vector<pair<double,double>> coord;
long vertexCount, edgeCount;

double calculateHValue(long u, long end){
    double dx = coord[u].first  - coord[end].first;
    double dy = coord[u].second - coord[end].second;
    return sqrt(dx * dx + dy * dy);
}

bool isValid(long v){
    return v >= 1 && v <= vertexCount;
}

bool isDestination(long v, long end){
    return v == end;
}

void tracePath(vector<cell> &cellDetails, long end){
    printf("Jalur: ");
    long v = end;
    stack<long> path;

    while(cellDetails[v].parent != v){
        path.push(v);
        v = cellDetails[v].parent;
    }
    path.push(v);

    while(!path.empty()){
        printf("v%ld", path.top());
        path.pop();
        if(!path.empty()) printf(" -> ");
    }
    printf("\n");
}

void aStarSearch(long start, long end){


    vector<bool> closedList(vertexCount + 1, false);
    vector<cell> cellDetails(vertexCount + 1);

    for(long i = 1; i <= vertexCount; i++){
        cellDetails[i].f = DBL_MAX;
        cellDetails[i].g = DBL_MAX;
        cellDetails[i].h = DBL_MAX;
        cellDetails[i].parent = -1;
    }

    long i = start;
    cellDetails[i].f = 0.0;
    cellDetails[i].g = 0.0;
    cellDetails[i].h = 0.0;
    cellDetails[i].parent = i;

    set<pPair> openList;
    openList.insert(make_pair(0.0, i));

    bool foundDest = false;

    while(!openList.empty()){
        pPair p = *openList.begin();
        openList.erase(openList.begin());

        i = p.second;
        closedList[i] = true;

        if(isDestination(i, end) == true){
            tracePath(cellDetails, end);
            printf("Total cost: %.0f\n", cellDetails[end].g);
            foundDest = true;
            return;
        }

        for(auto &edge : adjList[i]){
            long next = edge.first;
            long w = edge.second;

            if(closedList[next] == false){
                double gNew = cellDetails[i].g + w;
                double hNew = calculateHValue(next, end);
                double fNew = gNew + hNew;

                if(cellDetails[next].f == DBL_MAX || cellDetails[next].f > fNew){
                    openList.insert(make_pair(fNew, next));
                    cellDetails[next].f = fNew;
                    cellDetails[next].g = gNew;
                    cellDetails[next].h = hNew;
                    cellDetails[next].parent = i;
                }
            }
        }
    }

    if(foundDest == false)
        printf("Tidak ada jalur ke tujuan\n");
}

int main(void){
    cin >> vertexCount >> edgeCount;

    adjList.assign(vertexCount + 1, {});
    coord.assign(vertexCount + 1, make_pair(0.0, 0.0));

    for(long e = 0; e < edgeCount; e++){
        long u, v, w;
        cin >> u >> v >> w;
        adjList[u].push_back(make_pair(v, w));
        adjList[v].push_back(make_pair(u, w));
    }

    for(long i = 1; i <= vertexCount; i++){
        cin >> coord[i].first >> coord[i].second;
    }

    long start, end;
    cin >> start >> end;

    aStarSearch(start, end);

    return 0;
}