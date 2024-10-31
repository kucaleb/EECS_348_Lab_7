#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void read_matrix_from_file(
    const char *file_name,
    vector<vector<double>> &matrix_1,
    vector<vector<double>> &matrix_2) {
    ifstream file(file_name);
    int matrix_size;
    vector<int> tokens;
    string token;
    string line;
    file >> matrix_size;

    matrix_1 = vector<vector<double>>(matrix_size, vector<double>(matrix_size));
    matrix_2 = vector<vector<double>>(matrix_size, vector<double>(matrix_size));

    while (getline(file, line)){
        istringstream linestream(line);
        while (linestream >> token)
            tokens.push_back(stod(token));
    }
    for (int r = 0; r < matrix_size; r++) {
        for (int c = 0; c < matrix_size; c++){
            matrix_1.at(r).at(c) = tokens.at(c + r * matrix_size);
            matrix_2.at(r).at(c) = tokens.at((matrix_size * matrix_size) + c + (r * matrix_size));
        }
    }

}

void print_matrix(const vector<vector<double>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            cout << matrix.at(i).at(j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void print_matrix(const vector<vector<double>> &matrix_1, const vector<vector<double>> &matrix_2) {
    cout << "Matrix 1: " << endl;
    print_matrix(matrix_1);
    cout << "Matrix 2: " << endl;
    print_matrix(matrix_2);
}

vector<vector<double>> operator+(vector<vector<double>> matrix_1, vector<vector<double>> matrix_2) {
    for (int r = 0; r < matrix_1.size(); r++) {
        for (int c = 0; c < matrix_1.size(); c++) {
            matrix_1.at(r).at(c) += matrix_2.at(r).at(c);
        }
    }
    return matrix_1;
}

vector<vector<double>> operator*(vector<vector<double>> matrix_1, vector<vector<double>> matrix_2) {
    vector<vector<double>> product(matrix_1.size(), vector<double>(matrix_1.size()));
    for (int r = 0; r < matrix_1.size(); r++) {
        for (int c = 0; c < matrix_1.size(); c++) {
            for (int k = 0; k < matrix_1.size(); k++)
                product.at(r).at(c) += matrix_1.at(r).at(k) * matrix_2.at(k).at(c);
        }
    }
    return product;
}

void get_diagonal_sum(const vector<vector<double>> &matrix) {
    double sum;
    for (int i = 0; i < matrix.size(); ++i) {
        sum += matrix[i][i];
    }
    cout << "sum: " << sum << endl;
    sum = 0;
    for (int i = 0, j = matrix.size() - 1; i < matrix.size(); ++i, --j) {
        sum += matrix[i][j];
    }
    cout << "sum: " << sum << endl;
}

void swap_matrix_row(vector<vector<double>> matrix, int row1, int row2) {
    if (0 <= row1 && 0 <= row2 && row1 < matrix.size() && row2 < matrix.size() && row1 != row2) {
        swap(matrix[row1], matrix[row2]);
        print_matrix(matrix);
    } else {
        cout << "Invalid";
    }
}

int main(int argc, char *argv[]) {
    vector<vector<double>> matrix_1, matrix_2;
    read_matrix_from_file("matrix.txt", matrix_1, matrix_2);
    cout << "print_matrix" << endl;
    print_matrix(matrix_1, matrix_2);

    auto add_matrix = matrix_1 + matrix_2;
    cout << "operator+ overloading" << endl;
    print_matrix(add_matrix);

    auto multiply_matrix = matrix_1 * matrix_2;
    cout << "operator* overloading" << endl;
    print_matrix(multiply_matrix);

    cout << "get matrix diagonal sum" << endl;
    get_diagonal_sum(matrix_1);

    cout << "swap matrix rows" << endl;
    swap_matrix_row(matrix_1, 0, 1);
    swap_matrix_row(matrix_1, 0, 100);
}