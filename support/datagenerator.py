import numpy as np
import nnfs
import os
from nnfs.datasets import spiral_data

X,y  = spiral_data(samples =100, classes = 3);

X_data_file = "xData.txt"
y_data_file = "yData.txt"


if os.path.exists(X_data_file):
    print("removing existing x datafile")
    os.remove(X_data_file)


if os.path.exists(y_data_file):
    print("removing existing y datafile")
    os.remove(y_data_file)


print("creating new data...")
with open(X_data_file, "w") as file:
    data_string = ""
    for sample in X:
        l = f"{sample[0]},{sample[1]}\n"
        data_string+=l

    file.write(data_string)
file.close()


with open(y_data_file, "w") as file:
    data_string = ""
    for y_true in y:
        data_string+=f"{y_true},"

    file.write(data_string)

file.close()