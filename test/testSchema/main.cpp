#include <iostream>    
#include "libxml/tree.h"    
#include "libxml/parser.h"    
#include "libxml/xmlschemas.h"    
        
void XMLCALL myXmlStructuredErrorFunc (void *userData, xmlErrorPtr error)
{
	fprintf(stderr,"%s file'%s',line:%d\n",error->message,error->file,error->line);
	return;
}
/****************************************************  
    @describle   Ӧ��XML Schemaģ���ļ���֤�����ĵ� 
    @param schema_filename  ģʽ�ļ�  
    @param xmldoc           XML��ʽ�İ����ĵ� 
    @retval  ==0  ��֤�ɹ� 
            >0  ��֤ʧ��  
****************************************************/  
int is_valid(const char *schema_filename, const char *xmldoc) {  
    xmlDocPtr doc;    
    //doc = xmlReadFile(xmldoc, NULL, XML_PARSE_NONET|XML_PARSE_NOENT);  
	doc = xmlParseFile(xmldoc);
    if ( NULL == doc) {    
        fprintf(stderr, "��ȡXML�ĵ�����\n");  
        return -1;    
    }      
   
    xmlSchemaParserCtxtPtr parser_ctxt = xmlSchemaNewParserCtxt(schema_filename);  
    if (NULL == parser_ctxt) {  
		fprintf(stderr,"��ȡSchema����\n");  
        return -1;  
    }      
	
	xmlSchemaSetParserStructuredErrors(parser_ctxt,myXmlStructuredErrorFunc,stderr);

    xmlSchemaPtr schema = xmlSchemaParse(parser_ctxt);  
    if (schema == NULL) {    
        return -1;    
    }      
	xmlSchemaFreeParserCtxt(parser_ctxt);

    xmlSchemaValidCtxtPtr valid_ctxt = xmlSchemaNewValidCtxt(schema);  
    if (NULL == valid_ctxt) {  
        return -1;    
    }   

	xmlSchemaSetValidStructuredErrors(valid_ctxt,myXmlStructuredErrorFunc,stderr);
    int ret = xmlSchemaValidateDoc(valid_ctxt,doc);  
	if (ret == 0) {
		printf("%s validates\n", xmldoc);
	} else if (ret > 0) {
		printf("%s fails to validate\n", xmldoc);
	} else {
		printf("%s validation generated an internal error\n",
			xmldoc);
	}
    xmlSchemaFreeValidCtxt(valid_ctxt);  
    xmlSchemaFree(schema);  
      
    return ret;  
} 
int main(int argc, char **argv)
{
	if (argc < 3)
	{
		fprintf(stderr,"parameter error.\n"\
			"use this command schemafile xmlfile.\n");
		return -1;
	}

	return is_valid(argv[1],argv[2]);
}