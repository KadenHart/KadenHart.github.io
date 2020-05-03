# Jacobian Solve

**Routine Name:**           jacobiSolve

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the answer to a system of equations using the jacobian iteration method

**Input:** std::vector<std::vector<double>>& matrix, int maxIters

**Output:** std::vector<double> answer

**Usage/Example:**  

    matrix = {\{1,1,1,20},{0,1.21,5,20},{0,0,7,20}\};
    std::cout<<"Jacobi Solution of";
    printMat(matrix);
    answer = jacobiSolve(matrix,100);
    printVec(answer);
    std::cout<<"\n";


Output from the lines above:

    Jacobi Solution of
    [ 1 1 1 20 ]
    [ 0 1.21 5 20 ]
    [ 0 0 7 20 ]

    [ 12.4203 4.72255 2.85714 ]

**Implementation/Code:** The following is the code for jacobiSolve(std::vector<std::vector<double>>& matrix, int maxIters)

    std::vector<double> jacobiSolve(std::vector<std::vector<double>>& matrix, int maxIters){
        double accuracy = .0001;
        std::vector<double> answer;
        std::vector<double> pChange, cChange;
        for(unsigned int i =0; i <matrix.size();++i){
            answer.push_back(0);
            pChange.push_back(DBL_MAX);
            cChange.push_back(0);
        }
        for(unsigned int i =0; i <maxIters;++i){

            for(unsigned int j =0; j < matrix.size();++j){
                double temp = 0;
                for(unsigned int k =0; k <matrix[j].size();++k){
                    if(k ==j){}
                    else if(k==matrix[j].size()-1){
                        temp +=matrix[j][k];
                    }
                    else{
                        temp -= answer[k]*matrix[j][k];
                    }
                }
                temp = temp/matrix[j][j];
                cChange[j] = std::abs(answer[j]-temp);
                answer[j]=temp;
            }
            for(unsigned int j =0;j<answer.size();++j){
                if(cChange[j]>pChange[j]){ return answer;}
            }
            for(unsigned int j =0;j<answer.size();++j){
                if(cChange[j]>accuracy){ break;}
                if(j==answer.size()-1){ return answer;}
            }
            pChange = cChange;
            //std::cout<<i<<"\n"; // use this to count iterations
            //printVec(answer);
        }

        return answer;
    }
