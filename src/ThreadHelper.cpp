/*
 * ThreadHelper.cpp
 *
 *  Created on: Jul 25, 2016
 *      Author: developer
 */

#include "../inc/ThreadHelper.h"

namespace Mitrais
{
	namespace util
	{
		ThreadHelper::ThreadHelper()
		{}

		ThreadHelper::~ThreadHelper()
		{}

		/**
		 * Initialize threads as many as numOfThreads
		 * @param ioService the io service
		 * @param threads the threadpool
		 * @param numOfThreads number of threads
		 */
		void ThreadHelper::initializeThreads(
				boost::asio::io_service &ioService,
				boost::thread_group &threads,
				const int numOfThreads)
		{
			for (int i = 0; i < numOfThreads ; ++i)
			{
				// create threads
				threads.create_thread(
						boost::bind(&boost::asio::io_service::run, &ioService)
				);
			}
		}

		/**
		 * TODO: Remove this method once actual method is implemented
		 */
		int sleep_print(int seconds)
		{
			std::cout << "going to sleep (" << seconds << ")" << std::endl;
			sleep(seconds);
			std::cout << "wake up (" << seconds << ")" << std::endl;
			return 0;
		}

		/**
		 * Push task to a thread
		 * @param ioService the io service
		 * @param pendingData vector of future int to store result of the execution
		 */
		void ThreadHelper::pushTask(
				boost::asio::io_service& ioService,
				vector<boost::shared_future<int>>& pendingData)
		{
			/**
			 * TODO: replace sleep_print with actual method
			 * and seconds for params of the actual method
			 */
			int seconds =2;
			ptask_t task = boost::make_shared<task_t>(
					boost::bind(&sleep_print, seconds)
			);

			boost::shared_future<int> fut(task->get_future());
			pendingData.push_back(fut);
			ioService.post(boost::bind(&task_t::operator(), task));
		}

		/**
		 * Execute tasks in threadpool in async mode
		 * @param numOfThreads the number of thread
		 */
		void ThreadHelper::executeTaskAsync(const int numOfThreads)
		{
			boost::asio::io_service::work worker(ioService);

			initializeThreads(ioService, threads, numOfThreads);

			for (int i = 0; i < numOfThreads ; ++i)
			{
				pushTask(ioService, pendingData);
			}

			boost::wait_for_all(pendingData.begin(), pendingData.end());
		}
	}
}
