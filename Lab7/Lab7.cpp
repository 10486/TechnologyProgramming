// Lab7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
class Vector {
    public:
        int start, size;
        Vector(int size=10, int start=0) {
            this->start = start;
            this->size = size;
            storage = new int[size];
        }
        int& operator[](int idx) {
            if (idx<start || idx>(start+size)) {
                throw std::runtime_error("Index out of bounds");
            }
            int tmp = idx - start;
            return storage[tmp];
        }
        Vector* operator+(Vector other) {
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
            if (other.start != start || other.size != size) {
                throw std::runtime_error("Vectors bounds not same");
            }
            Vector* result = new Vector(size, start);
            for (size_t i = 0; i < size; i++)
            {
                result[start + i] = (*this)[start + i] - other[start + i];
            }
            return result;
        }
        Vector* operator*(int value) {
            Vector* result = new Vector(size);
            for (size_t i = 0; i < size; i++)
            {
                result[i] = (*this)[start + i] * value;
            }
            return result;
        }
        Vector* operator/(int value) {
            Vector* result = new Vector(size);
            for (size_t i = 0; i < size; i++)
            {
                result[i] = (*this)[start + i] / value;
            }
            return result;
        }
    private:
        int* storage;
};
int main()
{
    auto v1 = new Vector(10);
    auto v2 = new Vector(10);
    for (size_t i = 0; i < 10; i++)
    {
        (*v1)[i] = i;
        (*v2)[i] = i * i;
    }
    Vector* v3 = *v1 + *(*v2 * 3);
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << (*v3)[i] << " ";
    }
    std::cout << "Hello World!\n";
}
