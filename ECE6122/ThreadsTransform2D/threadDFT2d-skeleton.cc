// Threaded two-dimensional Discrete FFT transform
// YOUR NAME HERE
// ECE8893 Project 2


#include <iostream>
#include <string>
#include <math.h>

#include "Complex.h"
#include "InputImage.h"

// You will likely need global variables indicating how
// many threads there are, and a Complex* that points to the
// 2d image being transformed.

using namespace std;

// Function to reverse bits in an unsigned integer
// This assumes there is a global variable N that is the
// number of points in the 1D transform.
unsigned ReverseBits(unsigned v)
{ //  Provided to students
  unsigned n = N; // Size of array (which is even 2 power k value)
  unsigned r = 0; // Return value
   
  for (--n; n > 0; n >>= 1)
    {
      r <<= 1;        // Shift return value
      r |= (v & 0x1); // Merge in next bit
      v >>= 1;        // Shift reversal value
    }
  return r;
}

// GRAD Students implement the following 2 functions.
// Undergrads can use the built-in barriers in pthreads.

// Call MyBarrier_Init once in main
void MyBarrier_Init()// you will likely need some parameters)
{
}

// Each thread calls MyBarrier after completing the row-wise DFT
void MyBarrier() // Again likely need parameters
{
}
                    
void Transform1D(Complex* h, int N)
{
  // Implement the efficient Danielson-Lanczos DFT here.
  // "h" is an input/output parameter
  // "N" is the size of the array (assume even power of 2)
}

void* Transform2DTHread(void* v)
{ // This is the thread startign point.  "v" is the thread number
  // Calculate 1d DFT for assigned rows
  // wait for all to complete
  // Calculate 1d DFT for assigned columns
  // Decrement active count and signal main if all complete
  return 0;
}

void Transform2D(const char* inputFN) 
{ // Do the 2D transform here.
  InputImage image(inputFN);  // Create the helper object for reading the image
  // Create the global pointer to the image array data
  // Create 16 threads
  // Wait for all threads complete
  // Write the transformed data
  
    int k, a;
    int N = image.GetWidth();
    Complex h = image.GetImageData();

    // Step 1: Reorder the array
    for(k=0;k<(N/2);k++) {
        Complex tmp = h[k];
        unsigned int rk = ReverseBits(k);
        h[k] = h[r];
        h[r] = tmp;
    }

    // Step 2: Compute the W array
    Warray = new Complex[(N/2)];
    for(k=0;k<(N/2);k++){
        double r = cos(2*M_PI*k/N);
        double i = -sin(2*M_PI*k/N);
        Warray[k] = Complex(r,i);
    }

    // Step 3: Compute the transforms
    int arrayLevel = 2;
    for(arrayLevel=2;arrayLevel<=N;arrayLevel*=2){
        int arrayNumber = N/arrayLevel;
        for(arrayStart=0;arrayStart<arrayNumber;arrayStart+=arrayLevel) {
            for(k=0;k(arrayLevel/2);k++){
                int index = k*N/arrayLevel;
                if(index >= N/2) {
                    index = index - N/2;
                }
                He = h[arrayStart+k];
                Ho = h[arrayStart+k+(arrayLevel/2)];
                h[arrayStart+k] = He + W[index]*Ho;
                h[arrayStart+k+(arrayLevel/2)] = He - W[index]*Ho;
            }
        }
    }

    image.saveImage("test1D.txt", h, N, N);
    delete[] h;
    delete[] Warray;
}

int main(int argc, char** argv)
{
  string fn("Tower.txt"); // default file name
  if (argc > 1) fn = string(argv[1]);  // if name specified on cmd line
  // MPI initialization here
  Transform2D(fn.c_str()); // Perform the transform.
}  
  

  
