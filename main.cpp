#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include <sstream>
using namespace sf;

void play();		//LEVEL 1
void play2();		//LEVEL 2

struct tile			//STORE DIFFERENT DATATYPES IN ONE PIECE	
{
int x_axis,y_axis,column,row,specie,same,bozo;
tile(){same=0;bozo=255;}
}board[10][10];

int score1=0,score2=0,moves=30,move2=20;
float timer=60;
int win=2000;

void swap(tile t1,tile t2);

int main()
{	
	bool Menu=true;
	while(Menu)
		{
			int choose;
			std::cout<<"-------------------------------------------------"<<std::endl;
			std::cout<<"                    MAIN MENU                  "<<std::endl;
			std::cout<<"-------------------------------------------------"<<std::endl;
			std::cout<<"Press 1 for Level 1 (easy mode, no time)"<<std::endl;
			std::cout<<"Press 2 for level 2 (hard mode, time restriction)"<<std::endl;
			std::cout<<"Press 3 for exit"<<std::endl;
			std::cin>>choose;
			switch(choose)
			{
				case 1: play();break;
				case 2: play2();break;
				case 3: Menu=false;break;
				default: std::cout<<"Invalid Input";break;
			}
		}
}

void play()
{   	
    int ts = 54; //tile size
    Vector2i offset(12,24);
    srand(time(0));
    RenderWindow app(VideoMode(740,480), "Menagerie (level 1)");
    app.setFramerateLimit(60);
    Texture t1,t2;
    t1.loadFromFile("sprites/background.jpg");
    t2.loadFromFile("sprites/hero.png");
    Sprite background(t1), hero(t2);
    Font OpenSans;
    OpenSans.loadFromFile("fonts/OpenSans-Bold.ttf");
    
    Music music;
    if(!music.openFromFile("audio/music.ogg"));
    {
    	std::cout<<"Error"<<std::endl;
    }
    music.play();
    
    SoundBuffer buffer;
    if(!buffer.loadFromFile("audio/sound.wav"));
    {
    	std::cout<<"ERROR"<<std::endl;
    }
    
    Sound sound;
    sound.setBuffer(buffer);
    
    

    std::stringstream ssScore;
    ssScore<<"Score: "<<score1;

    Text Score;				//DEFINING SCORE AND ADJUSTING IT ON GAME BOARD WITH X AND Y COORDINATES
    Score.setCharacterSize(45);
    Score.setPosition({500,400});
    Score.setFont(OpenSans);
    Score.setString(ssScore.str());
    Score.setFillColor(Color::Blue);
    
    
    std::stringstream ssMove;
    ssMove<<"Moves left: "<<moves;
    
    Text Move;				//DEFINING MOVES
    Move.setCharacterSize(30);
    Move.setPosition({500,200});
    Move.setFont(OpenSans);
    Move.setString(ssMove.str());
    Move.setFillColor(Color::White); 
    
    std::stringstream ssWin;
    ssWin<<"points needed to win: "<<win;
    
    Text Win;				//DEFINING POINTS NEEDED TO WIN
    Win.setCharacterSize(20);
    Win.setPosition({450,250});
    Win.setFont(OpenSans);
    Win.setString(ssWin.str());
    Win.setFillColor(Color::Red);
    for (int i=1;i<=8;i++)
          for (int j=1;j<=8;j++)
          {
		  board[i][j].specie=rand()%7;
		  board[i][j].x_axis = j*ts;
		  board[i][j].y_axis = i*ts;
		  board[i][j].column=j;
		  board[i][j].row=i;
          }
          
    int pick=0, move=0;
    int tick=0;
    int x_one,y_one,x_two,y_two;  
    Vector2i position;
    Event e;
    while (app.isOpen()){
    while (app.pollEvent(e)){
    if (e.type == Event::Closed)
                app.close();
                if (e.type == Event::MouseButtonPressed)
                if (e.mouseButton.button == Mouse::Left){
        //code of action to be performed on mouse click
                	if(pick==0 && move==0)
                	{
                		tick++;
                		position= Mouse::getPosition(app)-offset;
                	}
                }
                } 
    if(tick==1)				//getting the x,y coordinates of a tile
    {
    	x_one=position.x/ts+1;
    	y_one=position.y/ts+1;
    }
    else if(tick==2)
    {
    	x_two=position.x/ts+1;
    	y_two=position.y/ts+1; 
    		if(abs(x_two-x_one)+abs(y_two-y_one)==1)
    			{
				swap(board[y_one][x_one],board[y_two][x_two]);
    				tick=0,pick=1;
    			        
    			      	moves-=1;						                    
		   		ssMove.str("");
		   		ssMove<<"Moves left: "<<moves;
		   		Move.setString(ssMove.str());
    			}
    		else
    			tick=1; 
    }  
    
    
    //finding same species in board
    for(int i=1;i<=8;i++)
    {
    	for(int j=1;j<=8;j++)
    	{
    		if(board[i][j].specie==board[i+1][j].specie && board[i][j].specie==board[i-1][j].specie)
    		{
    			for(int k=-1;k<=1;k++)
    				board[i+k][j].same++;
    		}
    		if(board[i][j].specie==board[i][j+1].specie && board[i][j].specie==board[i][j-1].specie)
    		{
    			for(int k=-1;k<=1;k++)
    				board[i][j+k].same++;
    		} 
    	}
    }
       
    // animation
    move=0;
    for(int i=1;i<=8;i++)
    {
    	for(int j=1;j<=8;j++)
    	{
    		tile &t=board[i][j];
    		int x0,y0;
    		for(int k=0;k<5;k++)
    		{
    			x0=t.x_axis-t.column*ts;
    			y0=t.y_axis-t.row*ts;
    			if(x0)
    			{
    				t.x_axis-=x0/abs(x0);
    			}
    			if(y0)
    			{
    				t.y_axis-=y0/abs(y0);
    			}
    		}
    		if(x0 || y0)
    		{
    			move=1;
    		}
    	}
    }
    
    
    //delete
    if(move==0)
    {
    	for(int i=1;i<=8;i++)
    	{
    		for(int j=1;j<=8;j++)
    		{
    			if(board[i][j].same && board[i][j].bozo>10)
    			{
    				board[i][j].bozo-=10;
    				move=1;
    				score1+=1;
       				ssScore.str("");
       				ssScore<<"Score "<<score1;
       				Score.setString(ssScore.str());
       				sound.play();
    				
    			}
    		}
    	}
    }
    
    int check=0;
    	for(int i=1;i<=8;i++)
    	{
    		for(int j=1;j<=8;j++)
    		{
    			check+=board[i][j].same;
    		}
    	}
    	
    //swap back if match returns false
    if(pick!=0 && move==0)
    {
    	if(check==0)
    	{
    		swap(board[y_one][x_one],board[y_two][x_two]); 
    	}
    		pick=0;
    }
    
    //board update(tiles falling)
    if(move==0)
    {
    	for(int i=8;i>0;i--)
    	{
    		for(int j=1;j<=8;j++)
    		{
    			if(board[i][j].same)
    			{
    				for(int k=i;k>0;k--)
    				{
    					if(!board[k][j].same)
    					{
    						swap(board[k][j],board[i][j]);
    						break;
    					}
    				}
    			}
    		}
    	}
    	for(int j=1;j<=8;j++)
    	{
    		for(int i=8,k=0;i>0;i--)
    		{
    			if(board[i][j].same)
    			{
    				board[i][j].specie=rand()%7;
    				board[i][j].y_axis=-ts*k++;
    				board[i][j].same=0;
    				board[i][j].bozo=255;
    			}
    		}
    	}
    }
                	    	    				   
    
    if(score1==2000)
    	app.close();		//GAME END IF SCORE =2000
    else if(moves==0)		//GAME END IF MOVE==0
    	app.close();
    //drawing backgorund
    app.draw(background);
    for (int i=1;i<=8;i++)
    {
    	for (int j=1;j<=8;j++)
    	{
		tile t= board[i][j];
		hero.setTextureRect( IntRect(t.specie*49,0,49,49));
		hero.setColor(Color(255,255,255,t.bozo));
		hero.setPosition(t.x_axis,t.y_axis);
		hero.move(offset.x-ts,offset.y-ts);
		app.draw(hero);
		app.draw(Score);
		app.draw(Move);
		app.draw(Win);
        }
     }
    app.display();
    }

}

void play2()
{   	
    int ts = 54; //tile size
    Vector2i offset(12,24);
    srand(time(0));
    RenderWindow app(VideoMode(740,480), "Menagerie (level 2)");
    app.setFramerateLimit(60);
    Texture t1,t2;
    t1.loadFromFile("sprites/background.jpg");
    t2.loadFromFile("sprites/hero.png");
    Sprite background(t1), hero(t2);
    Font OpenSans;
    OpenSans.loadFromFile("fonts/OpenSans-Bold.ttf");
    
    std::stringstream ssScore;
    ssScore<<"Score: "<<score2;

    Text Score;
    Score.setCharacterSize(45);			//DEFINING SCORE ON GAMEBOARD
    Score.setPosition({500,400});
    Score.setFont(OpenSans);
    Score.setString(ssScore.str());
    Score.setFillColor(Color::Blue);

    
    std::stringstream ssTimer;
    ssTimer<<"Timer: "<<timer;

    Text Timer;					//DEFINING TIMER ON GAMEBOARD
    Timer.setCharacterSize(30);
    Timer.setPosition({570,20});
    Timer.setFont(OpenSans);
    Timer.setString(ssTimer.str());
    Timer.setFillColor(Color::White);
    
    std::stringstream ssMove;
    ssMove<<"Moves left: "<<move2;
    
    Text Move;					//DEFINING MOVES
    Move.setCharacterSize(30);
    Move.setPosition({500,200});
    Move.setFont(OpenSans);
    Move.setString(ssMove.str());
    Move.setFillColor(Color::White);
    
    
    std::stringstream ssWin;
    ssWin<<"Points needed to win: "<<win;
    
    Text Win;					//DEFINING POINTS NEEDED TO WIN
    Win.setCharacterSize(20);
    Win.setPosition({450,250});
    Win.setFont(OpenSans);
    Win.setString(ssWin.str());
    Win.setFillColor(Color::Red); 
    
    Music music;
    if(!music.openFromFile("audio/music.ogg"));
    {
    	std::cout<<"Error"<<std::endl;
    }
    music.play();
    
    SoundBuffer buffer;
    if(!buffer.loadFromFile("audio/sound.wav"));
    {
    	std::cout<<"ERROR"<<std::endl;
    }
    
    Sound sound;
    sound.setBuffer(buffer);
    
    for (int i=1;i<=8;i++)
          for (int j=1;j<=8;j++)
          {
		  board[i][j].specie=rand()%7;
		  board[i][j].x_axis = j*ts;
		  board[i][j].y_axis = i*ts;
		  board[i][j].column=j;
		  board[i][j].row=i;
          }
          
    int pick=0, move=0;
    int tick=0;
    int x_one,y_one,x_two,y_two;  
    Vector2i position;
    Event e;
    while (app.isOpen()){
    while (app.pollEvent(e)){
    if (e.type == Event::Closed)
                app.close();
                if (e.type == Event::MouseButtonPressed)
                if (e.mouseButton.button == Mouse::Left){
        //code of action to be performed on mouse click
                	if(pick==0 && move==0)
                	{
                		tick++;
                		position= Mouse::getPosition(app)-offset;
                	}
                }
                } 
    if(tick==1)
    {
    	x_one=position.x/ts+1;			//getting the x,y coordinates of a tile
    	y_one=position.y/ts+1;
    }
    else if(tick==2)
    {
    	x_two=position.x/ts+1;
    	y_two=position.y/ts+1; 
    		if(abs(x_two-x_one)+abs(y_two-y_one)==1)
    			{
				swap(board[y_one][x_one],board[y_two][x_two]);
    				
    				tick=0,pick=1;
    			      	move2-=1;						                    
		   		ssMove.str("");
		   		ssMove<<"Moves left: "<<move2;
		   		Move.setString(ssMove.str());
    			}
    		else
    			tick=1; 
    }  
    
    
    //finding same species in board
    for(int i=1;i<=8;i++)
    {
    	for(int j=1;j<=8;j++)
    	{
    		if(board[i][j].specie==board[i+1][j].specie && board[i][j].specie==board[i-1][j].specie)
    		{
    			for(int k=-1;k<=1;k++)
    				board[i+k][j].same++;
    		}
    		if(board[i][j].specie==board[i][j+1].specie && board[i][j].specie==board[i][j-1].specie)
    		{
    			for(int k=-1;k<=1;k++)
    				board[i][j+k].same++;
    		} 
    	}
    }
       
    // animation
    move=0;
    for(int i=1;i<=8;i++)
    {
    	for(int j=1;j<=8;j++)
    	{
    		tile &t=board[i][j];
    		int x0,y0;
    		for(int k=0;k<10;k++)
    		{
    			x0=t.x_axis-t.column*ts;
    			y0=t.y_axis-t.row*ts;
    			if(x0)
    			{
    				t.x_axis-=x0/abs(x0);
    			}
    			if(y0)
    			{
    				t.y_axis-=y0/abs(y0);
    			}
    		}
    		if(x0 || y0)
    		{
    			move=1;
    		}
    	}
    }
    
    
    //delete
    if(move==0)
    {
    	for(int i=1;i<=8;i++)
    	{
    		for(int j=1;j<=8;j++)
    		{
    			if(board[i][j].same && board[i][j].bozo>10)
    			{
    				board[i][j].bozo-=10;
    				move=1;
    				score2+=1;
       				ssScore.str("");
       				ssScore<<"Score "<<score2;
       				Score.setString(ssScore.str());
       				sound.play();
    			}
    		}
    	}
    }
   timer-=0.02;
   ssTimer.str("");
   ssTimer<<"Timer "<<timer;
   Timer.setString(ssTimer.str());
    
    int check=0;
    	for(int i=1;i<=8;i++)
    	{
    		for(int j=1;j<=8;j++)
    		{
    			check+=board[i][j].same;
    		}
    	}
    	
    //swap back if match returns false
    if(pick!=0 && move==0)
    {
    	if(check==0)
    	{
    		swap(board[y_one][x_one],board[y_two][x_two]); 
    	}
    		pick=0;
    }
    
    //board update(tiles falling)
    if(move==0)
    {
    	for(int i=8;i>0;i--)
    	{
    		for(int j=1;j<=8;j++)
    		{
    			if(board[i][j].same)
    			{
    				for(int k=i;k>0;k--)
    				{
    					if(!board[k][j].same)
    					{
    						swap(board[k][j],board[i][j]);
    						break;
    					}
    				}
    			}
    		}
    	}
    	for(int j=1;j<=8;j++)
    	{
    		for(int i=8,k=0;i>0;i--)
    		{
    			if(board[i][j].same)
    			{
    				board[i][j].specie=rand()%7;
    				board[i][j].y_axis=-ts*k++;
    				board[i][j].same=0;
    				board[i][j].bozo=255;
    			}
    		}
    	}
    }
    
    if(score2==2000)  //when score reachers 1500 it ends
    	app.close();
    else if(timer<0)	//when timer goes into negative, game ends
    	app.close();
    else if(move2==0)
    	app.close();
    //drawing backgorund
    app.draw(background);
    for (int i=1;i<=8;i++)
    {
    	for (int j=1;j<=8;j++)
    	{
		tile t= board[i][j];
		hero.setTextureRect( IntRect(t.specie*49,0,49,49));
		hero.setColor(Color(255,255,255,t.bozo));
		hero.setPosition(t.x_axis,t.y_axis);
		hero.move(offset.x-ts,offset.y-ts);
		app.draw(hero);
		app.draw(Score);
		app.draw(Timer);
		app.draw(Move);
		app.draw(Win);
        }
     }
    app.display();
    }

}



void swap(tile t1,tile t2)
{
	std::swap(t1.column,t2.column);
	std::swap(t1.row,t2.row);			
	board[t1.row][t1.column]=t1;
	board[t2.row][t2.column]=t2;
}



