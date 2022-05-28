#include "canvasdata.h"

CanvasData::CanvasData(QObject *parent) : QObject(parent)
{

}

CanvasData::Tool CanvasData::getTool() {
    return tool;
}

void CanvasData::setTool(Tool tool) {
    this->tool = tool;
}

int CanvasData::getToolSize() {
    return toolSize;
}

void CanvasData::setToolSize(int size) {
    toolSize = size;
}

QColor CanvasData::getToolColor() {
    return toolColor;
}

void CanvasData::setToolColor(QColor color) {
    toolColor = color;
}
