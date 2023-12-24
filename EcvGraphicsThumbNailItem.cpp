
#include "EcvGraphicsThumbNailItem.h"

#include <qpainter.h>
#include <qdebug.h>

namespace ecv {

	EcvGraphicsThumbnailItem::EcvGraphicsThumbnailItem(const QImage& image,
		const QSize& thumbnail_size /*= QSize(100, 100)*/, QGraphicsItem *parent /*= 0*/) :
		//real_image_(std::move(thumbnail.toQImage())),
		image_(std::move(image)),
		thumbnail_(image.scaled(thumbnail_size.width(), thumbnail_size.height(), Qt::KeepAspectRatio)),
		thumbnail_size_(thumbnail_size),
		clicked_(false),
		QGraphicsItem(parent)
	{
		//thumbnail_.setName(image.name());
		//thumbnail_.setDetail(image.detail());
	}

	QRectF EcvGraphicsThumbnailItem::boundingRect() const
	{
		return QRectF(0, 0, thumbnail_size_.width(), thumbnail_size_.height());
	}

	void EcvGraphicsThumbnailItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
	{
		if (thumbnail_.size() != QSize(0, 0)) {

			int height_dif = thumbnail_size_.height() - thumbnail_.size().height();
			int width_dif = thumbnail_size_.width() - thumbnail_.size().width();

			painter->drawImage(QRectF(width_dif / 2, height_dif / 2, thumbnail_.size().width(), thumbnail_.size().height()), thumbnail_);
			//		imshow("VV", thumbnail_.toMat());
				//	waitKey(1);
		}

		if (clicked_)
			painter->fillRect(QRectF(0, 0, thumbnail_size_.width(), thumbnail_size_.height()), QBrush(QColor(128, 128, 255, 128)));

		painter->drawRect(QRectF(0, 0, thumbnail_size_.width(), thumbnail_size_.height()));

	}

	QImage EcvGraphicsThumbnailItem::thumbnail() const
	{
		return thumbnail_;
	}

	void EcvGraphicsThumbnailItem::clicked(bool clicked)
	{
		clicked_ = clicked;
		update();
	}
	bool EcvGraphicsThumbnailItem::isClicked() const
	{
		return clicked_;
	}

	QString EcvGraphicsThumbnailItem::detail()const
	{
		return "";// thumbnail_.detail();
	}

	QString EcvGraphicsThumbnailItem::directory()const
	{
		//return thumbnail_.directory();
		return "";
	}

	QSize EcvGraphicsThumbnailItem::size() const
	{
		return thumbnail_size_;
	}

	QImage& EcvGraphicsThumbnailItem::image()
	{
		return image_;
	}

	//QImage EcvGraphicsThumbnailItem::realImage()
	//{
	//	return image_.toQImage();
	//}

	EcvGraphicsThumbnailItem* graphics2ThumbItem(QGraphicsItem* graphics_item) {
		return dynamic_cast<EcvGraphicsThumbnailItem*>(graphics_item);
	}

}//ecv