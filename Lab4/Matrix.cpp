#include <iostream>
#include <fstream>
#include <string>

// Функция из варианта
double f(int i, int j) {
    return (abs(3.7 - j) - 2) * (i - 4.3) * pow(2, -i);
}
// Чтение размера матрицы из файла
int read_file(std::string filename) {
    int size = 0;
    std::ifstream in(filename);// Открываем поток файла
    if (in.is_open())// Если открыт ...
    {
        in >> size;// То читаем данные из потока
    }
    in.close();// Не забываем закрыть поток
    return size;
}
// Выделение памяти и заполнение матрицы
double** make_matrix(int n) {
    double** matrix = new double* [n];
    if(!matrix) throw std::runtime_error("Memory hasn't been alloceted"); // Бросаем исключение если не получилось выделить память
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
// Запись матрицы в файл
void write_file(double** matrix, std::string filename, int n) {
    std::ofstream out;// Аналогично чтению
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
        delete[] matrix[i];
    }
    delete[] matrix;
    return size;
}