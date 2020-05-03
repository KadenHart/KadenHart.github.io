# Absolute error of One Norm

**Routine Name:**           absErrorOneNorm

**Author:** Kaden Hart

**Language:** C++ Compiles with cMake as designated in CMakeLists.txt

**Description/Purpose:** This routine will compute the absolute error of approximating one vector with another for the one norm.

**Input:** vector<double> vector, vector<double> approx

**Output:** double

**Usage/Example:**  

    std::vector<double> vector = {1,2,3,4,5,6,7,8,9,10};
    std::vector<double> approx = {0,2,3,4,5,6,7,8,9,10};
    absErrorOneNorm(approx,vector);


Output from the lines above:

    1

**Implementation/Code:** The following is the code for absErrorOneNorm(const std::vector<double>& approx, const std::vector<double>& exact)

    double absErrorOneNorm(const std::vector<double>& approx, const std::vector<double>& exact){
        if(approx.size()!=exact.size()){ return DBL_MAX;}
        std::vector<double> combo;
        for(unsigned int i =0;i<approx.size();i++){
            combo.push_back(approx[i]-exact[i]);
        }
        return oneNorm(combo);
    }
