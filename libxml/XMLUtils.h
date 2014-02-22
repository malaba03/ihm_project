#ifndef XMLUtilsH
#define XMLUtilsH
#include "unicodeConvert.h"

#define CharValueCapacity    256
#define UTF16Capacity        2
#define constchar            L"\0\0";

unsigned int wchar_tLen(const wchar_t *Buffer);
bool  isValidName(const wchar_t*name);
bool  isValidCode(unsigned int CodePoint);
bool  isValidText(const wchar_t*name);
bool  isValidBeginName(wchar_t begin);
int   EncodeCharByte(EncodeType enc);
const wchar_t *GetNullwchar(void);
typedef int (*DecodeFunc)(unsigned char*,unsigned int*, int*);
typedef int (*EncodeFunc)(unsigned char*,unsigned int, int*);

template<typename A>
inline A Min(A Value1, A Value2)
{
	if(Value1<Value2)
	   return Value1;
	else return Value2;
}

template<typename A>
inline A Max(A Value1, A Value2)
{
	if(Value1>Value2)
	   return Value1;
	else return Value2;
}


//DecodeFunc DetectEncode(char*buffer,int  len,EncodeType&enc,char**BeginStream);
DecodeFunc DetectEncode(unsigned char*buffer, int len,EncodeType&enc,char**beginstream);

/*******************************************************************************
*Cette classe aura pour but d'accumulé les caractères unicodes lu durant le    *
*parsing d'un élément                                                          *
*                                                                              *
*                                                                              *
*******************************************************************************/
class XtreMLFlow
{
   private:
			unsigned int     CountItem;
			unsigned int     *Buffer;
			unsigned int     Capacity;

			friend   XtreMLFlow operator+(const XtreMLFlow &Char1, const XtreMLFlow &Char2)
		    {
				XtreMLFlow Temp(Char1);
				Temp+=Char2;
				return Temp;
			}

   public:
		 XtreMLFlow();
		 XtreMLFlow(unsigned int cap);
		 XtreMLFlow(const XtreMLFlow& ChValue);
		 ~XtreMLFlow();
		 void SetLength(int length);
		 XtreMLFlow &operator=( const XtreMLFlow &ChValue);
		 XtreMLFlow &operator+=(const XtreMLFlow  &ChValue);
		 bool operator==(const XtreMLFlow &ChValue)const;
		 int operator[](unsigned int Index)const;
		 int Length(void);
		 void Clear(void);
		 int GetUTF8Size(void);
		 int GetUTF16Size(void);
		 int GetUTF32Size(void);
		 void WriteToUTF16BE(UTF16*);
		 void WriteToUTF8(char*);
		 void WriteToUTF32(char*);
		 void AddValue(unsigned int value);



};

/*******************************************************************************
*  La classe UTFSTring  permet de manipuler des chaines de caractères unicodes,*
*	pour ce faire chaque caractères est codés sur deux octects.                *
*                                                                              *
*******************************************************************************/


class UTF16String
{
  private:
		   UTF16 *Buffer;
		   unsigned int Capacity;
		   unsigned int CountItem;
		   friend UTF16String operator+(const UTF16String &utfstring,const UTF16String &utfstring1)
		   {
			 UTF16String Temp(utfstring);
			 return Temp+=utfstring1;
		   }

			friend UTF16String operator+(const wchar_t*InChar,const UTF16String &utfstring)
			{
			  UTF16String Temp(InChar);
			  return Temp+=utfstring;
			}

			friend UTF16String operator+(const  char*CharString,const UTF16String &utfstring)
			{
			  UTF16String Temp(CharString);
			  return Temp+=utfstring;
			}

  public:

	   UTF16String();
	   UTF16String(unsigned int);
	   UTF16String(const UTF16String &utfstring );
	   UTF16String(const wchar_t *Copychar);
	   UTF16String(const  char    *CharToClone);
	   UTF16String( XtreMLFlow & ChValue);
	   ~UTF16String();
	   wchar_t* w_str(void)const;
	   wchar_t operator[](unsigned int Index)const;
	   UTF16String &operator=(const UTF16String &utfstring);
	   UTF16String &operator=(const  char*CharString );
	   UTF16String &operator=(const wchar_t* InChar);
	   UTF16String &operator=(XtreMLFlow &ChValue);
	   bool  operator==(const  char*CharString);
	   bool  operator==(const UTF16String &utfstring);
	   bool  operator==(const wchar_t*InChar);
	   UTF16String & operator+=(const  char*CharString);
	   UTF16String & operator+=(const UTF16String &utfstring);
	   UTF16String & operator+=(const wchar_t*InChar);
	   int GetUTF8Size(void);
	   int GetUnicodeSize(EncodeType enc);
	   const int Length()const ;
	   int GetUTF32Size(void);
	   void Clear(void);
};


bool  isValidName(const UTF16String&);


#endif