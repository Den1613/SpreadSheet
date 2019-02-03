/*
	Тестовое задание: электронная таблица.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>


int main()
{
	// В вектор записываем данные будущей таблицы
	std::vector<std::string> input;
	std::string temp;
	std::cout << "Enter the spreadsheet data.To stop typing write 'stop'" << std::endl;
	do
	{
		std::cin >> temp;
		if (temp == "stop") {
			break;
		}
		input.push_back(temp);
	} while (true);

	// Получаем высоту и ширину будущей таблицы
	std::istringstream iss(input[0]);
	std::string token;
	std::getline(iss, token, ',');
	int rows = atoi(token.c_str());
	std::getline(iss, token, ',');
	int columns = atoi(token.c_str());

	// Инициализируем таблицу
	std::string **spreadsheet = new std::string *[rows];
	for (int i = 0; i < rows; ++i)
		spreadsheet[i] = new std::string[columns];

	// Заполняем ее значениями из вектора
	for (int i = 0; i < rows; i++) {
		std::istringstream iss(input[i+1]);
		int j = 0;
		while (std::getline(iss, token, ',')) // В данном случае делимитером выступает запятая
		{
			spreadsheet[i][j] = token;
			j++;
		}
	}

	// Преобразуем таблицу в соответствии с заданием
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			// Проверка StringCell
			if (spreadsheet[i][j][0] == '‘') { 
				spreadsheet[i][j].erase(0, 1);
			}
			// Проверка ReferenceCell
			else if (spreadsheet[i][j][0] == '=') {
				char ch = spreadsheet[i][j].at(1);
				char chс = spreadsheet[i][j].at(2);
				if (ch - 'A' > columns || chс - '0' - 1 > rows) // Проверка корректности введенной ссылки
					spreadsheet[i][j] = "#error (out of range)";
				else
					spreadsheet[i][j] = spreadsheet[chс - '0' - 1][ch - 'A'];
			}
			// Проверка IntegerCell
			else if (spreadsheet[i][j][0] == '-')
				spreadsheet[i][j] = "#error (a negative number)";
			// Проверка EmptyCell
			else if (spreadsheet[i][j][0] == '\0')
				spreadsheet[i][j] = "EmptyCell";
	}

	// Печатаем таблицу
	for (int i = 0; i < rows; i++) {
		std::cout << std::endl;
		for (int j = 0; j < columns; j++)
			std::cout << spreadsheet[i][j] << "\t\t";
	}

	system("pause");
	return 0;
}