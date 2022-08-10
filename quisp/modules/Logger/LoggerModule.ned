package modules.Logger;
@namespace(quisp::modules::Logger);

simple Logger
{
    @class(LoggerModule);
    string log_filename;

    string logger = default("JsonLogger");
}
