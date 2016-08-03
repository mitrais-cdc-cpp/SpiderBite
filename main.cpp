/*
 * main.cpp
 *
 *  Created on: May 30, 2016
 *      Author: ari
 */

#include <iostream>
#include <boost/archive/tmpdir.hpp>

#include "inc/view/MainUI.h"

#include "inc/model/MainModel.hpp"
#include "inc/presenter/MainPresenter.hpp"
#include "inc/view/MainView.hpp"

using namespace Mitrais::View;
using namespace Mitrais::Model;
using namespace Mitrais::Presenter;

int main(int argc, char* argv[])
{
	// logger example
	LOG_INFO << "Program started";

	gtk_init(&argc, &argv);
	MainPresenter presenter(MainView::getInstance(), MainModel::getInstance());
	MainModel::getInstance()->run();
	MainModel::getInstance()->stop();
	return 0;
}


