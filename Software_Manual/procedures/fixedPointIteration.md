# Fixed Point Iteration

**Routine Name:**           fixedPointIteration

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the root of x cosh(x)+x^3=π using Fixed Point Iteration

**Input:** double starting value, integer max iterations

**Output:** double root of the equation

**Usage/Example:**

std::cout << fixedPointIteration(1,100);

Output from the lines above:

      1.09633

**Implementation/Code:** The following is the code for fixedPointIteration(double start, int maxiters)

          double fixedPointIteration(double start, int maxiters){ // x cosh(x)+x^3=π
              auto pChange = DBL_MAX;
              auto cChange =DBL_MAX;
              double x = start;
              double xn;
              for(int i=0; i < maxiters && std::abs(cChange) <=std::abs(pChange)&& cChange!=0;++i) {
                  pChange = cChange;
                  xn = std::cbrt(M_PI - x*cosh(x));
                  cChange = x - xn;
                  x = xn;
                  //std::cout <<i<<": "<<x<<"\n"; //used to watch convergence
              }
              return x;
          }


**Last Modified:** October/2019
