#pragma once
#ifndef _SCXML_TIMER_HEADER_
#define _SCXML_TIMER_HEADER_
#include <string>
#include <ctime>
#include "config.h"


namespace   fsm{

	//��ʱ��������״̬����ʵ�ֶ�ʱ���Ĺ��ܡ�
	class FSM_EXPORT Timer{
	public:
		//����һ����ʱ������ʱ��������ʱ����չ��������ʱ��id��
		Timer( int interval,std::string ext,std::string &strTimerId);
		virtual ~Timer();
		//��ʼ��ʱ
		void Start();
		//ִ��һ�Σ����㶨ʱ���Ƿ�ʱ��
		std::string Step();

		//��ʱ���Ƿ����
		bool valid;

		//����=
		Timer & operator=( Timer & other);
	private:
		std::string m_ext;
		std::string m_strTimerId;
		int m_interval;
		clock_t m_startTime;
	};
}
#endif // end timer header