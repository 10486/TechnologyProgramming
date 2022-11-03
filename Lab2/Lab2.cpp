// Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>

double get_f(double a, double b, int i) {
    if (a > 0) {
        return (a + b + i + pow(-1, i) * (b - a)) / sqrt(a * i);
    }
    return abs(a + i) + abs(b - i);
}

double get_g(double* y, int n) {
    double y_abs, z, g = 0;
    for (int i = 0; i < n; i++) {
        y_abs = abs(y[i]);
        z = y_abs > 1 ? 1 / y[i] : y[i];
        g += pow(z, 2);
    }
    return g;
}

double ref_get_f(double* a, double* b, int* i) {

    if (*a > 0) {
        return (*a + *b + *i + pow(-1, *i) * (*b - *a)) / sqrt(*a * *i);
    }
    return abs(*a + *i) + abs(*b - *i);
}

double ref_get_g(double** y, int* n) {
    double y_abs, z, g = 0;
    for (int i = 0; i < *n; i++) {
        y_abs = abs((*y)[i]);
        z = y_abs > 1 ? 1 / (*y)[i] : (*y)[i];
        g += pow(z, 2);
    }
    return g;
}

double a, b, *y;
int i, N;
double global_get_f() {
    
    if (a > 0) {
        return (a + b + i + pow(-1, i) * (b - a)) / sqrt(a * i);
    }
    return abs(a + i) + abs(b - i);
}

double global_get_g() {
    double y_abs, z, g = 0;
    for (int i = 0; i < N; i++) {
        y_abs = abs(y[i]);
        z = y_abs > 1 ? 1 / y[i] : y[i];
        g += pow(z, 2);
    }
    return g;
}

const bool DEBUG = false;
int main()
{
    setlocale(LC_ALL, "Russian");
    double amin, amax, da, bmin, bmax, ba, u, temp;
    int n;  
    double* data;
    unsigned int approach;
    bool flag = true;
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    std::cout << "a     | b     | i     | Yi    | U    " << std::endl;
    
    do
    {
        if (DEBUG) {
            approach = 0;
            amin = 1;
            amax = 10;
            da = 0.5;
            bmin = 1;
            bmax = 10;
            ba = 0.5;
            n = 10;
        }
        else {
            std::cout << "Выберите каким способом будут передававться переменные в функции:" << std::endl;
            std::cout << "0-по значению, 1-используя глобальные переменные, 2-по ссылке" << std::endl;
            std::cin >> approach;
            std::cout << "Введите значение amin:";
            std::cin >> amin;
            std::cout << "Введите значение amax:";
            std::cin >> amax;
            std::cout << "Введите значение da:";
            std::cin >> da;
            std::cout << "Введите значение bmin:";
            std::cin >> bmin;
            std::cout << "Введите значение bmax:";
            std::cin >> bmax;
            std::cout << "Введите значение ba:";
            std::cin >> ba;
            std::cout << "Введите значение n:";
            std::cin >> n;
            if (n <= 0) {
                std::cout << "n должен быть > 0" << std::endl;
                continue;
            }
        
        }
        

        switch (approach)
        {
        case 0:
            data = new double[n];
            for (double a = amin; a <= amax; a += da)
            {
                for (double b = bmin; b <= bmax; b += ba)
                {
                    u = 0;
                    for (size_t i = 1; i <= n; i++)
                    {
                        temp = get_f(a, b, i);
                        data[i-1] = temp;
                        if (n == i) u = get_g(data, n);
                        std::cout << a << " | " << b << " | " << i << " | " << temp << " | " << u << std::endl;
                    }
                }
            }
            delete data;
            break;
        case 1:
            N = n;
            y = new double[N];
            for (a = amin; a <= amax; a += da)
            {
                for (b = bmin; b <= bmax; b += ba)
                {
                    u = 0;
                    for (i = 1; i <= N; i++)
                    {
                        temp = global_get_f();
                        y[i-1] = temp;
                        if (n == i) u = global_get_g();
                        std::cout << a << " | " << b << " | " << i << " | " << temp << " | " << u << std::endl;
                    }
                }
            }
            delete y;
            break;
        case 2:
            data = new double[n];
            for (double a = amin; a <= amax; a += da)
            {
                for (double b = bmin; b <= bmax; b += ba)
                {
                    u = 0;
                    for (int i = 1; i <= n; i++)
                    {
                        temp = ref_get_f(&a, &b, &i);
                        data[i-1] = temp;
                        if (n == i) u = ref_get_g(&data, &n);
                        std::cout << a << " | " << b << " | " << i << " | " << temp << " | " << u << std::endl;
                    }
                }
            }
            delete data;
            break;
        default:
            break;
        }

        std::cout << "Продожить? (1-Да или 0-Нет) ";
        std::cin >> flag;
    } while (flag);
    
}


