#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;

struct MemberRecord
{
    char email[40];
    char password[24];
    char IDNumber[12];
    char name[12];
    char phone[12];
};

struct Movie
{
    int movieCode;
    int prices[2]; // prices[ 0 ]:adult, prices[1]:concession
    bool dates[6]; // dates[ i ] is true if and only if the movie is available on i-th date
    bool sessionTimes[12]; // sessionTimes[i] is true if and only if the movie is available on i-th session
    bool occupiedSeats[6][12][8][12];
};   // occupiedSeats[i][j] is the occupied Seats for all accounts at j-th session time on i-th date

struct BookingInfo
{
    char email[40];
    int movieCode;
    int dateCode;
    int sessionTimeCode;
    int numTickets[2]; // numTickets[ 0 ]: the number of adult tickets,
    // numTickets[ 1 ]: the number of concession tickets
    char seletedSeats[20][4]; // seleted seats for the user with the specified email
};

char hours[12][8] = { "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00",
                          "18:00", "19:00", "20:00", "21:00", "22:00" };

void loadMemberInfo(MemberRecord memberDetails[], int& numMembers);
void loadBookingHistories(BookingInfo bookingHistories[], int& numBookings);
void loadMovies(Movie movies[], int& numMovies);
void loadMovieNames(char movieNames[][60], int numMovies);
void loadAvailableDates(char availableDates[][12], int& numDates);

int inputAnInteger(int begin, int end);
void signIn(MemberRecord memberDetails[], int numMembers, Movie movies[], char movieNames[][60], int numMovies,
    BookingInfo bookingHistories[], int& numBookings, char availableDates[][12], int numDates);
bool legal(char email[], char password[], MemberRecord memberDetails[], int numMembers, int& recordNumber);
void accountInfor(MemberRecord memberDetails[], int numMembers, int recordNumber);

void buyTickets(BookingInfo bookingHistories[], int& numBookings, Movie movies[], char movieNames[][60],
    int numMovies, char availableDates[][12], int numDates, char email[]);
void selectSeats(BookingInfo bookingHistories[], int numBookings, Movie movies[]);

void displaySessionTimes(Movie movies[], char movieNames[][60], int numMovies,
    char availableDates[][12], int numDates);
void display(Movie movies[], BookingInfo bookingHistory);
void displayBookingHistory(BookingInfo bookingHistories[], int numBookings, Movie movies[],
    char movieNames[][60], char availableDates[][12], char email[]);

void newMember(MemberRecord memberDetails[], int& numMembers);
bool existingID(char newIDNumber[], MemberRecord memberDetails[], int& numMembers);
bool existingEmail(char newEmail[], MemberRecord memberDetails[], int& numMembers);

void saveMemberInfo(MemberRecord memberDetails[], int numMembers);
void saveMovies(Movie movies[], int numMovies);
void saveBookingHistories(BookingInfo bookingHistories[], int numBookings);

int main()
{
    MemberRecord memberDetails[100] = {};
    int numMembers = 0;
    loadMemberInfo(memberDetails, numMembers);

    BookingInfo bookingHistories[100] = {};
    int numBookings = 0;
    loadBookingHistories(bookingHistories, numBookings);

    Movie movies[30] = {};
    int numMovies = 0;
    loadMovies(movies, numMovies);

    char movieNames[30][60] = {};
    loadMovieNames(movieNames, numMovies);

    char availableDates[10][12];
    int numDates;
    loadAvailableDates(availableDates, numDates);

    cout << "Welcome to Vie Show Cinemas Taoyuan Geleven Plaza system\n\n";

    int choice;

    while (true)
    {
        cout << "1. Sign In\n";
        cout << "2. New Member\n";
        cout << "3. End\n";

        do cout << "\nEnter your choice (1~3): ";
        while ((choice = inputAnInteger(1, 3)) == -1);
        cout << endl;

        switch (choice)
        {
        case 1:
            signIn(memberDetails, numMembers, movies, movieNames, numMovies,
                bookingHistories, numBookings, availableDates, numDates);
            break;

        case 2:
            newMember(memberDetails, numMembers);
            break;

        case 3:
            saveMemberInfo(memberDetails, numMembers);
            saveMovies(movies, numMovies);
            saveBookingHistories(bookingHistories, numBookings);
            cout << "Thank you!\n\n";
            system("pause");
            return 0;

        default:
            cout << "Input Error!\n\n";
            break;
        }
    }

    system("pause");
}

void loadMemberInfo(MemberRecord memberDetails[], int& numMembers)
{
    ifstream inFile("Member Info.dat", ios::in | ios::binary);
    if (!inFile) {
        cout << "File could not be opend" << endl;
        exit(1);
    }
    while (inFile.read(reinterpret_cast<char*>(&memberDetails[numMembers]), sizeof(MemberRecord))) {
        numMembers++;
    }

    inFile.close();

}

void loadBookingHistories(BookingInfo bookingHistories[], int& numBookings)
{
    ifstream inFile("Booking Histories.dat", ios::in | ios::binary);
    if (!inFile) {
        cout << "File could not be opend" << endl;
        exit(1);
    }
    while (inFile.read(reinterpret_cast<char*>(&bookingHistories[numBookings]), sizeof(BookingInfo))) {
        numBookings++;
    }
    
    inFile.close();

}

void loadMovies(Movie movies[], int& numMovies)
{
    ifstream inFile("Movies.dat", ios::in | ios::binary);
    if (!inFile) {
        cout << "File could not be opend" << endl;
        exit(1);
    }
    while (inFile.read(reinterpret_cast<char*>(&movies[numMovies]), sizeof(Movie))) {
        numMovies++;
    }

    inFile.close();

}

void loadMovieNames(char movieNames[][60], int numMovies)
{
    ifstream inFile("Movie Names.txt", ios::in);
    if (!inFile) {
        cout << "File could not be opend" << endl;
        exit(1);
    }
    for (int i = 0;i < numMovies;i++) {
        inFile.getline(movieNames[i], 60);
    }

    inFile.close();

}

void loadAvailableDates(char availableDates[][12], int& numDates)
{
    numDates = 0;
    ifstream inFile("Available Dates.txt", ios::in);
    if (!inFile) {
        cout << "File could not be opend" << endl;
        exit(1);
    }
    while (inFile.getline(availableDates[numDates], 12)) {
        numDates++;
    }

    inFile.close();

}

int inputAnInteger(int begin, int end)
{
    char string[80];

    cin.getline(string, 80, '\n');

    if (strlen(string) == 0)
        return -1;

    for (unsigned int i = 0; i < strlen(string); i++)
        if (string[i] < '0' || string[i] > '9')
            return -1;

    int number = atoi(string);
    if (number >= begin && number <= end)
        return number;
    else
        return -1;
}

void signIn(MemberRecord memberDetails[], int numMembers, Movie movies[],
    char movieNames[][60], int numMovies, BookingInfo bookingHistories[],
    int& numBookings, char availableDates[][12], int numDates)
{
    int recordNumber = -1;
    char email[40] = "";
    char password[24] = "";

    do {
        cout << "Enter email address: ";
        cin >> email;
        cout << "Enter password: ";
        cin >> password;

    } while (!legal(email, password, memberDetails, numMembers, recordNumber));

    cin.ignore();

    int choice = 2;

    while (true)
    {
        cout << "\n1. Account Information\n";
        cout << "2. Buy Tickets\n";
        cout << "3. My Bookings\n";
        cout << "4. Sign Out\n";

        do cout << "\nEnter your choice (1~4): ";
        while ((choice = inputAnInteger(1, 4)) == -1);
        cout << endl;

        switch (choice)
        {
        case 1:
            accountInfor(memberDetails, numMembers, recordNumber);
            break;

        case 2:
            buyTickets(bookingHistories, numBookings, movies, movieNames,
                numMovies, availableDates, numDates, email);
            break;

        case 3:
            displayBookingHistory(bookingHistories, numBookings, movies,
                movieNames, availableDates, email);
            break;

        case 4:
            return;

        default:
            cout << "Input Error!\n";
            break;
        }
    }
}

bool legal(char email[], char password[], MemberRecord memberDetails[],
    int numMembers, int& recordNumber)
{
    for (int i = 0; i < numMembers; i++)
        if (strcmp(email, memberDetails[i].email) == 0 &&
            strcmp(password, memberDetails[i].password) == 0)
        {
            recordNumber = i;
            return true;
        }

    cout << "\nSorry, unrecognized email or password.\n\n";
    return false;
}

void accountInfor(MemberRecord memberDetails[], int numMembers, int recordNumber)
{
    
    cout << "1. Name: " << memberDetails[recordNumber].name << endl;
    cout << "2. Phone Number: " << memberDetails[recordNumber].phone << endl;
    cout << "3. ID Number: " << memberDetails[recordNumber].IDNumber << endl;
    cout << "4. Password: " << memberDetails[recordNumber].password << endl ;

    int choice;
    do cout << "\nWhich one do you want to modify (0 – not modify): ";
    while ((choice = inputAnInteger(0, 4)) == -1);
    
    switch (choice) {
    case 0:
        break;
    case 1:
        cout << endl;
        cout << "Enter correct data: ";
        cin >> memberDetails[recordNumber].name;
        cout << endl;
        cin.ignore();
        cout << "Successful!" << endl ;
        break;
    case 2:
        cout << endl;
        cout << "Enter correct data: ";
        cin >> memberDetails[recordNumber].phone;
        cout << endl;
        cin.ignore();
        cout << "Successful!" << endl ;
        break;
    case 3:
        cout << endl;
        cout << "Enter correct data: ";
        cin >> memberDetails[recordNumber].IDNumber;
        cout << endl;
        cin.ignore();
        cout << "Successful!" << endl ;
        break;
    case 4:
        cout << endl;
        cout << "Enter correct data: ";
        cin >> memberDetails[recordNumber].password;
        cout << endl;
        cin.ignore();
        cout << "Successful!" << endl ;
        break;
    }



}

void newMember(MemberRecord memberDetails[], int& numMembers)
{
    MemberRecord newMember;
    cout << "Enter your ID number: ";
    cin >> newMember.IDNumber;
    cin.ignore();
    if (existingID(newMember.IDNumber, memberDetails, numMembers)) {
        cout << endl;
        cout << "An account already exists with the ID number!" << endl << endl;
        return;
    }
    cout << "Enter your name: ";
    cin >> newMember.name;
    cout << "Enter an email address: ";
    cin >> newMember.email;
    cin.ignore();
    if (existingEmail(newMember.email, memberDetails, numMembers)) {
        cout << endl;
        cout << "An account already exists with the email address!" << endl << endl;
        while (existingEmail(newMember.email, memberDetails, numMembers)) {
            cout << "Enter an email address: ";
            cin >> newMember.email;
            if (existingEmail(newMember.email, memberDetails, numMembers)) {
                cout << endl;
                cout << "An account already exists with the email address!" << endl << endl;
            }
        }
    }
    cout << "Enter a password: ";
    cin >> newMember.password;
    cout << "Enter your phone number:";
    cin >> newMember.phone;
    cin.ignore();
    memberDetails[numMembers++] = newMember;
    cout << endl;
    cout << "Successful!" << endl << endl;


}

bool existingID(char newIDNumber[], MemberRecord memberDetails[], int& numMembers)
{
    for (int i = 0; i < numMembers; i++)
        if (strcmp(newIDNumber, memberDetails[i].IDNumber) == 0)
            return true;

    return false;
}

bool existingEmail(char newEmail[], MemberRecord memberDetails[], int& numMembers)
{
    for (int i = 0; i < numMembers; i++)
        if (strcmp(newEmail, memberDetails[i].email) == 0)
            return true;

    return false;
}

void buyTickets(BookingInfo bookingHistories[], int& numBookings, Movie movies[],
    char movieNames[][60], int numMovies, char availableDates[][12],
    int numDates, char email[])
{
    displaySessionTimes(movies, movieNames, numMovies, availableDates, numDates);

    do cout << "Enter movie code (0 - 10): ";
    while ((bookingHistories[numBookings].movieCode = inputAnInteger(0, 10)) == -1);
    cout << endl;
    do cout << "Enter date code (0 - 5): ";
    while ((bookingHistories[numBookings].dateCode = inputAnInteger(0, 5)) == -1 || !(movies[bookingHistories[numBookings].movieCode].dates[bookingHistories[numBookings].dateCode]));
    cout << endl;
    do cout << "Enter session time code (0 - 11): ";
    while ((bookingHistories[numBookings].sessionTimeCode = inputAnInteger(0, 11)) == -1 || !(movies[bookingHistories[numBookings].movieCode].sessionTimes[bookingHistories[numBookings].sessionTimeCode]));
    cout << endl;

    cout << "Movie: " << movieNames[bookingHistories[numBookings].movieCode] << endl;
    cout << "Date: " << availableDates[bookingHistories[numBookings].dateCode] << endl;
    cout << "Show Time: " << hours[bookingHistories[numBookings].sessionTimeCode] << endl;
    cout << "Price: Adult-" << movies[bookingHistories[numBookings].movieCode].prices[0] << "," << " Concession-" << movies[bookingHistories[numBookings].movieCode].prices[1] << endl << endl;

    display(movies, bookingHistories[numBookings]);

    selectSeats(bookingHistories, numBookings, movies);

    cout << "\nSuccessful!\n";

    numBookings++;
}

void selectSeats(BookingInfo bookingHistories[], int numBookings, Movie movies[])
{
    do cout << "Enter the number of adult tickets (0 - 10): ";
    while ((bookingHistories[numBookings].numTickets[0] = inputAnInteger(0, 10)) == -1);
    do cout << "Enter the number of concession tickets (0 - 10): ";
    while ((bookingHistories[numBookings].numTickets[1] = inputAnInteger(0, 10)) == -1);
    cout << endl;
    cout << "             No. of Tickets  Price  Subtotal" << endl;
    cout << "Adult" << setw(22) << bookingHistories[numBookings].numTickets[0] << setw(7) << movies[bookingHistories[numBookings].movieCode].prices[0] << setw(10) << bookingHistories[numBookings].numTickets[0] * movies[bookingHistories[numBookings].movieCode].prices[0] << endl;
    cout << "Concession" << setw(17) << bookingHistories[numBookings].numTickets[1] << setw(7) << movies[bookingHistories[numBookings].movieCode].prices[1] << setw(10) << bookingHistories[numBookings].numTickets[1] * movies[bookingHistories[numBookings].movieCode].prices[1] << endl << endl;
    cout << "Total Amount For Tickets: " << bookingHistories[numBookings].numTickets[0] * movies[bookingHistories[numBookings].movieCode].prices[0] + bookingHistories[numBookings].numTickets[1] * movies[bookingHistories[numBookings].movieCode].prices[1] << endl;

    cout << endl;
    cout << "  A B C D E F G H I J K L"<<endl;
    for (int i = 0;i < 8;i++) {
        cout << i;
        for (int j = 0;j < 12;j++) {
            if (movies[bookingHistories[numBookings].movieCode].occupiedSeats[bookingHistories[numBookings].dateCode][bookingHistories[numBookings].sessionTimeCode][i][j])
                cout << " 1";
            else
                cout << " 0";

        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0;i < bookingHistories[numBookings].numTickets[0] + bookingHistories[numBookings].numTickets[1];i++) {
        int row, col;
        cout << "Select "<< bookingHistories[numBookings].numTickets[0] + bookingHistories[numBookings].numTickets[1] <<" seats (e.g. 0A): " << endl << "? ";
        do {
            cin >> bookingHistories[numBookings].seletedSeats[i];
            cin.ignore();
            row = bookingHistories[numBookings].seletedSeats[i][0] - '0';
            col = bookingHistories[numBookings].seletedSeats[i][1] - 'A';
            if (movies[bookingHistories[numBookings].movieCode].occupiedSeats[bookingHistories[numBookings].dateCode][bookingHistories[numBookings].sessionTimeCode][row][col]) {
                cout << endl;
                cout << "This seat has been occupied. Please select another seat." << endl;
                cout << "? ";
            }
        } while (movies[bookingHistories[numBookings].movieCode].occupiedSeats[bookingHistories[numBookings].dateCode][bookingHistories[numBookings].sessionTimeCode][row][col]); 
        movies[bookingHistories[numBookings].movieCode].occupiedSeats[bookingHistories[numBookings].dateCode][bookingHistories[numBookings].sessionTimeCode][row][col] = true;
    }
    

}

void displaySessionTimes(Movie movies[], char movieNames[][60], int numMovies,
    char availableDates[][12], int numDates)
{
    cout << endl;
    for (int i = 0;i < numMovies;i++) {
        cout << setw(2) << i << ". Movie: " << movieNames[i] << endl;
        cout << "     Date:";
        for (int j = 0;j < numDates;j++) {
            if (movies[i].dates[j]) {
                cout << "  " << j << ". " << availableDates[j] << ", ";
            }
        }
        cout << endl;
        cout << "     Session Time: ";
        for (int j = 0;j < 12;j++) {
            if (movies[i].sessionTimes[j]) {
                cout << " " << j << ". " << hours[j] << ",";
            }
        }
        cout << endl << endl;
    }



}

void display(Movie movies[], BookingInfo bookingHistory)
{
    return;



}

void displayBookingHistory(BookingInfo bookingHistories[], int numBookings, Movie movies[],
    char movieNames[][60], char availableDates[][12], char email[])
{
    if (numBookings == 0) {
        cout << "No bookings!" << endl ;
        return;
    }
    cout << endl;
    cout << "Booking History: " << endl << endl;
    for (int i = 0;i < numBookings;i++) {
        cout << "Movie: " << movieNames[bookingHistories[i].movieCode] << endl;
        cout << "Date: " << availableDates[bookingHistories[i].dateCode] << endl;
        cout << "Show Time: " << hours[bookingHistories[i].sessionTimeCode] << endl;
        cout << "Seat: ";
        for (int j = 0;j < bookingHistories[i].numTickets[0] + bookingHistories[i].numTickets[1];j++) {
            cout << " " << bookingHistories[i].seletedSeats[j] << " ";
        }
        cout << endl << endl;
        cout << "             No. of Tickets  Price  Subtotal" << endl;
        cout << "Adult" << setw(22) << bookingHistories[i].numTickets[0] << setw(7) << movies[bookingHistories[i].movieCode].prices[0] << setw(10) << bookingHistories[i].numTickets[0] * movies[bookingHistories[i].movieCode].prices[0] << endl;
        cout << "Concession" << setw(17) << bookingHistories[i].numTickets[1] << setw(7) << movies[bookingHistories[i].movieCode].prices[1] << setw(10) << bookingHistories[i].numTickets[1] * movies[bookingHistories[i].movieCode].prices[1] << endl << endl;
        cout << "Total Amount For Tickets: " << bookingHistories[i].numTickets[0] * movies[bookingHistories[i].movieCode].prices[0] + bookingHistories[i].numTickets[1] * movies[bookingHistories[i].movieCode].prices[1] << endl;
        cout << endl << "----------------------------------------------"  <<endl;
    }



}

void saveMemberInfo(MemberRecord memberDetails[], int numMembers)
{
    ofstream outFile("Member Info.dat", ios::out | ios::binary);
    if (!outFile) {
        cout << "File could not be opened" << endl;
        exit(1);
    }

    for (int i = 0;i < numMembers;i++) {
        outFile.write(reinterpret_cast<const char*>(&memberDetails[i]), sizeof(MemberRecord));
    }

    outFile.close();
}

void saveMovies(Movie movies[], int numMovies)
{
    ofstream outFile("Movies.dat", ios::out | ios::binary);
    if (!outFile) {
        cout << "File could not be opend" << endl;
        exit(1);
    }

    for (int i = 0;i < numMovies;i++) {
        outFile.write(reinterpret_cast<const char*>(&movies[i]), sizeof(Movie));
    }

    outFile.close();
}

void saveBookingHistories(BookingInfo bookingHistories[], int numBookings)
{
    ofstream outFile("Booking Histories.dat", ios::out | ios::binary);
    if (!outFile) {
        cout << "File could not be opend" << endl;
        exit(1);
    }

    for (int i = 0;i < numBookings;i++) {
        outFile.write(reinterpret_cast<const char*>(&bookingHistories[i]), sizeof(BookingInfo));
    }

    outFile.close();
    
}