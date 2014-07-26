#pragma once
#ifndef _SCXML_TRIGGEREVENT_HEADER_
#define _SCXML_TRIGGEREVENT_HEADER_
#include <string>
#include "..\config.h"

namespace fsm
{

	//״̬���¼��࣬�����¼�ʱ������һ���˶���Ȼ���͸�״̬����
	class FSM_EXPORT TriggerEvent
	{

	public:

		TriggerEvent():m_ParamPtr(NULL),type(-1){};
		//�����¼����ƺ��¼���������һ���¼���
		TriggerEvent(const std::string &name, int const type); //this(name, type, nullptr);
		//�����¼����ƣ����ݣ��¼���������һ���¼���
		TriggerEvent(const std::string &name, const std::string &data, int const type); 

		
	private:
		std::string m_strEventName;
		std::string m_strData;
		const void * m_ParamPtr;
		int type;
		
		
	public:
		void setEventName(const std::string &strEventName){m_strEventName = strEventName;}
		void setData(const std::string &strData){m_strData = strData;}
		void setParam(const void * param){m_ParamPtr = param;}

		const std::string &getEventName(){return m_strEventName;}
		const std::string &getData(){return m_strData;}
		const void * getParam(){return m_ParamPtr;}

		const int &getType(){return type;}

		virtual bool Equals(const TriggerEvent & obj);
		virtual std::string ToString();

	};
}

#endif // end head file