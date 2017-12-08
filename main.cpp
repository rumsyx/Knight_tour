#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include<vector>
#include <map>

using namespace std;
const int move_x[]= {1, 2, 2, 1, -1, -2, -2, -1};
const int move_y[]= {-2, -1, 1, 2, 2, 1, -1, -2};
//const int move_x[]= {-1,-1,1,1};
//const int move_y[]= {1,-1,1,-1};
const int board=8;
class Knight
{
private:
    int pos_x;
    int pos_y;
    int next_x;
    int next_y;
    int i;
    int way[board*board+1] ;
    int step ;
    bool a[board][board];
    int path[board*board][2];
    vector<vector<int> > v_wrong;
public:
    Knight();
//    ~Knight();
    void Step();
    void show();
    int calculate();
    void sort(int * next_step);
};


Knight::Knight()
{
    for(int i=0;i<board;i++)
        for(int j=0;j< board;j++)
            a[i][j] = false;

    for(int i=0;i<board*board;i++)
        for(int j=0;j<2;j++)
            path[i][j] = 0;
    for(int i=0;i<board*board+1;i++)
        way[i] = 0;
    pos_x = rand()%(board-1);
    pos_y = rand()%(board-1);
//    pos_x = 3;
//    pos_y = 4;
    step = 0;
    next_x = 0;
    next_y = 0;
    for(int j=0;j<board*board;++j)
    {
        vector<int> temp;
        v_wrong.push_back(temp);
    }
//    recall = false;

}

void Knight::Step()
{
    int next_step[8] = {0,0,0,0,0,0,0,0};
    a[pos_x][pos_y] = true;
    path[0][0] = pos_x;
    path[0][1] = pos_y;
    int wrong_index[board*board][8];
    for(int j=0;j<board*board;++j)
        for(int k=0;k<8;++k)
            wrong_index[j][k] = 10;     //初始化成一个非0~8的数

        beginning:
        int able_num = 0;
        for(int j=0;j<8;++j)
        {
            next_x = pos_x + move_x[j];
            next_y = pos_y + move_y[j];
            if (!(next_x > board - 1 || next_x < 0 || next_y > board - 1 || next_y < 0 ||
                  (a[next_x][next_y] == true)))  //符合条件
                able_num = calculate();
            else
                able_num = 10000;  //不考虑
            next_step[j] = able_num ;

        }

        if(!(v_wrong[step].empty()))
        {
            for(int j=0;j<v_wrong[step].size(); ++j)
            {
                next_step[v_wrong[step][j]] = 10000;
            }
        }
        bool flag=true;

        if(step == board*board-2)
            for(int k=0; k<8; ++k) flag = flag&((next_step[k]==10000));
        else
            for(int k=0; k<8; ++k) flag = flag&((next_step[k]==10000)||(next_step[k]==0));

        if(flag)    //无路可走，回跳上一步
        {
            a[pos_x][pos_y] = false;
            way[step + 1] = 0;            //第step位置清零
            step--;
            pos_x = path[step][0];      //上个位置x坐标
            pos_y = path[step][1];      //上个位置y坐标
            cout << step << " {" << pos_x << ',' << pos_y << "}  "<< endl ;

            v_wrong[step].push_back(way[step]);



//            cout <<way[step];
            goto beginning;
        }

        sort(next_step);

        for(int _i=0; _i<8; ++_i)
        {
            i = next_step[_i];

            next_x = pos_x + move_x[i];
            next_y = pos_y + move_y[i];
            if (next_x > board - 1 || next_x < 0 || next_y > board - 1 || next_y < 0 ||
                (a[next_x][next_y] == true)) //是否出界or已经走过
                continue;

            way[step] = i;      //用的第i种跳法；
            step++;             //step 从1开始
            pos_x = next_x;
            path[step][0] = pos_x;
            next_x = 0;         //更新pos_x坐标，并清零临时存放变量

            pos_y = next_y;
            path[step][1] = pos_y;
            next_y = 0;         //更新pos_y坐标，并清零临时存放变量

            a[pos_x][pos_y] = true;        //taken





//            cout << "step" << step << "{" << path[step][0] << "," << path[step][1] << "}" << endl;
            if (step == board*board-1)
                break;
            goto beginning;
        }

}


void Knight::sort(int * next_step )         //next_step 按数值从小到大排序
{
    int tmp = 0;
    int label[8] = {0,1,2,3,4,5,6,7};
    for(int j=0;j<7;++j)
        for(int i=0;i<7;++i)
            if(next_step[i]>next_step[i+1])
            {
                tmp = next_step[i+1];
                next_step[i+1] = next_step[i];
                next_step[i] = tmp;
                tmp = label[i+1];
                label[i+1] = label[i];
                label[i] = tmp;
            }
    for(int i=0;i<8;++i)
        next_step[i] = label[i];
}

void Knight::show()
{
    cout << "Success!" << endl;
    for(int step=0; step< board*board;step++)
        cout << "step" << step << ":{" << path[step][0] << "," << path[step][1] << "}" << endl;
}

int Knight::calculate()  //下一步可以走多少步
{
    int num = 0;
    int nexter_x = 0;
    int nexter_y = 0;
    for(int j=0;j<board;++j)
    {
        nexter_x = next_x + move_x[j];
        nexter_y = next_y + move_y[j];
        if (nexter_x > board-1 || nexter_x < 0 || nexter_y > board-1 || nexter_y < 0 || (a[nexter_x][nexter_y] == true))
            continue;
        else num+=1;
    }

    return num;
}

int main() {
    srand(time(NULL));
    Knight kim;
    kim.Step();
    kim.show();
    return 0;
}