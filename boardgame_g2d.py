import g2d
from time import time

import cppyy
cppyy.include("boardgame.h")
from cppyy.gbl import BoardGame

W, H = 40, 40
LONG_PRESS = 0.5

flag1=g2d.load_image("flag.png")
bomb=g2d.load_image("bomb.png")

class BoardGameGui:
    def __init__(self, g: BoardGame):
        self._game = g
        self._downtime = 0
        g2d.init_canvas(((g.cols() * W)+250, g.rows() * H))
        self.update_buttons()
        g2d.handle_mouse(self.mousedown, self.mouseup)

    def main_loop(self):
        g2d.main_loop()

    def mousedown(self, pos, button):
        self._downtime = time()

    def mouseup(self, pos, button):
        x, y = pos[0] // W, pos[1] // H
        if time() - self._downtime > LONG_PRESS:
            self._game.flag_at(y, x)
        else:
            self._game.play_at(y, x)
        self.update_buttons()

    def update_buttons(self):
        g2d.fill_canvas((255, 255, 255))
        rows, cols , flag= self._game.rows(), self._game.cols(), 0
        cellevuote=0
        for y in range(1, rows):
            g2d.draw_line((0, 0, 0), (0, y * H), (cols * W, y * H))
        for x in range(1, cols+1):
            g2d.draw_line((0, 0, 0), (x * W, 0), (x * W, rows * H))
        for y in range(rows):
            for x in range(cols):
                if (self._game.get_valpos(y, x)==0):
                    g2d.draw_text_centered(" ", (0, 0, 0),(x * W + W//2, y * H + H//2), H//2)
                    cellevuote=cellevuote+1
                elif (self._game.get_valpos(y, x)==2):
                    g2d.draw_image(flag1,(x * W + W//8, y * H + H//8))
                    #g2d.draw_text_centered("<|", (0, 0, 0),(x * W + W//2, y * H + H//2), H//2)
                    flag=flag+1
                elif (self._game.get_val(y, x)==-1):
                    g2d.draw_image(bomb,(x * W + W//8, y * H + H//8))
                else:
                    g2d.draw_text_centered(str(self._game.get_val(y, x)), (0, 0, 0),(x * W + W//2, y * H + H//2), H//2)
        g2d.draw_text_centered("MINE RIMANENTI DA SEGNALARE",(0,0,0),((x*W)+160,H//2), H//2)
        g2d.draw_text_centered(str(self._game.mines()-flag),(0,0,0),((x*W)+160,H), H//2)
        g2d.draw_text_centered("CELLE VUOTE RIMANENTI",(0,0,0),((x*W)+160,H*2), H//2)
        g2d.draw_text_centered(str((cellevuote+flag)-self._game.mines()),(0,0,0),((x*W)+160,H*3), H//2)
        g2d.update_canvas()
        if (self._game.finished()==True):
            g2d.alert(self._game.message())
            g2d.exit()
            g2d.draw_text_centered(self._game.message(), (0, 0, 255),(cols * W//2, rows * H//2), H//2)
