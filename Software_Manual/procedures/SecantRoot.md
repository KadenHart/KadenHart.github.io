# Secant Root Finding Method

**Routine Name:**           secantRoot

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the root of x cosh(x)+x^3=π using Secant method

**Input:** double starting value, integer max iterations

**Output:** double: root of the equation

**Usage/Example:**

std::cout << newtonsRoot(1,100);

Output from the lines above:

      1.09038

**Implementation/Code:** The following is the code for secantRoot(double start, int maxiters)

      double secantRoot(double start, int maxiters){ // x cosh(x)+x^3=π
          auto pChange = DBL_MAX;
          auto cChange =DBL_MAX;
          double x = start;
          double xn,xp;
          auto fx = [&](double y){
              return (M_PI - y*y*y)/cosh(y);
          };
          xp= fx(1.09);
          for(int i=0; i < maxiters && std::abs(cChange) <=std::abs(pChange)&& cChange!=0;++i) {
              pChange = cChange;
              xn = xp- (fx(x)*x-fx(x)*xp)/(fx(x)-fx(xp));
              cChange = x - xn;
              xp =x;
              x = xn;
              //std::cout <<i<<": "<<x<<"\n"; //used to watch convergence
          }
          return x;
      }
