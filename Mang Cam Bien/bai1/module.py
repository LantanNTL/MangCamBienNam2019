b=[]
def sapXep(b,n):
	for i in range(0,n):
		for j in range(i+1,n):
			if(b[i]<b[j]):
				temp = b[i]
				b[i] = b[j]
				b[j] = temp
	print(b)

def timSoLanXuatHien(b,n):
 	sapXep(b,n);
 	dem = 1
 	temp = 0
	for i in range(0,n-1):
 		if (b[i] == b[i+1]):
 			dem = dem + 1
 			if(dem > temp):
 				temp = dem
 		else:
 			dem = 1;
 	return temp

def demGiaTri(b,n,x):
	dem = 0;
	for i in range(0,n):
		if(b[i] == x):
			dem = dem + 1
	return dem

def soHoanHao(b,n):
 	for i in range(0,n):
 		sum = 0
 		for j in range(1,b[i]):
 			if((b[i]%j) == 0):
 				sum = sum + j
 		if(sum == b[i]):
 			print(b[i],"la so hoan hao")
 		else:
 			print(b[i],"Khong phai so hoan hao")
