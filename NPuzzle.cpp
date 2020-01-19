#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<cstring>

using namespace std;
class NPuzzle
{ 
private://Npuzzle private
 class Board{

	public://board public
		void menu(string namef,const int namecheck);
		
		void print(const int mtx[][9],int *x,int *y,const int h,const int w);

		void readFromFile(string mtrx[][9],const string namef,int *h,int *w);

		void writeToFile(int mtrx[][9],const string namef,const int x,const int y,const int h,const int w);


		void reset(int mtrx[][9],int goalmtrx[][9],const int h,const int w,int resetcheck);

		void setsize(int mtrx[][9],int *h,int *w);


		void move(int mtrx[][9],const char secim,const int h,const int w,int *x,int *y,int *movecounter);

	    	bool isSolved(int goalmtrx[][9],int mtrx[][9],const int h,const int w);

	private://Board private
  		int mtrx[9][9];
	
	};//board curl


public://NPUZZLE PUBLİC AREA
	NPuzzle::Board b;
		void menu(string namef,const int namecheck){
			b.menu(namef,namecheck);
			}
		void print(const int mtx[][9],int *x,int *y,const int h,const int w){	
			b.print(mtx,x,y,h,w);
		}

		void printReport(const int movecounter,const int isolved);

		void readFromFile(string mtrx[][9],const string namef,int *h,int *w){
			b.readFromFile(mtrx,namef,h,w);
		}

		void writeToFile(int mtrx[][9],const string namef,const int x,const int y,const int h,const int w){
			b.writeToFile(mtrx,namef,x,y,h,w);		
			}

		void shuffle(int mtrx[][9],const int h,const int w,int *x,int *y,const int N,int *movecounter);

		void reset(int mtrx[][9],int goalmtrx[][9],const int h,const int w,int resetcheck){
			b.reset(mtrx,goalmtrx,h,w,resetcheck);
		}

		void setsize(int mtrx[][9],int *h,int *w){
			b.setsize(mtrx,h,w);	
		}

		void moveRandom(int mtrx[][9],const int h,const int w,int *x,int *y,int randnum,int *movecounter,int printcheck);

		void moveIntelligent (int mtrx[][9],const int h,const int w,int *x,int *y,int *movecheck,int *movecounter,int *stuckcheck);

		void move(int mtrx[][9],const char secim,const int h,const int w,int *x,int *y,int *movecounter){
			b.move(mtrx,secim,h,w,x,y,movecounter);	
		}

		void solvePuzzle(int mtrx[][9],int goalmtrx[][9],const int height,const int width,int *x,int *y,int *movecounter,int *stuckcheck);



};//npuzzle curl


int main(int argc,char *argv[]){//maın functıon
	srand(time(NULL));
	int size,fnamecheck;
	char filename[20];
	NPuzzle n;
	if(argc!=1){		
		strcpy(filename,argv[1]);
		fnamecheck=1;
		n.menu(filename,fnamecheck);	
	}
	else{cout<<"you didnt write file name on command line"<<endl;
		fnamecheck=0;
		n.menu(filename,fnamecheck);
	}
	return 0;
}


bool NPuzzle::Board::isSolved(int goalmtrx[][9],int mtrx[][9],const int h,const int w){//comparing current matrix with goal
	int i,j,k,counter=0;
	for(i=0;i<h;i++){
		for(j=0;j<w;j++){
			if(goalmtrx[i][j]==mtrx[i][j]){
				counter++;		
			}				
		}
	}
	if(counter== h*w){ return true;}
        else return false;	
}



void NPuzzle::Board::print(const int mtx[][9],int *x,int *y,const int h,const int w){ //printing matrix for 2. situation
    int i,j;
    for (i= 0; i < h; i++) 
	{	 
        	for (j = 0; j < w; j++){

			if(mtx[i][j]== 99){//if it is 99 this means bb
				cout <<"bb"<<" ";
					*y=i;
					*x=j; 
				}
			else{
     		         	if((mtx[i][j]/10)==0)
					cout<<"0"<< mtx[i][j] << " ";
				else 
					cout<< mtx[i][j] << " ";
			}
		} 
        cout <<"\n"; 
    	} 	
} 
void NPuzzle::printReport(const int movecounter,const int issolved){//reporting how many moves we did

	if(issolved==1)	cout <<"Problem solved"<<endl<<"Total number of moves: "<<movecounter << endl;


else cout<<"Total number of moves: "<<movecounter << endl;

}

void NPuzzle::Board::readFromFile(string mtrx[][9],const string namef,int *h,int *w){
	int i,j;
	string line,temp;
	ifstream rfile;
	rfile.open(namef);
		
	if(rfile.is_open()){
		cout << "file is opened succesfully"<<endl;
		for(i=0;i<10;i++){
			for(j=0;j<10;j++){
				if(rfile.peek() != EOF){
						if(rfile.peek() == '\n'){ //if line is end,then go next line
							*w=j;
							i++;
							j=0;
							rfile >> mtrx[i][j];	
						}						
						else {	rfile >> mtrx[i][j];
							}
									
				}
				else {	 
						*h=i;
						cout<< "height of file is=" << *h <<" width of file= "<<*w<<endl<<endl;
						rfile.close();
						return ; 
					}
				}        
			}
			
		}
		
	else { cout<< "wrong file name try it again later"<<endl;// if file name is wrong
			return ;	}

}

void NPuzzle::Board::writeToFile(int mtrx[][9],const string namef,const int x,const int y,const int h,const int w){
	ofstream wfile;
	int i,j;
	wfile.open(namef);

	if(wfile.is_open()){
		cout << "file is opened succesfully"<<endl;
		for(i=0;i<h;i++){
                    for(j=0;j<w;j++){
			if(i==y && j==x){
			 wfile<<"bb";
				if(j!=w-1){wfile << " ";}//we dont want to put space end of line
			}
			else{
     		         	if((mtrx[i][j]/10)==0){
					wfile <<"0"<< mtrx[i][j]; 
					if(j!=w-1){wfile << " ";}//we dont want to put space end of line
				}
				else {
					wfile <<mtrx[i][j];
					if(j!=w-1){wfile << " ";}//we dont want to put space end of line
				}
			}
				
		    }
		   wfile <<'\n';						
		}
	wfile.close();
	}
} 
void NPuzzle::shuffle(int mtrx[][9],const int h,const int w,int *x,int *y,const int N,int *movecounter){//shuffling with moving blank
		int printcheck=0;
		moveRandom(mtrx,h,w,x,y,N,movecounter,printcheck);
}



void NPuzzle::Board::reset(int mtrx[][9],int goalmtrx[][9],const int h,const int w,const int resetcheck){//finding the final board ascending 
	int i,j,k,l,m,n;
	int temp;
	NPuzzle f;
	//filling goal array with initial array,we dont change initial; 
	for (k = 0; k < h; k++){
		for (m = 0; m < w; m++){
			goalmtrx[k][m]=mtrx[k][m];
		}
	}
		for (k = 0; k < h; k++){//sorting array
			for (m = 0; m < w; m++){
			    n = m+1;
			    for ( i = k; i < h ; i++){
				for ( j = n; j < w; j++){
				    if(goalmtrx [k][m]!= 0 &&goalmtrx [i][j]!= 0  ){//we dont change 00 's
					if (goalmtrx [k][m] > goalmtrx [i][j]){
					temp=goalmtrx [k][m]; 
					goalmtrx [k][m]=goalmtrx [i][j];
					goalmtrx [i][j]=temp;     
					}
				    }
				}
				n=0;
			    } 
			}
		}


     if(resetcheck==1){//if we use this function just for finding goalmatrix we must know that
	for (k = 0; k < h; k++){//if we want reset mtrx then this resetting main matrix to goal
		for (m = 0; m < w; m++){
			mtrx[k][m]=goalmtrx[k][m];
		}
	}
     }


}



void NPuzzle::Board::setsize(int mtrx[][9],int *h,int *w){//if user didnt use comman line, we use this function
	int i,j,num=1;
	cout<< "Enter heiht: "<<endl;
	cin >> *h;
	cout<< "Enter width: "<<endl;
	cin >> *w;
		while(*h>9 || *h<3 ||  *w>9 || *w<3){
			cout <<"you must enter heigth-width between 3-9"<<endl;
			cout<< "Enter heiht: "<<endl;
			cin >> *h;
			cout<< "Enter width: "<<endl;
			cin >> *w;
		}
	for(i=0;i<*h;i++){
		for(j=0;j<*w;j++){
			if(i == *h-1 && j == *w-1 ){ mtrx[i][j]= 99;//we declare 99 for bb 
				  }			
			else	{mtrx[i][j]=num;}
				num=num+1;		
		}
	}

}

void NPuzzle::moveRandom(int mtrx[][9],const int h,const int w,int *x,int *y,const int randnum,int *movecounter,const int printcheck){
     int move,i,j,temp;
	// 1 -left 2-right 3-up 4-down   
	for(i=0;i<randnum;i++){
	 move=rand()%4+1;
		if( move==1 ){//left
			if(*x>0 && *y<h &&mtrx[*y][*x-1] != 0){//swapping with left
				temp=mtrx[*y][*x];
				mtrx[*y][*x]=mtrx[*y][*x-1];
				mtrx[*y][*x-1]=temp;
				*x=*x-1;
				*movecounter=  *movecounter+1;
				}
			}
		else if(move==2){
			if(*x<w-1 && *y<h && mtrx[*y][*x+1] !=0){//swapping with right
				temp=mtrx[*y][*x];
				mtrx[*y][*x]=mtrx[*y][*x+1];
				mtrx[*y][*x+1]=temp;
				*x=*x+1;
				*movecounter=*movecounter+1;
				}
			}
		else if(move==3){
			if(*x>=0 && *y>0 && mtrx[*y-1][*x] !=0){//swapping with up
				temp=mtrx[*y][*x];
				mtrx[*y][*x]=mtrx[*y-1][*x];
				mtrx[*y-1][*x]=temp;
				*y=*y-1;
				*movecounter=*movecounter+1;
				}
			}
		else if(move==4 ){
			if(*x>=0 && *y<h-1 && mtrx[*y+1][*x] !=0){//swapping with down
				temp=mtrx[*y][*x];
				mtrx[*y][*x]=mtrx[*y+1][*x];
				mtrx[*y+1][*x]=temp;
				*y=*y+1;
				*movecounter=*movecounter+1;
				}
			}
	if(printcheck==1){//if this using for intelligent then we print every move
		print(mtrx,x,y,h,w);
		cout<<"\n"<<"movecounter="<< *movecounter;
		cout<<"\n";}	

	}
}
void NPuzzle::moveIntelligent (int mtrx[][9],const int h,const int w,int *x,int *y,int *movecheck,int *movecounter,int *stuckcheck){//intelligent move
	int i,j;//movecheck numbers: up=1,down=2,left=3,right=4.
	int temp;
      if (*x < w-1 && *y < h-1 && *x >0 && *y > 0){//1-right-left-up-down 
			if(*movecheck!=2  && mtrx[*y][*x-1] < mtrx[*y-1][*x] && mtrx[*y][*x+1] > mtrx[*y-1][*x]&& mtrx[*y-1][*x]!=  0 ){//up is logical
						cout<<"intelligent move chooses up "<<endl;
						temp=mtrx[*y][*x];
						mtrx[*y][*x]=mtrx[*y-1][*x];
						mtrx[*y-1][*x]=temp;
						*y=*y-1;
						*movecheck=1;
						*movecounter=*movecounter+1;
					} 
			else	if(*movecheck!=1 && mtrx[*y][*x-1] < mtrx[*y+1][*x] && mtrx[*y][*x+1] > mtrx[*y+1][*x]&& mtrx[*y+1][*x]!= 0){//down 
						cout<<"intelligent move chooses down "<<endl;		
						temp=mtrx[*y][*x];
						mtrx[*y][*x]=mtrx[*y+1][*x];
						mtrx[*y+1][*x]=temp;
						*y=*y+1;
						*movecheck=2;	
						*movecounter=*movecounter+1;
					} 
			else	if(*movecheck!=4 && mtrx[*y-1][*x] <= mtrx[*y][*x-1] && mtrx[*y][*x+1] < mtrx[*y][*x-1]&& mtrx[*y][*x-1]!= 0){//left is
						cout<<"intelligent move chooses left "<<endl;						
						temp=mtrx[*y][*x];
						mtrx[*y][*x]=mtrx[*y][*x-1];
						mtrx[*y][*x-1]=temp;
						*x=*x-1;
						*movecheck=3;
						*movecounter=*movecounter+1;
					} 
			else	if(*movecheck!=3 && mtrx[*y][*x-1] > mtrx[*y][*x+1]&& mtrx[*y][*x+1]!= 0){//right is logical
						cout<<"intelligent move chooses right "<<endl;						
						temp=mtrx[*y][*x];
						mtrx[*y][*x]=mtrx[*y][*x+1];
						mtrx[*y][*x+1]=temp;
						*x=*x+1;
						*movecheck=4;
						*movecounter=*movecounter+1;
					}
			else {     *stuckcheck=1;     }

	}
	
  else	if((*x==0 && *y== h -1) || (mtrx[*y+1][*x]== 0 && mtrx[*y][*x-1]== 0 )){//2- right -up check-------------------
				if(*movecheck!=2  && mtrx[*y][*x+1] < mtrx[*y-1][*x]&&mtrx[*y-1][*x]!= 0){
					cout<<"intelligent move chooses up "<<endl;					
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y-1][*x];
					mtrx[*y-1][*x]=temp;
					*y=*y-1;
					*movecheck=1;
                    			*movecounter=*movecounter+1;
				} 
			else	if(*movecheck!=3  &&mtrx[*y][*x+1]!= 0){//right logical
					cout<<"intelligent move chooses right "<<endl;					
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y][*x+1];
					mtrx[*y][*x+1]=temp;
					*x=*x+1;
					*movecheck=4;
                    			*movecounter=*movecounter+1;
				}
			else {     *stuckcheck=1;                   }
	}

  else	if((*x==0 && *y==0)||(mtrx[*y-1][*x]== 0 && mtrx[*y][*x-1]== 0 ) ){//3- right -down check---------------------------- 
				if(*movecheck!=1  && mtrx[*y][*x+1] > mtrx[*y+1][*x]&& mtrx[*y+1][*x]!= 0){//down logical	
					cout<<"intelligent move chooses down "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y+1][*x];
					mtrx[*y+1][*x]=temp;
					*y=*y+1;
					*movecheck=2;
                    			*movecounter=*movecounter+1;
				} 
			else	if(*movecheck!=3 && mtrx[*y][*x+1]!= 0 ){//right logical
					cout<<"intelligent move chooses right "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y][*x+1];
					mtrx[*y][*x+1]=temp;
					*x=*x+1;
					*movecheck=4;
          				*movecounter=*movecounter+1;
				}
			else {     *stuckcheck=1;                   }
		}
  else	if((*x==w-1 && *y==0)||(mtrx[*y-1][*x]== 0 && mtrx[*y][*x+1]== 0 )){//4- left-down check--------------------
				if(*movecheck!=1  && mtrx[*y][*x-1] > mtrx[*y+1][*x]&& mtrx[*y+1][*x]!= 0){// logical
					cout<<"intelligent move chooses down "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y+1][*x];
					mtrx[*y+1][*x]=temp;
					*y=*y+1;
					*movecheck=2;
                   			*movecounter=*movecounter+1;
				} 			
			else	if(*movecheck!=4&&mtrx[*y][*x-1]!= 0 ){//logical
					cout<<"intelligent move chooses left "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y][*x-1];
					mtrx[*y][*x-1]=temp;
					*x=*x-1;
					*movecheck=3;
                    			*movecounter=*movecounter+1;
				}
			else {          *stuckcheck=1;                   }

	
	}
  else	if((*x== w-1 && *y==h -1)||(mtrx[*y+1][*x]== 0 && mtrx[*y][*x+1]== 0 )){//5- up-left check-----------------
				if(*movecheck!=2  && mtrx[*y][*x-1] < mtrx[*y-1][*x]&&mtrx[*y-1][*x]!= 0){//ogical
					cout<<"intelligent move chooses up "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y-1][*x];
					mtrx[*y-1][*x]=temp;
					*y=*y-1;
					*movecheck=1;
                   			 *movecounter=*movecounter+1;
				} 
			else	if(*movecheck!=4  &&mtrx[*y][*x-1]!= 0){//leftlogical
					cout<<"intelligent move chooses left "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y][*x-1];
					mtrx[*y][*x-1]=temp;
					*x=*x-1;
					*movecheck=3;
                    			*movecounter=*movecounter+1;				
				}
			else {          *stuckcheck=1;                   }	
	
	}
  else	if((*x==0 && *y<h -1 && *y>0&& mtrx[*y-1][*x]!= 0)||( mtrx[*y][*x-1]== 0 && *y>0 )){//6- right-up-down check--
				if(*movecheck!=2  &&mtrx[*y][*x+1] < mtrx[*y-1][*x] && mtrx[*y-1][*x]!= 0){//up islogical
					cout<<"intelligent move chooses up "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y-1][*x];
					mtrx[*y-1][*x]=temp;
					*y=*y-1;
					*movecheck=1;
                    			*movecounter=*movecounter+1;
				} 
			else	if(*movecheck!=1  &&mtrx[*y][*x+1] > mtrx[*y+1][*x]&& mtrx[*y+1][*x]!= 0){//down logical
					cout<<"intelligent move chooses down "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y+1][*x];
					mtrx[*y+1][*x]=temp;
					*y=*y+1;
                    			*movecheck=2;
                    			*movecounter=*movecounter+1;
				}
			else	if(*movecheck!=3 && mtrx[*y+1][*x] > mtrx[*y][*x+1]&&mtrx[*y][*x+1]!= 0){//right logical
					cout<<"intelligent move chooses right "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y][*x+1];
					mtrx[*y][*x+1]=temp;
					*x=*x+1;
                    			*movecheck=4;
                   			*movecounter=*movecounter+1;
				}
			else {     *stuckcheck=1;                   } 
			
	}
  else	if((*x>0 && *y==0 && *x<w-1) || (mtrx[*y-1][*x]== 0  )){//7-down-right-left check-------
				if(*movecheck!=4  && mtrx[*y][*x+1]<mtrx[*y][*x-1]&&mtrx[*y][*x-1]!= 0){//leftislogical
					cout<<"intelligent move chooses left "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y][*x-1];
					mtrx[*y][*x-1]=temp;
					*x=*x-1;
					*movecheck=3;
                    			*movecounter=*movecounter+1;
				}
			else	if(*movecheck!=1&& mtrx[*y][*x-1] < mtrx[*y+1][*x]&& mtrx[*y][*x+1] > mtrx[*y+1][*x]&&mtrx[*y+1][*x]!=0){//down
					cout<<"intelligent move chooses down "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y+1][*x];
					mtrx[*y+1][*x]=temp;
					*y=*y+1;
					*movecheck=2;
                    			*movecounter=*movecounter+1;
				}
			else	if(*movecheck!=3 && mtrx[*y+1][*x] > mtrx[*y][*x+1] && mtrx[*y][*x+1]!= 0){//rightlogic
					cout<<"intelligent move chooses right "<<endl;
 		       			temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y][*x+1];
					mtrx[*y][*x+1]=temp;
					*x=*x+1;
					*movecheck=4;
                   			 *movecounter=*movecounter+1;
				} 
			else {     *stuckcheck=1;                   }
	}
   else	if((*y==h-1 && *x>0 && *x<w-1)||(mtrx[*y+1][*x]== 0 )){//8-up -right-left check
				if(*movecheck!=2  &&mtrx[*y][*x-1] <mtrx[*y-1][*x] && mtrx[*y][*x+1] > mtrx[*y-1][*x]&& mtrx[*y-1][*x]!=0){//up islogic
					cout<<"intelligent move chooses up "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y-1][*x];
					mtrx[*y-1][*x]=temp;
					*y=*y-1;
					*movecheck=1;
                    			*movecounter=*movecounter+1;
				}				

		else	if(*movecheck!=4  && mtrx[*y-1][*x] < mtrx[*y][*x-1]&& mtrx[*y][*x+1] < mtrx[*y][*x-1]&& mtrx[*y][*x-1]!=0){//left islogic
					cout<<"intelligent move chooses left "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y][*x-1];
					mtrx[*y][*x-1]=temp;
					*x=*x-1;
					*movecheck=3;
                    			*movecounter=*movecounter+1;
				}
			else	if(*movecheck!=3  &&mtrx[*y][*x+1]!= 0){//rightis logic
					cout<<"intelligent move chooses right "<<endl;
        				temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y][*x+1];
					mtrx[*y][*x+1]=temp;
					*x=*x+1;
					*movecheck=4;
                    			*movecounter=*movecounter+1;
				} 
			else {     *stuckcheck=1;                   }
	}
   else	if((*x==w-1 && *y>0 && *y<h-1)||(mtrx[*y][*x+1]== 0 ) ){//9-left-up-down check----
			if(*movecheck!=2&& mtrx[*y][*x-1] < mtrx[*y-1][*x]&&mtrx[*y-1][*x]!=0){//up logic	
					cout<<"intelligent move chooses up "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y-1][*x];
					mtrx[*y-1][*x]=temp;
					*y=*y-1;
					*movecheck=1;
                    			*movecounter=*movecounter+1;
				}					
		else	if(*movecheck!=1  && mtrx[*y-1][*x] > mtrx[*y+1][*x] && mtrx[*y][*x-1] > mtrx[*y+1][*x]&& mtrx[*y+1][*x]!= 0 ){//downislogic
					cout<<"intelligent move chooses down "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y+1][*x];
					mtrx[*y+1][*x]=temp;
					*y=*y+1;
					*movecheck=2;
                		        *movecounter=*movecounter+1;
				}
		else	if(*movecheck!=4  && mtrx[*y+1][*x] < mtrx[*y][*x-1]&& mtrx[*y-1][*x] < mtrx[*y][*x-1]&& mtrx[*y][*x-1]!= 0){//leftislogic
					cout<<"intelligent move chooses left "<<endl;
					temp=mtrx[*y][*x];
					mtrx[*y][*x]=mtrx[*y][*x-1];
					mtrx[*y][*x-1]=temp;
					*x=*x-1;			
					*movecheck=3;
                    			*movecounter=*movecounter+1;
				}
		else {     *stuckcheck=1;                   }
	}
	
}

void NPuzzle::Board::move(int mtrx[][9],const char secim,const int h,const int w,int *x,int *y,int *movecounter){
	
        int resetcheck=0,goalmtrx[9][9],temp;
	reset(mtrx,goalmtrx,h,w,resetcheck);
	if( secim == 'L'  || secim == 'l' ){

			if(*x>0 && *y< h && mtrx[*y][*x-1] != 0){
				temp=mtrx[*y][*x];
				mtrx[*y][*x]=mtrx[*y][*x-1];
				mtrx[*y][*x-1]=temp;				
				*x=*x-1;				
				*movecounter=*movecounter+1;			
				if(isSolved(goalmtrx,mtrx,h,w)== true ){
					cout <<"Problem solved"<<endl<<"Total number of moves: "<< *movecounter <<endl;					
					}				
				print(mtrx,x,y,h,w);
				}
				
			else{ cout <<"\n you CAN'T use this move,NOT VALID\n";   }
		}
		else if(secim=='R' || secim=='r' ){
			if(*x<w-1 && *y<h && mtrx[*y][*x+1] != 0){
				temp=mtrx[*y][*x];
				mtrx[*y][*x]=mtrx[*y][*x+1];
				mtrx[*y][*x+1]=temp;
				*x=*x+1;				
				*movecounter=*movecounter+1;			
				if(isSolved(goalmtrx,mtrx,h,w)== true){
					cout <<"Problem solved"<<endl<<"Total number of moves: "<< *movecounter <<endl;					
					}				
				print(mtrx,x,y,h,w);
				}

			 else{ cout <<"\n you CAN'T use this move,NOT VALID\n";   }

		}
		else if(secim=='U' || secim=='u' ){

			if(*x>=0 && *y>0 && mtrx[*y-1][*x] != 0){
				temp=mtrx[*y][*x];
				mtrx[*y][*x]=mtrx[*y-1][*x];
				mtrx[*y-1][*x]=temp;
				*y=*y-1;				
				*movecounter=*movecounter+1;				
				if(isSolved(goalmtrx,mtrx,h,w)== true){
					cout <<"Problem solved"<<endl<<"Total number of moves: " << *movecounter <<endl;
					}
				print(mtrx,x,y,h,w);				
				}
			
			else{ cout <<"\n you CAN'T use this move,NOT VALID\n";   }

		}

		else if(secim=='D' || secim=='d' ){
			if(*x>=0 && *y<h-1 && mtrx[*y+1][*x] != 0){
				temp=mtrx[*y][*x];
				mtrx[*y][*x]=mtrx[*y+1][*x];
				mtrx[*y+1][*x]=temp;
				*y=*y+1;				
				*movecounter=*movecounter+1;			
			if(isSolved(goalmtrx,mtrx,h,w)== true){
				cout <<"Problem solved"<<endl<<"Total number of moves: " << *movecounter<<endl;
			}			
				print(mtrx,x,y,h,w);			
			}
		else{ cout <<"\n you CAN'T use this move,NOT VALID\n";   }

		}
}
void NPuzzle::solvePuzzle(int mtrx[][9],int goalmtrx[][9],const int height,const int width,int *x,int *y,int *movecounter,int *stuckcheck){
		NPuzzle a;
		NPuzzle::Board b;
		int movecheck=0;
		*stuckcheck=1;		
			cout<<"compare result "<<b.isSolved(goalmtrx,mtrx,height,width) <<endl;
			while(b.isSolved(goalmtrx,mtrx,height,width) != true){
								
	                       	moveIntelligent(mtrx,height,width,x,y,&movecheck,movecounter,stuckcheck);
				print(mtrx,x,y,height,width);
				
				if(*stuckcheck==1){//if intelligent stuck then we random it
				cout<<"stuckcheck="<<*stuckcheck<<endl;			
				int randnum=6,printcheck=1;
				moveRandom(mtrx,height,width,x,y,randnum,movecounter,printcheck);
				*stuckcheck=0;
				print(mtrx,x,y,height,width);
				cout<<"stuckcheck="<<*stuckcheck <<endl;
				}
				cout << "movecounter= "<<*movecounter<<endl;
			}
			if(b.isSolved(goalmtrx,mtrx,height,width)==true){
			cout <<"\nProblem solved"<<endl<<"Total number of moves: " << *movecounter <<endl;
			}

}


void NPuzzle::Board::menu(string namef,const int namecheck){
	NPuzzle f;
	int goalmtrx[9][9];//we will use it for comparing with mtrx
	int i,j,x,y,size,tempsize,movecounter=0,temp=0,movecheck=0,stuckcheck=0,height=0,width=0,randnum,o=0,resetcheck=0,movetemp=0;
	char secim;
	string smtrx[9][9];
	if(namecheck==1){//if user enter shapefile name
		f.readFromFile(smtrx,namef,&height,&width);
		for(i=0;i<height;i++){//converting string array to int array of board class and we use this other functions
			for(j=0;j<width;j++){
				if(smtrx[i][j] == "bb"){ 
						mtrx[i][j]= 99;	//we assign for bb option 
							}
				else   mtrx[i][j]=stoi(smtrx[i][j]);//string to int
			}	
		}
	}
	else {	f.setsize(mtrx,&height,&width);//if user didnt write commandline ,we fill manualy with setsize
		randnum=25;	
		}
		cout << "-----------------GOAL STATE-----------------\n\n";
		reset(mtrx,goalmtrx,height,width,resetcheck);
		f.print(goalmtrx,&x,&y,height,width);		
		cout << "--------------------------------------------\n\n";

		cout << "------------CURRENT CONFIGURATION-----------\n\n";
		if(namecheck==0){f.shuffle(mtrx,height,width,&x,&y,randnum,&movecounter);////if user didnt write commandline ,we shuffle it
		movecounter=0;			}
		f.print(mtrx,&x,&y,height,width);
		cout << "--------------------------------------------\n\n";
	
		
	while(1){
	      cout   <<"\nL moves the empty cell left if there is room\n"
		     <<"R moves the empty cell right if there is room\n"
	             <<"U moves the empty cell up if there is room\n"
          	     <<"D moves the empty cell down if there is room \n"
		     <<"I makes an 'intelligent' move for you.\n"
		     <<"S takes boards to final solution,and makes size*size random moves\n"
                     <<"V Solves the problem from the current configuration\n"
	      	     <<"T Prints a report about how many moves have been done \n"
		     <<"E Asks a file name and saves the current board configuration as a loadable shapefile\n"
		     <<"O Asks a file name and loads the current board configuration from the shapefile\n"
		     <<"Q Quits the game\n"
		     << "Please enter your CHOICE: " ; 

		cin  >> secim;
		cout << "\n";
		if( secim == 'L'  || secim == 'l' ){
                	f.move(mtrx,secim,height,width,&x,&y,&movecounter);}
		else if(secim=='R' || secim=='r' ){
			f.move(mtrx,secim,height,width,&x,&y,&movecounter);}
		
		else if(secim=='U' || secim=='u' ){
			f.move(mtrx,secim,height,width,&x,&y,&movecounter);}

		else if(secim=='D' || secim=='d' ){
			f.move(mtrx,secim,height,width,&x,&y,&movecounter);}

		else if(secim=='I' || secim=='i' ){
		  if(isSolved(goalmtrx,mtrx,height,width) == false){
			f.moveIntelligent(mtrx,height,width,&x,&y,&movecheck,&movecounter,&stuckcheck);
			if(isSolved(goalmtrx,mtrx,height,width) == true){
			cout <<"Problem solved"<<endl<<"Total number of moves: " << movecounter <<endl;
			}			
			f.print(mtrx,&x,&y,height,width);			
		    }
		   else
			cout <<"Problem solved,You don't need intelligent move"<<endl<<"Total number of moves: " << movecounter <<endl;		
		}

		else if(secim=='S' || secim=='s' ){
			movetemp=movecounter;
			resetcheck=1;//we change main mtrx with goalmtrx
			reset(mtrx,goalmtrx,height,width,resetcheck);				
			cout << "-----------------GOAL STATE-----------------\n\n";
			f.print(mtrx,&x,&y,height,width);		
			randnum=height*width;
			f.shuffle(mtrx,height,width,&x,&y,randnum,&movecounter);
			cout << "\n-----------------SHUFFLED STATE-----------------\n\n";
			f.print(mtrx,&x,&y,height,width);
			movecounter=movetemp;//shuffle dont changes the movecounter
			cout<<"\n  shuffled height*width  = "<< height*width<<" times moves "<<endl;
		}
		else if( secim == 'V'  || secim == 'v'){
			f.solvePuzzle(mtrx,goalmtrx,height,width,&x,&y,&movecounter,&stuckcheck);}
		
		else if(secim=='T' || secim=='t' ){
		cout << "Total number of moves: " << movecounter <<endl;}

		else if(secim=='E' || secim=='e' ){
			cout << "enter the name of the file : ";
			cin >> namef;

			f.writeToFile(mtrx,namef,x,y,height,width);
			}

		else if(secim=='O' || secim=='o' ){
			cout << "enter the name of the file : ";
			cin >> namef;
			f.readFromFile(smtrx,namef,&height,&width);			
			for(i=0;i<height;i++){//converting string array to int array
				for(j=0;j<width;j++){
					if(smtrx[i][j] == "bb"){ 
						mtrx[i][j]= 99;		
							}
				else   mtrx[i][j]=stoi(smtrx[i][j]);
			}	
		    }
			f.print(mtrx,&x,&y,height,width);
			resetcheck=0;
			reset(mtrx,goalmtrx,height,width,resetcheck);
		}

		else if(secim == 'Q' || secim == 'q'){
		cout <<"exiting,bye";
		return ;
		}

		else{
		cout << "WRONG choice my friend,try AGAIN\n";
		}
	}//while curl

}//menu curl
