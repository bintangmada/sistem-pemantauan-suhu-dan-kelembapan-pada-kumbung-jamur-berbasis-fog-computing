#edited ke 2
#library yang dibutuhkan
import serial
import sqlite3
import time

#database
dbConn = sqlite3.connect('dataSensor.db')
curs = dbConn.cursor()

#Arduino Uno
device = '/dev/ttyACM0'
try:
    uno = serial.Serial(device, 9600)
    print ("terhubung ke", device)

except:
    print ('gagal terhubunga ke ', device)
    
while True:
    data = uno.readline().decode('utf-8') #membaca data serial arduino uno
    #print (data)
    pieces = data.split("\t")
    node = pieces[0]
    suhu = float(pieces[1])
    kelembaban = float(pieces[2])
    notif = str(pieces[3])
    
    if (node == 'node1'):
        print ("ini dari node 1")
        print (suhu, kelembaban, notif)
        curs.execute("INSERT INTO dataNode1 VALUES (datetime('now'),(?),(?),(?))",(suhu,kelembaban,notif))
        dbConn.commit()
        
    #else :
    if (node == 'node2'):    
        print ("ini dari node 2")
        print (suhu, kelembaban, notif)
        curs.execute("INSERT INTO dataNode2 VALUES (datetime('now'),(?),(?),(?))",(suhu,kelembaban,notif))
        dbConn.commit()
    
