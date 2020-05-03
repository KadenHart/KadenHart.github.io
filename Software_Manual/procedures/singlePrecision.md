# Single Precision  

**Routine Name:**           singlePrecision  

**Author:** Kaden Hart  

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt  

**Description/Purpose:** This routine will compute machine precision on the central difference form of f(x) = e^x at x = pi using single precision floating point numbers 

**Input:** the maximum times h will be divided by two

**Output:** The number of times h was divided by two until the error started to increase rather than decrease  

**Usage/Example:**  

std::cout << singlePrecision(100);  

Output from the lines above:  

      9

**Implementation/Code:** The following is the code for singlePrecision(int maxPrecision)


      int singlePrecision(int maxPrecision){  //used to check machine precision on the central difference form of f(x) = e^x at x = pi answer should be e^pi
          float pi = M_PI;
          float e = M_E;
          float error = 5, newError, hh = 1.0/1.0;
          int precision = -1;

          for (int i=1; i<maxPrecision;++i){
              newError = std::abs(powf(e,pi) - (((float)(powf(e,pi+hh) - powf(e,pi-hh))/(float)((pi+hh) - (pi - hh)))));
              if (newError <= error || newError ==0){
                  error = newError;
                  precision = i;
              }
              else{
                  break;
              }

              hh = hh/2;
          }
          //std::cout<<"Single Error: "<< error<<std::endl;
          return precision;
      }


**Last Modified:** October/2019  
