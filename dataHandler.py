import ctypes
from Visualizer import Visualizer
import math
import json
from scipy.stats import beta

import numpy as np
import matplotlib.pyplot as plt
import math
if __name__ == '__main__':
    for i in range(7):
        f = open('build/simRes' +str(i), )

        # returns JSON object as
        # a dictionary
        data = f.read()

        # Closing file
        f.close()
        el = data.split()
        length = 0
        lengthTr = 0
        Tr = 0
        lengthUsed = 0
        for i in range(len(el)):
            if (i%4)==2 and int(el[i])>0:
                Tr += 1
            if i%4==3:
                length += float(el[i])
                if float(el[i])>=400:
                    lengthUsed += 1
                if int(el[i-1])>0:
                    lengthTr += float(el[i])

        print("Times target reached: " + str(Tr))
        print("Times stopped by maximal length: "+str(lengthUsed))
        print("Average length: " + str(length/(len(el)/4)))
        print("Average length when target reached: " + str(lengthTr/max(Tr,1)))
        print("Average length when target not reached: " + str(length/max((len(el)/4-Tr),1)))
        print()
        print()

    '''
    fig = plt.figure()
    ax = plt.axes(projection='3d')
    samples=10000
    # Data for a three-dimensional line
    angleFraction = beta.rvs(1, 1, size=samples)
    ar1 = np.abs(math.pi*(angleFraction-0.5))
    ar2 = (np.random.random(samples))*2*math.pi

    a1 = []
    a2 = []
    for i in range(samples):
        a1.append(math.atan(math.sin(ar1[i])*math.sin(ar2[i])/(math.cos(ar1[i]))))
        a2.append(math.pi*0.5-(math.atan(math.sin(ar1[i])*math.cos(ar2[i])/math.sqrt(
            ((math.cos(ar1[i]))**2)+(math.sin(ar1[i])*math.sin(ar2[i]))**2))))

    x=[]
    y=[]
    z=[]
    for i in range(samples):
        rsin_theta = math.sin(a2[i])
        x.append(rsin_theta * math.cos(a1[i]))
        y.append(rsin_theta * math.sin(a1[i]))
        z.append(math.cos(a2[i]))


    xdata = np.array(x)
    ydata = np.array(y)
    zdata = np.array(z)
    ax.scatter3D(xdata, ydata, zdata, c=zdata, cmap='Greens');
    ax.set_xlabel('X axis')
    ax.set_ylabel('Y axis')
    ax.set_zlabel('Z axis')
    #plt.plot(zdata)
    plt.show()
    '''