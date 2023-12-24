#ifndef ECVOBJECTDATA_H
#define ECVOBJECTDATA_H

#include "viewlib_global.h"
#include <QObject>
#include <QRectF>
#include <QPolygonF>
#include <QObject>
#include <QDataStream>


namespace ecv {


	class VIEWLIB_EXPORT EcvObjectData :public QObject {
		Q_OBJECT
	public:
		EcvObjectData();
		EcvObjectData(const QRectF& rect, int object_counter, int region_id, const QPolygonF& points = QPolygonF());
		EcvObjectData(const EcvObjectData& rhs);

		EcvObjectData& operator=(const EcvObjectData& rhs);
		bool operator==(const EcvObjectData& rhs);

		void set(const QRectF& rect, int object_counter, int region_id, const QPolygonF& points = QPolygonF());

		QRectF& rect();
		//cv::Rect cvRect()const;
		void setRect(const QRectF& value);
		//void setRect(const cv::Rect& vlaue);

		int objectCounter()const;
		void setObjectCounter(int value);

		int regionID()const;
		void setRegionID(int value);

		const QPolygonF& polygon()const;
		void setPolygon(const QPolygonF& value);

		int diameter() const;
	signals:
		void rectChanged();
	protected:
		QRectF rect_;
		int object_counter_;
		int region_id_;
		QPolygonF polygon_;
		friend VIEWLIB_EXPORT QDataStream& operator<< (QDataStream& stream, const EcvObjectData& value);
		friend VIEWLIB_EXPORT QDataStream& operator >> (QDataStream& stream, EcvObjectData& value);
	};

	using EcvObjectDataList = QVector<EcvObjectData>;

	VIEWLIB_EXPORT EcvObjectDataList filterDataListByRegionID(const EcvObjectDataList& list, const std::vector<int>& regions_id);

	VIEWLIB_EXPORT QDataStream& operator<< (QDataStream& stream, const EcvObjectData& value);
	VIEWLIB_EXPORT QDataStream& operator >> (QDataStream& stream, EcvObjectData& value);


}//ecv
#endif // ECVOBJECTDATA_H
