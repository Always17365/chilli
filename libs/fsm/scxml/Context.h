#pragma once
#ifndef FSM_CONTEXT_HEADER_
#define FSM_CONTEXT_HEADER_
#include <map>
#include <string>
#include "libxml/tree.h"


namespace fsm{

	class Evaluator;
	class  Context
	{
	public:
		Context(Evaluator * evl, Context * _parent):evaluator(evl),parent(_parent){
		};
		virtual ~Context(void){
		};

	public:

		/// <summary>
		/// Assigns a new value to an existing variable or creates a new one.
		/// The method allows to shadow a variable of the same name up the
		/// Context chain.
		/// </summary>
		/// <param name="name"> The variable name </param>
		/// <param name="value"> The variable value </param>
		virtual void setLocal(const std::string & name, const std::string & value,bool eventVars=true) = 0;

		/// <summary>
		/// Get the Map of all variables in this Context.
		/// </summary>
		/// <returns> Local variable entries Map
		/// To get variables in parent Context, call getParent().getVars(). </returns>
		/// <seealso cref= #getParent() </seealso>
		virtual std::map<std::string,std::string> & getEventVars() = 0;

		/// <summary>
		/// Set the Map of all variables in event vars of this Context.
		/// </summary>
		virtual void SetEventVars(const std::map<std::string,std::string> &vars) = 0;
		
		/// <summary>
		/// Clear  this event vars.
		/// </summary>
		virtual void ClearEventVars() = 0;
		/// <summary>
		/// reset this Context.
		/// </summary>
		virtual void Reset() = 0;

		/// <summary>
		/// Get the parent Context, may be null.
		/// </summary>
		/// <returns> The parent Context in a chained Context environment </returns>
		virtual Context *getParent() = 0;

		///<summary>
		///����һ�νű���
		///</summary>
		///<returns>���ش˽ű�ִ���Ƿ�ɹ��Ľ����</returns>
		virtual bool CompileScript(const std::string &script,const std::string &filename, unsigned int line,void *index) = 0;

		///<summary>
		///����һ�α��ʽ�ű���
		///</summary>
		///<returns>���ش˱��ʽִ�еĽ����ת��Ϊstring���͡�</returns>
		virtual std::string eval(const std::string &expr,const std::string &filename, unsigned int line,void *index) = 0;

		///<summary>
		///����һ��boolen���ʽ�ű�
		///</summary>
		///<returns>���ش˱��ʽִ�еĽ����</returns>
		virtual bool evalCond(const std::string &expr,const std::string &filename, unsigned int line,void *index) = 0;

		///<summary>
		///����˽�����ݡ�
		///</summary>
		virtual void SetContextPrivate(void *data) = 0;

		///<summary>
		///��ȡ�����������
		///</summary>
		///<returns>���������ָ�롣</returns>
		virtual Evaluator * getEvaluator(){ return evaluator; };

		///<summary>
		///ִ��һ�νű��ļ���
		///</summary>
		virtual void ExecuteFile(const std::string &fileName) = 0;

	protected:
		Evaluator * evaluator;
		//��Context
		Context *parent;
		//�������еı���
		std::map<std::string,std::string> eventVars;
	};

}

#endif //end Context