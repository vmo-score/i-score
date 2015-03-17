#include <iscore/serialization/DataStreamVisitor.hpp>
#include <iscore/serialization/JSONVisitor.hpp>
#include "State.hpp"
#include "Message.hpp"


template<>
void Visitor<Reader<DataStream>>::readFrom(const State& state)
{
    m_stream << state.m_data;
    insertDelimiter();
}

template<>
void Visitor<Reader<JSON>>::readFrom(const State& state)
{
    m_obj["Type"] = int(state.data().userType());
    if(state.data().canConvert<State>())
    {
        m_obj["Data"] = toJsonObject(state.data().value<State>());
    }
    else if(state.data().canConvert<StateList>())
    {
        m_obj["Data"] = toJsonArray(state.data().value<StateList>());
    }
    else if(state.data().canConvert<Message>())
    {
        m_obj["Data"] = toJsonObject(state.data().value<Message>());
    }
    else if(state.data().canConvert<MessageList>())
    {
        m_obj["Data"] = toJsonArray(state.data().value<MessageList>());
    }
    else
    {
        qDebug() << "TODO";
    }
}

template<>
void Visitor<Writer<DataStream>>::writeTo(State& state)
{
    m_stream >> state.m_data;

    checkDelimiter();
}

template<>
void Visitor<Writer<JSON>>::writeTo(State& state)
{
    QString t = QVariant::typeToName(m_obj["Type"].toInt());
    if("State" == t)
    {
        state = fromJsonObject<State>(m_obj["Data"].toObject());
    }
    else if("StateList" == t)
    {
        StateList t;
        fromJsonArray(m_obj["Data"].toArray(), t);
        state = t;
    }
    else if("Message" == t)
    {
        state = fromJsonObject<Message>(m_obj["Data"].toObject());
    }
    else if("MessageList" == t)
    {
        MessageList t;
        fromJsonArray(m_obj["Data"].toArray(), t);
        state = t;
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "TODO";
    }
/*
    m_obj["Type"] = state.data().type();
    if(state.data().canConvert<State>())
    {
        m_obj["Data"] = toJsonObject(state.data().convert<State>());
    }
    else if(state.data().canConvert<StateList>())
    {
        m_obj["Data"] = toJsonArray(state.data().convert<StateList>());
    }
    else if(state.data().canConvert<Message>())
    {
        m_obj["Data"] = toJsonObject(state.data().convert<Message>());
    }
    else if(state.data().canConvert<MessageList>())
    {
        m_obj["Data"] = toJsonArray(state.data().convert<MessageList>());
    }
    else if(state.data().canConvert<ProcessState>())
    {
        qDebug() << "TODO";
    }
*/
    //mess.m_data = m_obj["State"].toObject().toVariantMap()["Data"];
}

#include "Message.hpp"

template<>
void Visitor<Reader<DataStream>>::readFrom(const Message& mess)
{
    m_stream << mess.address << mess.value;
    insertDelimiter();
}

template<>
void Visitor<Reader<JSON>>::readFrom(const Message& mess)
{
    m_obj["Address"] = mess.address;
    m_obj["Value"] = mess.value.toString();
}

template<>
void Visitor<Writer<DataStream>>::writeTo(Message& mess)
{
    m_stream >> mess.address >> mess.value;

    checkDelimiter();
}

template<>
void Visitor<Writer<JSON>>::writeTo(Message& mess)
{
    mess.address = m_obj["Address"].toString();
    mess.value = QJsonValue(m_obj["Value"]).toVariant();
}
