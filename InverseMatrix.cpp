/* 과제 구현 목표
1. 행렬 입력기능 - 정방행렬 n x n
2. 행렬식을 이용한 역행렬 계산
3. 가우스 조던 소거법을 이용한 역행렬 계산
4. 결과 출력 및 비교 기능
5. 추가기능 구현 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPSILON = 1e-9; // 부동소수점 오차 고려

class InverseMatrix {
public:
    int degree;
    vector<vector<double>> mat;

    // 생성자 - 데이터 입력
    InverseMatrix() {
        // 차수 입력
        cout << "정방행렬의 차수를 입력하세요: ";
        cin >> this->degree;
        this->mat.resize(degree);

        // 원소 입력
        for(int i = 0; i < this->degree; i++) {
            cout << i + 1 << "행: ";
            for(int j = 0; j < degree; j++) {
                double data; cin >> data;
                this->mat[i].push_back(data);
            }
        }
    }
    
    // 행렬 출력문
    void printMat(vector<vector<double>> &matrix) {
        for(int i = 0; i < matrix.size(); i++) {
            cout << "| ";
            for(int j = 0; j < matrix.size(); j++) {
                cout << matrix[i][j] << "  ";
            }
            cout << "|" << '\n';
        }
    }

    // 전치행렬 반환
    vector<vector<double>> transepose(vector<vector<double>> matrix) {
        int size = matrix.size();
        vector<vector<double>> transe(size);

        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                transe[i].push_back(matrix[j][i]);
            }
        }

        return transe;
    }

    // 소행렬 계산
    vector<vector<double>> getMinor(vector<vector<double>> matrix, int row, int col) {
        vector<vector<double>> minor; // 리턴할 소행렬

        for(int i = 0; i < matrix.size(); i++) {
            if(i == row) continue;
            vector<double> rowElement; // 행요소들
            for(int j = 0; j < matrix.size(); j++) {
                if(j == col) continue;

                rowElement.push_back(matrix[i][j]);
            }
            minor.push_back(rowElement);
        }

        return minor;
    }

    // 행렬식 계산
    double getDeterminant(vector<vector<double>> matrix) {
        int size = matrix.size();
        
        // 1차, 2차의 경우
        if(size == 1)
            return matrix[0][0];
        else if(size == 2)
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

        // 3차 이상
        double derterminant = 0;
        for(int i = 0; i < size; i++) {
            derterminant += (pow(-1, i) * matrix[0][i] * this->getDeterminant(this->getMinor(matrix, 0, i)));
        }

        return derterminant;
    }

    // 역행렬 존재여부
    bool hasInverse() {
        double det = this->getDeterminant(this->mat);
        if(det == 0) return false;
        else return true;
    }

    // 행렬식을 이용한 역행렬 계산
    vector<vector<double>> inverseByDet() {
        double det = this->getDeterminant(this->mat);

        // 1차, 2차의 경우
        if(this->degree == 1)
            return vector<vector<double>>(1, vector<double>(1, 1.0 / this->mat[0][0]));
        else if(this->degree == 2) {
            vector<vector<double>> two(2, vector<double>(2));
            two[0][0] = this->mat[1][1] / det;
            two[0][1] = -this->mat[0][1] / det;
            two[1][0] = -this->mat[1][0] / det;
            two[1][1] = this->mat[0][0] / det;

            return two;
        }

        vector<vector<double>> inverse;
        for(int i = 0; i < this->degree; i++) {
            vector<double> row;
            for(int j = 0; j < this->degree; j++) {
                vector<vector<double>> minor = this->getMinor(this->mat, i, j);
                row.push_back((pow(-1, i+j) * this->getDeterminant(minor)) / det);
            }
            inverse.push_back(row);
        }

        inverse = this->transepose(inverse); // 전치행렬변환
        
        return inverse;
    }

    // 단위 행렬 추가 
    vector<vector<double>> addIdentity() {
        vector<vector<double>> added = this->mat;

        for(int i = 0; i < this->degree; i++) {
            for(int j = 0; j < this->degree; j++) {
                if(i == j)
                    added[i].push_back(1);
                else
                    added[i].push_back(0);
            }
        }

        return added;
    }

    // 소거 과정
    vector<vector<double>> elimination(vector<vector<double>> &matrix) {
        for(int i = 0; i < this->degree; i++) {
            // 만약 피봇이 0이라면 교환해야함 - 피봇 교환 로직
            if(matrix[i][i] == 0.0) {
                int swapRow = -1;
                for(int r = i+1; r < this->degree; r++) {
                    if(matrix[r][i] != 0) {
                        swapRow = r;
                        break;
                    }
                }
                
                if(swapRow != -1)
                    swap(matrix[i], matrix[swapRow]); // 행 교환
            }

            // 이제부터 소거
            double pivot = matrix[i][i]; // 기준 피봇

            // 원소들 피봇으로 나누기 
            for(int c = 0; c < matrix[i].size(); c++) {
                matrix[i][c] /= pivot;
            }
            

            // 나머지 열의 원소를 0으로 만들기 
            for(int j = 0; j < this->degree; j++) {
                if(i != j) { // 기준 행은 무시
                    double factor = matrix[j][i];

                    // 각원소를 기준행의 값에 맞춰서 빼줌 
                    for(int c = 0; c < matrix[i].size(); c++) {
                        matrix[j][c] -= matrix[i][c] * factor; 
                    }
                }
            }
        }

        // 결과 역행렬 반환
        vector<vector<double>> result(this->degree);
        for(int i = 0; i < matrix.size(); i++) {
            for(int j = matrix.size(); j < matrix[i].size(); j++) {
                result[i].push_back(matrix[i][j]);
            }
        }

        return result;
    }

    // 행렬이 같은지 판단
    bool equalMat(vector<vector<double>> &a, vector<vector<double>> &b) {
        // 사이즈 비교
        if(a.size() != b.size())
            return false;
        
        for(int i = 0; i < a.size(); i++) {
            // 열 개수 불일치
            if(a[i].size() != b[i].size())
                return false;

            for(int j = 0; j < a[i].size(); j++) {
                // 원소 불일치 
                if(abs(a[i][j] - b[i][j]) > EPSILON)
                    return false;
            }
        }

        return true;
    }

    // 상수 행렬 입력받기 - 추가과제파트
    vector<double> getConstants() {
        vector<double> c(this->degree);
        cout << "\n연립방정식의 상수 벡터를 입력하세요. " << '\n';

        for(int i = 0; i < this->degree; i++) {
            cout << i+1 << "행의 상수벡터: ";
            cin >> c[i];
        }

        return c;
    }

    // 연립방정식의 해 계산 
    vector<double> getSolution(vector<vector<double>> &matrix, vector<double> &constant) {
        vector<double> sol;

        for(int i = 0; i < this->degree; i++) {
            double sum = 0.0;
            for(int j = 0; j < this->degree; j++) {
                sum += matrix[i][j] * constant[j];
            }
            sol.push_back(sum);
        }

        return sol;
    }

};

int main() {
    InverseMatrix im;

    // 역행렬 존재 여부 확인
    if(!im.hasInverse())
        cout << '\n' << "역행렬이 존재하지 않습니다." << '\n';
    else {
        cout << '\n' << "행렬식으로 구한 역행렬: " << '\n';
        vector<vector<double>> inverseByDet = im.inverseByDet();
        im.printMat(inverseByDet);

        cout << '\n' << "가우스 소거법으로 구한 역행렬: " << '\n';
        vector<vector<double>> inverseByGause = im.addIdentity();
        inverseByGause = im.elimination(inverseByGause);
        im.printMat(inverseByGause);

        if(!im.equalMat(inverseByDet, inverseByGause)) {
            cout << '\n' << "두 방법의 결과가 동일하지 않습니다. " << '\n';
        }
        else {
            cout << '\n' << "두 방법의 결과가 동일합니다. " << '\n';
        }


        // 추가 구현 파트 - 역행렬을 이용한 연립방정식의 해
        vector<double> constant = im.getConstants();
        vector<double> solution = im.getSolution(inverseByGause, constant);

        // 해출력
        cout << '\n' << "역행렬을 이용한 연립방정식의 해: " << '\n';
        for(int i = 0; i < solution.size(); i++)
            cout << i+1 << "열 미지수: " << solution[i] << '\n';
    }

    return 0;
}