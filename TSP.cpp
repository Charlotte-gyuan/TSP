/***************************
** Program: TSP.cpp
** This is the implementation for the tsp algorithm with greedy construction and improved 2-opt optimization
***************************************/

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#define MAXNODES 1000

int D[MAXNODES][MAXNODES];//distance between two points
int N;                    // total number of points
std::vector<int> route;   //store an optimal route of points.


//a,b are two points on an edge, cost is the weight on an edge
struct Edge
{
    int a, b;
    int cost;
    Edge(int a, int b, int cost) : a(a), b(b), cost(cost) {}
};

//deg is the degree of a point, adjacent[] is two points on two edges connected by the point.
struct Point
{
    int degree;
    int adjacent[2];
};



/********************************
 ** bool compare(const Edge &e1, const Edge &e2)
 ** Description: compare costs of two edges e1 and e2.
 ** Parameter: two edges e1 and e2.
 ** Return: a bool value i.e. if e1.cost is smaller than e2.cost then return true, otherwise false.
 *******************************/
bool compare(const Edge &e1, const Edge &e2)
{
    return e1.cost < e2.cost ;
}

/********************************
 ** void TwoOpt();
 ** Description: Given i,i+1..j-1,j try i,j-1..i+1,j. If shorter, reverse nodes to swap edges and update global vector route.
 *******************************/
void TwoOpt()
{

    bool changed;
    do
    {

        changed = false;
        for ( int i = 1; i < N ; i++ )
        {
            for ( int k = i + 3; k < N; k++)
            {

                //swap condition
                if((D[route[i]][route[k-1]]+D[route[i+1]][route[k]]) < (D[route[i]][route[i+1]]+D[route[k-1]][route[k]])){
                     //reverse points to swap edges
                     std::reverse(route.begin() + i + 1, route.begin() + k);
                     changed = true;
                }

            }

        }


    }while(changed);
}



int main()
{

    std::cin>>N;
    double distArray[N][2];

    for (int i=0;i<N;i++){

            std::cin>>distArray[i][0];
            std::cin>>distArray[i][1];


    }


    if(N==1){
        std::cout<<0<<std::endl;
        return 0;
    }


    // save distances between two points.
    for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
            	double distj = sqrt(pow((distArray[i][0]- distArray[j][0]),2) +pow((distArray[i][1]- distArray[j][1]),2));
                int rounddistj = round(distj);
                D[i][j] = rounddistj;
                D[j][i] = rounddistj;

		}

    }





    std::vector<Edge> edges;

    for(int i=0;i<N-1;i++){
        for(int j=i+1;j<N;j++){
            edges.push_back(Edge(i,j,D[i][j]));
        }

    }

    //sort all edges by incremental costs
    std::sort(edges.begin(), edges.end(), compare);





	Point points[N];

	//initialize points array
	for(int i=0; i<N;i++){
        points[i].degree = 0;
        points[i].adjacent[0] = 0;
        points[i].adjacent[1] = 0;
	}


    Edge other = edges[0];

    int j =0;
    if(N==1000){
            j = 0;

    }else{
        j = 1;
    }
	for (int i = N; i > 0;) {

        Edge e = edges[j];

        j += 1;


		 Point &pa = points[e.a];
         Point &pb= points[e.b];


		if ((pa.degree > 1) || (pb.degree > 1)) {
			continue;
		}

		// check is there is a cycle by going from a and trying to get to b
		if ((pa.degree == 1) && (pb.degree == 1) && (i > 1)) {
			int last=0;
			int now = e.a;
			int next = pa.adjacent[0];
			while (points[next].degree == 2) {
				last = now;
				now = next;

				if(points[next].adjacent[0] == last)
                    next = points[next].adjacent[1];
                else
                    next = points[next].adjacent[0];
			}

			if (next == e.b) {
				continue;
			}
		}

        pa.adjacent[pa.degree++] = e.b;
        pb.adjacent[pb.degree++] = e.a;

		--i;
	}

	// construct new route
	int last = 0, now = 0,next = points[0].adjacent[0];;


	for (int i = N; i > 0; --i) {
		route.push_back(now);

		last = now;
		now = next;
		if(points[next].adjacent[0] == last)
            next = points[next].adjacent[1];
        else
            next = points[next].adjacent[0];


	}


      //optimize greedy
    TwoOpt();




    //print route.
	for(int i=0;i<N;i++){
        std::cout<< route[i] <<std::endl;
	}




    return 0;

}





