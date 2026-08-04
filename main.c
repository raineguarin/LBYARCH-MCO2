#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define NUM_RUNS 30
#define EPSILON 1e-9

/*
Windows x4 Calling Conventions
rcx = n
rdx = X1
r8  = X2
r9  = Y1
r10 = Y2
r11 = Z
[rsp + 40] = Y2
[rsp + 48] = Z
*/

// declare external kernel
extern void calculateDistanceASM(long n, const double* X1, const double* X2, const double* Y1, const double* Y2, double* Z);

// c version of kernel
void calculateDistanceC(long n, const double* X1, const double* X2, const double* Y1, const double* Y2, double* Z) {
    for (long i = 0; i < n; i++) {
        double dx = X2[i] - X1[i];
        double dy = Y2[i] - Y1[i];

        Z[i] = sqrt(dx * dx + dy * dy);
    }
}

// initialize vectors with random values
void initializeVectors(long n, double* X1, double* X2, double* Y1, double* Y2) {
    for (long i = 0; i < n; i++) {
        X1[i] = (double)rand() / RAND_MAX * 100.0;
        X2[i] = (double)rand() / RAND_MAX * 100.0;

        Y1[i] = (double)rand() / RAND_MAX * 100.0;
        Y2[i] = (double)rand() / RAND_MAX * 100.0;
    }
}

// sanity check: compare assembly and c outputs
bool compareResult(long n, const double* Z_c, const double* Z_asm) {
    for (long i = 0; i < n; i++) {
        if (fabs(Z_c[i] - Z_asm[i]) > EPSILON) {
            printf("Mismatch at index %ld: C=%f, ASM=%f\n", i, Z_c[i], Z_asm[i]);
            return false;
        }
    }
    return true;
}

// print the first 10 elements
void printFirstTen(const char* label, const double* Z) {
    printf("%sFirst 10 Elements:\n  [", label);
    for (int i = 0; i < 10; i++) {
        printf("%.8f%s", Z[i], (i == 9) ? "" : ", ");
    }
    printf("]\n");
}

void test(long n) {
    printf(" \nVector Size n = 2^%ld (%ld elements)\n\n", (long)log2(n), n);
    printf("==================================================\n");

    // memory allocation
    double* X1 = (double*)malloc(n * sizeof(double));  // rdx
    double* X2 = (double*)malloc(n * sizeof(double));  // r8
    double* Y1 = (double*)malloc(n * sizeof(double));  // r9
    double* Y2 = (double*)malloc(n * sizeof(double));  // [rsp + 40]
    double* Z_c = (double*)malloc(n * sizeof(double));
    double* Z_asm = (double*)malloc(n * sizeof(double)); // [rsp + 48] 

    if (!X1 || !X2 || !Y1 || !Y2 || !Z_c || !Z_asm) {
        printf("Memory allocation failed at n = %ld!\n", n);

        return;
    }

    initializeVectors(n, X1, X2, Y1, Y2);

    // run C kernel 30 times
    double totalTimeC = 0.0;

    for (int run = 0; run < NUM_RUNS; run++) {
        clock_t start = clock();
        calculateDistanceC(n, X1, X2, Y1, Y2, Z_c);
        clock_t end = clock();

        totalTimeC += (double)(end - start) / CLOCKS_PER_SEC;
    }
    double avgTimeC = totalTimeC / NUM_RUNS;

    // run asm kernel 30 times
    double totalTimeASM = 0.0;
    for (int run = 0; run < NUM_RUNS; run++) {
        clock_t start = clock();
        calculateDistanceASM(n, X1, X2, Y1, Y2, Z_asm);
        clock_t end = clock();

        totalTimeASM += (double)(end - start) / CLOCKS_PER_SEC;
    }
    double avgTimeASM = totalTimeASM / NUM_RUNS;

    printFirstTen("\nC         ||      ", Z_c);
    printf("\n");
    printFirstTen("Assembly    ||      ", Z_asm);
    printf("\n");

    if (compareResult(n, Z_c, Z_asm)) {
        printf("\n[CORRECTNESS CHECK]: PASSED\n\n");
    }
    else {
        printf("\n[CORRECTNESS CHECK]: FAILED\\nn");
    }

    printf("C Kernel Avg Time (%d runs)   : %.6f seconds\n", NUM_RUNS, avgTimeC);
    printf("ASM Kernel Avg Time (%d runs) : %.6f seconds\n", NUM_RUNS, avgTimeASM);

    // free memory
    free(X1); free(X2); free(Y1); free(Y2);
    free(Z_c); free(Z_asm);
}

int main() {
    srand(42); // fixed seed for running

    // test run using example case from the specs
    printf("\n\n=== TEST RUN USING EXAMPLE CASE ===\n\n");
    double ex_X1[] = { 1.5, 4.0, 3.5, 2.0 };
    double ex_X2[] = { 3.0, 2.5, 2.5, 1.0 };
    double ex_Y1[] = { 4.0, 3.0, 3.5, 3.0 };
    double ex_Y2[] = { 2.0, 2.5, 1.0, 1.5 };
    double ex_Z_c[4], ex_Z_asm[4];

    calculateDistanceC(4, ex_X1, ex_X2, ex_Y1, ex_Y2, ex_Z_c);
    calculateDistanceASM(4, ex_X1, ex_X2, ex_Y1, ex_Y2, ex_Z_asm);

    printf("C Test Run Output  : ");
    for (int i = 0; i < 4; i++) printf("%.8f ", ex_Z_c[i]);

    printf("\nASM Test Run Output: ");
    for (int i = 0; i < 4; i++) printf("%.8f ", ex_Z_asm[i]);
    printf("\n\nExpected Output   : 2.50000000 1.58113883 2.69258240 1.80277564\n");

    // benchmarks (until ^28, haven't tested ^30 yet)
    long sizes[] = { 1L << 20, 1L << 24, 1L << 28 };
    for (int i = 0; i < 3; i++) {
        test(sizes[i]);
    }
    return 0;
}