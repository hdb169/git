# read two columns from a text file having just the numbers and plot one vs the other:
#dated sept, 10, 2019

import matplotlib.pyplot as plt
f = open("read_columns.txt")
lines = f.readlines()

x,y = zip(*(line.split() for line in lines))

f.close()

print (x,y)

plt.plot(x,y)

plt.show()
