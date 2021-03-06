/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014-2020,  Regents of the University of California,
 *                           Arizona Board of Regents,
 *                           Colorado State University,
 *                           University Pierre & Marie Curie, Sorbonne University,
 *                           Washington University in St. Louis,
 *                           Beijing Institute of Technology,
 *                           The University of Memphis.
 *
 * This file is part of NFD (Named Data Networking Forwarding Daemon).
 * See AUTHORS.md for complete list of NFD authors and contributors.
 *
 * NFD is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * NFD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * NFD, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plugin-strategy.hpp"
#include <ndn-cxx/util/logger.hpp>
#include <iostream>

namespace nfd {
namespace fw {

// This should probably be dynamic (and not at compile time),
// assuming the target NFD has no clue what strategy you loading
// (Even if we do this, the registry returned in Strategy is might be different due to extern C
// NFD_REGISTER_STRATEGY(PluginStrategy);

// NFD_LOG_INIT(PluginStrategy);

NDN_LOG_INIT(nfd.plugin.PluginStrategy);

PluginStrategy::PluginStrategy(Forwarder& forwarder, const Name& name)
  : Strategy(forwarder)
{
  ParsedInstanceName parsed = parseInstanceName(name);
  if (!parsed.parameters.empty()) {
    NDN_THROW(std::invalid_argument("PluginStrategy does not accept parameters"));
  }
  if (parsed.version && *parsed.version != getStrategyName()[-1].toVersion()) {
    NDN_THROW(std::invalid_argument(
      "PluginStrategy does not support version " + to_string(*parsed.version)));
  }
  this->setInstanceName(makeInstanceName(name, getStrategyName()));

  NDN_LOG_INFO("Loaded PluginStrategy");
  std::cout << "\n---------------------Loaded PluginStrategy------------------\n" << std::endl;
}

const Name&
PluginStrategy::getStrategyName()
{
  static Name strategyName("/localhost/nfd/strategy/plugin/%FD%03");
  return strategyName;
}

extern "C" {

void
PluginStrategy::afterReceiveInterest(const FaceEndpoint& ingress, const Interest& interest,
                                     const shared_ptr<pit::Entry>& pitEntry)
{
  NDN_LOG_DEBUG("Received Interest " << interest);
  std::cout << "\n------------------Received Interest " << interest << std::endl;
}

}

/*void
PluginStrategy::afterReceiveNack(const FaceEndpoint& ingress, const lp::Nack& nack,
                                    const shared_ptr<pit::Entry>& pitEntry)
{
  this->processNack(ingress.face, nack, pitEntry);
}*/

} // namespace fw
} // namespace nfd
