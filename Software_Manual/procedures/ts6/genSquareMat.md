# Generate Square Matrix
**Routine Name:**           genSquareMat

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will Generate a square matrix

**Input:** double low, double high, int size

**Output:** std::vector<std::vector<double>> matrix

**Usage/Example:**  

    std::cout<<"random square matrix low: 1.0, high: 10.0, Size:5";
    matrix = genSquareMat(1.0,10.0,5);
    printMat(matrix);
    std::cout<<"\n";


Output from the lines above:

    random square matrix low: 1.0, high: 10.0, Size:5
    [ 7.53624 9.23805 6.34892 5.63822 9.77634 ]
    [ 6.95405 5.75787 8.09644 1.66691 3.96865 ]
    [ 6.25369 1.27875 9.35734 1.17777 8.01435 ]
    [ 4.0244 4.08273 4.73338 9.16582 6.86332 ]
    [ 6.13567 1.07045 3.58257 7.5661 7.3216 ]

**Implementation/Code:** The following is the code for genSquareMat(double low, double high, int size)

    std::vector<std::vector<double>> genSquareMat(double low, double high, int size){
        std::vector<std::vector<double>> matrix;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(low, high);
        for(int i =0; i <size;i++){
            std::vector<double> row;
            row.reserve(size);
            for (int j = 0; j < size; ++j) {
                row.push_back(dis(gen));
            }
            matrix.push_back(row);
        }
        return matrix;
    }
