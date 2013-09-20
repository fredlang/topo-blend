#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>
#include "BlendRenderItem.h"

BlendRenderItem::BlendRenderItem(QPixmap pixmap) : pixmap(pixmap)
{
	setAcceptHoverEvents(true);
	setZValue(10);
}

void BlendRenderItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)

	painter->drawPixmap(pixmap.rect(), pixmap);

	if( (isUnderMouse() && isOnTop()) || isSelected() )
	{
		painter->setBrush( Qt::NoBrush );
		painter->setPen( QPen(Qt::yellow, 2) );
		painter->drawRect( pixmap.rect() );
	}
}

bool BlendRenderItem::isOnTop()
{
	QRectF r = mapRectToScene(boundingRect().adjusted(10,10,-10,-10));
	QList<QGraphicsItem*> itemsAtRect = scene()->items(r, Qt::IntersectsItemBoundingRect, Qt::DescendingOrder);

	foreach(QGraphicsItem * i, itemsAtRect){
		if(i == this) return true;
		if(i->zValue() == zValue()) continue;
		break;
	}

	return false;
}

void BlendRenderItem::mousePressEvent( QGraphicsSceneMouseEvent * event )
{
	if(!isOnTop()) return;
	QGraphicsObject::mousePressEvent(event);
}

void BlendRenderItem::mouseMoveEvent( QGraphicsSceneMouseEvent * event )
{
	if(!isOnTop()) return;
	QGraphicsObject::mouseMoveEvent(event);
}