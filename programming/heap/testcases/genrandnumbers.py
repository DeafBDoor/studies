import random

with open("./randnumbers", "w") as f:
    vec = []
    for i in xrange(100):
        vec.append(random.getrandbits(32))

    vec.sort()

    for i in vec:
        f.write(str(i) + "\n")
