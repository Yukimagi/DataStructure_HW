#include <iostream>
#include "Maze.h"
#include <cstring>
#include<string>

using namespace std;
#define NEW2D(H, W, TYPE) (TYPE **)new2d(H, W, sizeof(TYPE))

//網路上可用於memset初始化0的動態二維陣列建立function
//https://www.mropengate.com/2015/12/cc-dynamic-2d-arrays-in-c.html
void* new2d(int h, int w, int size)
{
    int i;
    void** p;

    p = (void**)new char[h * sizeof(void*) + h * w * size];
    for (i = 0; i < h; i++)
        p[i] = ((char*)(p + h)) + i * w * size;

    return p;
}

int main()
{
    string inputs;
    string elements;
    int row = 0;
    int column = 0;
    Stack<Items<int, int> > stack;//建立stack

    //計算有幾行幾列
    while (getline(cin, inputs))
    {
        row++;
        elements = elements+" " + inputs;
        column = (inputs.length() + 1) / 2;//因為有空格所以要(s+1)/2
    }

    //建立動態二維陣列存地圖
    //(storing the legal positions)=maze
    char** map = NEW2D(row, column, char);

    int r = 0;//初始化地圖row=0
    int c = 0;//初始化地圖column=0

    //定義開始位置
    int start_row;
    int start_col;

    //定義結束位置
    int end_row;
    int end_col;

    //將地圖的每個值存入map
    for (int i = 1; i < elements.length(); i += 2)//因為有空格因此每次加2
    {
        map[r][c] = elements[i];
        if (elements[i] == 's')//存起始位置
        {
            start_row = r;
            start_col = c;
        }
        else if (elements[i] == 'e')//存結束位置
        {
            end_row = r;
            end_col = c;
        }

        c++;

        if (c == column) {
            r++,
            c = 0;
        }
    }

    Items<int, int> now(start_row, start_col);

    //(storing the positions visited)
    int** mark = NEW2D(row, column, int);
    //先初始化為0(表示沒走過)
    ::memset(mark[0], 0, sizeof(int) * row * column);

    stack.Push(now);

    // 方位結構
    struct offsets
    {
        int a;// to be used in move[q].a
              // (表示列的位移量)
        int b;// to be used in move[q].b
             // (表示行的位移量) 
    };

    //(storing the moving directions)
    offsets mov[8] = { { -1,0 },{ -1,1 },{ 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 } };

    //當尚未到達終點
    while (map[now.row][now.column] != 'e')//items內的row&column
    {
        mark[now.row][now.column] = 1;

        bool hasMoved = false;//初始化不可走
       
        for (int i = 0; i < 8; i++)
        {
            int g = now.row + mov[i].a;//mov[i][0]
            int h = now.column + mov[i].b;//mov[i][1]

            //1.在row與column大小裡2.並沒有走過(=0)3.非牆壁(b)
            if (g >= 0 && g < row &&h >= 0 && h < column &&mark[g][h] == 0 &&map[g][h] != 'b')
            {                                                                                 
                stack.Push(now);//push現在的值
                now.row =g, now.column=h;//依照offset值定義下一個位置
                hasMoved = true;//並定義可走
                break;
            }
        }
        //如果不可走
        if (hasMoved == false)
        {   //最上層的拿出來
            now.row = stack.Top().row;
            now.column = stack.Top().column;
            stack.Pop();//並將stack pop掉最上層
        }

    }

    int step = stack.Size();//記錄走幾步

    while (!stack.IsEmpty())
    {
        //最上層的拿出來
        int r_now = stack.Top().row;
        int c_now = stack.Top().column;
        stack.Pop();//並將stack pop最上層

        //紀錄拿掉後的下一個最上層
        int r_next = stack.Top().row;
        int c_next = stack.Top().column;


        if ((r_now - r_next) * (c_now - c_next) > 0) //[i−1] [j−1] 或 [i+1] [j+1]
        {
            map[r_now][c_now] = '\\';
        }
        else if ((r_now - r_next) * (c_now - c_next) < 0)//[i−1] [j+1] 或 [i+1] [j−1]
        {
            map[r_now][c_now] = '/';
        }
        else if ((r_now - r_next) != 0) //[i−1] [j] 或 [i+1] [j]
        {
            map[r_now][c_now] = '|';
        }
        else {//[i] [j−1] 或 [i] [j+1] 
            map[r_now][c_now] = '-';
        }

        if (map[r_next][c_next] == 's')
        {
            break;
        }

    }
    //印出結果
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Total " << step - 1 << " Steps."<<endl;

    delete[]map;
    delete[]mark;

    return 0;
}
