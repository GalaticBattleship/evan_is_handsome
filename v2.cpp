#include <stdio.h>
#include <cmath>
constexpr double PI = 3.1415926;

double dtoRad(double d) {
    return d*PI/180.0;
}
double rtoDeg(double r) {
    return r*180.0/PI;
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

class leg {
    public:
        double _len1;
        double _len2;

        double _theta1
        double theta2;
        
        double _baseX;
        double _baseY;
        double _baseZ;

        leg(double len1, double len2,
        double baseX = 0.0,
        double baseY = 0.0,
        double baseZ = 0.0,
        ) : _len1(len1),
            _len2(len2),
            _baseX(baseX),
            _baseY(baseY),
            _baseZ(baseZ),
    //note used ai check if error
    //forward kine
    // T = Base * Rz(theta1) * Tx(L1)
    //             * Ry(theta2) * Tx(L2)}
        4x4Matrix forwardM const {
            4x4Matrix base = 4x4Matrix::identity();

        // 設定腿部基座在機器人座標系中的位置。
        base.at(0, 3) = _baseX;
        base.at(1, 3) = _baseY;
        base.at(2, 3) = _baseZ;

        // 依照關節的實際順序相乘。
        return base
            * 4x4Matrix::rotationZ(_theta1)
            * 4x4Matrix::translationX(_len1)
            * 4x4Matrix::rotationY(_theta2)
            * 4x4Matrix::translationX(_len2);
        }
    // 輸入腳端世界座標 x、y、z。
    // 計算 theta1、theta2。
    //
    // 回傳 true：找到一組幾何解。
    // 回傳 false：目標位置不可達，或不符合此機構模型。
    //
    // 注意：此處採用 theta2 為正時腳端向下的座標約定。
    // note used ai check if error
    //reverse kine
    bool inverseKinematics(double x,
                           double y,
                           double z) {
        // 先將世界座標轉換成相對於腿部基座的座標。
        double localX = x - baseX_;
        double localY = y - baseY_;
        double localZ = z - baseZ_;

        // 水平旋轉角由 XY 平面中的方向決定。
        double horizontalDistance =
            std::hypot(localX, localY);

        // 此模型的兩段連桿在旋轉後的局部 XZ 平面內。
        // 第二關節旋轉不改變局部 Y 座標。
        // 因此腳端必須落在此模型所允許的平面上。
        //
        // 浮點數比較保留少量誤差。
        if (horizontalDistance < 1e-9) {
            // 水平距離為 0 時，水平方向不唯一。
            // 這個簡化模型不在此處猜測方向。
            return false;
        }

        theta1_ = std::atan2(localY, localX);

        // 旋轉到局部平面後：
        // q = horizontalDistance - L1
        // z = localZ
        //
        // 因為 theta2 正值代表腳端向下，
        // 局部垂直座標的符號在這裡反轉。
        double q = horizontalDistance - len1_;
        double vertical = -localZ;

        // 兩連桿平面逆向運動學的餘弦定理。
        double r2 = q * q + vertical * vertical;

        double c2 =
            (r2 - len2_ * len2_) /
            (2.0 * len2_ * 1.0);

        // 以上只是單關節繞 Y 軸的旋轉模型，
        // 第一段水平偏移已由 len1_ 扣除。
        //
        // 本模型中第二關節之後只有 L2 一段連桿，
        // 因此沒有第二段以上的平面雙連桿角度解。
        //
        // 此處必須由機構的實際關節位置決定，
        // 不能把雙連桿公式直接套在單一 Pitch 軸上。

        (void)c2;

        // 這個兩關節結構有一個重要限制：
        // theta1 決定水平方位，theta2 決定連桿的俯仰。
        // 若 len1 是水平固定偏移，則 L2 的長度固定，
        // 可達位置必須符合 q² + vertical² = L2²。
        //
        // 所以先檢查目標是否位於可達圓弧上。
        double distance = std::sqrt(r2);

        if (std::abs(distance - len2_) > 1e-6) {
            return false;
        }

        // 以幾何角度直接求解第二關節。
        // 水平投影 q 與向下的 vertical 決定俯仰角。
        theta2_ = std::atan2(vertical, q);

        return true;
    }
    double returnLen1() const { return _len1; }
    double returnLen2() const { return _len2; }
    double returnTheta1() const { return _theta1; }
    double returnTheta2() const { return _theta2; }
}

int main() {

}



//note fix pos reset
