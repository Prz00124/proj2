import sys

def print_mat(mat):
    rows = len (mat)
    #cols = len (mat[0])
    for r in range(rows):
         #for c in range(cols):
        print(mat[r])
        #print("")

def load_floor():
    floor = open(sys.argv[2],'r')
    initial_val = floor.readline()
    inval_list = initial_val.split(' ')

    rows = int(inval_list[0])
    cols = int(inval_list[1])
    battery = int(inval_list[2])

    mat = [[]]

    for r in range(rows):
        mat.append([])
        for c in range(cols):
            mat[r].append(floor.read(1))
        floor.read(1)#pop \n

    floor.close()

    return(mat, rows, cols, battery)

#print_mat(mat)


def load_path():
    final_p = open(sys.argv[1],'r') # read 'final.path' from working directory

    t = int(final_p.readline()) # read total steps denote on the 1st line of .final 

    yum = final_p.read().split("\n")[:-1]
    yum = [ [int(k) for k in i.split(" ")] for i in yum]
    #print(yum[0])
    #input()

    print("total steps in record: ", t,
          " | In actually: ", len(yum),
          " | Battery: ", battery)

    if len(yum) != t:
        t = len(yum)
        print("\n!! Warning: total steps are not equal to assigned value !!\n")
        print("count your steps again")
    final_p.close()
    
    return(yum, t)



mat, rows, cols, battery = load_floor()
yum, t = load_path()

temp = []
#pre = []
flag = False
step_count = 0
start = yum[0]

#progress bar
counter = 0
ratio = 33
part = t//ratio

for i in range(t):
    '''proccess bar'''
    if (i%(part) == 0):
        print('\r' + '[step]:[%s%s]%.2f%%;' % (
        '█' * int(i*ratio/t), ' ' * (ratio-int(i*ratio/t)),
        float(i/t*100)), end='')
        counter += 1


    '''check process'''
    pre = temp
    temp = yum[i]
    #print(pre, temp)
    #input()

    if mat[temp[0]] [temp[1]] == '1':
        print(f'step:{i} | x : {temp[0]} | y : {temp[1]} :\n', "Wall crush!")
        flag = True
        break
    elif pre != [] and abs(pre[0] - temp[0]) + abs(pre[1] - temp[1]) != 1:
        print(f'step:{i} | x : {temp[0]} | y : {temp[1]} :\n', "Move too fast or not move!")
        flag = True
        break
    mat[temp[0]] [temp[1]] = '2'
    if temp == start:
        step_count = 0
    else :
        step_count +=1
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
    if step_count > battery:
        print(f'step={step_count}', "Battery not enough!")
        flag = True
        break

#print_mat(mat)
    
if not flag:
    for r in range(rows):
        for c in range(cols):
            if mat[r][c] == '0':
                print(f'\n(r:{r},c:{c}):NOT FILLED')
                flag = True
                break
if flag:
    print("Unexpected error")
else:
    print("SUCCESS")


