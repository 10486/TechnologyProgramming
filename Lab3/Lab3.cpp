// Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
struct Point {
    double x, y;
};
class Vector {
    private:
        Point p1, p2;
    public:
        Vector(Point p1, Point p2) {
            this->p1 = p1;
            this->p2 = p2;
        }
        double operator *(Vector *v) {
            return this->get_x() * v->get_x() + this->get_y() * v->get_y();
        }
        double operator -() {
            Point tmp = p1;
            this->p1 = this->p2;
            this->p2 = tmp;
        }
        double get_length() {
            return sqrt(pow(this->p1.x - this->p2.x, 2) + pow(this->p1.y - this->p2.y, 2));
        }
        double get_x() {
            return this->p2.x - this->p1.x;
        }
        double get_y() {
            return this->p2.y - this->p1.y;
        }
        double get_angle(Vector* v) {
            return acos((*this * v) / (this->get_length() * v->get_length()));
        }

        double get_h_length(Point p) {
            double dx = this->get_x();
            double dy = this->get_y();
            return abs(dy * p.x - dx * p.y + this->p1.y * this->p2.x - this->p2.y * this->p1.x) / sqrt(pow(dy, 2) + pow(dx, 2));
        }
        
};
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

