# Pivoting solution using Lower and Upper triangularization of a matrix

**Routine Name:**           luPivoting

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the solution of a matrix using pivoting and the LU factorization of a matrix Lower matrix is where the zeros should be in the upper matrix. Diagonals of the lower matrix are assumed to be one  

**Input:** std::vector<std::vector<double>>& matrix, std::vector<unsigned int>& indices

**Output:** std::vector<double> answer

**Usage/Example:**  

    matrix = {\{3,5,3,4},{4,3,-1,6},{1,1,1,1}\};
    std::cout<<"LU Pivoting Solution of";
    printMat(matrix);
    std::vector<unsigned int> indices;
    answer = luPivoting(matrix, indices);
    std::cout <<"Index Vector";
    printVec(indices);
    std::cout <<"Solution Vector";
    printVec(answer);
    std::cout<<"\n";


Output from the lines above:

    LU Pivoting Solution of
    [ 3 5 3 4 ]
    [ 4 3 -1 6 ]
    [ 1 1 1 1 ]
    Index Vector
    [ 2 1 0 ]
    Solution Vector
    [ 1 0.5 -0.5 ]

**Implementation/Code:** The following is the code for luPivoting(std::vector<std::vector<double>>& matrix, std::vector<unsigned int>& indices)

    std::vector<double> luPivoting(std::vector<std::vector<double>>& matrix, std::vector<unsigned int>& indices){
        //Lower matrix is where the zeros should be in the upper matrix. Diagonals of the lower matrix are assumed to be one
        std::vector<unsigned int> indexV;
        for(unsigned int i=0;i<matrix.size();++i){
            indexV.push_back(i);
        }
        double uCoefficients[matrix.size()][matrix.size()];
        for(unsigned int i=1;i<matrix.size();++i){

            std::vector<double> maxV;
            for(unsigned int j = 0; j < matrix.size();++j){
                maxV.push_back(0);
            }
            for(unsigned int j = i-1; j < matrix.size();j++){
                maxV[j] = std::abs(matrix[indexV[j]][j]);
                for(unsigned int k = j+1; k<matrix.size(); ++k){
                    if(std::abs(matrix[indexV[j]][k]) > maxV[j]){
                        maxV[j] = std::abs(matrix[indexV[j]][k]);
                    }
                }
            }

            // pick the smallest row
            if(i!=matrix.size()-1){
                unsigned int smallestIndex =0;
                double smallest = maxV[0];
                for(unsigned int j=1; j<maxV.size();++j){
                    if(maxV[j]<smallest){
                        smallest = maxV[j];
                        smallestIndex=j;
                    }
                }
                unsigned int temp = indexV[i-1];
                indexV[i-1] = indexV[smallestIndex];
                indexV[smallestIndex] = temp;
            }

    #pragma omp parallel for
            for(unsigned int j=i;j<matrix.size();++j){
                if(matrix[indexV[j]][i-1]==0){uCoefficients[indexV[j]][i-1]=0; }
                else if(matrix[indexV[i-1]][i-1]==0){uCoefficients[indexV[j]][i-1]=0; }
                else {
                    double ratio = matrix[indexV[j]][i - 1] / matrix[indexV[i - 1]][i - 1];
                    uCoefficients[indexV[j]][i - 1] = ratio;
                    for (unsigned int k = 0; k < matrix[indexV[j]].size(); ++k) {
                        matrix[indexV[j]][k] = matrix[indexV[j]][k] - ratio * matrix[indexV[i - 1]][k];
                    }
                }
            }
        }
        for(unsigned int i=1;i<matrix.size();++i) {
            for (unsigned int j = 0; j < i; ++j) {
                matrix[indexV[i]][j]=uCoefficients[indexV[i]][j];
            }
        }

        //diagonal reduction
        for(unsigned int i =0; i < matrix.size()-1;++i){
            for(unsigned int j =i+1; j < matrix[indexV[i]].size()-1;++j){
                if(matrix[indexV[j]][j]==0){break;}
                if(matrix[indexV[i]][j]==0){break;}
                double ratio = matrix[indexV[i]][j]/matrix[indexV[j]][j];
                for(unsigned int k =j;k<matrix[indexV[i]].size();++k){
                    matrix[indexV[i]][k] = matrix[indexV[i]][k] - ratio*matrix[indexV[j]][k];
                }
            }

        }

        //diagonal solve
        std::vector<double> answer;
        for(unsigned int i =0; i < matrix.size();++i){
            answer.push_back(matrix[indexV[i]][matrix[indexV[i]].size()-1]/matrix[indexV[i]][i]);
        }
        indices = indexV;
        return answer;


    }
