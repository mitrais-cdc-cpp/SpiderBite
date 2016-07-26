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

using namespace std;

namespace Mitrais
{
	namespace util
	{
		class ThreadHelper
		{
		public:
			ThreadHelper();
			~ThreadHelper();
			void executeTaskAsync(const int numOfThreads);

		private:
			typedef boost::packaged_task<int> task_t;
			typedef boost::shared_ptr<task_t> ptask_t;

			vector<boost::shared_future<int>> pendingData;
			boost::asio::io_service ioService;
			boost::thread_group threads;

			void initializeThreads(
					boost::asio::io_service &ioService,
					boost::thread_group &threads,
					const int numOfThreads);

			void pushTask(
					boost::asio::io_service& ioService,
					vector<boost::shared_future<int>>& pendingData);
		};
	}
}


#endif /* INC_THREADHELPER_H_ */