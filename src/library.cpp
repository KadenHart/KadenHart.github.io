#pragma clang diagnostic push
#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"
#pragma ide diagnostic ignored "openmp-use-default-none"
#include "library.hpp"
#include <iostream>
#include <cmath>
#include <cfloat>
#include <vector>
#include <omp.h>
#include <random>

// Basic routines
double absError(double computed, double actual){
    return std::abs(actual - computed);
}
int doublePrecision(int maxPrecision){  //used to check machine precision on the central difference form of f(x) = e^x at x = pi answer should be e^pi.
    double pi = M_PI;
    double e = M_E;
    double error = 5, newError, hh = 1.0/1.0;
    int precision = -1;

    for (int i=1; i<maxPrecision;++i){
        newError = std::abs(pow(e,pi) - (((double)(pow(e,pi+hh) - pow(e,pi-hh))/(double)((pi+hh) - (pi - hh)))));
        if (newError <= error || newError ==0){
            error = newError;
            precision = i;
        }
        else{
            break;
        }

        hh = hh/2;
    }

    //std::cout<<"Double Error: "<< error<<std::endl;
    return precision;
}
double relError(double computed, double actual){
    return std::abs((actual - computed)/ actual);
}
int singlePrecision(int maxPrecision){  //used to check machine precision on the central difference form of f(x) = e^x at x = pi answer should be e^pi.
    float pi = M_PI;
    float e = M_E;
    float error = 5, newError, hh = 1.0/1.0;
    int precision = -1;

    for (int i=1; i<maxPrecision;++i){
        newError = std::abs(powf(e,pi) - (((float)(powf(e,pi+hh) - powf(e,pi-hh))/(float)((pi+hh) - (pi - hh)))));
        if (newError <= error || newError ==0){
            error = newError;
            precision = i;
        }
        else{
            break;
        }

        hh = hh/2;
    }
    //std::cout<<"Single Error: "<< error<<std::endl;
    return precision;
}
//x≈1.096327788292240187224006868725774624523189807363408824495262094888955008877488472442044026351833693544073747220676874491102970453662676747971345332569704084553 from wolfram
// Root Finding
double fixedPointIteration(double start, int maxiters){ // x cosh(x)+x^3=π
    auto pChange = DBL_MAX;
    auto cChange =DBL_MAX;
    double x = start;
    double xn;
    for(int i=0; i < maxiters && std::abs(cChange) <=std::abs(pChange)&& cChange!=0;++i) {
        pChange = cChange;
        xn = std::cbrt(M_PI - x*cosh(x));
        cChange = x - xn;
        x = xn;
        //std::cout <<i<<": "<<x<<"\n"; //used to watch convergence
    }
    return x;
}
double bisectionRoot(double low, double high){ // x cosh(x)+x^3=π
    int machinePrecision = doublePrecision(100);
    auto fx = [&](double x){
        return x*x*x+x*cosh(x)-M_PI;
    };
    double middle = (high+low)/2;
    double fmiddle = fx(middle);
    double fhigh = fx(high);
    double flow = fx(low);
    for(int i =0; i <machinePrecision;++i){ //skips one so the last run returns middle
        if(flow == 0) return low;
        if(fhigh == 0) return high;
        if(fmiddle ==0)return middle;
        if(flow*fhigh>=0) return DBL_MAX;
        if(flow*fmiddle<=0){
            high = middle;
        }
        else{
            low = middle;
        }

        middle = (high+low)/2;
        fmiddle = fx(middle);
        fhigh = fx(high);
        flow = fx(low);
    }
    return middle;
}
double newtonsRoot(double start, int maxiters){ // x cosh(x)+x^3=π
    auto pChange = DBL_MAX;
    auto cChange =DBL_MAX;
    int precision = doublePrecision(100);
    double h = 1;
    for(int i =0;i<precision;i++){
        h = h/2;
    }
    double x = start;
    double xn;
    for(int i=0; i < maxiters && std::abs(cChange) <=std::abs(pChange)&& cChange!=0;++i) {
        pChange = cChange;
        xn = std::cbrt(M_PI - x*cosh(x)) - (std::cbrt(M_PI - (x-h)*cosh(x-h))-std::cbrt(M_PI - (x+h)*cosh(x+h)))/2*h;
        cChange = x - xn;
        x = xn;
        //std::cout <<i<<": "<<x<<"\n"; //used to watch convergence
    }
    return x;
}
double secantRoot(double start, int maxiters){ // x cosh(x)+x^3=π
    auto pChange = DBL_MAX;
    auto cChange =DBL_MAX;
    double x = start;
    double xn,xp;
    auto fx = [&](double y){
        return (M_PI - y*y*y)/cosh(y);
    };
    xp= fx(1.09);
    for(int i=0; i < maxiters && std::abs(cChange) <=std::abs(pChange)&& cChange!=0;++i) {
        pChange = cChange;
        xn = xp- (fx(x)*x-fx(x)*xp)/(fx(x)-fx(xp));
        cChange = x - xn;
        xp =x;
        x = xn;
        //std::cout <<i<<": "<<x<<"\n"; //used to watch convergence
    }
    return x;
}
double mixedNewtRoot(double low, double high, int maxiters){ // x cosh(x)+x^3=π
    int machinePrecision = doublePrecision(100);
    auto fx = [&](double x){
        return x*x*x+x*cosh(x)-M_PI;
    };
    double middle = (high+low)/2;
    double fmiddle = fx(middle);
    double fhigh = fx(high);
    double flow = fx(low);
    for(int i =0; i <machinePrecision;++i){ //skips one so the last run returns middle
        if(flow == 0) return low;
        if(fhigh == 0) return high;
        if(fmiddle ==0)return middle;
        if(flow*fhigh>=0) return DBL_MAX;
        if(flow*fmiddle<=0){
            high = middle;
        }
        else{
            low = middle;
        }

        middle = (high+low)/2;
        fmiddle = fx(middle);
        fhigh = fx(high);
        flow = fx(low);
        if(std::abs(low-high) < .25){
            break;
        }
    }
    return newtonsRoot(middle, maxiters);
}
double mixedSecantRoot(double low, double high, int maxiters){ // x cosh(x)+x^3=π
    int machinePrecision = doublePrecision(100);
    auto fx = [&](double x){
        return x*x*x+x*cosh(x)-M_PI;
    };
    double middle = (high+low)/2;
    double fmiddle = fx(middle);
    double fhigh = fx(high);
    double flow = fx(low);
    for(int i =0; i <machinePrecision;++i){ //skips one so the last run returns middle
        if(flow == 0) return low;
        if(fhigh == 0) return high;
        if(fmiddle ==0)return middle;
        if(flow*fhigh>=0) return DBL_MAX;
        if(flow*fmiddle<=0){
            high = middle;
        }
        else{
            low = middle;
        }

        middle = (high+low)/2;
        fmiddle = fx(middle);
        fhigh = fx(high);
        flow = fx(low);
        if(std::abs(low-high) < .01){
            break;
        }
    }
    return secantRoot(middle, maxiters);
}
std::vector<double> multiBisection(double step, int numRoots){
    auto fx = [&](double x){
        return sin(M_PI*x*2+3.7);
    };
    auto bisect = [&](double low,double high){
        auto fx = [&](double x){
            return sin(M_PI*x*2+3.7);
        };
        int machinePrecision = doublePrecision(100);
        double middle = (high+low)/2;
        double fmiddle = fx(middle);
        double fhigh = fx(high);
        double flow = fx(low);
        for(int i =0; i <machinePrecision;++i){ //skips one so the last run returns middle
            if(flow == 0) return low;
            if(fhigh == 0) return high;
            if(fmiddle ==0)return middle;
            if(flow*fhigh>=0) return DBL_MAX;
            if(flow*fmiddle<=0){
                high = middle;
            }
            else{
                low = middle;
            }

            middle = (high+low)/2;
            fmiddle = fx(middle);
            fhigh = fx(high);
            flow = fx(low);
        }
        return middle;
    };
    std::vector<double> roots;
    double range[2] = {1.1,68.3};
    double current = range[0]+step;
    double low = range[0];
    if(fx(low)==0){roots.push_back(current);}
    while(current<=range[1]&&roots.size()<numRoots){
        if(fx(current)==0){roots.push_back(current);}
        if(fx(current)*fx(low)<0){
            roots.push_back(bisect(low,current));
        }
        low = current;
        current +=step;
    }
    return roots;
}
std::vector<double> multiNewtons(double step, int numRoots){
    auto fx = [&](double x){
        return sin(M_PI*x*2+3.7);
    };
    auto newton = [&](double start){
        auto fx = [&](double x){
            return sin(M_PI*x*2+3.7);
        };
        auto fpx = [&](double x){
            return cos(M_PI*x*2+3.7)*2*M_PI;
        };
        auto pChange = DBL_MAX;
        auto cChange =DBL_MAX;
        int precision = doublePrecision(100);
        double h = 1;
        for(int i =0;i<precision;i++){
            h = h/2;
        }
        double x = start;
        double xn;
        for(int i=0; i < 100 && cChange!=0;++i) {
            pChange = cChange;
            xn = x - fx(x) / fpx(x);
            cChange = x - xn;
            x = xn;
            //std::cout <<i<<": "<<x<<"\n"; //used to watch convergence
        }
        return x;
    };
    std::vector<double> roots;
    double range[2] = {1.1,68.3};
    double current = range[0]+step;
    double low = range[0];
    if(fx(low)==0){roots.push_back(current);}
    while(current<=range[1]&&roots.size()<numRoots){
        if(fx(current)==0){roots.push_back(current);}
        if(fx(current)*fx(low)<0){
            roots.push_back(newton(current));
        }
        low = current;
        current +=step;
    }
    return roots;
}
std::vector<double> multiSecant(double step, int numRoots){
    auto fx = [&](double x){
        return sin(M_PI*x*2+3.7);
    };
    auto secant = [&](double start){
        auto fx = [&](double x){
            return sin(M_PI*x*2+3.7);
        };
        auto pChange = DBL_MAX;
        auto cChange =DBL_MAX;
        double x = start;
        double xn,xp;
        xp= x-.01;
        for(int i=0; i < 100 && std::abs(cChange) <=std::abs(pChange)&& cChange!=0;++i) {
            pChange = cChange;
            xn = x- fx(x)*((x-xp)/(fx(x)-fx(xp)));
            cChange = x - xn;
            xp =x;
            x = xn;
            //std::cout <<i<<": "<<x<<"\n"; //used to watch convergence
        }
        return x;
    };
    std::vector<double> roots;
    double range[2] = {1.1,68.3};
    double current = range[0]+step;
    double low = range[0];
    if(fx(low)==0){roots.push_back(current);}
    while(current<=range[1]&&roots.size()<numRoots){
        if(fx(current)==0){roots.push_back(current);}
        if(fx(current)*fx(low)<0){
            roots.push_back(secant(current));
        }
        low = current;
        current +=step;
    }
    return roots;
}

//Vector Math###########################################################################################################

double oneNorm(const std::vector<double>& vector){
    double norm =0;
    for(double thing : vector){
        norm += std::abs(thing);
    }
    return norm;
}
double twoNorm(const std::vector<double>& vector) {
    double norm =0;
    for(double thing : vector){
        norm += thing*thing;
    }
    return std::sqrt(norm);
}
double infNorm(const std::vector<double>& vector) {
    double norm =0;
    for(double thing : vector){
        if(std::abs(thing)>norm){
            norm = thing;
        }
    }
    return norm;
}
double absErrorOneNorm(const std::vector<double>& approx, const std::vector<double>& exact){
    if(approx.size()!=exact.size()){ return DBL_MAX;}
    std::vector<double> combo;
    for(unsigned int i =0;i<approx.size();i++){
        combo.push_back(approx[i]-exact[i]);
    }
    return oneNorm(combo);
}
double relErrorOneNorm(const std::vector<double>& approx, const std::vector<double>& exact){
    if(approx.size()!=exact.size()){ return DBL_MAX;}
    std::vector<double> combo;
    for(unsigned int i =0;i<approx.size();i++){
        combo.push_back(approx[i]-exact[i]);
    }
    return oneNorm(combo)/oneNorm(approx);
}
double absErrorTwoNorm(const std::vector<double>& approx, const std::vector<double>& exact){
    if(approx.size()!=exact.size()){ return DBL_MAX;}
    std::vector<double> combo;
    for(unsigned int i =0;i<approx.size();i++){
        combo.push_back(approx[i]-exact[i]);
    }
    return twoNorm(combo);
}
double relErrorTwoNorm(const std::vector<double>& approx, const std::vector<double>& exact){
    if(approx.size()!=exact.size()){ return DBL_MAX;}
    std::vector<double> combo;
    for(unsigned int i =0;i<approx.size();i++){
        combo.push_back(approx[i]-exact[i]);
    }
    return twoNorm(combo)/oneNorm(approx);
}
double absErrorInfNorm(const std::vector<double>& approx, const std::vector<double>& exact){
    if(approx.size()!=exact.size()){ return DBL_MAX;}
    std::vector<double> combo;
    for(unsigned int i =0;i<approx.size();i++){
        combo.push_back(approx[i]-exact[i]);
    }
    return infNorm(combo);
}
double relErrorInfNorm(const std::vector<double>& approx, const std::vector<double>& exact){
    if(approx.size()!=exact.size()){ return DBL_MAX;}
    std::vector<double> combo;
    for(unsigned int i =0;i<approx.size();i++){
        combo.push_back(approx[i]-exact[i]);
    }
    return infNorm(combo)/infNorm(approx);
}
std::vector<double> vectorAdd(const std::vector<double>& v1, const std::vector<double>& v2){
    if(v1.size()!=v2.size()){ return std::vector<double> {0};}
    std::vector<double> answer;
    for(unsigned int i =0; i < v1.size();++i){
        answer.push_back(v1[i]+v2[i]);
    }
    return answer;
}
std::vector<double> vectorSub(const std::vector<double>& v1, const std::vector<double>& v2){
    if(v1.size()!=v2.size()){ return std::vector<double> {0};}
    std::vector<double> answer;
    for(unsigned int i =0; i < v1.size();++i){
        answer.push_back(v1[i]-v2[i]);
    }
    return answer;
}
std::vector<double> vectorScale(const std::vector<double>& v1, double scale){
    std::vector<double> answer;
    answer.reserve(v1.size());
for(double i : v1){
        answer.push_back(i*scale);
    }
    return answer;
}
double dotProduct(const std::vector<double>& v1, const std::vector<double>& v2){
    double answer =0;
    if(v1.size()!=v2.size()){ return answer;}
    for(unsigned int i =0; i < v1.size();++i){
        answer+=v1[i]*v2[i];
    }
    return answer;
}
std::vector<double> crossProduct(const std::vector<double>& v1, const std::vector<double>& v2){
    if(v1.size()!=v2.size()){ return std::vector<double> {0};}
    unsigned int size = v1.size();
    std::vector<double> answer;
    for(unsigned int i =0; i < v1.size();++i){
        answer.push_back(v1[(i+1)%size]*v2[(i+2)%size]-v1[(i+2)%size]*v2[(i+1)%size]);
    }
    return answer;
}
std::vector<double> saxpy(const std::vector<double>& v1, const std::vector<double>& v2, double scale){ //really daxpy
    return vectorAdd(vectorScale(v1,scale),v2);
}
std::vector<double> matTimesVector(const std::vector<std::vector<double>>& matrix, const std::vector<double>& v){
    if (matrix[0].size()!=v.size()){ return std::vector<double>{0};}
    std::vector<double> answer;
    answer.reserve(matrix.size());
#pragma omp parallel for
    for(unsigned int i =0; i < matrix.size();++i){
        answer.push_back(dotProduct(matrix[i],v));
    }
    return answer;
}

//Matrix Math
void printMat(const std::vector<std::vector<double>>& matrix){
    std::cout<<"\n[ ";
    for(unsigned int i =0; i <matrix.size();++i){
        for(unsigned int j =0; j <matrix[i].size();++j) {
            std::cout<<matrix[i][j]<<" ";
        }
        if(i < matrix.size()-1) {
            std::cout << "]\n[ ";
        }else{
            std::cout<<"]\n";
        }
    }
}
void printVec(const std::vector<double>& vector){
    std::cout<<"\n[ ";
    for(double thing : vector){
        std::cout << thing <<" ";
    }
    std::cout<<"]\n";
}
void printVec(const std::vector<unsigned int>& vector){
    std::cout<<"\n[ ";
    for(unsigned int thing : vector){
        std::cout << thing <<" ";
    }
    std::cout<<"]\n";
}
std::vector<double> diagMatSolve(const std::vector<std::vector<double>>& diagMatrix){
    std::vector<double> answer;
    for(unsigned int i =0; i < diagMatrix.size();++i){
        if(diagMatrix[i][i]==0){answer.push_back(0);}
        else {
            answer.push_back(diagMatrix[i][diagMatrix[i].size() - 1] / diagMatrix[i][i]);
        }
    }
    return answer;
}
std::vector<double> upperTMatSolve(const std::vector<std::vector<double>>& matrix){
    std::vector<std::vector<double>> answer = matrix;
    for(unsigned int i =0; i < answer.size()-1;++i){
        for(unsigned int j =i+1; j < answer[i].size()-1;++j){
            if(answer[j][j]==0){break;}
            if(answer[i][j]==0){break;}
            double ratio = answer[i][j]/answer[j][j];
            for(unsigned int k =j;k<answer[i].size();++k){
                answer[i][k] = answer[i][k] - ratio*answer[j][k];
            }
        }

    }
    return diagMatSolve(answer);
}
std::vector<double> lowerTMatSolve(const std::vector<std::vector<double>>& matrix){
    std::vector<std::vector<double>> answer = matrix;
    for(int i =answer.size()-1; i > 0;--i){
        for(int j =i-1; j >= 0;--j){
            if(answer[j][j]==0){break;}
            if(answer[i][j]==0){break;}
            double ratio = answer[i][j]/answer[j][j];
            for(int k =j;k>=0;--k){
                answer[i][k] = answer[i][k] - ratio*answer[j][k];
            }
            answer[i][answer[i].size()-1] -= ratio*answer[j][answer[j].size()-1];
        }
    }
    return diagMatSolve(answer);
}
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
std::vector<double> gaussianSolve(std::vector<std::vector<double>>& matrix){
    refMat(matrix);
    return upperTMatSolve(matrix);
}
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
std::vector<double> luSolve(std::vector<std::vector<double>> matrix){
    luFactorization(matrix);
    return upperTMatSolve(matrix);
}
std::vector<double> luPivoting(std::vector<std::vector<double>>& matrix, std::vector<unsigned int>& indices) {
    //Lower matrix is where the zeros should be in the upper matrix. Diagonals of the lower matrix are assumed to be one
    std::vector<unsigned int> indexV;
    for (unsigned int i = 0; i < matrix.size(); ++i) {
        indexV.push_back(i);
    }
    double uCoefficients[matrix.size()][matrix.size()];
    for (unsigned int i = 1; i < matrix.size(); ++i) {

        std::vector<double> maxV;
        for (unsigned int j = 0; j < matrix.size(); ++j) {
            maxV.push_back(0);
        }
        for (unsigned int j = i - 1; j < matrix.size(); j++) {
            maxV[j] = std::abs(matrix[indexV[j]][j]);
            for (unsigned int k = j + 1; k < matrix.size(); ++k) {
                if (std::abs(matrix[indexV[j]][k]) > maxV[j]) {
                    maxV[j] = std::abs(matrix[indexV[j]][k]);
                }
            }
        }

        // pick the smallest row
        if (i != matrix.size() - 1) {
            unsigned int smallestIndex = 0;
            double smallest = maxV[0];
            for (unsigned int j = 1; j < maxV.size(); ++j) {
                if (maxV[j] < smallest) {
                    smallest = maxV[j];
                    smallestIndex = j;
                }
            }
            unsigned int temp = indexV[i - 1];
            indexV[i - 1] = indexV[smallestIndex];
            indexV[smallestIndex] = temp;
        }

#pragma omp parallel for
        for (unsigned int j = i; j < matrix.size(); ++j) {
            if (matrix[indexV[j]][i - 1] == 0) { uCoefficients[indexV[j]][i - 1] = 0; }
            else if (matrix[indexV[i - 1]][i - 1] == 0) { uCoefficients[indexV[j]][i - 1] = 0; }
            else {
                double ratio = matrix[indexV[j]][i - 1] / matrix[indexV[i - 1]][i - 1];
                uCoefficients[indexV[j]][i - 1] = ratio;
                for (unsigned int k = 0; k < matrix[indexV[j]].size(); ++k) {
                    matrix[indexV[j]][k] = matrix[indexV[j]][k] - ratio * matrix[indexV[i - 1]][k];
                }
            }
        }
    }
    for (unsigned int i = 1; i < matrix.size(); ++i) {
        for (unsigned int j = 0; j < i; ++j) {
            matrix[indexV[i]][j] = uCoefficients[indexV[i]][j];
        }
    }

    //diagonal reduction
    for (unsigned int i = 0; i < matrix.size() - 1; ++i) {
        for (unsigned int j = i + 1; j < matrix[indexV[i]].size() - 1; ++j) {
            if (matrix[indexV[j]][j] == 0) { break; }
            if (matrix[indexV[i]][j] == 0) { break; }
            double ratio = matrix[indexV[i]][j] / matrix[indexV[j]][j];
            for (unsigned int k = j; k < matrix[indexV[i]].size(); ++k) {
                matrix[indexV[i]][k] = matrix[indexV[i]][k] - ratio * matrix[indexV[j]][k];
            }
        }

    }

    //diagonal solve
    std::vector<double> answer;
    for (unsigned int i = 0; i < matrix.size(); ++i) {
        answer.push_back(matrix[indexV[i]][matrix[indexV[i]].size() - 1] / matrix[indexV[i]][i]);
    }
    indices = indexV;
    return answer;
}
//TS6
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
std::vector<std::vector<double>> genSymmetricMat(double low, double high, int size){
    auto matrix = genSquareMat(low,high,size);
    for(int i =0; i <size;i++){
        for (int j = i; j <size; ++j) {
            matrix[i][j] = matrix[j][i];
        }
    }
    return matrix;
}
std::vector<std::vector<double>> genSymmetricDiagDominantMat(double low, double high, int size){
    auto matrix = genSquareDiagDominantMat(low,high,size);
    for(int i =0; i <size;i++){
        for (int j = i; j <size; ++j) {
            matrix[i][j] = matrix[j][i];
        }
    }
    return matrix;
}
std::vector<double> gaussSeidelSolve(std::vector<std::vector<double>>& matrix, int maxIters){
    double accuracy = .0001;
    std::vector<double> answer, oldAnswer;
    std::vector<double> pChange, cChange;
    for(unsigned int i =0; i <matrix.size();++i){
        answer.push_back(0);
        pChange.push_back(DBL_MAX);
        cChange.push_back(0);
        oldAnswer.push_back(0);
    }
    for(unsigned int i =0; i <maxIters;++i){

        for(unsigned int j =0; j < matrix.size();++j){
            double temp = 0;
            for(unsigned int k =0; k <matrix[j].size();++k){
                if(k==matrix[j].size()-1){
                    temp +=matrix[j][k];
                }
                else if(k<j){
                    temp -= answer[k]*matrix[j][k];
                }
                else if(k>j){
                    temp -= oldAnswer[k]*matrix[j][k];
                }
            }
            temp = temp/matrix[j][j];
            cChange[j] = std::abs(answer[j]-temp);
            oldAnswer[j]=answer[j];
            answer[j]=temp;
        }/*
        for(unsigned int j =0;j<answer.size();++j){
            if(cChange[j]>pChange[j]){ return answer;}
        }
        for(unsigned int j =0;j<answer.size();++j){
            if(cChange[j]>accuracy){ break;}
            if(j==answer.size()-1){ return answer;}
        }*/
        pChange = cChange;
        //std::cout<<i<<"\n"; // use this to count iterations
        //printVec(answer);
    }

    return answer;
}











































