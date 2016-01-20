#include "laundromatmachine.h"

LaundromatMachine::LaundromatMachine() : name("")
{
    for(int i = 0; i < 7;i++)
    {
        states[i] = 0;
    }

}

void LaundromatMachine::SetState(MACHINEDATA type, int value)
{
    states[(int)type] = value;
}

int LaundromatMachine::GetState(MACHINEDATA type) const
{
    return states[(int)type];
}

void LaundromatMachine::SetName(const QString& newName)
{
    name = newName;
}

QString LaundromatMachine::GetName() const
{
    return name;
}

void LaundromatMachine::SetConnectionID(const QString& newName)
{
    connectionName = newName;
}

QString LaundromatMachine::GetConnectionID() const
{
    return connectionName;
}
