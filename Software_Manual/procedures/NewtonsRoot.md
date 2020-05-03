# Newtons Root Finding Method

**Routine Name:**           newtonsRoot

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the root of x cosh(x)+x^3=π using Newtons method

**Input:** double starting value, integer max iterations

**Output:** double: root of the equation

**Usage/Example:**

std::cout << newtonsRoot(1,100);

Output from the lines above:

      1.09633

**Implementation/Code:** The following is the code for newtonsRoot(double start, int maxiters)

        double newtonsRoot(double start, int maxiters){ // x cosh(x)+x^3=π
            auto pChange = DBL_MAX;
            auto cChange =DBL_MAX;
            int precision = doublePrecision(100);
            double h = 1;
            for(int i =0;i<precision;i++){
                h = h/2;
            }
            double x = start;
            double xn;
            for(int i=0; i < maxiters && std::abs(cChange) <=std::abs(pChange)&& cChange!=0;++i) {
                pChange = cChange;
                xn = std::cbrt(M_PI - x*cosh(x)) - (std::cbrt(M_PI - (x-h)*cosh(x-h))-std::cbrt(M_PI - (x+h)*cosh(x+h)))/2*h;
                cChange = x - xn;
                x = xn;
                //std::cout <<i<<": "<<x<<"\n"; //used to watch convergence
            }
            return x;
        }
