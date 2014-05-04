#pragma once
#ifndef _SCXML_SCINSTANCE_HEADER_
#define _SCXML_SCINSTANCE_HEADER_

//#pragma warning(disable:4800)
#include <string>
#include <map>
#include <set>
#include <queue>
#include <list>
#include <vector>

#include <log4cplus\logger.h>
#include <libxml\tree.h>
#include <jsapi.h>

#include "..\config.h"
#include "Context.h"
#include "Evaluator.h"
#include "..\common\Timer.h"

namespace fsm
{


	/// <summary>
	/// ״̬��ִ��ģ�飬�����ű��������������ĵ�ά����
	/// 
	/// 
	/// </summary>

	class FSM_EXPORT SMInstance:public helper::TimerServer
	{
	private:
		/// <summary>
		/// The <code>Map</code> of <code>Context</code>s per
		/// </summary>
		mutable std::map<xmlNodePtr,Context *>contexts;//����ʹ�õ�Script ������
		mutable std::list<Context *>removedContexts;//�Ѿ���ʹ�õ�Script ������

		/// <summary>
		/// The evaluator for expressions.
		/// </summary>
		mutable std::vector<Evaluator *>evaluator;//Script �����

		static log4cplus::Logger log;
	private:
		virtual Evaluator *getEvaluator() const;
	public:
		SMInstance();
		virtual ~SMInstance();


		//virtual void setEvaluator(Evaluator *const evaluator);

		virtual  Context *getRootContext() const ;

		//virtual void setRootContext(Context *const context);

		virtual Context * getContext(xmlNodePtr xNode) const;
		virtual void removeContext(xmlNodePtr xNode);

		virtual Context *lookupContext(xmlNodePtr xNode);

		virtual void setContext(xmlNodePtr xNode, Context *const context);
	private:


	};
}
#endif //end head file