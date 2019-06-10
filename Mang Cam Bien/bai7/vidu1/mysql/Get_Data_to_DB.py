import pymysql
import json
#============================================================================================
def Sensor(jsonData):
	json_Dict = json.loads(jsonData)
	print(json_Dict)
	Date_and_Time = json_Dict['Time']
	Temperature = json_Dict['Temperature']
	Humidity = json_Dict['Humidity']
	Windspeed = json_Dict['Windspeed']
	W_status = json_Dict['W_status']
	# print(SensorID, Date_and_Time, Temperature, Humidity)
	db = pymysql.connect("localhost","wsn","1","wsn" )
	cursor = db.cursor()

	sql = """ INSERT INTO sensors(Date_and_Time, Temperature, Humidity, Windspeed, W_status)	
				VALUES(%s,%s,%s,%s,%s)"""

	val = (Date_and_Time, Temperature, Humidity, Windspeed, W_status)
	cursor.execute(sql,val)
	db.commit()
	print("Sensor created new value")
	print("-"*80)

	db.close()