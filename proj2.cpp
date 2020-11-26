#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<thread> 
#include<time.h>
#include<iomanip>

const int cores = 16;

using namespace std;

class label {
public:
    string lab[1000];
    label() {
        for (int i = 0; i < 1000; i++) {
            lab[i] = to_string(i);
        }
    }

    void print(int i) {
        for (int j = 0; j < i; j++) {
            cout << lab[j] << ' ';
        }
        cout << endl;
    }
};

class diction {
private:
    short lengh = 0;
public:
    label* abc;

    diction(int cor) {
        abc = new label[cor];
        lengh = cor;
    }

    void print(int top_n) {
        for (int i = 0; i < lengh; i++) {
            abc[i].print(top_n);
        }
    }

    label *part(int n) {
        return(abc + n);
    }

};

class path_node {
private:
    
public:
    path_node* next = NULL;
    int position[2]{ 0 };

    path_node(int y, int x) {
        position[0] = y, position[1] = x;
    }
    
};

class path {
private:
    path_node* tail, * header;
public:
    int length = 1;

    path(int R_y, int R_x) {
        header = new path_node(R_y, R_x);
        tail = header;
    }

    void push(int B[2]) {
        tail->next = new path_node(B[0], B[1]);
        tail = tail->next;
        length++;
    }

    void add(path_node *peice) {
        tail->next = peice;
        while (!(tail->next == NULL)) {
            tail = tail->next;
            length++;
        }
    }

    void clear() {
        path_node *temp;
        for (int i = 0; i < length; i++) {
            temp = header;
            header = header->next;
            delete temp;
        }
    }

    void print() {
        path_node* temp = header;
        for (int i = 0; i < length; i++) {
            cout << temp->position[0] << " " << temp->position[1]<<endl;
            temp = temp->next;
        }
    }

    void to_file(stringstream* BBB, string *lab) {
        path_node *temp = header;

        for (int i = 0; i < length; i++) {
            int* temptemp = temp->position;
            *BBB << lab[temptemp[0]] << ' ' << lab[temptemp[1]] << '\n';
            temp = temp->next;
        }
    }

};

void read_job(path* i_th, stringstream* BBB, string *lab) {
    i_th->to_file(BBB, lab);
}

class path_list {
private:
    int length = -1;
    int R[2]{ 0 }, r[2]{ 0 };
    bool bad_R = false;
    path* llist[1024]{ NULL };
    
public:
    path_list(bool bad, int A[2], int a[2]) {
        R[0] = A[0], R[1] = A[1];
        r[0] = a[0], r[1] = a[1];
        bad_R = bad;
    }

    void new_path() {
        length++;
        if (bad_R) {
            llist[length] = new path(R[0], R[1]);
            llist[length]->push(r);
        }
        else {
            llist[length] = new path(R[0], R[1]);
        }
    }

    void push_current(int B[2]) {
        llist[length]->push(B);
    }

    void add_current(path_node* temp) {
        llist[length]->add(temp);
    }

    int total() {
        int sum = 0;
        for (int i = 0; i < length + 1; i++) {
            sum += llist[i]->length;
        }
        return sum;
    }

    int info() {
        int temp = total();
        cout << "length: " << length + 1 << " | " << "total steps: " << temp << endl;
        return temp ;
    }

    void print() {
        for (int i = 0; i < length + 1; i++) {
            llist[i]->print();
            cout << "~~~~next one~~~~" << endl;
        }
    }

    void layout(string output_path) {
        ofstream file;
        file.open(output_path, ios_base::app);
        stringstream* BBB = new stringstream[length + 1];


        if (cores > 1) {
            thread* workers = new thread[length + 1];
            diction qqq(cores);

            int counter = (length + 1) / cores;
            for (int j = 0; j < counter; j++) {
                for (int i = j * cores; i < (j + 1) * (cores); i++) {
                    workers[i] = thread(read_job, llist[i], BBB + i, qqq.abc[j % 6].lab);
                }

                for (int i = j * cores; i < (j + 1) * (cores); i++) {
                    workers[i].join();
                }
            }

            for (int i = counter * cores; i < length + 1; i++) {
                workers[i] = thread(read_job, llist[i], BBB + i, qqq.abc[i % 6].lab);
            }
            for (int i = counter * cores; i < length + 1; i++) {
                workers[i].join();
            }
        }
        else {
            diction qqq(1);
            for (int i = 0; i < length + 1; i++) {
                read_job(llist[i], BBB + i, qqq.abc[0].lab);
        }


        for (int i = 0; i < length + 1; i++) {
            file << (BBB+i)->rdbuf();
        }

        file.close();
    }
};

class BOT {
    int*** floor = NULL, boot = 0;
    int B[2]{ 0 }, charger[2]{ 0 };
    bool bad_R;
    

public:
    int battary = 0;

    BOT(int*** fff, int* r, int batt, bool kkk) {
        floor = fff;
        B[0] = r[0], B[1] = r[1];
        charger[0] = B[0], charger[1] = B[1];
        battary = batt;
        boot = batt;
        bad_R = kkk;
    }

    int* f(int  a, int  b) {
        return(floor[a][b]);
    }

    int* position() {
        return(B);
    }

    void reboot() {
        battary = boot;
    }

    bool powerful(int* target) {//enough returns true
        //cout << target[0] << " " << target[1] << endl;
        if ((battary - f(B[0], B[1])[2]) > f(target[0], target[1])[1]) return true;
        else return false;
    }

    bool power() {//enough returns true
        if (battary > f(B[0], B[1])[1] + 2) return true;
        else return false;
    }

    path_node* rule1() {// return 1.not wall 2.farest 3.strange as direction 0 1 2 3 
        //one: _0_    two: 0_3
        //     1B3         _B_
        //     _2_         1_2
        int one[4][2] = { {B[0] - 1, B[1] }, {B[0], B[1] - 1}, {B[0] + 1, B[1]}, {B[0], B[1] + 1} },
            two[4][2] = { {B[0] - 1, B[1] - 1}, {B[0] + 1, B[1] - 1}, {B[0] + 1, B[1] + 1}, {B[0] - 1, B[1] + 1} };
        int farest = 0, far_ind = 0, pass_by = 0;// far_ind [one{0,1,2,3}, two{0,1,2,3}]


        for (int i = 0; i < 4; i++) {
            //cout << one[i][0] << " " << one[i][1] << endl;
            int* neighbor = f(one[i][0], one[i][1]), index, *point;

            if (!(neighbor[0] == 2)) {    //if this one not wall
                if (neighbor[0] == 0 && neighbor[1] > farest) {//haven't been here
                    farest = neighbor[1];
                    far_ind = i;
                }

                for (int j = 0; j < 2; j++) {       // for neighbor two
                    index = (i + 3 + j) % 4;
                    point = f(two[index][0], two[index][1]);
                    if (point[0] == 0) {            // not wall and never been here
                        if (far_ind == index) {
                            if (neighbor[0]==0) {
                                pass_by = i;
                            }
                        }
                        else if (point[1] > farest) {    // if this norm two point is farest
                            farest = point[1];
                            far_ind = index + 4;
                            pass_by = i;
                        }
                        
                    }
                }
            }
        }

        if (farest) {
            if (far_ind > 3) {
                path_node* temp = new path_node(one[pass_by][0], one[pass_by][1]);
                f(one[pass_by][0], one[pass_by][1])[0] = 1;
                far_ind -= 4;
                temp->next = new path_node(two[far_ind][0], two[far_ind][1]);
                B[0] = two[far_ind][0], B[1] = two[far_ind][1];
                f(two[far_ind][0], two[far_ind][1])[0] = 1;
                battary -= 2;
                return(temp);
            }
            else if (far_ind >= 0) {
                path_node* temp = new path_node(one[far_ind][0], one[far_ind][1]);
                B[0] = one[far_ind][0], B[1] = one[far_ind][1];
                f(one[far_ind][0], one[far_ind][1])[0] = 1;
                battary--;
                return(temp);
            }
        }

        return( NULL );
    }

    path_node* go_deeper() {
        //path_node* temp = NULL;
        if (power()) {
            return rule1();
        }
        return NULL;
    }

    path_node* ruleHome() {
        if (B[0] == charger[0] && B[1] == charger[1]) {
            return NULL;
        }
        f(B[0], B[1])[0] = 1;

        int  one[4][2] = { {B[0] - 1, B[1] }, {B[0], B[1] - 1}, {B[0] + 1, B[1]}, {B[0], B[1] + 1} };
        int * minima = f(B[0], B[1]), miniid = 0;

        for (int i = 0; i < 4; i++) {
            int* temp = f(one[i][0], one[i][1]);
            if (!(temp[0] == 2)) {
                if (temp[1] < minima[1]) {
                    minima = temp;
                    miniid = i;
                }
                else if (temp[1] == minima[1] && temp[0] < minima[0]) {
                    minima = temp;
                    miniid = i;
                }
            }
        }

        battary--;
        B[0] = one[miniid][0], B[1] = one[miniid][1];
        
        return(new path_node(B[0], B[1]));
    }

    path_node* go_home() {
        path_node* temp = ruleHome(), *head = temp, *tail = temp;
        temp = ruleHome();
        while (!(temp == NULL)) {
            tail->next = temp;
            tail = temp;
            temp = ruleHome();
        }
        //tail->next = new path_node(B[0], B[1]);

        return(head);
    }

    path_node* ruleOther() {
        if (f(B[0], B[1])[2] == 1) {
            return NULL;
        }

        int  one[4][2] = { {B[0] - 1, B[1] }, {B[0], B[1] - 1}, {B[0] + 1, B[1]}, {B[0], B[1] + 1} };
        int* minima = f(B[0], B[1]), miniid = 0;

        for (int i = 0; i < 4; i++) {
            int* temp = f(one[i][0], one[i][1]);
            if (!(temp[0] == 2)) {
                if (temp[2] < minima[2]) {
                    minima = temp;
                    miniid = i;
                }
            }
        }

        battary--;
        B[0] = one[miniid][0], B[1] = one[miniid][1];
        f(B[0], B[1])[0] = 1;
        return(new path_node(B[0], B[1]));
    }

    path_node* go_another() {
        path_node* temp = ruleOther(), * head = temp, * tail = temp;
        temp = ruleOther();
        while (!(temp == NULL)) {
            tail->next = temp;
            tail = temp;
            temp = ruleOther();
        }
        return(head);
    }

};

class flora {
private:
    int nraw = 0, ncolumn = 0, R[2]{ 0 }, r[2]{ 0 };
    int battary = 0;
    bool bad_R = false;
    path_list *path_set;
    BOT* bot;

// floor[0]: 2 wall, 1: have been here.
// floor[1]: contour map, 0 reboot, 1 if bad_R.
// floor[2]: guide ground.
public:
    int*** floor = NULL;

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

        floor = new int** [nraw]; //floor[nraw][ncolumn][3], read map(initial floor[0]).
        for (int i = 0; i < nraw; i++) {
            input_file.getline(line, 1025);
            temp = strtok_s(line, " ", &slices);

            floor[i] = new int* [ncolumn];
            for (int j = 0; j < ncolumn; j++) {
                if (temp[j] == '1') {
                    floor[i][j] = new int[3]{ 2,0,1 };// here is wall
                }
                else if (temp[j] == '0') {
                    floor[i][j] = new int[3]{ 0,0,1 };// here is empty
                }
                else {//if read R
                    floor[i][j] = new int[3]{ 1,0,1 };//[0] = 1: have been here
                    R[0] = i, R[1] = j; r[0] = i, r[1] = j; //R the recharge place and r the initial point

                    //wheather bad_R
                    if (R[0] == 0) {
                        bad_R = true;
                        r[0]++;
                    }
                    else if (R[0] == nraw - 1) {
                        bad_R = true;
                        r[0]--;
                    }
                    else if (R[1] == 0) {
                        bad_R = true;
                        r[1]++;
                    }
                    else if (R[1] == ncolumn - 1) {
                        bad_R = true;
                        r[1]--;
                    }
                }
            }
        }

        input_file.close();

        if (bad_R) {
            f(R[0], R[1])[0] = 2;//bad R in the wall
            f(r[0], r[1])[0] = 1;
            //f(r[0], r[1])[1] = 1;
        }
        f(r[0], r[1])[1] = 1;


        path_set = new path_list(bad_R, R, r);
        path_set->new_path();

        /*if (bad_R){
            contour_map(r, f(r[0], r[1])[1]+1, 1);// build contour(initial floor [1])
        }
        else {
            
        }*/
        contour_map(r, f(r[0], r[1])[1], 1);// build contour(initial floor [1])
        

        bot = new BOT(floor, r, battary, bad_R);

    }

    void print_floor(int layer) {
        cout << endl;
        cout << endl;
        cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<< endl;
        cout << endl;
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

    bool find_kernel(int a, int b, int contour, int layer) {
        int* there = f(a, b);
        if (there[0]==2) {// not wall
            return false;
        }
        else if (there[layer]) {//has been contoured?
            return false;
        }
        else {// no contour
            there[layer] = contour;
            return true;
        }
    }

    int expand(int(*here_list)[2], int here[2], int here_index, int contour, int layer) {
        int counter = 0;
        if (find_kernel(here[0]+1, here[1], contour, layer)) {
            here_list[here_index + counter][0] = here[0] + 1,
            here_list[here_index + counter][1] = here[1];
            counter++;
        }
        if (find_kernel(here[0]-1, here[1], contour, layer)) {
            here_list[here_index + counter][0] = here[0] - 1,
            here_list[here_index + counter][1] = here[1];
            counter++;
        }
        if (find_kernel(here[0], here[1]+1, contour, layer)) {
            here_list[here_index + counter][0] = here[0],
            here_list[here_index + counter][1] = here[1] + 1;
            counter++;
        }
        if (find_kernel(here[0], here[1]-1, contour, layer)) {
            here_list[here_index + counter][0] = here[0],
            here_list[here_index + counter][1] = here[1] - 1;
            counter++; 
        }

        return(counter);
    }

    int contour_iter(int(*update_list)[2], int length, int contour, int layer) {
        int here_list[2048][2]{ 0 }, here_length = 0;
        int update_index = 0;

        while (update_index < length) {
            here_length += expand(here_list, update_list[update_index], here_length, contour, layer);
            update_index++;
        }

        for (int i = 0; i < here_length; i++) {
            update_list[i][0] = here_list[i][0], update_list[i][1] = here_list[i][1];
        }

        return here_length;
    }
    
    void contour_map(int* orient, int contour, int layer) {
        int update_list[2048][2]{ 0 };
        int update_index = 1;
        update_list[0][0] = orient[0], update_list[0][1] = orient[1];
        f(orient[0], orient[1])[layer] = contour;
        while (update_index) {
            contour++;
            update_index = contour_iter(update_list, update_index, contour, layer);
            
        }
    }

    bool guide_kernel(int a, int b) { //find out if i have been here
        int* there = f(a, b);
        if (there[0] == 1&& there[2]>0) {
            there[2] = 0;
            return true; 
        }
        else return false;
    }

    int expand_guide(int(*here_list)[2], int here[2], int here_index) {
        int counter = 0, kkk = 0;
        if (guide_kernel(here[0] + 1, here[1])) {
            here_list[here_index + counter][0] = here[0] + 1,
                here_list[here_index + counter][1] = here[1];
            counter++;
        }
        else if (f(here[0] + 1, here[1])[0] == 0) kkk = (-(here[0] + 1) - here[1] * 1000);

        if (guide_kernel(here[0] - 1, here[1])) {
            here_list[here_index + counter][0] = here[0] - 1,
                here_list[here_index + counter][1] = here[1];
            counter++;
        }
        else if (f(here[0] - 1, here[1])[0] == 0) kkk = (-(here[0] - 1) - here[1] * 1000);

        if (guide_kernel(here[0], here[1] + 1)) {
            here_list[here_index + counter][0] = here[0],
                here_list[here_index + counter][1] = here[1] + 1;
            counter++;
        }
        else if (f(here[0], here[1] + 1)[0] == 0) kkk = (-here[0] - (here[1] + 1) * 1000);

        if (guide_kernel(here[0], here[1] - 1)) {
            here_list[here_index + counter][0] = here[0],
                here_list[here_index + counter][1] = here[1] - 1;
            counter++;
        }
        else if (f(here[0], here[1] - 1)[0] == 0) kkk = (-here[0] - (here[1] - 1) * 1000);

        if (kkk) return kkk;
        else return(counter);
    }

    int guide_iter(int(*update_list)[2], int length) {
        int here_list[2048][2]{ 0 };
        int here_length = 0, update_index = 0, temp = 0;

        while (update_index < length) {
            temp = expand_guide(here_list, update_list[update_index], here_length);

            if (temp < 0) return temp;

            here_length += temp;
            update_index++;
        }

        for (int i = 0; i < here_length; i++) {
            update_list[i][0] = here_list[i][0], update_list[i][1] = here_list[i][1];
        }

        return here_length;
    }

    int guide_who(int orient[2]) {
        //print_floor(0);
        //print_floor(1);
        int update_list[2048][2]{ 0 };
        int update_index = 1;
        update_list[0][0] = orient[0], update_list[0][1] = orient[1];
        while (update_index) {
            
            update_index = guide_iter(update_list, update_index);
            //cout << update_index << " ";
            if (update_index < 0) return(update_index);
        }

        return 0;
    }

    int guide(int target[2]) { // 0: have power to go other   1: whole map finished     2:should go home
        int con = guide_who(target);
        int temp[2] = { -con % 1000, -con / 1000 };

        if (temp[0] == 0 && temp[1] == 0) {
            return(1); //whole map finished
        }
        else {
            contour_map(temp, 1, 2);// reflash guide map
            //print_floor(2);
            if (!bot->powerful(temp)) return -1;
            return(0);
        }
        
    }

    bool step() {
        path_node* temp = NULL;
        //cout << bot->position()[0] << " " << bot->position()[1]<< " " << bot->battary << endl;
        temp = bot->go_deeper();
        if (temp == NULL) {
            if (bot->power()) { //has enough power but no neighbor to go
                int condition = guide(bot->position());
                if (condition == 1) return false; // guide 1 --> the whole map done
                else if (condition == -1) { //no enough power, so go home
                    temp = bot->go_home();
                    path_set->add_current(temp);
                    bot->reboot();
                    path_set->new_path();

                }
                else {// there is another strange point guide find and bot have power
                    //cout << "go another" << endl;
                    temp = bot->go_another();
                    path_set->add_current(temp);
                }
            }
            else {//has no power, should go home
                //cout << "go home1" << endl;
                temp = bot->go_home();
                path_set->add_current(temp);
                bot->reboot();
                path_set->new_path();
            }
        }
        else {
            path_set->add_current(temp);
        }
        return true;
    }

    int summary() {
        //path_set->print();
        return path_set->info();
    }

    void layout(string file_name){
        path_set->layout(file_name);
    }
};

int main(int argc, char* argv[])
{
    //cout << "Hello World!\n";
    double dur = 0;
    clock_t start, end;

    /*----------------------------------------------------------------------------*/

    start = clock();

    flora abc;
    abc.load_floor(argv[1]);
    //abc.print_floor(0);

    end = clock();
    dur = (double)(end - start);
    printf("Initial Time:%f\n", (dur / CLOCKS_PER_SEC));

    /*----------------------------------------------------------------------------*/

    start = clock();
    
    while (abc.step()) {
        //counter++;
    }
    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n", (dur / CLOCKS_PER_SEC));

    /*----------------------------------------------------------------------------*/

    start = clock();

    ofstream file;
    string file_path = "output/my.path";
    file.open(file_path);
    file << abc.summary() << endl;
    file.close();
    abc.layout(file_path);

    end = clock();
    dur = (double)(end - start);
    printf("Layout Time:%f\n", (dur / CLOCKS_PER_SEC));

    /*----------------------------------------------------------------------------*/

}

/*
start = clock();

end = clock();
dur = (double)(end - start);
printf("Use Time:%f\n", (dur / CLOCKS_PER_SEC));
*/