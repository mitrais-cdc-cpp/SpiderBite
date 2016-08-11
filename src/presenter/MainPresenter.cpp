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

	//SettingsView
	_view->onSVSaveClicked( [this]{ this->setSVSaveClicked_Callback(); });
	_view->onSVCancelClicked( [this]{ this->setSVCancelClicked_Callback(); });
	_view->onSVOpenDialogClicked( [this]{ this->setSVOpenDialogClicked_Callback(); });
	_view->onSVCloseClicked( [this]{ this->setSVCloseClicked_Callback(); });

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
	_model->checkConfigSetting();
	_view->build();
	_view->start();
}

void MainPresenter::applicationStopCallback()
{
	_view->closeMainView();
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
	_view->enableControlsWhenStopClicked();
	_view->setMessageToStatusbar("Crawling stopped");
}

void MainPresenter::setStartClicked_Callback()
{
	LOG_INFO << "setStartClicked_Callback()";
	_view->disableControlsWhenStartClicked();
	_model->startCrawling(_model->getUrls());
}

///
/// MainMenu
///

void MainPresenter::setSaveMenuClicked_Callback()
{
	LOG_INFO << "setSaveClicked_Callback()";

	_view->showSaveDialog();

	std::string fileName = _view->getFileName();
	std::string content = _view->getStringFromTextBuffer();

	_model->saveUrls(fileName, content);

	_view->setMessageToStatusbar("Saved into : " + fileName);

	LOG_INFO << "Save file: " + fileName;
}

void MainPresenter::setOpenMenuClicked_Callback()
{
	urls.clear();

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
	_view->openSettingView(*(_model->loadXMLConfiguration()));
}

void MainPresenter::setQuitMenuClicked_Callback()
{
	LOG_INFO << "setQuitClicked_Callback()";
	this->applicationStopCallback();
}

///
/// SettingView
///
void MainPresenter::setSVSaveClicked_Callback()
{
	LOG_INFO << "setSVSaveClicked_Callback()";
	util::ConfigSettings config;
	_view->onSettingFormSaveButtonClicked();

	config.dbHost = View::SettingView::getInstance()->getDbHost();
	config.dbPort = View::SettingView::getInstance()->getDbPort();
	config.dbName = View::SettingView::getInstance()->getDbName();
	config.logFileName = View::SettingView::getInstance()->getLogFileName();
	config.crawlingDeepness = View::SettingView::getInstance()->getCrawlingDeepness();
	config.saveTarget = View::SettingView::getInstance()->getSaveMode();
	config.pathToLocalDir = View::SettingView::getInstance()->getPathToLocalDir();

	_model->saveXMLConfiguration(config);
}

void MainPresenter::setSVCancelClicked_Callback()
{
	LOG_INFO << "setSVCancelClicked_Callback()";
	_view->onSettingFormCancelButtonClicked();
}

void MainPresenter::setSVCloseClicked_Callback()
{
	LOG_INFO << "setSVOpenDialogClicked_Callback()";
	_view->onSettingFormCloseForm();
}

void MainPresenter::setSVOpenDialogClicked_Callback()
{
	LOG_INFO << "setSVOpenDialogClicked_Callback()";
	_view->onSettingFormOpenDialogClicked();
}



