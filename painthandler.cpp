#include "painthandler.h"
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateTime>
#include "field.h"
#include "painttool.h"
#include "painttoolcontroller.h"
#include "simulationviewer.h"
#include "velocitymanipulator.h"

const float INIT_POWER = 0.2;
const int INIT_MANIPULATION_AREA = 5;

PaintHandler::PaintHandler(Field* field)
{
    mSmokePaintTool = new PaintTool(field->getSmokeDensityGrid());
    mWallPaintTool = new PaintTool(field->getWalls());
    mSmokePaintToolController = mSmokePaintTool->getController();
    mWallPaintToolController = mWallPaintTool->getController();
    mVelocityManipulator = new VelocityManipulator(field);
    mVelocityManipulator->setPower(INIT_POWER);
    mVelocityManipulator->setManipulationArea(INIT_MANIPULATION_AREA);
}

void PaintHandler::connectToSimulationViewer(SimulationViewer *simViewer)
{
    connect(simViewer, &SimulationViewer::mouseLeftButtonClicked, this, &PaintHandler::leftClicked);
    connect(simViewer, &SimulationViewer::mouseLeftButtonMoved, this, &PaintHandler::leftMoved);
    connect(simViewer, &SimulationViewer::mouseRightButtonClicked, this, &PaintHandler::rightMouseClick);
    connect(simViewer, &SimulationViewer::mouseRightButtonMoved, this, &PaintHandler::rightMouseMove);
}

void PaintHandler::connectToSettings(QSpinBox *brushSize, QDoubleSpinBox *hardness)
{
    mSmokePaintToolController->connectToBrushSettings(brushSize, hardness);
    mWallPaintToolController->connectToBrushSettings(brushSize, hardness);
}

void PaintHandler::leftClicked(int x, int y)
{
    if(mPaintType == SMOKE) {
        mSmokePaintTool->drawPoint(x, y);
    } else if(mPaintType == WALL) {
        mWallPaintTool->drawPoint(x, y);
    }
}

void PaintHandler::leftMoved(int x, int y)
{
    if(mPaintType == SMOKE) {
        mSmokePaintTool->drawPoint(x, y);
    } else if(mPaintType == WALL) {
        mWallPaintTool->drawPoint(x, y);
    }
}

void PaintHandler::rightMouseClick(int simX, int simY, int viewX, int viewY)
{
    if(mPaintType == SMOKE) {
        this->mLastSimX = simX;
        this->mLastSimY = simY;
        this->mLastViewX = viewX;
        this->mLastViewY = viewY;
        this->mTimer = QDateTime::currentMSecsSinceEpoch();
    } else if(mPaintType == WALL) {
        mWallPaintTool->resetPoint(simX, simY);
    }
}

void PaintHandler::rightMouseMove(int simX, int simY, int viewX, int viewY)
{
    if(mPaintType == SMOKE) {
        qint64 deltaTime = QDateTime::currentMSecsSinceEpoch() - this->mTimer;
        float horizontalSpeed = (float)(viewX - this->mLastViewX) / (float)deltaTime;
        float verticalSpeed = (float)(viewY - this->mLastViewY) / (float)deltaTime;
        this->mVelocityManipulator->move(this->mLastSimX, this->mLastSimY, horizontalSpeed, verticalSpeed);
        // Reset all variables for the next iteration
        this->mLastSimX = simX;
        this->mLastSimY = simY;
        this->mLastViewX = viewX;
        this->mLastViewY = viewY;
        this->mTimer = QDateTime::currentMSecsSinceEpoch();
    } else if(mPaintType == WALL) {
        mWallPaintTool->resetPoint(simX, simY);
    }
}