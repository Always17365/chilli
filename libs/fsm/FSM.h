#ifndef _INTERPRETER_HEADER_
#define _INTERPRETER_HEADER_
#include "common/xmlHelper.h"
#include <string>
#include <map>
#include "config.h"
#include <log4cplus/logger.h>

#include "scxml/TriggerEvent.h"
#include "scxml/EventDispatcher.h"
#include "scxml/Context.h"
//#include "scxml/Evaluator.h"
#include "scxml/SMInstance.h"
#include "scxml/model/Transition.h"
//#include "scxml/model/Log.h"
#include "common/lock.h"


using namespace std;


namespace fsm{

	//template class INTERPRETER_EXPORT std::map<std::string, Send *>;
	enum xmlType{
		File,
		Memory,
	};
	class FSM_EXPORT StateMachine {
	public:
		StateMachine(const string &xml = "", xmlType xtype = File);
		StateMachine(const StateMachine &other);
		virtual ~StateMachine();
		StateMachine & operator=(const StateMachine & other);
		
		//��ʼ��״̬��
		bool Init(void);
		bool Init(const string &xml, xmlType xtype = File);
		//��ʼ�����ʼ��״̬
		void go();
		const xmlNodePtr getCurrentState(void) const;
		const std::string getCurrentStateID(void) const;
		void pushEvent(TriggerEvent & Evt) const;
		void setName(const string &strName);
		bool addEventDispatcher( EventDispatcher * evtDsp);
		const std::string& getName() const;
		const std::string& getSessionId()const;
		Context  *  getRootContext() const; 
		xmlNodePtr getDataModel(); 
		void setscInstance(SMInstance *);
		void setLog(log4cplus::Logger log);
		void setSessionID(const std::string &strSessionid);
		void reset();
	protected:
		std::string m_strStateFile;
		helper::xml::CXmlDocumentPtr m_xmlDocPtr;
		//xmlHelper::xmlDocumentPtr _docPtr2;
		xmlNodePtr  m_initState;
		mutable xmlNodePtr m_currentStateNode;
		xmlNodePtr m_rootNode;
		std::string m_strSessionID;
		std::string m_strName;
		log4cplus::Logger  log;
		helper::xml::CXPathContextPtr xpathCtx;

		void normalize(const xmlNodePtr &rootNode);
		bool isState(const xmlNodePtr &xmlNode) const;
	private:
		//���ļ�������xml�ĵ���
		void parse();

		static bool inline isTransition(const xmlNodePtr &Node) ;
		static bool inline isLog(const xmlNodePtr &Node) ;
		static bool inline isEvent(const xmlNodePtr &Node) ;
		static bool inline isEntry(const xmlNodePtr &Node) ;
		static bool inline isExit(const xmlNodePtr &Node) ;
		static bool inline isSend(const xmlNodePtr &Node) ;
		static bool inline isScript(const xmlNodePtr &Node) ;
		static bool inline isTimer(const xmlNodePtr &Node) ;

		bool processEvent( const xmlNodePtr &eventNode) const;
		bool processTransition(const xmlNodePtr &node) const;
		bool processExit(const xmlNodePtr &node) const;

		//����entry�ڵ㺯��������entry�ڵ�ָ�룬����ֵ��ʾ�Ƿ����ִ�����µ�entry�ڵ㡣
		bool processEntry(const xmlNodePtr &node)const;
		bool processSend(const xmlNodePtr &node)const;
		bool processScript(const xmlNodePtr &node)const;
		bool processTimer(const xmlNodePtr &node)const;
		bool processLog(const xmlNodePtr &node) const;

		void enterStates(const xmlNodePtr &stateNode) const;
		void exitStates() const;
		xmlNodePtr getState(const string& stateId) const;

		const ::xmlNodePtr getParentState(const xmlNodePtr &currentState)const;
		xmlNodePtr getTargetStates(const xmlNodePtr &transition) const;
	private:
		std::map<std::string, EventDispatcher *> m_mapSendObject;
		SMInstance * m_scInstance;
		mutable helper::CLock m_lock;
	public:
		mutable TriggerEvent m_currentEvt;
	private:
		xmlType m_xmlType;
		std::string m_strStateContent;
		
	};
}
#endif