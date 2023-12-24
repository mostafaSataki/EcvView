

#include "EcvResizableGraphicsTitleRect.h"

#include <algorithm>

#include <QApplication>

using namespace std;

namespace ecv {

	EcvResizableGraphicsTitleRect::EcvResizableGraphicsTitleRect(const EcvObjectData& data, const QString &title, int handle_size , 
		QGraphicsItem *parent ):
		EcvResizableGraphicsRect(data, handle_size,parent)
		
	{
		setTitleVisiable(true);
		setTitle(title);
		

	}


}//ecv