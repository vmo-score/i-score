#include "ScenarioActions.hpp"
#include <Scenario/Control/ScenarioControl.hpp>
ScenarioActions::ScenarioActions(iscore::ToplevelMenuElement menuElt, ScenarioControl *parent) :
    QObject(parent),
    m_parent{parent},
    m_menuElt{menuElt}
{

}

QList<QAction*> ScenarioActions::actions() const
{
    return {};
}
