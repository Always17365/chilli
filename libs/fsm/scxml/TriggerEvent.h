#pragma once
#ifndef _SCXML_TRIGGEREVENT_HEADER_
#define _SCXML_TRIGGEREVENT_HEADER_
#include <string>
#include <config.h>

namespace fsm
{

	//״̬���¼��࣬�����¼�ʱ������һ���˶���Ȼ���͸�״̬����
	class FSM_EXPORT TriggerEvent
	{

	public:

		//�����¼����ƺ��¼���������һ���¼���
		TriggerEvent(const std::string &name, int const type); //this(name, type, nullptr);
		//�����¼����ƣ����ݣ��¼���������һ���¼���
		TriggerEvent(const std::string &name, const std::string &data, int const type); 
		/// <summary>
		/// <code>CALL_EVENT</code>.
		/// </summary>
		static const int CALL_EVENT = 1;

		/// <summary>
		/// <code>CHANGE_EVENT</code>.
		/// 
		/// </summary>
		static const int CHANGE_EVENT = 2;

		/// <summary>
		/// <code>SIGNAL_EVENT</code>.
		/// 
		/// </summary>
		static const int SIGNAL_EVENT = 3;

		/// <summary>
		/// <code>TIME_EVENT</code>.
		/// 
		/// </summary>
		static const int TIME_EVENT = 4;

		/// <summary>
		/// <code>ERROR_EVENT</code>.
		/// 
		/// </summary>
		static const int ERROR_EVENT = 5;

		
	private:
		std::string name;
		int type;
		std::string data;
	public:
		virtual std::string &getName();
		virtual std::string &getData();
		virtual int getType();
		virtual bool Equals(const TriggerEvent & obj);
		virtual std::string ToString();

	};
}

#endif // end head file