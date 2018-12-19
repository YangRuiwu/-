
#include <windows.h>

#include <stdlib.h>

#include <conio.h>

#include <time.h>

#include <cstring>

#include <cstdio>

#include <iostream>

#define  N 22

using namespace std;

 

    int gameover;

 

    int x1, y1; // Random food

 

    int x,y;

 

    long start;

 

//=======================================

//initialize

//=======================================

 

//The following defines the coordinate class of Snake

class snake_position

{

public:

 

    int x,y;      //x represents the line, y represents the column

 

    snake_position(){};

 

    void initialize(int &);//Coordinate initialization

 

 

};

 

snake_position position[(N-2)*(N-2)+1]; //Define an array of Snake coordinate classes with (N-2)*(N-2) coordinates

 

void snake_position::initialize(int &j)

{

        x = 1;

 

        y = j;

}

 

 

//The following defines the chessboard chart of the Snake

 

class snake_map

{

 

private:

 

    char s[N][N];//Define a snake board, including walls.

 

    int grade, length;

 

    int gamespeed; //Forward time interval

 

    char direction; // In the initial case, move to the right

 

    int head,tail;

 

    int score;

 

    bool gameauto;

 

public:

 

    snake_map(int h=4,int t=1,int l=4,char d=77,int s=0):length(l),direction(d),head(h),tail(t),score(s){}

 

    void initialize();   //Initialization function

 

    void show_game();

 

    int updata_game();

 

    void setpoint();

 

    void getgrade();

 

    void display();

 

 

};

 

//Define an initialization function that initializes the snake board map

 

void snake_map::initialize()

{

    int i,j;

 

    for(i=1;i<=3;i++)

 

        s[1][i] = '*';

 

    s[1][4] = '#';

 

    for(i=1;i<=N-2;i++)

 

        for(j=1;j<=N-2;j++)

 

            s[i][j]=' '; //Initialize the blank part of the Snake board

 

    for(i=0;i<=N-1;i++)

 

        s[0][i] = s[N-1][i] = '-'; //Initialize the snake snake board up and down the wall

 

    for(i=1;i<=N-2;i++)

 

        s[i][0] = s[i][N-1] = '|'; //Initialize the snake snake board left and right walls

}

 

 

//============================================

//Output Snake Board Information

 

void snake_map::show_game()

 

{

 

    system("cls"); // Clear screen

 

    int i,j;

 

    cout << endl;

 

    for(i=0;i<N;i++)

    {

 

        cout << '\t';

 

        for(j=0;j<N;j++)

 

            cout<<s[i][j]<<' '; // Output Snake Board

 

        if(i==2) cout << "\tLevel£º" << grade;

 

        if(i==6) cout << "\tSpeed£º" << gamespeed;

 

        if(i==10) cout << "\tScore£º" << score << "point" ;

 

        if(i==14) cout << "\tPause: Press the spacebar" ;

 

        if(i==18) cout << "\tContinue: press the space bar twice" ;

 

        cout<<endl;

    }

}

 

//Input selection level

void snake_map::getgrade()

{

    cin>>grade;

 

    while( grade>7 || grade<1 )

    {

        cout << "Please enter the number 1-7 to select the level, enter the other number is invalid" << endl;

 

        cin >> grade;

    }

    switch(grade)

    {

        case 1: gamespeed = 1000;gameauto = 0;break;

 

        case 2: gamespeed = 800;gameauto = 0;break;

 

        case 3: gamespeed = 600;gameauto = 0;break;

 

        case 4: gamespeed = 400;gameauto = 0;break;

 

        case 5: gamespeed = 200;gameauto = 0;break;

 

        case 6: gamespeed = 100;gameauto = 0;break;

 

        case 7: grade = 1;gamespeed = 1000;gameauto = 1;break;

 

    }

 

}

 

//Output level, score status and title

 

void snake_map::display()

{

 

    cout << "\n\t\t\t\tLevel£º" << grade;

 

    cout << "\n\n\n\t\t\t\tSpeed£º" << gamespeed;

 

    cout << "\n\n\n\t\t\t\tScore£º" << score << "point" ;

 

}

 

//Randomly produced Food

void snake_map::setpoint()

{

    srand(time(0));

 

    do

    {

 

        x1 = rand() % (N-2) + 1;

 

        y1 = rand() % (N-2) + 1;

 

    }while(s[x1][y1]!=' ');

 

    s[x1][y1]='*';

}

 

char key;

 

int snake_map::updata_game()

{

    gameover = 1;

 

    key = direction;

 

    start = clock();

 

    while((gameover=(clock()-start<=gamespeed))&&!kbhit());

 

    //Terminates the loop if there is a key press or the time exceeds the automatic forward time interval

 

 

 

        if(gameover)

        {

 

            getch();

 

            key = getch();

        }

 

        if(key == ' ')

 

        {

            while(getch()!=' '){};//The implementation here is to press the space bar to pause, press the space bar to continue, but for some reason, you need to press two spaces to continue. This is a bug.

        }

 

        else

 

            direction = key;

 

        switch(direction)

        {

            case 72: x= position[head].x-1; y= position[head].y;break; // up

 

            case 80: x= position[head].x+1; y= position[head].y;break; // down

 

            case 75: x= position[head].x; y= position[head].y-1;break; // left

 

            case 77: x= position[head].x; y= position[head].y+1; // right

 

        }

 

        if(!(direction==72||direction==80||direction==75 ||direction==77))   // Button non-directional button

 

            gameover = 0;

 

        else if(x==0 || x==N-1 ||y==0 || y==N-1)   // Hit the wall

 

            gameover = 0;

 

        else if(s[x][y]!=' '&&!(x==x1&&y==y1))    // Snake head hits the snake body

 

            gameover = 0;

 

        else if(x==x1 && y==y1)

 

        { // Eat Food, length plus 1

 

            length ++;

 

            if(length>=8 && gameauto)

 

            {

 

                length -= 8;

 

                grade ++;

 

                if(gamespeed>=200)

 

                    gamespeed -= 200; // Change the speed of snakes

 

                else

 

                    gamespeed = 100;

 

            }

 

            s[x][y]= '#';  //Update snake head

 

            s[position[head].x][position[head].y] = '*'; //After eating rice, turn the original snake head into a snake body.

 

            head = (head+1) % ( (N-2)*(N-2) );   //Snake head coordinates

 

            position[head].x = x;

 

            position[head].y = y;

 

            show_game();

 

            gameover = 1;

 

            score += grade*20;  //Add points

 

            setpoint();   //make food

 

        }

 

        else

        { // dont eat food

 

            s[position[tail].x][position[tail].y]=' ';//Empty the snake tail

 

            tail= (tail+1) % ( (N-2) * (N-2) );//Update snake tail coordinates

 

            s[position[head].x][position[head].y]='*';  //Make the snake head to snake body

 

            head= (head+1) % ( (N-2) * (N-2) );

 

            position[head].x = x;

 

            position[head].y = y;

 

            s[position[head].x][position[head].y]='#'; //Update snake head

 

            gameover = 1;

 

        }

    return gameover;

 

}

//====================================

//the main function

//====================================

int main()

{

    char ctn = 'y';

 

    int nodead;

 

    cout<<"\n\n\n\n\n\t\t\t Welcome to the game about Snake!"<<endl;//Welcome ;

 

    cout<<"\n\n\n\t\t\t Press any key to start¡£¡£¡£"<<endl;//ready to stat;;

 

    getch();

 

    while( ctn=='y' )

    {

        system("cls"); // delete screen

 

        snake_map snake;

 

        snake.initialize();

 

        cout << "\n\nPlease enter a number to select the game level£º" << endl;

 

        cout << "\n\n\n\t\t\t1.Level one£ºSpeed 1000 \n\n\t\t\t2.Level two£ºSpeed 800 \n\n\t\t\t3.Level three£ºSpeed 600 ";

 

        cout << "\n\n\t\t\t4.Level fore£ºSpeed 400 \n\n\t\t\t5.Level five£ºSpeed 200 \n\n\t\t\t6.Level six£ºSpeed 100 \n\n\t\t\t7.Infinite mode" << endl;

 

        snake.getgrade();//Get rating

 

        for(int i=1;i<=4;i++)

        {

            position[i].initialize(i);//Initialization coordinates

        }

 

        snake.setpoint();  // Produce the first Food

 

        do

        {

            snake.show_game();

 

            nodead = snake.updata_game();

 

        }while(nodead);

 

        system("cls"); //delete screen

 

 

 

        cout << "\n\n\n\t\t\t\tGameover£¡\n\n"<<endl;

 

        snake.display();//Output level/score situation

 

        cout << "\n\n\n\t\t    Do you choose to continue the game? Enter y to continue, n to exit" << endl;

 

        cin >> ctn;

 

    }

 

    return 0;

}

