#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;

struct Movie
{
	int movieCode;
	char dates[12] = "";
	int numSessions;
	char sessionTimes[3][8] = { "" };
};

void loadMovieNames(char movieNames[][40], int& numMovies);
void loadMovies(Movie movies[], int& numRecords);
void buyTickets(char movieNames[][40], Movie movies[], int numMovies, int numRecords);
int inputAnInteger(int begin, int end);

int main()
{
	char movieNames[12][40];
	int numMovies = 0;
	loadMovieNames(movieNames, numMovies);

	Movie movies[60];
	int numRecords = 0;
	loadMovies(movies, numRecords);

	buyTickets(movieNames, movies, numMovies, numRecords);

	system("pause");
}

void loadMovieNames(char movieNames[][40], int& numMovies)
{
	ifstream inFile("Movie Names.txt", ios::in);
	if (!inFile) {
		cout << "File could not be opened!" << endl;
		exit(1);
	}
	while (inFile.getline(movieNames[numMovies], 40)) {
		numMovies++;
	}

	inFile.close();

}

void loadMovies(Movie movies[], int& numRecords)
{
	ifstream inFile("Session Times.dat", ios::in | ios::binary);
	if (!inFile) {
		cout << "File could not be opened!" << endl;
		exit(1);
	}
	while (inFile.read(reinterpret_cast<char*>(&movies[numRecords]), sizeof(Movie))) {
		numRecords++;
	}

	inFile.close();

}

void buyTickets(char movieNames[][40], Movie movies[], int numMovies, int numRecords)
{
	for (int i = 0;i < numMovies;i++) {
		cout << setw(2) << i << ". " << movieNames[i] << endl;
	}
	cout << endl;
	cout << "Enter movie code (0 - " << numMovies - 1 << "): ";
	int movieCode = inputAnInteger(0, numMovies-1);
	cout << endl;
	while (movieCode == -1) {
		cout << "Enter movie code (0 - " << numMovies - 1 << "): ";
		movieCode = inputAnInteger(0, numMovies-1);
		cout << endl;
	}
	int numDate=0;
	int Date[100];
	for (int i = 0;i < numRecords;i++) {
		if (movies[i].movieCode == movieCode) {
			cout << setw(3) << numDate << ". " << movies[i].dates << endl;
			Date[numDate] = i;
			numDate++;
		}
	}
	cout << endl;
	cout << "Enter date code (0 - " << numDate - 1 << "): ";
	int dateCode = inputAnInteger(0, numDate - 1);
	cout << endl;
	while (dateCode == -1) {
		cout << "Enter date code (0 - " << numDate - 1 << "): ";
		dateCode = inputAnInteger(0, numDate - 1);
		cout << endl;
	}
	int movieIndex = Date[dateCode];
	for (int i = 0;i < movies[movieIndex].numSessions;i++) {
		cout << setw(3) << i << ". " << movies[movieIndex].sessionTimes[i] << endl;
	}
	cout << endl;
	cout << "Enter session time code (0 - " << movies[movieIndex].numSessions - 1 << "): ";
	int timeCode = inputAnInteger(0, movies[movieIndex].numSessions - 1);
	cout << endl;
	while (timeCode == -1) {
		cout << "Enter session time code (0 - " << movies[movieIndex].numSessions - 1 << "): ";
		timeCode = inputAnInteger(0, movies[movieIndex].numSessions - 1);
		cout << endl;
	}
	cout << movieNames[movieCode] << endl;
	cout << movies[movieIndex].dates << " " << movies[movieIndex].sessionTimes[timeCode] << endl;
}

int inputAnInteger(int begin, int end)
{
	char s[24];
	cin.getline(s, 24);
	if (strlen(s) == 0)
		return -1;
	for (int i = 0;i < strlen(s);i++) {
		if (s[i] < '0' || s[i]>'9')
			return -1;
	}
	int number;
	number = atoi(s);
	if (number >= begin && number <= end)
		return number;
	else
		return -1;
}