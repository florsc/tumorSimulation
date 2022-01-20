# tumorSimulation

The relevant files are in the folder SimulationSetUp.
Look in the respective files for more details in comments.

All parameters are set in the cpp files.

In AxonOrder the parameters for the order of growth are set.

In ConstraintSetUp the parameters for the exterior limit are set.

In GrowthModels the parameters for the axon growth are set.

In TargetSetUp the parameters for the targets are set. 
Currently this is not relevent, because they are changed in the simulation each run.

In ParameterStruct the general parameters are set. 
Additionally the respective models from the previous folders are chosen.

Outside of SimulationSetUp there is SimulationLibrary.cpp, where the runs are designed.

If specific distributions are necessary, you can add them in Samplers.h.
It should be simple to follow the structure of already existing distributions.

There are two possible runs. 

SimulationRun runs the simulation several times.
The results can be extracted by running the dataHandler.py while being in the tumorSimulation folder.

Visualization runs the simulation once.
The result can be shown as 3D diagram by running the python_wrapper.py while being in the tumorSimulation folder.

You can build the relevant targets by:

cmake --build /home/florian/CLionProjects/tumorSimulation/build --target simulationRun

cmake --build /home/florian/CLionProjects/tumorSimulation/build --target visualizationRun

Go in the directory and run respectively ./simulationRun or ./visualizationRun to create the data.
Afterwards you can run the python files.


