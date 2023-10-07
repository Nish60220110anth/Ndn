#include "ns3/node-container.h"
#include "ns3/node-list.h"
#include "ns3/command-line.h"
#include "ns3/simulator.h"
#include "ns3/string.h"
#include "ns3/double.h"
#include "ns3/uinteger.h"
#include "ns3/ptr.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/names.h"

#include "ns3/ndnSIM/helper/ndn-app-helper.hpp"
#include "ns3/ndnSIM/helper/ndn-global-routing-helper.hpp"
#include "ns3/ndnSIM/helper/ndn-stack-helper.hpp"
#include "ns3/ndnSIM/utils/tracers/ndn-l3-rate-tracer.hpp"
#include "ns3/ndnSIM/utils/tracers/ndn-cs-tracer.hpp"
#include "ns3/ndnSIM/utils/tracers/ndn-app-delay-tracer.hpp"

#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <functional>


/**
 * \brief Simple 4 node bus topology
 *
 * \subsection Why
 *
 * To know how entries in the fib and cs are getting updated
 *
 * Topology:
 *   (%)                                        (+)
 * /\ _________ /\ ___________ /\ ___________ /\
 * \/           \/             \/             \/
 *
 *  %  => Consumer
 *  +  => Producer
 *
 * (Note: Nodes are referenced using 1 based indexing but in code it is using 0 based)
 * (So node 1 in text denotes the first node from left to right. Last node is denoted by node 4)
 *
 * Simulation:
 *
 * #Idea : Initially there is no fib entries filled in node 1,2 but there is in node 3,4.
 * Different strategies is employed in node 1,2 and node 3,4.
 *
 * We want some nodes to be unaware of the path (we chose it to be node 1,2). Then
 * we use access-strategy to dynamically update the fib entries. In node 3,4 , as there
 * is enough information filled , there will be no fib updates.
 *
 * (i) Write custom tracer to trace content store hit/miss (done)
 * (ii) Fib updates tracer
 *
 *
 * Doubt:
 * 1) What happens if interest packet contains the next hop where it want to enter ?
 * At first ,whether it can store those info or not ?
 *
 * Yes! it is stored. Initially when a packet is arrived , the tag is not immediately
 * looked upon. Only when there is content miss , then it is used.
 *
*/

#include "ns3/ptr.h"
#include "ns3/simple-ref-count.h"
#include <ns3/nstime.h>
#include <ns3/event-id.h>
#include <ns3/node-container.h>

#include <ns3/ndnSIM/NFD/core/common.hpp>
#include <ndn-cxx/lp/tags.hpp>
#include <ns3/ndn-all.hpp>

#include <memory>
#include <iostream>

namespace Printer {
  void PrintFIB(std::shared_ptr<ns3::ndn::nfd::fib::Fib> fib) {
    for (const ns3::ndn::nfd::fib::Entry& entry : *fib) {

    }
  }
}


int main(int argc, char* argv[]) {
  // std::shared_ptr<ns3::ndn::Interest> interest = std::make_shared<ns3::ndn::Interest>();
  // interest->setName(*new ns3::ndn::Name("sample"));
  // interest->setTag<ns3::ndn::lp::NextHopFaceIdTag>(std::make_shared<ns3::ndn::lp::NextHopFaceIdTag>(
  //   static_cast<uint64_t>(5)
  // ));
  // interest->setInterestLifetime(ns3::ndn::time::milliseconds(ns3::Seconds(6).GetMilliSeconds()));

  // std::shared_ptr<ns3::ndn::lp::NextHopFaceIdTag> tag =
  //   interest->getTag<ns3::ndn::lp::NextHopFaceIdTag>();

  // std::cout << "TypeId " << tag->get();
  ns3::NodeContainer nodes;
  nodes.Create(1);

  std::string oldName = ns3::Names::FindName(nodes.Get(0)->GetObject<ns3::Node>());
  ns3::Names::Add("Node-0-NewName", nodes.Get(0)->GetObject<ns3::Node>());
  std::string newName = ns3::Names::FindName(nodes.Get(0)->GetObject<ns3::Node>());

  std::cout << "OldName " << oldName << " NewName " << newName << "\n";
}
