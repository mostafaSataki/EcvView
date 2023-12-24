#include "DbGraphicsView.h"

DbGraphicsView::DbGraphicsView(QWidget* parent):
	EcvGraphicsView3(parent),
	column_id_(0),
	column_(""),
	table_name_(""),
	title_(""),
	show_column_(true)

{
}

int DbGraphicsView::columnID() const
{
	return column_id_;
}

QString DbGraphicsView::getValue() const
{
	return filename();
}

void DbGraphicsView::setColumnID(int value)
{
	column_id_ = value;
}

QString DbGraphicsView::column() const
{
	return column_;
}

void DbGraphicsView::setColumn(const QString& value)
{
	column_ = value;
}

QString DbGraphicsView::tableName() const
{
	return table_name_;
}

void DbGraphicsView::setTableName(const QString& value)
{
	table_name_ = value;
}

void DbGraphicsView::setShowColumn(bool value)
{
	show_column_ = value;
}

QString DbGraphicsView::title() const
{
	return title_;
}

bool DbGraphicsView::showColumn() const
{
	return show_column_;
}

void DbGraphicsView::setTitle(const QString& value)
{
	title_ = value;
}

void DbGraphicsView::setValue(const QString& value)
{
	if (!value.isEmpty())
		setImage(value);
	else clear();
}

void DbGraphicsView::clear() {
	setBlank();
}
