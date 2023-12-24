#ifndef ECV_VIEW_REGION
#define ECV_VIEW_REGION

#include "viewlib_global.h"

#include <qpen.h>
#include "EcvViewType.h"

namespace ecv {

	class VIEWLIB_EXPORT EcvViewRegion {
	public:
		EcvViewRegion();
		EcvViewRegion(int id, const QPen& pen, const EcvShapeType& shape,bool selectable = true,bool resizable = true,bool editable = true,bool removable = true);

		EcvViewRegion& operator=(const EcvViewRegion& rhs);

		const int& ID()const;
		const QPen& pen()const;
		const EcvShapeType& shape()const;

		bool selectable()const;
		bool setSelectable()const;

		bool resizable()const;
		void setResizable(bool value);

		bool editable()const;
		void setEditable(bool value);

		bool removable()const;
		void setRemovable(bool value);

	private:
		int id_;
		QPen pen_;
		EcvShapeType shape_;
		bool selectable_;
		bool resizable_;
		bool editable_;
		bool removable_;
	};

	using EcvViewRegions = std::vector<EcvViewRegion>;
	using EcvViewRegionIt = EcvViewRegions::const_iterator;

	
}//ecv
#endif //ECV_VIEW_REGION
