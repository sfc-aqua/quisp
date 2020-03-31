
*Note: this file is an early design document, but might be updated as the version goes up.*

A workload is needed when creating one of our [[Datasets]].

A workload consists of:

- A set of workload elements
- A traffic pattern

# Workload Elements #

A workload element is an application. Each of these must specify the desired fidelity.

- IPsec with QKD: point-to-point (campus-to-campus), long-lived Bell pair streams. Long distance, random pairs. Intermediate fidelity should be adequate.
- IPsec with TLS: e-commerce topology, with randomly placed "clients" connecting to a centralized service. Connections live long enough to establish QKD (e.g., check end-to-end Bell pair fidelity), then create a few thousand Bell pairs for a shared, secret transaction key. Intermediate fidelity should be adequate.
- Quantum Byzantine agreement: a set of five nodes (here, we will only use five), working in a specific pattern: fanout from a centralized point (a few hundred Bell pairs?), then all-to-all communication (a few hundred more). Amin to provide exact numbers. Topology-wise, since this is a shared group function, most likely to be within a single network rather than randomly placed throughout the Internet. QBA will require high fidelity, but the exact value is not yet known.

# Traffic Pattern #

The original plan was to use something like a gravity model for placement, but each of the elements above appears to have a certain set of characteristics. What shall we do here?

The first link describes the gravity model:

- https://www.cs.utexas.edu/~yzhang/papers/tomogravity-sigm03.pdf
- http://web2.research.att.com/export/sites/att_labs/techdocs/TD-5CXQ97.pdf
- https://en.wikipedia.org/wiki/Traffic_generation_model
- https://www.cc.gatech.edu/~dovrolis/Courses/8803_F03/mehmet.ppt
