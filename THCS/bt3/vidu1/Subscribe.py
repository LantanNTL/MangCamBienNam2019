import paho.mqtt.client as mqtt
from Get_Data_to_DB import Sensor

MQTT_Broker = "m16.cloudmqtt.com"
MQTT_Port = 12155
Keep_Alive_Interval = 45
MQTT_Topic = "Test"

def on_connect(client, userdata, flags, rc):
	if  rc != 0:
		pass
		print("Unable to connect to MQTT Broker...")
	else:
		print("Connect with MQTT Broker: " + str(MQTT_Broker))

	client.subscribe(MQTT_Topic,0)

def on_message(client, userdata, msg):
	print("MQTT Data Received...")
	print("MQTT Topic: " + msg.topic)
	print("Data: " + str(msg.payload))
	Sensor(msg.payload)

client = mqtt.Client()
client.username_pw_set(username="lteqwnjb",password="O_zUwzxs1rqM")
client.on_connect = on_connect
client.on_message = on_message

client.connect(MQTT_Broker, MQTT_Port, Keep_Alive_Interval)
client.loop_forever()