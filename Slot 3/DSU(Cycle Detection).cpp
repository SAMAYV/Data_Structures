#include<bits/stdc++.h>
using namespace std;

struct Edge 
{ 
    int src, dest; 
}; 
  
struct Graph 
{ 
    int V, E;  
    struct Edge* edge; 
}; 
  
struct subset 
{ 
    int parent; 
    int rank; 
}; 

struct Graph* createGraph(int V, int E) 
{ 
    struct Graph* graph =  new struct Graph; 
    graph->V = V; 
    graph->E = E; 
    graph->edge = new struct Edge [graph->E]; 
    return graph; 
} 
  
int find(struct subset subsets[], int i) 
{ 
    if (subsets[i].parent != i) 
        subsets[i].parent = find(subsets, subsets[i].parent); 
  
    return subsets[i].parent; 
} 

void Union(struct subset subsets[], int x, int y) 
{ 
    int xroot = find(subsets, x); 
    int yroot = find(subsets, y); 
  
    if (subsets[xroot].rank < subsets[yroot].rank) 
        subsets[xroot].parent = yroot; 
    else if (subsets[xroot].rank > subsets[yroot].rank) 
        subsets[yroot].parent = xroot; 
    else
    { 
        subsets[yroot].parent = xroot; 
        subsets[xroot].rank++; 
    } 
} 
  
int isCycle( struct Graph* graph ) 
{ 
    int V = graph->V; 
    int E = graph->E; 

    struct subset *subsets = new struct subset [V]; 
  
    for (int v = 0; v < V; ++v) 
    { 
        subsets[v].parent = v; 
        subsets[v].rank = 0; 
    } 
  
    for(int e = 0; e < E; ++e) 
    { 
        int x = find(subsets, graph->edge[e].src); 
        int y = find(subsets, graph->edge[e].dest); 
  
        if (x == y) 
            return 1; 
  
        Union(subsets, x, y); 
    } 
    return 0; 
} 
  
int main() 
{ 
    int V,E;
    cout<<"Enter number of vertices and edges of graph respectively"<<endl;
    cin>>V>>E;
    struct Graph* graph = createGraph(V, E); 
  	for(int i=0;i<E;i++)
  	{
  		int x,y;
  		cout<<"Enter vertices of "<<i<<"th edge"<<endl;
  		cin>>x>>y;
  		graph->edge[i].src = x;
  		graph->edge[i].dest = y;
  	}
    if (isCycle(graph)) 
        cout<<"Graph contains cycle"<<endl; 
    else
        cout<<"Graph doesn't contain cycle"<<endl; 
  
    return 0; 
} 
