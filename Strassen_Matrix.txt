#include <iostream>
#include <vector>

using namespace std;

// Function to add two matrices
vector<vector<int>> addMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

// Function to subtract two matrices
vector<vector<int>> subtractMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return C;
}

// Function to multiply two matrices using Strassen's algorithm
vector<vector<int>> strassenMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    // Base case
    if (n == 1) {
        vector<vector<int>> C(1, vector<int>(1, 0));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Split matrices into quadrants
    int mid = n / 2;
    vector<vector<int>> A11(mid, vector<int>(mid, 0));
    vector<vector<int>> A12(mid, vector<int>(mid, 0));
    vector<vector<int>> A21(mid, vector<int>(mid, 0));
    vector<vector<int>> A22(mid, vector<int>(mid, 0));
    vector<vector<int>> B11(mid, vector<int>(mid, 0));
    vector<vector<int>> B12(mid, vector<int>(mid, 0));
    vector<vector<int>> B21(mid, vector<int>(mid, 0));
    vector<vector<int>> B22(mid, vector<int>(mid, 0));

    // Splitting matrix A into 4 quadrants
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];
        }
    }

    // Splitting matrix B into 4 quadrants
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }

    // Strassen's algorithm
    vector<vector<int>> P1 = strassenMultiply(addMatrices(A11, A22), addMatrices(B11, B22));
    vector<vector<int>> P2 = strassenMultiply(addMatrices(A21, A22), B11);
    vector<vector<int>> P3 = strassenMultiply(A11, subtractMatrices(B12, B22));
    vector<vector<int>> P4 = strassenMultiply(A22, subtractMatrices(B21, B11));
    vector<vector<int>> P5 = strassenMultiply(addMatrices(A11, A12), B22);
    vector<vector<int>> P6 = strassenMultiply(subtractMatrices(A21, A11), addMatrices(B11, B12));
    vector<vector<int>> P7 = strassenMultiply(subtractMatrices(A12, A22), addMatrices(B21, B22));

    // Calculate the result matrix C
    vector<vector<int>> C11 = addMatrices(subtractMatrices(addMatrices(P1, P4), P5), P7);
    vector<vector<int>> C12 = addMatrices(P3, P5);
    vector<vector<int>> C21 = addMatrices(P2, P4);
    vector<vector<int>> C22 = addMatrices(subtractMatrices(subtractMatrices(P1, P2), P3), P6);

    // Combine the results into a single matrix
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
    }

    return C;
}

// Function to display a matrix
void displayMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    // Example matrices to multiply
    vector<vector<int>> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int>> B = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

    cout << "Matrix A:" << endl;
    displayMatrix(A);

    cout << "\nMatrix B:" << endl;
    displayMatrix(B);

    vector<vector<int>> C = strassenMultiply(A, B);

    cout << "\nResultant Matrix C:" << endl;
    displayMatrix(C);

    return 0;
}
