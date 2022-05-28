#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QPixmap>
#include <QBitmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    ui->canvas->setScene(canvasControl->getCanvas());
}

MainWindow::~MainWindow() {
    delete ui;
    delete canvasControl;
    delete canvasData;
}

void MainWindow::on_timer()
{
    timer->stop();
    canvasControl->getCanvas()->setSceneRect(0, 0, ui->canvas->width(), ui->canvas->height());
    ui->toolColor->setIconSize(QSize(60 * ui->toolSize->value() / 100, 60 * ui->toolSize->value() / 100));
}

void MainWindow::init() {
    canvasData = new CanvasData();
    canvasControl = new CanvasControl();

    canvasData->setToolSize(ui->toolSize->value());
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::on_timer);
    timer->start(10);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(10);
    QWidget::resizeEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    canvasData->started = true;
    if (canvasData->getTool() == CanvasData::Tool::BRUSH) {
        canvasControl->startDrawBrush(canvasData, event);
    }
    if (canvasData->getTool() == CanvasData::Tool::LINE) {
        canvasControl->startDrawLine(canvasData, event);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (canvasData->getTool() == CanvasData::Tool::BRUSH && canvasData->started) {
        canvasControl->drawBrush(canvasData, event);
    }
    if (canvasData->getTool() == CanvasData::Tool::LINE && canvasData->started) {
        canvasControl->drawLine(canvasData, event);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    canvasData->started = false;
}

void MainWindow::on_toolColor_clicked()
{
    QColorDialog *colorDialog = new QColorDialog(this);
    colorDialog->setOptions(QColorDialog::DontUseNativeDialog | QColorDialog::NoButtons);
    colorDialog->show();
    connect(colorDialog, &QColorDialog::currentColorChanged, this, &MainWindow::setToolColor);

    QPixmap pixmap = QPixmap(":prefix/images/color.png");
    QBitmap mask = pixmap.createMaskFromColor(Qt::black, Qt::MaskOutColor);
    pixmap.fill(colorDialog->selectedColor());
    pixmap.setMask(mask);
    ui->toolColor->setIcon(QIcon(pixmap));
}

void MainWindow::setToolColor(QColor color) {
    QPixmap pixmap = QPixmap(":prefix/images/color.png");
    QBitmap mask = pixmap.createMaskFromColor(Qt::black, Qt::MaskOutColor);
    pixmap.fill(color);
    pixmap.setMask(mask);
    ui->toolColor->setIcon(QIcon(pixmap));
    canvasData->setToolColor(color);
}

void MainWindow::on_toolSize_valueChanged(int value)
{
    canvasData->setToolSize(value);
    ui->toolColor->setIconSize(QSize(60 * value / 100, 60 * value / 100));
}

void MainWindow::on_toolBrush_clicked()
{
    canvasData->setTool(CanvasData::Tool::BRUSH);
    ui->toolBrush->setChecked(true);
    ui->toolLine->setChecked(false);
    ui->toolEraser->setChecked(false);
}

void MainWindow::on_toolLine_clicked()
{
    canvasData->setTool(CanvasData::Tool::LINE);
    ui->toolBrush->setChecked(false);
    ui->toolLine->setChecked(true);
    ui->toolEraser->setChecked(false);
}

void MainWindow::on_toolEraser_clicked()
{
    canvasData->setTool(CanvasData::Tool::ERASER);
    ui->toolBrush->setChecked(false);
    ui->toolLine->setChecked(false);
    ui->toolEraser->setChecked(true);
}
