#include "campo_minato.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

Campo_minato::Campo_minato(int r, int c, int m){
    righe=r;
    colonne=c;
    mine=m;
    matricepos.assign(r,vector<int>(c,0));
    matricegioco.assign(r,vector<int>(c,0));
    finish=false;
    val=0;
    initmine();
}

int Campo_minato::get_valpos(int x, int y){
    return matricepos[x][y];
}

int Campo_minato::get_val(int x, int y){
    return matricegioco[x][y];
}

void Campo_minato::flag_at(int x,int y){
    if(x>=0 && y>=0 && x<righe && y<colonne){
        if(matricepos[x][y]==0){
        	matricepos[x][y]=2;
        }else{
		if(matricepos[x][y]==2){
			matricepos[x][y]=0;
		}else{
			int countb=0; //conta le bandierine presenti
			int countc=0; //conta le casella giocabili presenti
			//controllo caselle
			if(x>0 && y>0 && matricepos[x-1][y-1]==0){ //Controllo sulla colonna nella posizione y-1
		            countc++;
		        }
		        if(y>0 && matricepos[x][y-1]==0){
		            countc++;
		        }
		        if(x<righe-1 && y>0 && matricepos[x+1][y-1]==0){
		            countc++;
		        }
		        if(x>0 && matricepos[x-1][y]==0){ //Controllo sulla colonna nella posizione y
		            countc++;
		        }
		        if(x<righe-1 && matricepos[x+1][y]==0){
		            countc++;
		        }
		        if(x>0 && y<colonne-1 && matricepos[x-1][y+1]==0){ //Controllo sulla colonna nella posizione y+1
		            countc++;
		        }
		        if(y<colonne-1 && matricepos[x][y+1]==0){
		            countc++;
		        }
		        if(x<righe-1 && y<colonne-1 && matricepos[x+1][y+1]==0){
		            countc++;
		        }
			//controllo bandiere
			if(x>0 && y>0 && matricepos[x-1][y-1]==2){ //Controllo sulla colonna nella posizione y-1
		            countb++;
		        }
		        if(y>0 && matricepos[x][y-1]==2){
		            countb++;
		        }
		        if(x<righe-1 && y>0 && matricepos[x+1][y-1]==2){
		            countb++;
		        }
		        if(x>0 && matricepos[x-1][y]==2){ //Controllo sulla colonna nella posizione y
		            countb++;
		        }
		        if(x<righe-1 && matricepos[x+1][y]==2){
		            countb++;
		        }
		        if(x>0 && y<colonne-1 && matricepos[x-1][y+1]==2){ //Controllo sulla colonna nella posizione y+1
		            countb++;
		        }
		        if(y<colonne-1 && matricepos[x][y+1]==2){
		            countb++;
		        }
		        if(x<righe-1 && y<colonne-1 && matricepos[x+1][y+1]==2){
		            countb++;
		        }
			if(matricegioco[x][y]==countb){
				play_at(x-1,y-1);
		                play_at(x-1,y);
		                play_at(x-1,y+1);
		                play_at(x,y-1);
		                play_at(x,y+1);
		                play_at(x+1,y-1);
		                play_at(x+1,y);
		                play_at(x+1,y+1);
			}else{
				if((matricegioco[x][y]-countb)==countc){
		                       if(x>0 && y>0 && matricepos[x-1][y-1]==0){
						flag_at(x-1,y-1);
					}
					if(x>0 && matricepos[x-1][y]==0){
				        	flag_at(x-1,y);
					}
					if(x>0 && y<colonne-1 && matricepos[x-1][y+1]==0){
				        	flag_at(x-1,y+1);
					}
					if(y>0 && matricepos[x][y-1]==0){
				        	flag_at(x,y-1);
					}
					if(y<colonne-1 && matricepos[x][y+1]==0){
				        	flag_at(x,y+1);
					}
					if(x<righe-1 && y>0 && matricepos[x+1][y-1]==0){
				        	flag_at(x+1,y-1);
					}
					if(x<righe-1 && matricepos[x+1][y]==0){
				        	flag_at(x+1,y);
					}
					if(x<righe-1 && y<colonne-1 && matricepos[x+1][y+1]==0){
				        	flag_at(x+1,y+1);
					}
				}
			}
		}
    }
    int fine=0; //indice la fine del gioco
    int fine1=0; //indice bandierina
    for(unsigned int i=0;i<righe;i++){
        for(unsigned int c=0;c<colonne;c++){
            if(matricepos[i][c]==1){
                fine++;
            }
        }
    }
    if(fine==((righe*colonne)-mine)){
            finish=true;
    }
}
}

void Campo_minato::play_at(int x, int y){
    int countm=0; //count mine
    if(x>=0 && y>=0 && x<righe && y<colonne){
        if(matricepos[x][y]==0){
        matricepos[x][y]=1;
        if(matricegioco[x][y]!=-1){
                if(x>0 && y>0 && matricegioco[x-1][y-1]==-1){ //Controllo sulla colonna nella posizione y-1
                    countm++;
                }
                if(y>0 && matricegioco[x][y-1]==-1){
                    countm++;
                }
                if(x<righe-1 && y>0 && matricegioco[x+1][y-1]==-1){
                    countm++;
                }
                if(x>0 && matricegioco[x-1][y]==-1){ //Controllo sulla colonna nella posizione y
                    countm++;
                }
                if(x<righe-1 && matricegioco[x+1][y]==-1){
                    countm++;
                }
                if(x>0 && y<colonne-1 && matricegioco[x-1][y+1]==-1){ //Controllo sulla colonna nella posizione y+1
                    countm++;
                }
                if(y<colonne-1 && matricegioco[x][y+1]==-1){
                    countm++;
                }
                if(x<righe-1 && y<colonne-1 && matricegioco[x+1][y+1]==-1){
                    countm++;
                }
                matricegioco[x][y]=countm;
            if(countm==0){
                        play_at(x-1,y-1);
                        play_at(x-1,y);
                        play_at(x-1,y+1);
                        play_at(x,y-1);
                        play_at(x,y+1);
                        play_at(x+1,y-1);
                        play_at(x+1,y);
                        play_at(x+1,y+1);
            }
            }else{
                finish=true;
                val=matricegioco[x][y];
            }
        }
    }
    int fine=0; //indice la fine del gioco
    for(unsigned int i=0;i<righe;i++){
        for(unsigned int c=0;c<colonne;c++){
            if(matricepos[i][c]==1){
                fine++;
            }
        }
    }
    if(fine==((righe*colonne)-mine)){
            finish=true;
    }
}

void Campo_minato::initmine(){
    int k=0, j=0;
    srand (time(NULL));
    for(unsigned int i=0;i<mine;i++){
        k= rand() % (righe-1);
        j= rand() % (colonne-1);
        if(matricegioco[k][j]==0){
            matricegioco[k][j]=-1;
        }else{
            i=i-1;
        }
    }
}

int Campo_minato::cols(){
    return colonne;
}

int Campo_minato::rows(){
    return righe;
}

int Campo_minato::mines(){
    return mine;
}

bool Campo_minato::finished(){
    if(finish==true){
        return true;
    } else {
        return false;
    }
}

std::string Campo_minato::message(){
    if(val == -1){
        return "GAME OVER";
    }else{
        return "HAI VINTO";
    }
}
