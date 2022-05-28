#include "canvascontrol.h"
#include <QPen>
#include <QLineF>

CanvasControl::CanvasControl(QObject *parent) : QObject(parent)
{
    canvas = new QGraphicsScene(parent);
}

CanvasControl::~CanvasControl() {
    delete canvas;
}

QGraphicsScene* CanvasControl::getCanvas() {
    return canvas;
}

void CanvasControl::startDrawBrush(CanvasData* data, QMouseEvent *event) {
    canvas->addEllipse(event->pos().x() - data->getToolSize() / 2,
               event->pos().y() - data->getToolSize() / 2,
               data->getToolSize(),
               data->getToolSize(),
               QPen(Qt::NoPen),
               QBrush(data->getToolColor()));
    data->previous = event->pos();
}

void CanvasControl::drawBrush(CanvasData* data, QMouseEvent *event) {
    canvas->addLine(data->previous.x(),
            data->previous.y(),
            event->pos().x(),
            event->pos().y(),
            QPen(data->getToolColor(), data->getToolSize(), Qt::SolidLine, Qt::RoundCap));
    data->previous = event->pos();
}

void CanvasControl::startDrawLine(CanvasData* data, QMouseEvent *event) {
    item = nullptr;
    data->previous = event->pos();
}

void CanvasControl::drawLine(CanvasData* data, QMouseEvent *event) {
    if (item != nullptr)
        canvas->removeItem(item);
    auto current = QPointF(event->pos().x(), event->pos().y());
    auto line = QLineF(data->previous, current);
    item = new QGraphicsLineItem(line);
    item->setPen(QPen(data->getToolColor(), data->getToolSize(), Qt::SolidLine, Qt::RoundCap));
    item->setLine(line);
    canvas->addItem(item);
}
