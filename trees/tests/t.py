import random
f = open('text.txt','w')
f.write('4\n')
for i in range(0, 1000):
    a = random.randint(1,1000)
    f.write(str(a) + '\n')
f.close()


