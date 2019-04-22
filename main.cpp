#include "mainwindow.h"
#include <QApplication>
#define V 9
#include "iostream"
using namespace std;
void convertirTableroEnGrafo(int matriz[2][2],int resultado[4][4]){
    cout<<"VOY A EMPEZAR"<<endl;
    for (int i=0;i<2;i++){
        //cout<<"VOY A EMPEZAR2"<<endl;

        for (int j=0;j<2;j++){
           // cout<<"VOY A EMPEZAR3"<<endl;
            for (int x=0;x<4;x++){
                cout<<"VOY A EMPEZAR2"<<endl;

                for (int y=0;y<4;y++){
                    cout<<"VOY A EMPEZAR3"<<endl;
        if (x+y==i+j){
        resultado[x][y]=0;
        }
        else if (matriz[i][j]==2) {
           // resultado
        }

                }
            }

        }
    }
}

int minDistance(int dist[], bool sptSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;

   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}
// A utility function to print the constructed distance array
int printSolution(int dist[], int n)
{
   printf("Vertex   Distance from Source\n");
   for (int i = 0; i < V; i++)
      printf("%d tt %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
     int dist[V];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i

     bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized

     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

     // Distance of source vertex from itself is always 0
     dist[src] = 0;

     // Find shortest path for all vertices
     for (int count = 0; count < V-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in the first iteration.
       int u = minDistance(dist, sptSet);

       // Mark the picked vertex as processed
       sptSet[u] = true;

       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < V; v++)

         // Update dist[v] only if is not in sptSet, there is an edge from
         // u to v, and total weight of path from src to  v through u is
         // smaller than current value of dist[v]
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }

     // print the constructed distance array
     printSolution(dist, V);
}
int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
    /* Let us create the example graph discussed above */
//       int graph[V][V] = {{0, 0, 0, 0, 0, 0, 0, 0,  0},
//                          {0, 0, 0, 0, 0, 0, 0, 0,  0},
//                          {0, 0, 0, 0, 0, 0, 0, 0,  0},
//                          {0, 0, 0, 0, 0, 0, 0, 0,  0},
//                          {0, 0, 0, 0, 0, 0, 0, 0,  0},
//                          {0, 0, 0, 0, 0, 0, 0, 0,  0},
//                          {0, 0, 0, 0, 0, 0, 0, 0,  0},
//                          {0, 0, 0, 0, 0, 0, 0, 0,  0},
//                          {0, 0, 0, 0, 0, 0, 0, 0,  0}
//                         };

//        dijkstra(graph, 0);
    int graph[3][3] = {{1,2,3},{4,5,6,},{7,8,9,}};
    int graph2[9][9] = {{},{},{},{},{},{},{},{},{}};
    //convertirTableroEnGrafo(graph,graph2);
    for (int i=0;i<9;i++){
cout<<"{";
        for (int j=0;j<9;j++){
            cout<<"["<<graph2[i][j]<<"]";
        }
        cout<<"}    ";
    }

}
