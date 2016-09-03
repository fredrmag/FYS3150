/**
  Description of Project 1
  **/

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
    // Declare variables
    int n;

    double h, b_temp;

    // vectors
    double *a, *b, *c, *x, *b_tilde;

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

    // The vectors, x and b_tilde, are going from 0->n+1. Thus, we need to allocate
    // n+1-0+1=n+2 elements
    x = new double [n+2];
    b_tilde = new double [n+2];

    // step length
    h = 1/(n+1);



    // Deallocate vectors
    delete [] a;
    delete [] b;
    delete [] c;
    delete [] x;
    delete [] b_tilde;

    return 0;
}

