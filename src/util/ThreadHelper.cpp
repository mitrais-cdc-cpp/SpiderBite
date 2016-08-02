/*
 * ThreadHelper.cpp
 *
 *  Created on: Jul 25, 2016
 *      Author: developer
 */

#include "../../inc/util/ThreadHelper.h"

using namespace Mitrais::util;

ThreadHelper::ThreadHelper()
{}

ThreadHelper::~ThreadHelper()
{}

/**
 * Initialize threads as many as numOfThreads
 * @ioService the io service
 * @threads the threadpool
 * @numOfThreads number of threads
 */
void ThreadHelper::initializeThreads(const int numOfThreads)
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
 * @ioService the io service
 * @pendingData vector of future int to store result of the execution
 */
void ThreadHelper::pushTask(
		Model::MainModel &model,
		util::WebCrawler &crawler,
		util::UrlTarget& target)
{
	/**
	 * and seconds for params of the actual method
	 */

	ptask_t task = boost::make_shared<task_t>(
			boost::bind(&Model::MainModel::test, boost::ref(model), boost::ref(crawler), boost::ref(target))
	);

	boost::shared_future<int> fut(task->get_future());
	pendingData.push_back(fut);
	ioService.post(boost::bind(&task_t::operator(), task));
}

/**
 * Execute tasks in threadpool in async mode
 * @numOfThreads the number of thread
 */
void ThreadHelper::executeTaskAsync(const int numOfThreads)
{
	boost::asio::io_service::work worker(ioService);

	initializeThreads(numOfThreads);

	boost::wait_for_all(pendingData.begin(), pendingData.end());
}
