# Solution using Lower and Upper triangularization of a matrix

**Routine Name:**           luSolve

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the solution of a matrix using the LU factorization of a matrix Lower matrix is where the zeros should be in the upper matrix. Diagonals of the lower matrix are assumed to be one  

**Input:** std::vector<std::vector<double>>& matrix  

**Output:** std::vector<double> answer

**Usage/Example:**  

    matrix = {\{1,1,1,1},{4,3,-1,6},{3,5,3,4}\};
    std::cout<<"LU Solution of";
    printMat(matrix);
    answer = luSolve(matrix);
    printVec(answer);
    std::cout<<"\n";


Output from the lines above:

    LU Solution of
    [ 1 1 1 1 ]
    [ 4 3 -1 6 ]
    [ 3 5 3 4 ]

    [ 1 0.5 -0.5 ]

**Implementation/Code:** The following is the code for luSolve(std::vector<std::vector<double>> matrix)

    std::vector<double> luSolve(std::vector<std::vector<double>> matrix){
        luFactorization(matrix);
        return upperTMatSolve(matrix);
    }
