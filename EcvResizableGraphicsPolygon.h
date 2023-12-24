#ifndef ECV_RESIZABLE_GRAPHICS_POLYGON
#define ECV_RESIZABLE_GRAPHICS_POLYGON

#include "viewlib_global.h"
#include "EcvResizableGraphicsItem.h"
#include "EcvObjectData.h"

namespace ecv {
	extern const int HANDLE_SIZE;
	class VIEWLIB_EXPORT EcvResizableGraphicsPolygon : public EcvResizableGraphicsItem {
		
	public:

		EcvResizableGraphicsPolygon(const EcvObjectData& data, int handel_size = HANDLE_SIZE, QGraphicsItem *parent = 0);
		virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
		
	private:
	};

}//ecv
#endif //ECV_RESIZABLE_GRAPHICS_POLYGON
