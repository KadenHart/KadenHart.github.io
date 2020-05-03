# Lower Triangular Matrix Solve

**Routine Name:**           lowerTMatSolve

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the solution vector for a lower triangular matrix

**Input:** std::vector<std::vector<double>>& matrix

**Output:** std::vector<double> answer

**Usage/Example:**  

    matrix = {\{7,0,0,20},{5,1.21,0,20},{1,1,1,20}\};
    std::cout<<"Lower Triangular solve of";
    printMat(matrix);
    answer = lowerTMatSolve(matrix);
    printVec(answer);
    std::cout<<"\n";


Output from the lines above:

    Lower Triangular solve of
    [ 7 0 0 20 ]
    [ 5 1.21 0 20 ]
    [ 1 1 1 20 ]

    [ 2.85714 4.72255 12.4203 ]

**Implementation/Code:** The following is the code for lowerTMatSolve(const std::vector<std::vector<double>>& matrix)

    std::vector<double> lowerTMatSolve(const std::vector<std::vector<double>>& matrix){
        std::vector<std::vector<double>> answer = matrix;
        for(int i =answer.size()-1; i > 0;--i){
            for(int j =i-1; j >= 0;--j){
                if(answer[j][j]==0){break;}
                if(answer[i][j]==0){break;}
                double ratio = answer[i][j]/answer[j][j];
                for(int k =j;k>=0;--k){
                    answer[i][k] = answer[i][k] - ratio*answer[j][k];
                }
                answer[i][answer[i].size()-1] -= ratio*answer[j][answer[j].size()-1];
            }
        }
        return diagMatSolve(answer);
    }
