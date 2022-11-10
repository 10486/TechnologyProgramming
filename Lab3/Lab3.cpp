// Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

// Структура которая описывает точку на плоскости
struct Point {
    double x, y;
};

// Класс который описывает вектор на плоскости
class Vector {
    private:
        Point p1, p2;
    public:
        // Конструктор класса
        Vector(Point p1, Point p2) {
            this->p1 = p1;
            this->p2 = p2;
        }
        // Оператор скалярного умножения векторов
        double operator *(Vector *v) {
            return get_x() * v->get_x() + get_y() * v->get_y();
        }
        // Оператор разворота вектора
        double operator -() {
            Point tmp = p1;
            this->p1 = p2;
            this->p2 = tmp;
        }
        // Получение длинны
        double get_length() {
            return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
        }
        // Проекция по x
        double get_x() {
            return p2.x - p1.x;
        }
        // Проекция по y
        double get_y() {
            return p2.y - p1.y;
        }
        // Получаем угол между векторами в радианах
        double get_angle(Vector* v) {
            return acos((*this * v) / (get_length() * v->get_length()));
        }
        // Получаем расстояние от точки до вектора
        double get_h_length(Point p) {
            double dx = get_x();
            double dy = get_y();
            return abs(dy * p.x - dx * p.y + p1.y * p2.x - p2.y * p1.x) / sqrt(pow(dy, 2) + pow(dx, 2));
        }
        
};
// Радиус описанной окружности
double get_r(Point p1, Point p2, Point p3) {
    Vector *a, *b, *c;
    double a_len, b_len, c_len;
    a = new Vector(p1, p2);
    b = new Vector(p2, p3);
    c = new Vector(p3, p1);
    a_len = a->get_length();
    b_len = b->get_length();
    c_len = c->get_length();
    delete a, b, c;
    double p = (a_len + b_len + c_len) / 2;
    return (a_len * b_len * c_len) / (4 * sqrt(p * (p - a_len) * (p - b_len) * (p - c_len)));
}
// Получаем тип треугольника
int get_type(Point a_p, Point b_p, Point c_p) {
    Vector* a, * b, * c;
    double a_angle, b_angle, c_angle;
    a = new Vector(a_p, b_p);
    b = new Vector(b_p, c_p);
    c = new Vector(c_p, a_p);
    a_angle = b->get_angle(c);
    b_angle = a->get_angle(c);
    c_angle = a->get_angle(b);
    delete a, b, c;
    if (a_angle == b_angle && a_angle == c_angle) {
        return 0;
    }
    else if (a_angle == M_PI_2 || b_angle == M_PI_2 || c_angle == M_PI_2) {
        return 1;
    }
    else if (a_angle == b_angle || a_angle == c_angle || b_angle == c_angle) {
        return 2;
    }
    else if (a_angle > M_PI_2 || b_angle > M_PI_2 || c_angle > M_PI_2) {
        return 3;
    }
    return 4;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    //Ввод координат
    Point a_p, b_p, c_p;
    std::cout << "Первая вершина" << std::endl;
    std::cout << "Введите x,y через пробел:";
    std::cin >> a_p.x >> a_p.y;
    std::cout << "Вторая вершина" << std::endl;
    std::cout << "Введите x,y через пробел:";
    std::cin >> b_p.x >> b_p.y;
    std::cout << "Третья вершина" << std::endl;
    std::cout << "Введите x,y через пробел:";
    std::cin >> c_p.x >> c_p.y;
    //Определить тип
    int type = get_type(a_p, b_p, c_p);
    std::cout << "Тип треугольника: ";
    switch (type)
    {
    case 0:
        std::cout << "Равносторонний" << std::endl;
        break;
    case 1:
        std::cout << "Прямоугольный" << std::endl;
        break;
    case 2:
        std::cout << "Равнобедренный" << std::endl;
        break;
    case 3:
        std::cout << "Тупоугольный" << std::endl;
        break;
    case 4:
        std::cout << "Остроугольный" << std::endl;
        break;
    }
    //Углы
    Vector *a, *b, *c;
    a = new Vector(b_p, c_p);
    b = new Vector(a_p, c_p);
    c = new Vector(b_p, a_p);
    std::cout << "Угол A:" << b->get_angle(c) << std::endl << "Угол B:" << a->get_angle(c) << std::endl << "Угол C:" << a->get_angle(c) << std::endl;
    //Радиус
    std::cout << "Радиус описанной окружности: " << get_r(a_p, b_p, c_p) << std::endl;
    //Длинны высот
    double a_h = a->get_h_length(a_p);
    double b_h = b->get_h_length(b_p);
    double c_h = c->get_h_length(c_p);
    delete a, b, c;
    std::cout << "Длинна высоты из вершины A: " << a_h << std::endl;
    std::cout << "из вершины B: " << b_h << std::endl;
    std::cout << "из вершины C: " << c_h << std::endl;
}

