#include <iostream>
#include <random>
#include <fstream>
#include <string>
class Matrix {
    public:
        double** matrix;
        int height, width;
        Matrix(double** matrix, int height, int width) {
            this->matrix = matrix;
            this->height = height;
            this->width = width;
        }
        double* get_chars() {
            double* chars = new double[this->width];
            double col_char;
            for (size_t i = 0; i < this->width; i++)
            {
                col_char = 0;
                for (size_t j = 0; j < this->height; j++)
                {
                    col_char += this->matrix[i][j] > 0 ? 0 : abs(this->matrix[i][j]);
                }
                chars[i] = col_char;
            }
            return chars;
        }
        void recombine_cols() {
            double* chars = this->get_chars();
            double* tmp_matrix;
            double tmp;
            int item;
            for (int counter = 1; counter < this->width; counter++)
            {
                tmp = chars[counter];
                tmp_matrix = this->matrix[counter];
                item = counter - 1;
                while (item >= 0 && chars[item] > tmp)
                {
                    this->matrix[item + 1] = this->matrix[item];
                    this->matrix[item] = tmp_matrix;
                    chars[item + 1] = chars[item];
                    chars[item] = tmp;
                    item--;
                }
            }
        }
        double sum_cols_with_negatives() {
            double* chars = this->get_chars();
            double sum = 0;
            for (size_t i = 0; i < this->width; i++)
            {
                if (chars[i] > 0) {
                    for (size_t j = 0; j < this->height; j++)
                    {
                        sum += this->matrix[i][j];
                    }
                }
            }
            delete chars;
            return sum;
        }
};

void fill_randomly(double*** matrix, int width, int height, double from, double to) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> dist(from, to - 1); // Полуинтервал [from,to)
    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            (*matrix)[i][j] = dist(rng);
        }
    }
}
const bool DEBUG = true;
int main()
{
    setlocale(LC_ALL, "Russian");
    srand(42);
    int width, height;
    double from, to, ** values;
    bool fill_random = true;
    if (DEBUG) {
        width = 10;
        height = 10;
        from = -10;
        to = 10;
    }
    else {
        std::string filename;
        std::cout << "Введите путь до файла: ";
        std::cin >> filename;
        std::ifstream in(filename);
        if (in.is_open())
        {
            in >> width >> height >> from >> to;
        }
        in.close();
    }
    values = new double* [width];
    for (size_t i = 0; i < width; i++)
    {
        values[i] = new double[height];
    }
    if (fill_random) {

        fill_randomly(&values, width, height, from, to);
    }
    else {
        std::cout << "Введите значения в матрице (через пробел)";
        for (size_t i = 0; i < width; i++)
        {
            for (size_t j = 0; j < height; j++)
            {
                std::cin >> values[i][j];
            }
        }
    }

    Matrix* matrix = new Matrix(values, height, width);
    double* data = matrix->get_chars();
    for (size_t i = 0; i < width; i++)
    {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
    matrix->recombine_cols();
    data = matrix->get_chars();
    for (size_t i = 0; i < width; i++)
    {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl << matrix->sum_cols_with_negatives();
}

