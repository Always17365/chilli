#pragma once
#ifndef _SCXML_TIMER_HEADER_
#define _SCXML_TIMER_HEADER_
#include <string>
#include <ctime>
#include <log4cplus/logger.h>
#include <sys/timeb.h>
#include "config.h"


namespace   fsm{

	//��ʱ��������״̬����ʵ�ֶ�ʱ���Ĺ��ܡ�
	class FSM_EXPORT Timer{
	public:
		//����һ����ʱ������ʱ��������ʱ����չ��������ʱ��id��
		Timer( int interval,const std::string &ext,const std::string &strTimerId);
		virtual ~Timer();
		//��ʼ��ʱ
		void Start();
		//ִ��һ�Σ����㶨ʱ���Ƿ�ʱ��
		std::string execute();
		unsigned long long getInterval() const{
			struct timeb currTime;
			ftime(&currTime);
			long long i = m_interval - ((currTime.time-m_startTime.time)*1000 + currTime.millitm-m_startTime.millitm);
			return i > 0?i:0;
		};


		//����=
		Timer & operator=( Timer & other);
	

	private:
		std::string m_ext;
		std::string m_strTimerId;
		int m_interval;
		struct timeb m_startTime;
		log4cplus::Logger log;
	};
	class TimerComp{
	public:
		bool operator() (const Timer * const A, const Timer * const B)
		{
			return (A->getInterval()  > B->getInterval());
		}

	};
}
#endif // end timer header