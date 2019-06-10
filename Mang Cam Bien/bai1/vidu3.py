print ("nhap so hang:")
m = input()
print ("nhap so cot:")
n = input()

a = []

for i in range(m):
    a.append([0]*n)
    for j in range(n):
        print('a[%d][%d]=' %(i,j))
        a[i][j]=int(input())

print(a)