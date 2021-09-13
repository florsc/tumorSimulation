
import ctypes
from Visualizer import Visualizer
import json

if __name__ == '__main__':
    lib = ctypes.cdll['./cmake-build-debug/libsimulationLibrary.so']
    a = lib['run']
    a()
    # Opening JSON file
    f = open('cpp_results.json',)

    # returns JSON object as
    # a dictionary
    data = json.load(f)

    # Iterating through the json
    # list
    for i in data:
        print(i)

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

