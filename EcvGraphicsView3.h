#ifndef ECV_GRAPHICS_VIEW3
#define ECV_GRAPHICS_VIEW3

#include "viewlib_global.h"
#include <qgraphicsview.h>
#include <QWheelEvent>
#include <QString>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>

#include "EcvViewRegionManager.h"
#include "EcvResizableGraphicsRect.h"
#include "EcvResizableGraphicsTitleRect.h"
#include "EcvResizableGraphicsPolygon.h"
#include "EcvResizableGraphicsTitlePolygon.h"





	enum class EcvPaintAct{select,add,edit,del};

	class VIEWLIB_EXPORT EcvGraphicsView3 : public QGraphicsView {
		Q_OBJECT
	public:
		EcvGraphicsView3(QWidget *parent = 0);
		~EcvGraphicsView3();

		int regionsCounter()const;
		void setRegionsCounter(int value);


		void setImage(const QString& file_name);
		//void setImage3(const QString& file_name);
		void setBlankImage(const QString& filename, const QColor& color = Qt::white);
		void setBlank();
		void setImage(int width, int height, int stride, char* data, const QSize& fit_size = QSize(-1, -1));
		//void setImage(const cv::Mat &src,const cv::Size& fit_size = cv::Size(-1,-1));
		//void setImage2(const cv::Mat &src);

		void setImage(QPixmap src);
		void setImage(QImage& src);
		void setImage(const QByteArray& src);
		QByteArray getByteArray()const;

		QPixmap pixmap();

		//cv::Mat backMat();
		void clear();
		
		EcvPaintAct paintAct()const;
		void setPaintAct(EcvPaintAct value);

		int currentRegionId()const;
		void setCurrentRegionId(int value);

		ecv::EcvViewRegionsManager* regionManager();
		
		ecv::EcvResizableGraphicsItem* add(const ecv::EcvObjectData& object);
		ecv::EcvResizableGraphicsItem* add(const ecv::EcvObjectData& object, const ecv::EcvShapeType& value);

		std::vector<ecv::EcvResizableGraphicsItem*> add(const ecv::EcvObjectDataList& objects);

		void getAllRemovableItems(ecv::EcvObjectDataList& objects);
		void getAllItems(ecv::EcvObjectDataList& objects);
		void getItems(const std::vector<int>& regions_id, ecv::EcvObjectDataList& objects);
		QImage getQImage();
		void getItemsExcept(const std::vector<int>& regions_id, ecv::EcvObjectDataList& objects);

		void deleteAllItems();
		void deleteItems(const std::vector<int>& regions_id);
		void setShapeType(const ecv::EcvShapeType& value);

		QAbstractGraphicsShapeItem* itemUnderMouse();

		const QString& filename()const;

		Q_PROPERTY(bool fit_view READ fitView WRITE setFitView);
	public slots:
		bool fitView()const;
		void setFitView(bool value);
	protected:
		virtual void resizeEvent(QResizeEvent *event)override;
		virtual void wheelEvent(QWheelEvent *e) override;
		
		virtual void mousePressEvent(QMouseEvent *event) override;
		virtual void mouseMoveEvent(QMouseEvent *event)override;
		virtual void mouseReleaseEvent(QMouseEvent *event)override;
		virtual void keyPressEvent(QKeyEvent *event)override;
		virtual void mouseDoubleClickEvent(QMouseEvent *event) override;


		
	private:
		QString blank_image_filename_;
		QString filename_;
		bool double_clicked_;
		QPolygonF cur_polygon_;
		ecv::EcvViewRegion cur_view_region_;
		int objects_counter_;
		bool fit_view_;
		int current_zoom_;
		QGraphicsPixmapItem* back_item_;
		QGraphicsScene* scene_;
		QImage back_image_;
		ecv::EcvViewRegionsManager* regions_manager_;

		EcvPaintAct paint_act_;
		
		ecv::EcvShapeType shape_type_;
		int current_region_id_;
		QPointF pre_point_;
		bool pressed_;
		QAbstractGraphicsShapeItem* item_under_mouse_;
		QAbstractGraphicsShapeItem* cur_item_;
		QPointF first_point_;

		void setupMatrix();
		void createObjects();
		void releaseObjects();
		
		

		
		void mousePressEventAdd(const QPoint& value);
		
		ecv::EcvResizableGraphicsRect* curItem2Rect();
		ecv::EcvResizableGraphicsTitleRect* curItem2TitleRect();
		ecv::EcvResizableGraphicsPolygon* curItem2Polygon();
		ecv::EcvResizableGraphicsTitlePolygon* curItem2TitlePolygon();
		ecv::EcvResizableGraphicsItem* curItem2ResizableGraphicsItem();

		void item2Cur(const QPointF& value);
		void rect2Cur(const QPointF& value);
		void titleRect2Cur(const QPointF& value);
		void polygon2Cur(const QPointF& value);
		void titlePolygon2Cur(const QPointF& value);
		void setItemUnderMouse(const QPointF& value);

		

		void removeItem(QAbstractGraphicsShapeItem* value);
		void setCurrentCursor();
		void editResizableGraphicsItem(ecv::EcvResizableGraphicsItem* value,const QPointF& dst_pnt);

	signals:
		void onPaintActChanged();
		void onDeleteObject(int object_counter);
	};

#endif //ECV_GRAPHICS_VIEW3
