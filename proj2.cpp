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

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
