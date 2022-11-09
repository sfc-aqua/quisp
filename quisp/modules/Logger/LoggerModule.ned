package modules.Logger;
@namespace(quisp::modules::Logger);

simple Logger
{
    @class(LoggerModule);
    @display("p=30,100;");
    
    bool enable_log = default(true);
    string log_filename;

    string logger = default("JsonLogger");
}
