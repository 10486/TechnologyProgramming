#include <iostream>
#include <string>
#include <fstream>

double get_g(double* x, int n) {
	// Функция для вычисления итогового значения
	double prod = 1;
	for (int i = 0; i < (n - 1); i++)
	{
		prod *= 1 / (abs(x[i]) + 1) + x[i + 1];
	}
	return prod;
}
double* read_file(std::string filename, int n) {
	// Читаем вектор
	double* vector = new double[n];
	if (!vector)throw std::runtime_error("Memory hasn't been alloceted");
	std::ifstream in(filename);
	if (in.is_open())
	{
		for (size_t i = 0; i < n; i++)
		{
			in >> vector[i];
		}
	}
	in.close();
	return vector;
}
void write_file(double value, std::string filename, int n) {
	// Пишем значение
	std::ofstream out;
	out.open(filename);
	if (out.is_open())
	{
		out << value;
	}
}

void step3(std::string input_filename, std::string output_filename, int size) {
	double* vector = read_file(input_filename, size);
	double value = get_g(vector, size);
	delete vector;
	write_file(value, output_filename, size);
}