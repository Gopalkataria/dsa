from random import randint

k = randint(1, 2*(10**5))

print(k)

for i in range(k):
    print(randint(1, 10**9), end=' ')