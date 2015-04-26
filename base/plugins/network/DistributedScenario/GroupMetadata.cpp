#include "GroupMetadata.hpp"


GroupMetadata::GroupMetadata(
        const QObject* element,
        id_type<Group> id,
        QObject* parent):
    iscore::ElementPluginModel{parent},
    m_element{element},
    m_id{id}
{

}

GroupMetadata* GroupMetadata::clone(const QObject *element, QObject *parent) const
{
    auto grp = new GroupMetadata{element, this->group(), parent};
    return grp;
}

QString GroupMetadata::plugin() const
{
    return staticPluginName();
}

void GroupMetadata::serialize(const VisitorVariant& vis) const
{
    if(vis.identifier == DataStream::type())
    {
        static_cast<DataStream::Serializer*>(vis.visitor)->readFrom(*this);
        return;
    }
    else if(vis.identifier == JSON::type())
    {
        static_cast<JSON::Serializer*>(vis.visitor)->readFrom(*this);
        return;
    }

    Q_ASSERT(false);
}

void GroupMetadata::setGroup(const id_type<Group>& id)
{
    if(id != m_id)
    {
        m_id = id;
        emit groupChanged(id);
    }
}