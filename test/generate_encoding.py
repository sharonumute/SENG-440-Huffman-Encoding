import random

l = list(range(128))

random.shuffle(l)

codes_str = []
for i in range(128):
    codes_str.append([])
    for j in range(i-1):
        codes_str[i] += [1]
    codes_str[i] += [0]

#print(codes_str)

codes = list(range(128))

for i in range(128):
    print("{"+str(l[i])+", "+str(i)+"},", end=' ')


