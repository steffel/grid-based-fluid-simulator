#ifndef PAINTHANDLER_H
#define PAINTHANDLER_H

#include <QObject>

class QSpinBox;
class QDoubleSpinBox;

class Field;
class PaintTool;
class PaintToolController;
class SimulationViewer;
class VelocityManipulator;

enum PaintType {SMOKE, WALL};

class PaintHandler : public QObject
{
    Q_OBJECT
public:
    PaintHandler(Field* field);
    void connectToSimulationViewer(SimulationViewer* simViewer);
    void connectToSettings(QSpinBox* brushSize, QDoubleSpinBox* hardness);
    void setPaintType(PaintType paintType) {mPaintType = paintType;}
private:
    PaintTool* mSmokePaintTool;
    PaintTool* mWallPaintTool;
    PaintToolController* mSmokePaintToolController;
    PaintToolController* mWallPaintToolController;
    VelocityManipulator* mVelocityManipulator;
    PaintType mPaintType = WALL;
    int mLastSimX = 0;
    int mLastSimY = 0;
    int mLastViewX = 0;
    int mLastViewY = 0;
    qint64 mTimer;
public slots:
    void leftClicked(int x, int y);
    void leftMoved(int x, int y);
    void rightMouseClick(int simX, int simY, int viewX, int viewY);
    void rightMouseMove(int simX, int simY, int viewX, int viewY);
};

#endif // PAINTHANDLER_H