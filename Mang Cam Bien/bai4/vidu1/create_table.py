#Them thu vien
import pymysql
#============================================================================================
#Mo ket noi den MySQL
db = pymysql.connect("localhost","wsn","1","wsn" )
#============================================================================================
#Su dung mot doi tuong cursor de truy cap
cursor = db.cursor()
#============================================================================================
# Xoa table neu table da ton tai
cursor.execute("DROP TABLE IF EXISTS sensors2")
#============================================================================================
#Tao mot bang moi co ten "sensors"
sql = """CREATE TABLE sensors2 (
        id INT(10) PRIMARY KEY auto_increment,
        SensorID CHAR(10) not NULL,
        Long_id INT(10) NOT NULL,
		Lat INT(10) NOT NULL,
        Temperature INT(10) not NULL,
        Humidity INT(10) not NULL,
        Rain INT(3) NOT NULL,
		Rainweather VARCHAR(10) NOT NULL,
        Date_and_Time char(30) not NULL
        )
    """
#============================================================================================
#Thuc thi
cursor.execute(sql)
#============================================================================================
#Dong ket noi MySQL
db.close()