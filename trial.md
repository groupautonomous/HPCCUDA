<h1>HPC Assignment 2</h1>
<h5>hpcgp039</h5>
<h5> Earl Fernando</h5>

##### Anoop Subramanium 

##### Anand Hariharan
<h3>Problem Description</h3>
Use posix threads to parallelize the given problem of finding the root of a given polynomial function .
By using newton's method iteratively for calculating the root to which a certain point in space converges.
By discritizing these points in the form of a matrix of given dimension with their extreme points having their real and imaginary part ranging from -2 and 2. Further use these values in creating a PPM image file for the time taken convergence of these roots and the root to which a certain point converges.

## Newton Method
In order to calculate the root to which a certian point converges. The each iteration  was divided into several different subtasks.
1.Do newton iteration .
2.Check for convergence by comparing with precalculated root values.
3.Else Check for convergence by comparing with the origin.
4.Else check for divergence.
In order to speed up the process separate function were written for calculating the power of the complex number. Further the newton's equation for simplified manually by hand so that power of the roots needs to calculated just once. Use of inbuild functions like pow and sqrt were also removed.
After calculating the roots and convergence of a certain row of the matrix.
The roots were converted to RGB values. In order to make the write part faster the rgb values were converted to a string so that the values could be written directly to a file using fputs.This was done by writing a separate function that converts integer to a string instead of sprintf. All the columns in a certain row were appended into a newstring by using stpcpy which aligns the pointer to the end of the string.







