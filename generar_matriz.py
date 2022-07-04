import random
matriz = []
j = 0
for i in range(25):
    aux =[]
    if(j!=0):
        for z in range(0,j):
            aux.append(matriz[z][i])        
    for k in range(j,25):
        r1 = random.randint(5, 20)/10
                #aux.append(matriz[z][i])        
        #print(r1,end=',')
        aux.append(r1)
    matriz.append(aux)
    matriz[i][i]=0
    j=j+1

for i in matriz:
    print(i)