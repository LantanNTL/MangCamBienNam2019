import pymysql
import json
from datetime import datetime

def Sensor(jsonData):
	json_Dict = json.loads(jsonData.decode("utf-8"))
	Temperature = json_Dict['Temp']
	Humidity = json_Dict['Hum']
	Data_time = (datetime.today()).strftime("%d-%b-%y %H:%M:%S")
	db = pymysql.connect("localhost","wsn","1","wsn" )
	cursor = db.cursor()
	sql = "insert into sensors5(temperature,humidity,date_time) values (%s,%s,%s)"
	data = (Temperature,Humidity,Data_time)
	cursor.execute(sql,data)
	db.commit()
	print("Sensor created new value")
	print("------------------------")
	db.close()