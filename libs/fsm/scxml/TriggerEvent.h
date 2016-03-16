#pragma once
#ifndef _SCXML_TRIGGEREVENT_HEADER_
#define _SCXML_TRIGGEREVENT_HEADER_
#include "..\config.h"
#include <string>

namespace fsm
{

	//״̬���¼��࣬�����¼�ʱ������һ���˶���Ȼ���͸�״̬����
	class FSM_EXPORT TriggerEvent
	{

	public:

		TriggerEvent():m_ParamPtr(NULL){};
		//�����¼����ƺ��¼���������һ���¼���
		TriggerEvent(const std::string &name); //this(name,nullptr);
		//�����¼����ƣ����ݣ��¼���������һ���¼���
		TriggerEvent(const std::string &name, const std::string &data); 

		
	private:
		std::string m_strEventName;
		std::string m_strMsgType;
		std::string m_strData;
		const void * m_ParamPtr;
		std::map<std::string,std::string> m_eventVars;
		
		
	public:
		void setEventName(const std::string &strEventName){m_strEventName = strEventName;}
		void setData(const std::string &strData){m_strData = strData;}
		void setMsgType(const std::string &strMsgtype){m_strMsgType = strMsgtype;}
		void setParam(const void * param){m_ParamPtr = param;}
		void setVars(std::map<std::string,std::string> params);

		const std::string &getEventName()const{return m_strEventName;}
		const std::string &getData(){return m_strData;}
		const std::string &getMsgType(){return m_strMsgType;}
		const void * getParam(){return m_ParamPtr;}
		const std::map <std::string,std::string> &getVars() { return m_eventVars; };

		virtual bool Equals(const TriggerEvent & obj);
		virtual std::string ToString();

	};
}

#endif // end head file