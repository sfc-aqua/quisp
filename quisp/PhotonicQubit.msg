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
    bool isLost @getter(isLost) @setter(setLost) = false;
    bool isFirst @getter(isFirst) @setter(setFirst) = false;
    bool isLast @getter(isLast) @setter(setLast) = false;
    bool xError @getter(hasXError) = false;
    bool zError @getter(hasZError) = false;
}
