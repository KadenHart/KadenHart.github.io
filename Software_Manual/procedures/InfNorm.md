# Infinity Norm

**Routine Name:**           infNorm

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the infinity norm of a given vector

**Input:** vector<double> vector

**Output:** double

**Usage/Example:**  

    std::vector<double> vector = {1,2,3,4,5,6,7,8,9,10};  
    infNorm(vector);  


Output from the lines above:

    10

**Implementation/Code:** The following is the code for infNorm(const std::vector<double>& vector)

    double infNorm(const std::vector<double>& vector) {
        double norm =0;
        for(double thing : vector){
            if(std::abs(thing)>norm){
                norm = thing;
            }
        }
        return norm;
    }
