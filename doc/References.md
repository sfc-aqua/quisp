# References

QuISP builds upon and contributes to the research literature on quantum repeaters.

## Orientation

If you're not familiar with quantum networking at all, at IETF 104,
Tracy Northup and Rod Van Meter did a [two-hour
tutorial](https://www.youtube.com/watch?v=9nfaYAU92tY&feature=youtu.be),
which is uploaded to the IETF YouTube channel.

## The bible

The most important document on QuISP design and use is

* Takaaki Matsuo, "Simulation of a Dynamic, RuleSet-based Quantum
	Network", master's thesis, Keio University Graduate School of
	Media and Governance, Sept. 2019.
	Available as [arXiv:1908.10758
	[quant-ph]](https://arxiv.org/abs/1908.10758)

See also [Van Meter's Virtual March Meeting 2020 talk](https://virtualmarchmeeting.com/presentations/ruleset-based-operation-of-the-quantum-internet).

## General references

If you need to know about generations and stages of development,
carrying us from single-application quantum key distribution (QKD)
networks to a full Quantum Internet, see these three:

* Van Meter, _Quantum Networking_, Wiley-iSTE, 2014.
* Muralidharan et al., "Optimal architectures for long distance
  quantum communication", Scientific Reports 6, 20463, 2016.
* Wehner et al., "Quantum internet: A vision for the road ahead",
  Science 362, 6412, 2018.

At the moment, only first generation (1G) protocols have been implemented.

Also, as of this writing, the [Quantum Internet Research Group
(QIRG)](https://datatracker.ietf.org/rg/qirg/about/) is working on a
document titled, ["Architectural Principles for a Quantum
Internet"](https://datatracker.ietf.org/doc/draft-irtf-qirg-principles/)
that will be of tremendous use.

## Specific design decisions

In addition to Takaaki's thesis, the design decisions incorporated
here have evolved over fifteen years, and can be found in Rodney Van
Meter's research papers.

For details of the link architectures (which we call MM, MIM, MSM),
the best source is

* Jones et al., "Design and analysis of communication protocols for
  quantum repeater networks", New Journal of Physics 18(8), 083015,
  2016.

As of this writing, a paper is being written detailing the simulation
of non-Pauli errors while working in the error basis.  (There is some
description of this in Takaaki's thesis, above.)

For more discussion of the Quantum Recursive Network Architecture, our
proposed architecture for the entire Quantum Internet, see [Recursive
Quantum Repeater Networks](https://arxiv.org/abs/1105.1238).

For references on synthetic network topologies, see [Background on topology creation](Background%20on%20topology%20creation.md).

*TODO*: add a reference on match-and-action software defined
 networking (SDN).
