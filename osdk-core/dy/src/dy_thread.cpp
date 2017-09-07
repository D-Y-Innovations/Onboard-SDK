/*! @file dy_thread.cpp
*  @version 3.3
*  @date Jun 30 2017
*
*  @brief
*  Thread for Win32 platform.
*
*  @details
*  This is thread implementation for dy which inherit from
*  DJI::OSDK::Thread class.
*
*  @copyright
*  2016-17 DY innovations inc. All rights reserved.
* */

#ifdef _WIN32
#include <windows.h>
#include <iostream>
#include <sstream>
#include "dy_thread.hpp"

using namespace std;
using namespace DJI::OSDK;
using namespace DY;

DyThread::DyThread()
{
	vehicle = NULL;
	type = 0;
	m_pThread = NULL;
}

DyThread::DyThread(DJI::OSDK::Vehicle *vehicle, int type)
{
	this->vehicle = vehicle;
	this->type = type;
	m_pThread = NULL;
	vehicle->setStopCond(false);
}

DyThread::~DyThread()
{
}

bool DyThread::createThread()
{
	int ret = -1;
	std::string infoStr;

	try
	{
		if (1 == type)
		{
			infoStr = "sendPoll";
			m_pThread = std::make_shared<std::thread>(send_call, (void *)vehicle);
		}
		else if (2 == type)
		{
			infoStr = "readPoll";
			m_pThread = std::make_shared<std::thread>(read_call, (void *)vehicle);
		}
		else if (3 == type)
		{
			infoStr = "callback";
			m_pThread = std::make_shared<std::thread>(callback_call, (void *)vehicle);
		}
		else
		{
			infoStr = "error type number";
		}
	}
	catch (const exception &e)
	{
		ostringstream oss;
		oss << "Exception: " << e.what();
		DERROR("%s, fail to create thread for %s!\n", oss.str().c_str(), infoStr.c_str());
		return false;
	}

	return true;
}


int DyThread::stopThread()
{
	int ret = -1;
	void *status;
	vehicle->setStopCond(true);

	m_pThread->join();

	return 0;
}

void DyThread::send_call(void *param)
{
	Vehicle *pVehicle = (Vehicle *)param;
	while (true)
	{
		pVehicle->protocolLayer->sendPoll();
        Sleep(10);
	}
}

void DyThread::read_call(void *param)
{
	RecvContainer recvContainer;
	Vehicle	*pVehicle = (Vehicle *)param;
	while (!(pVehicle->getStopCond()))
	{
		// receive() implemented on the OpenProtocol side
		recvContainer = pVehicle->protocolLayer->receive();
		pVehicle->processReceivedData(recvContainer);
		Sleep(10); //! @note CPU optimization, reduce the CPU usage a lot
	}

	DDEBUG("Quit read function\n");
}

void DyThread::callback_call(void* param)
{
	Vehicle* pVehicle = (Vehicle*)param;
	while (!(pVehicle->getStopCond()))
	{
		pVehicle->callbackPoll();
		Sleep(10); //! @note CPU optimization, reduce the CPU usage a lot
	}

	DDEBUG("Quit callback function\n");
}
#endif
