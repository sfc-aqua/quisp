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
    IQubit *qubit_ref @getter(getQubitRef) @getterForUpdate(getQubitRefForUpdate);
    bool is_lost @getter(isLost) @setter(setLost) = false;
    bool is_first @getter(isFirst) @setter(setFirst) = false;
    bool is_last @getter(isLast) @setter(setLast) = false;
}
