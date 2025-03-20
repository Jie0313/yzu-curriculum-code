#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the vector program
void load(vector< char* >& program);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(char* sourceLine);

// deletes all string constants from sourceLine
void delStrConsts(char* sourceLine);

// deletes all character constants from sourceLine
void delCharConsts(char* sourceLine);

// extracts all identifiers from sourceLine, and
// put them into the vector identifiers
void extractIdentifiers(char* sourceLine, vector< char* >& identifiers);

// stores all non-keyword strings in the vector identifiers into a text file
void store(vector< char* >& identifiers);

// returns true if and only if str is a C++ keyword
bool keyword(char str[]);

// returns true iff identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(vector< char* >& identifiers, int pos);

const char keywords[][20] = { "auto", "break", "case", "char", "const",
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
    vector< char* > program;

    // reads in a C++ program from a cpp file, and put it to the vector program
    load(program);

    vector< char* > identifiers;
    for (size_t i = 0; i < program.size(); i++)
    {
        delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
        delStrConsts(program[i]); // deletes all string constants from program[ i ]
        delCharConsts(program[i]); // deletes all character constants from program[ i ]

        if (strcmp(program[i], "") != 0)
            extractIdentifiers(program[i], identifiers);
        // extracts all identifiers from program[ i ], and put them into the vector identifiers
    }

    // stores all non-keyword strings in the vector identifiers into a text file
    store(identifiers);

    for (size_t i = 0; i < identifiers.size(); i++)
        delete[] identifiers[i];

    for (size_t i = 0; i < program.size(); i++)
        delete[] program[i];

    system("pause");
}

void load(vector< char* >& program)
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

    char line[120];
    while (inFile.getline(line, 120)) {
        char* line2 = new char[strlen(line) + 1];
        strcpy_s(line2,strlen(line) + 1, line);
        program.push_back(line2);
    }




    inFile.close();
}


void delComment(char* sourceLine)
{
    size_t length = strlen(sourceLine);
    if (length > 1)
        for (size_t i = 0; i < length - 1; i++)
            if (sourceLine[i] == '/' && sourceLine[i + 1] == '/')
            {
                sourceLine[i] = '\0';
                return;
            }
}

void delStrConsts(char* sourceLine)
{
    size_t length = strlen(sourceLine);
    if (length > 1) {
        for (size_t i = 0;i < length;i++) {
            if (sourceLine[i] == '"') {
                sourceLine[i] = ' ';
                i++;
                while (sourceLine[i] != '"') {
                    if (sourceLine[i] == '\\' && sourceLine[i + 1] == '"') {
                        sourceLine[i] = ' ';
                        sourceLine[i + 1] = ' ';
                    }
                    else
                        sourceLine[i] = ' ';
                    i++;
                }
                sourceLine[i] = ' ';
            }
        }
    }
}


void delCharConsts(char* sourceLine)
{
    size_t length = strlen(sourceLine);
    if (length > 0) {
        for (size_t i = 0;i < length;i++) {
            if (sourceLine[i] == '\'' && sourceLine[i + 1] == '\\') {
                for (int j = 0;j < 4;j++) {
                    sourceLine[i] = ' ';
                    i++;
                }
                i--;
            }
            else if (sourceLine[i] == '\'') {
                for (int j = 0;j < 3;j++) {
                    sourceLine[i] = ' ';
                    i++;
                }
                i--;
            }
        }
    }
}


void extractIdentifiers(char* sourceLine, vector< char* >& identifiers)
{
    size_t length = strlen(sourceLine);
    size_t begin;
    size_t end = 0;

    while (true)
    {
        begin = end;
        while (begin < length && !isalpha(sourceLine[begin]) && sourceLine[begin] != '_') {
            begin++;
        }
        if (begin >= length)
            break;
        end = begin;
        while (isalnum(sourceLine[end]) || sourceLine[end] == '_') {
            end++;
        }


        char* identifier = new char[32];
        for (size_t i = begin; i < end; i++)
            identifier[i - begin] = sourceLine[i];
        identifier[end - begin] = '\0';

        if (!keyword(identifier))
            identifiers.push_back(identifier);
    }
}


void store(vector< char* >& identifiers)
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
    for (size_t i = 0;i < identifiers.size();i++) {
        if (!duplicate(identifiers, i)) {
            outFile << identifiers[i] << endl;
        }
    }




    outFile.close();
}

bool keyword(char str[])
{
    size_t numKeywords = sizeof(keywords) / 20;
    for (size_t i = 0; i < numKeywords; i++)
        if (strcmp(keywords[i], str) == 0)
            return true;

    return false;
}

bool duplicate(vector< char* >& identifiers, int pos)
{
    for (int i = 0; i < pos; i++)
        if (strcmp(identifiers[i], identifiers[pos]) == 0)
            return true;

    return false;
}