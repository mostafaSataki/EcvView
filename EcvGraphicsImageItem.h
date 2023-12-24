#ifndef BHGRAPHICSIMAGEITEM_H
#define BHGRAPHICSIMAGEITEM_H

#include "viewlib_global.h"
#include <QGraphicsItem>

namespace ecv {

	class EcvImage;

	class VIEWLIB_EXPORT EcvGraphicsImageItem : public QGraphicsItem
	{
		
	public:
		explicit EcvGraphicsImageItem(QGraphicsItem *parent = 0);
		QRectF boundingRct() const;
		void setImage(const QImage& image);
		QImage& image();

	private:
		virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		QImage image_;
	};

	EcvGraphicsImageItem* Q2BHGraphicsItem(QGraphicsItem*);

}//ecv

#endif // BHGRAPHICSIMAGEITEM_H