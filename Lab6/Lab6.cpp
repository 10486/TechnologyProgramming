// Lab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

class Parking {
    public:
        void add_car(int number) {
            park.push(number);
            counter.push_back(new int[] {number, 0});
        }
        int remove_car(int number) {
            int last = park.front();
            int tmp, idx;
            while (park.front() != number) {
                
                idx = find_counter(readd_car());
                counter[idx][1]++;
            }
            park.pop();
            // Исходный порядок это как?
            if (number != last) {
                while (park.front() != last) {
                    idx = find_counter(readd_car());
                    counter[idx][1]++;
                }
            }
            tmp = counter[find_counter(number)][1];
            delete_counter(number);
            return tmp;
        }
    private:
        std::queue<int> park;
        std::vector<int*> counter;
        int readd_car() {
            int tmp = park.front();
            park.pop();
            park.push(tmp);
            return tmp;
        }
        int find_counter(int number) {
            for (size_t i = 0; i < counter.size(); i++)
            {
                if (counter[i][0] == number) {
                    return i;
                }
            }
        }
        void delete_counter(int number) {
            int idx = find_counter(number);
            delete counter[idx];
            counter.erase(counter.begin() + idx);
        }

};
void parking_work(Parking* parking, int number, bool add) {
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
    if (argc > 1) {
        console = false;
        filename = argv[1];
    }
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

    if(argc==1){
        std::cout << "Введите путь до файла: ";
        std::cin >> filename;
    }
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
