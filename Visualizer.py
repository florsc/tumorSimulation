import matplotlib.pyplot as plt
import numpy as np


class Visualizer:

    def __init__(self, simulatedAxons, range):
        self.simulatedAxons = simulatedAxons
        plt.figure()
        self.axis = plt.axes(projection='3d')

        self.axis.set_xlim3d(range[0][0], range[0][1])
        self.axis.set_ylim3d(range[1][0], range[1][1])
        self.axis.set_zlim3d(range[2][0], range[2][1])
        '''
    def addBallLimits(self, radius):

        # Ball
        u = np.linspace(0, 2 * np.pi, 100)
        v = np.linspace(0, np.pi, 100)
        x = radius * np.outer(np.cos(u), np.sin(v))
        y = radius * np.outer(np.sin(u), np.sin(v))
        z = radius * np.outer(np.ones(np.size(u)), np.cos(v))

        # Plot the surface
        self.axis.plot_surface(x, y, z, alpha=0.2, color='b')




    def addTubeLimits(self, radius):

        # Cylinder
        x = np.linspace(0, 100, 10)
        z = np.linspace(-33.4, 33.4, 10)
        Xc, Zc = np.meshgrid(x, z)
        Yc = np.sqrt(33.4**2-Zc**2)

        # Draw parameters
        rstride = 20
        cstride = 10
        self.axis.plot_surface(Xc, Yc, Zc, color='r',
                               alpha=0.2, rstride=rstride, cstride=cstride)
        self.axis.plot_surface(Xc, -Yc, Zc, color='r',
                               alpha=0.2, rstride=rstride, cstride=cstride)
'''
    def addTargets(self, targets):
        for index in range(len(targets["radius"])):
            radius = targets["radius"][index]
            center = targets["centers"][index]
            u = np.linspace(0, 2 * np.pi, 100)
            v = np.linspace(0, np.pi, 100)
            x = radius * np.outer(np.cos(u), np.sin(v))+center[0]
            y = radius * np.outer(np.sin(u), np.sin(v))+center[1]
            z = radius * np.outer(np.ones(np.size(u)), np.cos(v))+center[2]

            # Plot the surface
            self.axis.plot_surface(x, y, z, alpha=0.2, color='r')


    def addAxons(self):
        for i in range(len(self.simulatedAxons)):
            axon = self.simulatedAxons[i]
            xline = [tipPosition[0]
                     for tipPosition in axon]
            yline = [tipPosition[1]
                     for tipPosition in axon]
            zline = [tipPosition[2]
                     for tipPosition in axon]
            self.axis.plot3D(xline, yline, zline, 'gray', scalex=False, scaley=False)

    def addBallLimits(self, radius):

        # Ball
        u = np.linspace(0, 2 * np.pi, 100)
        v = np.linspace(0, np.pi, 100)
        x = radius * np.outer(np.cos(u), np.sin(v))
        y = radius * np.outer(np.sin(u), np.sin(v))
        z = radius * np.outer(np.ones(np.size(u)), np.cos(v))

        # Plot the surface
        self.axis.plot_surface(x, y, z, alpha=0.2, color='b')


    def visualize(self):
        self.addAxons()
        #self.addBallLimits(400)
        self.addTargets({"radius":[20,30], "centers":[[12,70,20],[-120,5,20]]})
        self.axis.set_xlabel("X")
        self.axis.set_ylabel("Y")
        self.axis.set_zlabel("Z")

        plt.show()

        pass
