#ifndef ECV_VIEW_REGIONS_MANAGER
#define ECV_VIEW_REGIONS_MANAGER

#include "viewlib_global.h"

#include "EcvViewRegion.h"

namespace ecv {

	class VIEWLIB_EXPORT EcvViewRegionsManager {
	public:
		EcvViewRegionsManager();
		EcvViewRegionsManager(const EcvViewRegions& regions);
		bool add(int id, const QPen& pen, const EcvShapeType& shape, bool selectable = true, bool resizable = true, bool editable = true, bool removable = true);
		bool add(const EcvViewRegion& region);
		bool del(int id);
		void clear();
		size_t size()const;
		const EcvViewRegion& find(int id)const;
		int findId(int id)const;
		const EcvViewRegion& find(const QPen& pen, const EcvShapeType& shape)const;


		const EcvViewRegion& operator[](int index)const;

		void setViewRegions(const EcvViewRegions& regions);
	private:
		EcvViewRegions regions_;
		
		int findShapePen(const EcvViewRegion& region)const;

	};
}//ecv

#endif //ECV_VIEW_REGIONS_MANAGER
