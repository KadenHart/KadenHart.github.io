# Vector Scale

**Routine Name:**           vectorScale

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the subtraction of two vectors

**Input:** vector<double> v1, double scale

**Output:** vector<double> v3 = v1*scale

**Usage/Example:**  

    std::vector<double> vector = {1,2,3,4,5,6,7,8,9,10};
    vectorScale(vector,1.32);


Output from the lines above:

    {1.32,2.64,3.96,5.28,6.6,7.92,9.24,10.56,11.88,13.2}

**Implementation/Code:** The following is the code for vectorScale(const std::vector<double>& v1, double scale)

    std::vector<double> vectorScale(const std::vector<double>& v1, double scale){
        std::vector<double> answer;
        answer.reserve(v1.size());
    for(double i : v1){
            answer.push_back(i*scale);
        }
        return answer;
    }
