
#include "EcvGraphicsView3Ex.h"

namespace ecv {
	EcvGraphicsView3Ex::EcvGraphicsView3Ex(QWidget *parent):
		EcvGraphicsView3(),
		select_btn_(nullptr),
		add_btn_(nullptr),
		del_btn_(nullptr),
		clear_btn_(nullptr),

		select_action_(nullptr),
		add_action_(nullptr),
		del_action_(nullptr),
		clear_action_(nullptr)

	{
	}
	void EcvGraphicsView3Ex::setAllButtons(QPushButton * select_btn, QPushButton * add_btn, QPushButton * del_btn, QPushButton * clear_btn)
	{
		
		setButton(select_btn_, select_btn, this, &EcvGraphicsView3Ex::selectState);
		setButton(add_btn_, add_btn, this, &EcvGraphicsView3Ex::addState);
		setButton(del_btn_, del_btn, this, &EcvGraphicsView3Ex::delState);
		setButton(clear_btn_, clear_btn, this, &EcvGraphicsView3Ex::deleteAllItems);
	}
	void EcvGraphicsView3Ex::setAllActions(QAction * select_action, QAction * add_action, QAction * del_action, QAction * clear_action)
	{
		setAction(select_action_, select_action, this, &EcvGraphicsView3Ex::selectState);
		setAction(add_action_, add_action, this, &EcvGraphicsView3Ex::addState);
		setAction(del_action_, del_action, this, &EcvGraphicsView3Ex::delState);
		setAction(clear_action_, clear_action, this, &EcvGraphicsView3Ex::deleteAllItems);


	
	}

	void EcvGraphicsView3Ex::selectState()
	{
		if (select_btn_)
			select_btn_->setChecked(true);
		if (select_action_)
			select_action_->setChecked(true);
		setPaintAct(EcvPaintAct::select);
	}

	void EcvGraphicsView3Ex::addState()
	{
		if (add_btn_)
			add_btn_->setChecked(true);
		if (add_action_)
			add_action_->setChecked(true);
		setPaintAct(EcvPaintAct::add);
	}


	void EcvGraphicsView3Ex::delState()
	{
		if (del_btn_)
			del_btn_->setChecked(true);
		if (del_action_)
			del_action_->setChecked(true);
		setPaintAct(EcvPaintAct::del);
	}

}//ecv