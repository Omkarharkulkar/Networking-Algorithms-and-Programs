#include<stdio.h>
#include<iostream>

using namespace std; 
                                           
struct Node
{
    unsigned distance[6];
    unsigned from[6];
}RoutingTable[10];

int main()
{
    cout<<"\n\n-------------------- Distance Vector Routing Algorithm----------- ";
    int costMatrix[6][6];
    int nodes, i, j, k;
    cout<<"\n\n Enter the number of nodes : ";
    cin>>nodes; //Enter the nodes
    cout<<"\n Enter the cost matrix : \n" ;
    
    for(i = 0; i < nodes; i++)
     {
        for(j = 0; j < nodes; j++)
        {
            cin>>costMatrix[i][j];
            costMatrix[i][i] = 0;
            RoutingTable[i].distance[j] = costMatrix[i][j]; //initialise the distance equal to cost matrix
            RoutingTable[i].from[j] = j;
        }
    }
    
    for(i = 0; i < nodes; i++) //We choose arbitrary vertex k and we calculate the
            //direct distance from the node i to k using the cost matrix and add the distance from k to node j
        for(j = i+1; j < nodes; j++)
            for(k = 0; k < nodes; k++)
                if(RoutingTable[i].distance[j] > costMatrix[i][k] + RoutingTable[k].distance[j])
                {   //We calculate the minimum distance
                    RoutingTable[i].distance[j] = RoutingTable[i].distance[k] + RoutingTable[k].distance[j];
                    RoutingTable[j].distance[i] = RoutingTable[i].distance[j];
                    RoutingTable[i].from[j] = k;
                    RoutingTable[j].from[i] = k;
                }
                
        for(i = 0; i < nodes; i++)
        {
            cout<<"\n\n For router: "<<i+1;
            for(j = 0; j < nodes; j++)
                cout<<"\t\n node "<<j+1<<" via "<<RoutingTable[i].from[j]+1<<" Distance "<<RoutingTable[i].distance[j];
        }
        
    cout<<" \n\n ";
    return 0;
}
