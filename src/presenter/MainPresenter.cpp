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

	_view->onSettingViewClicked( [this]{ this->setSettingViewClicked_Callback(); });
}

void MainPresenter::registerEventsModel()
{
	LOG_INFO << "registerEventsModel()";
	_model->whenApplicationStarts( [this]{ this->applicationStartCallback(); });
	_model->whenApplicationStop( [this]{ this->applicationStopCallback(); });
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



void MainPresenter::setSaveClicked_Callback()
{
	LOG_INFO << "setSaveClicked_Callback()";
}

void MainPresenter::setQuitClicked_Callback()
{
	LOG_INFO << "setQuitClicked_Callback()";
	this->applicationStopCallback();
}

void MainPresenter::setOpenClicked_Callback()
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

void MainPresenter::setStopClicked_Callback()
{
	LOG_INFO << "setStopClicked_Callback()";
	_model->stopCrawling();
}

void MainPresenter::setStartClicked_Callback()
{
	LOG_INFO << "setStartClicked_Callback()";
	_model->startCrawling(_model->getUrls());
}


void MainPresenter::setSettingViewClicked_Callback()
{
	LOG_INFO << "setSettingViewClicked_Callback()";
	_view->openSettingView();
}

