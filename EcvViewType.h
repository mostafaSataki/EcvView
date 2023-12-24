#ifndef ECV_VIEW_TYPE
#define ECV_VIEW_TYPE

#include "viewlib_global.h"
#include <QPolygon>

namespace ecv {
	enum class EcvState { add_rect, add_polygon, edit_rect,edit_polygon, del_rect,del_polygon, select_rect ,select_polygon};
	enum class EcvShapeType { rect, title_rect,polygon,title_polygon, ellipse, blob ,none};
	
	enum class EcvCursors { del, del_over, img, arrow, move_over };


	



}//ecv

#endif //ECV_VIEW_TYPE
