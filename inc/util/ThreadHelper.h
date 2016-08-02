/*
 * ThreadHelper.h
 *
 *  Created on: Jul 25, 2016
 *      Author: developer
 */

#ifndef INC_THREADHELPER_H_
#define INC_THREADHELPER_H_

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/move/move.hpp>
#include <unistd.h>

#include "WebCrawler.h"

namespace Mitrais
{
	namespace util
	{
		class ThreadHelper
		{
		public:
			ThreadHelper();
			~ThreadHelper();
			static int test(util::WebCrawler &crawler, util::UrlTarget url);
			void executeTaskAsync(const int numOfThreads);
			void pushTask(
					util::WebCrawler &crawler,
					util::UrlTarget& target);

		private:
			typedef boost::packaged_task<int> task_t;
			typedef boost::shared_ptr<task_t> ptask_t;

			vector<boost::shared_future<int>> pendingData;
			boost::asio::io_service ioService;
			boost::thread_group threads;

			void initializeThreads(const int numOfThreads);
		};
	}
}


#endif /* INC_THREADHELPER_H_ */
