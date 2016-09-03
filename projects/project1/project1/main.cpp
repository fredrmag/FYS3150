/**
  Description of Project 1
  **/

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main(int argc, char* argv[])
{
    // Declare variables
    int i, n;

    double h, btemp;

    // vectors
    double *a, *b, *c, *x, *b_tilde, *u, *temp;

    // Welcome message
    cout << "FYS3150 - Project 1 - Fall 2016" << endl;

    // Check if commandline argument is present
    if (argc > 1){
        n=atoi(argv[1]);
        cout << "n=" << n << endl;
    } else {
        cout << "Correct usage: " << argv[0] << "<grid points>" << endl;
        exit(1);
    }

    // Allocate vectors

    // The vectors a, b, and, c goes from 1:n
    // We need to allocate n+1 elements as we dont use the 0 position, i.e., a[0].
    a = new double [n+1];
    b = new double [n+1];
    c = new double [n+1];
    temp = new double [n+1];

    // The vectors, x, u, and, b_tilde, are going from 0->n+1. Thus, we need to allocate
    // n+1-0+1=n+2 elements
    x = new double [n+2];
    u = new double [n+2];
    b_tilde = new double [n+2];

    // step length
    h = 1/(n+1);

    // Put boundary conditions
    x[0] = 0;
    u[0] = 0;
    x[n+2] = 1;
    u[n+2] = 0;

    // Calculate the b_tilde defined as h²*f(x_i), where f=100e^(-10x)
    for (i = 1; i <= n+1; i++){
        x[i]=i*h;
        b_tilde[i]=h*h*100*exp(-10*x[i]);
    }

    // Populate arrays a, b, and, c.
    for (i = 1; i <= n; i++){
        a[i] = -1;
        b[i] = 2;
        c[i] = -1;
    }

    // The algorithm for solvind the tridiagonal problem is given by Teukolsky et al,
    // and consists of a forward and backward substitution.

    btemp = b[1];
    u[1] = b_tilde[1]/btemp;
    // Forward substitution
    for (i = 2; i <= n; i++){
        temp[i] = c[i-1]/btemp;
        btemp = b[i] - a[i]*temp[i];
        u[i] = (b_tilde[i]-a[i]*u[i-1])/btemp;
    }

    // Backward substitution
    for (i = n-1; i>=1; i--){
        u[i] -= temp[i+1]*u[i+1];
    }


    // Deallocate vectors
    delete [] a;
    delete [] b;
    delete [] c;
    delete [] x;
    delete [] b_tilde;
    delete [] temp;

    return 0;
}

