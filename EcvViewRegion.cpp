
#include "EcvViewRegion.h"
#include "qrgb.h"

namespace ecv {
	EcvViewRegion::EcvViewRegion():
		id_(-1),
		pen_(QPen(Qt::green)),
		shape_(EcvShapeType::none),
		selectable_(true),
		resizable_(true),
		editable_(false),
		removable_(false)
	{
	}
	EcvViewRegion::EcvViewRegion(int id, const QPen& pen, const EcvShapeType& shape,bool selectable,bool resizable, bool editable , bool removable ):
		id_(id),
		pen_(pen),
		shape_(shape),
		selectable_(selectable),
		resizable_(resizable),
		editable_(editable),
		removable_(removable)
	{

	}

    EcvViewRegion& EcvViewRegion::operator=(const EcvViewRegion& rhs)
	{
		if (this == &rhs)
			return *this;

		id_ = rhs.id_;
		pen_ = rhs.pen_;
		shape_ = rhs.shape_;

		selectable_ = rhs.selectable_;
		resizable_ = rhs.resizable_;
		removable_ = rhs.removable_;
		editable_ = rhs.editable_;

		return *this;
	
	}
	const int& EcvViewRegion::ID() const
	{
		return id_;
	}



	const QPen& EcvViewRegion::pen() const
	{
		return pen_;
	}

	const EcvShapeType& EcvViewRegion::shape() const
	{
		return shape_;
	}

	bool EcvViewRegion::selectable() const
	{
		return selectable_;
	}

	bool EcvViewRegion::setSelectable() const
	{
		return selectable_;
	}

	bool EcvViewRegion::resizable() const
	{
		return resizable_;
	}

	void EcvViewRegion::setResizable(bool value)
	{
		resizable_ = value;
	}

	bool EcvViewRegion::editable() const
	{
		return editable_;
	}

	void EcvViewRegion::setEditable(bool value)
	{
		editable_ = value;
	}

	bool EcvViewRegion::removable() const
	{
		return removable_;
	}

	void EcvViewRegion::setRemovable(bool value)
	{
		removable_ = value;
	}

	

}//ecv