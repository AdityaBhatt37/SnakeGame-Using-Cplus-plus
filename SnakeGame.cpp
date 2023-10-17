#include<iostream>

#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;


void gotoxy(int x,int y){  //Funtion for Curser postion 
        COORD pos;//Is line mein humne COORD namak ek data structure ka object "pos" banaya hai.
        pos.X = x;// Is line mein humne object "pos" ke "X" property ko humne input parameter
                  //"x" se set kiya hai.

        pos.Y = y;// Is line mein humne object "pos" ke "Y" property ko humne input parameter 
                  //"y" se set kiya hai.
                  
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
// Is line mein humne console ki current position ko set karne ke liye 
// "SetConsoleCursorPosition" function ka use kiya hai. Is function mein 
// "GetStdHandle(STD_OUTPUT_HANDLE)" se humne console handle ko liya hai aur "pos" 
// se humne cursor ki position li hai.

}


    

void boundary(){

        cout<<(char)218;
    for (int i = 1; i<79; i++)  //top horizontal line setup
    {
        cout<<(char)196;
    }
    cout<<(char)191; //



    for(int i = 1; i<11; i++){  // left and right vertical lines setup.

         gotoxy(79,i);          // Right vertical line setup.
         cout<<(char)179;

         gotoxy(0,i);           //Left Vertical Line setup.
         cout<<(char)179;
    }
    cout<<"\n"<<(char)192;



    for (int i = 1; i<79; i++)   //Bottom horizontal line setup.
    {
        cout << (char)196;
    }
    cout << (char)217; 
    gotoxy(0, 0);

}



void move(int *x, int *y, char *l, char c, int len)
{
    gotoxy(x[len - 1], y[len - 1]);
    cout << " ";
    for(int i=len; i>0; i--){

         x[i] = x[i-1];
         y[i] = y[i-1];
    }
    *l = c;
    if (len > 1)
    {
        gotoxy(x[1], y[1]);
        cout<<"o";
    }
}


int check(int px, int py, int *x, int *y, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (px == x[i] && py == y[i])
        {
            return 1;
        }
    }
    return 0;
}


void over(int x, int y, int len)
{
    gotoxy(x, y);
    cout<<(char)254;
    gotoxy(1, 1);
    cout<<"Game Over!!!\n";
    cout<<(char)179 <<"Score : "<<len - 1;
    while (getch() != 13);
    exit(0);
}

int main(){

    
     gotoxy(1, 6);

    cout<<"- X --- X --- X --- X --- SNAKES --- X --- X --- X ---\n";
    cout<<(char)179<<"Use arrow keys to move the snake\n"<<(char)179;
    cout<<"Backward movement is not allowed\n"<<(char)179;
    cout<<"Press Enter any time to end the game\n"<<(char)179;
    cout<<"Don't maximize the window\n"<<(char)179;
    cout<<"Press any key to continue"<<(char)179;

    getch();
    system("cls");
    boundary();

     srand(time(NULL));
     int *xS, *yS, px = ((rand() % 9) * 2) + 3, py = (rand() % 10) + 1, len = 1;//for food
       char c, l;
       clock_t t;  //it will help us to move our snake automatic

    xS = (int *)malloc( (len + 1)*sizeof(int) );    
    yS = (int *)malloc( (len + 1)*sizeof(int) );  // for snake body both x and y.
    xS[0] = 3;
    yS[0] = 5;   //for snake position first time 

gotoxy(px, py); 
    cout<<(char)15;

    gotoxy(xS[0], yS[0]);
    cout<<"o";

    while (1)
    {
        do
        {
            t = clock();
            while (clock() < t + 250 && !kbhit());

            if (clock() < t + 250)
            {
                c = getch();
                if (c == 75 && l == 77)
                    c = 77;
                else if (c == 77 && l == 75)
                    c = 75;
                else if (c == 80 && l == 72)
                    c = 72;
                else if (c == 72 && l == 80)
                    c = 80;
            }

            switch (c)
            {
            case 0:
                break;

            case 224:
                break;

            case 80:
                move(xS, yS, &l, c, len);
                gotoxy(xS[0], ++yS[0]);
                cout<<(char)31;

                if (yS[0] == 11)
                    over(xS[0], yS[0], len);
                break;

            case 72:
                move(xS, yS, &l, c, len);
                gotoxy(xS[0], --yS[0]);
                cout<<(char)30;

                if (yS[0] == 0)
                    over(xS[0], yS[0], len);
                break; 

            case 75:
                move(xS, yS, &l, c, len);
                gotoxy(xS[0] = xS[0] - 2, yS[0]);
                cout<<(char)17;

                if (xS[0] == 1)
                    over(xS[0], yS[0], len);
                break;

            case 77:
                move(xS, yS, &l, c, len);
                gotoxy(xS[0] = xS[0] + 2, yS[0]);
                cout<<(char)16;

                if (xS[0] == 79)
                    over(xS[0], yS[0], len);
                break;

            default:
                break;
            }


            for (int i = 4; i < len; i++)
            {
                if (xS[0] == xS[i] && yS[0] == yS[i])
                    over(xS[0], yS[0], len);
            }
        } 
        while (xS[0] != px || yS[0] != py);

        gotoxy(xS[len], yS[len]);
        cout<<"o";
        len++;

        xS = (int *)realloc(xS, sizeof(int) * (len + 1));
        yS = (int *)realloc(yS, sizeof(int) * (len + 1));

        do
        {
            py = (rand() % 10) + 1;
            px = ((rand() % 9) * 2) + 3;
        } while (check(px, py, xS, yS, len));

        gotoxy(px, py);
        cout<<(char)15;
    }

    return 0;
}