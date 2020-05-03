# Vector Addition

**Routine Name:**           vectorAdd

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the addition of two vectors

**Input:** vector<double> v1, vector<double> v2

**Output:** vector<double> v3 = v1 + v2

**Usage/Example:**  

    std::vector<double> vector = {1,2,3,4,5,6,7,8,9,10};
    std::vector<double> approx = {0,2,3,4,5,6,7,8,9,10};
    vectorAdd(vector,approx);


Output from the lines above:

    {1,4,6,8,10,12,14,16,18,20}

**Implementation/Code:** The following is the code for vectorAdd(const std::vector<double>& v1, const std::vector<double>& v2)

    std::vector<double> vectorAdd(const std::vector<double>& v1, const std::vector<double>& v2){
        if(v1.size()!=v2.size()){ return std::vector<double> {0};}
        std::vector<double> answer;
        for(unsigned int i =0; i < v1.size();++i){
            answer.push_back(v1[i]+v2[i]);
        }
        return answer;
    }
