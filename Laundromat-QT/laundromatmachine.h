#ifndef LAUNDROMATMACHINE_H
#define LAUNDROMATMACHINE_H

#include <QString>


enum MACHINEDATA
{
    isLocked,
    drainOpen,
    sinkOpen,
    Speed,
    Rotation,
    runningState,
    activeProgram
};

class LaundromatMachine
{
    public:

        LaundromatMachine();

        void SetState(MACHINEDATA type, int value);
        int GetState(MACHINEDATA type) const;

        void SetName(const QString& name);
        QString GetName() const;

        void SetConnectionID(const QString& name);
        QString GetConnectionID() const;

    private:

        QString name;
        QString connectionName;
        int states[7];
};

#endif // LAUNDROMATMACHINE_H
