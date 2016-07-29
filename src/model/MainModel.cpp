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

void MainModel::writeUrlToFile(std::string filename, bool isSaveAsHtml)
{
	util::TextWriter writer(filename);
	util::BaseResponse response;
	writer.writeToFile(response, isSaveAsHtml);
}

void MainModel::writeUrlToDatabase(std::string filename)
{
	util::TextWriter writer(filename);
	util::BaseResponse response;
	writer.writeToDatabase(response);
}

std::vector<std::string> MainModel::findUrls(std::string content)
{
	util::TextLexer lexer(content);
	util::BaseResponse response;
	return lexer.findUrls(response);
}

void MainModel::clearBuffer(vector<std::string> stringBuffer)
{
	util::TextBuffer buffer(stringBuffer);
	buffer.clearBuffer();
}

void MainModel::insertContentToBuffer(vector<std::string> stringBuffer ,string content)
{
	util::TextBuffer buffer(stringBuffer);
	buffer.insertContentToBuffer(content);
}
