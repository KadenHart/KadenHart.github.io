# Generate Square Symmetric Diagonally Dominant Matrix  

**Routine Name:**           genSymmetricDiagDominantMat

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will generate a square Symmetric Diagonally Dominant matrix

**Input:** double low, double high, int size

**Output:** std::vector<std::vector<double>> matrix

**Usage/Example:**  

    std::cout<<"random square symmetric diagonally dominant matrix low: 1.0, high: 10.0, Size:5";
    matrix = genSymmetricDiagDominantMat(1.0,10.0,5);
    printMat(matrix);
    std::cout<<"\n";


Output from the lines above:

    random square symmetric diagonally dominant matrix low: 1.0, high: 10.0, Size:5
    [ 31.0015 6.95405 6.25369 4.0244 6.13567 ]
    [ 6.95405 20.686 1.27875 4.08273 1.07045 ]
    [ 6.25369 1.27875 16.7246 4.73338 3.58257 ]
    [ 4.0244 4.08273 4.73338 19.7038 7.5661 ]
    [ 6.13567 1.07045 3.58257 7.5661 18.3548 ]

**Implementation/Code:** The following is the code for genSymmetricDiagDominantMat(double low, double high, int size)

    std::vector<std::vector<double>> genSymmetricDiagDominantMat(double low, double high, int size){
        auto matrix = genSquareDiagDominantMat(low,high,size);
        for(int i =0; i <size;i++){
            for (int j = i; j <size; ++j) {
                matrix[i][j] = matrix[j][i];
            }
        }
        return matrix;
    }
