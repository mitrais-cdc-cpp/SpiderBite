/*
 * TextWriter.cpp
 *
 *  Created on: Jun 21, 2016
 *      Author: Andi_y
 */

#include "../../inc/util/TextWriter.h"

using namespace Mitrais::util;

/**
 * TextWriter default constructor
 */
TextWriter::TextWriter()
{

}

/**
 * TextWriter destructor
 */
TextWriter::~TextWriter()
{

}

/**
 * TextWriter constructor with param
 *
 * @param filepath a string filepath
 */
TextWriter::TextWriter(std::string filepath) :
		_file(filepath)
{
	// log info
	LOG_INFO << "Set the file path to be save the web crawler result into "+ _file;
}

/**
 * TextWriter constructor with params
 *
 * @param filepath a string filepath
 * @param content a string content
 */
TextWriter::TextWriter(std::string filepath, std::string content) :
		_file(filepath), _content(content)
{
	// log info
	LOG_INFO << "Set the file path to be save the web crawler result into "+ _file;
}

/**
 * TextWriter constructor with param
 *
 * @param filepath a string filepath
 * @params const UrlTarget& target a URL Target
 */
TextWriter::TextWriter(std::string filepath, const UrlTarget& target) :
		_file(filepath), _protocolType(target.Protocol), _url(target.Url)
{
	// log info
	LOG_INFO << "Set the file path to be save the web crawler result into "+ _file;
}

/**
 * TextWriter constructor with params
 *
 * @param filepath a string filepath
 * @param content a string content
 * @params const UrlTarget& target a URL Target
 */
TextWriter::TextWriter(std::string filepath, std::string content, const UrlTarget& target) :
		_file(filepath), _content(content), _protocolType(target.Protocol), _url(target.Url)
{
	// log info
	LOG_INFO << "Set the file path to be save the web crawler result into "+ _file;
}

/**
 * Set Content method
 *
 * @param value a string value
 */
void TextWriter::setContent(std::string value)
{
	_content = value;
}

/**
 * Set file path method
 *
 * @param value a string value
 */
void TextWriter::setFilePath(std::string value)
{
	_file = value;
}

/**
 * Write to file method
 *
 * @param response a response address
 * @param isSaveAsHtml is save as HTML
 */
void TextWriter::writeToFile(BaseResponse& response, bool isSaveAsHtml = true)
{
	try
	{
		std::string directoryPath;

		std::string fileName = _file;

		if (isSaveAsHtml)
		{
			directoryPath = util::Configuration::getSetting().pathToLocalDir;

			// fill blanks if we find http:// or https://
			if(fileName.find("http://") != std::string::npos)
				fileName = replaceFirst(fileName, "http://", "");

			if(fileName.find("https://") != std::string::npos)
				fileName = replaceFirst(fileName, "https://", "");

			// fill blanks if we find www.
			if(fileName.find("www.") != std::string::npos)
				fileName = replaceFirst(fileName, "www.", "");

			// replace / with _
			if(fileName.find("/") != std::string::npos)
				fileName = replaceAll(fileName, "/", "_");

			fileName += ".html";
			fileName = directoryPath + "/" + fileName;
		}

		_fileStream.open(fileName.c_str(), std::ios::trunc);

		if(_fileStream.is_open())
		{
			// insert the content to file stream
			_fileStream << _content;

			// close file stream after insert
			_fileStream.close();

			response.updateStatus(true);
			response.addSuccessMessage();

			// log info
			LOG_INFO << "Successed save the result into "+ fileName;
		}
		else
		{
			std::string message = "Unable to open " + _file;

			response.addMessage(message);
			response.updateStatus(false);

			// log error
			LOG_ERROR << message;
		}
	}
	catch (std::exception& ex)
	{
		// catch the exception
		std::string message = std::string(ex.what());

		response.addMessage(message);
		response.updateStatus(false);

		// log error
		LOG_ERROR << message;
	}
}

/**
 * Method to replace in a given string ALL appearances
 * @param subject_ target string
 * @param old_ substring as old appearance
 * @param new_ substring as new replace
 * @return
 */
std::string TextWriter::replaceAll(std::string subject_, const std::string& old_, const std::string& new_)
{
	// do nothing if old string is empty
	if(!old_.empty())
	{
		std::size_t pos = 0;

		// iterate through target string until reached npos
		// if appearance is found, replace it
		while ((pos = subject_.find(old_, pos)) != std::string::npos)
		{
			subject_.replace(pos, old_.length(), new_);
			pos += new_.length();
		}
	}

	return subject_;
}

/**
 *  * Method to replace in a given string the FIRST appearances
 * @param subject_ target string
 * @param old_ substring as old appearance
 * @param new_ substring as new replace
 * @return
 */
std::string TextWriter::replaceFirst(std::string subject_, const std::string& old_, const std::string& new_)
{
	if(!old_.empty())
	{
		subject_.replace( subject_.find(old_), old_.length(), new_);
	}
	return subject_;
}

/**
 * Write to database method
 * @param response: BaseResponse reference
 */
void TextWriter::writeToDatabase(BaseResponse &response)
{
	try
	{
		const std::string dbHost = Configuration::getSetting().dbHost;
		const int dbPort = Configuration::getSetting().dbPort;
		const std::string dbName = Configuration::getSetting().dbName;
		DB::Connector connector(dbHost, dbPort, dbName);
		DB::Website website;

		switch (_protocolType)
		{
		case util::UrlTargetProtocol::HTTP:
			website.protocolType = "http";
			break;
		case util::UrlTargetProtocol::HTTPS:
			website.protocolType = "https";
			break;
		case util::UrlTargetProtocol::FTP:
			website.protocolType = "ftp";
			break;
		default:
			website.protocolType = "http";
		}

		website.url = _url;
		website.content = _content;

		connector.Insert(website);

		std::string message = _file + " is success saved to database";
		response.updateStatus(true);
		response.addMessage(_file);

		LOG_INFO << message;
	}
	catch (std::exception& ex)
	{
		// catch the exception
		std::string message = std::string(ex.what());

		response.addMessage(message);
		response.updateStatus(false);

		// log error
		LOG_ERROR << message;

	}
}
