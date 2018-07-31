#pragma once
#include "../config.h"

namespace helper {

	//��ʱ����ʱ֪ͨ�ӿ�

	class FSM_EXPORT OnTimerInterface
	{
	public:
		OnTimerInterface() {}

	public:

		/// <summary>
		/// Send this message to the target.
		/// </summary>

		virtual void OnTimer(unsigned long timerId, const std::string & attr, void * userdata) = 0;

	};
}