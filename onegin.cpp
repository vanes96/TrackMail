#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm> 


bool isWord(const char chr)
{
	if (chr >= -32 && chr <= -1 || chr >= -64 && chr <= -33 ||
		chr >= 65 && chr <= 90 || chr >= 97 && chr <= 122)
		return true;
	else
		return false;
}

int compare1(const void *a, const void *b)
{
	char *s1 = *(char**)a, *s2 = *(char**)b;
	int n1 = strlen(s1), n2 = strlen(s2), n = std::min(n1, n2);
	for (int i = 0, j = 0; i < n && j < n; i++, j++)
	{
		while (!isWord(s1[i]))
			i++;
		while (!isWord(s2[j]))
			j++;
		if (s1[i] > s2[j])  return 1;
		if (s1[i] < s2[j]) return -1;
	}
	return n1 - n2;
}

int compare2(const void *a, const void *b)
{
	char *s1 = *(char**)a, *s2 = *(char**)b;
	int n1 = strlen(s1), n2 = strlen(s2);
	for (int i = n1 - 1, j = n2 - 1; i >= 0 && j >= 0; i--, j--)
	{
		while (!isWord(s1[i]))
			i--;
		while (!isWord(s2[j]))
			j--;
		if (s1[i] > s2[j])  return 1;
		if (s1[i] < s2[j]) return -1;
	}
	return n1 - n2;
}

char* readToBuffer(const char* fileName, int& nStrings)
{
	std::ifstream ifs(fileName);
	char* buffer;
	int size;

	ifs.seekg(0, ifs.end);
	size = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	buffer = new char[size];
	ifs.read(buffer, size);

	nStrings = std::count(buffer, buffer + strlen(buffer), '\n');
	size -= nStrings;
	buffer[size] = '\0';
	nStrings++;

	ifs.close();
	return buffer;
}

char** bufferToText(char* buffer, const int nStrings)
{
	char **text = new char*[nStrings], *s = strtok(buffer, "\n");
	for (int i = 0; s; i++)
	{
		text[i] = s;
		s = strtok(NULL, "\n");
	}
	return text;
}

void writeText(const char* fileName, char** text, const int nStrings)
{
	std::ofstream ofs(fileName);
	for (int i = 0; i < nStrings; i++)
		ofs << text[i] << std::endl;
	ofs.close();
}


int main()
{
	setlocale(LC_ALL, "Russian");
	char *buffer = NULL, **text = NULL;
	int nStrings = 0;
	

	buffer = readToBuffer("onegin.txt", nStrings); // Считывание данных в буфер из файла

	text = bufferToText(buffer, nStrings); // Преобразование буфера в текст

	qsort(text, nStrings, sizeof(char*), compare1); // Сортировка с начала строк текста
	writeText("sorted.txt", text, nStrings); // Запись отсортированного текста в файл

	qsort(text, nStrings, sizeof(char*), compare2); // Сортировка с концов строк текста
	writeText("rhymes.txt", text, nStrings); // Запись словаря рифм в файл

	//system("pause");	
	return 0;
}