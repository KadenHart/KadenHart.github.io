# Matrix times a vector

**Routine Name:**           newtonsRoot

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute B in B=Ax where A is a matrix, and x is a vector

**Input:** vector<vector<double>> matrix, vector<double> vector

**Output:** vector<double> B

**Usage/Example:**  

    std::vector<double> v2 = \{1,2,3\};
    std::vector<std::vector<double>> matrix = \{\{1,2,3\},\{5,10,20\},\{1,1,1\}\};
    answer = matTimesVector(matrix,v2);  
    
Output from the lines above:

    {85,6,14}

**Implementation/Code:** The following is the code for matTimesVector(const std::vector<std::vector<double>>& matrix, const std::vector<double>& v)

    std::vector<double> matTimesVector(const std::vector<std::vector<double>>& matrix, const std::vector<double>& v){
        if (matrix[0].size()!=v.size()){ return std::vector<double>{0};}
        std::vector<double> answer;
        answer.reserve(matrix.size());
    #pragma omp parallel for
        for(unsigned int i =0; i < matrix.size();++i){
            answer.push_back(dotProduct(matrix[i],v));
        }
        return answer;
    }
