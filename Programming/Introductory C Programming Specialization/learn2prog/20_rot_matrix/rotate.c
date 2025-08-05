#define MAX 10

void rotate(char matrix[10][10]) {
  char temp[MAX][MAX];
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      temp[j][MAX - 1 - i] = matrix[i][j];
    }
  }
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      matrix[i][j] = temp[i][j];
    }
  }
}
