//Crude model for satellite visibility: this module checks whether the satellite should be visible or not at this time and sets the Line Of Sight
//parameter of Free-Space channels accordingly.

package modules.Satellite;
@namespace(quisp::modules::Satellite);
simple PointingSystem
{
parameters:
    string name = "VisChecker";
    double orbital_period @unit(s) = default(1d);
//    double vis_start_coeff = default(0);
//    double vis_end_coeff = default(1);
    @class(PointingSystem);
gates:
    input req;
    output ans;
}
