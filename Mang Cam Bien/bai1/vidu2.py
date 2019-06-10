import module
#Nhap va in mang ban dau
try:
    n = int(input("Nhap n: "))
    if n <= 0:
        exit()
except:
    print('Phai nhap so tu nhien')
    exit()
a = []
for i in range(n):
    a.append(input('a[%d]= ' % (i+1)))
print("Mang sau ban dau la:");
print(a)

#Mang sau khi sap xep
print("Mang sau khi sap xep giam dan la:");
module.sapXep(a,n);

#Dem so lan xuat hien nhieu nhat cua phan tu trong mang
temp = module.timSoLanXuatHien(a,n);
print('So lan xuat hien nhieu nhat la:')
print(temp);

#Dem so lan xuat hien cua phan tu nhap vao trong mang 1 chieu
print("Nhap so can kiem tra: ")
x = input()
temp1 = module.demGiaTri(a,n,x)
if(temp1 == 0 ):
	print("So kiem tra khong xuat hien trong mang")
else:
	print("So lan xuat hien la: ", temp1)

#Tim so hoan hao trong mang
module.soHoanHao(a,n)