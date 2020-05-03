# SAXPY

**Routine Name:**           saxpy

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the saxpy of two vectors

**Input:** vector<double> v1, vector<double> v2

**Output:** vector<double>

**Usage/Example:**  

    std::vector<double> v1 = {1,1,0};
    std::vector<double> v2 = {0,1,1};
    saxpy(v1,v2,5.9);


Output from the lines above:

    {5.9,6.9,1}

**Implementation/Code:** The following is the code for saxpy(const std::vector<double>& v1, const std::vector<double>& v2, double scale)

std::vector<double> saxpy(const std::vector<double>& v1, const std::vector<double>& v2, double scale){ //really daxpy
    return vectorAdd(vectorScale(v1,scale),v2);
}
