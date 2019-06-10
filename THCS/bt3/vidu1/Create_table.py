import pymysql
db = pymysql.connect("localhost","wsn","1","wsn" )
cursor = db.cursor()

cursor.execute("drop table if exists sensors5")

sql = """create table sensors5(
			id int(10) primary key auto_increment,
			temperature int(10) not null,
			humidity int(10) not null,
			date_time char(30) not null
		)"""
cursor.execute(sql)
db.close()