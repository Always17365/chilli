#ifndef _INTERPRETER_HEADER_
#define _INTERPRETER_HEADER_
#include "common/xmlHelper.h"
#include <string>
#include <map>
#include "config.h"
#include <log4cplus/logger.h>

#include "scxml/TriggerEvent.h"
#include "scxml/SendInterface.h"
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
		//const xmlNodePtr getCurrentState(void) const;
		const std::string getCurrentStateID(void) const;
		
		const std::string& getName() const;
		const std::string& getSessionId()const;

		bool setVar(const std::string &name, const Json::Value &value);
		Json::Value getVar(const std::string &name) const;
		bool addSendImplement( SendInterface * evtDsp);
		void setscInstance(SMInstance *);
		void setLog(log4cplus::Logger log);
		void setSessionID(const std::string &strSessionid);
		void reset();
		void pushEvent(TriggerEvent & Evt);
		void mainEventLoop();
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
		
	private:
		//���ļ�������xml�ĵ���
		void parse();

		static bool isState(const xmlNodePtr &xmlNode) ;
		static bool isTransition(const xmlNodePtr &Node) ;
		static bool isLog(const xmlNodePtr &Node) ;
		static bool isEvent(const xmlNodePtr &Node) ;
		static bool isEntry(const xmlNodePtr &Node) ;
		static bool isExit(const xmlNodePtr &Node) ;
		static bool isSend(const xmlNodePtr &Node) ;
		static bool isScript(const xmlNodePtr &Node) ;
		static bool isTimer(const xmlNodePtr &Node) ;
		static bool isRaise(const xmlNodePtr &Node) ;

		bool processEvent(const TriggerEvent &event);

		bool processEvent( const xmlNodePtr &eventNode) const;
		bool processTransition(const xmlNodePtr &node) const;
		bool processExit(const xmlNodePtr &node) const;

		//����entry�ڵ㺯��������entry�ڵ�ָ�룬����ֵ��ʾ�Ƿ����ִ�����µ�entry�ڵ㡣
		bool processEntry(const xmlNodePtr &node)const;
		bool processSend(const xmlNodePtr &node)const;
		bool processScript(const xmlNodePtr &node)const;
		bool processTimer(const xmlNodePtr &node)const;
		bool processLog(const xmlNodePtr &node) const;
		bool processRaise(const xmlNodePtr &node)const;

		void enterStates(const xmlNodePtr &stateNode) const;
		void exitStates() const;

		Context  *  getRootContext() const; 
		xmlNodePtr getState(const string& stateId) const;
		const ::xmlNodePtr getParentState(const xmlNodePtr &currentState)const;
		xmlNodePtr getTargetStates(const xmlNodePtr &transition) const;
	private:
		std::map<std::string, SendInterface *> m_mapSendObject;
		SMInstance * m_scInstance;
		mutable helper::CLock m_lock;
	protected:
		mutable TriggerEvent m_currentEvt;
	private:
		xmlType m_xmlType;
		std::string m_strStateContent;
		mutable std::queue<TriggerEvent> m_internalQueue;
		std::queue<TriggerEvent> m_externalQueue;
		std::map<std::string,Json::Value> m_globalVars;
		bool m_running;
	public:
		virtual bool isTerminationEvent(const TriggerEvent &)const = 0;
		/****************************************************  
		@describle   Ӧ��XML Schemaģ���ļ���֤�����ĵ� 
		@param schema_filename  ģʽ�ļ�  
		@param xml           XML��ʽ�İ����ĵ� 
		@param xmlType		�����ĵ��Ǵ����ļ������ڴ��ַ�����
		@ErrorMsg		���صĴ�������
		@retval  ==0  ��֤�ɹ� 
				>0  ��֤ʧ��  
		****************************************************/  
		static int is_valid(const std::string &schema_filename, const std::string & xml, xmlType xtype, std::string &ErrorMsg);
		static void XMLCALL myXmlStructuredErrorFunc (void *userData, xmlErrorPtr error)
		{
			fprintf(stderr,"%s file'%s',line:%d\n",error->message,error->file,error->line);
			return;
		}
	};
}
#endif