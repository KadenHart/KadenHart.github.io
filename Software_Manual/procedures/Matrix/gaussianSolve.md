# Gaussian Solve

**Routine Name:**           gaussianSolve

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will find a solution to a linear system of equations (Matrix)

**Input:** std::vector<std::vector<double>>& matrix

**Output:**  std::vector<double> answer, NONE: modifies given matrix to REF form

**Usage/Example:**  

    matrix = {\{7,1,1,20},{5,1.21,1,20},{1,1,1,20}\};
    std::cout<<"Solution of";
    printMat(matrix);
    answer=gaussianSolve(matrix);
    printVec(answer);
    std::cout<<"\n";


Output from the lines above:

    Solution of
    [ 7 1 1 20 ]
    [ 5 1.21 1 20 ]
    [ 1 1 1 20 ]

    [ 0 0 20 ]

**Implementation/Code:** The following is the code for gaussianSolve(std::vector<std::vector<double>>& matrix)

    std::vector<double> gaussianSolve(std::vector<std::vector<double>>& matrix){
        refMat(matrix);
        return upperTMatSolve(matrix);
    }
