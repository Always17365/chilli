#ifndef _INTERPRETERIMP_HEADER_
#define _INTERPRETERIMP_HEADER_
#include "common/xmlHelper.h"
#include <string>
#include <map>
#include <log4cplus/logger.h>
#include "scxml/TriggerEvent.h"
#include "scxml/SendInterface.h"
#include "scxml/SMInstance.h"
#include "scxml/model/Transition.h"
#include "common/lock.h"


using namespace std;


namespace fsm{

	//template class INTERPRETER_EXPORT std::map<std::string, Send *>;

	class  StateMachineimp {
	public:
		StateMachineimp(const string &xml = "", int xtype = 0);
		virtual ~StateMachineimp();

		StateMachineimp(const StateMachineimp &other) = delete;
		StateMachineimp & operator=(const StateMachineimp & other) = delete;
		
		//��ʼ��״̬��
		bool Init(void);
		bool Init(const string &xml, int xtype = 0);
		//��ʼ�����ʼ��״̬
		void go();
		//const xmlNodePtr getCurrentState(void) const;
		const std::string getCurrentStateID(void) const;

		void setName(const string &strName);
		const std::string& getName() const;

		void setSessionID(const std::string &strSessionid);
		const std::string& getSessionId()const;

		bool setVar(const std::string &name, const Json::Value &value);
		Json::Value getVar(const std::string &name) const;

		bool addSendImplement( SendInterface * evtDsp);
		void setscInstance(SMInstance *);
		void setLog(log4cplus::Logger log);

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

	private:
		void normalize(const xmlNodePtr &rootNode);
		void reset();
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
		static bool isSleep(const xmlNodePtr &Node);

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
		bool processSleep(const xmlNodePtr &node)const;

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
		int m_xmlType;
		std::string m_strStateContent;
		mutable std::queue<TriggerEvent> m_internalQueue;
		std::queue<TriggerEvent> m_externalQueue;
		std::map<std::string,Json::Value> m_globalVars;
		bool m_running;
	public:
		virtual bool isTerminationEvent(const TriggerEvent & e)const
		{
			return e.getEventName() == "stop";
		};
		/****************************************************  
		@describle   Ӧ��XML Schemaģ���ļ���֤�����ĵ� 
		@param schema_filename  ģʽ�ļ�  
		@param xml           XML��ʽ�İ����ĵ� 
		@param xmlType		�����ĵ��Ǵ����ļ������ڴ��ַ�����
		@ErrorMsg		���صĴ�������
		@retval  ==0  ��֤�ɹ� 
				>0  ��֤ʧ��  
		****************************************************/  
		static int is_valid(const std::string &schema_filename, const std::string & xml, int xtype, std::string &ErrorMsg);
		static void XMLCALL myXmlStructuredErrorFunc (void *userData, xmlErrorPtr error)
		{
			fprintf(stderr,"%s file'%s',line:%d\n",error->message,error->file,error->line);
			return;
		}
	};
}
#endif