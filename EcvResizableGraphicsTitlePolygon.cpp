
#include "EcvResizableGraphicsTitlePolygon.h"
#include <algorithm>

#include <QApplication>

using namespace std;

namespace ecv {
	EcvResizableGraphicsTitlePolygon::EcvResizableGraphicsTitlePolygon(const EcvObjectData& data, const QString &title, int handle_size , 
		QGraphicsItem *parent ):	
		EcvResizableGraphicsPolygon(data, handle_size, parent)
	{
		setTitleVisiable(true);
		setTitle(title);
		//setPen(pen);

	}


}//ecv