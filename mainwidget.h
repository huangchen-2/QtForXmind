#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include "EightPointItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private:
    void mouseReleaseEvent(QMouseEvent* event) ;
    void mouseMoveEvent(QMouseEvent* event) ;
    void mousePressEvent(QMouseEvent* event) ;
private:
    Ui::MainWidget *ui;
    QPoint m_DragPosition  ;
    bool m_Drag = false ;
};
#endif // MAINWIDGET_H
