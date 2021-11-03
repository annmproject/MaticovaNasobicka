filename1 = "output.txt"
filename2 = "output1.txt"

with open(filename1) as f1:
    with open(filename2) as f2:
        if f1.read() == f2.read():
            print("jsou stejne")
        else:
            print("stejne")

