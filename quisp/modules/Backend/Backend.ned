package modules.Backend;
@namespace(quisp::modules::backend);

simple Backend
{
    parameters:
        @class(BackendContainer);
        @display("p=30,40;");
        string backend_type = default("ErrorTrackingBackend");
}
