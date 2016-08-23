#ifndef GRIDPATHER_H
#define GRIDPATHER_H

#include "quickpather_global.h"

#include <QHash>
#include <QObject>
#include <QPointF>
#include <QVector>

#include "gridpathnode.h"

class GameTimer;
class QuickEntity;
class SteeringAgent;

class GridPathData
{
public:
    QPointF targetPos;
    QVector<QSharedPointer<GridPathNode> > nodes;
};

class QUICKPATHERSHARED_EXPORT GridPather : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int cellSize READ cellSize WRITE setCellSize NOTIFY cellSizeChanged)
    Q_PROPERTY(GameTimer *timer READ timer WRITE setTimer NOTIFY timerChanged)

public:
    GridPather();

    Q_INVOKABLE void moveTo(QuickEntity *entity, const QPointF &pos);
    Q_INVOKABLE void cancel(QuickEntity *entity);

    int cellSize() const;
    void setCellSize(int cellSize);

    GameTimer *timer() const;
    void setTimer(GameTimer *timer);

signals:
    void cellSizeChanged();
    void timerChanged();

private slots:
    void timerUpdated(qreal delta);

private:
    int mCellSize;
    GameTimer *mTimer;
    SteeringAgent *mSteeringAgent;
    QHash<QuickEntity*, GridPathData> mData;
};

#endif // GRIDPATHER_H