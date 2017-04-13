#pragma once
#ifndef _SCXML_TRIGGEREVENT_HEADER_
#define _SCXML_TRIGGEREVENT_HEADER_
#include "..\config.h"
#include <string>
#include <json/json.h>

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
		TriggerEvent(const std::string &name, const std::string & type); 

		
	private:
		std::string m_strEventName;
		std::string m_strMsgType;
		const void * m_ParamPtr;
		std::map<std::string, Json::Value> m_eventVars;
		
		
	public:
		void setEventName(const std::string &strEventName){m_strEventName = strEventName;}
		void setMsgType(const std::string &strMsgtype){m_strMsgType = strMsgtype;}
		void setParam(const void * param){m_ParamPtr = param;}
		void addVars(const std::string & name, const Json::Value & value);

		const std::string &getEventName()const{return m_strEventName;}
		const std::string &getMsgType(){return m_strMsgType;}
		const void * getParam(){return m_ParamPtr;}
		const std::map <std::string,Json::Value> &getVars() { return m_eventVars; };

		virtual bool Equals(const TriggerEvent & obj);
		virtual std::string ToString();

	};
}

#endif // end head file