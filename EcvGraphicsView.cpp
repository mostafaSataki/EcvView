#include "EcvGraphicsView.h"


EcvGraphicsView::EcvGraphicsView(QWidget* parent ):
QGraphicsView(parent){
	scene_ = new QGraphicsScene();
	setScene(scene_);
}
EcvGraphicsView::~EcvGraphicsView() {
	delete scene_;
}

void EcvGraphicsView::setImage(int width, int height, int stride, char* data, const QSize& fit_size)
{




	scene_->clear();
	resetMatrix();



	auto Img = QImage((const uchar*)(data), width, height, stride, QImage::Format_RGB888);

	scene_->addPixmap(QPixmap::fromImage(Img));
	fitInView(scene_->itemsBoundingRect(), Qt::KeepAspectRatio);
}