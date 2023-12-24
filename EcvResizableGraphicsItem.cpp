

#include "EcvResizableGraphicsItem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

namespace ecv {
	

	EcvResizableGraphicsItem::EcvResizableGraphicsItem(const EcvObjectData& data, int handel_size, QGraphicsItem *parent /*= 0*/) :
		object_data_(data),
		handle_size_(HANDLE_SIZE),
		title_border_size_(1),
		font_(QFont("tahoma",8)),
		title_visiable_(false),
		title_(""),
		is_selectable_(true)

	{
		setZValue(1000);
		setAcceptHoverEvents(true);
		setFlags(QGraphicsItem::ItemIsSelectable);

//--		QObject::connect(&object_data_, &EcvObjectData::rectChanged, this, &onRectChanged);
		setRect();
		
		
	}

	

	EcvResizableGraphicsItem::~EcvResizableGraphicsItem()
	{
		qDebug() << "end" << endl;
	}


	QRectF EcvResizableGraphicsItem::boundingRect() const
	{
		return bnd_rect_;
	}

	void EcvResizableGraphicsItem::setBoundingRect(const QRectF& value) 
	{
		bnd_rect_ = value;
		
	}

	void EcvResizableGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/)
	{
		//QGraphicsItem::paint(painter, option, widget);
		setRect();
		drawTitle(painter);
		drawHandles(painter);


		painter->setPen(this->pen());

		//setHandlesPoints(bounding_rect_);
		//setHandlesRects();

		//drawHandlesRect(painter);
	}

	void EcvResizableGraphicsItem::setRect()
	{
		
		setHandelsRect();
		setTitleRect();



		bnd_rect_ = handels_br_;
		if (title_br_.width() > bnd_rect_.width())
			bnd_rect_.setWidth(title_br_.width());

		//if (handels_br_.width() > bounding_rect_.width())
		//	bounding_rect_.setWidth(handels_br_.width());

		if (title_br_.height() > bnd_rect_.height())
			bnd_rect_.setHeight(title_br_.height());

		//if (handels_br_.height() > bounding_rect_.height())
		//	bounding_rect_.setHeight(handels_br_.height());


		update();
		//	QApplication::processEvents();
		//qDebug() << bounding_rect_ << endl;


	}

	bool EcvResizableGraphicsItem::titleVisiable() const
	{
		return title_visiable_;
	}

	void EcvResizableGraphicsItem::setTitleVisiable(const bool &value)
	{
		title_visiable_ = value;
	}

	int EcvResizableGraphicsItem::titleBorderSize() const
	{
		return title_border_size_;
	}

	void EcvResizableGraphicsItem::setTitleBorderSize(int value)
	{
		title_border_size_ = value;
	}

	void EcvResizableGraphicsItem::setHandleSize(int size)
	{
		handle_size_ = size;
	}

	int EcvResizableGraphicsItem::handleSize() const
	{
		return handle_size_;
	}

	QFont EcvResizableGraphicsItem::font() const
	{
		return font_;
	}

	void EcvResizableGraphicsItem::setFont(const QFont& value)
	{
		if (font_ != value) {
			font_ = value;
			//	setTitleSize();
		}
	}

	QString EcvResizableGraphicsItem::title() const
	{
		return title_;
	}

	void EcvResizableGraphicsItem::setTitle(const QString &value)
	{
		if (title_ != value) {
			title_ = value;
			setTitleSize();
		}

	}

	QCursor EcvResizableGraphicsItem::cursor() const
	{
		return cursor_;
	}

	bool EcvResizableGraphicsItem::isSelectable() const
	{
		return is_selectable_;
	}

	void EcvResizableGraphicsItem::setIsSelectable(bool value)
	{
		is_selectable_ = value;
	}

	EcvObjectData & EcvResizableGraphicsItem::data()
	{
		return object_data_;
	}

	void EcvResizableGraphicsItem::setCursor(const QCursor& value)
	{
		cursor_ = value;
	}

	::QRectF EcvResizableGraphicsItem::getSqure(const QPointF& center) const
	{
		return QRectF(center.x() - handle_size_, center.y() - handle_size_, handle_size_ * 2, handle_size_ * 2);

	}

	void EcvResizableGraphicsItem::setHandlesRects()
	{
		for (size_t i = 0; i < 8; i++)
			handle_rects_[i] = getSqure(handle_points_[i]);

	}

	void EcvResizableGraphicsItem::setHandlesPoints(const QRectF& rct)
	{
		handle_points_[0] = rct.topLeft();// +QPointF(-handle_size_, -handle_size_);
		handle_points_[1] = getRectCoordinate(rct, RectDirect::top);// +QPointF(0, handle_size_);
		handle_points_[2] = rct.topRight();// +QPointF(-handle_size_, handle_size_);
		handle_points_[3] = getRectCoordinate(rct, RectDirect::right);// +QPointF(-handle_size_, 0);
		handle_points_[4] = rct.bottomRight();// +QPointF(-handle_size_, -handle_size_);
		handle_points_[5] = getRectCoordinate(rct, RectDirect::bottom);// +QPointF(0, -handle_size_);
		handle_points_[6] = rct.bottomLeft();// +QPointF(handle_size_, -handle_size_);
		handle_points_[7] = getRectCoordinate(rct, RectDirect::left);// +QPointF(handle_size_, 0);


	}

	void EcvResizableGraphicsItem::drawHandlesRect(QPainter *painter)
	{
		for (size_t i = 0; i < 8; i++) {
			painter->drawRect(getSqure(handle_points_[i]));
			int next_i = (i + 1) % 8;

			//auto line = getLine(handle_points_[i], handle_points_[next_i], handle_size_);
			//painter->drawLine(line);
		}

	}

	QLineF EcvResizableGraphicsItem::getLine(const QPointF &p1, const QPointF &p2, int size)
	{
		size++;
		QLineF result;
		QPointF offset(0, 0);

		if (p1.x() < p2.x())
			offset.setX(size);
		else if (p1.y() < p2.y())
			offset.setY(size);
		else if (p1.x() > p2.x())
			offset.setX(-size);
		else if (p1.y() > p2.y())
			offset.setY(-size);

		result.setP1(p1 + offset);
		result.setP2(p2 - offset);
		return result;
	}

	void EcvResizableGraphicsItem::setCurrentCursor()
	{

		switch (mouse_state_)
		{
		case RectDirect::left_top:
		case RectDirect::bottom_right:
			setCursor(Qt::SizeFDiagCursor);
			break;
		case RectDirect::right_top:
		case RectDirect::bottom_left:
			setCursor(Qt::SizeBDiagCursor);
			break;
		case RectDirect::top:
		case RectDirect::bottom:
			setCursor(Qt::SizeVerCursor);
			break;
		case RectDirect::left:
		case RectDirect::right:
			setCursor(Qt::SizeHorCursor);
			break;
		case RectDirect::move:
			setCursor(Qt::SizeAllCursor);
			break;
		case RectDirect::hover:
			setCursor(Qt::ArrowCursor);
			break;

		}
	}

	QPointF EcvResizableGraphicsItem::getRectCoordinate(const QRectF& rct, const RectDirect& rect_direct)
	{
		QPointF result;
		switch (rect_direct)
		{
		case RectDirect::left:
			result = rct.topLeft() + QPointF(0, rct.height() / 2);
			break;
		case RectDirect::top:
			result = rct.topLeft() + QPointF(rct.width() / 2, 0);
			break;
		case RectDirect::right:
			result = rct.topRight() + QPointF(0, rct.height() / 2);
			break;
		case RectDirect::bottom:
			result = rct.bottomLeft() + QPointF(rct.width() / 2, 0);
			break;

		}
		return result;

	}

	void EcvResizableGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
	{
		//qDebug() << "mouseMoveEvent" << endl;
		moveEvent(event->pos());
		QGraphicsItem::mouseMoveEvent(event);
	}

	void EcvResizableGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
	{
		//qDebug() << "mouseMoveEvent" << endl;
		event->accept();
		pressed_ = true;
		update();
		//qDebug() << "press:" << pressed_ << endl;
		prepareGeometryChange();
		QGraphicsItem::mousePressEvent(event);

	}

	void EcvResizableGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
	{
		//qDebug() << "mouseReleaseEvent" << endl;
		pressed_ = false;

		QGraphicsItem::mouseReleaseEvent(event);
	}

	void EcvResizableGraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent * event)
	{
		static int count = 1;

		//qDebug() << "hoverMoveEvent:" << count++ << endl;
		moveEvent(event->pos());
		QGraphicsItem::hoverMoveEvent(event);
	}

	//void EcvResizableGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
	//{
	//	parent_cursor_ = cursor();
	//}
	//
	//void EcvResizableGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
	//{
	//	setCursor(Qt::ArrowCursor);
	//}

	void EcvResizableGraphicsItem::moveEvent(const QPointF &pos)
	{

		if (!(mouse_state_ < RectDirect::move && pressed_)) {
			setMouseState(pos);
			setCurrentCursor();
		}
		if (mouse_state_ == RectDirect::move) {
			setFlag(QGraphicsItem::ItemIsMovable, true);
		}
		else {
			setFlag(QGraphicsItem::ItemIsMovable, false);
			if (pressed_) {
				changeHandlePosition(pos);
			}
		}
		prepareGeometryChange();

	}

	void EcvResizableGraphicsItem::setMouseState(const QPointF &point)
	{
		mouse_state_ = RectDirect::hover;
		for (size_t i = 0; i < 8; i++)
			if (handle_rects_[i].contains(point))
				mouse_state_ = static_cast<RectDirect>(i);

		if (mouse_state_ == RectDirect::hover) {
			if (pressed_)
				mouse_state_ = RectDirect::move;
		}

	}

	void EcvResizableGraphicsItem::changeHandlePosition(const QPointF& pos)
	{
		switch (mouse_state_)
		{
		case RectDirect::left_top:
			data().rect().setTopLeft(pos);
			break;
		case RectDirect::top:
			data().rect().setTop(pos.y());
			break;
		case RectDirect::right_top:
			data().rect().setTopRight(pos);
			break;
		case RectDirect::right:
			data().rect().setRight(pos.x());
			break;
		case RectDirect::bottom_right:
			data().rect().setBottomRight(pos);
			break;
		case RectDirect::bottom:
			data().rect().setBottom(pos.y());
			break;
		case RectDirect::bottom_left:
			data().rect().setBottomLeft(pos);
			break;
		case RectDirect::left:
			data().rect().setLeft(pos.x());
			break;
		}
		setRect();

	}

	void EcvResizableGraphicsItem::setTitleSize()
	{
		QFontMetrics metrics(font_);
		title_size_.setWidth(metrics.width(title_) + 2 * title_border_size_ + 10);
		title_size_.setHeight(metrics.height() + 2 * title_border_size_);

	}

	void EcvResizableGraphicsItem::setHandelsRect()
	{

		handels_br_.setRect(data().rect().x() - handle_size_,data().rect().y() - handle_size_,data().rect().width() + handle_size_ * 2, 
			data().rect().height() + handle_size_ * 2);
	}

	void EcvResizableGraphicsItem::setTitleRect()
	{
		title_br_ = data().rect();
		if (title_visiable_) {
			title_br_.setWidth(title_size_.width());
			title_br_.setHeight(std::max(title_size_.height(), (qreal)handle_size_) + data().rect().height() + handle_size_);
		}

	}

	void EcvResizableGraphicsItem::drawHandles(QPainter *painter)
	{
		if (is_selectable_ && isSelected()) {
			//	painter->setCompositionMode(QPainter::RasterOp_SourceXorDestination);

			QPen temp_pen(pen());
			temp_pen.setWidth(1);
			painter->setPen(temp_pen);

			setHandlesPoints(data().rect());
			setHandlesRects();
			drawHandlesRect(painter);
		}

	}

	void EcvResizableGraphicsItem::drawTitle(QPainter *painter)
	{
		if (title_visiable_) {

			auto cur_brush = painter->brush();
			auto br = bnd_rect_;


			QBrush title_brush_(pen().color().dark(200));
			painter->setBrush(title_brush_);
			painter->setPen(pen());

			QRectF title_rect(br.x() + handle_size_, br.y() + br.height() - title_size_.height(), title_size_.width() - pen().width() * 2, title_size_.height() - pen().width() * 2);
			painter->drawRoundedRect(title_rect,1, 1);
			painter->drawText(QPointF(br.x() + handle_size_ * 2 + title_border_size_, br.y() + br.height() - (title_size_.height() / 4)), title_);
			painter->setBrush(cur_brush);

		}


	}

	QRectF EcvResizableGraphicsItem::getNormRect(const QPointF& pnt1, const QPointF& pnt2)
	{
		int x1 = pnt1.x();
		int y1 = pnt1.y();
		int x2 = pnt2.x();
		int y2 = pnt2.y();

		if (x2 < x1)
			std::swap(x1, x2);
		if (y2 < y1)
			std::swap(y1, y2);

		return QRectF(QPointF(x1, y1), QPointF(x2, y2));

	}

	void EcvResizableGraphicsItem::onRectChanged()
	{
		setRect();
	}


}//ecv