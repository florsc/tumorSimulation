import ctypes
from Visualizer import Visualizer
import math
import json

if __name__ == '__main__':
    lib = ctypes.cdll['./build/libsimulationLibrary.so']
    lib['run']()
    # Opening JSON file
    f = open('cpp_results.json', )

    # returns JSON object as
    # a dictionary
    data = json.load(f)

    # Closing file
    f.close()
    axisLimits = [[999999999, -999999999],[999999999, -999999999],[999999999, -999999999]]
    for position in data:
        for i in range(3):
            if position[i]<axisLimits[i][0]:
                axisLimits[i][0]=position[i]
            if position[i]>axisLimits[i][1]:
                axisLimits[i][1]=position[i]

    ranges = [-1,-1,-1]
    for i in range(3):
        ranges[i] = axisLimits[i][1]-axisLimits[i][0]

    axisWithMaxRange = -1
    maxRange = -1
    for i in range(3):
        if ranges[i] > maxRange:
            maxRange = ranges[i]
            axisWithMaxRange = i

    for i in range(3):
        axisDiff = ranges[axisWithMaxRange]-ranges[i]
        axisLimits[i] = [axisLimits[i][0]-axisDiff/2,axisLimits[i][1]+axisDiff/2]

    visualizer = Visualizer(data, axisLimits)
    """
    distance = []
    for index in range(min([len(axon['axonalTipPositions']) for axon in simulation.axons])-1):
        distance.append(0)
        for axon in simulation.axons:
            distance[index] += np.dot(axon["axonalTipPositions"][index+1],axon["axonalTipPositions"][index+1])
    print(np.array(distance)/len(simulation.axons))
    plt.loglog(np.array(distance)/len(simulation.axons))
    plt.show()
    """
    visualizer.visualize()
