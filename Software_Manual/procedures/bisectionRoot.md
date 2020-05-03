# Bisection Root Finding

**Routine Name:**           bisectionRoot

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the root of x cosh(x)+x^3=π using Bisection

**Input:** double low starting value, double high starting value

**Output:** double root of the equation

**Usage/Example:**

std::cout << bisectionRoot(1,2);

Output from the lines above:

      1.09633

**Implementation/Code:** The following is the code for bisectionRoot(double low, double high)

        double bisectionRoot(double low, double high){ // x cosh(x)+x^3=π
            int machinePrecision = doublePrecision(100);
            auto fx = [&](double x){
                return x*x*x+x*cosh(x)-M_PI;
            };
            double middle = (high+low)/2;
            double fmiddle = fx(middle);
            double fhigh = fx(high);
            double flow = fx(low);
            for(int i =0; i <machinePrecision;++i){ //skips one so the last run returns middle
                if(flow == 0) return low;
                if(fhigh == 0) return high;
                if(fmiddle ==0)return middle;
                if(flow*fhigh>=0) return DBL_MAX;
                if(flow*fmiddle<=0){
                    high = middle;
                }
                else{
                    low = middle;
                }

                middle = (high+low)/2;
                fmiddle = fx(middle);
                fhigh = fx(high);
                flow = fx(low);
            }
            return middle;
        }


**Last Modified:** October/2019
