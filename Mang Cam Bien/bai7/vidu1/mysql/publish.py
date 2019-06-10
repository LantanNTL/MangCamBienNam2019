import paho.mqtt.client as mqtt
import random,json
from datetime import datetime
from time import sleep
#============================================================================================
#Setting MQTT
MQTT_Broker = "localhost"
MQTT_Port = 1883
Keep_Alive_Interval = 45
MQTT_Topic = "home/sensors"
#============================================================================================
#Ham ket noi den may chu MQTT
def on_connect(client, userdata, rc):
	if rc != 0:
		pass
		print("Unable to connect to MQTT Broker...")
	else:
		print("Connected with MQTT Broker: " + str(MQTT_Broker))

def on_publish(client, userdata, mid):
	pass

def on_disconnect(client, userdata, rc):
	if rc != 0:
		pass

mqttc = mqtt.Client()
mqttc.on_connect = on_connect
mqttc.on_disconnect = on_disconnect
mqttc.on_publish = on_publish
mqttc.connect(MQTT_Broker, MQTT_Port, Keep_Alive_Interval)
#============================================================================================
#Publish du lieu
def publish_To_Topic(topic, message):
	mqttc.publish(topic, message)
	print (("Published: " + str(message) + " " + "on MQTT Topic: " + str(topic)))
	print ("")
#============================================================================================
#Fake random sensors
def publish_Fake_Sensors_Values_to_MQTT():
	Humidity_Fake_Value = int(random.uniform(0,100))
	Temperature_Fake_Value = int(random.uniform(20,40))
	Windspeed_Fake_Value = int(random.uniform(0,200))
	status = str('');
	if(Temperature_Fake_Value<30):
		status = 'Good';
	if(Humidity_Fake_Value<80):
		status = 'Good';
	if(Windspeed_Fake_Value<100):
		status = 'Good';
	if(Temperature_Fake_Value>=30 and Temperature_Fake_Value<35 ):
		status = 'Nomal';
	if(Humidity_Fake_Value>=80 and Humidity_Fake_Value<100):
		status = 'Nomal';
	if(Windspeed_Fake_Value>=100 and Windspeed_Fake_Value<200):
		status = 'Nomal';
	if(Temperature_Fake_Value >=35):
		status = 'Bad';	
	#=====================================================
	Sensor_data = {}
	Sensor_data['Time'] = (datetime.today()).strftime("%d-%b-%Y %H:%M:%S")
	Sensor_data['Humidity'] = Humidity_Fake_Value
	Sensor_data['Temperature'] = Temperature_Fake_Value
	Sensor_data['Windspeed'] = Windspeed_Fake_Value
	Sensor_data['W_status'] = status
	Sensor_json_data = json.dumps(Sensor_data)
	print ("Publishing fake Sensor Value: ")
	publish_To_Topic (MQTT_Topic, Sensor_json_data)
	sleep(3)

while True:
	publish_Fake_Sensors_Values_to_MQTT()
	print('-'*80)
	sleep(3)