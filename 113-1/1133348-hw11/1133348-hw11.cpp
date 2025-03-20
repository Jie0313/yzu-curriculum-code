#include <iostream>
#include <fstream>

using namespace::std;

struct Member
{
    char email[40];
    char password[24];
    char IDNumber[12];
    char name[12];
    char phone[12];
};

void loadMemberInfo(ifstream& inMemberFile, Member memberDetails[], int& numMembers);

// input an integer from the keyboard, and
// returns the integer if it belongs to [ begin, end ], returns -1 otherwise.
int inputAnInteger(int begin, int end);

void login(Member memberDetails[], int numMembers);

// returns true if there is a member
// whose email and password are equal to the specified email and password, respectively
bool legal(char email[], char password[], Member memberDetails[], int numMembers, int& recordNumber);

void accountInfor(Member memberDetails[], int numMembers, int recordNumber);

void newMember(Member memberDetails[], int& numMembers);

// returns true if there is a member whose IDNumber is equal to newIDNumber
bool existingID(char newIDNumber[], Member memberDetails[], int& numMembers);

// returns true if there is a member whose email is equal to newEmail
bool existingEmail(char newEmail[], Member memberDetails[], int& numMembers);

void saveMemberInfo(ofstream& outMemberFile, Member memberDetails[], int numMembers);

int main()
{
    Member memberDetails[100] = { "", "", "", "", "" };
    int numMembers = 0;

    ifstream inMemberFile;
    ofstream outMemberFile;

    loadMemberInfo(inMemberFile, memberDetails, numMembers);

    cout << "Welcome to Vieshow Cinemas member system\n\n";

    int choice;

    while (true)
    {
        cout << "Enter your choice:" << endl;
        cout << "1. Sign In\n";
        cout << "2. New Member\n";
        cout << "3. Sign Out\n? ";

        choice = inputAnInteger(1, 3);
        cout << endl;

        switch (choice)
        {
        case 1:
            login(memberDetails, numMembers);
            break;

        case 2:
            newMember(memberDetails, numMembers);
            break;

        case 3:
            saveMemberInfo(outMemberFile, memberDetails, numMembers);
            cout << "Thank you...\n\n";
            system("pause");
            return 0;

        default:
            cout << "Input Error!\n\n";
            break;
        }
    }

    system("pause");
}

void loadMemberInfo(ifstream& inMemberFile, Member memberDetails[], int& numMembers) {
    inMemberFile.open("MemberInfo.dat", ios::in | ios::binary);
    if (!inMemberFile) {
        cout << "Error opening file MemberInfo.dat!" << endl;
        return;
    }
    while (inMemberFile.read(reinterpret_cast<char*>(&memberDetails[numMembers]), sizeof(Member))) {
        numMembers++;
    }

    inMemberFile.close();
}

int inputAnInteger(int begin, int end) {
    char s[20];
    cin.getline(s, 20,'\n');
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

void login(Member memberDetails[], int numMembers) {
    char email[40], password[24];
    while (true) {
        cout << "Enter email address: ";
        cin >> email;
       
        cout << "Enter password: ";
        cin >> password;
        cout << endl;
        cin.ignore();
        int recordNumber = -1;
        if (legal(email, password, memberDetails, numMembers, recordNumber)) {
            while (true) {
                cout << "Enter your choice : " << endl;
                cout << "1. Account Information" << endl;
                cout << "2. Buy Tickets" << endl;
                cout << "3. End\n?";

                int choice;
                choice = inputAnInteger(1, 3);
                cout << endl;

                switch (choice)
                {
                case 1:
                    accountInfor(memberDetails, numMembers, recordNumber);
                    break;

                case 2:
                    break;

                case 3:
                    cout << endl;
                    return ;

                default:
                    cout << "Input Error!\n\n";
                    break;
                }
            }
            break;
        }
        else
            cout << "Sorry, unrecognized email or password." << endl << endl;
    }

}

bool legal(char email[], char password[], Member memberDetails[], int numMembers, int& recordNumber) {
    for (int i = 0;i < numMembers;i++) {
        if (strcmp(email, memberDetails[i].email) == 0 && strcmp(password, memberDetails[i].password) == 0) {
            recordNumber = i;
            return true;
        }
    }
    return false;
}

void accountInfor(Member memberDetails[], int numMembers, int recordNumber) {
    cout << "1. Name: " << memberDetails[recordNumber].name << endl;
    cout << "2. Email Address: " << memberDetails[recordNumber].email << endl;
    cout << "3. Phone Number: " << memberDetails[recordNumber].phone << endl;
    cout << "4. ID Number: " << memberDetails[recordNumber].IDNumber << endl;
    cout << "5. Password: " << memberDetails[recordNumber].password << endl<<endl;

    cout << "Which one do you want to modify (0 – not modify)?";
    int choice;
    choice = inputAnInteger(0, 5);
    while (true) {
        switch (choice) {
        case 0:
            cout << endl;
            return;
        case 1:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].name;
            cin.ignore();
            cout << endl;
            cout << "Successful!" << endl << endl;
            return;
        case 2:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].email;
            cin.ignore();
            cout << endl;
            cout << "Successful!" << endl << endl;
            return;
        case 3:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].phone;
            cin.ignore();
            cout << endl;
            cout << "Successful!" << endl << endl;
            return;
        case 4:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].IDNumber;
            cin.ignore();
            cout << endl;
            cout << "Successful!" << endl << endl;
            return;
        case 5:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].password;
            cin.ignore();
            cout << endl;
            cout << "Successful!" << endl << endl;
            return;
        default:
            cout << endl;
            cout << "Input Error! Please try again: ";
            choice = inputAnInteger(0, 5);
            break;
        }
    }
}

void newMember(Member memberDetails[], int& numMembers) {
    if (numMembers >= 100) {
        cout << "Member limit reached!" << endl;
        return;
    }

    Member newMember;
    cout << "Enter your ID number: ";
    cin >> newMember.IDNumber;
    cin.ignore();
    if (existingID(newMember.IDNumber, memberDetails, numMembers)) {
        cout << endl << "An account already exists with the ID number!" << endl<<endl;
        return;
    }
    cout << "Enter your name: ";
    cin >> newMember.name;
    cout << "Enter an email address: ";
    cin >> newMember.email;
    cin.ignore();
    if (existingEmail(newMember.email, memberDetails, numMembers)) {
        cout << endl << "An account already exists with the email!" << endl << endl;
        return;
    }
    cout << "Enter a password: ";
    cin >> newMember.password;
    cout << "Enter your phone number: ";
    cin >> newMember.phone;
    cout << endl;
    cin.ignore();
    memberDetails[numMembers++] = newMember;
    cout << "Successful!" << endl << endl;
}

bool existingID(char newIDNumber[], Member memberDetails[], int& numMembers) {
    for (int i = 0;i < numMembers;i++) {
        if (strcmp(newIDNumber, memberDetails[i].IDNumber) == 0) {
            return true;
        }
    }
    return false;
}

bool existingEmail(char newEmail[], Member memberDetails[], int& numMembers) {
    for (int i = 0;i < numMembers;i++) {
        if (strcmp(newEmail, memberDetails[i].email) == 0) {
            return true;
        }
    }
    return false;
}

void saveMemberInfo(ofstream& outMemberFile, Member memberDetails[], int numMembers) {
    outMemberFile.open("MemberInfo.dat", ios::out | ios::binary);
    if (!outMemberFile) {
        cout << "Error opening file for saving!"<<endl;
        return;
    }
    for (int i = 0;i < numMembers;i++) {
        outMemberFile.write(reinterpret_cast<const char*>(&memberDetails[i]), sizeof(Member));
    }

    outMemberFile.close();
}