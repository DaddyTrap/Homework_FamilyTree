# include <iostream>
# define MAX 1002
using namespace std;

int data[MAX];
bool adjacent_matrix[MAX][MAX];

void Initialize() {
	for (int i = 0; i < MAX; i++) {
		data[i] = 0;
		for (int j = 0; j < MAX; j++) {
			adjacent_matrix[i][j] = 0;
		}
	}
}

int main(void) {
	Initialize();
	int vecNum, edgeNum;
	cin >> 
}