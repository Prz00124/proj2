#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>

using namespace std;

class flora {
private:
    char line[2056]{0}, * temp = NULL, * slices = NULL;
    int nraw = 0, ncolumn = 0;
public:
    int*** floor = NULL;
    /*flora() {
        
    }*/

    void load_floor(char* path) {
        ifstream input_file(path);
        if (!input_file) cout << "load input file failed" << endl;

        input_file.getline(line, 16);
        temp = strtok_s(line, " ", &slices);
        nraw = stoi(temp);
        temp = strtok_s(NULL, " ", &slices);
        ncolumn = stoi(temp);
        cout << nraw << " " << ncolumn << endl;

        floor = new int** [nraw]; //floor[nraw][ncolumn][3]
        for (int i = 0; i < nraw; i++) {
            floor[i] = new int *[ncolumn];
            int index = 0;
            floor[i][index] = new int[3]{0};

            input_file.getline(line, 2056);
            temp = strtok_s(line, " ", &slices);
            
            floor[i][index][0] = 1;
            index++;

            while (temp = strtok_s(NULL, " ", &slices)) {
                //temp = strtok_s(NULL, " ", &slices);
                if (temp[0] == '1') {
                    floor[i][index][0] = 1;
                }
                else if (temp[0] == '0') {
                    floor[i][index][0] = 0;
                }
                else {
                    floor[i][index][0] = -1;
                    floor[i][index][2] = 1;
                }
            }
        }

    }

    void print_floor() {
        
    }
};
    


int main(int argc, char* argv[])
{
    cout << "Hello World!\n";

    


}
