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
cursor.execute("DROP TABLE IF EXISTS ngola")
#============================================================================================
#Tao mot bang moi co ten "ngola"
sql = """CREATE TABLE ngola (
        id INT(10) PRIMARY KEY auto_increment,
        SensorID CHAR(10) not NULL,
        Temperature INT(10) not NULL,
        Humidity INT(10) not NULL,
        Date_and_Time char(30) not NULL
        )
    """
#============================================================================================
#Thuc thi
cursor.execute(sql)
#============================================================================================
#Dong ket noi MySQL
db.close()