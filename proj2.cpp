#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<math.h>
#include<time.h>

using namespace std;
/*
class update_list {
private:

public:

};
*/
class flora {
private:
    int nraw = 0, ncolumn = 0, battary = 0, R[2]{0};
public:
    int*** floor = NULL;
    /*flora() {
        
    }*/

    void load_floor(char* path) {
        char line[1025]{ 0 }, * temp = NULL, * slices = NULL;

        ifstream input_file(path);
        if (!input_file) cout << "load input file failed" << endl;

        input_file.getline(line, 32);
        temp = strtok_s(line, " ", &slices);
        nraw = stoi(temp);
        temp = strtok_s(NULL, " ", &slices);
        ncolumn = stoi(temp);
        temp = strtok_s(NULL, " ", &slices);
        battary = stoi(temp);
        cout << nraw << " " << ncolumn << " " << battary << endl;

        floor = new int** [nraw]; //floor[nraw][ncolumn][3]
        for (int i = 0; i < nraw; i++) {
            floor[i] = new int* [ncolumn];
            for (int j = 0; j < ncolumn; j++) {
                floor[i][j] = new int[3]{ 0 };
            }
        }

        double dur = 0;
        clock_t start, end;
        start = clock();

        for (int i = 0; i < nraw; i++) {
            input_file.getline(line, 1025);
            temp = strtok_s(line, " ", &slices);
            //cout << temp << endl;

            for (int j = 0; j < ncolumn; j++) {
                floor[i][j] = new int[3]{ 0 };// [0]:wall [1]:distance [2]:have been here

                if (temp[j] == '1') {
                    floor[i][j][0] = 2;// here is wall
                }
                else if (temp[j] == '0') {
                    floor[i][j][0] = 0;// here is empty
                }
                else {
                    floor[i][j][0] = 1;// here is bettary
                    floor[i][j][2] = 1;// have been here
                    R[0] = i;
                    R[1] = j;
                }
            }
        }

        end = clock();
        dur = (double)(end - start);
        printf("Use Time:%f\n", (dur / CLOCKS_PER_SEC));

    }

    void print_floor(int layer) {
        cout << endl;
        for (int i = 0; i < nraw; i++) {
            for (int j = 0; j < ncolumn; j++) {
                cout << floor[i][j][layer];
            }
            cout << endl;
        }
    }

    int f(int index[2], int layer) {
        return(floor[index[0]][index[1]][layer]);
    }

    int find_kernel(int(*here_list)[2], int here[2], int contour) {
        int counter = 0;




        return(counter);
    }



    int contour_iter(int(*update_list)[2], int length, int contour) {
        int here_list[2048][2]{ 0 }, here_length = 0, update_index = 0;

        while (update_index<length) {
            here_length += find_kernel(here_list, update_list[update_index], contour);
            update_index++;
        }

        for (int i = 0; i < here_length; i++) {
            update_list[i][0] = here_list[i][0], update_list[i][1] = here_list[i][1];
        }

        delete []here_list;

        return here_length;
    }
    
    void contour_map() {
        int update_list[2048][2]{ 0 }, update_index = 1, contour = 1;
        update_list[0][0] = R[0], update_list[0][1] = R[1];
        while (update_index) {
            update_index = contour_iter(update_list, update_index, contour);
            contour++;
        }

    }
};
    


int main(int argc, char* argv[])
{
    cout << "Hello World!\n";

    flora abc;
    abc.load_floor(argv[1]);
    abc.print_floor(0);

}
