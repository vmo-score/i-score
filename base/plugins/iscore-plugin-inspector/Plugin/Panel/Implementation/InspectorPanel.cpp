#include "InspectorPanel.hpp"
#include <Inspector/InspectorWidgetBase.hpp>
#include <Inspector/InspectorSectionWidget.hpp>
#include <Inspector/InspectorWidgetList.hpp>

#include <QVBoxLayout>
#include <QTabWidget>

InspectorPanel::InspectorPanel(iscore::SelectionStack& s, QWidget* parent) :
    QWidget {parent},
    m_layout{new QVBoxLayout{this}},
    m_tabWidget{new QTabWidget{this}},
    m_selectionDispatcher{s}
{
    m_layout->setMargin(0);
    setMinimumWidth(300);
    setMaximumWidth(300);
    m_layout->addWidget(m_tabWidget);
}

void InspectorPanel::newItemsInspected(const Selection& objects)
{
    delete m_tabWidget;

    m_tabWidget = new QTabWidget{this};
    m_layout->addWidget(m_tabWidget);

    m_tabWidget->setTabsClosable(true);

    for(auto object : objects)
    {
        auto widget = InspectorWidgetList::makeInspectorWidget(object->objectName(),
                                                               object,
                                                               m_tabWidget);
        m_tabWidget->addTab(widget, object->objectName());
    }


    connect(m_tabWidget,    &QTabWidget::tabCloseRequested,
            [=] (int index)
    {
        // need m_tabWidget.movable() = false !
        Selection sel = objects;
        sel.removeAt(index);
        m_selectionDispatcher.setAndCommit(sel);
    });
}