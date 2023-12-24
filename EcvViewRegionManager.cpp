
#include "EcvViewRegionManager.h"
#include <algorithm>

namespace ecv {

	EcvViewRegionsManager::EcvViewRegionsManager()
	{
		regions_.push_back(EcvViewRegion(0, QPen(Qt::green), EcvShapeType::rect));
	}

	EcvViewRegionsManager::EcvViewRegionsManager(const EcvViewRegions& regions)
	{
		regions_.insert(regions_.end(), regions.begin(), regions.end());
	}

	bool EcvViewRegionsManager::add(int id, const QPen& pen, const EcvShapeType& shape, bool selectable , bool resizable , bool editable , bool removable )
	{
		return add(EcvViewRegion(id, pen, shape,selectable,resizable,editable,removable));
	}

	bool EcvViewRegionsManager::add(const EcvViewRegion& region)
	{
		bool result = false;
		if (findId(region.ID()) == -1 && findShapePen(region) == -1) {
			result = true;
			regions_.push_back(region);

		}
		return result;
	}

	bool EcvViewRegionsManager::del(int id)
	{
		bool result = false;
		auto index = findId(id);
		if (index != -1) {
			result = true;
			regions_.erase(regions_.begin() + index);
		}
		return result;

	}

	void EcvViewRegionsManager::clear()
	{
		regions_.clear();
	}

	size_t EcvViewRegionsManager::size() const
	{
		return regions_.size();
	}

	const EcvViewRegion& EcvViewRegionsManager::find(int id) const
	{
		auto index = findId(id);
		assert(index != -1);

		return regions_[index];
	}

	const EcvViewRegion& EcvViewRegionsManager::find(const QPen& pen, const EcvShapeType& shape) const
	{
		auto index = findShapePen(EcvViewRegion(-1,pen,shape));
		assert(index != -1);

		return regions_[index];
	}

	const EcvViewRegion& EcvViewRegionsManager::operator[](int index)const
	{
		assert(index >= 0 && index < regions_.size());
		return regions_[index];
	}

	void EcvViewRegionsManager::setViewRegions(const EcvViewRegions & regions)
	{
		regions_.clear();
		regions_ = regions;
	}

	int EcvViewRegionsManager::findId(int id)const
	{
		int result = -1;
		auto pos = std::find_if(regions_.begin(), regions_.end(), [id](const EcvViewRegion& value) { return value.ID() == id; });
		if (pos != regions_.end())
			result = std::distance(regions_.begin(), pos);
		return result;
	}

	int EcvViewRegionsManager::findShapePen(const EcvViewRegion& region)const
	{
		int result = -1;
		auto pos = std::find_if(regions_.begin(), regions_.end(), [region](const EcvViewRegion& value) {
			return value.pen().color() == region.pen().color() && value.shape() == region.shape();
		});
		if (pos != regions_.end())
			result = std::distance(regions_.begin(), pos);

		return result;
	}



}//ecv