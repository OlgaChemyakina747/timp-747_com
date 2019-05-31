#include <stdlib.h>
#include <stdio.h>


void swapToNumber(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int* searchway(int array[5][5], int size, int v)
{
	int* razm = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		if (i == v)
			razm[i] = 0;
		else
			razm[i] = 1000;
	}
	int t, minr, minv, pos[5] = { 1, 1, 1, 1, 1 };
	do {
		minr = 1000;
		minv = 1000;
		for (int i = 0; i < size; i++) {
			if ((pos[i] == 1) && (razm[i] < 1000)) {
				minr = razm[i];
				minv = i;
			}
		}
		if (minv != 1000) {
			for (int i = 0; i < size; i++) {
				if (array[minv][i] > 0) {
					t = minr + array[minv][i];
					if (t < razm[i])
						razm[i] = t;
				}
			}
			pos[minv] = 0;
		}
	} while (minv < 1000);
	return razm;
}
int minContour(int* a, int g[5][5], int n, int cost)
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
		{
			if (i == j)
				g[i][j] = 0;
			else {
				if (g[i][j] == 0)
					g[i][j] = 1000;
			}
		}
	}
	int temp = 0;
	int gr = 0;
	int sum = 0;
	for (int i = 0; i <= n - 1; i++)
		sum += g[a[i % 5]][a[(i + 1) % 5]];
	if (cost > sum) {
		cost = sum;
	}
	while (gr < 119) {
		sum = 0;
		int j = n - 2;
		while (j != -1 && a[j] >= a[j + 1])
			j--;
		if (j == -1)
			gr = 119;
		int k = n - 1;
		while (a[j] >= a[k])
			k--;
		{
			swapToNumber(&a[j], &a[k]);
		}
		int l = j + 1, r = n - 1;
		while (l < r)
			swapToNumber(&a[l++], &a[r--]);
		for (int i = 0; i <= n - 1; i++)
			sum += g[a[i % 5]][a[(i + 1) % 5]];
		if (cost > sum)
			cost = sum;
		gr++;
	};
	return cost;
}
int main()
{
	const int V = 5;
	char nameFile[] = "result.txt";
	FILE *result;
	result = fopen(nameFile, "w");
	int graph[V][V];
	printf("Enter Adjacency matrix (size 5 x 5)\n");
	for (int i = 0; i < V; i++)
	    for (int j = 0; j < V; j++) {
	        scanf("%d", &graph[i][j]);
	    }

	int* arr = (int*)malloc(V * sizeof(int));
	for (int i = 0; i < 5; i++)
		arr[i] = i;
	int z = 1;
	fprintf(result, "Adjacency matrix:\n");
	printf("Adjacency matrix:\n");
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			printf("%d ", graph[i][j]);
			fprintf(result, "%d ", graph[i][j]);
		}
		printf("\n");
		fprintf(result, "\n");
	}
	int v;
	printf("Starting vertex number:\n");
	scanf("%d", &v);
	int* f = searchway(graph, V, v - 1);
	for (int i = 0; i < 5; i++) {
		if (f[i] <= 9999) {
			fprintf(result, "Shortest way %d -> %d: %d\n", v, z, f[i]);
			printf("Shortest way %d -> %d: %d\n", v, z, f[i]);
		}
		z++;
	}
	int fk = minContour(arr, graph, V, 9999);
	if (fk <= 9999) {
		fprintf(result, "The contour of the minimum length is: %d\n", fk);
		printf("The contour of the minimum length is: %d\n", fk);
	}
	fclose(result);
	return 0;
}
