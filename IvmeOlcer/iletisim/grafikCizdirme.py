import time
import sqlite3

import serial
import matplotlib.pyplot as plt 
import matplotlib.animation as animation
import RingBuffer
from tkinter import *
from functools import partial
LoggedIn = 0
def veritabaniOkuma(veritabanim,cursor,kullaniciadi, sifre,forCloseWindow):
    #window
    cursor.execute('''SELECT * FROM kullanici''')
    cursor.execute('SELECT * FROM kullanici WHERE username = ? AND password = ?', (kullaniciadi, sifre))
    girisBilgisiDogrulama = cursor.fetchall() #Eger sorgudan donen herhangi bir eleman varsa dogru kombinasyon
    print(girisBilgisiDogrulama)
    if girisBilgisiDogrulama:
        print("Welcome the system.")
        forCloseWindow.destroy()
        LoggedIn=1
    else:
        print("Password is wrong")
    return LoggedIn


def veriTabaniOlusturma():
    veritabani = sqlite3.connect('proje.sqlite')
    cursor = veritabani.cursor()
    cursor.execute("CREATE TABLE IF NOT EXISTS kullanici (username, password)")
    # ilk uyeyi olustururken admini bir defaya mahsus calistirdim.
    #cursor.execute("INSERT INTO kullanici VALUES ('admin','admin')")
    veritabani.commit()
    
    return veritabani,cursor
def validateLogin(username, password,myWindow):
	
	print("username entered :"+ username.get())
	print("password entered :"+ password.get())
	veritabaniOkuma(veritabanim,cursor, username.get(),password.get(),myWindow)
	return

def loglamaEkraniAcilis():
    loglamaEkrani = Tk()  
    loglamaEkrani.geometry('200x200')  
    loglamaEkrani.title('IvmeOlcer Izleme Ekranina Hosgeldin')


def girisEkrani(validateLogin):
    #window
    myWindow = Tk()  
    myWindow.geometry('300x150')  
    myWindow.title('IvmeOlcer Haberlesme Ekrani')

    #username label and text entry box
    usernameLabel = Label(myWindow, text="Username").grid(row=0, column=0)
    username = StringVar()
    usernameEntry = Entry(myWindow, textvariable=username).grid(row=0, column=1)  

    #password label and password entry box
    passwordLabel = Label(myWindow,text="Password").grid(row=1, column=0)  
    password = StringVar()
    passwordEntry = Entry(myWindow, textvariable=password, show='*').grid(row=1, column=1)  
    
    validateLogin = partial(validateLogin, username, password,myWindow)

    #login button
    loginButton = Button(myWindow, text="Login", command=validateLogin).grid(row=1, column=4)  

    myWindow.mainloop()
    return username.get(), password.get(), myWindow
veritabanim,cursor = veriTabaniOlusturma()
kullaniciadi, sifre, forCloseWindow = girisEkrani(validateLogin)

veritabanim.close()




dogrulamaByte = 0x03
ikinciDogrulamaByte = 0x01
sonKontrolByte = 0x0A
myRingBuffer = RingBuffer.RingBuffer(20)
myRingBufferY = RingBuffer.RingBuffer(20)
myRingBufferZ = RingBuffer.RingBuffer(20)
fig = plt.figure()
axline = fig.add_subplot(1,1,1)

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
    
    xDegerBuffer = myRingBuffer.get()
    yDegerBuffer = myRingBufferY.get()
    zDegerBuffer = myRingBufferZ.get()
    if(len(xDegerBuffer) == 20):
        #print(deneme)
        axline .clear()
        axline.plot(Yekseni, yDegerBuffer)
        axline.plot(Yekseni,xDegerBuffer)
        axline.plot(Yekseni, zDegerBuffer)






anim = animation.FuncAnimation(fig, cizimYap, fargs =(aaa,Yekseni,myRingBuffer,ser),  interval = 10)
plt.show()