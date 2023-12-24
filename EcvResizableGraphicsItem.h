#ifndef ECV_RESIZABLE_GRAPHICS_ITEM
#define ECV_RESIZABLE_GRAPHICS_ITEM

#include "viewlib_global.h"

#include <QGraphicsItem>
#include "EcvObjectData.h"

#include <array>
#include <QPointF>
#include <QRectF>
#include <QFont>
#include <QCursor>
#include <qdebug.h>
#include <QObject>
#include <QAbstractGraphicsShapeItem>



namespace ecv {
	//QGraphicsRectItem

	const int HANDLE_SIZE = 3;

	using HandlePoints = std::array<QPointF, 8>;
	using HandleRects = std::array<QRectF, 8>;

	enum class RectDirect { left_top, top, right_top, right, bottom_right, bottom, bottom_left, left, move, hover };



	class VIEWLIB_EXPORT EcvResizableGraphicsItem : public QAbstractGraphicsShapeItem
	{
		
	public:

		explicit EcvResizableGraphicsItem(const EcvObjectData& data, int handel_size = HANDLE_SIZE,  QGraphicsItem *parent = 0);
		~EcvResizableGraphicsItem();

		QRectF boundingRect() const;
		void setBoundingRect(const QRectF& value) ;
		virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0)override;

		void setRect();

		bool titleVisiable()const;
		void setTitleVisiable(const bool &value);


		int titleBorderSize()const;
		void setTitleBorderSize(int value);

		void setHandleSize(int size);
		int handleSize()const;

		QFont font()const;
		void setFont(const QFont& value);

		QString title()const;
		void setTitle(const QString &value);

		QCursor cursor()const;

		bool isSelectable()const;
		void setIsSelectable(bool value);

		EcvObjectData& data();
	protected:
		EcvObjectData object_data_;
		bool is_selectable_;
		QRectF bnd_rect_;
		HandleRects handle_rects_;
		HandlePoints handle_points_;
		int handle_size_;
		RectDirect mouse_state_;
		bool pressed_;
		int title_border_size_;
		QFont font_;
		QSizeF title_size_;
		bool title_visiable_;
		QString title_;
		QRectF handels_br_;
		QRectF title_br_;
		QCursor cursor_;

		void setCursor(const QCursor& value);

		QRectF getSqure(const QPointF& center)const;
		void setHandlesRects();
		void setHandlesPoints(const QRectF& rct);
		void drawHandlesRect(QPainter *painter);
		QLineF getLine(const QPointF &p1, const QPointF &p2, int size);
		void setCurrentCursor();
		QPointF getRectCoordinate(const QRectF& rct, const RectDirect& rect_direct);


		void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
		void mousePressEvent(QGraphicsSceneMouseEvent * event);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
		void hoverMoveEvent(QGraphicsSceneHoverEvent * event);
		//void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
		//void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

		void moveEvent(const QPointF &pos);
		void setMouseState(const QPointF &point);
		void changeHandlePosition(const QPointF& pos);
		void setTitleSize();
		void setHandelsRect();
		void setTitleRect();

		void drawHandles(QPainter *painter);
		void drawTitle(QPainter *painter);
	private:
		QRectF getNormRect(const QPointF& pnt1, const QPointF& pnt2);
	//private slots:
	    void onRectChanged();
	};


}//ecv
#endif //ECV_RESIZABLE_GRAPHICS_ITEM
