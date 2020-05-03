# Upper Triangular Matrix Solve

**Routine Name:**           upperTMatSolve

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the solution vector for an Upper Triangular matrix

**Input:** const std::vector<std::vector<double>>& matrix

**Output:** std::vector<double> answer

**Usage/Example:**  

    matrix = {\{1,1,1,20},{0,1.21,5,20},{0,0,7,20}\};
    std::cout<<"Upper Triangular solve of";
    printMat(matrix);
    answer = upperTMatSolve(matrix);
    printVec(answer);
    std::cout<<"\n";


Output from the lines above:

    Upper Triangular solve of
    [ 1 1 1 20 ]
    [ 0 1.21 5 20 ]
    [ 0 0 7 20 ]

    [ 12.4203 4.72255 2.85714 ]

**Implementation/Code:** The following is the code for upperTMatSolve(const std::vector<std::vector<double>>& matrix)

    std::vector<double> upperTMatSolve(const std::vector<std::vector<double>>& matrix){
        std::vector<std::vector<double>> answer = matrix;
        for(unsigned int i =0; i < answer.size()-1;++i){
            for(unsigned int j =i+1; j < answer[i].size()-1;++j){
                if(answer[j][j]==0){break;}
                if(answer[i][j]==0){break;}
                double ratio = answer[i][j]/answer[j][j];
                for(unsigned int k =j;k<answer[i].size();++k){
                    answer[i][k] = answer[i][k] - ratio*answer[j][k];
                }
            }

        }
        return diagMatSolve(answer);
    }
