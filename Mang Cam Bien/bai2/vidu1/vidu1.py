import pymysql
from datetime import datetime
from time import gmtime,strftime
from random import randint
import random
#==============================================================================
db = pymysql.connect("localhost","wsn","1","wsn" )
cursor = db.cursor()
#==============================================================================
#Tao bang du lieu
cursor.execute("DROP TABLE IF EXISTS sensors1")
sql = """CREATE TABLE sensors1(
			id INT(10) PRIMARY KEY AUTO_INCREMENT,
			rain INT(3) NOT NULL,
			wind_speed INT(3) NOT NULL,
			light INT(3) NOT NULL,
			date_and_time DATETIME  NOT NULL
		)
	"""
cursor.execute(sql)
#==============================================================================
#Insert du lieu vao bang
for i in range(0,9):
	mua = randint(20,30)
	gio = randint(40,99)
	anhsang = randint(10,99)
	now = datetime.now()
	time_now = now.strftime("%Y-%m-%d %H:%M:%S")
	sql = """INSERT INTO sensors1(rain, wind_speed, light, date_and_time)
			VALUES (%s,%s,%s,%s)"""
	try:
		cursor.execute(sql,(mua,gio,anhsang,time_now))
		db.commit()        
	except:				
		db.rollback()
#==============================================================================
#Thuc hien bang sau sap xep
try:
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
	while y<'1' or y>'2' :
		print("Please choose number 1 or 2!")
		y = input("You want to sort: ")

	if x=='1':
		if y=='1':
			sql = "SELECT * from sensors1 order by id asc"
		elif y == '2':
			sql = "SELECT * from sensors1 order by id desc"
	elif x == '2':
		if y == '1':
			sql = "SELECT * from sensors1 order by rain asc"
		elif y == '2':
			sql = "SELECT * from sensors1 order by rain desc"
	elif x == '3':
		if y == '1':
			sql = "SELECT * from sensor1 order by wind_speed asc"
		elif y == '2':
			sql = "SELECT * from sensor1 order by wind_speed desc"
	elif x == '4':
		if y == '1':
			sql = "SELECT * from sensor1 order by light asc"
		elif y == '2':
			sql = "SELECT * from sensor1 order by light desc"
	
	cursor.execute(sql)
	for row in cursor:
		print("id = %s  rain = %s   wind_speed = %s    light = %s    date_and_time = %s" %(str(row[0]),str(row[1]),str(row[2]),str(row[3]),str(row[4])))
except:
	print("Khong co du lieu")
db.close()
