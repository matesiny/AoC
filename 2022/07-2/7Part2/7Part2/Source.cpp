#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class file
{
public:
    unsigned long size;
    int count;
    int SubfoldersIDs[11];

    file()
    {
        size = 0;
        count = 0;
        for (int i = 0; i < 11; i++)
        {
            SubfoldersIDs[i] = NULL;
        }
    }

    void PridatSlozku(int a)
    {
        SubfoldersIDs[this->count] = a;
        count++;
    }
};

/*
$ cd /
$ ls
dir a
14848514 b.txt
8504156 c.dat
dir d
$ cd a
$ ls
dir e
29116 f
2557 g
62596 h.lst
$ cd e
$ ls
584 i
$ cd ..
$ cd ..
$ cd d
$ ls
4060174 j
8033020 d.log
5626152 d.ext
7214296 k*/

file slozky[200];

int prevest(string tp)
{
    int j = 0, vypocteno = 0;
    char c;

    for (int i = 0; tp[i] != ' '; i++)
    {
        j = i;
    }

    for (int i = 0; tp[i] != ' '; i++, j--)
    {
        char c = tp[i];

        vypocteno += (c - 48) * pow(10, j);
    }
    return vypocteno;
}

string jmeno(string tp, int a)
{
    string jmen = " ";
    jmen= tp[4 + a];
    for (int i = 5 + a; tp[i] != '\0'; i++)
    {
        jmen += tp[i];
    }
    return jmen;
}

int main()
{
    string identification[200];
    identification[0] = "/";
    fstream slozka;
    slozka.open("FileSystem.txt", ios::in); //open a file to perform read operation using file object
    int id = 1, ID = 0;

    if (slozka.is_open()) {   //checking whether the file is open
        string tp;

        getline(slozka, tp); // protože první je unikátní($ cd / a '/' nikde neni
        while (getline(slozka, tp)) //read data from file object and put it into string.
        {
            if (tp[0] == '$')
            {
                if (tp[2] == 'c' && tp[5] != '.')
                {
                    for (int i = 1; i < 200; i++)
                    {
                        string name = jmeno(tp, 1);
                        if (identification[i] == name) ID = i;
                    }

                }
                if (tp[2] == 'c' && tp[5] != '.') // otevírá se další složka
                {

                }
            }
            else
            {
                if (tp[0] == 'd')//když je to directory
                {
                    slozky[ID].PridatSlozku((id));
                    identification[id] = jmeno(tp, 0);
                    id++;
                }
                else //když je to soubor
                {

                    slozky[ID].size += prevest(tp);

                    // cout << slozky[id].size << endl;
                }
            }

        }
        slozka.close();
    }
    id--;

    int celkemslozka = 0;
    for (int i = id; i >= 0; i--)
    {
        celkemslozka = 0;

        cout << "id: "  << i  << " jmenen " << identification[i] << " podslozky: ";

        celkemslozka += slozky[i].size;

        for (int j = 0; j < 11; j++)
        {
            if (slozky[i].SubfoldersIDs[j] != 0)
            {
                ID = slozky[i].SubfoldersIDs[j];
                cout << ID << " ";
                celkemslozka += slozky[ID].size;
            }
        }

        slozky[i].size = celkemslozka;
        cout << " velikost: " << celkemslozka << endl;
    }

    //celkem = 70000000, needed = 30000000
    int c = 70000000, b, misto = 70000000 - slozky[0].size;

    for (int i = 0; i <= id; i++)
    {
        b = slozky[i].size;
        if (misto + b >= 30000000 && b < c)
        {
            c = b;
            ID = i;
        }
    }

    cout << endl << " smazat slozku: " << ID << " jmenen " << identification[ID] << " velikosti: " << slozky[ID].size << endl;


}