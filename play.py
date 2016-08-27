from tkinter import *

COLORS = {"m": "#f0f",
          "y": "#ff0",
          "c": "#0ff",
          "o": "#ffa500",
          "r": "#f00",
          ".": "#000"}

TILE_SIZE = 16
BOARD_WIDTH = 10
BOARD_HEIGHT = 22

CANVAS_WIDTH = BOARD_WIDTH * TILE_SIZE
CANVAS_HEIGHT = BOARD_HEIGHT * TILE_SIZE

TEST_MATRIX = [row.split() for row in \
[". . . . . . . . . .",
 ". . . . . . . . . .",
 ". . . . . . . . . .",
 ". . . . . . . . . .",
 ". . . . . . . . . .",
 ". . . . . . . . . .",
 ". . . . . . . . . .",
 ". . . . . . . . . .",
 ". . . . . . . . . .",
 ". . . . . . . . . .",
 ". . . . . . . . . .",
 ". . . . . . . . . .",
 ". . . . . . . . . .",
 ". . . . . . . . . .",
 ". . . . . y y . . .",
 ". . . . . y y . . .",
 ". . . . . . m . . .",
 ". . . . . . m m . .",
 ". . . . . . m c . .",
 ". . . . . . . c . .",
 ". . . . . . . c . .",
 ". . . . . . . c . ."]]

class Game(Frame):
    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent
        self.init_ui()
        
    def init_ui(self):
        self.parent.title("Learntris")
        self.pack(fill=BOTH, expand=1)

        self.canvas = Canvas(self)
        self.canvas.pack(fill=BOTH, expand=1)

        matrix = ['mmmyyy', 'ccyooo', 'rrrrrr']
        self.draw_matrix(TEST_MATRIX)

    def draw_matrix(self, matrix):
        for y,row in enumerate(matrix):
            for x,t in enumerate(row):
                x_pos = x*TILE_SIZE
                y_pos = y*TILE_SIZE
                self.canvas.create_rectangle(x_pos, y_pos, x_pos+TILE_SIZE, y_pos+TILE_SIZE,
                                             fill=COLORS[t], width=1)

def main():
    root = Tk()
    game = Game(root)
    root.geometry("%dx%d" % (CANVAS_WIDTH, CANVAS_HEIGHT))
    root.mainloop()

if __name__ == "__main__":
    main()