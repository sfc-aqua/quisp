namespace quisp::messages;

packet Header
{
    int srcAddr;
    int destAddr;
    int hopCount;
}

packet Error extends Header
{
    string error_text;
}
