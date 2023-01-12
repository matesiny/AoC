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

// ukázka: 5x5, real 99x99

int main()
{
    string tp;
    fstream calor;

    const int polestrobux = 99, polestromuy = 99;

    int stromy[polestrobux][polestromuy];
    int x = polestrobux, y = polestromuy;

    int Xmax = x, Ymax = y;
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


    int pocethidden = 0, schovany, j;
    for (x = 1; x < Xmax-1; x++)//part 1
    {
        for (y = 1; y < Ymax - 1; y++) // projiždí všechny stromy uvnitø
        {
            schovany = 0;
            for (j = 0; j < x; j++)
            {
                if ((stromy[j][y] >= stromy[x][y]))
                {
                    schovany++;
                    break;
                }
            }

            for (j = x + 1; j < Xmax; j++)
            {
                if ((stromy[j][y] >= stromy[x][y]))
                {
                    schovany++;
                    break;
                }
            }

            for (j = 0; j < y; j++)
            {
                if ((stromy[x][j] >= stromy[x][y]))
                {
                    schovany++;
                    break;
                }
            }

            for (j = y+1; j < Ymax; j++)
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


    int scene = 1, mostbeautiful = 0, sceneriecelkem, a, b;
    bool odecist;
    for (x = 0; x < Xmax; x++)//part2
    {
        for (y = 0; y < Ymax; y++) 
        {
            sceneriecelkem = 1;
            for (j = x-1, scene = 1, odecist = true; j >= 0; j--, scene++)
            {
                if (stromy[j][y] >= stromy[x][y])
                {
                    odecist = false;
                    break;
                }
            }
            if (odecist) scene--;
            sceneriecelkem *= scene;
                

            for (j = x+1, scene = 1, odecist = true; j < Xmax; j++, scene++)
            {
                if (stromy[j][y] >= stromy[x][y])
                {
                    odecist = false;
                    break;
                }
            }
            if (odecist) scene--;
            sceneriecelkem *= scene;

            for (j = y-1, scene = 1, odecist = true; j >= 0; j--, scene++)
            {
                if (stromy[x][j] >= stromy[x][y])
                {
                    odecist = false;
                    break;
                }
            }
            if (odecist) scene--;
            sceneriecelkem *= scene;

            for (j = y+1, scene = 1, odecist = true; j < Ymax; j++, scene++)
            {
                if (stromy[x][j] >= stromy[x][y])
                {
                    odecist = false;
                    break;
                }
            }
            if (odecist) scene--;
            sceneriecelkem *= scene;


            if (sceneriecelkem > mostbeautiful)
            {
                mostbeautiful = sceneriecelkem;
                a = x, b = y;
            }
        }
    }


    cout << "part 1: " << endl << " pocet viditelnych stromu: " << Xmax * Ymax - pocethidden << endl;

    cout << endl << "part 2: " << endl << " nejlepsi strom: " << mostbeautiful << " souradnice x:" << a << " y:"<< b << endl;
}

