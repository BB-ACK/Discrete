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
    }

    // 순서쌍 출력문
    void printRelation(Matrix mat) {
        cout << "[관계 R의 포함된 순서쌍]\n";
        for(int r = 0; r < 5; r++) {
            for(int c= 0; c < 5; c++) {
                if(mat[r][c] == 1)
                    cout << "(" << r << ", " << c << ")";
            }
        }
        cout << '\n';
    }

    // 반사관계 판별
    bool isReflexive(Matrix mat) {
        this->printRelation(mat); // 순서쌍 출력

        for(int i = 0; i < 5; i++) {
            if(mat[i][i] != 1) {
                cout << "이 관계는 반사관계가 아닙니다.\n";
                return false;
            }
        }

        cout << "이 관계는 반사관계입니다.\n";
        return true;
    } 

};

int main() {

    return 0;
}