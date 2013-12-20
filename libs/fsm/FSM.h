#ifndef _INTERPRETER_HEADER_
#define _INTERPRETER_HEADER_
#include "xmlHelper.h"
#include <string>
#include <map>
#include "config.h"
#include <log4cplus/logger.h>

#include "scxml/TriggerEvent.h"
#include "scxml/EventDispatcher.h"
#include "scxml/Context.h"
#include "scxml/Evaluator.h"
#include "scxml/SCInstance.h"
#include "scxml/model/Transition.h"
#include "scxml/model/Log.h"
#include "scxml/lock.h"


using namespace std;


namespace fsm{

	//template class INTERPRETER_EXPORT std::map<std::string, Send *>;
	class FSM_EXPORT StateMachine {
	public:
		StateMachine(const string xml = "");
		StateMachine(const StateMachine &other);
		virtual ~StateMachine();
		StateMachine & operator=(const StateMachine & other);
		
		//��ʼ��״̬��
		bool Init(void);
		bool Init(const string xmlFile);
		//��ʼ�����ʼ��״̬
		void go();
		const xmlNodePtr getCurrentState(void) const;
		const std::string getCurrentStateID(void) const;
		void pushEvent(TriggerEvent & Evt) const;
		void setName(const string &strName);
		bool addEventDispatcher( EventDispatcher * evtDsp);
		const std::string& getName();
		const std::string& getSessionId()const;
		Evaluator * getEvaluator() const;
		Context  *  getRootContext(); 
		xmlNodePtr getDataModel(); 
		void setscInstance(SCInstance *);
		void setLog(log4cplus::Logger log);
		void setSessionID(std::string strSessionid);
	protected:
		std::string m_strStateFile;
		xmlHelper::xmlDocumentPtr m_xmlDocPtr;
		//xmlHelper::xmlDocumentPtr _docPtr2;
		xmlNodePtr  m_initState;
		mutable xmlNodePtr m_currentStateNode;
		xmlNodePtr m_rootNode;
		std::string m_strSessionID;
		std::string m_strName;
		log4cplus::Logger  log;

		void normalize(const xmlNodePtr rootNode);
		bool isState(const xmlNodePtr xmlNode) const;
	private:
		//���ļ�������xml�ĵ���
		void parse();

		static bool inline isTransition(const xmlNodePtr Node) throw();
		static bool inline isLog(const xmlNodePtr Node) throw();
		static bool inline isEvent(const xmlNodePtr Node) throw();
		static bool inline isEntry(const xmlNodePtr Node) throw();
		static bool inline isExit(const xmlNodePtr Node) throw();
		static bool inline isSend(const xmlNodePtr Node) throw();
		static bool inline isScript(const xmlNodePtr Node) throw();
		static bool inline isTimer(const xmlNodePtr Node) throw();

		void processEvent( xmlNodePtr eventNode) const;
		void processTransition(model::Transition & transition) const;
		void processExit(const xmlNodePtr node) const;

		//����entry�ڵ㺯��������entry�ڵ�ָ�룬����ֵ��ʾ�Ƿ����ִ�����µ�entry�ڵ㡣
		bool processEntry(const xmlNodePtr node)const;
		void processSend(const xmlNodePtr node)const;
		void processScript(const xmlNodePtr node)const;
		void processTimer(const xmlNodePtr node)const;

		void enterStates(const xmlNodePtr stateNode) const;
		void exitStates() const;
		xmlNodePtr getState(const string& stateId) const;

		const ::xmlNodePtr getParentState(const xmlNodePtr currentState)const;
		xmlNodePtr getTargetStates(const xmlNodePtr transition) const;
	private:
		std::map<std::string, EventDispatcher *> m_mapSendObject;
		SCInstance * m_scInstance;
		mutable fsm::CLock m_lock;
	public:
		mutable TriggerEvent m_currentEvt;
		
	};
}
#endif