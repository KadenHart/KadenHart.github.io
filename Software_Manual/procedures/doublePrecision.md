# Double Precision  

**Routine Name:**           doublePrecision  

**Author:** Kaden Hart  

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt  

**Description/Purpose:** This routine will compute machine precision on the central difference form of f(x) = e^x at x = pi using double precision floating point numbers 

**Input:** the maximum times h will be divided by two

**Output:** The number of times h was divided by two until the error started to increase rather than decrease  

**Usage/Example:**  

std::cout << doublePrecision(100);  

Output from the lines above:  

      18

**Implementation/Code:** The following is the code for doublePrecision(int maxPrecision)

      int doublePrecision(int maxPrecision){  //used to check machine precision on the central difference form of f(x) = e^x at x = pi answer should be e^pi.
          double pi = M_PI;
          double e = M_E;
          double error = 5, newError, hh = 1.0/1.0;
          int precision = -1;

          for (int i=1; i<maxPrecision;++i){
              newError = std::abs(pow(e,pi) - (((double)(pow(e,pi+hh) - pow(e,pi-hh))/(double)((pi+hh) - (pi - hh)))));
              if (newError <= error || newError ==0){
                  error = newError;
                  precision = i;
              }
              else{
                  break;
              }

              hh = hh/2;
          }

          //std::cout<<"Double Error: "<< error<<std::endl;
          return precision;
      }


**Last Modified:** October/2019  
