#ifndef DB_GRAPHICS_VIEW_H
#define DB_GRAPHICS_VIEW_H

#include "viewlib_global.h"
#include "EcvGraphicsView3.h"
#include <qwidget.h>


class VIEWLIB_EXPORT DbGraphicsView : public EcvGraphicsView3
{
	Q_OBJECT
public:

	explicit DbGraphicsView(QWidget* parent = nullptr);
	Q_PROPERTY(int column_id READ columnID WRITE setColumnID)
		Q_PROPERTY(QString column READ column WRITE setColumn)
		Q_PROPERTY(QString table_name READ tableName WRITE setTableName)
		Q_PROPERTY(QString title READ title WRITE setTitle)
		Q_PROPERTY(bool show_column READ showColumn WRITE setShowColumn)
		
	int columnID()const;
	QString column()const;
	QString tableName()const;
	QString title()const;
	bool showColumn()const;


public slots:
	void setValue(const QString& value);
	void clear();
	QString getValue()const;
	void setColumnID(int value);
	void setColumn(const QString& value);
	void setTitle(const QString& value);
	void setTableName(const QString& value);
	void setShowColumn(bool value);
protected:

	int column_id_;
	QString column_;
	QString table_name_;
	QString title_;
	bool show_column_;

};

#endif //DB_TIME_EDIT_H

