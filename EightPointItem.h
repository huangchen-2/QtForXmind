#ifndef EIGHTPOINTITEM_H
#define EIGHTPOINTITEM_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QObject>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

class ItemProperty
{
public:
    bool isClicked = false ;
    int orignWidth = 100 ;
    int orignHeight = 100 ;
};

class EightPointItem : public QObject , public QGraphicsItem
{
    Q_OBJECT
public:
    EightPointItem(QGraphicsItem *parent = nullptr);
private:
    QRectF boundingRect() const override;
    QPainterPath shape() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) ;
public:
    ItemProperty itemProperty;
private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event)  ;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:

};



#endif // EIGHTPOINTITEM_H
