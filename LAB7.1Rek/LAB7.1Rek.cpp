#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std; // Додано

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i, int j);
void Print(int** a, const int rowCount, const int colCount, int i, int j);
void Sort(int** a, const int rowCount, const int colCount, int j0 = 0);
void Change(int** a, const int col1, const int col2, int rowCount);
int RecursiveCalc(int** a, const int rowCount, const int colCount, int& S, int& k, int rowIndex = 0, int colIndex = 0);

int main() {
    srand((unsigned)time(NULL));
    int Low = -26;
    int High = 23;
    int rowCount = 8;
    int colCount = 6;
    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Create(a, rowCount, colCount, Low, High, 0, 0);
    Print(a, rowCount, colCount, 0, 0);
    Sort(a, rowCount, colCount);
    Print(a, rowCount, colCount, 0, 0);

    int S = 0;
    int k = 0;
    RecursiveCalc(a, rowCount, colCount, S, k);

    cout << "S = " << S << endl;
    cout << "k = " << k << endl;

    Print(a, rowCount, colCount, 0, 0);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i, int j) {
    a[i][j] = Low + rand() % (High - Low + 1);
    if (j < colCount - 1)
        Create(a, rowCount, colCount, Low, High, i, j + 1);
    else if (i < rowCount - 1)
        Create(a, rowCount, colCount, Low, High, i + 1, 0);
}

void Print(int** a, const int rowCount, const int colCount, int i, int j) {
    cout << setw(4) << a[i][j];
    if (j < colCount - 1)
        Print(a, rowCount, colCount, i, j + 1);
    else if (i < rowCount - 1) {
        cout << endl;
        Print(a, rowCount, colCount, i + 1, 0);
    }
    else
        cout << endl << endl;
}

void Change(int** a, const int col1, const int col2, int rowCount) {
    if (rowCount <= 0) {
        return;
    }

    int tmp = a[rowCount - 1][col1];
    a[rowCount - 1][col1] = a[rowCount - 1][col2];
    a[rowCount - 1][col2] = tmp;

    Change(a, col1, col2, rowCount - 1);
}

void Sort(int** a, const int rowCount, const int colCount, int j0) {
    if (j0 >= colCount - 1) {
        return;
    }

    for (int j1 = 0; j1 < colCount - j0 - 1; j1++) {
        if ((a[0][j1] > a[0][j1 + 1]) ||
            (a[0][j1] == a[0][j1 + 1] && a[1][j1] < a[1][j1 + 1]) ||
            (a[0][j1] == a[0][j1 + 1] && a[1][j1] == a[1][j1 + 1] && a[2][j1] > a[2][j1 + 1])) {
            Change(a, j1, j1 + 1, rowCount);
        }
    }

    Sort(a, rowCount, colCount, j0 + 1);
}

int RecursiveCalc(int** a, const int rowCount, const int colCount, int& S, int& k, int rowIndex, int colIndex) {
    if (rowIndex >= rowCount) {
        return S;
    }

    if (colIndex < colCount) {
        if (!(a[rowIndex][colIndex] % 2 == 0 && (a[rowIndex][colIndex] > 0))) {
            S += a[rowIndex][colIndex];
            k++;
            a[rowIndex][colIndex] = 0;
        }

        return RecursiveCalc(a, rowCount, colCount, S, k, rowIndex, colIndex + 1);
    }

    return RecursiveCalc(a, rowCount, colCount, S, k, rowIndex + 1, 0);
}