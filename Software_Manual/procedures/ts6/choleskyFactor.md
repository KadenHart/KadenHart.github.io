# Cholesky Factor

**Routine Name:**           choleskyFactor

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the Cholesky factorization of the given matrix

**Input:** std::vector<std::vector<double>>& matrix

**Output:** NONE: modifies the given matrix

**Usage/Example:**  

    std::vector<std::vector<double>> matrix = {\{4,12,-16},{12,37,-43},{-16,-43,98}\};
    std::vector<double> answer;
    std::cout<<"Cholesky of";
    printMat(matrix);
    choleskyFactor(matrix);
    printMat(matrix);
    std::cout<<"\n";


Output from the lines above:

    Cholesky of
    [ 4 12 -16 ]
    [ 12 37 -43 ]
    [ -16 -43 98 ]

    [ 1 3 -4 ]
    [ 3 1 5 ]
    [ -4 5 1 ]

**Implementation/Code:** The following is the code for choleskyFactor(std::vector<std::vector<double>>& matrix)

    void choleskyFactor(std::vector<std::vector<double>>& matrix){
        //Check For symmetry
        for(unsigned int i =0; i < matrix.size()/2;i++){
            for(unsigned int j =0; j < matrix.size();j++){
                if(matrix[i][j] != matrix[j][i]){
                    return;
                }
            }
        }
        luFactorization(matrix);
        //remove uppper triangular
        for(unsigned int i =0; i < matrix.size();i++) {
            matrix[i][i]= 1;
        }
        for(unsigned int i =0; i < matrix.size();i++){
            for(unsigned int j =i; j < matrix.size();j++){
                matrix[i][j]=matrix[j][i];
            }
        }

    }
