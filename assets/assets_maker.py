import os
class Direction:
    NONE = 0
    UP = 1
    DOWN = 2
    LEFT = 3
    RIGHT = 4

class WallAngleType:
    NONE = 0
    START = 1
    END = 2
    BOTH = 3

class Walls:
    def __init__(self, x, y, direction, length, angle_type):
        self.x = x
        self.y = y
        self.direction = direction
        self.length = length
        self.angle_type = angle_type
        # debug print all info
        # print("x: " + str(self.x))
        # print("y: " + str(self.y))
        # print("direction: " + str(self.direction))
        # print("length: " + str(self.length))
        # print("angle_type: " + str(self.angle_type))
    def draw(self, board):
        x_adder = 0 
        y_adder = 0
        print_char = '#'

        if self.direction == Direction.UP:
            x_adder = -1
            print_char = '|'
        elif self.direction == Direction.DOWN:
            x_adder = 1
            print_char = '|'
        elif self.direction == Direction.LEFT:
            y_adder = -1
            print_char = '-'
        elif self.direction == Direction.RIGHT:
            y_adder = 1
            print_char = '-'


        for i in range(self.length):
            board[self.x + x_adder * i][self.y + y_adder * i] = print_char 

            if i == 0 and (self.angle_type & 1):
                board[self.x + x_adder * i][self.y + y_adder * i] = '+'
            elif i == self.length - 1 and (self.angle_type & 2):
                board[self.x + x_adder * i][self.y + y_adder * i] = '+'

class DoorSegment:
    def __init__(self, x, y, direction, length, px = -1, py = -1):
        self.x = x
        self.y = y
        self.direction = direction
        self.length = length
        self.px = px
        self.py = py

    def draw(self, board):
        x_adder = 0 
        y_adder = 0
        print_char = 'X'

        if self.direction == Direction.UP:
            x_adder = -1
        elif self.direction == Direction.DOWN:
            x_adder = 1
        elif self.direction == Direction.LEFT:
            y_adder = -1
        elif self.direction == Direction.RIGHT:
            y_adder = 1

        for i in range(self.length):
            board[self.x + x_adder * i][self.y + y_adder * i] = print_char

        if self.px != -1 and self.py != -1:
            board[self.px][self.py] = 'P'

class Artifacts: 
    def __init__(self, x, y, life):
        self.x = x
        self.y = y
        self.life = life

    def draw(self, board):
        board[self.x][self.y] = 'A'

class Enemy: 
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def draw(self, board):
        board[self.x][self.y] = 'E'

class Power: 
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def draw(self, board):
        board[self.x][self.y] = 'C'

def get_files(path: str):
    """
    Get all files in a directory
    """
    return [f for f in os.listdir(path) if os.path.isfile(os.path.join(path, f))]

def handle_print(file: str):
    """
    Prints the contents of a file
    """
    with open(file, "r") as f:
        board = [[' ' for x in range(60)] for y in range(17)]

        n_walls = int(f.readline())  
        print(f"{file} has {n_walls} walls") 
        stuff_to_print = []
        for i in range(n_walls):
            line = f.readline()
            line = line.split()
            stuff_to_print.append(Walls(int(line[0]), int(line[1]), int(line[2]), int(line[3]), int(line[4])))
        
        n_doors = int(f.readline())
        print(f"{file} has {n_doors} doors")
        for i in range(n_doors):
            line = f.readline()
            line = line.split()
            stuff_to_print.append(DoorSegment(int(line[0]), int(line[1]), int(line[2]), int(line[3]), int(line[5]), int(line[6])))
        
        n_local_doors = int(f.readline())
        print(f"{file} has {n_local_doors} local doors")
        for i in range(n_local_doors):
            line = f.readline()
            line = line.split()
            stuff_to_print.append(DoorSegment(int(line[0]), int(line[1]), int(line[2]), int(line[3])))

        n_artifacts = int(f.readline())
        print(f"{file} has {n_artifacts} artifacts")
        for i in range(n_artifacts):
            line = f.readline()
            line = line.split()
            stuff_to_print.append(Artifacts(int(line[0]), int(line[1]), int(line[2])))

        n_power = int(f.readline())
        print(f"{file} has {n_power} power")
        for i in range(n_power):
            line = f.readline()
            line = line.split()
            stuff_to_print.append(Power(int(line[0]), int(line[1])))

        n_enemy = int(f.readline())
        print(f"{file} has {n_enemy} enemy")
        for i in range(n_enemy):
            line = f.readline()
            line = line.split()
            stuff_to_print.append(Enemy(int(line[0]), int(line[1])))


    for i in stuff_to_print:
        i.draw(board)

    # change extension of file to map 
    file = file.split('.')
    file = file[0] + '.map'
    with open(file, "w") as f:
        for i in board:
            for j in i:
                f.write(j)
            f.write('\n')

def main():
    files = get_files("./")  
    files = [f for f in files if f.endswith(".txt")] # get all txt files 

    for file in files:
        print(f"elaborato il file {file}")
        handle_print(file)

    pass 


if __name__ == "__main__":
    main() 