import numpy as np
import random
import time

class Bingo:
    def __init__(self, length=5):
        self.length = length
        self.size = length * length
        self.bingo_list = self.generate_bingo_list()

    def generate_bingo_list(self):
        bingo_temp = np.arange(1, self.size + 1)
        np.random.shuffle(bingo_temp)
        return bingo_temp.reshape(self.length, self.length)

    def print_bingo(self):
        for row in self.bingo_list:
            for num in row:
                print("X" if num == -1 else num, end="\t")
            print()

    def bingo_number(self, number):
        self.bingo_list[self.bingo_list == number] = -1

    def is_bingo(self):
        for i in range(self.length):
            if np.all(self.bingo_list[i, :] == -1) or np.all(self.bingo_list[:, i] == -1):
                return True

        if np.all(np.diag(self.bingo_list) == -1) or np.all(np.diag(np.fliplr(self.bingo_list)) == -1):
            return True

        return False

def get_user_input(size, input_record):
    while True:
        try:
            number = int(input("Input a number: "))
            if number < 0 or number > size:
                raise ValueError
            if number in input_record:
                raise ValueError("Repeated number, please input again")
            return number
        except ValueError as e:
            print(e)


def main():
    np.random.seed(int(time.time()))
    print("Start the bingo game\nYou can enter 0 to end the game")
    bingo = Bingo()
    input_record = set()

    while True:
        bingo.print_bingo()
        start_time = time.time()
        user_input = get_user_input(bingo.size, input_record)

        if user_input == 0:
            print("Game is end")
            break

        input_record.add(user_input)
        bingo.bingo_number(user_input)
        if bingo.is_bingo():
            print("You win")
            break

        end_time = time.time()
        print(f"Time taken by function: {(end_time - start_time) * 1000000} microseconds")

if __name__ == "__main__":
    main()
