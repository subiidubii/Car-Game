#include<iostream>
#include<time.h> //random rand k liye 
#include<windows.h> //game slow krny k liye
#include<conio.h> //getch() and khbit k liye
#include <fstream>
#define SCREEN_WIDTH 95
#define SCREEN_HEIGHT 30
#define WIN_WIDTH 70

using namespace std;
//global variable declaration
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyX[3];
int enemyY[3];
int enemyFlag[3];

char car[4][4] = { ' ', '#', '#', ' ',
    '#', '#', '#', '#',
    ' ', '#', '#', ' ',
    '#', '#', '#', '#' };   
int carPos = WIN_WIDTH/2;//window k center main hogi
int score = 0;          
void gotoxy(int x,int y){
   CursorPosition.X = x;
   CursorPosition.Y=y;
   SetConsoleCursorPosition(console,CursorPosition);
}


void drawBorder(){
   for(int i =0;i<SCREEN_HEIGHT;i++){
      for(int j=0;j<17;j++){
         gotoxy(0+j,i);cout<<"|";
         gotoxy(WIN_WIDTH-j,i);cout<<"|";
      }
   }
     for(int i=0; i<SCREEN_HEIGHT; i++){  
        gotoxy(SCREEN_WIDTH,i); cout<<"|";  
    }
}

void updateScore(){
    
   int highScore = 0;
   ifstream file("scores.txt");
   if(file.is_open()){
    file>>highScore;
    file.close();
   }
   gotoxy(WIN_WIDTH+7,5);cout<<"Score: "<<score<<endl;
   if (score > highScore) {
        highScore = score;//file main score input krny k liye
        ofstream file("scores.txt"); 
        file << highScore;
        file.close();
   }
}

void genEnemy(int pos){
   enemyX[pos] = 17 + rand()%(33);//enemy kisi bhi random place main generate hojai ga
}

void drawCar(){
   for(int i=0;i<4;i++){// 4 is liye cause indexing 4x4 ki di ha
      for(int j=0;j<4;j++){
         gotoxy(j+carPos,i+22);cout<<car[i][j];
      }
   }
}

void drawEnemy(int pos){
   if(enemyFlag[pos]==true){
     gotoxy(enemyX[pos], enemyY[pos]);   cout<<"****";    
        gotoxy(enemyX[pos], enemyY[pos]+1); cout<<" ** ";   
        gotoxy(enemyX[pos], enemyY[pos]+2); cout<<"****";   
        gotoxy(enemyX[pos], enemyY[pos]+3); cout<<" ** ";     
   }
}
int collision(){
   if( enemyY[0]+4 >= 23 ){  
        if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){  
            return 1;  
        }  
    } 
     return 0; 
} 
   void gameover() {  
    system("cls");  
    cout<<endl;  
    cout<<"\t\t--------------------------"<<endl;  
    cout<<"\t\t-------- Game Over -------"<<endl; 

cout<<"\t\t--------------------------"<<endl<<endl;  
    cout<<"\t\tPress any key to go back to menu.";  
    getch(); 
} 
void eraseCar(){  
    for(int i=0; i<4; i++){  
        for(int j=0; j<4; j++){  
            gotoxy(j+carPos, i+22); cout<<" ";  
        }  
    }  
}  
void eraseEnemy(int pos){  
    if( enemyFlag[pos] == true ){  
        gotoxy(enemyX[pos], enemyY[pos]); cout<<"    ";    
        gotoxy(enemyX[pos], enemyY[pos]+1); cout<<"    ";   
        gotoxy(enemyX[pos], enemyY[pos]+2); cout<<"    ";   
        gotoxy(enemyX[pos], enemyY[pos]+3); cout<<"    ";
    }
} 
void resetEnemy(int pos){  
    eraseEnemy(pos);  
    enemyY[pos] = 1;  
    genEnemy(pos);  
} 



   




void play(){
   carPos=-1+WIN_WIDTH/2;//car middle main hogi
   score = 0;
   enemyFlag[0]= 1;
   enemyFlag[1]= 0;// for apperanace and disapperance of enemy
   enemyY[0] = enemyY[1] = 1;

   system ("cls");
   drawBorder();
   updateScore();
   genEnemy(0);
   genEnemy(1);
   
       gotoxy(WIN_WIDTH + 7, 2);cout<<"Car Game";  
    gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";  
    gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";  
    gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";  
    gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";  
    gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";  
    gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right";   
    gotoxy(18,5);cout<<"Press any key to start";
    getch();
    gotoxy(18, 5);cout<<"                      "; 

    while(true){
      //basically kbhit A or D ko move karny k liye use ho rha
      if(kbhit()){
         char ch = getch();
   if(ch=='a'|| ch=='A'){
      if(carPos>18)//18 sa is liye bara hona chayie qka left wall 18 pr ha
         carPos -= 4;

   }
   if( ch=='d'|| ch=='d'){
      if(carPos<50)
      carPos+=4;
   }
if(ch==27){
   //ascii code for esc
   break;
}
      }
     
drawCar();//functions written below
drawEnemy(0);
drawEnemy(1);

if(collision()==1){
   gameover();
   return;
}
Sleep(50);
eraseCar();
eraseEnemy(0);
eraseEnemy(1);
//if condition for the movement of the enemy
if( enemyY[0] == 10 )  //enemy [0] means first enemy agar wo 10 indexing k equal hojai tu enemy disappear ho jai ga
            if( enemyFlag[1] == 0 )//enemy [1] enemy 1 appear hojai ga
                enemyFlag[1] = 1; 
				
        if( enemyFlag[0] == 1 )  // ye if condition enemy k move krny k liye like enemy[0] 1 indexing k sath move hota rhy ga
            enemyY[0] += 1;  
			
        if( enemyFlag[1] == 1 )  
            enemyY[1] += 1;
			
        if( enemyY[0] > SCREEN_HEIGHT-4 ){  
            resetEnemy(0);  //ye if condition is liye cause if enemy screen sa disapper hoga tu score update hoga
            score++;  
            updateScore(); 
        }       
        if( enemyY[1] > SCREEN_HEIGHT-4 ){  
            resetEnemy(1);  
            score++;  
            updateScore();  
        } 

    }
}
void setcursor(bool visible, DWORD size) {  
//cursor ki postioning k liye
    if(size == 0)  
        size = 20; 
    CONSOLE_CURSOR_INFO lpCursor;     
    lpCursor.bVisible = visible;  
    lpCursor.dwSize = size;  
    SetConsoleCursorInfo(console,&lpCursor);  
}  
void saveScore(string playerName){ //first neechy kia tha tu uninitialize hogya tha
    fstream file("scores.txt", ios::in | ios::out | ios::app);//yahan par ham file creae krky usmain score ko store kara rhy
    if(file.is_open()){
        file << playerName << " " << score << endl;
        file.close();
    } else {
        cout << "Error opening score file!" << endl;
    }
}
void loadScores(){
    system("cls");
    fstream file("scores.txt", ios::in);
    string name;
    int sc;
    if(file.is_open()){
        cout << "\nHigh Scores:\n";
        while(file >> name >> sc){
            cout << name << " : " << sc << endl;
        }
        file.close();
    } else {
        cout << "No high scores yet!" << endl;
    }
    cout << "\nPress any key to return to menu.";
    getch();
}
int main()
{//how to clear the screen in vs code
gotoxy(0,0);
srand((unsigned)time(NULL));//random entity generate hogi
string playerName;
do{//cause game main infinity loop chlty hain
system("cls");
//gotoxy basically system ko quadrinates assign kr rha ha ka yahan jana ha 
gotoxy(10,5);cout<<"---------------------------------------------------";
gotoxy(10,6);cout<<"|          CP PROJECT                             |";
gotoxy(10,7);cout<<"---------------------------------------------------";
system("cls");
//for menu
gotoxy(10,9); cout<<"1. Start Game";
gotoxy(10,10);cout<<"2. High Scores";
gotoxy(10,11);cout<<"3. Quit";
system("cls");
gotoxy(10,13);cout<< "Enter name: ";
cin>>playerName;
gotoxy(10,15); cout<<"Select option: ";  
        
char op=getche();//The getche() function obtains the next available keystroke from the console

if(op=='1') play();
else if (op=='2')loadScores();
else if(op=='3') exit(0);

}while(true);

   return 0; 
}