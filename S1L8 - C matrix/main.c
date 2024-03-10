#include <stdio.h>
#include <limits.h>

int main() {
    FILE *file = fopen("C:\\Users\\den41\\CLionProjects\\untitled\\test.txt", "r");

    int n;
    fscanf(file, "%d", &n);

    int matrix[n][n];
    int mn = INT_MAX;
    int mn_column = -1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fscanf(file, "%d", &matrix[i][j]);
            if (matrix[i][j] <= mn) {
                mn = matrix[i][j];
                mn_column = j;
            }
        }
    }

    fclose(file);

    int product = 1;
    for (int i = 0; i < n; ++i) {
        product *= matrix[i][mn_column];
    }

    printf("Произведение элементов в максимальном столбце с минимальным элементом: %d\n", product);
    return 0;
}
