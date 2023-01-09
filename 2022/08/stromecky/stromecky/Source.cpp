#include<iostream>
#include<fstream>
#include <string>

/*
30373
25512
65332
33549
35390
*/

using namespace std;

int main()
{
    string tp;
    fstream calor;
    int x = 1, y = 0;
    calor.open("stromky.txt", ios::in);
    if (calor.is_open()) {  
        for (; getline(calor, tp); x++);
        calor.close();
        for (; tp[y] != '\0'; y++);
        y++;
    }
    x--, y--;
    int Xmax = x, Ymax = y;

    int** stromy = new int*[x];
    for (int i = 0; i < x; i++)
    {
        stromy[i] = new int[y];
    }

    y = 0;
    calor.open("stromky.txt", ios::in);
    if (calor.is_open()) {
        while (getline(calor, tp))
        {
            for (x = 0; tp[x] != '\0'; x++)
            {
                stromy[y][x] = (tp[x] - 48);
            }
            y++;
        }
    }
    calor.close();

    /*
    for (x = 0; x < Xmax; x++)
    {
        for (y = 0; y < Ymax; y++)
        {
            cout << stromy[x][y];
        }
        cout << endl;
    }
    cout << endl;*/

    int pocethidden = 0, schovany;

    for (x = 1; x < Xmax-1; x++)
    {
        for (y = 1; y < Ymax - 1; y++) // projiždí všechny stromy uvnitø
        {
            schovany = 0;
            for (int j = 0; j < x; j++)
            {
                if ((stromy[j][y] >= stromy[x][y]))
                {
                    schovany++;
                    break;
                }
            }

            for (int j = x + 1; j < Xmax; j++)
            {
                if ((stromy[j][y] >= stromy[x][y]))
                {
                    schovany++;
                    break;
                }
            }

            for (int j = 0; j < y; j++)
            {
                if ((stromy[x][j] >= stromy[x][y]))
                {
                    schovany++;
                    break;
                }
            }

            for (int j = y+1; j < Ymax; j++)
            {
                if (stromy[x][j] >= stromy[x][y])
                {
                    schovany++;
                    break;
                }
            }

            if (schovany == 4) pocethidden++;
        }
    }

    cout << "part 1: " << endl << " pocet viditelnych stromu: " << Xmax * Ymax - pocethidden << endl;
}

