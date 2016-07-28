#include "../../inc/presenter/MainPresenter.hpp"
#include "../../inc/util/Logger.h"

using namespace Mitrais::Presenter;

MainPresenter::MainPresenter(View::MainView* view_, Model::MainModel* model_)
: _view(view_)
, _model(model_)
{
	registerEvents();
}

MainPresenter::~MainPresenter()
{
	delete _view;
	delete _model;
}

void MainPresenter::registerEventsView()
{
	LOG_INFO << "registerEventsView()";

	_view->onSaveClicked( [this]{ this->setSaveClicked_Callback(); });
	_view->onQuitClicked( [this]{ this->setQuitClicked_Callback(); });
	_view->onOpenClicked( [this]{ this->setOpenClicked_Callback(); });
	_view->onStopClicked( [this]{ this->setStopClicked_Callback(); });
	_view->onStartClicked( [this]{this->setStartClicked_Callback(); });
//	_view->onSettingClicked( [this]{ this->setSettingClicked_Callback(); });
}

void MainPresenter::registerEventsModel()
{
	LOG_INFO << "registerEventsModel()";
	_model->whenApplicationStarts( [this]{ this->applicationStartCallback(); });
}

void MainPresenter::applicationStartCallback()
{
	_view->build();
	_view->start();
}

void MainPresenter::registerEvents()
{
	try
	{
		registerEventsView();
		registerEventsModel();
	}
	catch(std::exception& ex)
	{
		LOG_ERROR << "an error occurs while register events: " << ex.what();
	}
}



void MainPresenter::setSaveClicked_Callback()
{
	LOG_INFO << "setSaveClicked_Callback()";
}

void MainPresenter::setQuitClicked_Callback()
{
	LOG_INFO << "setQuitClicked_Callback()";
}

void MainPresenter::setOpenClicked_Callback()
{
	LOG_INFO << "setOpenClicked_Callback()";
}

void MainPresenter::setStopClicked_Callback()
{
	LOG_INFO << "setStopClicked_Callback()";
}

void MainPresenter::setStartClicked_Callback()
{
	LOG_INFO << "setStartClicked_Callback()";
}

void setSettingClicked_Callback()
{
	LOG_INFO << "setSettingClicked_Callback()";
//	PropertyUI prop;
//	prop.activateUI(argc, argv);
}

