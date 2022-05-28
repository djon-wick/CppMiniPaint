#ifndef CANVASCONTROL_H
#define CANVASCONTROL_H

#include <QObject>
#include <QPointF>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <canvasdata.h>

class CanvasControl : public QObject
{
    Q_OBJECT
public:
    explicit CanvasControl(QObject *parent = nullptr);
    ~CanvasControl();
    QGraphicsScene* getCanvas();
    void startDrawBrush(CanvasData *data, QMouseEvent *event);
    void drawBrush(CanvasData *data, QMouseEvent *event);
    void startDrawLine(CanvasData *data, QMouseEvent *event);
    void drawLine(CanvasData *data, QMouseEvent *event);

private:
    QGraphicsScene* canvas;
    QGraphicsLineItem* item = nullptr;
};

#endif // CANVASCONTROL_H
