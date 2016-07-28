#ifndef _MAINPRESENTER_H_
#define _MAINPRESENTER_H_

#include <memory>
#include "../view/MainView.hpp"
#include "../model/MainModel.hpp"


namespace Mitrais {
namespace Presenter {

class MainPresenter
{
public:
	MainPresenter(View::MainView* view_, Model::MainModel* model_);
	~MainPresenter();

	void registerEvents();
	void registerEventsView();
	void registerEventsModel();

	//View
	void setSaveClicked_Callback();
	void setQuitClicked_Callback();
	void setOpenClicked_Callback();
	void setStopClicked_Callback();
	void setStartClicked_Callback();
	void setSettingClicked_Callback();

	void applicationStartCallback();

	//Model



private:

	View::MainView* _view;
	Model::MainModel* _model;
};

}} //namespace Mitrais::presenter



#endif // _MAINPRESENTER_H_
