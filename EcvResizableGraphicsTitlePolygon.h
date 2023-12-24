#ifndef ECV_RESIZABLE_GRAPHICS_TITLE_POLYGON
#define  ECV_RESIZABLE_GRAPHICS_TITLE_POLYGON

#include "viewlib_global.h"
#include <array>

#include "EcvResizableGraphicsPolygon.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include <QCursor>




namespace ecv {
	

	class VIEWLIB_EXPORT EcvResizableGraphicsTitlePolygon : public EcvResizableGraphicsPolygon {
		
	public:
		
		EcvResizableGraphicsTitlePolygon(const EcvObjectData& data, const QString &title, int handle_size = HANDLE_SIZE,  QGraphicsItem *parent = 0);

	};
}//ecv
#endif //ECV_RESIZABLE_GRAPHICS_TITLE_POLYGON