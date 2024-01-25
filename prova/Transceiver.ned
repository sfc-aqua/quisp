simple Transceiver
{
parameters:
    bool start = default(false);
    bool is_satellite = default(false);
    @signal[received_photon](type=int);
gates:
    input p1;
    output p2;
}
