/*
**
**  Warmup exercise - Computational Physics  2016
**
**  Program to compute the first derivative of arctan(x) for different 
**  step lenghts, h, when x is set to sqrt(2). It contains two functions,
**  one for computing the first derivative using 2 and 3 points for different 
**  step sizes h, which are decaying by a factor of two for each iteration. The
**  other function outputs the results to the file RESULTS.txt.
**
**  This program is strongly influenced by the second derivative program,
**  more specificly program3.cpp in chapter03, in the lecture notes of the 
**  Computational Physics course written by Morten Hjorth-Jensen.
*/
using namespace std;
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

void first_derivative(int, double, double, double *, double *, double *);
void output(double *, double *, double *, double, int);

ofstream ofile;

// Function to calculate the first derivative of arctan(x) with 2 and 3 points.
void first_derivative(int number_of_steps, double x, double initial_step,
		      double *h_step, double *computed_derivative_2point,
		      double *computed_derivative_3point){
  // Initialize variables, step size, h and counter
  int counter;
  double h;
  h = initial_step;

  // The step size will gradually go from initial_step towards 0,
  // by dividing the step size of 2 for each step.
  for (counter=0; counter < number_of_steps; counter++){
    // Store the step size to h_step and calculate the derivative
    // using the 2point and 3point methods
    h_step[counter] = h;
    computed_derivative_2point[counter] = (atan(x+h)-atan(x))/h;
    computed_derivative_3point[counter] = (atan(x+h)-atan(x-h))/(2*h);

    // update the step size
    h = h*0.5;
    
  } // End of for loop
  return;
} // End of function first_derivative

// Function to output the results to a txt file
void output(double *h_step, double *computed_derivative_2point,
	    double *computed_derivative_3point,
	    double x, int number_of_steps){
  int i;
  ofile << "RESULTS:" << endl;
  ofile << setiosflags(ios::showpoint | ios::uppercase);

  for(i = 0; i < number_of_steps; i++){
    ofile << setw(15) << setprecision(8) << h_step[i];
    ofile << setw(15) << setprecision(8) << computed_derivative_2point[i];
    ofile << setw(15) << setprecision(8) << computed_derivative_3point[i] << endl;
  }
} // End of output function


int main(int argc, char* argv[]){
  // declare variables
  int number_of_steps;
  double x, initial_step;
  double *h_step, *computed_derivative_2point, *computed_derivative_3point;

  // Set intial step, x and number_of_steps, and output file name
  initial_step = 1000.0;
  x = sqrt(2);
  number_of_steps = 100;

  // Print out the variables the program is running with
  cout << "initial_step="<< initial_step << "; x=" << sqrt(2)
       << "; n_steps=" << number_of_steps << endl;
  
  // open output file
  ofile.open("RESULTS.TXT", fstream::in | fstream::out | fstream::app);
  
  // Allocate space in the memory for h_step, computed_derivative_2point,
  // and computed_derivative_3point.
  h_step = new double[number_of_steps];
  computed_derivative_2point = new double[number_of_steps];
  computed_derivative_3point = new double[number_of_steps];

  

  // Compute the first derivative of arctan(x)
  first_derivative(number_of_steps, x, initial_step, h_step,
		   computed_derivative_2point,computed_derivative_3point);
  
  // Print the results to file
  
  output(h_step, computed_derivative_2point, computed_derivative_3point,
	 x, number_of_steps);
  
  // free memory
  delete [] h_step;
  delete [] computed_derivative_2point;
  delete [] computed_derivative_3point;
  // close output file
  ofile.close();
  return 0;
} // end main program


  
