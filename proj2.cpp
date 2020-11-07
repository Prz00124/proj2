#include<iostream>
#include<string>
#include<fstream>
//#include<stdlib.h>

#include<time.h>
#include<iomanip>

using namespace std;

class path_node {
private:
    int position[2]{ 0 };
public:
    path_node* next = NULL;

    path_node(int y, int x) {
        position[0] = y, position[1] = x;
    }
};

class path {
private:
    int length = 0;
    path_node* tail, * header;
public:
    path(int R_y, int R_x) {
        header = new path_node(R_y, R_x);
        tail = header;
    }

    void push(int B[2]) {
        tail->next = new path_node(B[0], B[1]);
        tail = tail->next;
        length++;
    }
};

class path_list {
private:
    int length = -1;
    path* llist[1024]{ NULL };
    
public:
    void new_path(int R_y, int R_x) {
        length++;
        llist[length] = new path(R_y, R_x);
    }

    void push_current(int B[2]) {
        llist[length]->push(B);
    }
};


class flora {
private:
    int nraw = 0, ncolumn = 0, battary = 0, B[2]{ 0 }, R[2]{ 0 }, *** floor = NULL;
    path_list path_set;
public:
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
                    floor[i][j][0] = 1,// here is bettary
                    floor[i][j][2] = 1;// have been here

                    R[0] = i, R[1] = j, B[0] = i, B[1] = j;
                    path_set.new_path(i, j);

                    if (R[0] == 0) {
                        B[0]++;
                        f(B[0], B[1])[1] = 1;
                        path_set.push_current(B);
                    }
                    else if( R[0] == nraw - 1) {
                        B[0]--;
                        f(B[0], B[1])[1] = 1;
                        path_set.push_current(B);
                    }
                    else if (R[1] == 0) {
                        B[1]++;
                        f(B[0], B[1])[1] = 1;
                        path_set.push_current(B);
                    }
                    else if (R[1] == ncolumn - 1) {
                        B[1]--;
                        f(B[0], B[1])[1] = 1;
                        path_set.push_current(B);
                    }

                }
            }
        }

        input_file.close();

    }

    void print_floor(int layer) {
        cout << endl;
        for (int i = 0; i < nraw; i++) {
            for (int j = 0; j < ncolumn; j++) {
                cout << floor[i][j][layer]%10;
            }
            cout << endl;
        }
    }

    int *f(int a, int b) {
        return(floor[a][b]);
    }

    bool find_kernel(int a, int b, int contour) {
        int* there = f(a, b);
        if (there[0]) {
            return false;
        }
        else if (there[1]) {
            return false;
        }
        else {
            there[1] = contour;
            return true;
        }
    }

    int expand(int(*here_list)[2], int here[2], int here_index, int contour) {
        int counter = 0;
        if (find_kernel(here[0]+1, here[1], contour)) {
            here_list[here_index + counter][0] = here[0] + 1,
            here_list[here_index + counter][1] = here[1];
            counter++;
        }
        if (find_kernel(here[0]-1, here[1], contour)) {
            here_list[here_index + counter][0] = here[0] - 1,
            here_list[here_index + counter][1] = here[1];
            counter++;
        }
        if (find_kernel(here[0], here[1]+1, contour)) {
            here_list[here_index + counter][0] = here[0],
            here_list[here_index + counter][1] = here[1] + 1;
            counter++;
        }
        if (find_kernel(here[0], here[1]-1, contour)) {
            here_list[here_index + counter][0] = here[0],
            here_list[here_index + counter][1] = here[1] - 1;
            counter++;
        }

        return(counter);
    }

    int contour_iter(int(*update_list)[2], int length, int contour) {
        int here_list[2048][2]{ 0 }, here_length = 0, update_index = 0;

        while (update_index<length) {
            here_length += expand(here_list, update_list[update_index], here_length, contour);
            update_index++;
        }

        for (int i = 0; i < here_length; i++) {
            update_list[i][0] = here_list[i][0], update_list[i][1] = here_list[i][1];
        }

        return here_length;
    }
    
    void contour_map() {
        int update_list[2048][2]{ 0 }, update_index = 1, contour = f(B[0], B[1])[1] + 1;
        update_list[0][0] = B[0], update_list[0][1] = B[1];
        while (update_index) {
            update_index = contour_iter(update_list, update_index, contour);
            contour++;
        }

    }

    void bot_iter() {

    }
};
    


int main(int argc, char* argv[])
{
    cout << "Hello World!\n";
    double dur = 0;
    clock_t start, end;


    flora abc;

    start = clock();

    abc.load_floor(argv[1]);

    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n", (dur / CLOCKS_PER_SEC));


    //abc.print_floor(0);
    start = clock();

    abc.contour_map();

    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n", (dur / CLOCKS_PER_SEC));
    
    //abc.print_floor(1);






}
