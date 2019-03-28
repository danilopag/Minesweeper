import cppyy
cppyy.include("campo_minato.cpp")
from cppyy.gbl import Campo_minato

from boardgame_g2d import BoardGameGui

righe=1
colonne=1
mine=0

print("CAMPO MINATO")
while righe<=1:
    righe=int(input("Inserisci il numero delle righe della matrice: ")) 

while colonne<=1:
    colonne=int(input("Inserisci il numero delle colonne della matrice: ")) 

while mine<=0 or mine>(righe*colonne):
    mine=int(input("Inserisci il numero di mine da inserire nella matrice:")) 

game = Campo_minato(righe,colonne,mine)
gui = BoardGameGui(game)
gui.main_loop()
