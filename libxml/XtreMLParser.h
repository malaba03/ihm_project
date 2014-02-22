

#ifndef XtreMLParserH
#define XtreMLParserH



#include "XMLUtils.h"
#include "UnicodeConvert.h"
enum XtreMLType {tXMLComment,tXMLCdata,tXMLNode,tXMLAttribut, tXMLDoctype,tXMLText,
			   tXMLProcessing} ;



#define MaxFileSize    1024*1024*20
#define XMLBufferSize  8192
#define TestLen        1024
class XtreMLObject
{

  public :

   XtreMLObject  *Prev;
   XtreMLObject  *Next;

   XtreMLObject()
   {Prev=Next=NULL;}
};

template < class T >
class XtreMLNodeStack
{
private:

   struct StackNode
   {
	  T *Value;
	  StackNode *Next;
   };

   StackNode   *Top;
   int       CountItem;

public:
   // Constructor
   XtreMLNodeStack()
	  {  Top = 0;CountItem=0; }

   // Destructor
   ~XtreMLNodeStack()
   {
		  StackNode *nodePtr, *nextNode;

	   // Position nodePtr at the top of the stack.
		 nodePtr = Top;

   // Traverse the list deleting each node.
	  while (nodePtr != 0)
	  {
		 nextNode = nodePtr->Next;
		 delete nodePtr;
		 nodePtr = nextNode;
	  }

   }

   // Stack operations
void Push( T*node )
{
   StackNode *newNode; // Pointer to a new node

   // Allocate a new node and store num there.
   newNode = new StackNode;
   newNode->Value = node;

   // If there are no nodes in the list
   // make newNode the first node.
   if (CountItem==0)
   {
	  Top = newNode;
	  newNode->Next = 0;
	  CountItem++;
   }
   else  // Otherwise, insert NewNode before Top.
   {
	  newNode->Next = Top;
	  Top = newNode;
	  CountItem++;
   }
}
T*   Pop(void)
{
	if(CountItem==0)
	  return NULL;
	else
	{
	   StackNode *Temp=Top;
	   Top=Top->Next;
	   T  *ReturnT=Temp->Value;
	   delete Temp;
	   CountItem--;
       return ReturnT;
	}
}

T     *GetFirst(void)
{
	if(CountItem==0)
	   return NULL;
	else
	 return Top->Value;
}

void Clear(void)
{
		  StackNode *nodePtr, *nextNode;

	   // Position nodePtr at the top of the stack.
		 nodePtr = Top;

   // Traverse the list deleting each node.
	  while (nodePtr != 0)
	  {
		 nextNode = nodePtr->Next;
		 delete nodePtr;
		 nodePtr = nextNode;
	  }

	  Top=NULL;

}
bool isEmpty()
{
   return (Top==NULL);
}


   int GetCount(void)
   {
	   return CountItem;
   }
};






template<typename T=XtreMLObject>
class XtreMLList :public XtreMLObject
{
   private:
			T   *Head;
			T   *Last;
			int CountItem;
   public:
		  XtreMLList():XtreMLObject()
		  {
			  Head=NULL;
			  Last=NULL;
			  CountItem=0;
		  }

		  ~XtreMLList()
		  {   }

		  void Clear(void)
		  {
			  Last=Head=NULL;
			  CountItem=0;
          }

		  T*GetFirst(void)
		  {return Head;}

		  T*GetLast(void)
		  {return Last;}

		  T*GetNext(T*xobject)
		  {
			  if(xobject!=NULL)
				return xobject->Next;
			  else xobject;
		  }

		  void Add(T*xobject)
		  {
			   if(xobject==NULL)
				 return;
				if (Head==NULL)
				{
					Head=Last=xobject;
					Head->Prev=NULL;
					Head->Next=NULL;

				}
				else
				{
					xobject->Next=NULL;
					Last->Next=xobject;
					xobject->Prev=Last;
					Last=xobject;
				}

				CountItem++;
		  }

		  void Remove(T*xobject)
		  {
				if(xobject==Head&&xobject==Last)
				{
					Head=NULL;
					Last=NULL;

				}
				else if(xobject==Head&&!(xobject==Last))
				{
					Head=(T*)Head->Next;
					Head->Prev=NULL;
				}
				else if(!(xobject==Head)&&xobject==Last)
				{
					Last=(T*)Last->Prev;
					Last->Next=NULL;
				}
				else
				{
					(xobject->Prev)->Next=xobject->Next;
					(xobject->Next)->Prev=xobject->Prev;
				}

				CountItem--;
		  }

		  void PushFront(T*xobject)
		  {
			   if(xobject==NULL)
				 return;
				if (Head==NULL)
				{
					Head=Last=xobject;
					Head->Prev=NULL;
					Head->Next=NULL;

				}
				else
				{
					Head->Prev=xobject;
					xobject->Next=Head;
					Head=xobject;

				}

				CountItem++;
		  }

		  int GetCount(void)
		  {
              return CountItem;
		  }

	bool InsertBefore(T*TargetNode,T*NodeToInsert)
	{

		if(TargetNode==Head)
		{
		   PushFront(NodeToInsert);
           return true;
		}
		T*_tmp=Head;
		while(_tmp)
		{
			if(_tmp==TargetNode)
			{
				NodeToInsert->Next=TargetNode;
				NodeToInsert->Prev=TargetNode->Prev;
				(TargetNode->Prev)->Next=NodeToInsert;
				TargetNode->Prev=NodeToInsert;
				return true;
			}
			_tmp=(T*)_tmp->Next;
		}

       return false;
	}

	bool InsertAfter(T*TargetNode,T*NodeToInsert)
	{
		if(TargetNode==Last)
        {
			Add(NodeToInsert);
			return true;
		}

		T *_tmp=Head;
		while(_tmp)
		{
			 if(_tmp==TargetNode)
			 {
				 NodeToInsert->Prev=_tmp;
				 NodeToInsert->Next=_tmp->Next;
				 (_tmp->Next)->Prev=NodeToInsert;
				 _tmp->Next=NodeToInsert;
				 return true;
             }
			_tmp=(T*)_tmp->Next;
        }
    }



};



class XtreMLDocument;
class XtreMLCDATA;
class XtreMLTEXT;
class XtreMLCOMMENT;
class XtreMLDOCTYPE;
class XtreMLPROCESSING;
class XtreMLNODE;
class XtreMLATTRIBUTE;
class XtreMLStream;

class XtreMLElement:protected XtreMLObject
{
   friend class XtreMLDocument;
   friend class XtreMLNODE;
   friend class XtreMLList<XtreMLElement>;
   protected:
			int             Deep;
			XtreMLDocument *Document;
			XtreMLNODE     *Container;
			XtreMLType      XType;
			UTF16String     *Content;
			XtreMLElement(XtreMLDocument*, XtreMLNODE*, XtreMLType);
		   ~XtreMLElement();
   public:

		   int                GetDeep(void);
		   XtreMLType         GetXMLType(void);
		   XtreMLDocument    *GetDocument(void);
		   XtreMLNODE        *GetContainer(void);
		   XtreMLElement     *GetNext(void);
		   XtreMLElement     *GetNextSibbling(void);
		   wchar_t     *GetContent(void) const ;


};



class XtreMLNODE:public XtreMLElement
{
  friend class XtreMLDocument;
  friend class XtreMLElement;
	protected:
             XtreMLNODE(XtreMLDocument*,XtreMLNODE*);
			 ~XtreMLNODE();
			 XtreMLList<XtreMLATTRIBUTE>      *AttributList;
			 XtreMLList<XtreMLElement >       *ChildList;
			 XtreMLPROCESSING                 *ProcessingAdd(void);
			 XtreMLATTRIBUTE                  *AttrAdd(void);
			 XtreMLNODE                       *NodeAdd(void);
			 XtreMLCOMMENT                    *CommentAdd(void);
			 XtreMLTEXT                       *TextAdd(void);
			 XtreMLCDATA                      *CdataAdd(void);
			 XtreMLNODE                       *FindNode(UTF16String &NodeName);
			 XtreMLNODE                       *FindNode(UTF16String&  NodeName,
														UTF16String&  AttrName,
														UTF16String&  AttrValue);
			 XtreMLATTRIBUTE                  *FindAttr(UTF16String&  AttrName);



	public:

			 int                         AttrCount(void);
			 int                         ChildCount(void);
			 wchar_t*              GetName(void) const ;
			 void                        SetName(const wchar_t*);
			 void                        SetName(const char*);
			 void                        DeleteAttr(XtreMLATTRIBUTE*);
			 void                        DeleteChild(XtreMLElement*);
			 XtreMLElement               *AddElement(XtreMLElement*Element);
			 XtreMLNODE                  *FindNode(const wchar_t*NodeName);
			 XtreMLNODE                  *FindNode(const char*NodeName);
			 XtreMLNODE                  *FindNode(const wchar_t*NodeName,
										   const wchar_t*AttrName,const wchar_t*AttrValue);
			 XtreMLNODE                  *FindNode(const char*NodeName,
										   const char*AttrName,const char*AttrValue);
			 XtreMLATTRIBUTE             *FindAttr(const char*);
			 XtreMLATTRIBUTE             *FindAttr(const wchar_t*);
			 XtreMLNODE                  *AddTree(XtreMLNODE*NodeTree);

			 XtreMLATTRIBUTE                *AttrAdd(const wchar_t*,const wchar_t*);
			 XtreMLATTRIBUTE                *AttrAdd(const char*,const char*);
			 XtreMLNODE                     *NodeAdd(const wchar_t*);
			 XtreMLNODE                     *NodeAdd(const char*);
			 XtreMLCOMMENT                  *CommentAdd(const wchar_t*);
			 XtreMLCOMMENT                  *CommentAdd(const char*);
			 XtreMLTEXT                     *TextAdd(const wchar_t*);
			 XtreMLTEXT                     *TextAdd(const char*);
			 XtreMLCDATA                    *CdataAdd(const wchar_t*);
			 XtreMLCDATA                    *CdataAdd(const char*);
			 XtreMLPROCESSING               *ProcessingAdd(const wchar_t*);
			 XtreMLPROCESSING               *ProcessingAdd(const char*);
			 XtreMLElement                  *GetFirstChild(void);
			 XtreMLElement                  *GetLastChild(void);
			 XtreMLATTRIBUTE                *GetFirstAttr(void);

};
class XtreMLCDATA:public XtreMLElement
{
   private:

			friend class XtreMLDocument;
			friend class XtreMLNODE;
			XtreMLCDATA(XtreMLDocument*doc,XtreMLNODE*Owner);
			~XtreMLCDATA();
  // virtual void
   public:

			wchar_t *GetCDATA(void ) const;
			void           SetCDATA(const wchar_t*);
			void           SetCDATA(const char*);

};
class XtreMLTEXT:public XtreMLElement
{
	private:

			  friend class XtreMLDocument;
			  friend class XtreMLNODE;
			  XtreMLTEXT(XtreMLDocument*doc,XtreMLNODE*Owner);
			  ~XtreMLTEXT();
	public:

					wchar_t *GetText(void)const;
					void     SetText(const wchar_t*);
					void     SetText(const char*);
};



class XtreMLCOMMENT:public XtreMLElement
{
	private:

			  friend class XtreMLDocument;
			  friend class XtreMLNODE;
			  XtreMLCOMMENT(XtreMLDocument*doc,XtreMLNODE*Owner);
			  ~XtreMLCOMMENT();
	public:

					wchar_t  *GetComment(void )const;
					void      SetComment(const wchar_t*);
					void      SetComment(const char*);
};

class XtreMLDOCTYPE:public XtreMLElement
{
	private:

			  friend class XtreMLDocument;
			  friend class XtreMLNODE;
			  XtreMLDOCTYPE(XtreMLDocument*doc,XtreMLNODE*Owner);
							 ~XtreMLDOCTYPE();
	public:

					wchar_t  *GetDoctype(void ) const;
					void      SetDoctype(const wchar_t*);
					void      SetDoctype(const char*);
};


class XtreMLPROCESSING:public XtreMLElement
{
	private:

			  friend class XtreMLDocument;
			  friend class XtreMLNODE;
			  XtreMLPROCESSING(XtreMLDocument*doc,XtreMLNODE*Owner);
			  ~XtreMLPROCESSING();
	public:

					wchar_t  *GetPI(void )const ;
					void      SetPI(const wchar_t*);
					void      SetPI(const char*);
};



class XtreMLATTRIBUTE:protected XtreMLObject
{
  friend class XtreMLDocument;
  friend class XtreMLNODE;
  friend class XtreMLList<XtreMLATTRIBUTE>;
	private:
			  UTF16String    *Name;
			  UTF16String    *Value;
			  XtreMLNODE     *Container;


	public:
							   XtreMLATTRIBUTE(XtreMLNODE*Owner);
							  ~XtreMLATTRIBUTE();
					wchar_t   *GetName(void) const;
					wchar_t   *GetValue(void)const;
			  XtreMLATTRIBUTE *GetNext(void);
					void       SetValue(const wchar_t*);
					void       SetName(const  wchar_t*);
					void       SetValue(const char*);
					void       SetName(const  char*);

};






class XtreMLSaveStream
{
	private:
			bool               isFile;
			char               *Buffer;
			int                BufferSize;
			char               *CourantBufferPos;

			HANDLE             SaveFile;
			EncodeFunc         WriteFunc;
			UTF16String        *UTFString;
			EncodeFunc         GetEncodeFunc(EncodeType enctype);
			void               WriteBOM(EncodeType Encode);

	public:
		DWORD              ByteLeft;
		XtreMLSaveStream();
		~XtreMLSaveStream();
		bool SaveToFile(LPCSTR FileName,EncodeType enctype,bool WithBOM);
		bool SaveToFile(LPWSTR FileName,EncodeType enctype,bool WithBOM);
		bool SaveToBuffer(char*Array,int Arraylen,
							EncodeType Enctype,bool WithBOM);

		inline bool AddToStream(UTF16String &utfstring)
		{
		  int len;
			if(CourantBufferPos==NULL)
			   return false ;
			for(int i=0;i<utfstring.Length();i++)
			{
			   if(ByteLeft>3)
			   {
				 if(WriteFunc((unsigned char*)CourantBufferPos,utfstring[i],&len)==0)
					return false;
				 CourantBufferPos+=len;
				 ByteLeft-=len;

			   }
			   else if(ByteLeft<4&&isFile)
			   {   DWORD bytewrite;
				   WriteFile(SaveFile,Buffer,XMLBufferSize-ByteLeft,
							   &bytewrite,NULL);
				   ByteLeft=XMLBufferSize;
				   CourantBufferPos=Buffer;

                   if(WriteFunc((unsigned char*)CourantBufferPos,utfstring[i],&len)==0)
					       return false;
				   CourantBufferPos+=len;
				   ByteLeft-=len;
			   }
			   else
                 return false;
			}

			return true;

		}

		inline bool AddToStream(const wchar_t*wchar)
		{
			*UTFString=wchar;
			return AddToStream(*UTFString);
		}

		void Clear(void);
		void EndStreaming(void);

};




class XtreMLReadStream
{

	private:
				DWORD             TotalSize;
				DWORD             CountByteRead;
				DWORD             BufferContentSize;
				int               CodeLen;
				DWORD             ByteBufferLeft;
				HANDLE            HFILE;
				bool              isFile;
				EncodeType        Encode;
				char              *Buffer;
				char              *CourantCharPos;
				DecodeFunc        ParserFunc;
	public:
			   XtreMLReadStream();
			   ~XtreMLReadStream();
			   bool LoadFile(LPCSTR);
			   bool LoadFile(LPWSTR);
			   bool LoadFromBuffer(char*,unsigned int len);
			   EncodeType GetEncode(void)
			   {
                   return Encode;
               }

inline bool GetNext(unsigned int*CodePoint)
{
  if(ByteBufferLeft<1)
	 return false;

  if(CountByteRead==TotalSize)
  {
	if(ParserFunc((unsigned char*)CourantCharPos,CodePoint,&CodeLen)==0)
	 {
		 if(Encode==EncUTF8)
		 {  ParserFunc=ASCIIToCodePoint;
			ParserFunc((unsigned char*)CourantCharPos,CodePoint,&CodeLen);
		 }
		 else
		  return false;
	 }
	ByteBufferLeft-=CodeLen;
	CourantCharPos+=CodeLen;
	return true;
  }
  else
  {
	  if(ByteBufferLeft>4)
	  {
			if(ParserFunc((unsigned char*)CourantCharPos,CodePoint,&CodeLen)==0)
			{
					if(Encode==EncUTF8)
					{  ParserFunc=ASCIIToCodePoint;
					   ParserFunc((unsigned char*)CourantCharPos,CodePoint,&CodeLen);
					}
					else
					{
						if(HFILE!=INVALID_HANDLE_VALUE)
						{
							CloseHandle(HFILE);
							isFile=true;
							HFILE=INVALID_HANDLE_VALUE;
                        }
						return false;
					}
			}
			ByteBufferLeft-=CodeLen;
			CourantCharPos+=CodeLen;
			return true;
	  }
	  else if(ByteBufferLeft<5&&isFile&&HFILE!=INVALID_HANDLE_VALUE)
	  {
		   for(unsigned int i=0;i<ByteBufferLeft;i++)
			   Buffer[i]=CourantCharPos[i];
		   ReadFile(HFILE,&Buffer[ByteBufferLeft],XMLBufferSize-ByteBufferLeft
													  ,&BufferContentSize,NULL);
		   CountByteRead+=BufferContentSize;
		   ByteBufferLeft+=BufferContentSize;
		   if(CountByteRead==TotalSize)
		   {
			   CloseHandle(HFILE);
			   HFILE= INVALID_HANDLE_VALUE;
           }
		   CourantCharPos=Buffer;

		   if(ParserFunc((unsigned char*)CourantCharPos,CodePoint,&CodeLen)==0)
			{
					if(Encode==EncUTF8)
					{  ParserFunc=ASCIIToCodePoint;
					   ParserFunc((unsigned char*)CourantCharPos,CodePoint,&CodeLen);
					}
					else
					{
						if(HFILE!=INVALID_HANDLE_VALUE)
						{
							CloseHandle(HFILE);
							isFile=true;
							HFILE=INVALID_HANDLE_VALUE;
                        }
						return false;
					}
			}
		   ByteBufferLeft-=CodeLen;
		   CourantCharPos+=CodeLen;
           return true;

	  }
	  else
		return false;
  }


}

};

class XtreMLDocument:protected XtreMLNODE
{
	private:

			  int                          Column;
			  int                          Line;
			  XtreMLFlow                   CourantBuffer;
			  //XtreMLList<XMLBASE>         *ChildList;
			  XtreMLNodeStack<XtreMLElement>     XMLStack;
			  XtreMLReadStream                 *StreamXML;
			  XtreMLSaveStream                 *SaveStream;
			  bool                             Indent;
			  int                              CountIndent;

			  bool           AddToStream(void);
			  bool           AddToStreamBuffer(void);
			  void           ClearChildList(void);
			  XtreMLDOCTYPE   *DoctypeAdd(void);
			  bool           Parse(void);

		   /*	  inline  bool   GetNextControlCode(unsigned int*Code)
			  {
					   if(!StreamXML->GetNext(Code))
					   {
							//ClearChildList();
							return false;
					   }
					   else return true;
			  } */

			   bool ParseElement(void);
			   bool ParseAttribute(XtreMLNODE*);


			  inline bool ParsePI(void)
			  {  unsigned int CodePoint;
				 XtreMLFlow Tempval;
				 XtreMLNODE   *node;
				 XtreMLPROCESSING *proc;
				 while(1)
				 {
					 if(!StreamXML->GetNext(&CodePoint))
						return false;
					 if(CodePoint== 62)//>
					 {
						 if(CourantBuffer[CourantBuffer.Length()-1]==63)//?
						 {
							CourantBuffer.SetLength(CourantBuffer.Length()-1);

							if(XMLStack.GetCount()==0 )
								proc=XtreMLNODE::ProcessingAdd();
							else
							  {
								  node=(XtreMLNODE*)XMLStack.GetFirst();
								  proc=node->ProcessingAdd();
							  }
							*(proc->Content)=UTF16String(CourantBuffer);
							CourantBuffer.Clear();
							return true;
						 }
					 }
					 else
						CourantBuffer.AddValue(CodePoint);
				 }

				 //return false;
			  }

			  inline bool ParseDeclaration(void)
			  {
				unsigned int CodePoint;

					XtreMLCOMMENT *com;
					XtreMLCDATA   *cdata;
					XtreMLNODE    *node;
					XtreMLDOCTYPE *doctype;
					int countbar=0;
					while(1)
					{
						if(!StreamXML->GetNext(&CodePoint))
						return false;

						CourantBuffer.AddValue(CodePoint);

						switch(CourantBuffer.Length())
						{
						  case 2:
								  if(UTF16String(CourantBuffer)==L"--" )
								  {  CourantBuffer.Clear();
									  while(1)
									  {
										if(!StreamXML->GetNext(&CodePoint))
											return false;
										if(CodePoint==62)//>
										{
										  if(CourantBuffer[CourantBuffer.Length()-1]==L'-'
											 &&CourantBuffer[CourantBuffer.Length()-2]==L'-')
										  {
											CourantBuffer.SetLength(CourantBuffer.Length()-2);
											if(XMLStack.GetCount()==0)
											  com=XtreMLNODE::CommentAdd();
											else
											{
												node=(XtreMLNODE*)XMLStack.GetFirst();
												com=node->CommentAdd();
											}
											 *(com->Content)=UTF16String(CourantBuffer);
											CourantBuffer.Clear();
											return true;

										  }
										  else CourantBuffer.AddValue(CodePoint);
										}
										else CourantBuffer.AddValue(CodePoint);
									  }

								  }

								   break;


						  case 7: if(UTF16String(CourantBuffer)==L"[CDATA[" )
								  {
                                      CourantBuffer.Clear();
									  while(1)
									  {
										 if(!StreamXML->GetNext(&CodePoint))
											return false;
										if(CodePoint==62)//>
										{

										  if(CourantBuffer[CourantBuffer.Length()-1]==L']'
											 &&CourantBuffer[CourantBuffer.Length()-2]==L']')
										  {
                                            CourantBuffer.SetLength(CourantBuffer.Length()-2);
											if(XMLStack.GetCount()==0)
											  cdata=XtreMLNODE::CdataAdd();
											else
											{
												node=(XtreMLNODE*)XMLStack.GetFirst();
												cdata=node->CdataAdd();
											}
											 *(cdata->Content)=UTF16String(CourantBuffer);
											 CourantBuffer.Clear();
											return true;
										  }else CourantBuffer.AddValue(CodePoint);
										}
										else CourantBuffer.AddValue(CodePoint);
                                      }

								  }
								  else if(UTF16String(CourantBuffer)==L"DOCTYPE" )
								  {
									  CourantBuffer.Clear();
									  while(1)
									  {
                                        if(!StreamXML->GetNext(&CodePoint))
											return false;

										if(CodePoint==62)
										{
										   if((countbar==0)||
											  (countbar>0&&CourantBuffer[CourantBuffer.Length()-1]==93))//[
										   {
											   /*if(countbar>0)
												 CourantBuffer.SetLength(CourantBuffer.Length()-1); */
											   if(XMLStack.GetCount()==0)
												  doctype=DoctypeAdd();
											   else return false;

											   *(doctype->Content)=UTF16String(CourantBuffer);
											   CourantBuffer.Clear();
											   return true;
										   }
										   else
                                              CourantBuffer.AddValue(CodePoint);
										}
										else
										{
										  CourantBuffer.AddValue(CodePoint);
										  if(CodePoint==91)
											countbar++;
										}
									  }

								  }
								  else
								   return false;
						}
					}

			  }




	public:
		 XtreMLDocument();
		 ~XtreMLDocument();
		 bool                         LoadFromFile(const LPCSTR);
		 bool                         LoadFromFile(const LPWSTR);
		 bool				          LoadFromBuffer( char*,unsigned int );
		 bool 				          SaveToFile( LPCSTR,EncodeType,bool);
		 bool 				          SaveToFile(LPWSTR,EncodeType,bool);
		 int                          SaveToBuffer(char*, unsigned int len,EncodeType,
												   bool WithBOM);

		 int                          GetDocumentSize(EncodeType);
		 int                          ChildCount(void);
		 int                          GetIndent(void);
		 void                         SetIndent(unsigned int);
		 void                         DeleteChild(XtreMLElement*);
		 XtreMLNODE                  *FindNode(const wchar_t*NodeName);
		 XtreMLNODE                  *FindNode(const char*NodeName);
		 XtreMLNODE                  *FindNode(const wchar_t*NodeName,
										   const wchar_t*AttrName,const wchar_t*AttrValue);
		 XtreMLNODE                  *FindNode(const char*NodeName,
										   const char*AttrName,const char*AttrValue);

		 XtreMLNODE                  *NodeAdd(const wchar_t*);
		 XtreMLNODE                  *NodeAdd(const char*);
		 XtreMLCOMMENT               *CommentAdd(const wchar_t*);
		 XtreMLCOMMENT               *CommentAdd(const char*);
		 XtreMLDOCTYPE               *DoctypeAdd(const wchar_t*);
		 XtreMLDOCTYPE               *DoctypeAdd(const char*);
		 XtreMLCDATA                 *CdataAdd(const wchar_t*);
		 XtreMLCDATA                 *CdataAdd(const char*);
		 XtreMLPROCESSING           *ProcessingAdd(const wchar_t*);
		 XtreMLPROCESSING           *ProcessingAdd(const char*);
		 XtreMLElement               *GetFirstChild(void);
		 XtreMLElement               *GetLastChild(void);
		 XtreMLElement               *InsertBefore(XtreMLElement* TargetElement,
												   XtreMLElement*ElementToInsert);
		 XtreMLElement               *InsertAfter(XtreMLElement*TargetElement,
												   XtreMLElement*ElementToInsert);
		 XtreMLNODE                  *InsertTreeBefore(XtreMLElement* TargetElement,
												   XtreMLNODE*NodeTreeToInsert);
		 XtreMLNODE                  *InsertTreeAfter(XtreMLElement*TargetElement,
												   XtreMLNODE*NodeTreeToInsert);
		 XtreMLNODE                  *AddTree(XtreMLNODE *NodeTree);
		 XtreMLElement               *AddElement(XtreMLElement*ElementToAdd);
		 void                         Clear(void);




};

#endif
