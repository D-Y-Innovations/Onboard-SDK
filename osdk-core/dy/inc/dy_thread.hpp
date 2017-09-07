/*! @file dy_thread_manager.hpp
*  @version 3.3
*  @date Jun 30 2017
*
*  @brief
*  Thread for Win32 platform.
*
*  @details
*  This is thread manager implementation for dy which inherit from
*  DJI::OSDK::ThreadAbstract class.
*
*  @copyright
*  2016-17 DY innovations inc. All rights reserved.
* */

#ifndef DY_THREAD_H
#define DY_THREAD_H

#include <memory>
#include <thread>
#include "dji_vehicle.hpp"
#include "dji_thread_manager.hpp"

namespace DY
{
	class DyThread : public DJI::OSDK::Thread
	{
	public:
		DyThread();
		DyThread(DJI::OSDK::Vehicle *vehicle, int type);
		~DyThread();

	public:
		bool createThread();
		int stopThread();

	private:
		std::shared_ptr<std::thread> m_pThread;

	private:
		static void send_call(void *param);
		static void read_call(void *param);
		static void callback_call(void *param);
	};
}	//namespace DY

#endif	//DY_THREAD_H