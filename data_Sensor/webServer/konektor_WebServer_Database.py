from flask import Flask, render_template, request
app = Flask(__name__)

import sqlite3

#mengambil data dari database
def getDataNode1():
	conn=sqlite3.connect('../dataSensor.db')
	curs=conn.cursor()
	while True:
		for row in curs.execute("SELECT * FROM dataNode1 ORDER BY timestamp1 DESC LIMIT 1"):
			time1 = str(row[0])
			suhu1 = row[1]
			kelembaban1 = row[2]
			notif1 = row [3]
		#conn.close()
		return time1,suhu1,kelembaban1,notif1
	
def getDataNode2():
	conn=sqlite3.connect('../dataSensor.db')
	curs=conn.cursor()
	while True:
		for row in curs.execute("SELECT * FROM dataNode2 ORDER BY timestamp2 DESC LIMIT 1"):
			time2 = str(row[0])
			suhu2 = row[1]
			kelembaban2 = row[2]
			notif2 = row [3]
		#conn.close()
		return time2,suhu2,kelembaban2,notif2
	
#main route
@app.route("/")
def index():
	time1,suhu1,kelembaban1,notif1 = getDataNode1()
	time2,suhu2,kelembaban2,notif2 = getDataNode2()
	templateData={
		'time1' : time1,
		'suhu1' : suhu1,
		'kelembaban1' : kelembaban1,
		'notif1' : notif1,
		'time2' : time2,
		'suhu2' : suhu2,
		'kelembaban2' : kelembaban2,
		'notif2' : notif2
		}
	return render_template('index.html', **templateData)
		
if __name__ == "__main__":
	app.run(host='0.0.0.0', port=80, debug=False)
		 
		
