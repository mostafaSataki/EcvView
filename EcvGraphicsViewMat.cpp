
#include "EcvGraphicsViewMat.h"
#include <qmath.h>
#include <thread>
#include <thread>
#include <iostream>
#include <QDebug>

#include <qimage.h>

using namespace std;


	//EcvGraphicsViewMat::EcvGraphicsViewMat(QWidget * parent) :
	//	QGraphicsView(parent),
	//	objects_counter_(1),
	//	current_zoom_(200),
	//	scene_(nullptr),
	//	filename_(""),
	//	fit_view_(true),
	//	back_item_(nullptr)
	//	
	//{
	//	

	//	createObjects();
	//	setScene(scene_);

	//	setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
	//	setMouseTracking(true);
	//

	//}
	//EcvGraphicsViewMat::~EcvGraphicsViewMat()
	//{

	//////	releaseObjects();
	//}

	//void EcvGraphicsViewMat::createObjects(){
	//	scene_ = new QGraphicsScene();
	//

	//}

	//void EcvGraphicsViewMat::releaseObjects(){
	//	if (scene_)
	//	   delete scene_;

	//}



	//void EcvGraphicsViewMat::setImage(const QString& file_name){
	//	filename_ = file_name;
	//	auto pix = QPixmap::fromImage(QImage(file_name));
	//	//pix.fill();
	//	setImage(pix);

	//	//cv::Mat img = cv::imread(file_name.toStdString(),1);
	//	//setImage(img);

	//}

	////void EcvGraphicsViewMat::setImage3(const QString& file_name){
	////	filename_ = file_name;
	////

	////	cv::Mat img = cv::imread(file_name.toStdString(),1);
	////	setImage(img);
	////}

	//void EcvGraphicsViewMat::setBlankImage(const QString& filename,const QColor& color){
	//	blank_image_filename_ = filename;
	//	setBackgroundBrush(QBrush(color, Qt::SolidPattern));
	//}

	//void EcvGraphicsViewMat::setBlank(){
	//	filename_ = "";
	//	if (!blank_image_filename_.isEmpty()) {
	//		auto pix = QPixmap::fromImage(QImage(blank_image_filename_));
	//		//pix.fill();
	//		setImage(pix);
	//	}
	//	else clear();

	//}


	////void EcvGraphicsViewMat::setImage(const cv::Mat &src) {
	//////	cout << "set" << endl;

	////	if (!src.empty()) {

	////		QPixmap pix;
	////		back_image_ = mat2Image(src);
	////		pix = QPixmap::fromImage(back_image_);
	////		setImage(pix);
	////		//cout << "set captured :" ;
	////		//showNow();
	////	}
	////	else setBlank();

	////}

	////void EcvGraphicsViewMat::setImage2(const cv::Mat & src){
	////	std::vector<uchar> buffer;
	////	cv::imencode(".jpeg", src, buffer);
	////	QPixmap m_pixmap;
	////	if (buffer.size() != 0) {
	////		if (m_pixmap.loadFromData(buffer.data(), buffer.size(), "JPEG")) {
	////			setImage(m_pixmap);
	////		}
	////	}
	////}

	//void EcvGraphicsViewMat::setImage(QPixmap& src) {

	//	
	//	if (back_item_) {
	//		scene_->removeItem(reinterpret_cast<QGraphicsItem*>(back_item_));
	//		delete back_item_;
	//	}
	//	
	//	back_item_ = scene_->addPixmap(src);
	//	back_item_->setZValue(0);
	//	scene_->setSceneRect(QRectF(QPointF(0, 0), src.size()));
	//	setFitView(fit_view_);
	//}

	//void EcvGraphicsViewMat::setImage(QImage& src)
	//{
	//	QPixmap map = QPixmap::fromImage(src);
	//	setImage(map);
	//}

	//void EcvGraphicsViewMat::setImage(const QByteArray& src) {

	//	QPixmap pix;
	//	back_image_ = byteArray2Image(src,"jpg");
	//	pix = QPixmap::fromImage(back_image_);
	//	setImage(pix);

	//}

	//QByteArray EcvGraphicsViewMat::getByteArray() const
	//{
	//	return image2ByteArray(back_image_,"jpg");
	//}

	//QPixmap EcvGraphicsViewMat::pixmap()
	//{
	//	QPixmap pix = QPixmap::fromImage(back_image_);
	//	return pix;
	//	
	//}

	////cv::Mat EcvGraphicsViewMat::backMat()
	////{
	////	return  image2Mat(back_image_);
	////}

	//void EcvGraphicsViewMat::clear()
	//{
	//	//if (back_image_) 
	//	{
	//		back_image_ = QImage();
	//		scene_->clear();
	//		
	//		back_item_ = nullptr;
	//	}
	//}
	//


	//

	//QImage EcvGraphicsViewMat::getQImage()
	//{
	//	//QImage image;
	//	//QPainter painter(&image);
	//	//painter.setRenderHint(QPainter::Antialiasing);
	//	//scene()->render(&painter);
	//	//return image;

	//	scene()->clearSelection();                                                  // Selections would also render to the file
	//	scene()->setSceneRect(scene()->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
	//	QImage image(scene()->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
	//	image.fill(Qt::transparent);                                              // Start all pixels transparent

	//	QPainter painter(&image);
	//	scene()->render(&painter);
	//	return image;
	//}

	//
	//bool EcvGraphicsViewMat::fitView() const
	//{
	//	return fit_view_;
	//}
	//void EcvGraphicsViewMat::setFitView(bool value)
	//{
	//	fit_view_ = value;
	//	if (fit_view_)
	//		fitInView(scene()->itemsBoundingRect(), Qt::KeepAspectRatio);

	//}
	//