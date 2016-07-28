/*
 * MainModel.hpp
 *
 *  Created on: Jul 28, 2016
 *      Author: developer
 */

#ifndef INC_MODEL_MAINMODEL_HPP_
#define INC_MODEL_MAINMODEL_HPP_

#include <functional>
#include <iostream>
#include "../util/UrlTarget.h"
#include "../util/TextReader.h"
#include "../util/TextWriter.h"

namespace Mitrais
{
	namespace Model
	{
		typedef std::function<void()> CallbackFunction;

		class MainModel
		{
		public:
			~MainModel();
			MainModel(MainModel const&) = delete;
			void operator=(MainModel const&) = delete;

			static MainModel* getInstance();

			void run();
			std::vector<Mitrais::util::UrlTarget> readUrlFromFile(std::string filename);
			void writeUrlToFile(std::string fileName, std::vector<Mitrais::util::UrlTarget> urls);

			void whenApplicationStarts(CallbackFunction callback);
			void whenReadUrlsFromFile(CallbackFunction callback);
			void whenWriteUrlsToFile(CallbackFunction callback);

		private:
			MainModel();
			CallbackFunction cb;
			static MainModel* m_instance;
		};
	}
}



#endif /* INC_MODEL_MAINMODEL_HPP_ */
