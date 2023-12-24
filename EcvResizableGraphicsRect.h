#ifndef ECV_RESIZABLE_GRAPHICS_RECT
#define ECV_RESIZABLE_GRAPHICS_RECT

#include "viewlib_global.h"
#include "EcvResizableGraphicsItem.h"


namespace ecv {
	extern const int HANDLE_SIZE ;
	class VIEWLIB_EXPORT EcvResizableGraphicsRect : public EcvResizableGraphicsItem {
		
	public:
		
		EcvResizableGraphicsRect(const EcvObjectData& data, int handel_size = HANDLE_SIZE, QGraphicsItem *parent = 0);
		virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
		
	private:
		
	};

}//ecv
#endif //ECV_RESIZABLE_GRAPHICS_RECT
