import ctypes
from Visualizer import Visualizer
import math
import json

if __name__ == '__main__':
    lib = ctypes.cdll['./src/libsimulationLibrary.so']
    print("aa")
    lib['run']()
    print("aa")
    # Opening JSON file
    f = open('cpp_results.json', )

    # returns JSON object as
    # a dictionary
    data = json.load(f)

    # Closing file
    f.close()
    visualizer = Visualizer(data)
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
