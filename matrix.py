import sys
import numpy
import time

A = []
A_rows = 0
A_cols = 0

B = []
B_rows = 0
B_cols = 0

with open('./tests/input/test04.txt', "r") as file:

    lines = file.readlines()

    # matrix A
    line = lines.pop(0)

    A_rows = int(line.split()[0])
    A_cols = int(line.split()[1])

    for r in range(0, A_rows):
        line = lines.pop(0)
        lst = []
        for el in line.split():
            lst.append(int(el))
        A.append(lst)

    # matrix B
    line = lines.pop(0)

    B_rows = int(line.split()[0])
    B_cols = int(line.split()[1])

    for r in range(0, B_rows):
        line = lines.pop(0)
        lst = []
        for el in line.split():
            lst.append(int(el))
        B.append(lst)

npA = numpy.array(A).astype(numpy.int32)
npB = numpy.array(B).astype(numpy.int32)

start = time.process_time()

try:
    npAB = numpy.matmul(npA, npB)
except:
    pass

print(time.process_time() - start)

print(str(npAB.shape[0]) + " " + str(npAB.shape[1]))
for r in npAB:
    for c in r:
        sys.stdout.write(str(c) + " ")
    print("")
