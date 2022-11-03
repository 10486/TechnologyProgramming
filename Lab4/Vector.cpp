#include <string>
#include <fstream>

double* get_vec_x(double** matrix, int n) {
	double dot_prod;
	double* result = new double[n];
	if (!result)throw std::runtime_error("Memory hasn't been alloceted");
	for (size_t i = 0; i < n; i++)
	{
		dot_prod = 0;
		int max_ind = 0;
		double max = matrix[i][0];
		for (size_t j = 1; j < n; j++)
		{
			// find max
			if (matrix[i][j] > max) {
				max = matrix[i][j];
				max_ind = j;
			}
		}
		for (size_t j = 0; j < n; j++)
		{
			dot_prod += matrix[j][max_ind] * matrix[i][j];
		}
		result[i] = dot_prod;
	}
	return result;
}

double** read_file(std::string filename, int n) {
	double** matrix = new double* [n];
	if (!matrix)throw std::runtime_error("Memory hasn't been alloceted");
	std::ifstream in(filename);
	if (in.is_open())
	{
		for (size_t i = 0; i < n; i++)
		{
			matrix[i] = new double[n];
			if (!matrix[i])throw std::runtime_error("Memory hasn't been alloceted");
			for (size_t j = 0; j < n; j++)
			{

				in >> matrix[i][j];
			}
		}
	}
	in.close();
	return matrix;
}
void write_file(double* vector, std::string filename, int n) {
	std::ofstream out;
	out.open(filename);
	if (out.is_open())
	{
		for (size_t i = 0; i < n; i++)
		{
			out << vector[i] << " ";
		}
	}
}

void step2(std::string input_filename, std::string output_filename, int size) {
	double** matrix = read_file(input_filename, size);
	double* vector = get_vec_x(matrix, size);
	for (size_t i = 0; i < size; i++)
	{
		delete matrix[i];
	}
	delete matrix;
	write_file(vector, output_filename, size);
	delete vector;
}