import pymysql
import json
#============================================================================================
def Sensor(jsonData):
	json_Dict = json.loads(jsonData)
	SensorID = json_Dict['Sensor_ID']
	Long_id = json_Dict['Long_id']
	Lat = json_Dict['Lat']
	Date_and_Time = json_Dict['Date']
	Temperature = json_Dict['Temperature']
	Humidity = json_Dict['Humidity']
	Rain = json_Dict['Rain']
	Rainweather = json_Dict['Rainweather']

	print(SensorID,Long_id, Lat, Date_and_Time, Temperature, Humidity, Rain, Rainweather)
	db = pymysql.connect("localhost","wsn","1","wsn" )
	cursor = db.cursor()

	sql = """ INSERT INTO sensors2(SensorID, Long_id, Lat, Date_and_Time, Temperature, Humidity, Rain, Rainweather)	
				VALUES(%s,%s,%s,%s,%s,%s,%s,%s)"""

	val = (SensorID, Long_id, Lat, Date_and_Time, Temperature, Humidity, Rain, Rainweather)
	cursor.execute(sql,val)
	db.commit()
	print("Sensor created new value")
	print("-"*80)

	db.close()