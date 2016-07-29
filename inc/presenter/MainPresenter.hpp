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

	//View
	void setSaveClicked_Callback();
	void setQuitClicked_Callback();
	void setOpenClicked_Callback();
	void setStopClicked_Callback();
	void setStartClicked_Callback();
	void setSettingViewClicked_Callback();

	void applicationStartCallback();
	void applicationStopCallback();
	void crawlingStartCallback();
	void crawlingStopCallback();
	void crawlingRunningCallback();

	//Model

private:

	void registerEventsView();
	void registerEventsModel();


	std::vector<std::string> urls;
	View::MainView* _view;
	Model::MainModel* _model;
};

}} //namespace Mitrais::presenter



#endif // _MAINPRESENTER_H_
