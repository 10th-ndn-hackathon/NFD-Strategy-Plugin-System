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

#ifndef NFD_DAEMON_FW_MULTICAST_STRATEGY_HPP
#define NFD_DAEMON_FW_MULTICAST_STRATEGY_HPP

#include "forwarder.hpp"
#include "strategy.hpp"
#include "process-nack-traits.hpp"
#include "retx-suppression-exponential.hpp"
#include <string>
#include <iostream>
#include <experimental/filesystem>

#include <iostream>

namespace nfd {
namespace fw {

const std::string SHARED_OBJECT_PATH("/usr/local/lib/nfd-strategy-plugins");

/** \brief A forwarding strategy that forwards Interests to all FIB nexthops
 */
class PluginStrategy : public Strategy
{
public:
  explicit
  PluginStrategy(Forwarder& forwarder, const Name& name = getStrategyName());

  static const Name&
  getStrategyName();

  void
  afterReceiveInterest(const FaceEndpoint& ingress, const Interest& interest,
                       const shared_ptr<pit::Entry>& pitEntry) override;

  /*void
  afterReceiveNack(const FaceEndpoint& ingress, const lp::Nack& nack,
                   const shared_ptr<pit::Entry>& pitEntry) override;*/

private:
  std::vector<std::string> m_sharedObjects;
};

} // namespace fw
} // namespace nfd

extern "C" {

std::unique_ptr<nfd::fw::Strategy>
getStrategyInstance(nfd::Forwarder& forwarder)
{
  std::cout << "Registering strategy" << std::endl;
  return std::make_unique<nfd::fw::PluginStrategy>(forwarder,
           nfd::fw::PluginStrategy::getStrategyName());
  // ::nfd::fw::Strategy::registerType<nfd::fw::PluginStrategy>();
}

ndn::Name
getStrategyName()
{
  return nfd::fw::PluginStrategy::getStrategyName();
}

}

#endif // NFD_DAEMON_FW_MULTICAST_STRATEGY_HPP
