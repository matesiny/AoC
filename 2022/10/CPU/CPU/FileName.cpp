#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int aBS(int a)
{
    if (a < 0)
    {
        return a * -1;
    }
    return a;
}

bool checkClock(int cycle)
{
    for (int i = 0; ((i * 40) + 20) < 221; i++)
    {
        if (cycle == ((i * 40) + 20))
        {
            return true;
        }
    }
    return false;
}

int pow(int power)
{
    int a = 1;
    if (power == 0)
    {
        return a;
    }

    for (int i = 0; i < power; i++)
    {
        a *= 10;
    }
    return a;
}

int getNumber(string tp)
{
    int i, num = 0, j;
    bool negative = false;
    for (i = 0; tp[i] != ' '; i++);

    i++;
    if (tp[i] == '-') { negative = true; i++; }//raise i so that later there is only the numbers (not '-')

    for (j = 0; tp[j + i] != '\0'; j++);

    for (int k = 0; k < j; k++)
    {
        num += (tp[k+i] - 48) * pow((j-k-1));
    }

    if (negative)
    {
        return  (num * (-1));
    }
    else
    {
        return num; 
    }
}

void printCRT(int cycle, int X)
{
    cycle--;
    if (cycle % 40 == 0)
    {
        cout << endl;
    }

    if (aBS((cycle % 40) - X) < 2)
    {
        cout << "#";
    }
    else
    {
        cout << ".";
    }
}

int main()
{
    int cycle = 1;//starting cycle
    int X = 1, whole = 0; // starting value for register X
    bool regX = false, executing = false, executingX = false;

    fstream RPS;
    RPS.open("Input.txt", ios::in); //open a file to perform read operation using file object
    if (RPS.is_open()) {   //checking whether the file is open
        string tp;
        while (getline(RPS, tp))
        {
            switch (tp[0])
            {
            case('a'): regX = true, executing = true; break;
            case('n'):
                {
                    printCRT(cycle, X);
                    cycle++;
                    if (checkClock(cycle))
                        { whole += cycle * X; }
                    break;
                }
            default: break;
            }

            while (executing)
            {
                printCRT(cycle, X);

                cycle++;

                if (executingX) //has to be first to take an extra cycle
                { 
                    X += getNumber(tp);
                    executing = false; 
                    executingX = false;
                }

                if (regX) 
                { 
                    executingX = true; 
                }

                regX = false;// set false to prevent an endless loop

                if (checkClock(cycle)) 
                { 
                    whole += cycle * X; 
                }


            }

        }
        RPS.close();
    }
    cout << endl << whole;
}
