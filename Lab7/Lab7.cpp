// Lab7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
class Vector {
    public:
        int start, size;
        Vector(int size=10, int start=0) {
            // Конструктор
            this->start = start;
            this->size = size;
            storage = new int[size];
        }
        int& operator[](int idx) {
            // Оператор взятия по индексу
            if (idx<start || idx>(start+size)) {
                throw std::runtime_error("Index out of bounds");
            }
            int tmp = idx - start;
            return storage[tmp];
        }
        Vector* operator+(Vector other) {
            // Сложение векторов и возврат нового вектора(суммы)
            if (other.start != start || other.size != size) {
                throw std::runtime_error("Vectors bounds not same");
            }
            Vector* result = new Vector(size, start);
            for (size_t i = 0; i < size; i++)
            {
                (*result)[start + i] = (*this)[start + i] + other[start + i];
            }
            return result;
        }
        Vector* operator-(Vector other) {
            // Вычитание векторов и возврат нового вектора(разности)
            if (other.start != start || other.size != size) {
                throw std::runtime_error("Vectors bounds not same");
            }
            Vector* result = new Vector(size, start);
            for (size_t i = 0; i < size; i++)
            {
                (*result)[start + i] = (*this)[start + i] - other[start + i];
            }
            return result;
        }
        Vector* operator*(int value) {
            // Оператор умножения на константу
            Vector* result = new Vector(size);
            for (size_t i = 0; i < size; i++)
            {
                (*result)[i + start] = (*this)[start + i] * value;
            }
            return result;
        }
        Vector* operator/(int value) {
            // Оператор деления на константу
            Vector* result = new Vector(size);
            for (size_t i = 0; i < size; i++)
            {
                (*result)[i + start] = (*this)[start + i] / value;
            }
            return result;
        }
    private:
        int* storage;
};
int main()
{
    setlocale(LC_ALL, "Russian");
    int size, start;

    std::cout << "Введите размер первого массива и начало отсчета индексов (через пробел): ";
    std::cin >> size >> start;
    std::cout << "Введите элементы массива (через пробел): ";
    auto v1 = new Vector(size, start);
    for (size_t i = 0; i < size; i++)
    {
        std::cin >> (*v1)[v1->start+i];
        
    }
    std::cout << "Введите размер второго массива и начало отсчета индексов (через пробел): ";
    std::cin >> size >> start;
    std::cout << "Введите элементы массива (через пробел): ";
    auto v2 = new Vector(size, start);
    for (size_t i = 0; i < size; i++)
    {
        std::cin >> (*v2)[v2->start+i];

    }
    int action;
    do
    {
        double value;
        Vector* result;
        std::cout << "Введите действие с вектором(0-сложить два вектора,1-вычесть из первого второй вектор, 2-умножить на скаляр, 3-поделить на скаляр, 4-выход): ";
        std::cin >> action;
        switch (action)
        {
        case 0:
            result = (*v1) + (*v2);
            break;
        case 1:
            result = (*v1) - (*v2);
            break;
        case 2:
            std::cout << "Введите скаляр: ";
            std::cin >> value;
            result = (*v1) * value;
            break;
        case 3:
            std::cout << "Введите скаляр: ";
            std::cin >> value;
            result = (*v1) / value;
            break;
        case 4:
            return 0;
        default:
            throw std::runtime_error("Wrong argument");
            break;
        }
        for (size_t i = 0; i < result->size; i++)
        {
            std::cout << (*result)[result->start + i] << " ";
        }
        delete result;
        std::cout << std::endl;
    } while (true);
}
