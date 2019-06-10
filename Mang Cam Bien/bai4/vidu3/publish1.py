import paho.mqtt.client as mqtt
import random,json
from datetime import datetime
from time import sleep
#============================================================================================
#Setting MQTT
MQTT_Broker = "localhost"
MQTT_Port = 1883
Keep_Alive_Interval = 45
MQTT_Topic = "ngola/hearate"
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
# mqttc.username_pw_set(username="ngola",password="123456")
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
	a = int(random.uniform(50,100))
	if(a>50 and a<60):
		status = 'Low';
	elif(a>60 and a<70):
		status = 'Nomal'
	elif(a>70 and a<100):
		status = 'Hate'
	elif(a>100 and a<120):
		status = 'Wanning'	
	#=====================================================
	Sensor_data = {}
	Sensor_data['Sensor_ID'] = "DHT11"
	Sensor_data['Hear_rate'] = a
	Sensor_data['Date'] = (datetime.today()).strftime("%d-%b-%Y %H:%M:%S")
	Sensor_data['Status'] = status
	Sensor_json_data = json.dumps(Sensor_data)
	print ("Publishing fake Sensor Value: ")
	publish_To_Topic (MQTT_Topic, Sensor_json_data)
	sleep(3)

for i in range(0,9):
	publish_Fake_Sensors_Values_to_MQTT()
	print('-'*80)
	sleep(3)