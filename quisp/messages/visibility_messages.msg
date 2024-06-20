namespace quisp::messages;

packet VisibilityMessage {}

packet VisCheckOutcome extends VisibilityMessage {
    double next_check_time @getter(getNextCheckTime) @setter(setNextCheckTime);
}

packet VisCheckRequest extends VisibilityMessage {
     string out_gate;
     int index;
}

packet VisCheckRetry extends VisibilityMessage {}
