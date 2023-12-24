#ifndef _ECV_GRAPHICS_THUMBNAIL_ITEM
#define _ECV_GRAPHICS_THUMBNAIL_ITEM

#include "viewlib_global.h"

#include <QGraphicsItem>

namespace ecv {

	class VIEWLIB_EXPORT EcvGraphicsThumbnailItem : public QGraphicsItem
	{
	public:
		explicit EcvGraphicsThumbnailItem(const QImage& image,
			const QSize& thumbnail_size = QSize(100, 100), QGraphicsItem *parent = 0);

		QImage thumbnail() const;

		void clicked(bool clicked = true);
		bool isClicked() const;
		QString detail()const;
		QString directory()const;
		QSize size()const;
		QImage& image();
		//QImage realImage();
	protected:
		QRectF boundingRect() const;
		private slots:
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	private:
		QImage thumbnail_;
		//QImage real_image_;
		QImage image_;
		QSize thumbnail_size_;
		bool clicked_;
	};

	EcvGraphicsThumbnailItem* graphics2ThumbItem(QGraphicsItem*);

}//ecv

#endif // _ECV_GRAPHICS_THUMBNAIL_ITEM
