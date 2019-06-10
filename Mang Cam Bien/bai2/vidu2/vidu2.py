import module
module.create_Table()
module.insert_Table()
# module.select_Table()
print("1.ID")
print("2.Rain")
print("3.Wind_speed")
print("4.Light")
x = input("You want to sort by: ")
while x<'1' or x>'4' :
	print("Please choose number from 1 to 4!")
	x = input("Nhap lua chon cua ban: ")

print("1.Increment")
print("2.Decrement")
y = input("You want to sort: ")
module.sort_Table(x,y)