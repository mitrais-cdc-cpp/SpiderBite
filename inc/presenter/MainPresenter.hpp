#ifndef _MAINPRESENTER_H_
#define _MAINPRESENTER_H_

#include <memory>
#include "../view/MainView.hpp"


namespace Mitrais {
namespace Presenter {

namespace Model {
class MainModel;
}


class MainPresenter
{
public:
	MainPresenter(std::shared_ptr<View::MainView> view_, std::shared_ptr<Model::MainModel> model_);
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

	//Model



private:

	std::shared_ptr<View::MainView> _view;
	std::shared_ptr<Model::MainModel> _model;
};

}} //namespace Mitrais::presenter



#endif // _MAINPRESENTER_H_
