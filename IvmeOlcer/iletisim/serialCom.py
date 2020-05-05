import time
import serial
import matplotlib.pyplot as plt 
import matplotlib.animation as animation
import RingBuffer


fig = plt.figure()
axline = fig.add_subplot(1,1,1)

Xekseni = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19] 
Yekseni = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19] 
# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='COM5',
    baudrate=9600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)

myRingBuffer = RingBuffer.RingBuffer(20)
ser.isOpen()
##def cizimYap(i, myRingBuffer, ser,Yekseni):
##    xx = ser.read()
##    myRingBuffer.append(ord(xx))
##    
 ##   deneme = myRingBuffer.get()
##   print(len(deneme))
##    if(len(deneme) == 20):
##        axline .clear()
##        axline.plot(Yekseni,deneme)
        
        

print 'Enter your commands below.\r\nInsert "exit" to leave the application.'

input=1
while 1 :
    xx = ser.read()
    print(ord(xx))
    #Xekseni[0]=ord(xx)

        #plt.plot(Yekseni,deneme)
        #plt.pause(0.01)
        #plt.draw()
    #anim = animation.FuncAnimation(fig, cizimYap, 
    #fargs =(myRingBuffer,ser,Yekseni,),  interval = 100)

    #print(ord(xx))