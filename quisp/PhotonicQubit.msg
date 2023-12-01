cplusplus  {{
    #include <backends/interfaces/IQubit.h>
    using quisp::backends::abstract::IQubit;
}}

class IQubit {
    @existingClass;
    @opaque;
};

namespace quisp::messages;

message PhotonicQubit
{
    string message_type = "qubit";
    IQubit *qubitRef;
    bool isLost = false;
    bool isFirst = false;
    bool isLast = false;
    bool has_x_error @getter(hasXError) @setter(setXError) = false;
    bool has_z_error @getter(hasZError) @setter(setZError) = false;
}
