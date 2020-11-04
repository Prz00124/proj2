#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Hello World!\n";
    char line[2056], * temp, *slices = NULL;
    int x = 0, y = 0;

    ifstream input_file(argv[1]);
    if (!input_file) cout << "load input file failed" << endl;

    input_file.getline(line, 16);
    temp = strtok_s(line, " ", &slices);
    x = stoi(temp);
    temp = strtok_s(NULL, " ", &slices);
    y = stoi(temp);
    cout << x << " " << y << endl;

}
