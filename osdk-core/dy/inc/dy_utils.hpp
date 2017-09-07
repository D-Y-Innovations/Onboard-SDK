/*! @file dy_utils.hpp
*  @version 3.3
*  @date July 05 2017
*
*  @brief
*  utilities for Win32 platform.
*
*  @details
*  This is utility functions for dy projects.
*
*  @copyright
*  2016-17 DY innovations inc. All rights reserved.
* */

#ifndef DY_UTILS_H
#define DY_UTILS_H

#include <string>
#include <vector>
#include <sstream>

namespace DY
{
	/*! @brief struct for TOPIC_QUATERNION
	*
	*/
	typedef struct Quaternion
	{
		float q0; /*!< w */
		float q1; /*!< x */
		float q2; /*!< y */
		float q3; /*!< z */

		Quaternion(float q0_, float q1_, float q2_, float q3_) :
			q0(q0_), q1(q1_), q2(q2_), q3(q3_){};
	} Quaternion;   // pack(1)

	/*!
	* @brief struct for multiple Topics
	*/
	typedef struct Vector3f
	{
		float x;
		float y;
		float z;
		
		Vector3f() :x(0.0), y(0.0), z(0.0){};
		Vector3f(float x_, float y_, float z_) :
			x(x_), y(y_), z(z_){};
	} Vector3f; // pack(1)

	class DyUtils
	{
	public:
		static Vector3f ToEulerAngle(const Quaternion &qData);

	public:
		static std::string GetMilliTimestamp();
		static int GetPosBySeparators(const std::string &sStr, const std::vector<char> &vecSep);
		static std::vector<std::string> SplitString(const std::string & sStr,
			const std::vector<char> &vecSep);

        //cross-platform sleep function
        static void Sleep(int iMilliSeconds);

		static void SaveLogInLocal(const std::string &sStr);

	public:
		const static double DEG2RAD;
		const static double RAD2DEG;
	};
}	//namespace DY

#endif	//DY_UTILS_H
