cplusplus {{
    #include <modules/PhysicalConnection/BSA/types.h>
    using quisp::physical::types::BSAClickResult;
}}

class BSAClickResult {
    @existingClass;
    @opaque;
};

import base_messages;

namespace quisp::messages;

packet BSMNotificationTimeout {}

packet BatchClickEvent {
    BSAClickResult click_results[] @appender(appendClickResults) @getter(getClickResults) @sizeGetter(numberOfClicks);
}

// Used for MSM.
packet SingleClickResult extends Header {
    BSAClickResult click_result @setter(setClickResult) @getter(getClickResult);
    int qnic_index @getter(getQnicIndex) @setter(setQnicIndex);
}

packet CancelBSMTimeOutMsg {}
