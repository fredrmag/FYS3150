// Scientific hello world program, taken from FYS3150, UiO
// https://github.com/CompPhysics/ComputationalPhysics

using namespace std;
#include <iostream>
#include <cstdlib>
#include <cmath>

int main (int argc, char* argv[]) {
  // declare variables 
  double r,s;
  // Check if the user has typed in a command-line argument
  if (argc <= 1) {
    if (argv[0])
      cout << "Usage: " << argv[0] << " <number>" << endl;
    else
      cout << "Usage <program name> <number>" << endl;

    exit(1);
  }
  
  // Convert the text argv[1] to double using atof
  r = atof(argv[1]);
  s = sin(r);
  cout << "Hello, World! sin(" << r << ") = " << s << endl;
  
  // success
  return 0;
}
