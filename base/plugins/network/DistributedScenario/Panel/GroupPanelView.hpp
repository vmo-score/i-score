#pragma once
#include <iscore/plugins/panel/PanelViewInterface.hpp>
class GroupManager;
class Session;

namespace iscore
{
    class View;
}

class GroupPanelView : public iscore::PanelViewInterface
{
    public:
        GroupPanelView(iscore::View* v);

        QWidget* getWidget() override;
        Qt::DockWidgetArea defaultDock() const override;

        void setView(const GroupManager* mgr,
                     const Session* session);

        void setEmptyView();

    private:
        QWidget* m_widget{}, *m_subWidget{};
};