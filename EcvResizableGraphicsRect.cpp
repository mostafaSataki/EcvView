
#include "EcvResizableGraphicsRect.h"
#include <QPainter>
namespace ecv {

	EcvResizableGraphicsRect::EcvResizableGraphicsRect(const EcvObjectData & data, int handel_size, QGraphicsItem * parent):
		EcvResizableGraphicsItem(data,handel_size,parent)
	{
	}
	void EcvResizableGraphicsRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/)
	{
		if (widget) {
			EcvResizableGraphicsItem::paint(painter, option, widget);

				
				painter->drawRect(data().rect());

			

			//for (size_t i = 0; i < 8; i++) {
			//	//painter->drawRect(getSqure(handle_points_[i]));
			//	int next_i = (i + 1) % 8;

			//	auto line = getLine(handle_points_[i], handle_points_[next_i], handle_size_);
			//	painter->drawLine(line);
			//}

			
		}
	

	}
}//ecv