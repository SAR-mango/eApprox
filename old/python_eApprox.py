
import numpy as np
import matplotlib.pyplot as plt

numCircPts = 100
rad = 0.01
numTotPts = 1000

eApproxPts = np.empty ((1, 2))
eRealPts = np.empty ((0))

def quartCircAround (x, y):
    quartCirc = np.empty ((0, 2))
    angleIncrements = np.pi/(2*numCircPts)
    for theta in np.arange (angleIncrements, np.pi/2, angleIncrements):
        quartCirc = np.append (quartCirc, [[x + rad*np.cos (theta), y + rad*np.sin (theta)]], axis = 0)
    return quartCirc

def getSlopes (x2y2, x1y1):
    a = np.subtract (x2y2, x1y1)
    return np.divide (a [:, 1], a [:, 0])

def choosePt (pts, slopes):
    differences = np.abs (np.subtract (pts [:, 1], slopes))
    prevI = differences [0]
    index = 0
    for i in range (len (differences)):
        if differences [i] < prevI:
            index = i
        prevI = differences [i]
    return pts [index]

eApproxPts [0] = [0, 1]

for p in range (numTotPts):
    lastPt = eApproxPts [p]
    potentialPts = quartCircAround (lastPt [0], lastPt [1])
    print (potentialPts)
    plt.scatter (potentialPts [:, 0], potentialPts [:, 1])
    slopes = getSlopes (potentialPts, lastPt)
    eApproxPts = np.append (eApproxPts, [choosePt (potentialPts, slopes)], axis = 0)

for q in eApproxPts [:, 0]:
    eRealPts = np.append (eRealPts, [np.e ** q], axis = 0)

plt.scatter (eApproxPts [:, 0], eApproxPts [:, 1])
plt.plot (eApproxPts [:, 0], eRealPts, color = 'orange')
plt.plot (eApproxPts [:, 0], eRealPts - eApproxPts [:, 1], color = 'red')
plt.show ()
