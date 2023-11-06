#include <stdio.h>
#include <math.h>
#include <stdbool.h>

const int I_0 = 20;
const int J_0 = 0;
const int L_0 = 11;

struct step{
    int i;
    int j;
    int l;
    int iteration;
};

int max(int a, int b){
    return a < b ? b : a;
}

int min(int a, int b){
    return a < b ? a : b;
}

int sign(int a){
    return a > 0 ? 1 : a == 0 ? 0 : -1;
}

int count_i(int i, int j, int l, int k) {
    int new_i = ((i - k) * max(j, l) + (j - k) * min(i, l) + (l - k) * max(i, j)) % 23;

    return new_i;
}

int count_j(int i, int j, int l, int k) {
    int new_j = -(((i - k) * min(j, l) + (j - k) * max(i, l) + (l - k) * min(i, j)) % 27);

    return new_j;
}

int count_l(int i, int j, int l, int k) {
    int new_l = abs(i + j - l - k) * sign(i - j + l - k);

    return new_l;
}

bool check(struct step point){
    if (point.j > point.i + 10 && point.j < -point.i + 10 && point.i > -10){
        return true;
    }

    return false;
}

int main() {
    struct step last_point = {I_0, J_0, L_0, 0};

    for (int i = 1; i <= 50; ++i){
        int new_i = count_i(last_point.i, last_point.j, last_point.l, last_point.iteration + 1);
        int new_j = count_j(last_point.i, last_point.j, last_point.l, last_point.iteration + 1);
        int new_l = count_l(last_point.i, last_point.j, last_point.l, last_point.iteration + 1);


        struct step current_point = {new_i, new_j, new_l, last_point.iteration + 1};

        if (check(current_point)) {
            printf("\nStopped on iteration: %d\nFinal variables i: %d, j: %d, k: %d", current_point.iteration, current_point.i, current_point.j, current_point.l);
            return 0;
        }

        last_point = current_point;
        printf("i: % 3d j: % 3d, l: % 3d\n", current_point.i, current_point.j, current_point.l);

    }

    printf("Fucked up!");
    return 0;
}
