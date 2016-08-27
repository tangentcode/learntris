from tkinter import *
import string, random
import testris

COLORS = {"m": "#f0f", # magenta
          "y": "#ff0", # yellow
          "c": "#0ff", # cyan
          "o": "#ffa500", # orange
          "r": "#f00", # red
          "g": "#0f0", # green
          "b": "#00f", # blue
          ".": "#000"} # black

TILE_SIZE = 16
BOARD_WIDTH = 10
BOARD_HEIGHT = 22

CANVAS_WIDTH = BOARD_WIDTH * TILE_SIZE
CANVAS_HEIGHT = BOARD_HEIGHT * TILE_SIZE

def has_active_tetramino(matrix):
    # active tetraminos are denoted by uppercase letters
    # in the learntris output matrix (given by 'P').

    return any(any(c in string.ascii_uppercase for c in row) for row in matrix)

class Game(Frame):
    def __init__(self, parent, process):
        super().__init__(parent)
        self.parent = parent
        self.process = process

        self.init_ui()

        self.emit("T")
        self.redraw()
        
    def init_ui(self):
        self.parent.title("Learntris")
        self.pack(fill=BOTH, expand=1)

        self.canvas = Canvas(self)
        self.canvas.pack(fill=BOTH, expand=1)

        self.bind_all("<Key>", self.key_pressed)

    def read_row(self):
        # read and parse a single row from a matrix
        return self.process.stdout.readline().decode("utf-8").rstrip().split(" ")

    def get_matrix(self):
        # obtain the current matrix from learntris
        self.emit("P", update_ui=False)
        return [self.read_row() for _ in range(22)]

    def redraw(self):
        self.canvas.delete(ALL) # clear the canvas
        self.draw_matrix(self.update())

    def update(self):
        matrix = self.get_matrix()

        if not has_active_tetramino(matrix):
            # emit a random tetramino, then re-fetch the matrix
            self.emit(random.choice("IOZSJLT"), update_ui=False)
            matrix = self.get_matrix()

        return matrix

    def emit(self, command, update_ui=True):
        print(">", command)

        # send command to the learntris process
        self.process.stdin.write(bytes(command + "\n", "utf-8"))
        self.process.stdin.flush()

        if update_ui:
            # update the UI
            self.redraw()

    def key_pressed(self, event):
        key = event.keysym

        key_map = {"Left": "<",
                   "Right": ">",
                   "Down": "v",
                   "Up": "V",
                   "r": ")",
                   "Escape": "!"}

        if key in key_map:
            self.emit(key_map[key])

    def draw_matrix(self, matrix):
        for y,row in enumerate(matrix):
            for x,t in enumerate(row):
                x_pos = x*TILE_SIZE
                y_pos = y*TILE_SIZE
                self.canvas.create_rectangle(x_pos, y_pos, x_pos+TILE_SIZE, y_pos+TILE_SIZE,
                                             fill=COLORS[t.lower()], width=1)

def main():
    # spawn the learntris program
    program_args, use_shell = testris.find_learntris()
    process = testris.spawn(program_args, use_shell)

    # set up the GUI, hand off the process to it
    root = Tk()
    game = Game(root, process)
    root.geometry("%dx%d" % (CANVAS_WIDTH, CANVAS_HEIGHT))
    root.mainloop()

if __name__ == "__main__":
    main()