#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])
#define N 10001
#define xlim 5000

double sinc(double x) {
    if (x == 0.0){
        return 1.0;
    } else {
        return sin(x)/x;
    }
}

int main() {
    double Delta = (double) 2 * xlim / (N - 1);
    double data[2*N];

    gsl_fft_complex_wavetable * wavetable;
    gsl_fft_complex_workspace * workspace;

    for (int i=0; i < N; i++) {
        double x = -xlim + i * Delta;
        REAL(data,i) = sinc(x);//Real Part
        IMAG(data,i) = 0.0;//Imaginary Part
    }

    wavetable = gsl_fft_complex_wavetable_alloc(N);
    workspace = gsl_fft_complex_workspace_alloc(N);

    gsl_fft_complex_forward(data, 1, N, wavetable, workspace);

    FILE *file = fopen("q3_data.csv","w");
    if (file == NULL) {
        printf("Error Opening File!\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        fprintf(file, "%g, %g\n", REAL(data,i), IMAG(data,i));
    }

    gsl_fft_complex_wavetable_free (wavetable);
    gsl_fft_complex_workspace_free (workspace);
    fclose(file);

    printf("Fourier transform data has been written to 'q3_data.csv'.\n");

    return 0;
}