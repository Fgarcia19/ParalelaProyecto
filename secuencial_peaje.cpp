#include <bits/stdc++.h>
using namespace std;
const int N = 10;

int final_path[N+1];
bool visited[N];
double final_res = DBL_MAX;


double peaje[N][N] = { 
    {0, 0.6, 1.8, 0.5, 1.6, 1.0, 1.8, 1.6, 1.0, 1.1},
    {0.6, 0, 0.6, 1.8, 0.9, 0.7, 0.8, 1.9, 1.0, 1.6},
    {1.8, 0.6, 0, 1.4, 1.3, 1.8, 0.7, 2.0, 1.3, 1.2},
    {0.5, 1.8, 1.4, 0, 1.0, 0.5, 0.6, 2.0, 1.0, 1.2},
    {1.6, 0.9, 1.3, 1.0, 0, 1.1, 1.3, 0.5, 0.5, 1.6},
    {1.0, 0.7, 1.8, 0.5, 1.1, 0, 2.0, 1.6, 2.0, 0.8},
    {1.8, 0.8, 0.7, 0.6, 1.3, 2.0, 0, 0.8, 1.7, 1.0},
    {1.6, 1.9, 2.0, 2.0, 0.5, 1.6, 0.8, 0, 0.8, 0.6},
    {1.0, 1.0, 1.3, 1.0, 0.5, 2.0, 1.7, 0.8, 0, 1.3},
    {1.1, 1.6, 1.2, 1.2, 1.6, 0.8, 1.0, 0.6, 1.3, 0}  
};


double Minimo(double matriz[N][N], int i)
{
	double min = DBL_MAX;
	for (int k=0; k<N; k++)
		if (matriz[i][k]<min && i != k)
			min = matriz[i][k];
	return min;
}

double SegundoMinimo(double matriz[N][N], int i)
{
	double first = DBL_MAX, second = DBL_MAX;
	for (int j=0; j<N; j++)
	{
		if (i == j)
			continue;
		if (matriz[i][j] <= first)
		{
			second = first;
			first = matriz[i][j];
		}
		else if (matriz[i][j] <= second &&
				matriz[i][j] != first)
			second = matriz[i][j];
	}
	return second;
}

void TSPRec(double matriz[N][N], double curr_bound, double curr_weight,
			int level, int curr_path[])
{

	if (level==N)
	{
        /*
			ser accedida por un proceso a la vez
			critial section
		*/
		if (matriz[curr_path[level-1]][curr_path[0]] != 0)
		{
			double curr_res = curr_weight +
					matriz[curr_path[level-1]][curr_path[0]];
			if (curr_res < final_res)
			{
                for (int i=0; i<N; i++)
		            final_path[i] = curr_path[i];
	            final_path[N] = curr_path[0];
				final_res = curr_res;
			}
		}
		return;
	}

	for (int i=0; i<N; i++)
	{
		if (matriz[curr_path[level-1]][i] != 0 &&
			visited[i] == false)
		{
			double temp = curr_bound;
			curr_weight += matriz[curr_path[level-1]][i];

			if (level==1)
			curr_bound -= ((Minimo(matriz, curr_path[level-1]) +
							Minimo(matriz, i))/2);
			else
			curr_bound -= ((SegundoMinimo(matriz, curr_path[level-1]) +
							Minimo(matriz, i))/2);

			if (curr_bound + curr_weight < final_res)
			{
				curr_path[level] = i;
				visited[i] = true;

				TSPRec(matriz, curr_bound, curr_weight, level+1,
					curr_path);
			}

			curr_weight -= matriz[curr_path[level-1]][i];
			curr_bound = temp;

			memset(visited, false, sizeof(visited));
			for (int j=0; j<=level-1; j++)
				visited[curr_path[j]] = true;
		}
	}
}

void TSP(double matriz[N][N])
{
	int curr_path[N+1];

	double curr_bound = 0;
	memset(curr_path, -1, sizeof(curr_path));
	memset(visited, 0, sizeof(curr_path));

	for (int i=0; i<N; i++)
		curr_bound += (Minimo(matriz, i) + SegundoMinimo(matriz, i));

	curr_bound = curr_bound/2;
	visited[0] = true;
	curr_path[0] = 0;
	TSPRec(matriz, curr_bound, 0, 1, curr_path);
	/*
		#pragma dsa,das
			for i < n
				visit[i]=true
				curr_path[1]=i
				TSPRec(matriz, curr_bound, arista_costo(0,i), 2, curr_path);
	*/
}

int main()
{
	double distancias[N][N] = { 
        
    {0,  4.9,  7,  10, 3.6,  13, 13, 3,  6,  7},  
    {4.9,  0,  3,  6,  7,  16, 14, 2,  4,  5},  
    {7,  3,  0,  3,  10, 20, 13, 5,  5,  5},  
    {10, 6,  3,  0,  14, 23, 14, 8,  8,  7},  
    {3.6,  7,  10, 14, 0,  11, 15, 6,  9,  10}, 
    {13, 16, 20, 23, 11, 0,  26, 16, 16, 20}, 
    {13, 14, 13, 14, 15, 26, 0,  13, 17, 8},  
    {3,  2,  5,  8,  6,  16, 12, 0,  6,  4},  
    {6,  4,  5,  8,  9,  16, 17, 6,  0,  9},  
    {7,  5,  5,  7,  10, 20, 8,  4,  9,  0}  
	};


    double matriz[N][N];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            {
            matriz[i][j] = distancias[i][j] * peaje[i][j];
            }
    }


	TSP(matriz);

	printf("Minimum cost : %f\n", final_res);
	printf("Path Taken : ");
	for (int i=0; i<=N; i++)
		printf("%d ", final_path[i]);

	return 0;
}

/*
    {0,  44,  71,  105, 38,  134, 137, 33,  68,  71},  
    {44,  0,  32,  69,  74,  168, 143, 28,  46,  58},  
    {71,  32,  0,  39,  107, 200, 135, 54,  57,  52},  
    {105, 69,  39,  0,  141, 234, 145, 83,  87,  74},  
    {38,  74,  107, 141, 0,  114, 159, 66,  96,  103}, 
    {134, 168, 200, 234, 114, 0,  265, 165, 165, 202}, 
    {137, 143, 135, 145, 159, 265, 0,  132, 179, 88},  
    {33,  28,  54,  83,  66,  165, 123, 0,  68,  43},  
    {68,  46,  57,  87,  96,  165, 179, 68,  0,  92},  
    {71,  58,  52,  74,  103, 202, 88,  43,  92,  0}


    peaje
    [0, 0.6, 1.8, 0.5, 1.6, 1.0, 1.8, 1.6, 1.0, 1.1]
    [0.6, 0, 0.6, 1.8, 0.9, 0.7, 0.8, 1.9, 1.0, 1.6]
    [1.8, 0.6, 0, 1.4, 1.3, 1.8, 0.7, 2.0, 1.3, 1.2]
    [0.5, 1.8, 1.4, 0, 1.0, 0.5, 0.6, 2.0, 1.0, 1.2]
    [1.6, 0.9, 1.3, 1.0, 0, 1.1, 1.3, 0.5, 0.5, 1.6]
    [1.0, 0.7, 1.8, 0.5, 1.1, 0, 2.0, 1.6, 2.0, 0.8]
    [1.8, 0.8, 0.7, 0.6, 1.3, 2.0, 0, 0.8, 1.7, 1.0]
    [1.6, 1.9, 2.0, 2.0, 0.5, 1.6, 0.8, 0, 0.8, 0.6]
    [1.0, 1.0, 1.3, 1.0, 0.5, 2.0, 1.7, 0.8, 0, 1.3]
    [1.1, 1.6, 1.2, 1.2, 1.6, 0.8, 1.0, 0.6, 1.3, 0]   

*/
