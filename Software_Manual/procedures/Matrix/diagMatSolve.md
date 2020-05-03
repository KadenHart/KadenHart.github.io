# Diagonal Matrix Solve

**Routine Name:**           diagMatSolve

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the solution vector for a diagonal matrix

**Input:** std::vector<std::vector<double>>& diagMatrix

**Output:** std::vector<double> answer

**Usage/Example:**  

    std::vector<std::vector<double>> matrix = {\{1,0,0,20},{0,1.21,0,20},{0,0,5442.5899,20}\};
    std::vector<double> answer;
    std::cout<<"Diagonal solve of";
    printMat(matrix);
    answer = diagMatSolve(matrix);
    printVec(answer);
    std::cout<<"\n";


Output from the lines above:

    Diagonal solve of
    [ 1 0 0 20 ]
    [ 0 1.21 0 20 ]
    [ 0 0 5442.59 20 ]

    [ 20 16.5289 0.00367472 ]

**Implementation/Code:** The following is the code for diagMatSolve(const std::vector<std::vector<double>>& diagMatrix)  

    std::vector<double> diagMatSolve(const std::vector<std::vector<double>>& diagMatrix){
        std::vector<double> answer;
        for(unsigned int i =0; i < diagMatrix.size();++i){
            if(diagMatrix[i][i]==0){answer.push_back(0);}
            else {
                answer.push_back(diagMatrix[i][diagMatrix[i].size() - 1] / diagMatrix[i][i]);
            }
        }
        return answer;
    }
