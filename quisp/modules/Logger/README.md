# Logging

Logger class is responsible for logging data related to simulation.

## Usage

```cpp

using quisp::modules::Logger::LoggerBase

class SomeModule: public cSimpleModule, public LoggerBase {
    void initialize() override {
        // don't forget to initialize the logger
        // LoggerModule defines which logger to use
        initializeLogger(provider);
    }

    void handleMessage(cMessage* msg) override {
        // you can use the logPacket method defined in LoggerBase
        // then the msg logged in the way that is defined at the specified logger
        // the default logger is JsonLogger.
        logPacket("a label for the packet", msg);
    }
};

```
