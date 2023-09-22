//Crude model for satellite visibility: this module checks whether the satellite should be visible or not at this time and sets the Line Of Sight
//parameter of Free-Space channels accordingly.

package modules.Satellite;
@namespace(quisp::modules::Satellite);
simple VisibilityChecker
{
parameters:
    string name = "VisChecker";
    double orbital_period @unit(s) = default(6s);
    double visibility_window @unit(s) = default(1s);
    bool starts_visible = default(true);
    @class(VisibilityChecker);
gates:
    output ctrl;
}
