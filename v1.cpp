#include <stdio.h>
#include <cmath>
constexpr double PI = 3.1415926;

double dtoRad(double d) {
    return d*PI/180.0;
}
double rtoDeg(double r) {
    return r*180.0/PI;
}

class leg {
    public:
        double _len;
        double _theta;
        Matrix(int len, int theta) {
            _len = len;
            _theta = theta;
        }
    int returnLen() {
        return _len;
    }
    int returnTheta() {
        return _theta;
    }
}
class 4x4Matrix {
    private:
        int rows, cols = 0;
        double data[4][4]
    public:
        Matrix(int r, int c) {
            rows = r;
            cols = c;

        }
    /*
    void assignMatrix() {
        for (int row = 0 ; row < rows ; row++) {
            for (int col = 0 ; col < cols ; col++) {
                std::cin >> data[row][col];
            }
        }
    }
    void assignSingle(const int *v, int rc) {
        int row = int(rc / 10);
        int col = (rc > 9) ? int(rc - row * 10) : rc;
        if (*v != 0) {
            data[row][col] = *v;
        } else {
             data[row][col] = 0;
        }
    }
    */
    void displayMatrix() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << data[i][j] << " ";
            }
            std::cout << '\n';
        }
    }
    /*
    double returnSignleValue(int rc) {
        int row = int(rc / 10);
        int col = (rc > 9) ? int(rc - row * 10) : rc;
        return data[row][col]
    }
    int returnRowsSize() {
        return rows;
    }
    int returnColsSize() {
        return cols;
    }
    */
    double& at(int r, int c) {
        return data[r][c];
    }
    double at(int r, int c) const {
        return data[r][c];
    }
    4x4Matrix operator*(const 4x4Matrix& rhs) const {
        4x4Matrix result;

        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                for (int k = 0; k < 4; ++k) {
                    result.at(row, col) +=
                        at(row, k) * rhs.at(k, col);
                }
            }
        }

        return result;
    }
    //https://linear.axler.net/LADR4e.pdf
    static 4x4Matrix identityM() {
        4x4Matrix re;
        for (int i = 0 ; i < 4 ; i++) {
            re.at(i, i) = 1.0;
        }
        return re;
    }
    //https://www.wolframalpha.com/input?i=rotation+matrix&assumption=%7B%22F%22%2C+%22RotationCalculator%22%2C+%22alpha%22%7D+-%3E%2230+%C2%B0%22&assumption=%7B%22FP%22%2C+%22RotationCalculator%22%2C+%22dir%22%7D+-%3E+%22plus%22&assumption=%7B%22FP%22%2C+%22RotationCalculator%22%2C+%22axis%22%7D+-%3E+%22y%22&lang=zh
    //https://mathworld.wolfram.com/RotationMatrix.html
    static 4x4Matrix rotationMforZ(double theta) {
        4x4Matrix re = identityM();
        double cos = std::cos();
        double sin = std::sin();
        T.at(0,0) = cos;
        T.at(0,1) = -sin;
        T.at(1,0) = sin;
        T.at(1,1) = cos;
        return re;
    }
    static 4x4Matrix rotationMforY(double theta) {
        4x4Matrix re = identityM();
        double cos = std::cos();
        double sin = std::sin();
        T.at(0,0) = cos;
        T.at(0,2) = sin;
        T.at(2,0) = -sin;
        T.at(2,2) = cos;
        return re;
    }
    //x is not used ig
    static 4x4Matrix rotationMforX(double theta) {
        4x4Matrix re = identityM();
        double cos = std::cos();
        double sin = std::sin();
        T.at(1,2) = cos;
        T.at(1,2) = -sin;
        T.at(2,1) = sin;
        T.at(2,2) = cos;
        return re;
    }
    //x rotation  matrix ends here
    static 4x4Matrix translationforX(double len) {
        4x4Matrix re = identityM();
        T.at(0,3) = len;
        return re;
    }
    static 4x4Matrix translationforZ(double height) {
        4x4Matrix re = identityM();
        T.at(2,3) = height;
        return T;
    }
}

int 

int main() {

}



//note fix pos reset
