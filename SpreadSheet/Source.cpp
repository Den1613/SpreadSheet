/*
	�������� �������: ����������� �������.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>


int main()
{
	// � ������ ���������� ������ ������� �������
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

	// �������� ������ � ������ ������� �������
	std::istringstream iss(input[0]);
	std::string token;
	std::getline(iss, token, ',');
	int rows = atoi(token.c_str());
	std::getline(iss, token, ',');
	int columns = atoi(token.c_str());

	// �������������� �������
	std::string **spreadsheet = new std::string *[rows];
	for (int i = 0; i < rows; ++i)
		spreadsheet[i] = new std::string[columns];

	// ��������� �� ���������� �� �������
	for (int i = 0; i < rows; i++) {
		std::istringstream iss(input[i+1]);
		int j = 0;
		while (std::getline(iss, token, ',')) // � ������ ������ ����������� ��������� �������
		{
			spreadsheet[i][j] = token;
			j++;
		}
	}

	// ����������� ������� � ������������ � ��������
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			// �������� StringCell
			if (spreadsheet[i][j][0] == '�') { 
				spreadsheet[i][j].erase(0, 1);
			}
			// �������� ReferenceCell
			else if (spreadsheet[i][j][0] == '=') {
				char ch = spreadsheet[i][j].at(1);
				char ch� = spreadsheet[i][j].at(2);
				if (ch - 'A' > columns || ch� - '0' - 1 > rows) // �������� ������������ ��������� ������
					spreadsheet[i][j] = "#error (out of range)";
				else
					spreadsheet[i][j] = spreadsheet[ch� - '0' - 1][ch - 'A'];
			}
			// �������� IntegerCell
			else if (spreadsheet[i][j][0] == '-')
				spreadsheet[i][j] = "#error (a negative number)";
			// �������� EmptyCell
			else if (spreadsheet[i][j][0] == '\0')
				spreadsheet[i][j] = "EmptyCell";
	}

	// �������� �������
	for (int i = 0; i < rows; i++) {
		std::cout << std::endl;
		for (int j = 0; j < columns; j++)
			std::cout << spreadsheet[i][j] << "\t\t";
	}

	system("pause");
	return 0;
}