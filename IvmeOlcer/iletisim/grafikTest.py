import time
import serial
import matplotlib.pyplot as plt 
import matplotlib.animation as animation
import RingBuffer


dogrulamaByte = 0x03
ikinciDogrulamaByte = 0x01
sonKontrolByte = 0x0A
fig = plt.figure()
axline = fig.add_subplot(1,1,1)
myRingBuffer = RingBuffer.RingBuffer(20)
myRingBufferY = RingBuffer.RingBuffer(20)
myRingBufferZ = RingBuffer.RingBuffer(20)


ser = serial.Serial(
    port='COM5',
    baudrate=9600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)


Xekseni = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19] 
Yekseni = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19] 
aaa = 15





ser.isOpen()

cozucu = {
    1: "DogrulamaByte",
    2: "DogrulamaIkinciByte",
    3: "xEkseniHigh",
    4: "xEkseniLow"
    
    }

def paketCozucuDogrulamaByte():
    print("ILK BYTE YAKALANDI")
    
def paketCozucuDogrulamaIkinciByte():
    print("IKINCI BYTE YAKALANDI")

def paketCozucuDogrulamaxEkseniHigh():
    print("HIGH YAKALANDI")
    
def paketCozucuDogrulamaxEkseniLow():
    print("LOW YAKALANDI")
def cizimYap(i, bbb, eksenBilgim,cemberBuffer, seriBaglanti):
    
    myBufferIncome = (seriBaglanti.read(8))
    print(ord(myBufferIncome[5]))
    if(ord(myBufferIncome[0]) == 0x03): #ilkDogrulamaByteKontrolu
        if(ord(myBufferIncome[1]) == 0x01): #ikinciDogrulamaByteKontrolu
            ivmeOlcerXEkseniHigh = ord(myBufferIncome[3])
            ivmeOlcerXEkseniLow =ord(myBufferIncome[2])
            ivmeOlcerXEkseniMerge = (ivmeOlcerXEkseniHigh << 8) + ivmeOlcerXEkseniLow
            ivmeOlcerYEkseniLow = ord(myBufferIncome[4])
            ivmeOlcerYEkseniHigh = ord(myBufferIncome[5])
            ivmeOlcerYEkseniMerge = (ivmeOlcerYEkseniHigh << 8) + ivmeOlcerYEkseniLow
            print(ivmeOlcerYEkseniLow) #Cok hassas olcum yapmak istemedigim icin bu kismi almadim grafiklerde.
                                         # High Byte kismi bizim icin yeterli olacaktir.
                                         
            #print(ivmeOlcerXEkseniLow)
            #ivmeOlcerXEkseni = bin((bin(ord(myBufferIncome[3])) << 8))
            #print(bin(ivmeOlcerXEkseni))
    
    
    
    
    
    myRingBuffer.append(ord(myBufferIncome[3]))
    myRingBufferY.append(ord(myBufferIncome[5]))
    myRingBufferZ.append(ord(myBufferIncome[7]))
    
    denemeX = myRingBuffer.get()
    denemeY = myRingBufferY.get()
    denemeZ = myRingBufferZ.get()
    if(len(denemeX) == 20):
        #print(deneme)
        axline .clear()
        axline.plot(Yekseni, denemeY)
        axline.plot(Yekseni,denemeX)
        axline.plot(Yekseni, denemeZ)
    
    


#myRingBuffer.append(11111)
anim = animation.FuncAnimation(fig, cizimYap, fargs =(aaa,Yekseni,myRingBuffer,ser),  interval = 20)
plt.show()