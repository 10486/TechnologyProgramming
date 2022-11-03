// Lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include "Matrix.h"
#include "Vector.h"
#include "FinalValue.h"

const bool DEBUG = true;
int main()
{
	setlocale(LC_ALL, "Russian");
	std::string input_file, tmp_file_1, tmp_file_2, tmp_file_3;
	if (DEBUG) {
		input_file = "data/INPUT_1.TXT";
		tmp_file_1 = "data/OUTPUT_1.TXT";
		tmp_file_2 = "data/OUTPUT_2.TXT";
		tmp_file_3 = "data/OUTPUT_3.TXT";
	}
	else {
		std::cout << "Введите пути для 4 файлов: " << std::endl;
		std::cin >> input_file >> tmp_file_1 >> tmp_file_2 >> tmp_file_3;
	}
	int size = step1(input_file, tmp_file_1);
	step2(tmp_file_1, tmp_file_2, size);
	step3(tmp_file_2, tmp_file_3, size);
}




