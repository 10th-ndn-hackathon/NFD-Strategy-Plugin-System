# 10th Hackathon Strategy Plugin System

## PluginStrategy

- Added a sample PluginStratey that is not compiled as a part of NFD
- PluginStrategy is compiled as a shared library and installed in /usr/local/lib/nfd-strategy-plugins
  - Don't "use" core-objects or daemon object in shlib - strange link errors about overflow and recommendation of using -fPIC
- Need to put the derived functions in extern "C" because C++ name mangling
- NFD logger does not seem to work in PluginStrategy - so changed to ndn-cxx logger
  - But having problems with configuring NDN_LOG for NFD (nfd.conf always overrides)
  - So added couts as well!
- Do not try to call registerType (i.e. NFD_REGISTER_STRATEGY) from extern "C" function in PluginStrategy
  - The registry returned will be different
  - Have tried making registerType, NFD_REGISTER_STRATEGY also as extern "C"

## StrategyChoice

- When nfdc strategy set triggers insert, we look for strategies in /usr/local/lib/nfd-strategy-plugins
  - That is if the Strategy is not found in already registered Strategy
- If Strategy is found with the name in the shared file, it is loaded and created

## Testing

- Compile and install NFD and check that the plugin strategy, libnfd-strategy.so.0.7.1 is located at

   /usr/local/lib/nfd-strategy-plugins/

- Set the following logs in /usr/local/etc/ndn/nfd.conf:

    PluginStrategy TRACE
    StrategyChoice TRACE
    Strategy TRACE

- Start NFD and try to set the strategy in a new terminal:

    nfdc strategy set /plugin /localhost/nfd/strategy/plugin/%FD%01

- Check nfdc strategy has the line:

    prefix=/plugin strategy=/localhost/nfd/strategy/plugin/%FD%01

- Send an Interest:

    ndnping -c1 /plugin

- See the lines in cout (or NDN_LOG log if that works for you):

    Received Interest /plugin/ping/12730949938297044207?MustBeFresh&Nonce=1d31d516

- STILL WORKING ON HOW TO UPDATE VERSION OF PLUGINSTRATEGY, FIX BUG, AND, LOAD A REPLACEMENT STRATEGY
  - Either some bug or some problem in the shared-object!

## Future Work/Conclusion

- Decide on whether to make all Strategies as plugin
  - Or just have the plugin system as a backup
- Plugin strategies can be used to deliver quick fixes to existing Strategies
  - So this is an argument to make all Strategies as plugin so that we don't have to replicate them
- Plugin system can be used to load experimental Strategies on the testbed
  - Can test strategies developed in ndnSIM/MiniNDN based publications which were/cannot be not merged in NFD
- Maybe create a folder such as daemon/fw/strategy-plugins where plugin strategies can be there for wscript to decide
  - Only compile them when a flag is provided

## Resources

- [Making a Plugin System](http://www.cplusplus.com/articles/48TbqMoL/)
- [Dynamic Loading Example](https://github.com/xbanks/dynamic-loading-example)
- [dlsym manpage](https://man7.org/linux/man-pages/man3/dlsym.3.html)
- [Compiling NFD as shared object](https://github.com/named-data-mobile/android-crew-staging/blob/master/patches/packages/nfd/0.7.0/0002-Build-patches.patch)

# NFD - Named Data Networking Forwarding Daemon

![Language](https://img.shields.io/badge/C%2B%2B-14-blue.svg)
[![Build Status](https://travis-ci.org/named-data/NFD.svg?branch=master)](https://travis-ci.org/named-data/NFD)
![Latest Version](https://img.shields.io/github/tag/named-data/NFD.svg?color=darkkhaki&label=latest%20version)

## Overview

NFD is a network forwarder that implements and evolves together with the Named Data
Networking (NDN) [protocol](https://named-data.net/doc/NDN-packet-spec/current/).
Since the initial public release in 2014, NFD has been a core component of the
[NDN Platform](https://named-data.net/codebase/platform/).

The main design goal of NFD is to support diverse experimentation of NDN technology.  The
design emphasizes *modularity* and *extensibility* to allow easy experiments with new
protocol features, algorithms, new applications.  We have not fully optimized the code for
performance.  The intention is that performance optimizations are one type of experiments
that developers can conduct by trying out different data structures and different
algorithms; over time, better implementations may emerge within the same design framework.

NFD will keep evolving in three aspects: improvement of the modularity framework, keeping
up with the NDN protocol spec, and addition of other new features. We hope to keep the
modular framework stable and lean, allowing researchers to implement and experiment with
various features, some of which may eventually work into the protocol spec.

## Documentation

See [`docs/INSTALL.rst`](docs/INSTALL.rst) for compilation and installation instructions.

Extensive documentation is available on NFD's [homepage](https://named-data.net/doc/NFD/).

## Reporting bugs

Bug reports and feedback are highly appreciated and can be submitted through the
[NFD issue tracker](https://redmine.named-data.net/projects/nfd/issues) or the
[ndn-interest mailing list](http://www.lists.cs.ucla.edu/mailman/listinfo/ndn-interest).

## Contributing

NFD is developed by a community effort.  Although the first release was mostly done by the
members of [NSF-sponsored NDN project team](https://named-data.net/project/participants/),
it already contains significant contributions from people outside the project team (see
[`AUTHORS.md`](AUTHORS.md)).  We strongly encourage participation from all interested parties,
since broader community support is key for NDN to succeed as a new Internet architecture.

If you are new to the NDN software community, please read [`README-dev.md`](README-dev.md)
and the [Contributor's Guide](https://github.com/named-data/.github/blob/master/CONTRIBUTING.md)
to get started.

## License

NFD is a free and open-source software package licensed under the GPL version 3 and
is the centerpiece of our committement to making NDN's core technology free and open
to all Internet users and developers. For more information about licensing, refer to
[`COPYING.md`](COPYING.md).
