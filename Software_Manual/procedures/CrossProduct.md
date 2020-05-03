# Cross Product

**Routine Name:**           crossProduct

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the Cross product of two vectors

**Input:** vector<double> v1, vector<double> v2

**Output:** vector<double> v3 = v1 X v2

**Usage/Example:**  

    std::vector<double> v1 = {1,1,0};
    std::vector<double> v2 = {0,1,1};
    dotProduct(v1,v2)


Output from the lines above:

    {1,-1,1}

**Implementation/Code:** The following is the code for crossProduct(const std::vector<double>& v1, const std::vector<double>& v2)

    std::vector<double> crossProduct(const std::vector<double>& v1, const std::vector<double>& v2){
        if(v1.size()!=v2.size()){ return std::vector<double> {0};}
        unsigned int size = v1.size();
        std::vector<double> answer;
        for(unsigned int i =0; i < v1.size();++i){
            answer.push_back(v1[(i+1)%size]*v2[(i+2)%size]-v1[(i+2)%size]*v2[(i+1)%size]);
        }
        return answer;
    }
