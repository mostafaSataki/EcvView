#ifndef ECV_GRAPHICS_VIEW_Mat_H
#define ECV_GRAPHICS_VIEW_Mat_H

#include "viewlib_global.h"
#include <qgraphicsview.h>
#include <QString>
#include <QGraphicsScene>

#include <qgraphicsitem.h>


//
//	class VIEWLIB_EXPORT EcvGraphicsViewMat : public QGraphicsView {
//		Q_OBJECT
//	public:
//		EcvGraphicsViewMat(QWidget *parent = 0);
//		~EcvGraphicsViewMat();
//
//	
//		void setImage(const QString& file_name);
//		void setImage3(const QString& file_name);
//		void setBlankImage(const QString& filename, const QColor& color = Qt::white);
//		void setBlank();
//		//void setImage(const cv::Mat &src);
//		//void setImage2(const cv::Mat &src);
//
//		void setImage(QPixmap& src);
//		void setImage(QImage& src);
//		void setImage(const QByteArray& src);
//		QByteArray getByteArray()const;
//
//		QPixmap pixmap();
//
//		//cv::Mat backMat();
//		void clear();
//		
//	
//		const QString& filename()const;
//		QImage getQImage();
//
//		Q_PROPERTY(bool fit_view READ fitView WRITE setFitView);
//	public slots:
//		bool fitView()const;
//		void setFitView(bool value);
//
//
//		
//	private:
//		QString blank_image_filename_;
//		QString filename_;
//		
//		int objects_counter_;
//		bool fit_view_;
//		int current_zoom_;
//		QGraphicsPixmapItem* back_item_;
//		
//		
//		QGraphicsScene* scene_;
//		QImage back_image_;
//		
//
//	
//		void createObjects();
//		void releaseObjects();
//
//		
//
//		
//
//
//	};
//
#endif //ECV_GRAPHICS_VIEW_Mat_H
