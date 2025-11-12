/* 과제 구현 목표
1. 관계 행렬 입력 기능
2. 동치 관계 판별 기능
3. 동치 관계일 경우 동치류 출력 가능
4. 폐포 구현 기능
5. 추가 기능 구현 */
#include <iostream>
#include <vector>
using namespace std;

// 2차원 벡터 별칭 선정
using Matrix = vector<vector<int>>;

class Relation {
public:
    Matrix relationship;

    // 생성자 - 관계 행렬 데이터 입력
    Relation() {
        cout << "5 x 5 크기의 관계행렬을 한 행씩 입력하세요.\n";
        relationship.resize(5); // 5행으로 초기화
        
        // 각 행에 원소 삽입 - 0 또는 1 
        for(int r = 0; r < 5; r++) {
            cout << r+1 << "행: ";
            for(int c = 0; c < 5; c++) {
                int e; cin >> e;
                relationship[r].push_back(e);
            }
        }

        cout << '\n';
    }

    // 순서쌍 출력문
    void printRelation(Matrix mat) {
        cout << "[관계 R의 포함된 순서쌍]\n";
        for(int r = 0; r < 5; r++) {
            for(int c= 0; c < 5; c++) {
                if(mat[r][c] == 1)
                    cout << "(" << r+1 << ", " << c+1 << ") ";
            }
        }
        cout << '\n' << '\n';
    }

    // 부울곱 연산함수
    Matrix boolean(Matrix matA, Matrix matB) {
        Matrix result(5, vector<int>(5, 0)); // 0으로 채워진 5x5 행렬 생성

        // 부울 연산
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                for(int k = 0; k < 5; k++) {
                    result[i][j] |= matA[i][k] && matB[k][j];
                }
            }
        }

        return result;
    }

    // 반사관계 판별
    bool isReflexive(Matrix mat) {
        for(int i = 0; i < 5; i++) {
            if(mat[i][i] != 1) {
                cout << "이 관계는 반사관계가 아닙니다.\n";
                return false;
            }
        }

        cout << "이 관계는 반사관계입니다.\n";
        return true;
    } 

    // 대칭관계 판별
    bool isSymmetric(Matrix mat) {
        for(int r = 0; r < 5; r++) {
            for(int c = 0; c < 5; c++) {
                if(mat[r][c] == 1 && mat[c][r] != 1) {
                    cout << "이 관계는 대칭관계가 아닙니다.\n";
                    return false;
                }
            }
        }

        cout << "이 관계는 대칭관계입니다.\n";
        return true;
    }

    // 추이관계 판별
    bool isTransitive(Matrix mat) {
        Matrix power = mat; // 계속 제곱해질 행렬, 기존 matrix 복사
        Matrix combined = mat; // 최종 MR+로 기존 MR과 비교할 행렬, 기존 mat 복사
        
        for(int i = 0; i < 5; i++) { // 원래 기수만큼 반복해야하지만 과제는 5x5 행렬이므로 5번 반복
            power = this->boolean(power, mat); // R^n 행렬

            for(int r = 0; r < 5; r++) {
                for(int c = 0; c < 5; c++) {
                    combined[r][c] |= power[r][c]; // 둘다 1인 원소만 남음 
                }
            }
        }

        bool result = combined == mat; // R^5가 아니면 이전의 함수도 부분집합에 속하지 않게됨
        
        if(result) 
            cout << "이 관계는 추이관계입니다.\n";
        else
            cout << "이 관계는 추이관계가 아닙니다.\n";

        return result;
    }
};

int main() {
    cout << "집합 A = [1, 2, 3, 4, 5]" << '\n';
    Relation R; // 객체 생성시 생성자 호출과 함께 원소 입력
    R.printRelation(R.relationship); // 관계 순서쌍 출력
    
    bool isR = R.isReflexive(R.relationship); // 반사관계 판단
    bool isS = R.isSymmetric(R.relationship); // 대칭관계 판단
    bool isT = R.isTransitive(R.relationship); // 추이관계 판단

    return 0;
}