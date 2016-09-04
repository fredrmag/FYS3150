/**
  Description of Project 1
  **/

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <ctime>

using namespace std;

void populate_vectors(int, double *, double *, double *, double *, double *, double *);
void solve_tridiagonal(int, double *, double *, double *, double *, double *, double *, double *);

// Function which populates the vectors with our given function and boundary condtitions
void populate_vectors(int n, double *a, double *b, double *c, double *x, double *b_tilde, double *u){
    // Intitialize variables
    double h;
    int i;

    // Put boundary conditions
    x[0] = 0;
    u[0] = 0;
    x[n+2] = 1;
    u[n+2] = 0;

    // step length
    h = 1.0/(n+1.0);
    // Calculate the b_tilde defined as h²*f(x_i), where f=100e^(-10x)
    for (i = 1; i <= n+1; i++){
        x[i]=i*h;
        b_tilde[i]=h*h*100.0*exp(-10.0*x[i]);
    }

    // Populate arrays a, b, and, c.
    for (i = 1; i <= n; i++){
        a[i] = -1.0;
        b[i] = 2.0;
        c[i] = -1.0;
    }
    return;
}

// Function which solve the set of linear equations when the matrix is
// a tridiagonal matrix. The algorithm is given by Teukolsky et al,
// and consists of a forward and backward substitution.
void solve_tridiagonal(int n, double *a, double *b, double *c, double *b_tilde, double *u, double* temp){
    // Declare variables
    double btemp;
    int i;

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
    return;
}

// Function which gets the current time
string get_time_now(){
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    return asctime(now);
}

void output(double *column1, double *column2, int n){
    // Write the results to a file
    // Filename will be on the format data_nXX.dat
    ostringstream oss;
    oss << "../results/data_n" << n << ".dat";
    string out_filename = oss.str();
    cout << "Output the results to: " << out_filename << endl;
    // Convert std::string to char*:
    const char* cstr_ofilename = out_filename.c_str();

    ofstream ofile(cstr_ofilename);

    // Add header to output file
    ofile << "Project 1 - FYS3150" << endl
          <<"Solving the one-dimensional Poissons equation" << endl;
    ofile << "n = " << n << endl;
    ofile << get_time_now() << endl;

    int i;
    // Populate the file
    for (i=0; i<=n+1; i++){
        ofile << setw(25) << setprecision(16) << column1[i];
        ofile.setf(ios::scientific, ios::floatfield);
        ofile << setw(25) << setprecision(16) << column2[i] << endl;
    }
    ofile.close();
    return;
}

int main(int argc, char* argv[])
{
    // Declare variables
    int n;

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

    // Populate vectors
    populate_vectors(n, a, b, c, x, b_tilde, u);

    // Solve the tridiagonal system
    solve_tridiagonal(n, a, b, c, b_tilde, u, temp);

    // Output our results to file
    output(x,u,n);

    // Deallocate vectors
    delete [] a;
    delete [] b;
    delete [] c;
    delete [] x;
    delete [] b_tilde;
    delete [] temp;

    return 0;
}

