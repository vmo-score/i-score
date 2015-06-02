#pragma once
#include "Process/Temporal/StateMachines/Tools/ScenarioToolState.hpp"
#include <iscore/selection/SelectionDispatcher.hpp>

class SelectionTool : public ScenarioToolState
{
    public:
        SelectionTool(ScenarioStateMachine& sm);

        void on_pressed() override;
        void on_moved() override;
        void on_released() override;

        void setSelectionArea(const QRectF& area);


    private:
        QState* m_singleSelection{};
        QState* m_multiSelection{};

        iscore::SelectionDispatcher m_dispatcher;

        QPointF m_initialPoint;
        QPointF m_movePoint;

        QState* m_waitState{};
};