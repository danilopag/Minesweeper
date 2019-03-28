#ifndef CAMPO_MINATO_H
#define CAMPO_MINATO_H
#include <iostream>
#include <vector>
#include <string>
#include "boardgame.h"

using namespace std;

class Campo_minato : public BoardGame{
    public:
        Campo_minato(int r, int c, int m);
        int get_val(int x, int y);
	int get_valpos(int x, int y);
        void play_at(int x, int y);
        void flag_at(int x,int y);
        void stampamatrice();
        int cols();
        int rows();
	int mines();
        bool finished();
        std::string message();
        void initmine(); // inizializza le mine nella matrice gioco
    protected:
    private:
        int righe;
        int colonne;
        int mine;
        vector <vector <int> > matricepos; //matrice posizione mine
        vector <vector <int> > matricegioco; //matrice di gioco
        bool finish;
	int val;
};

#endif // CAMPO_MINATO_H

