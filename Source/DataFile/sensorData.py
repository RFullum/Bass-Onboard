import random
import threading
from subprocess import Popen, PIPE

def getRandomValue():
    return random.randrange(0, 100, 1) * 0.01

def writeToFile():
    file = open("sensorData.txt", "wt")
    for i in range(3):
        file.write(str(getRandomValue()) + "\n")
    file.close()

def sendToJuce():
    value = bytes(str(getRandomValue()), 'UTF-8')
    p = Popen(['/Users/Prophetnoise/JUCE/Projects/Bass Onboard/Builds/MacOSX/build/Debug/Bass Onboard.app', value], stdout=PIPE, stderr=PIPE)
    p.communicate()

while(True):
    sr = 1.0 / 10000.0
    sendToJuce()
    #threading.Timer(sr, writeToFile())
