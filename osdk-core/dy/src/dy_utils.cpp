/*! @file dy_utils.cpp
*  @version 3.3
*  @date July 05 2017
*
*  @brief
*  Thread for Win32 platform.
*
*  @details
*  This is utility functions for dy projects.
*
*  @copyright
*  2016-17 DY innovations inc. All rights reserved.
* */

#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "dy_utils.hpp"

using namespace std;
using namespace DY;

const double DyUtils::DEG2RAD = 0.01745329252;
const double DyUtils::RAD2DEG = 57.29577951308;

std::string DyUtils::GetMilliTimestamp()
{
	tm localTime;
    time_t rawtime;
    struct tm* timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    //get milliseconds
	std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
	const std::chrono::duration<double> tse = t.time_since_epoch();
	std::chrono::seconds::rep milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(tse).count() % 1000;

	ostringstream oss;
	oss << (1900 + timeinfo->tm_year) << '-'
		<< std::setfill('0') << std::setw(2) << (timeinfo->tm_mon + 1) << '-'
		<< std::setfill('0') << std::setw(2) << timeinfo->tm_mday << ' '
		<< std::setfill('0') << std::setw(2) << timeinfo->tm_hour << ':'
		<< std::setfill('0') << std::setw(2) << timeinfo->tm_min << ':'
		<< std::setfill('0') << std::setw(2) << timeinfo->tm_sec << '.'
		<< std::setfill('0') << std::setw(3) << milliseconds;
	return oss.str();
}

Vector3f DyUtils::ToEulerAngle(const Quaternion &qData)
{
	Vector3f ans;

	double q2sqr = qData.q2 * qData.q2;
	double t0 = -2.0 * (q2sqr + qData.q3 * qData.q3) + 1.0;
	double t1 = +2.0 * (qData.q1 * qData.q2 + qData.q0 * qData.q3);
	double t2 = -2.0 * (qData.q1 * qData.q3 - qData.q0 * qData.q2);
	double t3 = +2.0 * (qData.q2 * qData.q3 + qData.q0 * qData.q1);
	double t4 = -2.0 * (qData.q1 * qData.q1 + q2sqr) + 1.0;

	t2 = (t2 > 1.0) ? 1.0 : t2;
	t2 = (t2 < -1.0) ? -1.0 : t2;

	ans.x = asin(t2);
	ans.y = atan2(t3, t4);
	ans.z = atan2(t1, t0);

	return ans;
}

int DyUtils::GetPosBySeparators(const std::string &sStr, const std::vector<char> &vecSep)
{
	vector<int> vecPos;
	for (auto cSep : vecSep){
		int iPos = sStr.find(cSep);
		if (iPos != std::string::npos){
			vecPos.push_back(iPos);
		}
	}

	if (vecPos.empty()){
		return std::string::npos;
	}

	return *(min_element(vecPos.begin(), vecPos.end()));
}

std::vector<std::string> DyUtils::SplitString(const std::string &sStr,
	const std::vector<char> &vecSep)
{
	vector<string> vecStr;
	int iIndex = 0;
	size_t iPos = 0;
	string tmpStr(sStr);
	while ((iPos = DyUtils::GetPosBySeparators(tmpStr, vecSep)) != std::string::npos)
	{
		string sToken = tmpStr.substr(0, iPos);
		if (sToken.compare("") != 0){
			vecStr.push_back(tmpStr.substr(0, iPos));
		}
		tmpStr = tmpStr.substr(iPos + 1);
	}

	if (tmpStr.compare("") != 0){
		vecStr.push_back(tmpStr);
	}

	return vecStr;
}

void DyUtils::Sleep(int iMilliseconds)
{
#ifdef WIN32
    Sleep(iMilliseconds);
#else
    usleep(iMilliseconds * 1000);
#endif
}

void DyUtils::SaveLogInLocal(const std::string &sStr)
{
	std::cerr << sStr << std::endl;
}
