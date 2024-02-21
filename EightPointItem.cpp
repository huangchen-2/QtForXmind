#include "EightPointItem.h"

EightPointItem::EightPointItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{

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
        update();
    }
}

void EightPointItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(! itemProperty.isClicked) return ;
    QPointF scenePos = event->scenePos();
    QPointF itemPos = mapToScene(0, 0);
    QRectF rect = boundingRect();
    // 计算鼠标位置与矩形每个边的距离
    qreal leftDistance = qAbs(scenePos.x() - itemPos.x());
    qreal rightDistance = qAbs(scenePos.x() - (itemPos.x() + rect.width()));
    qreal topDistance = qAbs(scenePos.y() - itemPos.y());
    qreal bottomDistance = qAbs(scenePos.y() - (itemPos.y() + rect.height()));
    qDebug()<<leftDistance<<rightDistance<<topDistance<<bottomDistance;
    // 找出距离最小的那个边
    qreal minDistance = qMin(qMin(qMin(leftDistance, rightDistance), topDistance), bottomDistance);
    // 如果这个边的距离小于或等于3个像素，改变鼠标手势；否则，保持原样
    if (minDistance <= 10) {
        setCursor(Qt::SizeAllCursor); // 缩放手势
    } else {
        setCursor(Qt::ArrowCursor);   // 默认手势
    }
}



