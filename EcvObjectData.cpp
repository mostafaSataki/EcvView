
#include "EcvObjectData.h"


namespace ecv {
	EcvObjectData::EcvObjectData() :
		rect_(QRectF()),
		object_counter_(-1),
		region_id_(0)
	{
	}
	EcvObjectData::EcvObjectData(const QRectF & rect, int object_counter, int region_id, const QPolygonF& points) :
		rect_(rect),
		object_counter_(object_counter),
		region_id_(region_id),
		polygon_(points)
	{
	}
	EcvObjectData::EcvObjectData(const EcvObjectData & rhs)
	{
		*this = rhs;
	}
	EcvObjectData & EcvObjectData::operator=(const EcvObjectData & rhs)
	{
		if (this == &rhs)
			return *this;

		rect_ = rhs.rect_;
		object_counter_ = rhs.object_counter_;
		region_id_ = rhs.region_id_;
		polygon_ = rhs.polygon_;

		return *this;
	}
	bool EcvObjectData::operator==(const EcvObjectData & rhs)
	{
		return object_counter_ == rhs.object_counter_ && region_id_ == rhs.region_id_;
	}
	void EcvObjectData::set(const QRectF & rect, int object_counter, int region_id, const QPolygonF& points)
	{
		rect_ = rect;
		object_counter_ = object_counter;
		region_id_ = region_id;
		polygon_ = points;
	}
	QRectF & EcvObjectData::rect()
	{
		return rect_;
	}
	//cv::Rect EcvObjectData::cvRect() const
	//{
	//	return cv::Rect(rect_.x(), rect_.y(), rect_.width(), rect_.height());
	//}
	void EcvObjectData::setRect(const QRectF & value)
	{
		if (rect_ != value) {
			rect_ = value;
			emit rectChanged();
		}
	}
	//void EcvObjectData::setRect(const cv::Rect & vlaue)
	//{
	//	setRect(cvRect2QRect(vlaue));

	//}
	int EcvObjectData::objectCounter() const
	{
		return object_counter_;
	}
	void EcvObjectData::setObjectCounter(int value)
	{
		object_counter_ = value;
	}
	int EcvObjectData::regionID() const
	{
		return region_id_;
	}
	void EcvObjectData::setRegionID(int value)
	{
		region_id_ = value;
	}
	const QPolygonF & EcvObjectData::polygon() const
	{
		return polygon_;
	}
	void EcvObjectData::setPolygon(const QPolygonF & value)
	{
		polygon_ = value;
		rect_ = value.boundingRect();
		emit rectChanged();


	}
	int EcvObjectData::diameter() const
	{
		auto dis = rect_.bottomRight() - rect_.topLeft();
		return (int)dis.manhattanLength();
	}


	

	EcvObjectDataList filterDataListByRegionID(const EcvObjectDataList & list, const std::vector<int>& regions_id)
	{
		EcvObjectDataList result;
		result.reserve(list.size());
		for (int i = 0; i < list.size(); i++) {
			auto pos = std::find(regions_id.begin(), regions_id.end(), list[i].regionID());
			if (pos != regions_id.end())
				result.push_back(list[i]);
		}
		return result;
	}

	QDataStream& operator<< (QDataStream& stream, const EcvObjectData& value)
	{

		stream << value.object_counter_;
		stream << value.region_id_;
		stream << value.rect_;
		stream << value.polygon_;
		return stream;
	}

	 QDataStream& operator >> (QDataStream& stream, EcvObjectData& value)
	{
		 stream >> value.object_counter_;
		 stream >> value.region_id_;
		 stream >> value.rect_;
		 stream >> value.polygon_;
		return stream;
	}

}//ecv