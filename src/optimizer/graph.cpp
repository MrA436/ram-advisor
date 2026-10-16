
#include<iostream>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    const int V=5;
    int dist[V];
    bool visited[V]={false};
// Vertex 0 = 8 GB, 1 = 16 GB, 2 = 24 GB,
// Vertex 3 = 32 GB, 4 = 64 GB
    int ram[V]={8,16,24,32,64};
    int inventory[V]={10,6,4,3,2};
    int graph[V][V]={0};
    graph[0][1]=2000;
    graph[0][2]=3000;
    graph[0][3]=7500;
    graph[0][4]=9000;
    graph[1][2]=4000;
    graph[1][3]=4500;
    graph[1][4]=5000;
    graph[2][3]=2500;
    graph[3][4]=5000;

cout << "\nAvailable RAM Inventory:\n";
for(int i=0;i<V;i++){
    cout << ram[i] << " GB RAM: "
         << inventory[i] << " sticks available\n";
}
// NEW: Ask the user for current and target RAM
    int currentRAM, targetRAM;
    cout<<"Available RAM: 8, 16, 24, 32, 64 GB\n";
    cout<<"Enter your current RAM (GB): ";
    cin>>currentRAM;
    cout<<"Enter your target RAM (GB): ";
    cin>>targetRAM;
// NEW: Convert RAM capacities into vertex numbers
    int source=-1, destination=-1;
    for(int i=0;i<V;i++){
        if(ram[i]==currentRAM){
            source=i;
        }
        if(ram[i]==targetRAM){
            destination=i;
        }
    }
// NEW: Check whether the inputs are valid
    if(source==-1 || destination==-1){
        cout<<"Invalid RAM capacity. Please choose from the list.\n";
        return 1;
    }
    if(destination<source){
        cout<<"This prototype currently supports upgrades to higher capacities only.\n";
        return 1;
    }
// Initialize distances and parents
    int parent[V];
    for(int i=0;i<V;i++){
        dist[i]=INT_MAX;
        parent[i]=-1;
    }
// CHANGED: Start from the user's selected RAM
    dist[source]=0;
// Dijkstra's algorithm - same structure as your code
    for(int count=0;count<V;count++){
        int u=-1;
// Find the unvisited vertex with the smallest distance
        for(int i=0;i<V;i++){
            if(!visited[i] && dist[i]!=INT_MAX &&
               (u==-1 || dist[i]<dist[u])){
                u=i;
            }
        }
// Stop if no reachable vertex remains
        if(u==-1){
            break;
        }
        visited[u]=true;
// Check every outgoing edge from u
        for(int v=0;v<V;v++){
            if(graph[u][v]>0 && !visited[v]){
                int newcost=dist[u]+graph[u][v];
                if(newcost<dist[v]){
                    dist[v]=newcost;
                    parent[v]=u;
                }
            }
        }
    }
// NEW: Show the result for the selected target
    cout<<"\nCurrent RAM: "<<currentRAM<<" GB\n";
    cout<<"Target RAM: "<<targetRAM<<" GB\n";
    if(dist[destination]==INT_MAX){
        cout<<"No upgrade route found.\n";
        return 0;
    }
// NEW: Reconstruct the cheapest route
    vector<int> path;
    for(int v=destination;v!=-1;v=parent[v]){
        path.push_back(v);
    }
    reverse(path.begin(),path.end());
    cout<<"\nCheapest upgrade route:\n";
    for(int i=0;i<(int)path.size();i++){
        cout<<ram[path[i]]<<" GB";
        if(i<(int)path.size()-1){
            cout<<" -> ";
        }
    }
    cout<<"\nMinimum estimated cost: Rs. "
        <<dist[destination]<<'\n';
    return 0;
}
