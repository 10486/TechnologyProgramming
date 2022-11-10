// Lab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

class Parking {
    // Класс парковки
    public:
        void add_car(int number) {
            // Добавляем машину(число)
            park.push(number);
            // Добавляем счетчик сколько раз машина выезжала
            counter.push_back(new int[] {number, 0});
        }
        int remove_car(int number) {
            // Берем ближайшую к выезду машину
            int last = park.front();
            int tmp, idx;
            while (park.front() != number) {
                // Вытаскиваем машину и загоняем обратно с другой стороны, пока не найдем нужную
                idx = find_counter(readd_car());
                // Не забываем добавить к счетчику единичку
                counter[idx][1]++;
            }
            // Убираем нужную машину
            park.pop();
            // Исходный порядок это как?
            if (number != last) {
                // Возвращаем все так чтоб ближайщая к выезду машина которая была там в начале, вернулась на свое место
                // путем выезда и возращения остальных машин
                while (park.front() != last) {
                    idx = find_counter(readd_car());
                    // Не забываем добавить к счетчику единичку
                    counter[idx][1]++;
                }
            }
            // Находим счетчик для нужной машины и запомниаем количество раз которое она выезжала
            tmp = counter[find_counter(number)][1];
            // Удаляем счетчик
            delete_counter(number);
            return tmp;
        }
    private:
        std::queue<int> park;// Очередь машин
        std::vector<int*> counter;// Массив счетчиков выездов
        int readd_car() {
            // Выезд машины со стоянки и полседующий въезд обратно с другой стороны
            int tmp = park.front();
            park.pop();
            park.push(tmp);
            return tmp;
        }
        int find_counter(int number) {
            // Поиск счетчика выездов машины
            for (size_t i = 0; i < counter.size(); i++)
            {
                if (counter[i][0] == number) {
                    return i;
                }
            }
        }
        void delete_counter(int number) {
            // Удаление счетчика
            int idx = find_counter(number);
            delete counter[idx];
            counter.erase(counter.begin() + idx);
        }

};
void parking_work(Parking* parking, int number, bool add) {
    // Работа с парковкой(въезд и выезд машин) и вывод в кносоль результатов её работы
    int result;
    if (add) {
        parking->add_car(number);
        std::cout << "Машина с номером " << number << " добавлена" << std::endl;
    }
    else {
        result = parking->remove_car(number);
        std::cout << "Машина с номером " << number << " выехала" << std::endl;
        std::cout << "Машина с номером " << number << " выезжала со стоянки " << result << " раз" << std::endl;
    }
}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    bool flag = false;
    bool add;
    int number, result, count;
    bool console = true;
    std::string filename;
    Parking* parking = new Parking();
    if (argc > 1) { // Если были аргументы при запуске программы, то используем имя файла из аргументов
        console = false;
        filename = argv[1];
    }
    // Консольная работа с программой
    if (console) {
        do {
            std::cout << "Добавить или удалить автомобиль?(1-добавить,0-удалить): ";
            std::cin >> add;
            std::cout << "Введите номер машины: ";
            std::cin >> number;
            parking_work(parking, number, add);
            std::cout << "Продолжить?(1-да, 0-нет): ";
            std::cin >> flag;
        } while (flag);
        return 0;
    }
    // Если аргументов не было то ввод имени файла
    if(argc==1){
        std::cout << "Введите путь до файла: ";
        std::cin >> filename;
    }
    // Работа с парковкой по данным из файоа
    std::ifstream in(filename);
    if (in.is_open())
    {
        in >> count;
        for (size_t i = 0; i < count; i++)
        {
            in >> add >> number;
            parking_work(parking, number, add);
        }    
    }
    in.close();
    return 0;
}
