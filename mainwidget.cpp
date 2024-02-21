#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPixmap>
#include <QUrl>
#include <QGraphicsScene>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    EightPointItem * item = new EightPointItem;
    ui->graphicsView->scene()->addItem(item);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_Drag = true;
        m_DragPosition = event->globalPos() - this->pos();
        event->accept();
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_Drag && (event->buttons() && Qt::LeftButton)) {
        move(event->globalPos() - m_DragPosition);
        event->accept();
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_Drag = false;
}
