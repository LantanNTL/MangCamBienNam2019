import random
from time import *
from datetime import *
while (True):
	temperature = random.randint(10,40)
	humidity = random.randint(70,90)
	time_now = datetime.now()
	print("Nhiet do: ",temperature)
	print("Do am: ",humidity)
	print("Thoi gian: ",time_now)
	sleep(2)
	