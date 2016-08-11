/*
 * ThreadHelper.h
 *
 *  Created on: Jul 25, 2016
 *      Author: developer
 */

#ifndef INC_THREADHELPER_H_
#define INC_THREADHELPER_H_

#include <boost/thread.hpp>

namespace Mitrais
{
	namespace util
	{
		static bool _beRunning = true;

		class ThreadHelper
		{
		public:

			ThreadHelper()
			{

			}

			~ThreadHelper()
			{

			}

			static void setBeRunning(bool status)
			{
				_beRunning = status;
			}

			static bool getBeRunning()
			{
				return _beRunning;
			}

			template<typename function, typename arg>
			void executeAsyncBoost(function func, arg urls)
			{
				int size = urls.size();
				boost::thread p[size];

				for(int i=0; i<size; i++)
				{
					p[i]=boost::thread(func, urls[i]);
				}

				// TODO: Fix the mechanism for joining the thread, for now it still block the GUI
				/*for(int i=0; i<size; i++)
				{
					p[i].join();
				}*/
			}
		};
	}
}


#endif /* INC_THREADHELPER_H_ */
