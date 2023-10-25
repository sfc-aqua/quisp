namespace quisp::messages;

packet VisCheckOutcome {
    double next_check_time;
}

packet VisCheckRequest {
     string out_gate;  
     int index; 
}

packet VisCheckRetry {}