#ifndef CANVASDATA_H
#define CANVASDATA_H

#include <QObject>
#include <QColor>
#include <QPointF>

class CanvasData : public QObject
{
    Q_OBJECT
public:
    enum Tool {
        BRUSH, LINE, ERASER
    };
    QPointF previous;
    bool started = false;

    explicit CanvasData(QObject *parent = nullptr);
    Tool getTool();
    void setTool(Tool tool);
    int getToolSize();
    void setToolSize(int size);
    QColor getToolColor();
    void setToolColor(QColor color);

private:
    Tool tool = Tool::BRUSH;
    int toolSize = 1;
    QColor toolColor = Qt::black;
};

#endif // CANVASDATA_H
