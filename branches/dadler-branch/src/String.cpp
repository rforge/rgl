#include "String.hpp"

#include "types.h"

//////////////////////////////////////////////////////////////////////////////
//
// SECTION: Strings
//

//
// CLASS
//   StringArrayImpl
//

class StringArrayImpl : public AutoDestroy
{
public:
  StringArrayImpl(int in_ntexts, char** in_texts) 
  {
    int i;

    ntexts = in_ntexts;

    lengths = new unsigned int [ntexts];

    int buflen = 0;

    for(i=0;i<ntexts;i++)
      buflen += lengths[i] = strlen(in_texts[i]);

    char* tptr = textbuffer = new char [buflen];

    for(i=0;i<ntexts;i++) {
      int len = lengths[i];
      memcpy(tptr, in_texts[i], len);
      tptr += len;
    }
  }

  ~StringArrayImpl()
  {
    delete [] lengths;
    delete [] textbuffer;
  }
  int   ntexts;
  char* textbuffer;
  unsigned int*  lengths;
};

//
// CLASS
//   StringArray
//

StringArray::StringArray()
{
  impl = NULL;
}

StringArray::StringArray(int in_ntexts, char** in_texts)
{
  if (in_ntexts > 0)
    impl = new StringArrayImpl(in_ntexts, in_texts);
  else
    impl = NULL;
}

StringArray::StringArray(StringArray& from)
{
  impl = from.impl;

  if (impl)
    impl->ref();
}

StringArray::~StringArray()
{
  if (impl)
    impl->unref();
}

//
// CLASS
//   StringArrayIterator
//

StringArrayIterator::StringArrayIterator(StringArray* in_array)
{
  array = in_array;
}

void StringArrayIterator::first()
{
  cnt = 0;
  if (array->impl)
    textptr = array->impl->textbuffer;
  else
    textptr = NULL;
}

void StringArrayIterator::next()
{
  if ( (textptr) && (cnt < array->impl->ntexts) )
    textptr += array->impl->lengths[cnt++];
}

String StringArrayIterator::getCurrent()
{
  return String(array->impl->lengths[cnt], textptr );
}

bool StringArrayIterator::isDone() const 
{
  if (array->impl)
    return (cnt == array->impl->ntexts) ? true : false;
  else
    return true;
}
