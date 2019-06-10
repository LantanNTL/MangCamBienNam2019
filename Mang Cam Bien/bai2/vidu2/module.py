import pymysql
from time import gmtime,strftime
from datetime import datetime,timedelta
from random import randint
import random
#==============================================================================
db = pymysql.connect("localhost","wsn","1","wsn" )
cursor = db.cursor()
#==============================================================================
#Tao bang du lieu
def create_Table():
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
def insert_Table():
	for i in range(0,9):
		mua = randint(20,30)
		gio = randint(40,99)
		anhsang = randint(10,99)
		time_now = datetime.now()
		sql = """INSERT INTO sensors1(rain, wind_speed, light, date_and_time)
				VALUES (%s,%s,%s,%s)"""
		try:
			cursor.execute(sql,(mua,gio,anhsang,time_now))
			db.commit()        
		except:				
			db.rollback()
#==============================================================================				
#Truy van du lieu
def select_Table():
	sql = "SELECT * FROM sensors2"
	try:
		cursor.execute(sql)
		results = cursor.fetchall()
		print(results)
		print("|id|rain|wind_speed|light|                date_and_time")
		for row in cursor:
			print(row)
			print('-'*60)
	except:
		print("Khong co du lieu")
#==============================================================================
#Thuc hien bang sau sap xep
def sort_Table(a,b):
	try:
		if a == '1':
			if b == '1':
				sql = "select * from sensors1 order by id asc"
			elif b == '2':
				sql = "select * from sensors1 order by id desc"
		elif a == '2':
			if b == '1':
				sql = "select * from sensors1 order by rain asc"
			elif b == '2':
				sql = "select * from sensors1 order by rain desc"
		elif a == '3':
			if b == '1':
				sql = "select * from sensors1 order by wind_speed asc"
			elif b == '2':
				sql = "select * from sensors1 order by wind_speed desc"
		elif a == '4':
			if b == '1':
				sql = "select * from sensors1 order by light asc"
			elif b == '2':
				sql = "select * from sensors1 order by light desc"
	
		cursor.execute(sql)
		for row in cursor:
			print("id = %s  rain = %s   wind_speed = %s    light = %s    timer = %s" %(str(row[0]),str(row[1]),str(row[2]),str(row[3]),str(row[4])))
	except:
		print("Khong co du lieu")
	db.close()