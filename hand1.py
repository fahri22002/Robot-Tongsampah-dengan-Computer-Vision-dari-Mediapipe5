import serial
ser = serial.Serial('COM8', 9600) 
huruf = 'F'
ser.write(huruf.encode('utf-8'))
ser.close()