#if defined(_MSC_VER) && (_MSC_VER >= 1200 )
#include "Visual Studio\\XtreMLParser\\stdafx.h" //A modifier suivant le dossier ou se trouve stdafx
#pragma warning(disable:4309)
#endif
 

#include "XtreMLParser.h"




XtreMLElement:: XtreMLElement(XtreMLDocument*doc, XtreMLNODE*xmlbase,
							   XtreMLType xmltype):XtreMLObject()
{
	Document=doc;
	Container=xmlbase;
	if(xmlbase&&(xmlbase!=(XtreMLElement*)doc))
     {
		 this->Deep=xmlbase->Deep+1;
	 }
	 else
	   Deep=0;
	 XType=xmltype;
	 Content=new UTF16String();
}


XtreMLElement::~XtreMLElement()
{
	if(Content)
     delete Content;
}

int         XtreMLElement::GetDeep(void)
{
	return Deep;
}
XtreMLType      XtreMLElement::GetXMLType(void)
{
	return XType;
}
XtreMLDocument *XtreMLElement::GetDocument(void)
{
	return Document;
}

XtreMLNODE     *XtreMLElement::GetContainer(void)
{
    return Container;
}

XtreMLElement  *XtreMLElement::GetNext(void)
{
   if(Next)
	 return (XtreMLElement*)Next;
   else
   {  XtreMLNODE *node=GetContainer();
	   while(node!=(XtreMLNODE*)Document)
	   {
		  if(node->Next)
			return (XtreMLElement*)node->Next;
		  else node=node->Container;
	   }
	   return NULL;
   }
}

XtreMLElement  *XtreMLElement::GetNextSibbling(void)
{

  return (XtreMLElement*)Next;
}

 wchar_t *XtreMLElement::GetContent(void) const
{
	return Content->w_str();
}

//-------------------------------------------------------------------------------


XtreMLNODE::XtreMLNODE(XtreMLDocument*doc,XtreMLNODE*cont):XtreMLElement(doc,cont,tXMLNode)
{

  AttributList     =new XtreMLList<XtreMLATTRIBUTE>();
  ChildList        =new XtreMLList<XtreMLElement>();
}


XtreMLNODE::~XtreMLNODE()
{

	XtreMLElement    *base;
	XtreMLATTRIBUTE*attr;
	XtreMLCOMMENT *com;
	XtreMLCDATA   *cdata;
	XtreMLNODE    *node;
	XtreMLDOCTYPE *doctype;
	XtreMLTEXT    *text;
	XtreMLPROCESSING *proc;
	
   /*	XMLComment,XMLCdata,XMLNode,XMLAttribut, XMLDoctype,XMLText,
			   XMLProcessing */
	while(AttributList->GetCount()>0)
	{
		attr=AttributList->GetFirst();
		AttributList->Remove(attr);
		delete attr;
	}

	while( ChildList->GetCount()>0)
	{
	   base=ChildList->GetFirst();
	   switch(base->GetXMLType())
	   {
		   case  tXMLComment: com=(XtreMLCOMMENT*)base;
							 ChildList->Remove(com);
							 delete com;
							 break;
		   case  tXMLCdata  : cdata=(XtreMLCDATA*)base;
							 ChildList->Remove(cdata);
							 delete cdata;
							 break;
		   case tXMLNode    : node=(XtreMLNODE*)base;
							 ChildList->Remove(node);
							 delete node;
							 break;
		   case tXMLText    : text=(XtreMLTEXT*)base;
							 ChildList->Remove(text);
							 delete text;
							 break;
		   case tXMLDoctype : doctype=(XtreMLDOCTYPE*)base;
							 ChildList->Remove(doctype);
							 delete doctype;
							 break;
		   case tXMLProcessing:proc=(XtreMLPROCESSING*)base;
							  ChildList->Remove(proc);
							  delete proc;
							  break;
		   default : break;
	   }
	}

   delete AttributList;
   delete ChildList;
}
int    XtreMLNODE::AttrCount(void)
{
	return AttributList->GetCount();
}

XtreMLElement   *XtreMLNODE::GetFirstChild(void)
{
	return    ChildList->GetFirst();
}

XtreMLElement   *XtreMLNODE::GetLastChild(void)
{
    return ChildList->GetLast() ;
}

XtreMLATTRIBUTE *XtreMLNODE::GetFirstAttr(void)
{
   return  AttributList->GetFirst();
}

int    XtreMLNODE::ChildCount(void)
{
	return ChildList->GetCount();
}

 wchar_t*  XtreMLNODE::GetName(void) const
{
	return Content->w_str();
}
void   XtreMLNODE::SetName(const wchar_t*name)
{
  if(isValidName(name))
	*Content=name;
}

void XtreMLNODE::SetName(const char*name)
{
	*Content=name;

	if(!isValidName(*Content))
		Content->Clear();

}

void   XtreMLNODE::DeleteAttr(XtreMLATTRIBUTE*Attr)
{
	if(Attr->Container!=this)
	return;
	if(this==Attr->Container)
	{
	   AttributList->Remove(Attr);
	   delete Attr;
    }
}
void   XtreMLNODE::DeleteChild(XtreMLElement*base)
{
	
	XtreMLCOMMENT *com;
	XtreMLCDATA   *cdata;
	XtreMLNODE    *node;
	XtreMLDOCTYPE *doctype;
	XtreMLTEXT    *text;
	XtreMLPROCESSING *proc;
	if(base->Container!=this)
	  return;

	   switch(base->GetXMLType())
	   {
		   case  tXMLComment: com=(XtreMLCOMMENT*)base;
							 ChildList->Remove(com);
							 delete com;
							 break;
		   case  tXMLCdata  : cdata=(XtreMLCDATA*)base;
							 ChildList->Remove(cdata);
							 delete cdata;
							 break;
		   case tXMLNode    : node=(XtreMLNODE*)base;
							 ChildList->Remove(node);
							 delete node;
							 break;
		   case tXMLText    : text=(XtreMLTEXT*)base;
							 ChildList->Remove(text);
							 delete text;
							 break;
		   case tXMLDoctype : doctype=(XtreMLDOCTYPE*)base;
							 ChildList->Remove(doctype);
							 delete doctype;
							 break;
		   case tXMLProcessing:proc=(XtreMLPROCESSING*)base;
							  ChildList->Remove(proc);
							  delete proc;
							  break;
		   default : break;
	   }

}
XtreMLPROCESSING   *XtreMLNODE::ProcessingAdd(void)
{
    if(Content->Length()==0)
	  return NULL;
	 XtreMLPROCESSING *proc=new XtreMLPROCESSING(Document,this);
	 ChildList->Add(proc);
	 return proc;
}

XtreMLATTRIBUTE    *XtreMLNODE::AttrAdd(void)
{
	if(Content->Length()==0)
	  return NULL;
	 XtreMLATTRIBUTE *attr=new XtreMLATTRIBUTE(this);
	 AttributList->Add(attr);
	 return attr;
}

XtreMLNODE       *XtreMLNODE::NodeAdd(void)
{
	if(Content->Length()==0)
	  return NULL;
	XtreMLNODE*node=new XtreMLNODE(Document,this);
	ChildList->Add(node);
	return node;
}
XtreMLCOMMENT    *XtreMLNODE::CommentAdd(void)
{
	if(Content->Length()==0)
	  return NULL;
	XtreMLCOMMENT*com=new XtreMLCOMMENT(Document,this);
	ChildList->Add(com);
	return com;
}
XtreMLTEXT       *XtreMLNODE::TextAdd(void)
{
	if(Content->Length()==0)
	  return NULL;
	XtreMLTEXT*text=new XtreMLTEXT(Document,this);
	ChildList->Add(text);
	return text;
}
XtreMLCDATA      *XtreMLNODE::CdataAdd(void)
{
	if(Content->Length()==0)
	  return NULL;
	XtreMLCDATA*cdata=new XtreMLCDATA(Document,this);
	ChildList->Add(cdata);
	return cdata;
}

XtreMLATTRIBUTE   *XtreMLNODE::AttrAdd(const wchar_t*name,const wchar_t*value)
{
   XtreMLATTRIBUTE *attr=AttrAdd();
   if(!attr)
	 return NULL;
	 attr->SetName(name);
	 if(wchar_tLen(attr->GetName())==0)
	 {
		 DeleteAttr(attr);
		 return NULL;
     }
	 attr->SetValue(value);
   return attr;
}

XtreMLATTRIBUTE   *XtreMLNODE::AttrAdd(const char*name,const char*value)
{
   XtreMLATTRIBUTE *attr=AttrAdd();
   if(!attr)
	 return NULL;
	 *(attr->Name)=name;
	 if(wchar_tLen(attr->GetName())==0)
	 {
		 DeleteAttr(attr);
		 return NULL;
     }
	 attr->SetValue(value);
   return attr;
}

XtreMLNODE       *XtreMLNODE::NodeAdd(const char*name)
{
   XtreMLNODE *node=NodeAdd();
   if(!node)
	return NULL;
   *(node->Content)=name;
   if(wchar_tLen(node->GetName())==0)
   {
	   DeleteChild(node);
	   return NULL;
   }
   return node;
}

XtreMLNODE       *XtreMLNODE::NodeAdd(const wchar_t*name)
{
   XtreMLNODE *node=NodeAdd();
   if(!node)
	return NULL;
   node->SetName(name);
   if(wchar_tLen(node->GetName())==0)
   {
	   DeleteChild(node);
	   return NULL;
   }
   return node;
}

XtreMLCOMMENT    *XtreMLNODE::CommentAdd(const wchar_t*comment)
{
   XtreMLCOMMENT *com=CommentAdd();
   if(!com)
	 return NULL;
   com->SetComment(comment);
   if(wchar_tLen(com->GetComment())==0)
   {
	   DeleteChild(com);
	   return NULL;
   }
   return com;
}

XtreMLCOMMENT    *XtreMLNODE::CommentAdd(const char*comment)
{
   XtreMLCOMMENT *com=CommentAdd();
   if(!com)
	 return NULL;
   com->SetComment(comment);
   if(wchar_tLen(com->GetComment())==0)
   {
	   DeleteChild(com);
	   return NULL;
   }
   return com;
}

XtreMLTEXT       *XtreMLNODE::TextAdd(const wchar_t*text)
{
   XtreMLTEXT *xmltext=TextAdd();
   if(!xmltext)
	 return NULL;
   xmltext->SetText(text);
   if(wchar_tLen(xmltext->GetText())==0)
   {
	   DeleteChild(xmltext);
	   return NULL;
   }
   return xmltext;
}

XtreMLTEXT       *XtreMLNODE::TextAdd(const char*text)
{
   XtreMLTEXT *xmltext=TextAdd();
   if(!xmltext)
	 return NULL;
   xmltext->SetText(text);
   if(wchar_tLen(xmltext->GetText())==0)
   {
	   DeleteChild(xmltext);
	   return NULL;
   }
   return xmltext;
}


XtreMLCDATA      *XtreMLNODE::CdataAdd(const wchar_t*cdata)
{
   XtreMLCDATA* data=CdataAdd();
   if(!data)
	  return NULL;
   data->SetCDATA(cdata);
   return data;
}

XtreMLCDATA      *XtreMLNODE::CdataAdd(const char*cdata)
{
   XtreMLCDATA* data=CdataAdd();
   if(!data)
	  return NULL;
   data->SetCDATA(cdata);
   return data;
}

XtreMLPROCESSING *XtreMLNODE::ProcessingAdd(const wchar_t*procI)
{
  XtreMLPROCESSING *pinst=ProcessingAdd();
  if(!pinst)
	return NULL;
  pinst->SetPI(procI);
  return pinst;

}

XtreMLPROCESSING *XtreMLNODE::ProcessingAdd(const char*procI)
{
  XtreMLPROCESSING *pinst=ProcessingAdd();
  if(!pinst)
	return NULL;
  pinst->SetPI(procI);
  return pinst;

}

XtreMLElement     *XtreMLNODE::AddElement(XtreMLElement*ElementToInsert)
{
	XtreMLNODE *node,*nodetoadd;
	XtreMLATTRIBUTE*attr,*attradd;
	XtreMLCOMMENT *com,*comadd;
	XtreMLCDATA   *cdata,*cdataadd;
	//XtreMLDOCTYPE *doctype,*doctypeadd;
	XtreMLTEXT    *text,*textadd;
	XtreMLPROCESSING *proc,*procadd;
  try
  {
	if(!ElementToInsert)
	  return NULL;

	switch(ElementToInsert->GetXMLType())
	{
		case tXMLNode :  nodetoadd=(XtreMLNODE*)ElementToInsert;
						 node=NodeAdd();
						 *(node->Content)=*(nodetoadd->Content);
						 attradd=nodetoadd->GetFirstAttr();
						 while(attradd)
						 {
							 attr=node->AttrAdd();
							 *(attr->Name)=*(attradd->Name);
							 *(attr->Value)=*(attradd->Value);
							 attradd=attradd->GetNext();
						 }
						 return node;


		case tXMLText :  textadd=(XtreMLTEXT*)ElementToInsert;
						 text=TextAdd();
						 *(text->Content)=*(textadd->Content);
						 return text;

		case tXMLCdata : cdataadd=(XtreMLCDATA*)ElementToInsert;
						 cdata=CdataAdd();
						 *(cdata->Content)=*(cdataadd->Content);
						 return cdata;

	case tXMLProcessing: procadd=(XtreMLPROCESSING*)ElementToInsert;
						 proc=ProcessingAdd();
						 *(proc->Content)=*(procadd->Content);
						 return procadd;

		case tXMLComment:comadd=(XtreMLCOMMENT*)ElementToInsert;
						 com=CommentAdd();
						 *(com->Content)=*(comadd->Content);
						 return com;

		default         :return NULL;
	}
  }
  catch(...)
  {

  }

  return NULL;

}

XtreMLNODE     *XtreMLNODE::AddTree(XtreMLNODE*NodeTree)
{
	if(!NodeTree)
	  return NULL;
XtreMLElement  *base,*par;
XtreMLNODE  *node,*NodeToFill,*tmpnode;
XtreMLATTRIBUTE  *attr,*attrtree;
	try
	{
		 node=NodeAdd();
		 NodeToFill=node;
		 *(node->Content)=*(NodeTree->Content);
		 attrtree=NodeTree->GetFirstAttr();
		 while(attrtree)
		 {
			 attr=node->AttrAdd();
			 *(attr->Name)=*(attrtree->Name);
			 *(attr->Value)=*(attrtree->Value);
			 attrtree=attrtree->GetNext();
		 }
		 par=NodeTree->GetFirstChild();
		 while (par!=NodeTree)
		 {
			if(par->GetXMLType()==tXMLNode)
			{
			   tmpnode=node->NodeAdd();
			   *(tmpnode->Content)=*(((XtreMLNODE*)par)->Content);

			   attrtree=((XtreMLNODE*)par)->GetFirstAttr();
			   while(attrtree)
			   {
				 attr=tmpnode->AttrAdd();
				 *(attr->Name)=*(attrtree->Name);
				 *(attr->Value)=*(attrtree->Value);
				 attrtree=attrtree->GetNext();
			   }
			   if(((XtreMLNODE*)par)->ChildCount()>0)
			   {
					par=node->GetFirstChild();
					node=tmpnode;
					continue;
			   }
			 }

			 if(par->GetXMLType()==tXMLProcessing)
				node->ProcessingAdd(((XtreMLPROCESSING*)par)->GetContent());

			 if(par->GetXMLType()==tXMLText)
			   node->TextAdd(((XtreMLTEXT*)par)->GetContent());

			if(par->GetXMLType()==tXMLComment)
			  node->CommentAdd(((XtreMLCOMMENT*)par)->GetContent());

			if(par->GetXMLType()==tXMLCdata)
			  node->CdataAdd(((XtreMLCDATA*)par)->GetContent());

			if(!(par->Next==NULL))
			{
			  par=(XtreMLElement*)par->Next;
			  continue;
			}


			while(par->GetContainer()!=NULL)
			{
			   base=par->GetContainer();
			   par=(XtreMLElement*)base->Next;
			   node=node->GetContainer();
			   if(base==NodeTree)
			   {
				   par=base;
				   break;
			   }

			   if(par==NULL&&base->GetContainer())
			   {  par=base;
				  node=node->GetContainer();
				 continue;
			   }
			   else break;
			}
		 }

       return NodeToFill;
	}
	catch(...)
	{
	  return NULL;
    }

}
/*
   Les fonctions de recherche, recherche les elements suivant leur profondeur
   dans la structure XML. Ainsi un element  situé tout à la fin du document et
   ayant une profondeur de 2, sera retrouvé plus vite qu'un element se trouvant
   dans le premier noeud dont la profondeur est 5 par exemple.

*******************************************************************************/

XtreMLNODE  *XtreMLNODE::FindNode(UTF16String &NodeName)
{
  XtreMLList<XtreMLList<XtreMLElement> > nodelist;
  XtreMLElement *element;
  XtreMLList<XtreMLElement> *courantlist;

  if(ChildList->GetCount()>0)
	 nodelist.Add(ChildList);
  else
	 return NULL;

  while(nodelist.GetCount()>0)
  {         courantlist=nodelist.GetFirst();
			element=courantlist->GetFirst();
			while(element)
			{
				if(element->GetXMLType()==tXMLNode)
				{
				   if(*(((XtreMLNODE*)element)->Content)==NodeName)
					 return (XtreMLNODE*)element;
				   if(((XtreMLNODE*)element)->ChildList->GetCount()>0)
					  nodelist.Add(((XtreMLNODE*)element)->ChildList);
				}

				element=(XtreMLElement*)element->Next;
			}

	   nodelist.Remove(courantlist);
  }
  return NULL;
}

XtreMLNODE  *XtreMLNODE::FindNode(UTF16String&  NodeName,UTF16String&  AttrName,
													 UTF16String&  AttrValue)
{
  XtreMLList<XtreMLList<XtreMLElement> > nodelist;
  XtreMLElement *element;
  XtreMLATTRIBUTE  *attr;
  XtreMLList<XtreMLElement> *courantlist;

  if(ChildList->GetCount()>0)
	 nodelist.Add(ChildList);
  else
	 return NULL;

  while(nodelist.GetCount()>0)
  {         courantlist=nodelist.GetFirst();
			element=courantlist->GetFirst();
			while(element)
			{
				if(element->GetXMLType()==tXMLNode)
				{
				   if(*(((XtreMLNODE*)element)->Content)==NodeName)
				   {
					 attr=((XtreMLNODE*)element)->GetFirstAttr();
					 while(attr)
					 {
						 if(*(attr->Name)==AttrName&&
							*(attr->Value)==AttrValue)
							return (XtreMLNODE*)element;

						 attr=attr->GetNext();
					 }
				   }
				   if(((XtreMLNODE*)element)->ChildList->GetCount()>0)
					  nodelist.Add(((XtreMLNODE*)element)->ChildList);
				}

				element=(XtreMLElement*)element->Next;
			}

	   nodelist.Remove(courantlist);
  }
  return NULL;
}


XtreMLNODE  *XtreMLNODE::FindNode(const wchar_t*NodeName)
{ UTF16String temp(NodeName);
  return FindNode(temp);
}

XtreMLNODE  *XtreMLNODE::FindNode(const char*NodeName)
{ UTF16String temp(NodeName);
  return FindNode(temp);
}

XtreMLNODE  *XtreMLNODE::FindNode(const wchar_t*NodeName,
										   const wchar_t*AttrName,const wchar_t*AttrValue)
{
   UTF16String node(NodeName),attrname(AttrName),attrvalue(AttrValue);
	return FindNode(node,attrname,attrvalue);
}

XtreMLNODE  *XtreMLNODE::FindNode(const char*NodeName,
										   const char*AttrName,const char*AttrValue)
{
   UTF16String node(NodeName),
					  attrname(AttrName),
					   attrvalue(AttrValue);
	return FindNode(node,attrname,attrvalue);
}




XtreMLATTRIBUTE   *XtreMLNODE::FindAttr(UTF16String& AttrName)
{
	if(AttributList->GetCount()>0)
	{
	  XtreMLATTRIBUTE *attr=AttributList->GetFirst();
	  while(attr)
	  {
		  if(*(attr->Name)==AttrName)
			return attr;
         attr=attr->GetNext();
	  }

	}

	 return NULL;
}

XtreMLATTRIBUTE  *XtreMLNODE::FindAttr(const char*AttrName)
{
	UTF16String temp(AttrName);
	return FindAttr(temp);
}

XtreMLATTRIBUTE   *XtreMLNODE::FindAttr(const wchar_t*AttrName)
{
    UTF16String temp(AttrName);
	return FindAttr(temp);
}



//------------------------------------------------------------------------------

XtreMLCDATA::XtreMLCDATA(XtreMLDocument*doc,XtreMLNODE*Owner)
							   :XtreMLElement(doc,Owner,tXMLCdata)
{

}
XtreMLCDATA::~XtreMLCDATA()
{

}

wchar_t       *XtreMLCDATA::GetCDATA(void ) const
{
	return Content->w_str();
}

void           XtreMLCDATA::SetCDATA(const wchar_t*data)
{
   *Content=data;
}

void XtreMLCDATA::SetCDATA(const char*data)
{
	*Content=data;
}

//-----------------------------------------------------------------------------

XtreMLTEXT::XtreMLTEXT(XtreMLDocument*doc,XtreMLNODE*Owner)
	   :XtreMLElement(doc,Owner,tXMLText)
{

}

XtreMLTEXT::~XtreMLTEXT()
{

}

 wchar_t *XtreMLTEXT::GetText(void) const
{
	return Content->w_str();
}

void     XtreMLTEXT::SetText(const wchar_t*text)
{
	*Content=text;
}

void XtreMLTEXT::SetText(const char*text)
{
   *Content=text;
}

//------------------------------------------------------------------------------

XtreMLCOMMENT::XtreMLCOMMENT(XtreMLDocument*doc,XtreMLNODE*Owner)
					 :XtreMLElement(doc,Owner,tXMLComment)
{

}


XtreMLCOMMENT::~XtreMLCOMMENT()
{

}

 wchar_t  *XtreMLCOMMENT::GetComment(void ) const
{
	return Content->w_str();
}

void      XtreMLCOMMENT::SetComment(const wchar_t*comment)
{
	*Content=comment;
}

void      XtreMLCOMMENT::SetComment(const char*comment)
{
	*Content=comment;
}

//------------------------------------------------------------------------------

XtreMLDOCTYPE::XtreMLDOCTYPE(XtreMLDocument*doc,XtreMLNODE*Owner)
						:XtreMLElement(doc,Owner,tXMLDoctype)
{

}

XtreMLDOCTYPE::~XtreMLDOCTYPE()
{

}

 wchar_t  *XtreMLDOCTYPE::GetDoctype(void ) const
{
	return Content->w_str();
}

void      XtreMLDOCTYPE::SetDoctype(const wchar_t*doctype)
{
	*Content=doctype;
}

void      XtreMLDOCTYPE::SetDoctype(const char*doctype)
{
	*Content=doctype;
}
//------------------------------------------------------------------------------

XtreMLATTRIBUTE::XtreMLATTRIBUTE(XtreMLNODE*Owner)
{
   Container=Owner;
   Name= new UTF16String();
   Value= new UTF16String();

}
XtreMLATTRIBUTE::~XtreMLATTRIBUTE()
{
	if(Name)
	  delete Name;
	if(Value)
	  delete Value;
}

 wchar_t   *XtreMLATTRIBUTE::GetName(void) const
{
	return Name->w_str();
}

 wchar_t   *XtreMLATTRIBUTE::GetValue(void) const
{
	return Value->w_str();
}

void       XtreMLATTRIBUTE::SetValue(const wchar_t*value)
{
	*Value=value;
}

void       XtreMLATTRIBUTE::SetName(const wchar_t*name)
{   if(isValidName(name))
    *Name=name;
}

 XtreMLATTRIBUTE *XtreMLATTRIBUTE::GetNext(void)
 {
	 return (XtreMLATTRIBUTE*)Next;
 }

 void       XtreMLATTRIBUTE::SetValue(const char*attrvalue)
 {
	 *Value=attrvalue;
 }

 void       XtreMLATTRIBUTE::SetName(const char* attrname)
 {
	  *Name=attrname;
 }

//------------------------------------------------------------------------------

XtreMLPROCESSING::XtreMLPROCESSING(XtreMLDocument*doc,XtreMLNODE*Owner)
						:XtreMLElement(doc,Owner,tXMLProcessing)
{

}
XtreMLPROCESSING::~XtreMLPROCESSING()
{

}

 wchar_t  *XtreMLPROCESSING::GetPI(void ) const
{
	return Content->w_str();
}

void      XtreMLPROCESSING::SetPI(const wchar_t*ProcessingInstruction)
{
	*Content= ProcessingInstruction;
}

void      XtreMLPROCESSING::SetPI(const char*ProcessingInstruction)
{
	*Content=ProcessingInstruction;
}

//------------------------------------------------------------------------------

XtreMLDocument::XtreMLDocument():XtreMLNODE(NULL,NULL)
{
   Column=0;
   Line  =0;
   *Content=L"  ";
   Indent=true;
   CountIndent=3;
   Document=this;



}

XtreMLDocument::~XtreMLDocument()
{
  ClearChildList();
}

void  XtreMLDocument::ClearChildList(void)
{
	XtreMLElement*base;
	XtreMLCOMMENT *com;
	XtreMLCDATA   *cdata;
	XtreMLNODE    *node;
	XtreMLDOCTYPE *doctype;
	XtreMLTEXT    *text;
	XtreMLPROCESSING *proc;

	//wchar_t *tmp, *temp2, *temp3,*temp4, *temp5;
	while( ChildList->GetCount()>0)
	{
	   base=ChildList->GetFirst();
   /*	   if(ChildList->GetCount()==312)
		 {
			node=node=(XMLNODE*)base;
			tmp=(wchar_t*)node->GetName();
			attr=node->GetFirstAttr();
			temp2=(wchar_t*)attr->GetName();
			temp3=(wchar_t*)attr->GetValue() ;
			attr=(XMLATTRIBUT*)attr->Next;
			temp4=(wchar_t*)attr->GetName();
			temp5=(wchar_t*)attr->GetValue() ;


		 }  */
	   switch(base->GetXMLType())
	   {
		   case  tXMLComment: com=(XtreMLCOMMENT*)base;
							 ChildList->Remove(com);
							 delete com;
							 break;
		   case  tXMLCdata  : cdata=(XtreMLCDATA*)base;
							 ChildList->Remove(cdata);
							 delete cdata;
							 break;
		   case tXMLNode    : node=(XtreMLNODE*)base;
							 ChildList->Remove(node);
							 delete node;
							 break;
		   case tXMLText    : text=(XtreMLTEXT*)base;
							 ChildList->Remove(text);
							 delete text;
							 break;
		   case tXMLDoctype : doctype=(XtreMLDOCTYPE*)base;
							 ChildList->Remove(doctype);
							 delete doctype;
							 break;
		   case tXMLProcessing:proc=(XtreMLPROCESSING*)base;
							  ChildList->Remove(proc);
							  delete proc;
							  break;
		   default : break;
	   }
	}

	XMLStack.Clear();
}

XtreMLDOCTYPE  *XtreMLDocument::DoctypeAdd(void)
{
	if(Content->Length()==0)
	  return NULL;
	 XtreMLDOCTYPE *attr=new XtreMLDOCTYPE(this,this);
	 ChildList->Add(attr);
	 return attr;
}

XtreMLDOCTYPE  *XtreMLDocument::DoctypeAdd(const wchar_t* content)
{
	if(Content->Length()==0)
	  return NULL;
	 XtreMLDOCTYPE *attr=new XtreMLDOCTYPE(this,this);
	 ChildList->Add(attr);
	 *(attr->Content)=content;
	 return attr;
}

XtreMLDOCTYPE  *XtreMLDocument::DoctypeAdd(const char* content)
{
	if(Content->Length()==0)
	  return NULL;
	 XtreMLDOCTYPE *attr=new XtreMLDOCTYPE(this,this);
	 ChildList->Add(attr);
	 *(attr->Content)=content;
	 return attr;
}


bool  XtreMLDocument::Parse(void)
{
 unsigned int CodePoint,CodeType;
 int i;
 XtreMLNODE *node;
   while(1)
   {
	   if(!StreamXML->GetNext(&CodePoint))
		 break;

		 if(CourantBuffer.Length()==0)
		  if(CodePoint==32||CodePoint==13||CodePoint==10||CodePoint==9||CodePoint==0)
			 continue;

	   if(CodePoint==60) //<
	   {
		  if(CourantBuffer.Length()!=0)
			if(XMLStack.GetCount()>0)
			{ i=CourantBuffer.Length()-1;

			  while(i>0)
			  {
				  if(CourantBuffer[i]==32||CourantBuffer[i]==13||
					  CourantBuffer[i]==10)
					  i--;
				  else
				   break;
			  }

			  if(i>0)
			  {  CourantBuffer.SetLength(i+1);
				 XtreMLTEXT *text=((XtreMLNODE*)XMLStack.GetFirst())->TextAdd();
				 *(text->Content)=UTF16String(CourantBuffer);
			  }
			  CourantBuffer.Clear();
			}
			else
             CourantBuffer.Clear();

		   if(!StreamXML->GetNext(&CodePoint))   // test <
			  return false;
		   while(CodePoint==32||CodePoint==13||CodePoint==10)
		   {
			  if(!StreamXML->GetNext(&CodePoint))
				 return false;
		   }

		   CodeType=CodePoint;
		   if(!StreamXML->GetNext(&CodePoint))// parser espace et retour a ligne
			  return false;
		   while(CodePoint==32||CodePoint==13||CodePoint==10||CodePoint==9||CodePoint==0)
		   {
			  if(!StreamXML->GetNext(&CodePoint))
				 return false;
		   }


		   switch(CodeType)   // test ! ou ? ou element;
		   {
				case 63:      CourantBuffer.AddValue(CodePoint);
							  if(!ParsePI())
								 return false;
							  CourantBuffer.Clear();
							  break;

				case 33:     CourantBuffer.AddValue(CodePoint);
							 if(!ParseDeclaration())
							   return false;
							 CourantBuffer.Clear();
							  break;
				case 47:      CourantBuffer.AddValue(CodePoint);
							  if(!StreamXML->GetNext(&CodePoint))
								 return false;
							  while(!(CodePoint==32||CodePoint==13||CodePoint==10||
								   CodePoint==62))
							  {
									CourantBuffer.AddValue(CodePoint);
									if(!StreamXML->GetNext(&CodePoint))
									 return false;
							  }

							  if(CourantBuffer.Length()==0)
							   return false;
							  if(XMLStack.GetCount()==0)
								return false;
							  node=(XtreMLNODE*)XMLStack.GetFirst();
							  if(*(node->Content)==UTF16String(CourantBuffer))
								 XMLStack.Pop();
							  else return false;
                              CourantBuffer.Clear();
							 break;
				default:
						   if(isValidBeginName((wchar_t)CodeType))
						   {
							  CourantBuffer.AddValue(CodeType);
							  CourantBuffer.AddValue(CodePoint);
							   if(!ParseElement())
								 return false;
						   }
						   else
						   {
							  ClearChildList();
							   return false;
						   }

		   }
	   }
	   else if(XMLStack.GetCount()!=0&&CodePoint!=60)
	   {
			if(CodePoint==9||CodePoint==0)
               continue;
			CourantBuffer.AddValue(CodePoint);
       }
	   else
	   {
		 ClearChildList();
		 return false;
	   }
   }

   return true;
}

bool XtreMLDocument::ParseElement(void)
{
  XtreMLNODE *node;

   unsigned int CodePoint;
   if(CourantBuffer[CourantBuffer.Length()-1]==47||
		CourantBuffer[CourantBuffer.Length()-1]==62)
	{
      CodePoint=CourantBuffer[CourantBuffer.Length()-1];
	  CourantBuffer.SetLength(CourantBuffer.Length()-1) ;

	}
	else
	{
	  if(!StreamXML->GetNext(&CodePoint))
		  return false;
	}
   while(CodePoint!=32||CodePoint!=13||CodePoint!=10)
   {
	   if(CodePoint==62||CodePoint==47)
		 break;
	   if(CodePoint==32||CodePoint==13||CodePoint==10)
        break;
		 CourantBuffer.AddValue(CodePoint);
		 if(!StreamXML->GetNext(&CodePoint))
		  return false;

  /*	   if(UTF16String(CourantBuffer)==L"descrip")
	   int bfd=12; */
   }


  if(XMLStack.GetCount()==0)
	 node=XtreMLNODE::NodeAdd();
  else
	 node=((XtreMLNODE*)XMLStack.GetFirst())->NodeAdd();


	 *(node->Content)=UTF16String(CourantBuffer);
	 CourantBuffer.Clear();


  while(1)
  {

	 switch(CodePoint)
	 {    //fermeture premier  balise
		 case 62:  XMLStack.Push(node) ;
				   return true;

		 //fermeture balise simple
		 case 47:	 if(!StreamXML->GetNext(&CodePoint))
						return false;
					 while(CodePoint==32||CodePoint==13||CodePoint==10
							 ||CodePoint==9||CodePoint==0)
					 {
						 if(!StreamXML->GetNext(&CodePoint))
							return false;
					 }

					 if(CodePoint!=62)
					   return false;
					 else
					   return true;


		 default :if((CodePoint==32)||(CodePoint==13)||(CodePoint==10)
					  ||CodePoint==9||CodePoint==0)
                	break;
				   if(isValidBeginName((wchar_t)CodePoint))
					{ CourantBuffer.AddValue(CodePoint);
					  if(!ParseAttribute(node))
						return false;
					}
					else return false;
				   break;
	 }

	 if(!StreamXML->GetNext(&CodePoint))
	   return false;
	 while(CodePoint==32||CodePoint==13||CodePoint==10
		   ||CodePoint==9||CodePoint==0)
	 {
		 if(!StreamXML->GetNext(&CodePoint))
		  return false;
	 }

  }

}

bool XtreMLDocument::ParseAttribute(XtreMLNODE*Node)
{
   unsigned int CodePoint, CodeQuote;
   XtreMLFlow AttrValue;
   XtreMLATTRIBUTE *attr;

   if(!StreamXML->GetNext(&CodePoint))
	 return false;
   while(CodePoint!=32||CodePoint!=13||CodePoint!=10||CodePoint!=61)
   {
	   if(CodePoint==61)
		 break;
	   if(CodePoint==32||CodePoint==13||CodePoint==10)
		break;
		 CourantBuffer.AddValue(CodePoint);
		 if(!StreamXML->GetNext(&CodePoint))
		  return false;
   }

   if(!(CodePoint==61)) //=
	 while(!(CodePoint==61))
	 {
	   if(!StreamXML->GetNext(&CodePoint))
		 return false;
     }

	 if(!StreamXML->GetNext(&CodePoint))
		 return false;

   while(CodePoint==32||CodePoint==13||CodePoint==10
				  ||CodePoint==9||CodePoint==0)
   {
		 CourantBuffer.AddValue(CodePoint);
		 if(!StreamXML->GetNext(&CodePoint))
		  return false;

   }

   if(CodePoint==34||CodePoint==39)
	 CodeQuote=CodePoint;
   else
	 return false;

	 if(!StreamXML->GetNext(&CodePoint))
		 return false;

   while(CodePoint!=CodeQuote)
   {
		 if(CodePoint==60)
		   return false;
		 else
		   AttrValue.AddValue(CodePoint);

		 if(!StreamXML->GetNext(&CodePoint))
		  return false;


   }

   attr=Node->AttrAdd();

   *(attr->Name)= UTF16String(CourantBuffer);
   CourantBuffer.Clear();
   UTF16String ghis(AttrValue);
   *(attr->Value)=ghis;

   return true;

}

bool XtreMLDocument::LoadFromFile(LPWSTR FileName)
{

XtreMLReadStream  TempStream;
   if(ChildList->GetCount()!=0)
	  return false;
	if(!TempStream.LoadFile(FileName))
	return false;

		StreamXML=&TempStream;
		if(!Parse())
		{
			ClearChildList();
			return false;
		}
		else
		   return true;

}


bool XtreMLDocument::LoadFromFile(LPCSTR FileName)
{

XtreMLReadStream  TempStream;
  if(ChildList->GetCount()!=0)
	  return false;
   if(ChildList->GetCount()!=0)
	  return false;
	if(!TempStream.LoadFile(FileName))
	return false;

		StreamXML=&TempStream;
		if(!Parse())
		{
			ClearChildList();
			return false;
		}
		else
		   return true;

}

bool	 XtreMLDocument::LoadFromBuffer(char*buffer,unsigned int Buffer_Len)
{
  XtreMLReadStream  TempStream;
    if(ChildList->GetCount()!=0)
	  return false;

	if(!TempStream.LoadFromBuffer(buffer,Buffer_Len))
	  return false;

		StreamXML=&TempStream;
		if(!Parse())
		{
			ClearChildList();
			return false;
		}
		else return true;
}

int  XtreMLDocument::SaveToBuffer(char*buffer, unsigned int Buffer_Len,
								   EncodeType Encode,bool WithBOM)
{
  XtreMLSaveStream Save;
  if(!Save.SaveToBuffer(buffer,Buffer_Len+4,Encode,WithBOM))
	  0;
  SaveStream=&Save;
   if(!AddToStreamBuffer())
	return 0;
   else
   return Buffer_Len-Save.ByteLeft+4;

}


bool   XtreMLDocument::SaveToFile( LPCSTR FileName,EncodeType Encode,bool WithBOM)
{
   XtreMLSaveStream Save;
   if(!Save.SaveToFile(FileName,Encode,WithBOM))
	 return false;
   SaveStream=&Save;
   bool Breturn=AddToStream();
   Save.EndStreaming();
   return Breturn;
}

bool   XtreMLDocument::SaveToFile(LPWSTR FileName,EncodeType Encode,bool WithBOM)
{
   XtreMLSaveStream Save;
   if(!Save.SaveToFile(FileName,Encode,WithBOM))
	 return false;
   SaveStream=&Save;
   bool Breturn=AddToStream();
   Save.EndStreaming();
   return Breturn;
}

bool   XtreMLDocument::AddToStream(void )
{
   XtreMLElement         *base,*par;
   XtreMLNODE            *node;
   XtreMLPROCESSING      *proc;
   XtreMLATTRIBUTE       *attr;
   XtreMLTEXT            *text;
   XtreMLCOMMENT         *com;
   XtreMLCDATA           *cdata;
   XtreMLDOCTYPE         *doctype;

   base=GetFirstChild();
   par=base;
   UTF16String  string(250);
   XtreMLFlow   Flow;
   int i;
   Flow.Clear();
   while(par!=NULL&&par!=this)
   {

	  if(par->GetXMLType()==tXMLNode)
		 {
			if(Flow.Length()>0)
			  SaveStream->AddToStream(string);
			node=(XtreMLNODE*)par;
			SaveStream->AddToStream(L"<");
			SaveStream->AddToStream(*(node->Content));

			attr=node->GetFirstAttr();


			while(attr)
			{
			  
				SaveStream->AddToStream(L" ");
				SaveStream->AddToStream(*(attr->Name));
				SaveStream->AddToStream(L"=");
				SaveStream->AddToStream(L"\"");
				SaveStream->AddToStream(*(attr->Value));
				SaveStream->AddToStream(L"\"");
				attr=(XtreMLATTRIBUTE*)attr->Next;
				
			}

			if(node->ChildCount()>0)
			{
				if(node->ChildCount()==1&&
				   node->GetFirstChild()->GetXMLType()==tXMLText)
				 SaveStream->AddToStream(L">");
				else
				 SaveStream->AddToStream(L">\r\n");
				par=node->GetFirstChild();
				for(i=0;i<CountIndent;i++)
				  Flow.AddValue(32);
				string=Flow;
				continue;
			}
			else
			{
			  SaveStream->AddToStream(L"/>\r\n");
            }

		 }

		 if(par->GetXMLType()==tXMLProcessing)
		 {
		   proc=(XtreMLPROCESSING*)par;
		   if(Flow.Length()>0)
			  SaveStream->AddToStream(string);
		   SaveStream->AddToStream(L"<?");
		   SaveStream->AddToStream(*(proc->Content));
		   SaveStream->AddToStream(L"?>\r\n");

		 }

		 if(par->GetXMLType()==tXMLText)
		 { text=(XtreMLTEXT*)par;
		   if(text->GetContainer()->ChildCount()>1)
			  if(Flow.Length()>0)
				SaveStream->AddToStream(string);
		   SaveStream->AddToStream(*(text->Content));
			 if(text->GetContainer()->ChildCount()>1)
			   SaveStream->AddToStream(L"\r\n");
		 }

		 if(par->GetXMLType()==tXMLDoctype)
		 {  doctype=(XtreMLDOCTYPE*)par;
			if(Flow.Length()>0)
				SaveStream->AddToStream(string);
			SaveStream->AddToStream(L"<!DOCTYPE ");
			SaveStream->AddToStream(*(doctype->Content));
			SaveStream->AddToStream(L">\r\n");
		 }

		 if(par->GetXMLType()==tXMLComment)
		 {
			com=(XtreMLCOMMENT*)par;
			if(Flow.Length()>0)
				SaveStream->AddToStream(string);
			SaveStream->AddToStream(L"<!--");
			SaveStream->AddToStream(*(com->Content));
			SaveStream->AddToStream(L"-->\r\n");
		 }

		 if(par->GetXMLType()==tXMLCdata)
		 {
			cdata=(XtreMLCDATA*)par;
			if(Flow.Length()>0)
				SaveStream->AddToStream(string);
			SaveStream->AddToStream(L"<![CDATA[");
			SaveStream->AddToStream(*(cdata->Content));
			SaveStream->AddToStream(L"]]>\r\n") ;

		 }
		 if(!(par->Next==NULL))
		  {
			  par=(XtreMLElement*)par->Next;
			  continue;
		  }


			while(par->GetContainer()!=NULL)
			{
			  base=par->GetContainer();
			  if(base!=this)
			  {
				Flow.SetLength(Flow.Length()-CountIndent);
				string=Flow;
				node=(XtreMLNODE*)base;
				if(Flow.Length()>0)
				  if(!(node->ChildCount()==1&&
						 node->GetFirstChild()->GetXMLType()==tXMLText))
				   SaveStream->AddToStream(string);
				SaveStream->AddToStream(L"</");
				SaveStream->AddToStream(*(base->Content));
				SaveStream->AddToStream(L">\r\n");

			  }
				par=(XtreMLElement*)base->Next;

			 if(par==NULL&&base->GetContainer())
			 {  par=base; continue;
			 }
			 else break;

		   }



   }

   return true;
}


bool   XtreMLDocument::AddToStreamBuffer(void )
{
   XtreMLElement         *base,*par;
   XtreMLNODE            *node;
   XtreMLPROCESSING      *proc;
   XtreMLATTRIBUTE       *attr;
   XtreMLTEXT            *text;
   XtreMLCOMMENT         *com;
   XtreMLCDATA           *cdata;
   XtreMLDOCTYPE         *doctype;

   base=GetFirstChild();
   par=base;

   while(par!=NULL&&par!=this)
   {

	  if(par->GetXMLType()==tXMLNode)
		 {
			node=(XtreMLNODE*)par;
			SaveStream->AddToStream(L"<");
			SaveStream->AddToStream(*(node->Content));

			attr=node->GetFirstAttr();


			while(attr)
			{   SaveStream->AddToStream(L" ");
				SaveStream->AddToStream(*(attr->Name));
				SaveStream->AddToStream(L"=");
				SaveStream->AddToStream(L"\"");
				SaveStream->AddToStream(*(attr->Value));
				SaveStream->AddToStream(L"\"");
				attr=(XtreMLATTRIBUTE*)attr->Next;

			}

			if(node->ChildCount()>0)
			{

				 SaveStream->AddToStream(L">");
				par=node->GetFirstChild();

				continue;
			}
			else
			{
			  SaveStream->AddToStream(L"/>");
            }

		 }

		 if(par->GetXMLType()==tXMLProcessing)
		 {
		   proc=(XtreMLPROCESSING*)par;
		   SaveStream->AddToStream(L"<?");
		   SaveStream->AddToStream(*(proc->Content));
		   SaveStream->AddToStream(L"?>");

		 }

		 if(par->GetXMLType()==tXMLText)
		 { text=(XtreMLTEXT*)par;

		   SaveStream->AddToStream(*(text->Content));

		 }

		 if(par->GetXMLType()==tXMLDoctype)
		 {  doctype=(XtreMLDOCTYPE*)par;

			SaveStream->AddToStream(L"<!DOCTYPE ");
			SaveStream->AddToStream(*(doctype->Content));
			SaveStream->AddToStream(L">");
		 }

		 if(par->GetXMLType()==tXMLComment)
		 {
			com=(XtreMLCOMMENT*)par;

			SaveStream->AddToStream(L"<!--");
			SaveStream->AddToStream(*(com->Content));
			SaveStream->AddToStream(L"-->");
		 }

		 if(par->GetXMLType()==tXMLCdata)
		 {
			cdata=(XtreMLCDATA*)par;

			SaveStream->AddToStream(L"<![CDATA[");
			SaveStream->AddToStream(*(cdata->Content));
			SaveStream->AddToStream(L"]]>") ;

		 }
		 if(!(par->Next==NULL))
		  {
			  par=(XtreMLElement*)par->Next;
			  continue;
		  }


			while(par->GetContainer()!=NULL)
			{
			  base=par->GetContainer();
			  if(base!=this)
			  {
				node=(XtreMLNODE*)base;
				SaveStream->AddToStream(L"</");
				SaveStream->AddToStream(*(base->Content));
				SaveStream->AddToStream(L">");
			  }
				par=(XtreMLElement*)base->Next;

			 if(par==NULL&&base->GetContainer())
			 {  par=base; continue;
			 }
			 else break;

		   }



   }

   return true;
}



int  XtreMLDocument::GetDocumentSize(EncodeType Encode)
{
  int length=0;
  int charlen=EncodeCharByte(Encode);
   XtreMLElement         *base,*par;
   XtreMLNODE            *node;
   XtreMLPROCESSING      *proc;
   XtreMLATTRIBUTE       *attr;
   XtreMLTEXT            *text;
   XtreMLCOMMENT         *com;
   XtreMLCDATA           *cdata;
   XtreMLDOCTYPE         *doctype;

   base=GetFirstChild();
   par=base;

   while(par!=NULL&&par!=this)
   {
	  if(par->GetXMLType()==tXMLNode)
		 {
			node=(XtreMLNODE*)par;
			length+=charlen;
			length+=node->Content->GetUnicodeSize(Encode);
			attr=node->GetFirstAttr();
			while(attr)
			{
				length+=charlen*4;//espace,=,","
				length+=attr->Name->GetUnicodeSize(Encode);
				length+=attr->Value->GetUnicodeSize(Encode);
				attr=(XtreMLATTRIBUTE*)attr->Next;

			}

			if(node->ChildCount()>0)
			{
			    length+=charlen;
				par=node->GetFirstChild();

				continue;
			}
			else
			{
			  length+=charlen*2;
			}

		 }

		 if(par->GetXMLType()==tXMLProcessing)
		 {
		   proc=(XtreMLPROCESSING*)par;
		   length+=charlen*4;
		   length+=proc->Content->GetUnicodeSize(Encode);
		 }

		 if(par->GetXMLType()==tXMLText)
		 { text=(XtreMLTEXT*)par;
		   length+=text->Content->GetUnicodeSize(Encode);
		 }

		 if(par->GetXMLType()==tXMLDoctype)
		 {  doctype=(XtreMLDOCTYPE*)par;
			length+=charlen*11;
			length+=doctype->Content->GetUnicodeSize(Encode);
		 }

		 if(par->GetXMLType()==tXMLComment)
		 {
			com=(XtreMLCOMMENT*)par;
			length+=charlen*7;
			length+=com->Content->GetUnicodeSize(Encode);
		 }

		 if(par->GetXMLType()==tXMLCdata)
		 {
			cdata=(XtreMLCDATA*)par;
			length+=charlen*12;
			length+=cdata->Content->GetUnicodeSize(Encode);

		 }
		 if(!(par->Next==NULL))
		  {
			  par=(XtreMLElement*)par->Next;
			  continue;
		  }


			while(par->GetContainer()!=NULL)
			{
			  base=par->GetContainer();
			  if(base!=this)
			  {
				node=(XtreMLNODE*)base;
				length+=charlen*3;
				length+=base->Content->GetUnicodeSize(Encode);
			  }
				par=(XtreMLElement*)base->Next;

			 if(par==NULL&&base->GetContainer())
			 {  par=base; continue;
			 }
			 else break;

		   }



   }
   //return la taille du document, plus l'espace nécessaire à l'écriture du BOM
   //
   return length+4;

}
int                XtreMLDocument::ChildCount(void)
{
	return XtreMLNODE::ChildCount();
}
void               XtreMLDocument::DeleteChild(XtreMLElement*Element)
{
	XtreMLNODE::DeleteChild(Element);
}

void XtreMLDocument::SetIndent(unsigned int indent)
{
	CountIndent=indent;
}

int XtreMLDocument::GetIndent(void)
{
	return CountIndent;
}

XtreMLNODE        *XtreMLDocument::FindNode(const wchar_t*NodeName)
{
   return XtreMLNODE::FindNode(NodeName);
}

XtreMLNODE        *XtreMLDocument::FindNode(const char*NodeName)
{
	return XtreMLNODE::FindNode(NodeName);
}

XtreMLNODE        *XtreMLDocument::FindNode(const wchar_t*NodeName,
										   const wchar_t*AttrName,const wchar_t*AttrValue)
{
	return XtreMLNODE::FindNode(NodeName,AttrName,AttrValue);
}

XtreMLNODE        *XtreMLDocument::FindNode(const char*NodeName,
										   const char*AttrName,const char*AttrValue)
{
  return XtreMLNODE::FindNode(NodeName,AttrName,AttrValue);
}

XtreMLNODE        *XtreMLDocument::NodeAdd(const wchar_t*NodeName)
{
	return XtreMLNODE::NodeAdd(NodeName);
}

XtreMLNODE        *XtreMLDocument::NodeAdd(const char*NodeName)
{
	return XtreMLNODE::NodeAdd(NodeName);
}

XtreMLCOMMENT     *XtreMLDocument::CommentAdd(const wchar_t*Content)
{
	return XtreMLNODE::CommentAdd(Content);
}

XtreMLCOMMENT     *XtreMLDocument::CommentAdd(const char*Content)
{
	return XtreMLNODE::CommentAdd(Content);
}

XtreMLCDATA       *XtreMLDocument::CdataAdd(const wchar_t*Content)
{
	return XtreMLNODE::CdataAdd( Content);
}

XtreMLCDATA       *XtreMLDocument::CdataAdd(const char*Content)
{
	return XtreMLNODE::CdataAdd( Content);
}

XtreMLPROCESSING   *XtreMLDocument::ProcessingAdd(const wchar_t*Content)
{
	return XtreMLNODE::ProcessingAdd(Content);
}

XtreMLPROCESSING   *XtreMLDocument::ProcessingAdd(const char*Content)
{
	return XtreMLNODE::ProcessingAdd(Content);
}

XtreMLElement     *XtreMLDocument::AddElement(XtreMLElement*ElementToAdd)
{
    return XtreMLNODE::AddElement(ElementToAdd);
}

XtreMLElement     *XtreMLDocument::GetFirstChild(void)
{
	return XtreMLNODE::GetFirstChild();
}

 XtreMLElement    *XtreMLDocument::GetLastChild(void)
 {
	 return XtreMLNODE::GetLastChild();
 }

void     XtreMLDocument::Clear(void)
{
    ClearChildList();
}

XtreMLElement     *XtreMLDocument::InsertBefore(XtreMLElement* TargetElement,
												   XtreMLElement*ElementToInsert)
{
	XtreMLNODE *node,*nodetoadd,*parentnode;
	XtreMLATTRIBUTE*attr,*attradd;
	XtreMLCOMMENT *com,*comadd;
	XtreMLCDATA   *cdata,*cdataadd;
	XtreMLDOCTYPE *doctype,*doctypeadd;
	XtreMLTEXT    *text,*textadd;
	XtreMLPROCESSING *proc,*procadd;
  try
  {
	if(!ElementToInsert||!TargetElement||TargetElement->Document!=this)
	  return NULL;
	 parentnode=TargetElement->GetContainer();
	switch(ElementToInsert->GetXMLType())
	{
		case tXMLNode :  nodetoadd=(XtreMLNODE*)ElementToInsert;
						 node=parentnode->NodeAdd();
						 *(node->Content)=*(nodetoadd->Content);
						 attradd=nodetoadd->GetFirstAttr();
						 while(attradd)
						 {
							 attr=node->AttrAdd();
							 *(attr->Name)=*(attradd->Name);
							 *(attr->Value)=*(attradd->Value);
							 attradd=attradd->GetNext();
						 }

						 parentnode->ChildList->Remove(node);
						 parentnode->ChildList->InsertBefore(TargetElement,node);
						 return node;


		case tXMLText :  textadd=(XtreMLTEXT*)ElementToInsert;
						 text=parentnode->TextAdd();
						 *(text->Content)=*(textadd->Content);
						 parentnode->ChildList->Remove(text);
						 parentnode->ChildList->InsertBefore(TargetElement,text);
						 return text;

		case tXMLDoctype:doctypeadd=(XtreMLDOCTYPE*)ElementToInsert;
						 doctype=DoctypeAdd();
						 *(doctype->Content)=*(doctypeadd->Content);
						 parentnode->ChildList->Remove(doctype);
						 parentnode->ChildList->InsertBefore(TargetElement,doctype);
						 return doctype;

		case tXMLCdata : cdataadd=(XtreMLCDATA*)ElementToInsert;
						 cdata=parentnode->CdataAdd();
						 *(cdata->Content)=*(cdataadd->Content);
						 parentnode->ChildList->Remove(cdata);
						 parentnode->ChildList->InsertBefore(TargetElement,cdata);
						 return cdata;

	case tXMLProcessing: procadd=(XtreMLPROCESSING*)ElementToInsert;
						 proc=parentnode->ProcessingAdd();
						 *(proc->Content)=*(procadd->Content);
						 parentnode->ChildList->Remove(proc);
						 parentnode->ChildList->InsertBefore(TargetElement,proc);
						 return procadd;

		case tXMLComment:comadd=(XtreMLCOMMENT*)ElementToInsert;
						 com=parentnode->CommentAdd();
						 *(com->Content)=*(comadd->Content);
						 parentnode->ChildList->Remove(com);
						 parentnode->ChildList->InsertBefore(TargetElement,com);
						 return com;

		default         :return NULL;
	}
  }
  catch(...)
  {

  }

  return NULL;

}

XtreMLElement     *XtreMLDocument::InsertAfter(XtreMLElement*TargetElement,
												   XtreMLElement*ElementToInsert)
{
	XtreMLNODE *node,*nodetoadd,*parentnode;
	XtreMLATTRIBUTE*attr,*attradd;
	XtreMLCOMMENT *com,*comadd;
	XtreMLCDATA   *cdata,*cdataadd;
	XtreMLDOCTYPE *doctype,*doctypeadd;
	XtreMLTEXT    *text,*textadd;
	XtreMLPROCESSING *proc,*procadd;
  try
  {
	if(!ElementToInsert||!TargetElement||TargetElement->Document!=this)
	  return NULL;
	 parentnode=TargetElement->GetContainer();
	switch(ElementToInsert->GetXMLType())
	{
		case tXMLNode :  nodetoadd=(XtreMLNODE*)ElementToInsert;
						 node=parentnode->NodeAdd();
						 *(node->Content)=*(nodetoadd->Content);
						 attradd=nodetoadd->GetFirstAttr();
						 while(attradd)
						 {
							 attr=node->AttrAdd();
							 *(attr->Name)=*(attradd->Name);
							 *(attr->Value)=*(attradd->Value);
							 attradd=attradd->GetNext();
						 }

						 parentnode->ChildList->Remove(node);
						 parentnode->ChildList->InsertAfter(TargetElement,node);
						 return node;


		case tXMLText :  textadd=(XtreMLTEXT*)ElementToInsert;
						 text=parentnode->TextAdd();
						 *(text->Content)=*(textadd->Content);
						 parentnode->ChildList->Remove(text);
						 parentnode->ChildList->InsertAfter(TargetElement,text);
						 return text;

		case tXMLDoctype:doctypeadd=(XtreMLDOCTYPE*)ElementToInsert;
						 if(parentnode!=this)
                            return NULL;
						 doctype=DoctypeAdd();
						 *(doctype->Content)=*(doctypeadd->Content);
						 parentnode->ChildList->Remove(doctype);
						 parentnode->ChildList->InsertAfter(TargetElement,doctype);
						 return doctype;

		case tXMLCdata : cdataadd=(XtreMLCDATA*)ElementToInsert;
						 cdata=parentnode->CdataAdd();
						 *(cdata->Content)=*(cdataadd->Content);
						 parentnode->ChildList->Remove(cdata);
						 parentnode->ChildList->InsertAfter(TargetElement,cdata);
						 return cdata;

	case tXMLProcessing: procadd=(XtreMLPROCESSING*)ElementToInsert;
						 proc=parentnode->ProcessingAdd();
						 *(proc->Content)=*(procadd->Content);
						 parentnode->ChildList->Remove(proc);
						 parentnode->ChildList->InsertAfter(TargetElement,proc);
						 return procadd;

		case tXMLComment:comadd=(XtreMLCOMMENT*)ElementToInsert;
						 com=parentnode->CommentAdd();
						 *(com->Content)=*(comadd->Content);
						 parentnode->ChildList->Remove(com);
						 parentnode->ChildList->InsertAfter(TargetElement,com);
						 return com;

		default         :return NULL;
	}
  }
  catch(...)
  {

  }

  return NULL;
}


XtreMLNODE   *XtreMLDocument::InsertTreeBefore(XtreMLElement*TargetElement,
												   XtreMLNODE*NodeTreeToInsert)
{
  XtreMLNODE*node,*returnnode;
	if(!NodeTreeToInsert||!TargetElement||TargetElement->Document!=this)
	  return NULL;
	node=TargetElement->GetContainer();
	if((returnnode=node->AddTree(NodeTreeToInsert))==NULL)
		return NULL;
	node->ChildList->Remove(returnnode);
	node->ChildList->InsertBefore(TargetElement,returnnode);
	return returnnode;

}

XtreMLNODE   *XtreMLDocument::InsertTreeAfter(XtreMLElement*TargetElement,
												   XtreMLNODE*NodeTreeToInsert)
{
   XtreMLNODE*node,*returnnode;
	if(!NodeTreeToInsert||!TargetElement||TargetElement->Document!=this)
	  return NULL;
	node=TargetElement->GetContainer();
	if((returnnode=node->AddTree(NodeTreeToInsert))==NULL)
		return NULL;
	node->ChildList->Remove(returnnode);
	node->ChildList->InsertAfter(TargetElement,returnnode);
	return returnnode;
}



//------------------------------------------------------------------------------

XtreMLReadStream::XtreMLReadStream()
{
	TotalSize=0;
	CountByteRead=0;
	ByteBufferLeft=0;
	Buffer=new char[XMLBufferSize];
	HFILE=INVALID_HANDLE_VALUE;
	isFile=false;
	CourantCharPos=NULL;
	Encode=EncUNKNOWN;
}
XtreMLReadStream::~XtreMLReadStream()
{
	if(HFILE!=INVALID_HANDLE_VALUE)
	  CloseHandle(HFILE);
	if(isFile)
	 delete[] Buffer;
}

bool XtreMLReadStream::LoadFromBuffer(char*Array,unsigned int len)
{
   CountByteRead=TotalSize=len;
   Buffer=Array;
   BufferContentSize=len;
   ParserFunc=DetectEncode((unsigned char*)Buffer,Min((int)BufferContentSize,TestLen), Encode,&CourantCharPos);
   if(Encode==EncUNKNOWN)
	   return false;

   ByteBufferLeft=BufferContentSize-((int)CourantCharPos-(int)(Buffer));
   isFile=false;
  return true;
}

bool XtreMLReadStream::LoadFile(LPWSTR FileName)
{

  if(HFILE!=INVALID_HANDLE_VALUE)
	 return false;

   HFILE=CreateFileW(FileName, GENERIC_READ, 0,  0, OPEN_EXISTING,
					FILE_ATTRIBUTE_READONLY,0);
   if(HFILE==INVALID_HANDLE_VALUE)
			return false;
   TotalSize=GetFileSize(HFILE,&BufferContentSize);
   if(TotalSize>MaxFileSize||TotalSize<4)
   {
	   CloseHandle(HFILE);
	   HFILE=INVALID_HANDLE_VALUE;
	   return false;
   }

   ReadFile(HFILE,Buffer,XMLBufferSize,&BufferContentSize,NULL);
   CountByteRead+=BufferContentSize;
   ParserFunc=DetectEncode((unsigned char*)Buffer,Min((int)BufferContentSize,TestLen), Encode,&CourantCharPos);
   if(Encode==EncUNKNOWN)
   {
	   CloseHandle(HFILE);
	   HFILE=INVALID_HANDLE_VALUE;
	   isFile=false;
	   return false;
   }

   ByteBufferLeft=BufferContentSize-((int)CourantCharPos-(int)(Buffer));
   isFile=true;
   if( CountByteRead==TotalSize)
	{
	  CloseHandle(HFILE);
	  HFILE=INVALID_HANDLE_VALUE;
	  isFile=false;
	}

   return true;

}

bool XtreMLReadStream::LoadFile(LPCSTR FileName)
{

  if(HFILE!=INVALID_HANDLE_VALUE)
	 return false;

   HFILE=CreateFileA(FileName, GENERIC_READ, 0,  0, OPEN_EXISTING,
					FILE_ATTRIBUTE_READONLY,0);
   if(HFILE==INVALID_HANDLE_VALUE)
			return false;
   TotalSize=GetFileSize(HFILE,&BufferContentSize);
   if(TotalSize>MaxFileSize||TotalSize<4)
   {
	   CloseHandle(HFILE);
	   HFILE=INVALID_HANDLE_VALUE;
	   return false;
   }

   ReadFile(HFILE,Buffer,XMLBufferSize,&BufferContentSize,NULL);
   CountByteRead+=BufferContentSize;
   ParserFunc=DetectEncode((unsigned char*)Buffer,Min((int)BufferContentSize,TestLen), Encode,&CourantCharPos);
   if(Encode==EncUNKNOWN)
   {
	   CloseHandle(HFILE);
	   HFILE=INVALID_HANDLE_VALUE;
	   isFile=false;
	   return false;
   }

   ByteBufferLeft=BufferContentSize-((int)CourantCharPos-(int)(Buffer));
   isFile=true;
   if( CountByteRead==TotalSize)
	{
	  CloseHandle(HFILE);
	  HFILE=INVALID_HANDLE_VALUE;
	  isFile=false;
	}

   return true;

}

//******************************************************************************

XtreMLSaveStream::XtreMLSaveStream()
{
	isFile=false;
	Buffer=NULL;
	ByteLeft=0;
	CourantBufferPos=NULL;
	UTFString=new UTF16String(50);
	SaveFile=INVALID_HANDLE_VALUE;
}


XtreMLSaveStream::~XtreMLSaveStream()
{
  if(isFile)
	if(Buffer)
	 delete[] Buffer;
	if(SaveFile!=INVALID_HANDLE_VALUE)
	  CloseHandle(SaveFile);
	delete UTFString;
}

EncodeFunc  XtreMLSaveStream::GetEncodeFunc(EncodeType Enctype)
{
	switch(Enctype)
	{
		case  EncUTF8    : return  CodePointToUTF8;
		case  EncUTF16BE : return  CodePointToUTF16_BE;
		case  EncUTF16LE : return  CodePointToUTF16_LE;
		case  EncUTF32BE : return  CodePointToUTF32_BE;
		case  EncUTF32LE : return  CodePointToUTF32_LE;
		default          : return  CodePointToASCII;
	}
}

bool XtreMLSaveStream::SaveToFile(LPCSTR FileName,EncodeType Enctype,bool WithBOM)
{
   if(SaveFile!=INVALID_HANDLE_VALUE||CourantBufferPos!=NULL)
	 return false;

	SaveFile=CreateFileA(FileName, GENERIC_READ | GENERIC_WRITE, 0,  0,
						CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
   if(SaveFile==INVALID_HANDLE_VALUE)
	  return false;

   Buffer=new char[XMLBufferSize];
   CourantBufferPos=Buffer;
   ByteLeft=XMLBufferSize;
   WriteFunc=GetEncodeFunc(Enctype);
   isFile=true;
   if(WithBOM)
	WriteBOM(Enctype);

   return true;

}

bool XtreMLSaveStream::SaveToFile(LPWSTR FileName,EncodeType Enctype,bool WithBOM)
{
   if(SaveFile!=INVALID_HANDLE_VALUE||CourantBufferPos!=NULL)
	 return false;

	SaveFile=CreateFileW(FileName, GENERIC_READ | GENERIC_WRITE, 0,  0,
						CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
   if(SaveFile==INVALID_HANDLE_VALUE)
	  return false;

   Buffer=new char[XMLBufferSize];
   CourantBufferPos=Buffer;
   ByteLeft=XMLBufferSize;
   WriteFunc=GetEncodeFunc(Enctype);
   isFile=true;
   if(WithBOM)
	WriteBOM(Enctype);

   return true;

}

bool XtreMLSaveStream::SaveToBuffer(char*Array,int Arraylen,EncodeType Enctype,bool WithBOM)
{
  if(Arraylen<4)
    return false;
   Buffer=Array;
   CourantBufferPos=Buffer;
   ByteLeft=Arraylen;
   WriteFunc=GetEncodeFunc(Enctype);
   isFile=false;
   if(WithBOM)
	 WriteBOM(Enctype);

   return true;
}

void XtreMLSaveStream::WriteBOM(EncodeType Encode)
{
	switch(Encode)
	{
		case EncUTF8:Buffer[0]=0xEF;
					 Buffer[1]=0xBB ;
					 Buffer[2]=0xBF;
					 CourantBufferPos+=3;
					 ByteLeft-=3;
					 return;
		case EncUTF16BE :Buffer[0]=0xFE;
						 Buffer[1]=0xFF ;
						 CourantBufferPos+=2;
						 ByteLeft-=2;
						 return;
		case EncUTF16LE :Buffer[0]=0xFF;
						 Buffer[1]=0xFE ;
						 CourantBufferPos+=2;
						 ByteLeft-=2;
						 return;

		case EncUTF32BE :Buffer[0]=0x00;
						 Buffer[1]=0x00 ;
						 Buffer[2]=0xFE;
						 Buffer[3]=0xFF ;
						 CourantBufferPos+=4;
						 ByteLeft-=4;
						 return;
		case EncUTF32LE :Buffer[0]=0xFF;
						 Buffer[1]=0xFE ;
						 Buffer[2]=0x00;
						 Buffer[3]=0x00 ;
						 CourantBufferPos+=4;
						 ByteLeft-=4;
						 return;
		default :    return;

    }
}

void XtreMLSaveStream::Clear(void)
{
	if(Buffer)
	  delete[] Buffer;
	if(SaveFile!=INVALID_HANDLE_VALUE)
	  CloseHandle(SaveFile);
	isFile=false;
	Buffer=NULL;
	ByteLeft=0;
	CourantBufferPos=NULL;
	SaveFile=INVALID_HANDLE_VALUE;
}



void XtreMLSaveStream::EndStreaming(void)
{
	if(isFile)
	{  DWORD bytewrite;
	   WriteFile(SaveFile,Buffer,XMLBufferSize-ByteLeft,&bytewrite,NULL);
	}

	if(Buffer)
	  delete[] Buffer;
	if(SaveFile!=INVALID_HANDLE_VALUE)
	  CloseHandle(SaveFile);
	isFile=false;
	Buffer=NULL;
	ByteLeft=0;
	CourantBufferPos=NULL;
	SaveFile=INVALID_HANDLE_VALUE;
}


