import random

# we specified head and tail of a coin in string
values = [
    23, 113, 96, 73, 1, 82, 54, 93, 37, 116, 88, 
    39, 6, 55, 46, 7, 19, 49, 66, 64, 104, 45, 21, 
    120, 20, 61, 76, 106, 102, 81, 34, 62, 14, 99, 
    22, 84, 71, 77, 58, 17, 124, 126, 27, 117, 41, 
    97, 12, 4, 32, 38, 13, 25, 83, 101, 9, 28, 85, 
    24, 95, 57, 18, 3, 92, 48, 50, 86, 79, 91, 103, 
    108, 123, 80, 125, 5, 90, 70, 94, 89, 87, 44, 
    2, 33, 69, 26, 127, 111, 75, 118, 8, 36, 121, 
    105, 107, 78, 15, 11, 74, 10, 43, 51, 122, 100, 
    72, 63, 98, 68, 119, 16, 65, 60, 52, 42, 53, 
    35, 0, 115, 67, 59, 30, 47, 114, 29, 40, 112, 
    31, 109, 56, 110
]
# Execute 3 times to verify we are getting 6 or more heads in every 10 spins

cum_weights = []
p = 0.5
cp = 0.5
for i in range(128):
    cum_weights.append(cp)
    p /= 2.0
    cp += p

    

for i in range(3):
    print(random.choices(values, cum_weights, k=10))
