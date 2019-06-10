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
cursor.execute("DROP TABLE IF EXISTS sensors")
sql = """CREATE TABLE sensors(
            id INT(10) PRIMARY KEY AUTO_INCREMENT,
            Temperature INT(3) NOT NULL,
            Humidity INT(3) NOT NULL,
            Date_and_Time DATETIME  NOT NULL
        )
    """
cursor.execute(sql)
#==============================================================================
#Insert du lieu vao bang
for i in range(0,9):
    temp = randint(20,30)
    hum = randint(40,100)
    now = datetime.now()
    time_now = now.strftime("%Y-%m-%d %H:%M:%S")
    sql = """INSERT INTO sensors(Temperature,Humidity,Date_and_Time)
            VALUES (%s,%s,%s)"""
    try:
        cursor.execute(sql,(temp,hum,time_now))
        db.commit()        
    except:             
        db.rollback()
#==============================================================================             
#Truy van du lieu
# sql = "SELECT * FROM sensors1"
# try:
#   cursor.execute(sql)
#   results = cursor.fetchall()
#   print("|id|temp|hum|                timer")
#   for row in cursor:
#       print(row)
#       print('-'*60)
# except:
#   print("Khong co du lieu")
#==============================================================================
#Thuc hien bang sau sap xep
try:
    print("Ban muon sap xep theo:")
    print("1.ID")
    print("2.Temperature")
    print("3.Humidity")
    x = input("Nhap x = ")
    while x<'1' or x>'3' :
        print("Gia tri nhap vao bi loi!")
        x = input("Moi ban nhap lai x =  ")

    print("Ban muon sap xep 'tang' hay 'giam' (1/2)?")
    y = input("Nhap y = ")
    while y<'1' or y>'2' :
        print("Gia tri nhap vao bi loi!")
        y = input("Moi ban nhap lai y = ")
    if x == '1':
        if y == '1':
            sql = "select * from sensors order by id asc"
        else:
            sql = "select * from sensors order by id desc"
    elif x == '2':
        if y == '1':
            sql = "select * from sensors order by Temperature asc"
        else:
            sql = "select * from sensors order by Temperature desc"
    else:
        if y == '1':
            sql = "select * from sensors order by Humidity asc"
        else:
            sql = "select * from sensors order by Humidity desc"
    
    cursor.execute(sql)
    for row in cursor:
        print("id = %s  Temperature = %s   Humidity = %s   Date_and_Time = %s" %(str(row[0]),str(row[1]),str(row[2]),str(row[3])))
except:
    print("Khong co du lieu!")
db.close()
