/*
 * MainModel.cpp
 *
 *  Created on: Jul 28, 2016
 *      Author: developer
 */

#include "../../inc/model/MainModel.hpp"

using namespace Mitrais::Model;

MainModel* MainModel::m_instance = nullptr;

MainModel::MainModel()
{}

MainModel::~MainModel()
{
	delete m_instance;
}

MainModel* MainModel::getInstance()
{
	if(!m_instance)
		m_instance = new MainModel();
	return m_instance;
}

void MainModel::whenApplicationStarts(CallbackFunction callback)
{
	cb = callback;
}

void MainModel::whenReadUrlsFromFile(CallbackFunction callback)
{

}

void MainModel::run()
{
	cb();
}

std::vector<Mitrais::util::UrlTarget> MainModel::readUrlFromFile(std::string filename)
{
	util::TextReader reader(filename);
	util::BaseResponse response;
	return reader.getUrls(response);

}
