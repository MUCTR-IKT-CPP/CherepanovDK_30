#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

/**
 * @brief Выделяет память под двумерный массив размером N x N.
 * 
 * @param N Размерность массива.
 * @return Указатель на массив указателей (двумерный массив).
 */
double** allocateMatrix(int N) {
    double** matrix = new double*[N];
    for (int i = 0; i < N; ++i)
        matrix[i] = new double[N];
    return matrix;
}

/**
 * @brief Освобождает память, выделенную под двумерный массив.
 * 
 * @param matrix Указатель на двумерный массив.
 * @param N Размерность массива.
 */
void freeMatrix(double** matrix, int N) {
    for (int i = 0; i < N; ++i)
        delete[] matrix[i];
    delete[] matrix;
}

/**
 * @brief Заполняет двумерный массив случайными числами в диапазоне от 0 до 10.
 * 
 * @param matrix Указатель на двумерный массив.
 * @param N Размерность массива.
 */
void fillMatrix(double** matrix, int N) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            matrix[i][j] = rand() % 11;
}

/**
 * @brief Выводит двумерный массив на экран.
 * 
 * @param matrix Указатель на двумерный массив.
 * @param N Размерность массива.
 */
void printMatrix(double** matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << setw(6) << matrix[i][j];
        cout << endl;
    }
}

/**
 * @brief Выполняет сложение двух матриц A и B. Результат сохраняется в матрицу C.
 * 
 * @param A Первая матрица.
 * @param B Вторая матрица.
 * @param C Матрица, в которую будет сохранен результат сложения.
 * @param N Размерность матриц.
 */
void addMatrices(double** A, double** B, double** C, int N) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            C[i][j] = A[i][j] + B[i][j];
}

/**
 * @brief Выполняет умножение двух матриц A и B. Результат сохраняется в матрицу C.
 * 
 * @param A Первая матрица.
 * @param B Вторая матрица.
 * @param C Матрица, в которую будет сохранен результат умножения.
 * @param N Размерность матриц.
 */
void multiplyMatrices(double** A, double** B, double** C, int N) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }
}

/**
 * @brief Выполняет транспонирование матрицы A. Результат сохраняется в матрицу C.
 * 
 * @param A Матрица, которую необходимо транспонировать.
 * @param C Матрица, в которую будет сохранен результат транспонирования.
 * @param N Размерность матриц.
 */
void transposeMatrix(double** A, double** C, int N) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            C[j][i] = A[i][j];
}

/**
 * @brief Вычисляет определитель матрицы рекурсивным методом.
 * 
 * @param matrix Матрица, для которой необходимо вычислить определитель.
 * @param N Размерность матрицы.
 * @return Определитель матрицы.
 */
double determinant(double** matrix, int N) {
    if (N == 1)
        return matrix[0][0];
    
    double det = 0;
    double** submatrix = allocateMatrix(N - 1);
    
    for (int x = 0; x < N; x++) {
        int subi = 0;
        for (int i = 1; i < N; i++) {
            int subj = 0;
            for (int j = 0; j < N; j++) {
                if (j == x) continue;
                submatrix[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        det = det + (pow(-1, x) * matrix[0][x] * determinant(submatrix, N - 1));
    }
    
    freeMatrix(submatrix, N - 1);
    return det;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    
    int N;
    cout << "Введите размерность матриц (N): ";
    cin >> N;
    
    // Выделение памяти под матрицы
    double** A = allocateMatrix(N);
    double** B = allocateMatrix(N);
    double** C = allocateMatrix(N);
    
    // Заполнение матриц случайными числами
    fillMatrix(A, N);
    fillMatrix(B, N);
    
    cout << "Матрица A:" << endl;
    printMatrix(A, N);
    cout << "Матрица B:" << endl;
    printMatrix(B, N);
    
    int choice;
    cout << "\nВыберите операцию:\n";
    cout << "1. Сложение матриц A и B\n";
    cout << "2. Умножение матриц A и B\n";
    cout << "3. Транспонирование матрицы A или B\n";
    cout << "4. Определитель матрицы A или B\n";
    cin >> choice;
    
    switch (choice) {
        case 1:
            addMatrices(A, B, C, N);
            cout << "Результат сложения A и B (матрица C):" << endl;
            printMatrix(C, N);
            break;
        
        case 2:
            multiplyMatrices(A, B, C, N);
            cout << "Результат умножения A и B (матрица C):" << endl;
            printMatrix(C, N);
            break;
        
        case 3: {
            int matrixChoice;
            cout << "Выберите матрицу для транспонирования (1 - A, 2 - B): ";
            cin >> matrixChoice;
            if (matrixChoice == 1) {
                transposeMatrix(A, C, N);
                cout << "Транспонированная матрица A (матрица C):" << endl;
            } else {
                transposeMatrix(B, C, N);
                cout << "Транспонированная матрица B (матрица C):" << endl;
            }
            printMatrix(C, N);
            break;
        }
        
        case 4: {
            int matrixChoice;
            cout << "Выберите матрицу для нахождения определителя (1 - A, 2 - B): ";
            cin >> matrixChoice;
            double det;
            if (matrixChoice == 1)
                det = determinant(A, N);
            else
                det = determinant(B, N);
            cout << "Определитель выбранной матрицы: " << det << endl;
            break;
        }
        
        default:
            cout << "Неверный выбор операции!" << endl;
            break;
    }
    
    // Освобождение памяти
    freeMatrix(A, N);
    freeMatrix(B, N);
    freeMatrix(C, N);
    
    return 0;
}
