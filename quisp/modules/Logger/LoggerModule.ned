package modules.Logger;
@namespace(quisp::modules::Logger);

simple Logger
{
    @class(LoggerModule);
    @display("p=30,100;");
    
    string log_filename;

    string logger = default("JsonLogger");
}
