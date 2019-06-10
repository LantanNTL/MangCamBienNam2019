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
cursor.execute("DROP TABLE IF EXISTS sensors3")
#============================================================================================
#Tao mot bang moi co ten "sensors"
sql = """CREATE TABLE sensors3 (
        id INT(10) PRIMARY KEY auto_increment,
        SensorID CHAR(10) not NULL,
        Hear_rate INT(10) NOT NULL,
		Status CHAR(10) NOT NULL,
        Date_and_Time char(30) not NULL
        )
    """
#============================================================================================
#Thuc thi
cursor.execute(sql)
#============================================================================================
#Dong ket noi MySQL
db.close()