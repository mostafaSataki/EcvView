#ifndef ECV_GRAPHICS_VIEW3_EX
#define ECV_GRAPHICS_VIEW3_EX

#include "viewlib_global.h"
#include "EcvGraphicsView3.h"
#include <QPushButton>
#include <QAction>

namespace ecv {

	class VIEWLIB_EXPORT EcvGraphicsView3Ex : public EcvGraphicsView3 {
		Q_OBJECT
	public:
		EcvGraphicsView3Ex(QWidget *parent = 0);
		void setAllButtons(QPushButton* select_btn, QPushButton* add_btn, QPushButton* del_btn, QPushButton* clear_btn);
		void setAllActions(QAction* select_action, QAction* add_action, QAction* del_action, QAction* clear_action);

		void selectState();
		void addState();
		void delState();
		


	private:
		QPushButton* select_btn_;
		QPushButton* add_btn_;
		QPushButton* del_btn_;
		QPushButton* clear_btn_;

		QAction* select_action_;
		QAction* add_action_;
		QAction* del_action_;
		QAction* clear_action_;
		
		template <typename Func2>
		void setButton(QPushButton* pre_btn, QPushButton* new_btn, const typename QtPrivate::FunctionPointer<Func2>::Object *receiver, Func2 slot)
		{
			if (new_btn != pre_btn) {
				if (pre_btn) {
					disconnect(pre_btn, &QPushButton::clicked, 0, 0);
					pre_btn->setCheckable(false);
					pre_btn->setAutoExclusive(false);
				}
				pre_btn = new_btn;
				if (pre_btn) {
					pre_btn->setCheckable(true);
					pre_btn->setAutoExclusive(true);
					connect(pre_btn, &QPushButton::clicked, receiver, slot);
				}

			}

		}

		template <typename Func2>
		void setAction(QAction* pre_action, QAction* new_action, const typename QtPrivate::FunctionPointer<Func2>::Object *receiver, Func2 slot)
		{
			if (new_action != pre_action) {
				if (pre_action) {
					disconnect(pre_action, &QAction::triggered, 0, 0);
					pre_action->setCheckable(false);
				}
				pre_action = new_action;
				if (pre_action) {
					pre_action->setCheckable(true);

					connect(pre_action, &QAction::triggered, receiver,slot);
				}

			}

		}

	};
	
}//ecv
#endif //ECV_GRAPHICS_VIEW3_EX
