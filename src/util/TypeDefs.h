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

class AxonSetUpParameters;

class RandomDirectionSetUpParameters;

class RazettiSetUpParameters;

class GeneratorSingleton;

class AxonOrderLinearData;

class AxonOrderSampledWaitingTimeData;

class AxonOrderData;

class ExteriorLimitSetUpParameters;

class SphericalTargetSetUpParameters;

class TargetSetUpParameters;

class SphericalLimitSetUpParameters;

using TargetManagerHandle = std::shared_ptr<TargetManager>;
using TargetHandle = std::shared_ptr<Target>;
using TargetVector = std::vector<TargetHandle>;
using Generator = std::mt19937;
using GeneratorHandle = std::shared_ptr<Generator>;
using AxonFactoryHandle = std::shared_ptr<AxonFactory>;
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
using AxonSetUpParametersHandle = std::shared_ptr<AxonSetUpParameters>;
using RandomDirectionSetUpParametersHandle = std::shared_ptr<RandomDirectionSetUpParameters>;
using RazettiSetUpParametersHandle = std::shared_ptr<RazettiSetUpParameters>;
using GeneratorSingletonHandle = std::shared_ptr<GeneratorSingleton>;
using AxonOrderLinearDataHandle = std::shared_ptr<AxonOrderLinearData>;
using AxonOrderSampledWaitingTimeDataHandle = std::shared_ptr<AxonOrderSampledWaitingTimeData>;
using AxonOrderDataHandle = std::shared_ptr<AxonOrderData>;
using ExteriorLimitSetUpParametersHandle = std::shared_ptr<ExteriorLimitSetUpParameters>;
using SphericalTargetSetUpParametersHandle = std::shared_ptr<SphericalTargetSetUpParameters>;
using SphericalLimitSetUpParametersHandle = std::shared_ptr<SphericalLimitSetUpParameters>;
using TargetSetUpParametersHandle = std::shared_ptr<TargetSetUpParameters>;
using TargetSetUpVector = std::vector<TargetSetUpParametersHandle>;


#endif //TUMORSIMULATION_TYPEDEFS_H
