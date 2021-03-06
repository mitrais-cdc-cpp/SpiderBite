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



	//Main
	void setStopClicked_Callback();
	void setStartClicked_Callback();

	//Menu
	void setOpenMenuClicked_Callback();
	void setSettingMenuClicked_Callback();
	void setQuitMenuClicked_Callback();
	void setSaveMenuClicked_Callback();

	//SettingsView
	void setSVSaveClicked_Callback();
	void setSVCancelClicked_Callback();
	void setSVCloseClicked_Callback();
	void setSVOpenDialogClicked_Callback();


	void applicationStartCallback();
	void applicationStopCallback();
	void crawlingStartCallback();
	void crawlingStopCallback();
	void crawlingRunningCallback();

	//Model

private:

	void registerEvents();
	void registerEventsView();
	void registerEventsModel();


	std::vector<std::string> urls;
	View::MainView* _view;
	Model::MainModel* _model;
};

}} //namespace Mitrais::presenter



#endif // _MAINPRESENTER_H_
