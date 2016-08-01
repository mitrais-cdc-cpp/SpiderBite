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

	//main
	_view->onStopClicked( [this]{ this->setStopClicked_Callback(); });
	_view->onStartClicked( [this]{this->setStartClicked_Callback(); });

	//Menu
	_view->onOpenClicked( [this]{ this->setOpenMenuClicked_Callback(); });
	_view->onSaveClicked( [this]{ this->setSaveMenuClicked_Callback(); });
	_view->onSettingViewClicked( [this]{ this->setSettingMenuClicked_Callback(); });
	_view->onQuitClicked( [this]{ this->setQuitMenuClicked_Callback(); });
}

void MainPresenter::registerEventsModel()
{
	LOG_INFO << "registerEventsModel()";

	//start/stop application
	_model->whenApplicationStarts( [this]{ this->applicationStartCallback(); });
	_model->whenApplicationStop( [this]{ this->applicationStopCallback(); });

	//crawling
	_model->whenCrawlingStart( [this]{ this->crawlingStartCallback(); });
	_model->whenCrawlingStop( [this]{ this->crawlingStopCallback(); });
	_model->whenCrawlingRunning( [this]{ this->crawlingRunningCallback(); });
}

void MainPresenter::applicationStartCallback()
{
	_view->build();
	_view->start();
}

void MainPresenter::applicationStopCallback()
{
}

void MainPresenter::crawlingStartCallback()
{

}
void MainPresenter::crawlingStopCallback()
{
	//TBD inform the gui....
}
void MainPresenter::crawlingRunningCallback()
{
	//TBD update the gui....
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


///
/// MainView
///

void MainPresenter::setStopClicked_Callback()
{
	LOG_INFO << "setStopClicked_Callback()";
	_model->stopCrawling();
}

void MainPresenter::setStartClicked_Callback()
{
	LOG_INFO << "setStartClicked_Callback()";
	_model->startCrawling(_model->getUrls(), 0); // we start from level 0!
}

///
/// MainMenu
///

void MainPresenter::setSaveMenuClicked_Callback()
{
	LOG_INFO << "setSaveClicked_Callback()";
}

void MainPresenter::setOpenMenuClicked_Callback()
{
	LOG_INFO << "setOpenClicked_Callback()";

	_view->showOpenDialog();

	if(_model->readUrls(_view->getFilename()))
	{
		for(auto const& target: _model->getUrls())
		{
			urls.push_back(target.Url);
		}

		LOG_INFO << "send url collection to view";
		_view->displayFileContent(urls);
	}
	else
	{
		LOG_INFO << "couldnt read urls from file";
	}
}

void MainPresenter::setSettingMenuClicked_Callback()
{
	LOG_INFO << "setSettingViewClicked_Callback()";
	_view->openSettingView();
}

void MainPresenter::setQuitMenuClicked_Callback()
{
	LOG_INFO << "setQuitClicked_Callback()";
	this->applicationStopCallback();
}

///
/// SettingView
///


