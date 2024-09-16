#include <iostream>
using namespace std;

// Recursive function to calculate binomial coefficient
int binomialCoeff(int row, int col) {
    if (col == 0 || col == row)
        return 1;
    return binomialCoeff(row - 1, col - 1) + binomialCoeff(row - 1, col);
}

// Function to print Pascal's Triangle
void printPascalTriangle(int levels) {
    for (int line = 0; line < levels; line++) {
        for (int elem = 0; elem <= line; elem++) {
            cout << binomialCoeff(line, elem) << " ";
        }
        cout << endl;
    }
}

int main() {
    int levels = 3; // Number of levels in the triangle
    printPascalTriangle(levels);
    return 0;
}