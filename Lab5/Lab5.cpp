#include <iostream>
#include <random>
#include <fstream>
#include <string>
class Matrix {
    public:
        double** matrix;
        int height, width;
        Matrix(double** matrix, int height, int width) {
            // Конструктор класса
            this->matrix = matrix;
            this->height = height;
            this->width = width;
        }
        double* get_chars() {
            // Получаем характеристический вектор для матрицы
            double* chars = new double[width];
            double col_char;
            for (size_t i = 0; i < width; i++)
            {
                col_char = 0;
                for (size_t j = 0; j < height; j++)
                {
                    col_char += matrix[i][j] > 0 ? 0 : abs(matrix[i][j]);
                }
                chars[i] = col_char;
            }
            return chars;
        }
        void recombine_cols() {
            // Перемещаем колонки
            double* chars = get_chars();
            double* tmp_matrix;
            double tmp;
            int item;
            // Сортировка вставками
            for (int counter = 1; counter < width; counter++)
            {
                tmp = chars[counter];
                tmp_matrix = matrix[counter];
                item = counter - 1;
                while (item >= 0 && chars[item] > tmp)
                {
                    matrix[item + 1] = matrix[item];
                    matrix[item] = tmp_matrix;
                    chars[item + 1] = chars[item];
                    chars[item] = tmp;
                    item--;
                }
            }
        }
        double sum_cols_with_negatives() {
            // Получаем сумму по всем колонкам с отрицательными числами
            double* chars = get_chars();
            double sum = 0;
            for (size_t i = 0; i < width; i++)
            {
                if (chars[i] > 0) {
                    for (size_t j = 0; j < height; j++)
                    {
                        sum += matrix[i][j];
                    }
                }
            }
            delete[] chars;
            return sum;
        }
};

void fill_randomly(double*** matrix, int width, int height, double from, double to) {
    // Заполняем матрицу рандомными числами
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
    // иф не нужен в блок схеме, просто чтение данных из файла
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
    // Заполнение матрицы(вручную или ранодмными числами)
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

    //Выводим характеристический вектор до и после перестановки колонок
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
    // Выводим сумму по всем колонкам с отрицательными числами
    std::cout << std::endl << matrix->sum_cols_with_negatives();
}

