#ifndef ECVGRAPHICSSCENE_H
#define ECVGRAPHICSSCENE_H

#include "viewlib_global.h"

#include <QGraphicsScene>

namespace ecv {
	class VIEWLIB_EXPORT EcvGraphicsScene : public QGraphicsScene
	{
		

	public:
		EcvGraphicsScene(QObject *parent = 0);
		~EcvGraphicsScene();

	private:

	};
}//ecv
#endif // ECVGRAPHICSSCENE_H
