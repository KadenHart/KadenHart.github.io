# Row Echelon Form Matrix

**Routine Name:**           refMat

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the REF of the given matrix

**Input:** std::vector<std::vector<double>>& matrix

**Output:** NONE: modifies the given matrix

**Usage/Example:**  

    matrix = {\{7,1,1,20},{5,1.21,1,20},{1,1,1,20}\};
    std::cout<<"REF of";
    printMat(matrix);
    refMat(matrix);
    printMat(matrix);
    std::cout<<"\n";


Output from the lines above:

    REF of
    [ 7 1 1 20 ]
    [ 5 1.21 1 20 ]
    [ 1 1 1 20 ]

    [ 7 1 1 20 ]
    [ 0 0.495714 0.285714 5.71429 ]
    [ 0 0 0.363112 7.26225 ]

**Implementation/Code:** The following is the code for refMat(std::vector<std::vector<double>>& matrix)

    void refMat(std::vector<std::vector<double>>& matrix){
        for(unsigned int i=1;i<matrix.size();++i){
            for(unsigned int j=i;j<matrix.size();++j){
                if(matrix[j][i-1]==0){break;}
                if(matrix[i-1][i-1]==0){break;}
                double ratio = matrix[j][i-1]/matrix[i-1][i-1];
                for(unsigned int k = 0;k<matrix[j].size();++k){
                    matrix[j][k]= matrix[j][k] - ratio*matrix[i-1][k];
                }
            }
        }
    }
