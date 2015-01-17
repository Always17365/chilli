#pragma once
#ifndef FSM_CONTEXT_HEADER_
#define FSM_CONTEXT_HEADER_
#include <string>
#include <json/json.h>


namespace fsm{

	enum ValueContext{
		globalObject,
		eventOjbect,
	};
	class Evaluator;
	class  Context
	{
	public:
		Context(Evaluator * evl, Context * _parent):evaluator(evl),parent(_parent){
		};
		virtual ~Context(void){
		};

	public:
		///<summary>
		///��һ������������ֵ��
		///</summary>
		///<returns></returns>
		virtual void setVar(const std::string & name, const Json::Value & value, ValueContext va = globalObject) = 0;

		///<summary>
		///��ȡһ������ֵ��
		///</summary>
		///<returns>���ش˱���ֵ��</returns>
		virtual Json::Value getVar(const std::string &name, ValueContext va = globalObject) = 0;

		///<summary>
		///ɾ��һ��������
		///</summary>
		///<returns></returns>
		virtual void deleteVar(const std::string & name, ValueContext va = globalObject) = 0;

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
		virtual bool CompileScript(const std::string &script,const std::string &filename, unsigned int line,const void *index) = 0;

		///<summary>
		///����һ�α��ʽ�ű���
		///</summary>
		///<returns>���ش˱��ʽִ�еĽ����ת��Ϊstring���͡�</returns>
		virtual std::string eval(const std::string &expr,const std::string &filename, unsigned int line,const void *index) = 0;

		///<summary>
		///����һ��boolen���ʽ�ű�
		///</summary>
		///<returns>���ش˱��ʽִ�еĽ����</returns>
		virtual bool evalCond(const std::string &expr,const std::string &filename, unsigned int line,const void *index) = 0;

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
	};

}

#endif //end Context