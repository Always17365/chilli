#pragma once
#ifndef _CONTEXT_HEADER_
#define _CONTEXT_HEADER_
#include <map>
#include <string>
#include "libxml/tree.h"


namespace fsm{


	/// <summary>
	/// A Context or &quot;scope&quot; for storing variables; usually tied to
	/// a SCXML root Object.
	/// </summary>
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
		/// The method searches the chain of parent Contexts for variable
		/// existence.
		/// </summary>
		/// <param name="name"> The variable name </param>
		/// <param name="value"> The variable value </param>
		virtual void set(const std::string & name, const std::string & value) = 0;

		/// <summary>
		/// Assigns a new value to an existing variable or creates a new one.
		/// The method allows to shadow a variable of the same name up the
		/// Context chain.
		/// </summary>
		/// <param name="name"> The variable name </param>
		/// <param name="value"> The variable value </param>
		virtual void setLocal(const std::string & name, const std::string & value,bool isDelete=true) = 0;

		/// <summary>
		/// Get the value of this variable; delegating to parent.
		/// </summary>
		/// <param name="name"> The name of the variable </param>
		/// <returns> The value (or null) </returns>
		virtual std::string get(const std::string & name) = 0;

		/// <summary>
		/// Check if this variable exists, delegating to parent.
		/// </summary>
		/// <param name="name"> The name of the variable </param>
		/// <returns> Whether a variable with the name exists in this Context </returns>
		virtual bool has(const std::string & name) = 0;

		/// <summary>
		/// Get the Map of all variables in this Context.
		/// </summary>
		/// <returns> Local variable entries Map
		/// To get variables in parent Context, call getParent().getVars(). </returns>
		/// <seealso cref= #getParent() </seealso>
		virtual std::map<std::string,std::string> & getVars() = 0;

		/// <summary>
		/// Set the Map of all variables in this Context.
		/// </summary>
		virtual void setVars(const std::map<std::string,std::string> &vars) = 0;

		/// <summary>
		/// Clear this Context.
		/// </summary>
		virtual void reset() = 0;

		/// <summary>
		/// Get the parent Context, may be null.
		/// </summary>
		/// <returns> The parent Context in a chained Context environment </returns>
		virtual Context *getParent() = 0;

		///<summary>
		///����һ�νű���
		///</summary>
		///<returns>���ش˽ű�ִ���Ƿ�ɹ��Ľ����</returns>
		virtual bool CompileScript(const std::string &script,const std::string &filename, unsigned int line,void *) = 0;

		///<summary>
		///����һ�α��ʽ�ű���
		///</summary>
		///<returns>���ش˱��ʽִ�еĽ����ת��Ϊstring���͡�</returns>
		virtual std::string eval(const std::string &expr,const std::string &filename, unsigned int line,void *) = 0;

		///<summary>
		///����һ��boolen���ʽ�ű�
		///</summary>
		///<returns>���ش˱��ʽִ�еĽ����</returns>
		virtual bool evalCond(const std::string &expr,const std::string &filename, unsigned int line,void *) = 0;

		///<summary>
		///����ָ��xml�ĵ����ݵ�һ���ڵ�ָ�롣
		///</summary>
		///<returns>����ָ��xml�ĵ����ݵ�һ���ڵ�ָ�롣</returns>
		virtual xmlNodePtr evalLocation(const std::string &expr, const std::string &filename, unsigned int line,void *) = 0;

		virtual void SetContextPrivate(void *data) = 0;
		virtual Evaluator * getEvaluator(){ return evaluator; };
		virtual void ExecuteFile(const std::string &fileName) = 0;

	protected:
		Evaluator * evaluator;
		//��Context
		Context *parent;
		//�������еı���
		std::map<std::string,std::string> vars;
		std::map<void*,void*>mapObjectRoot;
	};

}

#endif //end Context