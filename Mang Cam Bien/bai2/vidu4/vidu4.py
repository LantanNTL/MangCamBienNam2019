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
cursor.execute("DROP TABLE IF EXISTS sensors2")
sql = """CREATE TABLE sensors2(
			id INT(10) PRIMARY KEY AUTO_INCREMENT,
			sensorid INT(10) NOT NULL,
			long_id INT(10) NOT NULL,
			lat INT(10) NOT NULL,
			temperature INT(3) NOT NULL,
			humidity INT(3) NOT NULL,
			rain INT(3) NOT NULL,
			rainweather VARCHAR(10) NOT NULL,
			date_and_time DATETIME  NOT NULL
		)
	"""
cursor.execute(sql)
#==============================================================================
#Insert du lieu vao bang
for i in range(10):
	a = [1,2,3,4]
	b = [1,2,3,4]
	c = [1,2,3,4]
	d = ['mua_nhe','mua_phun','mua_rao','mua_bao']
	j = randint(0,3)
	sensor_id = a[j]
	long_i = b[j]
	lat_i = c[j]
	weather = d[j]
	temp = randint(20,30)
	hum = randint(40,99)
	rain = randint(0,1)
	now = datetime.now()
	time_now = now.strftime("%Y-%m-%d %H:%M:%S")
	sql = """INSERT INTO sensors2(sensorid, long_id, lat, temperature, humidity, rain, rainweather, date_and_time)
			VALUES (%s,%s,%s,%s,%s,%s,%s,%s)"""
	try:
		cursor.execute(sql,(sensor_id,long_i,lat_i,temp,hum,rain,weather,time_now))
		db.commit()        
	except:				
		db.rollback()
#==============================================================================
#Thuc hien bang sau sap xep
try:
	print("1.temperature")
	print("2.humidity")
	x = input("You want to sort by: ")
	while x<'1' or x>'2' :
		print("Please choose number from 1 to 2!")
		x = input("Nhap lua chon cua ban: ")

	print("1.Increment")
	print("2.Decrement")
	y = input("You want to sort: ")
	while y<'1' or y>'2' :
		print("Please choose number 1 or 2!")
		y = input("You want to sort: ")

	if x=='1':
		if y=='1':
			sql = "SELECT * from sensors2 order by temperature asc"
		else:
			sql = "SELECT * from sensors2 order by temperature desc"
	else:
		if y == '1':
			sql = "SELECT * from sensors2 order by humidity asc"
		else:
			sql = "SELECT * from sensors2 order by humidity desc"
	

	cursor.execute(sql)
	rows = cursor.fetchmany(3)
	for row in rows:
		print("id=%s sensor_id=%s long_id=%s lat=%s temperature=%s humidity=%s rains=%s rainweather=%s date_and_time=%s" \
			%(str(row[0]),str(row[1]),str(row[2]),str(row[3]),str(row[4]),str(row[5]),str(row[6]),str(row[7]),str(row[8])))

except:
	print("Khong co du lieu !")
db.close()
