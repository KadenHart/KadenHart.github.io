# Dot Product

**Routine Name:**           dotProduct

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the Dot product of two vectors

**Input:** vector<double> v1, vector<double> v2

**Output:** double v3 = v1 * v2

**Usage/Example:**  

    std::vector<double> v1 = {1,1,0};
    std::vector<double> v2 = {0,1,1};
    dotProduct(v1,v2);


Output from the lines above:

    1

**Implementation/Code:** The following is the code for dotProduct(const std::vector<double>& v1, const std::vector<double>& v2)

    double dotProduct(const std::vector<double>& v1, const std::vector<double>& v2){
        double answer =0;
        if(v1.size()!=v2.size()){ return answer;}
        for(unsigned int i =0; i < v1.size();++i){
            answer+=v1[i]*v2[i];
        }
        return answer;
    }
