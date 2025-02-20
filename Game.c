#include <stdio.h>
#include <stdlib.h> /*to yse system function*/
#include <termios.h> /* to change the properties of the console*/
#include <unistd.h>
#include <time.h> /* to have the random function*/

/* to make the pitch*/
#define HEIGHT 20
#define WIDTH 60

/* prototyping */
void clear_screen(); /*to clear the console*/
struct termios old_props;
void set_terminal(); /* to ste the attributes of the terminal*/
void reset(); /* to reset the terminal to its default state*/
void draw();
void assign();
int input();
void move();
void take_input();

/* possible directions*/
enum Arrow
{Up, Down, Left, Right, Stop};
enum Arrow direction;

/* all the intezers */
int a = 0;
int x_O, y_O;
int x_matha, y_matha;
int tail;
int tail_location_x[3267];
int tail_location_y[3267];

/* Execution */
int main()
{
    srand(time(NULL)); /* randomizes the locatuion of the fruit */
    set_terminal();
    assign(); // this will assign value to the intezers at the start
    while(1)
    {
     draw();
     take_input();
     move();
     int sleep = 300000/(a!=0 ? a:10);
     usleep (sleep);
    }
}

/* checks the teminal whether the input can be done by the keyboard*/
/* cpoy pasted from youtube */
int input()
{
  struct timeval tv = { 0L, 0L };
  fd_set fds;
  FD_SET(0, &fds);
  return select(1, &fds, NULL, NULL, &tv);
}

void take_input()
{
 if (input())
 {
    cahr c = getchar();
    switch (c)
    {
        case 'w':
            direction= Up;
            break;
        case 's':
            direction = Down;
            break;
        case 'a':
            direction = Left;
            break;
        case 'd':
            direction = Right;
            break;
        case 'q':
            exit (0);
            break;
    }
 }
}
/* draws the screen */
void draw()
{
    clear_screen();
    printf ("\t Let's start\n");

    for (int i=0;i<WIDTH+2; i++) /* it will print the horizontal boundary*/
       printf ("=");
       printf("\n");
        
    for (int i=0;i<HEIGHT+2; i++)/* it will print the vertical boundary*/
    { 
        printf("\n||");
        for (int j=0;j<WIDTH+2; j++) /* it will print the grid*/
       {
            if (i == y_matha && j == x_matha)
            printf("M"); 
            if (i == y_O && j == x_O)
            printf("<$>");
           else
         { 
              int got = 0;
               for( int h = 0; h<tail; h++)
            {
               if (tail_location_x[h] == j && tail_location_y[h] == i)
              printf ("~");
               got =1;
               break;
            }
               if (!got)
                printf(" ");
         }
        }
       printf("||\n");
    }


    for (int i=0;i<WIDTH+2; i++) /* it will print the horizontal boundary*/
    printf ("=");  
    printf("\n");

       printf("\nPOINTS- %d",a);
}

void assign()
{
    /* the should start from the middle of the board */
    x_matha = WIDTH/2;
    y_matha = HEIGHT/2;
    x_O = rand()% WIDTH; /* random number between 0 to horizontal length*/
    y_O = rand()% HEIGHT; /* random number between 0 to vertical length*/
    direction = Stop;
    tail = 0;
    a=0;
}    

/*main logic of the game*/
void move()
{
    int x = x_matha, y = y_matha;
    int x1, y1;
    for (int i = tail-1; i>1; i--)
    {
        tail_location_x[i] = tail_location_x[i-1];
        tail_location_y[i] = tail_location_y[i-1];
    }
tail_location_x[0] = x_matha;
tail_location_y[0] = y_matha;

 switch (direction)
 {
    case Up:
    y_matha--;
    break;
    case Down:
    y_matha++;
    break;
    case Left:
    x_matha--;
    break;
    case Right:
    x_matha++;
    break;
    case Stop:/* stops automatically */
    break;
 }
 /* to continue through the walls*/
  if (x_matha<0)
  x_matha= WIDTH-1;
 
  else if ( x_matha>= WIDTH)
  x_matha = 0;

  if (y_matha<0)
  y_matha = HEIGHT-1;

  else if (y_matha>= HEIGHT)
  y_matha=0;

  /* if collided with the tail */
for (int i = 0; i<tail; i++)
{
    if (x_matha == tail_location_x[i] && y_matha == tail_location_y[i])
    {
        printf("Game Done\n");
    
    exit (0);
    }
}
 
/*grabed the fruit*/
  if (x_matha== x_O && y_matha==y_O)
  {
  a = a + 9;
  tail ++;
  x_O= rand ()% WIDTH;
  y_O = rand ()% HEIGHT;
  }
}

void set_terminal()
{

    tcgetattr(STDIN_FILENO, &old_props);
    atexit(reset); /* calls restet automatically */
    struct termios new_props = old_props;
    new_props.c_lflag= ~(ECHO | ICANON); /* Echo shows the input, Icanon give the input to the terminal, here we turned off both*/
    tcsetattr(STDIN_FILENO, TCSANOW, &new_props);
}

void reset()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &old_props);
}

void clear_screen()
{
 #ifdef _Win32
 system("cls"); /*for wondows*/
 #else
 system( "clear" ); /*for unix/linux/mac*/
 #endif
}
