# One Norm

**Routine Name:**           oneNorm

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the one norm of a given vector

**Input:** vector<double> vector

**Output:** double

**Usage/Example:**  

    std::vector<double> vector = {1,2,3,4,5,6,7,8,9,10};  
    oneNorm(vector);  


Output from the lines above:

    55

**Implementation/Code:** The following is the code for oneNorm(const std::vector<double>& vector)

    double oneNorm(const std::vector<double>& vector){
        double norm =0;
        for(double thing : vector){
            norm += std::abs(thing);
        }
        return norm;
    }
