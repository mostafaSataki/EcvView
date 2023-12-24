

#include "EcvGraphicsImageItem.h"



#include <qpainter.h>
#include <qdebug.h>


namespace ecv{

	EcvGraphicsImageItem::EcvGraphicsImageItem(QGraphicsItem *parent) :
		QGraphicsItem(parent)
	{
		//setFlag(QGraphicsItem::ItemIsMovable);
	}

	QRectF EcvGraphicsImageItem::boundingRct() const
	{
		
		return QRectF(0, 0, image_.width() + 1, image_.height() + 1);
	}

	QRectF operator+(QRectF a, const  QRectF& b)
	{
		a.setX(a.x() + b.x());
		a.setY(a.y() + b.y());
		a.setWidth(a.width() + b.width());
		a.setHeight(a.height() + b.height());
		return a;
	}
	void EcvGraphicsImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *op, QWidget *w)
	{
		painter->drawImage(0, 0, image_);

		painter->setPen(QPen(QColor(Qt::red), 3));
	}


	void EcvGraphicsImageItem::setImage(const QImage& image)
	{
		image_ = image;
	}


	QImage& EcvGraphicsImageItem::image()
	{
		return image_;
	}

	EcvGraphicsImageItem* Q2BHGraphicsItem(QGraphicsItem *graphic_item){
		return dynamic_cast<EcvGraphicsImageItem*>(graphic_item);
	}

}//ecv