#include <iostream>
#include <fstream>
#include <string>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load(string* program, int& numLines);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(string& sourceLine);

// deletes all string constants from sourceLine
void delStrConsts(string& sourceLine);

// deletes all character constants from sourceLine
void delCharConsts(string& sourceLine);

// extracts all identifiers from sourceLine, and
// put them into the array identifiers
void extractIdentifiers(string& sourceLine, string* identifiers,
    int& numIdentifiers);

// stores all non-keyword strings in the array identifiers into a text file
void store(string* identifiers, int numIdentifiers);

// return true if and only if "str" is a C++ keyword
bool keyword(string str);

// returns true iff identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(string* identifiers, int pos);

const string keywords[] = { "auto", "break", "case", "char", "const",
                            "continue", "default", "define","do", "double",
                            "else", "enum", "extern", "float", "for",
                            "goto", "if", "int", "long", "register",
                            "return", "short", "signed", "sizeof",
                            "static", "struct", "switch", "typedef",
                            "union", "unsigned", "void", "volatile",
                            "while", "bool", "catch", "class",
                            "const_cast", "delete", "dynamic_cast",
                            "explicit", "false", "friend", "inline",
                            "mutable", "namespace", "new", "operator",
                            "private", "protected", "public",
                            "reinterpret_cast", "static_cast", "template",
                            "this", "throw", "true", "try", "typeid",
                            "typename", "using", "virtual", "include" };

int main()
{
    string* program = new string[500];
    int numLines = 0;

    // reads in a C++ program from a cpp file, and put it to the array program
    load(program, numLines);

    string* identifiers = new string[500];
    string null;
    int numIdentifiers = 0;

    for (int i = 0; i < numLines; i++)
    {
        delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
        delStrConsts(program[i]); // deletes all string constants from program[ i ]
        delCharConsts(program[i]); // deletes all character constants from program[ i ]

        if (program[i] != null)
            extractIdentifiers(program[i], identifiers, numIdentifiers);
        // extracts all identifiers from program[ i ], and put them into the array identifiers
    }

    // stores all non-keyword strings in the array identifiers into a text file
    store(identifiers, numIdentifiers);

    delete[] program;
    delete[] identifiers;

    system("pause");
}

void load(string* program, int& numLines)
{
    char filename[12];
    cout << "Input the name of a cpp file: ";
    cin >> filename;
    ifstream inFile(filename, ios::in);

    if (!inFile)
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }
    while (getline(inFile, program[numLines])) {
        numLines++;
    }




    inFile.close();
}


void delComment(string& sourceLine)
{
    size_t length = sourceLine.size();
    if (length > 1)
        for (size_t i = 0; i < length - 1; i++)
            if (sourceLine[i] == '/' && sourceLine[i + 1] == '/')
            {
                sourceLine.erase(i, length);
                break;
            }
}

void delStrConsts(string& sourceLine)
{
    size_t length = sourceLine.size();
    size_t begin, end;
    if (length > 0) {
        for (size_t i = 0;i < length;i++) {
            if (sourceLine[i] == '\"'&&sourceLine[i-1]!='\''&&sourceLine[i+1]!='\'') {
                begin = i;
                i++;
                while (i < length && sourceLine[i] != '\"') {
                    if (sourceLine[i] == '\\' && sourceLine[i + 1] == '\"') {
                        sourceLine[i + 1] = ' ';
                    }
                    i++;

                }
                if (i < length && sourceLine[i] == '\"') {
                    end = i;
                    sourceLine.erase(begin, end - begin + 1);
                    length = sourceLine.size();
                    i = begin - 1;
                }
            }
        }
    }


}

void delCharConsts(string& sourceLine)
{
    size_t length = sourceLine.size();
    if (length > 0) {
        for (size_t i = 0;i < length;i++) {
            if (sourceLine[i] == '\'' && sourceLine[i + 1] == '\\') {
                sourceLine.erase(i, 4);
                length = sourceLine.size();
            }
            else if (sourceLine[i] == '\'' && sourceLine[i + 1] != '\\') {
                sourceLine.erase(i, 3);
                length = sourceLine.size();

            }
        }
    }


}


void extractIdentifiers(string& sourceLine, string* identifiers,
    int& numIdentifiers)
{
    size_t length = sourceLine.size();
    size_t begin;
    size_t end = 0;

    while (true)
    {
        begin = end;
        while (!isalpha(sourceLine[begin]) && sourceLine[begin] != '_' && begin < length) {
            begin++;
        }

        if (begin >= length) {
            break;
        }

        end = begin;
        while (isalnum(sourceLine[end]) || sourceLine[end] == '_') {
            end++;
        }

        identifiers[numIdentifiers++] = sourceLine.substr(begin, end - begin);
    }
}

void store(string* identifiers, int numIdentifiers)
{
    char filename[20];
    cout << "Input the name of a txt file: ";
    cin >> filename;
    ofstream outFile(filename, ios::out);

    if (!outFile)
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }
    for (size_t i = 0;i < numIdentifiers;i++) {
        if (!duplicate(identifiers, i) && !keyword(identifiers[i]))
            outFile << identifiers[i] << endl;
    }




    outFile.close();
}


bool keyword(string str)
{
    const int numKeywords = 62;
    for (int i = 0; i < numKeywords; i++)
        if (keywords[i] == str)
            return true;

    return false;
}

bool duplicate(string* identifiers, int pos)
{
    for (int i = 0; i < pos; i++)
        if (identifiers[i] == identifiers[pos])
            return true;

    return false;
}