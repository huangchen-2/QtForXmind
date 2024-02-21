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
    QPointF m_startPos;
    QRectF m_originalRect;
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
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        ItemProperty.m_startPos = QPointF();
    }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override
    {
        setCursor(Qt::ArrowCursor); // 鼠标离开时恢复默认鼠标手势
    }
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;


private:
    bool isOnBorder(const QPointF &pos);

    void setRect(const QRectF &rect);



};



#endif // EIGHTPOINTITEM_H
