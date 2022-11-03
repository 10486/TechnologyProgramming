// Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

double get_c() {
    return (pow(0.027, -1. / 3) - pow((1. / 6), -2.2)) * log(3);
}

double get_k() {
    return 3 * sin(1) + cos(1);
}

double get_l() {
    double c = get_c();
    double k = get_k();
    double arg = c - 2 * k;
    if (abs(c + k) > 2) {
        return tanh(arg);
    }
    return log(abs(arg));
}

double get_y(double x, double a, double b) {
    return pow(sin(pow(pow(x, 2) + a, 2)), 3) - sqrt(x / b);
}

double get_z(double x, double a, double b) {
    return pow(x, 2) / a + cos(pow(x + b, 3));
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "c = " << get_c() << std::endl;
    std::cout << "k = " << get_k() << std::endl;
    std::cout << "l = " << get_l() << std::endl;

    double x, a, b;
    std::cout << "Введите x: ";
    std::cin >> x;
    std::cout << "Введите a: ";
    std::cin >> a;
    std::cout << "Введите b: ";
    std::cin >> b;

    std::cout << "y = " << get_y(x, a, b) << std::endl;
    std::cout << "z = " << get_z(x, a, b) << std::endl;
 
}
