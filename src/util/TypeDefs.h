//
// Created by florian on 10/11/21.
//

#ifndef TUMORSIMULATION_TYPEDEFS_H
#define TUMORSIMULATION_TYPEDEFS_H

#include <memory>
#include <vector>
#include <list>
#include <random>

class BaseAxon;

class Samplers;

class RazettiAxon;

class ConstraintManager;

class EuclideanVector;

class AxonManager;

class AxonFactory;

class SimulationManager;

class TargetManager;

class Target;

using TargetManagerHandle = std::shared_ptr<TargetManager>;
using TargetHandle = std::shared_ptr<Target>;
using TargetVector = std::vector<TargetHandle>;
using Generator = std::mt19937;
using GeneratorHandle = std::shared_ptr<Generator>;
using AxonFactoryHandle = std::unique_ptr<AxonFactory>;
using SamplerHandle = std::shared_ptr<Samplers>;
using SimulationManagerHandle = std::weak_ptr<SimulationManager>;
using AxonManagerHandle = std::shared_ptr<AxonManager>;
using PositionVector = std::vector<EuclideanVector>;
using PositionList = std::list<EuclideanVector>;
using AxonHandle = std::shared_ptr<BaseAxon>;
using WeakAxonHandle = std::weak_ptr<BaseAxon>;
using AxonVector = std::vector<AxonHandle>;
using AxonList = std::list<AxonHandle>;
using ConstraintManagerHandle = std::shared_ptr<ConstraintManager>;

#endif //TUMORSIMULATION_TYPEDEFS_H
