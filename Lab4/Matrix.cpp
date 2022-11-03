#include <iostream>
#include <fstream>
#include <string>


double f(int i, int j) {
    return (abs(3.7 - j) - 2) * (i - 4.3) * pow(2, -i);
}

int read_file(std::string filename) {
    int size = 0;
    std::ifstream in(filename);
    if (in.is_open())
    {
        in >> size;
    }
    in.close();
    return size;
}

double** make_matrix(int n) {
    double** matrix = new double* [n];
    if(!matrix) throw std::runtime_error("Memory hasn't been alloceted");
    for (size_t i = 0; i < n; i++)
    {
        matrix[i] = new double[n];
        if(!matrix[i]) throw std::runtime_error("Memory hasn't been alloceted");
        for (size_t j = 0; j < n; j++)
        {
            matrix[i][j] = f(i, j);
        }
    }
    return matrix;
}

void write_file(double** matrix, std::string filename, int n) {
    std::ofstream out;
    out.open(filename);
    if (out.is_open())
    {
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                out << matrix[i][j] << " ";
            }
            out << std::endl;
        }
    }
}

int step1(std::string input_filename, std::string output_filename) {
    int size = read_file(input_filename);
    double** matrix = make_matrix(size);
    write_file(matrix, output_filename, size);
    for (size_t i = 0; i < size; i++)
    {
        delete matrix[i];
    }
    delete matrix;
    return size;
}