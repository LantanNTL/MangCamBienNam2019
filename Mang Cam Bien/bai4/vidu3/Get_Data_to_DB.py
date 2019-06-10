import pymysql
import json
#============================================================================================
def Sensor(jsonData):
	json_Dict = json.loads(jsonData)
	SensorID = json_Dict['Sensor_ID']
	Hear_rate = json_Dict['Hear_rate']
	Status = json_Dict['Status']
	Date_and_Time = json_Dict['Date']

	print(SensorID, Date_and_Time, Hear_rate, Status)
	db = pymysql.connect("localhost","wsn","1","wsn" )
	cursor = db.cursor()

	sql = """ INSERT INTO sensors3(SensorID, Date_and_Time, Hear_rate, Status)	
				VALUES(%s,%s,%s,%s)"""

	val = (SensorID, Date_and_Time, Hear_rate, Status)
	cursor.execute(sql,val)
	db.commit()
	print("Sensor created new value")
	print("-"*80)

	db.close()