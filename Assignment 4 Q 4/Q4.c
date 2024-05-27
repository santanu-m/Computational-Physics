#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double exp_dist(double a) {
    return -log(1 - ((double) rand() / RAND_MAX)) / a;
}

int main() {
    const int n = 10000;
    const double a = 2.0;
    double r[n];

    srand((unsigned) time(NULL));
    for (int i = 0; i < n; ++i) {
        r[i] = exp_dist(a);
    }

    FILE *f = fopen("exp_dist.txt", "w");
    if (f == NULL) {
        perror("Error opening file");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        fprintf(f, "%f\n", r[i]);
    }

    fclose(f);

    return 0;
}
