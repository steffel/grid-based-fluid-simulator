#ifndef SIMULATIONFIELDCONTROLLER_H
#define SIMULATIONFIELDCONTROLLER_H

#include <QObject>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include "field.h"
#include "velocitymanipulator.h"
#include "simulationviewer.h"

class SimulationField;

class SimulationFieldController : public QObject
{
    Q_OBJECT
public:
    SimulationFieldController(SimulationField* field, QObject* parent = nullptr);
    void connectToViewer(SimulationViewer* simViewer);
    void connectToSimSettingsCheckboxes(QCheckBox* forwardAdvectionToggle, QCheckBox* reverseAdvectionToggle, QCheckBox* pressureToggle);
    void connectToResetButton(QPushButton* resetBtn);
    void connectEdgeCaseSelector(QComboBox* edgeCaseSelector);
private:
    VelocityManipulator mVelocityManipulator;
    SimulationField* mSimField;
    int mLastSimX = 0;
    int mLastSimY = 0;
    int mLastViewX = 0;
    int mLastViewY = 0;
    qint64 mTimer;
public slots:
    void rightMouseClick(int simX, int simY, int viewX, int viewY);
    void rightMouseMove(int simX, int simY, int viewX, int viewY);
    void edgeCaseChanged(int index);
};

#endif // SIMULATIONFIELDCONTROLLER_H
