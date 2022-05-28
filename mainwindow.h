#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvascontrol.h"
#include <QTimer>
#include <QGraphicsSceneMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_timer();
    void setToolColor(QColor color);
    void on_toolBrush_clicked();
    void on_toolSize_valueChanged(int value);
    void on_toolColor_clicked();
    void on_toolLine_clicked();

    void on_toolEraser_clicked();

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    CanvasData* canvasData;
    CanvasControl* canvasControl;
    QTimer* timer;

    void init();
};

#endif // MAINWINDOW_H
