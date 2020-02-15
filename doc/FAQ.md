# Frequently Asked Questions (FAQ)

At this point, since all of our users are AQUA members, this is a set
of questions we frequently ask ourselves.

To be filled in...

* Q: I can't get it to install!!!
  -- A: Welcome to the club.  Getting OMNeT++ to run is the biggest
  hassle.  Once you have that done, everything else is smooth.  There
  _are_ a lot of dependencies on other free software packages, as well
  as on Java.  See [doc/INSTALL.md](doc/INSTALL.md) for additional
  info on troubleshooting.
* Q: Wow, OMNeT++ runs!!! Exciting! ...now what?
  - A: We definitely need better notes on adding QuISP into OMNeT++ and running
  your first QuISP sims.
* Q: Okay, I got the basic first QuISP demo running.  What the heck
  are these .ini and .ned files, and how do I create my own?
  - A: Yup...  See, of course, [the OMNeT++
  documentation])https://doc.omnetpp.org/omnetpp/manual/), but we
  should have more of our own description here, too.
* Q: There are a bunch of parameters in the .ini file that aren't
  described in the OMNeT++ documentation.  What are they?
  - A: Probably, you're looking at the quantum-specific parameters.
  At the moment, the best source of information on them is [Takaaki
  Matsuo's mster's thesis](https://arxiv.org/abs/1908.10758).
* Q: QuISP is fantastic, but I want Feature X, which doesn't
  seem to be included...?
  - A: Time to start looking at the C++ code!  OMNeT++ is very
  sophisticated and rich, i.e. complicated, so you'll have a bit of
  learning to do, but hopefully our existing code serves as a good
  guide to what you'll need.  See also, of course, [the OMNeT++
  documentation](https://doc.omnetpp.org/omnetpp/manual/).
* Q: Can I change the generation of RuleSets without changing C++
  code?
  - A: At the moment, no.
