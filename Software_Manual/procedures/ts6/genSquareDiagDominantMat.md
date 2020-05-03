# Generate Square Diagonally Dominant Matrix
**Routine Name:**           genSquareDiagDominantMat

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will generate a square Diagonally Dominant matrix

**Input:** double low, double high, int size

**Output:** std::vector<std::vector<double>> matrix

**Usage/Example:**  

    std::cout<<"random square diagonally dominant matrix low: 1.0, high: 10.0, Size:5";
    matrix = genSquareDiagDominantMat(1.0,10.0,5);
    printMat(matrix);
    std::cout<<"\n";


Output from the lines above:

    random square diagonally dominant matrix low: 1.0, high: 10.0, Size:5
    [ 31.0015 9.23805 6.34892 5.63822 9.77634 ]
    [ 6.95405 20.686 8.09644 1.66691 3.96865 ]
    [ 6.25369 1.27875 16.7246 1.17777 8.01435 ]
    [ 4.0244 4.08273 4.73338 19.7038 6.86332 ]
    [ 6.13567 1.07045 3.58257 7.5661 18.3548 ]

**Implementation/Code:** The following is the code for genSquareDiagDominantMat(double low, double high, int size)

    std::vector<std::vector<double>> genSquareDiagDominantMat(double low, double high, int size){
        auto matrix = genSquareMat(low, high, size);
        for(unsigned int i =0; i <matrix.size();i++){
            double rowtotal = std::abs(matrix[i][i])*-2;
            for(auto thing : matrix[i]){
                rowtotal += std::abs(thing);
            }
            if(rowtotal>0){
                matrix[i][i] += rowtotal;
            }
        }
        return matrix;
    }
