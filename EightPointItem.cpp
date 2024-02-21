#include "EightPointItem.h"

EightPointItem::EightPointItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    this->setAcceptHoverEvents(true);
}

QRectF EightPointItem::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}


QPainterPath EightPointItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void EightPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    // 设置背景颜色
    painter->setBrush(Qt::green);
    painter->drawRect(boundingRect());
    if (itemProperty.isClicked) {
        // 设置圆的半径
        const qreal radius = 5; // 圆的半径

        // 计算每个圆的中心位置
        const QPointF topCorner = QPointF(boundingRect().width()/2, boundingRect().y());
        const QPointF buttomCorner = QPointF(boundingRect().width()/2,boundingRect().height());
        const QPointF LeftCorner = QPointF(boundingRect().x(),boundingRect().height()/2);
        const QPointF RightCorner = QPointF(boundingRect().width(),boundingRect().height()/2);


        // 绘制四个圆
        painter->setBrush(Qt::red);
        painter->setPen(Qt::NoPen); // 设置无边框
        painter->drawEllipse(topCorner, radius, radius);
        painter->drawEllipse(buttomCorner, radius, radius);
        painter->drawEllipse(LeftCorner, radius, radius);
        painter->drawEllipse(RightCorner, radius, radius);
    }
}


QVariant EightPointItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        QPointF newPos = value.toPointF();
        if (newPos.x() < 0) newPos.setX(0);
        if (newPos.y() < 0) newPos.setY(0);
        if (newPos.x() > boundingRect().right()) newPos.setX(boundingRect().right());
        if (newPos.y() > boundingRect().bottom()) newPos.setY(boundingRect().bottom());
        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}

void EightPointItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        itemProperty.isClicked = true ;
        if (isOnBorder(event->pos())) {
            ItemProperty.m_startPos = event->pos();
            ItemProperty.m_originalRect = boundingRect();
        }
        update();
    }
}

void EightPointItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!ItemProperty.m_startPos.isNull()) {
        QPointF delta = event->pos() - ItemProperty.m_startPos;
        QRectF newRect = ItemProperty.m_originalRect.adjusted(0, 0, delta.x(), delta.y());
        setRect(newRect);
    }
}

void EightPointItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug()<<"hover enter";
    if (isOnBorder(event->pos())) {
        setCursor(Qt::SizeFDiagCursor); // 鼠标悬浮在边上时改变鼠标手势
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

bool EightPointItem::isOnBorder(const QPointF &pos)
{
    qreal x = pos.x();
    qreal y = pos.y();
    qreal w = boundingRect().width();
    qreal h = boundingRect().height();
    return (qAbs(x) < 5 || qAbs(x - w) < 5 || qAbs(y) < 5 || qAbs(y - h) < 5);
}

void EightPointItem::setRect(const QRectF &rect)
{
    prepareGeometryChange();
    setPos(rect.topLeft());
}



