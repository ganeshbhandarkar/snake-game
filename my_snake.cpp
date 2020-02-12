#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
enum eDirection{Stop = 0,Left,Right,Up,Down};
int x,y,fruitX,fruitY,score;
eDirection dir;
int tailX[100],tailY[100];
int nTail;

void Setup(){

	gameOver = false;
	dir = Stop;
	x = width/2;
	y = height/2;
	score = 0;
	fruitX = rand() % width;
	fruitY = rand() % height;	
}


void Draw(){
	//Important for flickering windows as on cmd system
        system("cls");
	for(int i=0;i<width+2;i++){
		cout<<"#";
	}
	cout<<endl;

	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if(j==0){
				cout<<"#";
			}
			if(i==y && j== x){ cout<<"O";}
			else if(i==fruitY && j== fruitX){ cout<<"$";}
			else{
				bool print = false;
				for(int k=0;k<nTail;k++){
					if(tailX[k]==j && tailY[k]==i){
		                        	cout<<"o";
						print = true;
					} 	
				}if(!print){
		        		cout<<" ";
				}
			}
			if(j==width-1){
				cout<<"#";
			}

		}
		cout<<endl;
	 }
		
	for(int i=0;i<width+2;i++) cout<< "#";cout<<endl;
	cout<<"SCORES = "<<score<<endl;
}

void Input(){

	if(_kbhit()){
		switch(_getch()){
			case 'a': dir = Left;
			break;
			case 'd': dir = Right;
			break;
			case 'w': dir = Up;
			break;
			case 's': dir = Down;
			break;
			case 'm': gameOver=true;
			break;
		}
	}

}

void Logic(){

	int preX = tailX[0];
	int preY = tailY[0];
	int pre2X,pre2Y;
	tailX[0] = x;
	tailY[0] = y;
	for(int i=1;i<nTail;i++){
		pre2X = tailX[i];
		pre2Y = tailY[i];
		tailX[i] = preX;
		tailY[i] = preY;
		preX = pre2X;
		preY = pre2Y;
	}
	
	switch(dir){
	       /*	case Stop:
		break;*/
		case Left: x--;
		break;
		case Right: x++;
		break;
		case Up:  y--;
		break;
		case Down:  y++;
		break;
	}
	if(x>width || x<0 || y>height || y<0) gameOver=true;
	for(int i=0;i<nTail;i++){
		if(tailX[i]==x && tailY[i]==y) gameOver=true;
	}
	if(x==fruitX && y==fruitY){ score+=10; fruitX = rand()%width; fruitY = rand()%height; nTail++; }
}


int main(){
	Setup();
	while(!gameOver){
		Draw();
		Input();
		Logic();
	//	Sleep(5);
	}
	return 0;
}