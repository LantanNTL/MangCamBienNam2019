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
cursor.execute("DROP TABLE IF EXISTS sensors")
#============================================================================================
#Tao mot bang moi co ten "sensors"
sql = """CREATE TABLE sensors (
        id INT(10) PRIMARY KEY auto_increment,
        Temperature INT(10) NOT NULL,
		Humidity INT(10) NOT NULL,
		Windspeed INT(10) NOT NULL,
		W_status CHAR(10) NOT NULL,
        Date_and_Time char(30) NOT NULL
        )
    """
#============================================================================================
#Thuc thi
cursor.execute(sql)
#============================================================================================
#Dong ket noi MySQL
db.close()