# Generate Square Symmetric Matrix  

**Routine Name:**           genSymmetricMat

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will generate a square Symmetric matrix

**Input:** double low, double high, int size

**Output:** std::vector<std::vector<double>> matrix

**Usage/Example:**  

    std::cout<<"random square symmetric matrix low: 1.0, high: 10.0, Size:5";
    matrix = genSymmetricMat(1.0,10.0,5);
    printMat(matrix);
    std::cout<<"\n";


Output from the lines above:

    random square symmetric matrix low: 1.0, high: 10.0, Size:5
    [ 7.53624 6.95405 6.25369 4.0244 6.13567 ]
    [ 6.95405 5.75787 1.27875 4.08273 1.07045 ]
    [ 6.25369 1.27875 9.35734 4.73338 3.58257 ]
    [ 4.0244 4.08273 4.73338 9.16582 7.5661 ]
    [ 6.13567 1.07045 3.58257 7.5661 7.3216 ]

**Implementation/Code:** The following is the code for genSymmetricMat(double low, double high, int size)

    std::vector<std::vector<double>> genSymmetricMat(double low, double high, int size){
        auto matrix = genSquareMat(low,high,size);
        for(int i =0; i <size;i++){
            for (int j = i; j <size; ++j) {
                matrix[i][j] = matrix[j][i];
            }
        }
        return matrix;
    }
