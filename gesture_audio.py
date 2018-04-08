import serial
import time
from gtts import gTTS
import os

language = 'en'
port = '/dev/ttyACM1'
p1="Arduino/Genuino Uno"
baud = 9600
while True:
    try:
        arduino = serial.Serial(port, baud, timeout=.1)
        break
    except:
        print "Couldn't connect to Arduino. Re-trying in 5s"
        time.sleep(5)

# When connected print the serial port and baud rate.
print "Arduino connected on port: %s with baud: %d" % (port, baud)
def tospeech(text):
    myobj = gTTS(text=text, lang=language, slow=False)
    myobj.save("audio.mp3")
    os.system("mpg321 audio.mp3")
    os.remove("audio.mp3")

def readArduino():
    global ardComm

    ardComm = arduino.readline()        # Just reads the serial port and stores it in "ardComm"


def processArduino():
    if ardComm != "":                       # If ardComm is not empty then process it.
        print ardComm
        tospeech(ardComm)

def main():
    # Pretty self-explanatory
    while True:
        readArduino()
        processArduino()


if __name__ == '__main__':
    main()                  # Call main()