# Lower and Upper triangularization of a matrix

**Routine Name:**           luFactorization

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the LU factorization of a matrix Lower matrix is where the zeros should be in the upper matrix. Diagonals of the lower matrix are assumed to be one  

**Input:** std::vector<std::vector<double>>& matrix  

**Output:** NONE: Modifies the given matrix 

**Usage/Example:**  

    matrix = {\{1,1,1,1},{4,3,-1,6},{3,5,3,4}\};
    std::cout<<"LU of";
    printMat(matrix);
    luFactorization(matrix);
    printMat(matrix);
    std::cout<<"\n";


Output from the lines above:

    LU of
    [ 1 1 1 1 ]
    [ 4 3 -1 6 ]
    [ 3 5 3 4 ]

    [ 1 1 1 1 ]
    [ 4 -1 -5 2 ]
    [ 3 -2 -10 5 ]

**Implementation/Code:** The following is the code for luFactorization(std::vector<std::vector<double>>& matrix)

    void luFactorization(std::vector<std::vector<double>>& matrix){
        //Lower matrix is where the zeros should be in the upper matrix. Diagonals of the lower matrix are assumed to be one

        double uCoefficients[matrix.size()][matrix.size()];
        for(unsigned int i=1;i<matrix.size();++i){

    #pragma omp parallel for
            for(unsigned int j=i;j<matrix.size();++j){
                if(matrix[j][i-1]==0){uCoefficients[j][i-1]=0; }
                else if(matrix[i-1][i-1]==0){uCoefficients[j][i-1]=0; }
                else {
                    double ratio = matrix[j][i - 1] / matrix[i - 1][i - 1];
                    uCoefficients[j][i - 1] = ratio;
                    for (unsigned int k = 0; k < matrix[j].size(); ++k) {
                        matrix[j][k] = matrix[j][k] - ratio * matrix[i - 1][k];
                    }
                }
            }
        }
        for(unsigned int i=1;i<matrix.size();++i) {
            for (unsigned int j = 0; j < i; ++j) {
                matrix[i][j]=uCoefficients[i][j];
            }
        }
    }
