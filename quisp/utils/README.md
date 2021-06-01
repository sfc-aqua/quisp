# quisp::utils

## ComponentProvider

`ComponentProvider` is inside quisp modules.
This class provides the way to access other modules from quisp modules.
This class adopts [Strategy Pattern](https://en.wikipedia.org/wiki/Strategy_pattern).
`ComponentProvider` itself doesn't know how to get other module, actual behavior defined in a class inherits `IComponentProviderStrategy`.

## Unit Testing

we can change a returned module from `ComponentProvider` by creating a class inherits `IComponentProviderStrategy`.
OMNeT++'s architecture is so great, but it's hard to write unit tests, so this mechanism solves the problem.
