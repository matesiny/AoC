#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int aBS(int a)
{
    if (a < 0)
    {
        a = -a;
    }
    return a;
}

struct Knot{
    int X; // souradnice X uzlu
    int Y; // souradnice Y uzlu
    Knot* next; // adresa dalšího uzlu
};

Knot* createKnot(int x, int y)
{
    Knot* knot = new Knot();
    knot->X = x;
    knot->Y = y;
    knot->next = NULL;
    return knot;
}

void addKnot(Knot* rope, Knot* knot) // rope == list
{
    Knot* last = rope;
    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = knot;
}

void moveHead(Knot* knot, int pohyb, bool horizontal, bool negative)
{
    int minus;
    if (negative) 
    { minus = -1; }
    else
    { minus = 1; }

    if (horizontal)
    {
        knot->X += pohyb * minus;
    }
    else
    {
        knot->Y += pohyb * minus;
    }
}

void move(Knot* knot, int pohyb)
{
    switch (pohyb)
    {
    case(1): knot->Y += 1; break;
    case(2): knot->Y += 1; knot->X += 1; break;
    case(3): knot->X += 1; break;
    case(4): knot->Y -= 1; knot->X += 1; break;
    case(5): knot->Y -= 1; break;
    case(6): knot->Y -= 1; knot->X -= 1; break;
    case(7): knot->X -= 1; break;
    case(8): knot->Y += 1; knot->X -= 1; break;
    default: break;
    }
}

int  checkMove(Knot* lead, Knot* follow)
{
    int deltaX, deltaY;

    deltaX = lead->X - follow->X;
    deltaY = lead->Y - follow->Y;

    if (aBS(deltaX) < 2 && aBS(deltaY) < 2)
    {
        return 0;
    }

    if(aBS(deltaX) > 1 || aBS(deltaY) > 1)
    {
        if (deltaX == 0)
        {
            if (deltaY > 0)// vertical
            {
                return 1;//up
            }
            else
            {
                return 5;//down
            }
        }

        if (deltaY == 0)
        {
            if (deltaX > 0)
            {
                return 3;// right
            }
            else
            {
                return 7;//left
            }
        }

        if (deltaX == 1)
        {
            if (deltaY == 2) { return 2; } //right up
            if (deltaY == -2) { return 4; }// right down
        }

        if (deltaX == -1)
        {
            if (deltaY == 2) { return 8; } //left up
            if (deltaY == -2) { return 6; } // left down
        }

        if (deltaY == 1)
        {
            if (deltaX == 2) { return 2; } // right up
            if (deltaX == -2) { return 8; } //left up
        }

        if (deltaY == -1)
        {
            if (deltaX == 2) { return 4; } // right down
            if (deltaX == -2) { return 6; } // left down
        }

        if (deltaX == 2 && deltaY == 2) { return 2; } // right up
        if (deltaX == 2 && deltaY == -2) { return 4; } // right down
        if (deltaX == -2 && deltaY == -2) { return 6; } // left down
        if (deltaX == -2 && deltaY == 2) { return 8; } // left up

    }
    return 0;
}

int prevod(string tp)
{
    int a = 0;

    if (tp[3] == '\0')
    {
        a += (tp[2] - 48);
    }
    else
    {
        a += (tp[3] - 48) + ((tp[2] - 48) * 10);
    }

    return (a);
}

int main()
{
    const int numberOfKnots = 10;//should be larger than 0
    const int stred = 300;// to put the knots in the middle of the field

    bool detection[stred * 2][stred * 2];//we'll see where the rope was

    for (int i = 0, j = 0; i < (stred * 2); i++, j = 0)
    {
        while (j < (stred * 2))
        {
            detection[i][j] = false;
            j++;
        }
    }

    Knot* Head = createKnot(stred, stred);
    Knot* currentknot; // will be used to cycle through the list

    for (int i = 0; i < numberOfKnots - 1; i++)
    {
        addKnot(Head, createKnot(stred, stred));
    }

    bool hor, neg;


    fstream RPS;
    RPS.open("Input.txt", ios::in); //open a file to perform read operation using file object
    if (RPS.is_open()) {   //checking whether the file is open
        string tp;
        while (getline(RPS, tp))
        {
            if (tp[0] == 'U' || tp[0] == 'D') // is it horizontal?
            { hor = false; }
            else
            {  hor = true; }

            if (tp[0] == 'D' || tp[0] == 'L') // will we be subtracting from the possition?
            { neg = true; }
            else
            {  neg = false; }

            for (int i = 0; i < prevod(tp); i++)
            {
                moveHead(Head, 1, hor, neg);//moves the first knot(the head)
                currentknot = Head;

                while (true)//runs through the whole list
                {
                    if (currentknot->next == NULL)  // last knot-> we need to mark it's movement
                    { 
                        detection[currentknot->X][currentknot->Y] = true;
                        break; // resets the movement cycle
                    }

                    move(currentknot->next, checkMove(currentknot, currentknot->next));

                    currentknot = currentknot->next;
                }
            }
        }

        RPS.close();

        int pocet = 0;
        for (int i = 0, j = 0; i < (stred * 2); i++, j = 0)
        {
            while (j < (stred * 2))
            {
                if (detection[i][j])
                {
                    pocet++;
                }
                j++;
            }
        }

        cout << endl <<"Last knot occupied " << pocet << " positions." << endl;

    }
}
