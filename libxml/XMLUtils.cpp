#if defined(_MSC_VER) && (_MSC_VER >= 1200 )
   #include "Visual Studio\\XtreMLParser\\stdafx.h" //A modifier suivant le dossier ou se trouve stdafx
#endif

#include "XMLUtils.h"





			   //        0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
int     ValidUTFCode[]= {1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 1 , 0 , 0, //0x  X
						 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, //1x  X
						 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1, //2x  X
						 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1, //3x  X
						 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1, //4x  X
						 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1, //5x  X
						 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1, //6x  X
						 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 //7x  X
						 } ;

int ValidBeginName  []= {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, //0x  X
						 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, //1x  X
						 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, //2x  X
						 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, //3x  X
						 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1, //4x  X
						 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0, //5x  X
						 0 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1, //6x  X
						 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 //7x  X
						 } ;

bool  isValidCode(unsigned int CodePoint)
{

	if(CodePoint<0x7F)
	 if( ValidUTFCode[CodePoint]==1)
	   return true;
	  else return false;

	 return true;

}

bool isValidBeginName(wchar_t begin)
{
   if((int)begin<0x7F)
	return (ValidBeginName[(int)begin]==1);
   else return true;
}





/*******************************************************************************
*                  DEBUT                                                       *
*              IMPLEMENTATION XMLFlow                                          *
*                                                                              *
*******************************************************************************/

XtreMLFlow::XtreMLFlow()
{
	Capacity=CharValueCapacity;
	Buffer=new unsigned int[Capacity];
	CountItem=0;
}

XtreMLFlow::XtreMLFlow(unsigned int cap)
{
	Capacity=cap;
	CountItem=0;
	Buffer=new unsigned int[Capacity];
}

XtreMLFlow::XtreMLFlow(const XtreMLFlow& ChValue)
{
	this->Capacity=ChValue.Capacity;
	this->CountItem=ChValue.CountItem;
	Buffer=new unsigned int[Capacity];
	for(unsigned int i=0;i<this->CountItem;i++)
	this->Buffer[i]=ChValue.Buffer[i];
}

XtreMLFlow::~XtreMLFlow()
{
	if(Buffer)
	   delete[] Buffer;
}

void XtreMLFlow::SetLength(int length)
{
	if(length>-1&&(unsigned int)length<CountItem)
	{
	   CountItem=length;
	}
}

XtreMLFlow		 &XtreMLFlow::operator=( const XtreMLFlow &ChValue)
{
	if(&ChValue==this)
	   return *this;
	if(this->Capacity<ChValue.CountItem)
	{  XtreMLFlow Temp(*this);
	   delete[] this->Buffer;
	   this->Buffer=new unsigned int[ChValue.Capacity];
	   this->Capacity=ChValue.Capacity;
	   if(this->Buffer)
		  for(unsigned int i=0;i<ChValue.CountItem;i++)
			this->Buffer[i]=ChValue.Buffer[i];

	}
	else
	   for(unsigned int i=0;i<ChValue.CountItem;i++)
		 this->Buffer[i]=ChValue.Buffer[i];

			 this->CountItem=ChValue.CountItem;
            return *this;
}

bool XtreMLFlow::operator==(const XtreMLFlow &ChValue)const
{
	if(&ChValue==this)
	   return true;

	if(this->CountItem!=ChValue.CountItem)
	   return false;

	for(unsigned int i=0;i<this->CountItem;i++)
	   if(this->Buffer[i]!=ChValue.Buffer[i])
		  return false;

	return true;
}




XtreMLFlow &XtreMLFlow::operator+=(const XtreMLFlow  &ChValue)
{
   if(&ChValue!=this)
   {
	   if(ChValue.CountItem>(this->Capacity-this->CountItem))
	   {  XtreMLFlow Temp(*this);
		  this->Capacity+=ChValue.Capacity;
		  delete[] this->Buffer;
		  this->Buffer=new unsigned int[this->Capacity];
		  *this=ChValue;
	   }

	   if(this->Buffer)
	   {
		  for(unsigned int i=0;i<ChValue.CountItem;i++)
			 this->Buffer[this->CountItem+i]=ChValue.Buffer[i];
		  this->CountItem+=ChValue.CountItem;
	   }

	   return *this;
   }
   else
   { XtreMLFlow Temp(ChValue);
	  return *this+=Temp;
   }
}

int XtreMLFlow::operator[](unsigned int Index)const
{
	if(Index<this->CountItem)
	   return this->Buffer[Index];
	else return 0;
}


int XtreMLFlow::Length(void)
{
	return CountItem;
}

void XtreMLFlow::Clear(void)
{
	if(Capacity>CharValueCapacity)
	{ delete[] Buffer;
		Buffer=new unsigned int[Capacity=CharValueCapacity];
	}
	CountItem=0;
}

int XtreMLFlow::GetUTF8Size(void)
{
	int len=0;
	for(unsigned int i=0;i<CountItem;i++)
	{
	   if(Buffer[i]<0x80)
		  len+=1;
	   else if(Buffer[i]<0x1000)
		  len+=2;
	   else if(Buffer[i]<0x10000)
		  len+=3;
	   else if(Buffer[i]<0x11000)
		  len+=4;
	   else
		  return 0;
	}
	return len;
}

int XtreMLFlow::GetUTF16Size(void)
{
	int len=0;
	for(unsigned int i=0;i<CountItem;i++)
	{
	  if(Buffer[i]<=0xD7FF||((Buffer[i]>=0xE000)&&(Buffer[i]<=0xFFFD)))
		 len+=2;
	  else if( Buffer[i]>=0x10000 && Buffer[i]<=0x10FFFF)
		 len+=4;
	  else
		 return 0;

	}
	return len;
}

int XtreMLFlow::GetUTF32Size(void)
{
	return CountItem*4;
}
void XtreMLFlow::WriteToUTF16BE(UTF16*OutChar)
{
   try
   { 
	 for(unsigned int i=0;i<CountItem;i++)
	 {
		OutChar[i]=Buffer[i];
	 }

   }
   catch(...)
   {

   }
}
void XtreMLFlow::WriteToUTF8(char*)
{

}

void XtreMLFlow::WriteToUTF32(char*)
{

}

void XtreMLFlow::AddValue(unsigned int value)
{
	if(CountItem<Capacity)
	   Buffer[CountItem++]=value;
	else
	{   XtreMLFlow Temp(*this);
		Capacity*=2;
		delete[] this->Buffer;
		this->Buffer=new unsigned int[Capacity];
		if(Buffer)
		{
		   *this=Temp;
		   this->Buffer[CountItem++]=value;
		}
		else
		   CountItem=0;
	}

}

/*******************************************************************************
*                  Debut                                                       *
*              IMPLEMENTATION UTF16String                                      *
*                                                                              *
*******************************************************************************/

UTF16String::UTF16String()
{
		   CountItem=0;
		   Capacity;
		   Buffer= NULL;
}

UTF16String::UTF16String(unsigned int capacity)
{
	CountItem=0;
	Capacity=capacity;
	Buffer=Buffer=new UTF16[this->Capacity];
}

UTF16String::UTF16String(const UTF16String &utfstring )
{
			if(utfstring.CountItem==0)
			{
			  this->CountItem=0;
			  this->Capacity=0;
			  this->Buffer=NULL;
			  return;
			}
		  this->CountItem=utfstring.CountItem;
		  this->Capacity=this->CountItem+1;
		  Buffer=new UTF16[this->Capacity];
		  for(unsigned int i=0;i<utfstring.CountItem+1;i++)
			this->Buffer[i]=utfstring.Buffer[i];
}

UTF16String::UTF16String(const  char    *CharToClone)
{
	this->Capacity=0;
	this->Buffer=NULL;
	this->CountItem=0;
	try
	{
	   XtreMLFlow  temp;
	   int i=0;
	   while(CharToClone[i]!='\0')
	   temp.AddValue((unsigned int)((unsigned char)CharToClone[i++]));

	   *this=temp;
	}
	catch(...)
	{

    }

}

UTF16String::UTF16String(const wchar_t *Copychar)
{
		   unsigned int len=wchar_tLen(Copychar);
		   if(len==0)
			{
			  CountItem=0;
			  Capacity=0;
			  Buffer=NULL;
			  return;
			}

		  CountItem=len;
		  Capacity=len;
		   Buffer=new UTF16[len+1];
			for(unsigned int i=0;i<len+1;i++)
			  Buffer[i]=(UTF16)Copychar[i];


}

UTF16String::UTF16String(XtreMLFlow & ChValue)
{
            if(ChValue.Length()==0)
			{
			  this->CountItem=0;
			  this->Capacity=0;
			  this->Buffer=NULL;
			  return;
			}
			CountItem=ChValue.GetUTF16Size()/2;
			Capacity=CountItem+1;
			Buffer=new UTF16[Capacity];
			ChValue.WriteToUTF16BE((UTF16*)Buffer);
			Buffer[CountItem]=0;


}

UTF16String::~UTF16String()
{
		   if(Buffer)
			  delete[]Buffer;
}


wchar_t* UTF16String::w_str(void) const
{
		   if(Buffer)
			 return (wchar_t*)Buffer;
		   else return (wchar_t*)GetNullwchar();
}

wchar_t UTF16String::operator[](unsigned int Index) const
{
		   if(Index<CountItem)
			return Buffer[Index];
		   else
			return (wchar_t)0;

}

UTF16String &UTF16String::operator=( XtreMLFlow &ChValue)
{
	return *this=UTF16String(ChValue);
}

UTF16String &UTF16String::operator=(const  char*CharString )
{
    return *this=UTF16String(CharString);
}

UTF16String &UTF16String::operator=(const UTF16String &utfstring)
{

		  if(utfstring.CountItem==0)
		  {
			if(this->Buffer)
			{  delete[] this->Buffer;
			   this->Buffer=NULL;
			}
			this->Capacity=0;
			this->CountItem=0;
			return *this;
		  }

		  if(this->Buffer==NULL)
		  {
			this->CountItem=utfstring.CountItem;
			this->Capacity=this->CountItem+1;
			this->Buffer=new UTF16[this->CountItem+1];

		  }
		  else if(this->Capacity-1<utfstring.CountItem)
		  {
			 delete[] Buffer;
			 this->CountItem=utfstring.CountItem;
			 this->Capacity=this->CountItem+1;
			 this->Buffer=new UTF16[this->CountItem+1];
		  }

		  this->CountItem=utfstring.CountItem;
		  for(unsigned int i=0;i<this->CountItem+1;i++)
			 this->Buffer[i]=utfstring.Buffer[i];

			 return *this;

}

UTF16String &UTF16String::operator=(const wchar_t* InChar)
{
		   unsigned int len=wchar_tLen(InChar);
		   if(len==0)
			{
				 Capacity=0;
				 CountItem=0;
				 if(this->Buffer)
				 {  delete[] this->Buffer;
			        this->Buffer=NULL;
				}
				 return *this;
			}

		  if(this->Buffer==NULL)
		  {
			this->CountItem=len;
			this->Capacity=this->CountItem+1;
			this->Buffer=new UTF16[this->CountItem+1];

		  }
		  else if(this->Capacity-1<len)
		  {
			 delete[] Buffer;
			 this->CountItem=len;
			 this->Capacity=this->CountItem+1;
			 this->Buffer=new UTF16[this->CountItem+1];
		  }


			for(unsigned int i=0;i<len+1;i++)
			  this->Buffer[i]=InChar[i];
			this->CountItem=len;
			return *this;
}

bool  UTF16String::operator==(const  char*CharString)
{
    return *this==UTF16String(CharString);
}

bool  UTF16String::operator==(const UTF16String &utfstring)
{
		   if(utfstring.CountItem!=this->CountItem)
			 return false;
		   if(&utfstring==this)
			  return true;

		   for(unsigned int i=0;i<this->CountItem;i++)
			 if(utfstring.Buffer[i]!=this->Buffer[i])
				return false;

		   return true;

}

bool  UTF16String::operator==(const wchar_t*InChar)
{
			unsigned int len=wchar_tLen(InChar);
		   if(len!=this->CountItem)
			 return false;

		   for(unsigned int i=0;i<this->CountItem;i++)
			 if(InChar[i]!=(wchar_t)this->Buffer[i])
				return false;

		   return true;

}

UTF16String & UTF16String::operator+=(const  char*CharString)
{
    return *this+=UTF16String(CharString);
}

UTF16String & UTF16String::operator+=(const UTF16String &utfstring)
{

		  if(&utfstring!=this)
		  {
			 if(this->Capacity-1<(utfstring.CountItem+this->CountItem))
			 {
				 UTF16String Temp(*this);
				 if(this->Buffer)
				 {  delete[] this->Buffer;
			      this->Buffer=NULL;
				 }
				 this->Capacity=utfstring.CountItem+this->CountItem+1;
				 this->Buffer=new UTF16[this->Capacity];
				 *this=Temp;
			 }

			 for(unsigned int i=0;i<utfstring.CountItem+1;i++)
			   this->Buffer[i+this->CountItem]=utfstring.Buffer[i];

			 this->CountItem+=utfstring.CountItem;
			 return *this;
		  }
		  else
		  {
			  UTF16String TempString(*this);
			   *this=TempString;
			  return *this;

		  }

}

UTF16String &UTF16String::operator+=(const wchar_t*InChar)
{
		  unsigned int len=wchar_tLen(InChar);
		  if (len==0)
		  return *this;

			 if(this->Capacity-1<(len+this->CountItem))
			 {  UTF16String Temp(*this);
				 if(this->Buffer)
			     {  delete[] this->Buffer;
			        this->Buffer=NULL;
			     }
				 this->Capacity=len+this->CountItem+1;

				 this->Buffer=new UTF16[this->Capacity];
				 *this=Temp;
			 }

			 for(unsigned int i=0;i<len+1;i++)
			   this->Buffer[i+this->CountItem]=(UTF16)InChar[i];

			 this->CountItem+=len;
			 return *this;
}



int UTF16String::GetUTF8Size(void)
{

   			 int len=0;
			 for(unsigned int i=0;i<CountItem;i++)
			 {
				if(Buffer[i]<0x80)
				  len+=1;
				else if(Buffer[i]<0x1000)
				 len+=2;
				else //if(Buffer[i]<=0xFFFF)
				 len+=3;
			   /*	else if(Buffer[i]<0x11000)
				 len+=4;
				else
				 return 0; */
			 }
			 return len;

}

const int UTF16String::Length()const
{
     return this->CountItem;
}

void UTF16String::Clear(void)
{
    CountItem=0;
}

int UTF16String::GetUTF32Size(void)
{
	 return CountItem*4;
}

int UTF16String::GetUnicodeSize(EncodeType enc)
{
  switch(enc)
  {
	case EncUTF8 : return GetUTF8Size();
	case EncASCII: return GetUTF8Size();
	case EncUTF16LE : return CountItem*2;
	case EncUTF16BE: return CountItem*2;
	case EncUTF32LE:return CountItem*4;
	case EncUTF32BE:return CountItem*4;
	default : return 0;
  }
}



unsigned int wchar_tLen(const wchar_t *Buffer)
{
	try
	{ int i=0;
	   while(Buffer[i++]!=0);
       return i-1;
	}
	catch(...)
	{

    }

	return 0;
}

const wchar_t *GetNullwchar(void)
{
    return constchar;
}

bool  isValidName(const wchar_t*name)
{
  int len;
	if((len=wchar_tLen(name))==0)
	 return false;

	if(!isValidBeginName(name[0]))
	  return false;

	for(int i=1; i<len;i++)
	  if(!isValidCode((int)name[i])|| name[i]==L' ')
		 return false;

	return true;
}

bool  isValidName(const UTF16String& name)
{
   if(name.Length()==0)
	 return false;


	if(!isValidBeginName(name[0]))
	  return false;

	for(int i=1; i<name.Length();i++)
	  if(!isValidCode((int)name[i])|| name[i]==L' ')
		 return false;

	return true;
}

bool  isValidText(const wchar_t*name)
{
  int len;
	if((len=wchar_tLen(name))==0)
	 return false;
	for(int i=0; i<len;i++)
	if(name[i]==L'>'||name[i]==L'<')
	  return false;


	return true;
}

int   EncodeCharByte(EncodeType enc)
{
  switch(enc)
  {
	case EncUTF8 :return 1;
	case EncASCII: return 1;
	case EncUTF16LE:return 2;
	case EncUTF16BE: return 2;
	case EncUTF32LE :return 4;
	case EncUTF32BE:return 4;
	default : return 0;
  }

}


bool TestUnicodeXMLFormat(DecodeFunc UnicodeFunct,char*Stream,
								   int len,char**beginstream)
{
 int codelen,i=0,j,CountZero=0,cpt=0;

 unsigned int code;
  while(i<len)
  {
	  if(UnicodeFunct((unsigned char*)Stream,&code,&codelen)==0)
		return false;
	  i+=codelen;
	  if(isValidCode(code))
		if(code==10||code==13||code==32||code==0)
		{

			Stream+=codelen;
			cpt++;
			if(code==0)
			  CountZero++;
			continue;
		}
	  if(code==60)
	  {

			  *beginstream=(char*)Stream;
			  j=i;
			  while(j<len-4)
			  {
				 Stream+=codelen;
				 if(UnicodeFunct((unsigned char*)Stream,&code,&codelen)==0)
                   return false;
				 j+=codelen;
				 cpt++;
				 if(code==0)
					 CountZero++;
				 if(!isValidCode(code))
					break;
			  }

			  if(!isValidCode(code))
				 break;
			  if(((CountZero*100)/cpt)>10)
				return false;
			  else
			    return true;
	  }
	  else
	   return false;
  }

  return false;
}


const unsigned char UTF8_BOM[3]={0xEF ,0xBB ,0xBF};
const unsigned char UTF8_BOM1[3]={0xEF ,0xBF ,0xBF};
const unsigned char UTF8_BOM2[3]={0xEF ,0xBF ,0xBE};
const unsigned char UTF16_BE_BOM[2]={ 0xFE,0xFF};
const unsigned char UTF16_LE_BOM[2]={0xFF, 0xFE };
const unsigned char UTF32_BE_BOM[4]={0x00,0x00,0xFE,0xFF};
const unsigned char UTF32_LE_BOM[4]={0xFF,0xFE,0x00,0x00};


DecodeFunc DetectEncode(unsigned char*buffer, int len,EncodeType&enc,char**beginstream)
{

  if(buffer[0]==0xEF&&buffer[1]==0xBB&&buffer[2]==0xBF)
  {
	  enc=EncUTF8;
	  if(TestUnicodeXMLFormat(UTF8ToCodePoint,(char*)&buffer[3],len-3,beginstream))
	   return UTF8ToCodePoint;
  }

if(buffer[0]==0xEF&&buffer[1]==0xBF&&buffer[2]==0xBE)
  {
	  enc=EncUTF8;
	  if(TestUnicodeXMLFormat(UTF8ToCodePoint,(char*)&buffer[3],len-3,beginstream))
	   return UTF8ToCodePoint;
  }

if(buffer[0]==0xEF&&buffer[1]==0xBF&&buffer[2]==0xBF)
  {
	  enc=EncUTF8;
	  if(TestUnicodeXMLFormat(UTF8ToCodePoint,(char*)&buffer[3],len-3,beginstream))
	   return UTF8ToCodePoint;
  }


  if(buffer[0]==0xFE&&buffer[1]==0xFF)
  {
	  enc=EncUTF16BE;
	   if(TestUnicodeXMLFormat(UTF16_BEToCodePoint,(char*)&buffer[2],len-2,beginstream))
	  return UTF16_BEToCodePoint;
  }

  if(buffer[2]==0x00&&buffer[3]==0x00&&buffer[1]==0xFE&&buffer[0]==0xFF)
  {
	  enc=EncUTF32LE;
	  if(TestUnicodeXMLFormat(UTF32_LEToCodePoint,(char*)&buffer[4],len-4,beginstream))
	  return UTF32_LEToCodePoint;
  }

  if(buffer[0]==0xFF&&buffer[1]==0xFE)
  {
	  enc=EncUTF16LE;
	   if(TestUnicodeXMLFormat(UTF16_LEToCodePoint,(char*)&buffer[2],len-2,beginstream))
	  return UTF16_LEToCodePoint;
  }

  if(buffer[0]==0x00&&buffer[1]==0x00&&buffer[2]==0xFE&&buffer[3]==0xFF)
  {
	  enc=EncUTF32BE;
	  if(TestUnicodeXMLFormat(UTF32_BEToCodePoint,(char*)&buffer[4],len-4,beginstream))
	  return UTF32_BEToCodePoint;
  }

if(TestUnicodeXMLFormat(UTF8ToCodePoint,(char*)&buffer[0],len,beginstream))
{
	enc=EncUTF8;
	return UTF8ToCodePoint;
}

if(TestUnicodeXMLFormat(UTF16_BEToCodePoint,(char*)&buffer[0],len,beginstream))
{
	enc=EncUTF16BE;
	return UTF16_BEToCodePoint;
}

if(TestUnicodeXMLFormat(UTF16_LEToCodePoint,(char*)&buffer[0],len,beginstream))
{
	enc=EncUTF16LE;
	return UTF16_LEToCodePoint;
}

if(TestUnicodeXMLFormat(UTF32_BEToCodePoint,(char*)&buffer[0],len,beginstream))
{
	enc=EncUTF32BE;
	return UTF32_BEToCodePoint;
}

if(TestUnicodeXMLFormat(UTF32_LEToCodePoint,(char*)&buffer[0],len,beginstream))
{
	enc=EncUTF32LE;
	return UTF32_LEToCodePoint;
}

if(TestUnicodeXMLFormat(ASCIIToCodePoint,(char*)&buffer[0],len,beginstream))
{
	enc=EncASCII;
	return ASCIIToCodePoint;
}

enc= EncUNKNOWN;
return ASCIIToCodePoint;
}




