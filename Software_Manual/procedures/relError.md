# Relative Error  

**Routine Name:**           relError  

**Author:** Kaden Hart  

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt  

**Description/Purpose:** This routine will compute the relative error between two numbers  

**Input:** the computed value, and the expected value  

**Output:** returns the relative difference between the two inputs  

**Usage/Example:**  

std::cout << relError(1,2);  

Output from the lines above:  

      1

**Implementation/Code:** The following is the code for relError(double computed, double actual)  

      double relError(double computed, double actual){  
          return std::abs((actual - computed)/ actual);  
      }  


**Last Modified:** October/2019  
