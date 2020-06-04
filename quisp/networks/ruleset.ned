package networks;

simple Rule
{
    parameters:
        @signal[actual_res](type="int");
        @statistic[actual_res](title="actual resource"; record=vector?, timeavg, max, min; interpolationmode=sample-hold);
    gates:
        //inout dummyQNICLink[];
}