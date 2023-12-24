
#include "EcvGraphicsView3.h"
#include <qmath.h>
#include <thread>
#include <thread>
#include "EcvResizableGraphicsPolygon.h"
#include "EcvResizableGraphicsTitlePolygon.h"
#include <iostream>
#include <QDebug>
#include <qbuffer.h>

using namespace std;
using namespace ecv;

	EcvGraphicsView3::EcvGraphicsView3(QWidget * parent) :
		QGraphicsView(parent),
		objects_counter_(1),
		current_zoom_(200),
		back_item_(nullptr),
		current_region_id_(-1),
		shape_type_(EcvShapeType::none),
		item_under_mouse_(nullptr),
		pressed_(false),
		double_clicked_(false),
		scene_(nullptr),
		regions_manager_(nullptr),
		cur_item_(nullptr),
		paint_act_(EcvPaintAct::select),
		first_point_(0.f,0.f),
		pre_point_(0.f, 0.f),
		filename_(""),
		fit_view_(true)
		
	{
		createObjects();
		setScene(scene_);

		setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
		setMouseTracking(true);
		setPaintAct(EcvPaintAct::select);

	}
	EcvGraphicsView3::~EcvGraphicsView3()
	{
		releaseObjects();
	}
	int EcvGraphicsView3::regionsCounter() const
	{
		return objects_counter_;
	}
	void EcvGraphicsView3::setRegionsCounter(int value)
	{
		objects_counter_ = value;
	}
	bool EcvGraphicsView3::fitView() const
	{
		return fit_view_;
	}
	void EcvGraphicsView3::setFitView(bool value)
	{
		fit_view_ = value;
		if (fit_view_)
			fitInView(scene()->itemsBoundingRect(), Qt::KeepAspectRatio);

	}
	void EcvGraphicsView3::resizeEvent(QResizeEvent * event)
	{
		setFitView(fit_view_);
	}
	void EcvGraphicsView3::wheelEvent(QWheelEvent * e)
	{
		if (e->modifiers() & Qt::ControlModifier && !fit_view_) {
			if (e->delta() > 0)
				current_zoom_ += 6;
			else
				current_zoom_ -= 6;

			setupMatrix();
			e->accept();
		}
		else {
			QGraphicsView::wheelEvent(e);
		}
	}
	void EcvGraphicsView3::mousePressEvent(QMouseEvent * event)
	{

		switch (paint_act_)
		{
		case EcvPaintAct::add:
			mousePressEventAdd(event->pos());
			break;
		}

		QGraphicsView::mousePressEvent(event);
	}
	void EcvGraphicsView3::mouseMoveEvent(QMouseEvent * event)
	{
		QPointF cur_pos = mapToScene(event->pos());

		
		setItemUnderMouse(cur_pos);
		setCurrentCursor();

		if (pressed_) {
			switch (shape_type_)
			{
			case ecv::EcvShapeType::rect:
			case ecv::EcvShapeType::title_rect:
			case ecv::EcvShapeType::ellipse:
			{

				auto cur_item = curItem2ResizableGraphicsItem();
				editResizableGraphicsItem(cur_item, cur_pos);
			}
			break;
			case ecv::EcvShapeType::polygon:
			{
				auto cur_polygon_item = curItem2Polygon();
				if (pressed_ && cur_polygon_item) {
					auto cur_polygon = cur_polygon_;
					cur_polygon.append(cur_pos);
					cur_polygon_item->data().setPolygon(cur_polygon);
				}
			}


			break;
			case ecv::EcvShapeType::blob:
				break;
			default:
				break;
			}
		}
		else QGraphicsView::mouseMoveEvent(event);

	}
	void EcvGraphicsView3::mouseReleaseEvent(QMouseEvent * event)
	{
		if (double_clicked_) {
			double_clicked_ = false;
			return;
		}
		switch (paint_act_)
		{
		//case ecv::EcvPaintAct::select:
		case EcvPaintAct::add:
	//	case ecv::EcvPaintAct::edit:
		{
			switch (shape_type_)
			{
			case ecv::EcvShapeType::rect:
			case ecv::EcvShapeType::title_rect:
			case ecv::EcvShapeType::ellipse:
			{
				auto cur_item = curItem2ResizableGraphicsItem();

				if (pressed_ && cur_item) {
					if (cur_item->data().diameter() < 10)
						removeItem(cur_item);
					else {
						if (cur_item) {
							auto item_region = regions_manager_->find(cur_item->data().regionID());
							cur_item->setIsSelectable(item_region.selectable());
							cur_item->setZValue(1000);
						}

						auto cur_grect = curItem2TitleRect();
						if (cur_grect)
							cur_grect->setTitle(QString::number(objects_counter_));

						objects_counter_++;
					}

					pressed_ = false;
				}

			}

			break;

			case ecv::EcvShapeType::polygon: 
			case ecv::EcvShapeType::title_polygon:
			{
				auto cur_pos = mapToScene(event->pos());
				if (!pressed_) {
					cur_polygon_ = QPolygonF();
					cur_polygon_.append(cur_pos);
					item2Cur(cur_pos);
					pressed_ = true;
				}
				else {
					cur_polygon_.append(cur_pos);
					curItem2Polygon()->data().setPolygon(cur_polygon_);
				}
			}

			break;
			case ecv::EcvShapeType::blob:


				break;
			}
		}
		break;
		case EcvPaintAct::del:
			if (item_under_mouse_)
				removeItem(item_under_mouse_);
			break;
		}
		emit onPaintActChanged();
		QGraphicsView::mouseReleaseEvent(event);
	}
	void EcvGraphicsView3::keyPressEvent(QKeyEvent * event)
	{
		if (event->key() == Qt::Key_Escape) {
			pressed_ = false;
			if (cur_item_)
				scene_->removeItem(cur_item_);
		}
		QGraphicsView::keyPressEvent(event);

	}
	void EcvGraphicsView3::mouseDoubleClickEvent(QMouseEvent * event)
	{
		if (cur_item_ && pressed_ && paint_act_ == EcvPaintAct::add && shape_type_ == EcvShapeType::polygon)
		{
			pressed_ = false;
			cur_item_ = nullptr;
			double_clicked_ = true;

		}


	}
	const QString& EcvGraphicsView3::filename() const
	{
		return filename_;
	}


	void EcvGraphicsView3::setupMatrix()
	{
		qreal scale = qPow(qreal(2), (current_zoom_ - 250) / qreal(50));

		QMatrix matrix;
		matrix.scale(scale, scale);
		matrix.rotate(0);


		setMatrix(matrix);

	}

	void EcvGraphicsView3::createObjects()
	{
		scene_ = new QGraphicsScene();
		regions_manager_ = new EcvViewRegionsManager();

	}

	void EcvGraphicsView3::releaseObjects()
	{
		if (scene_)
		delete scene_;
		if (regions_manager_)
		delete regions_manager_;
	}

	void EcvGraphicsView3::setShapeType(const EcvShapeType & value)
	{
		if (shape_type_ != value) {
			shape_type_ = value;
			//setPaintAct(EcvPaintAct::select);
		
		}
	}

	QAbstractGraphicsShapeItem* EcvGraphicsView3::itemUnderMouse()
	{
		return item_under_mouse_;
	}

	
	void EcvGraphicsView3::mousePressEventAdd(const QPoint & value)
	{
		switch (shape_type_)
		{
		case ecv::EcvShapeType::rect:
		case ecv::EcvShapeType::title_rect:
		case ecv::EcvShapeType::ellipse:
			if (!pressed_) {
				qDebug() << first_point_ << endl;
				auto cur_p = mapToScene(value);
				item2Cur(cur_p);
				first_point_ = cur_p;
				pressed_ = true;
			}
			break;

		}

	}


	EcvResizableGraphicsRect * EcvGraphicsView3::curItem2Rect()
	{
		return dynamic_cast<EcvResizableGraphicsRect*>(cur_item_);
	}

	EcvResizableGraphicsTitleRect* EcvGraphicsView3::curItem2TitleRect()
	{
		return dynamic_cast<EcvResizableGraphicsTitleRect*>(cur_item_);
	}

	EcvResizableGraphicsPolygon * EcvGraphicsView3::curItem2Polygon()
	{
		return dynamic_cast<EcvResizableGraphicsPolygon*>(cur_item_);
	}

	EcvResizableGraphicsTitlePolygon * EcvGraphicsView3::curItem2TitlePolygon()
	{
		return dynamic_cast<EcvResizableGraphicsTitlePolygon*>(cur_item_);
	}

	EcvResizableGraphicsItem * EcvGraphicsView3::curItem2ResizableGraphicsItem()
	{
		auto res = dynamic_cast<EcvResizableGraphicsItem*>(cur_item_);
		if (res)
			return res;
		return nullptr;
	}

	void EcvGraphicsView3::item2Cur(const QPointF & value)
	{
		//auto region = regions_manager_->find(current_region_id_);
		switch (shape_type_)
		{
		case EcvShapeType::rect:
			rect2Cur(value);
			break;
		case EcvShapeType::title_rect:
			titleRect2Cur(value);
			break;
		case EcvShapeType::polygon:
			polygon2Cur(value);
			break;
		case EcvShapeType::title_polygon:
			titlePolygon2Cur(value);
			break;
		case EcvShapeType::ellipse:
			break;
		case EcvShapeType::blob:
			break;

		default:
			break;
		}
		
		cur_item_->setFlag(QGraphicsItem::ItemIsSelectable, cur_view_region_.selectable()); 
		cur_item_->setFlag(QGraphicsItem::ItemIsMovable, cur_view_region_.removable());
		if (!cur_view_region_.removable())
			cur_item_->setZValue(10);
		else cur_item_->setZValue(1000);
		auto cur_item = dynamic_cast<EcvResizableGraphicsItem*>(cur_item_);
		cur_item->data().setObjectCounter(objects_counter_);
		scene_->addItem(cur_item_);
		cur_item_->setPen(cur_view_region_.pen());

	}

	void EcvGraphicsView3::rect2Cur(const QPointF & value)
	{
		auto cur_rect = new EcvResizableGraphicsRect(EcvObjectData(QRectF(value, value),objects_counter_, current_region_id_), HANDLE_SIZE );
		cur_item_ = cur_rect;
		cur_rect->setIsSelectable(false);

	}

	void EcvGraphicsView3::titleRect2Cur(const QPointF & value)
	{
		auto region = regions_manager_->find(current_region_id_);
		auto cur_rect = new EcvResizableGraphicsTitleRect(EcvObjectData(QRectF(value, value),objects_counter_,current_region_id_),
			QString::number(objects_counter_));
		cur_item_ = cur_rect;
		cur_rect->setIsSelectable(false);
	}

	void EcvGraphicsView3::polygon2Cur(const QPointF & value)
	{
		QPolygonF polygon;
		polygon.append(value);
		auto cur_polygon  = new EcvResizableGraphicsPolygon(EcvObjectData(QRectF(value,value),objects_counter_,current_region_id_,polygon));
		cur_item_ = cur_polygon;
		cur_polygon->setIsSelectable(false);
	}

	void EcvGraphicsView3::titlePolygon2Cur(const QPointF & value)
	{
		QPolygonF polygon;
		polygon.append(value);

		auto region = regions_manager_->find(current_region_id_);
		auto cur_polygon = new EcvResizableGraphicsTitlePolygon(EcvObjectData(QRectF(value,value),objects_counter_,current_region_id_,polygon), 
			QString::number(objects_counter_), HANDLE_SIZE);
		cur_item_ = cur_polygon;
		cur_item_ = cur_polygon;
		cur_polygon->setIsSelectable(false);

	}

	void EcvGraphicsView3::setItemUnderMouse(const QPointF & value)
	{
		if (pressed_)
			return;

		QPoint p(value.x(), value.y());
		
		auto item = scene()->itemAt(value.x(),value.y(),this->transform());
		

	
		if (item == back_item_ || item == nullptr)
			item_under_mouse_ = nullptr;
		else item_under_mouse_ = dynamic_cast<QAbstractGraphicsShapeItem*>(item);

		
	}

	void EcvGraphicsView3::removeItem(QAbstractGraphicsShapeItem * value)
	{
		auto cur_item = dynamic_cast<EcvResizableGraphicsItem*>(value);
		if (cur_item) {
			auto item_region = regions_manager_->find(cur_item->data().regionID());
			if (item_region.removable()) {
				emit onDeleteObject(cur_item->data().objectCounter());
				delete value;
				value = nullptr;
			}
		}

	}

	void EcvGraphicsView3::setImage(const QString& file_name )
	{
		filename_ = file_name;
		auto pix = QPixmap::fromImage(QImage(file_name));
		//pix.fill();
		setImage(pix);

		//cv::Mat img = cv::imread(file_name.toStdString(),1);
		//setImage(img);

	}

	//void EcvGraphicsView3::setImage3(const QString& file_name)
	//{
	//	filename_ = file_name;
	//

	//	cv::Mat img = cv::imread(file_name.toStdString(),1);
	//	setImage(img);
	//}

	void EcvGraphicsView3::setBlankImage(const QString& filename,const QColor& color)
	{
		blank_image_filename_ = filename;
		setBackgroundBrush(QBrush(color, Qt::SolidPattern));
	}

	void EcvGraphicsView3::setBlank()
	{
		filename_ = "";
		if (!blank_image_filename_.isEmpty()) {
			auto pix = QPixmap::fromImage(QImage(blank_image_filename_));
			//pix.fill();
			setImage(pix);
		}
		else clear();

	}

	void EcvGraphicsView3::setImage(int width, int height, int stride, char* data, const QSize& fit_size)
	{
		if (data != nullptr) {
			QImage src((uchar*)data, width, height, stride, QImage::Format_RGB888);

			QPixmap pix;
			if (!fit_size.isEmpty()) {
				QImage src_img = src.scaled(fit_size, Qt::KeepAspectRatio);
				back_image_ = src_img;
			}
			else {
				back_image_ = src;
			}

			pix = QPixmap::fromImage(back_image_);
			setImage(pix);
		}
		else {
			setBlank();
		}
	}
	//void EcvGraphicsView3::setImage(const cv::Mat &src, const cv::Size& fit_size) {
	////	cout << "set" << endl;

	//	if (!src.empty()) {

	//		QPixmap pix;
	//		if (!fit_size.empty()) {
	//			cv::Mat src_img;
	//			ecv::fitOnSizeMat3(src, src_img, fit_size);
	//			back_image_ = mat2Image(src_img);
	//		}
	//		else  	back_image_ = mat2Image(src);

	//		pix = QPixmap::fromImage(back_image_);
	//		setImage(pix);
	//		//cout << "set captured :" ;
	//		//showNow();
	//	}
	//	else setBlank();

	//}

	//void EcvGraphicsView3::setImage2(const cv::Mat & src)
	//{
	//	std::vector<uchar> buffer;
	//	cv::imencode(".jpeg", src, buffer);
	//	QPixmap m_pixmap;
	//	if (buffer.size() != 0) {
	//		if (m_pixmap.loadFromData(buffer.data(), buffer.size(), "JPEG")) {
	//			setImage(m_pixmap);
	//		}
	//	}
	//}

	void EcvGraphicsView3::setImage(QPixmap src) {

		
		if (back_item_) {
			scene_->removeItem(reinterpret_cast<QGraphicsItem*>(back_item_));
			delete back_item_;
		}
		
		back_item_ = scene_->addPixmap(src);
		back_item_->setZValue(0);
		scene_->setSceneRect(QRectF(QPointF(0, 0), src.size()));
		setFitView(fit_view_);
	}

	void EcvGraphicsView3::setImage(QImage& src)
	{
		setImage(QPixmap::fromImage(src));
	}

	void EcvGraphicsView3::setImage(const QByteArray& src) {

		QPixmap pix;
		back_image_ = QImage::fromData(src, "jpg");  
		pix = QPixmap::fromImage(back_image_);
		setImage(pix);

	}
	QByteArray image2ByteArray2(const QImage& image, const std::string& ext) {
		QByteArray result;

		QBuffer buffer(&result);
		buffer.open(QIODevice::WriteOnly);
		image.save(&buffer, ext.c_str());
		return result;
	}
	QByteArray EcvGraphicsView3::getByteArray() const
	{
		return image2ByteArray2(back_image_,"jpg");
	}

	QPixmap EcvGraphicsView3::pixmap()
	{
		QPixmap pix = QPixmap::fromImage(back_image_);
		return pix;
		
	}


	void EcvGraphicsView3::clear()
	{
		//if (back_image_) 
		{
			back_image_ = QImage();
			scene_->clear();
			
			back_item_ = nullptr;
		}
	}
	EcvPaintAct EcvGraphicsView3::paintAct() const
	{
		return paint_act_;
	}
	void EcvGraphicsView3::setPaintAct(EcvPaintAct value)
	{
		if (paint_act_ != value) {
			paint_act_ = value;

		}
	}
	int EcvGraphicsView3::currentRegionId() const
	{
		return current_region_id_;
	}
	void EcvGraphicsView3::setCurrentRegionId(int value)
	{
		if (current_region_id_ != value) {
			current_region_id_ = value;
			cur_view_region_ = regions_manager_->find(current_region_id_);
			setShapeType(cur_view_region_.shape());
		}
	}
	EcvViewRegionsManager * EcvGraphicsView3::regionManager()
	{
		return regions_manager_;
	}

	EcvResizableGraphicsItem* EcvGraphicsView3::add(const EcvObjectData & object)
	{
		auto cur_view_region = regions_manager_->find(object.regionID());
		EcvResizableGraphicsItem* cur_item = nullptr;

		switch (cur_view_region.shape())
		{
		case EcvShapeType::rect:
			cur_item = new EcvResizableGraphicsRect(object, HANDLE_SIZE);
			break;
		case EcvShapeType::title_rect:
			cur_item = new EcvResizableGraphicsTitleRect(object,QString::number(object.objectCounter()));
			break; 
		case EcvShapeType::polygon:
			cur_item = new EcvResizableGraphicsPolygon(object);
			break;
		case EcvShapeType::title_polygon:
			cur_item = new EcvResizableGraphicsTitlePolygon(object,	QString::number(object.objectCounter()), HANDLE_SIZE);
			break;
		case EcvShapeType::ellipse:
			break;
		case EcvShapeType::blob:
			break;
		default:
			break;

		};
		if (cur_item) {
			cur_item->setFlag(QGraphicsItem::ItemIsSelectable, cur_view_region.selectable());
			cur_item->setFlag(QGraphicsItem::ItemIsMovable, cur_view_region.removable());

			scene_->addItem(cur_item);
			cur_item->setPen(cur_view_region.pen());
		}
		return cur_item;
	}

	EcvResizableGraphicsItem* EcvGraphicsView3::add(const EcvObjectData& object, const EcvShapeType& value)
	{
		setShapeType(value);
		return add(object);
	}
	std::vector<EcvResizableGraphicsItem*> EcvGraphicsView3::add(const EcvObjectDataList & objects)
	{
		vector<EcvResizableGraphicsItem*> result;
		result.reserve(objects.size());
		for (int i = 0; i < objects.size(); i++)
			result.push_back( add(objects[i]));
		return result;
	}

	void EcvGraphicsView3::getAllRemovableItems(EcvObjectDataList& objects)
	{
		auto items = scene_->items();

		objects.clear();

		objects.reserve(items.size());

		for (int i = 0; i < items.size(); i++) {
			auto cur_item = dynamic_cast<EcvResizableGraphicsItem*>(items[i]);
			if (cur_item) {
				auto& cur_region = regions_manager_->find(cur_item->data().regionID());
				if (cur_region.removable()) 
					objects.push_back(cur_item->data());
				
			}

		}
	}

	void EcvGraphicsView3::getAllItems(EcvObjectDataList & objects)
	{
		auto items = scene_->items();

		objects.clear();

		objects.reserve(items.size());

		for (int i = 0; i < items.size(); i++) {
			auto cur_item = dynamic_cast<EcvResizableGraphicsItem*>(items[i]);
			if (cur_item) {
				auto& cur_region = regions_manager_->find(cur_item->data().regionID());
				objects.push_back(cur_item->data());

			}

		}
	}

	void EcvGraphicsView3::getItems(const std::vector<int>& regions_id, EcvObjectDataList& objects)
	{
		auto items = scene_->items();
		
		objects.clear();

		objects.reserve(items.size());
		

		for (int i = 0; i < items.size(); i++) {
			auto cur_item = dynamic_cast<EcvResizableGraphicsItem*>(items[i]);
			if (cur_item == nullptr)
				continue;
			int cur_id = cur_item->data().regionID();

			auto pos = std::find_if(regions_id.begin(), regions_id.end(), [cur_id](int value) {return value == cur_id; });
			if (pos != regions_id.end()) {
				auto& cur_region = regions_manager_->find(cur_item->data().regionID());
				if (cur_region.removable()) {
					objects.push_back(cur_item->data());
				}
			}

		}

	}

	QImage EcvGraphicsView3::getQImage()
	{
		//QImage image;
		//QPainter painter(&image);
		//painter.setRenderHint(QPainter::Antialiasing);
		//scene()->render(&painter);
		//return image;

		scene()->clearSelection();                                                  // Selections would also render to the file
		scene()->setSceneRect(scene()->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
		QImage image(scene()->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
		image.fill(Qt::transparent);                                              // Start all pixels transparent

		QPainter painter(&image);
		scene()->render(&painter);

		return image;
	}

	void EcvGraphicsView3::getItemsExcept(const std::vector<int>& regions_id, EcvObjectDataList & objects)
	{
		auto items = scene_->items();

		objects.clear();

		objects.reserve(items.size());

		for (int i = 0; i < items.size(); i++) {
			auto cur_item = dynamic_cast<EcvResizableGraphicsItem*>(items[i]);
			int cur_id = cur_item->data().regionID();

			auto pos = std::find_if(regions_id.begin(), regions_id.end(), [cur_id](int value) {return value == cur_id; });
			if (pos == regions_id.end()) {
				auto& cur_region = regions_manager_->find(cur_item->data().regionID());
				if (cur_region.removable()) {
					objects.push_back(cur_item->data());
				}
			}

		}


	}

	void EcvGraphicsView3::deleteAllItems()
	{
		auto items = scene_->items();

		for (int i = 0; i < items.size(); i++) {
			auto cur_item = dynamic_cast<EcvResizableGraphicsItem*>(items[i]);
			if (cur_item) {
				auto& cur_region = regions_manager_->find(cur_item->data().regionID());
				if (cur_region.removable())
					scene_->removeItem(items[i]);
			}
			

		}
	}

	void EcvGraphicsView3::deleteItems(const std::vector<int>& regions_id)
	{
		auto items = scene_->items();

		for (int i = 0; i < items.size(); i++) {
			auto cur_item = dynamic_cast<EcvResizableGraphicsItem*>(items[i]);
			int cur_id = cur_item->data().regionID();

			auto pos = std::find_if(regions_id.begin(), regions_id.end(), [cur_id](int value) {return value == cur_id; });
			if (pos != regions_id.end()) {
				auto cur_region = regions_manager_->find(cur_item->data().regionID());
				if (cur_region.removable()) {
					scene_->removeItem(items[i]);
				}
			}

		}

	}

	void EcvGraphicsView3::setCurrentCursor()
	{
		setCursor(Qt::ArrowCursor);

		if (item_under_mouse_)
			switch (paint_act_)
			{
			case EcvPaintAct::add:
			{
				if (item_under_mouse_)
					setCursor(Qt::ForbiddenCursor);
				else item_under_mouse_ = nullptr;
			}
			break;
			case EcvPaintAct::edit:
				break;
			case EcvPaintAct::del:
				setCursor(Qt::CrossCursor);
				break;
			case EcvPaintAct::select:
			{

				if (item_under_mouse_) {
					if (item_under_mouse_->cursor().shape() == Qt::ArrowCursor)
						setCursor(Qt::SizeAllCursor);
					else setCursor(item_under_mouse_->cursor());
				}

				break;

			}
			}
	}
	QRectF getNormRect(const QPointF& pnt1, const QPointF& pnt2)
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
	void EcvGraphicsView3::editResizableGraphicsItem(ecv::EcvResizableGraphicsItem * value, const QPointF& dst_pnt)
	{

		value->data().setRect(getNormRect(first_point_, dst_pnt));

	}
