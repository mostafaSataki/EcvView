#pragma once
#include <qgraphicsview.h>

#include "viewlib_global.h"

class VIEWLIB_EXPORT EcvGraphicsView : public QGraphicsView
{
	Q_OBJECT
public :
	EcvGraphicsView(QWidget* parent = nullptr);
	~EcvGraphicsView();
	void setImage(int width, int height, int stride, char* data, const QSize& fit_size = QSize(-1, -1));
	//void setImage(const cv::Mat& image, const cv::Size& size = cv::Size());
protected:
	QGraphicsScene* scene_;

};

