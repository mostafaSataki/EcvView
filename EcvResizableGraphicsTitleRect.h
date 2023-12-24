#ifndef ECV_RESIZABLE_GRAPHICS_TITLE_RECT
#define  ECV_RESIZABLE_GRAPHICS_TITLE_RECT

#include "viewlib_global.h"
#include <array>

#include "EcvResizableGraphicsRect.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include <QCursor>




namespace ecv {
	

	class VIEWLIB_EXPORT EcvResizableGraphicsTitleRect : public EcvResizableGraphicsRect {
		
	public:
		
		EcvResizableGraphicsTitleRect(const EcvObjectData& data, const QString &title, int handle_size = HANDLE_SIZE, QGraphicsItem *parent = 0);

	};
}//ecv
#endif //ECV_RESIZABLE_GRAPHICS_TITLE_RECT