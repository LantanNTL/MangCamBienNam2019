import pymysql
import json
#============================================================================================
def Sensor(jsonData):
	json_Dict = json.loads(jsonData)
	SensorID = json_Dict['Sensor_ID']
	Date_and_Time = json_Dict['Date']
	Temperature = json_Dict['Temperature']
	Humidity = json_Dict['Humidity']

	print(SensorID, Date_and_Time, Temperature, Humidity)
	db = pymysql.connect("localhost","wsn","1","wsn" )
	cursor = db.cursor()

	sql = """ INSERT INTO sensors(SensorID, Date_and_Time,Temperature,Humidity)	
				VALUES(%s,%s,%s,%s)"""

	val = (SensorID, Date_and_Time, Temperature, Humidity)
	cursor.execute(sql,val)
	db.commit()
	print("Sensor created new value")
	print("-"*80)

	db.close()