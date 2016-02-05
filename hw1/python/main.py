import random
import time
import timeit

from datastructure import Datastructure

# Constants for commands
READ = "R"        # reads score data given file
PRINT = "P"       # Prints score data from best to worst
ALPHA = "A"       # Prints score data alphabetically
MAXMIN = "X"      # Prints the best or the worst score
ADD = "D"         # Adds a new player
EMPTY = "E"       # Empties the datastructure
SEARCH = "S"      # Searches for the given usen
QUIT = "Q"        # Exits the program

GENERATE = 'G'    # Generates a given amount of data
EFFICIENCY = 'F'  # Tests efficiency
TEST = 'T'        # Tests a lot of stuff

# Other constants
BEST = "best"     # For MINMAX
WORST = "worst"   # For MINMAX

# Error messages
E_FILE_NOT_FOUND = 'Error: file not found'
E_INT_EXPECTED = 'Error: bus count and passenger count must be integers'

# User interface
PROMPT = '> '
SEPARATOR = ' '


def generate(datastructure, amount):
    for i in range(amount):
        ran = '%018x' % random.randrange(16**18)
        nickname = ran[8:]
        bus_count = random.randint(0, 2000)
        passenger_count = random.randint(0, bus_count * 100)
        datastructure.add(nickname, bus_count, passenger_count)


def efficiency_test(datastructure, amount):
    # Generate first, because python is slow to generate random data
    generate(datastructure, amount)

    start = time.time()
    datastructure.print()
    datastructure.best()
    datastructure.worst()
    datastructure.print()
    datastructure.print()
    datastructure.print()
    datastructure.print()
    datastructure.print()
    datastructure.print()
    datastructure.print()
    end = time.time()
    print("{0:f}".format(end - start))


def test(datastructure, test_range=30):
    datastructure.empty()

    def test_print(datastructure):
        generate(datastructure, 1)
        datastructure.print()

    with open("sort.dat", 'w', encoding="utf-8") as output_file:
        output_file.write("#x y\n")

        for j in range(test_range):
            generate(datastructure, 250)
            t = timeit.Timer(lambda: test_print(datastructure), 'gc.enable()')
            sum_ = t.timeit(number=5) / 5
            size = datastructure.size()
            output_file.write("{0:d} {1:f}\n".format(size, sum_))
        datastructure.empty()

    def test_add(datastructure):
        generate(datastructure, 10)

    def test_best(datastructure):
        generate(datastructure, 1)
        datastructure.best()

    def test_worst(datastructure):
        generate(datastructure, 1)
        datastructure.worst()

    add_file = open('add.dat', 'w', encoding="utf-8")
    add_file.write("#x y\n")
    best_file = open('best.dat', 'w', encoding="utf-8")
    best_file.write("#x y\n")
    worst_file = open('young.dat', 'w', encoding="utf-8")
    worst_file.write("#x y\n")

    t1 = timeit.Timer(lambda: generate(datastructure, 10), 'gc.enable()')
    t2 = timeit.Timer(lambda: test_best(datastructure), 'gc.enable()')
    t3 = timeit.Timer(lambda: test_worst(datastructure), 'gc.enable()')
    for j in range(test_range):
        generate(datastructure, 250)
        add_sum = 0.0
        best_sum = 0.0
        worst_sum = 0.0
        for i in range(5):
            add_sum += t1.timeit(number=1)
            best_sum += t2.timeit(number=1)
            worst_sum += t3.timeit(number=1)
        size = datastructure.size()
        add_file.write("{0:d} {1:f}\n".format(size, add_sum / 5))
        best_file.write("{0:d} {1:f}\n".format(size, best_sum / 5))
        worst_file.write("{0:d} {1:f}\n".format(size, worst_sum / 5))
    add_file.close()
    best_file.close()
    worst_file.close()

    datastructure.empty()

    del_file = open('del.dat', 'w', encoding="utf-8")
    del_file.write("#x y\n")
    t4 = timeit.Timer(lambda: datastructure.empty())
    for j in range(1, test_range + 1):
        generate(datastructure, j*250)
        size = datastructure.size()
        sum_ = t4.timeit(number=5) / 5
        del_file.write("{0:d} {1:f}\n".format(size, sum_))
    del_file.close()

    datastructure.empty()


def readfile(filename, datastructure):
    try:
        input_file = open(filename, "r", encoding="utf-8")
        for line in input_file:
            input_line = line.strip("\n").split(";")

            # Skip invalid data
            if len(input_line) != 3:
                continue

            nickname = input_line[0]
            bus_count = int(input_line[1])
            passenger_count = int(input_line[2])

            datastructure.add(nickname, bus_count, passenger_count)

    except IOError:
        print(E_FILE_NOT_FOUND)
        return
    except ValueError:
        print(E_INT_EXPECTED)
        return


def main():
    ds = Datastructure()
    input_line = ""
    command = ""
    while command != QUIT:

        input_line = input(PROMPT).split()
        if len(input_line) == 0:
            continue

        command = input_line[0]

        if command == READ and len(input_line) == 2:
            filename = input_line[1]
            print(command, filename, sep=SEPARATOR)
            readfile(filename, ds)

        elif command == PRINT:
            print(command, sep=SEPARATOR)
            ds.print()

        elif command == ALPHA:
            print(command, sep=SEPARATOR)
            ds.print_by_name()

        elif command == MAXMIN and len(input_line) == 2:
            parameter = input_line[1]
            print(command, parameter, sep=SEPARATOR)
            if parameter == BEST:
                ds.best()
            if parameter == WORST:
                ds.worst()

        if command == SEARCH and len(input_line) > 1:
            name = " ".join(input_line[1:])
            print(command, name, sep=SEPARATOR)
            ds.search(name)

        if command == EMPTY:
            print(command, sep=SEPARATOR)
            ds.empty()

        if command == ADD and len(input_line) > 1:
            info = " ".join(input_line[1:]).split(";")
            print(command, info[0], info[1], info[2])
            try:
                ds.add(info[0], int(info[1]), int(info[2]))
            except ValueError:
                print(E_INT_EXPECTED)

        if command == GENERATE and len(input_line) == 2:
            amount = int(input_line[1])
            generate(ds, amount)

        if command == EFFICIENCY and len(input_line) == 2:
            amount = int(input_line[1])
            efficiency_test(ds, amount)

        if command == TEST:
            if len(input_line) == 2:
                count = int(input_line[1])
            else:
                count = 30
            test(ds, count)
    print(command, sep=SEPARATOR)



main()