#ifndef   _LIST_TA_CPP
#define   _LIST_TA_CPP

#include "..\H\_LIST.H"

//implementation for CListItem class
CListItem::CListItem()
{
   Next     = NULL;
   Previous = NULL;
};

void CListItem::SetNext(CListItem *_Next)
{
   Next = _Next;
   if (_Next!=NULL)
   {
      Next->Previous = this;
   }
};

CListItem *CListItem::GetNext()
{
   return Next;
};

void CListItem::SetPrevious(CListItem *_Previous)
{
   Previous = _Previous;
   if (_Previous!=NULL)
   {
      Previous->Next = this;
   }
};

CListItem *CListItem::GetPrevious()
{
   return Previous;
};

CListItem::~CListItem()
{

}

//Implementation for CList class
CList::CList()
{
   First   = NULL;
   Last    = NULL;
   Current = NULL;
   Number  = 0;
   ElementSize = 0;
};

bool CList::Add(CListItem *_item, int where)
{
   if (_item == NULL)
   {
      return false;
   }
   if (First == NULL)
   {
      Number  = 0;
      First   = _item;
      Last    = _item;
      _item->SetNext(NULL);
      _item->SetPrevious(NULL);
   }
   else
   {
      if  (where == CList::LAEnd)
      {
         Last->SetNext(_item);
         Last = _item;
         _item->SetNext(NULL);
      }
      else if (where == CList::LABeginning)
      {
         First->SetPrevious(_item);
         First = _item;
         _item->SetPrevious(NULL);
      }
   }
   Number++;
   Current = _item;
   return true;
};


bool CList::Delete (CListItem *&_item)
{
   if (_item == NULL) return false;
   CListItem *c = _item->GetPrevious();
   if (_item == First)
   {                           
       First = First->GetNext();      
   }                           
   if (_item == Last)
   {                           
       Last = Last->GetPrevious();
   }                          
   if (_item->GetPrevious() != NULL) 
   {
       _item->GetPrevious()->SetNext(_item->GetNext());
   }
   else if (_item->GetNext() != NULL)
   {
       _item->GetNext()->SetPrevious(NULL);
   }
   if (Current == _item)
   {
       if (!ElementSize)
       {
           delete _item;
       }
       else VirtualFree( _item, ElementSize, MEM_DECOMMIT);   
       _item = c;
       Current = c;
   }
   else
   {
       if (!ElementSize)
       {
           delete _item;
       }
       else VirtualFree( _item, ElementSize, MEM_DECOMMIT);   
       _item = c;
   }
   Number--;
   return true;
};

bool CList::Clear()
{
  if (First == NULL && Last == NULL) return true;
  if (First == NULL || Last == NULL) return false;

  Current = First;
  while (Current->GetNext()!=NULL)
  {
      if (Current->GetNext()->GetPrevious() != Current) return false;
      Current = Current->GetNext();
      if (!ElementSize)
      {
          delete Current->GetPrevious();
      }
      else VirtualFree( Current->GetPrevious(), ElementSize, MEM_DECOMMIT);         
  };
  if (!ElementSize)
  {
      delete Current;
  }
  else VirtualFree( Current, ElementSize, MEM_DECOMMIT);   
  First    = NULL;
  Last     = NULL;
  Current  = NULL;
  Number   = 0;
  return true;
};

DWORD CList::GetNumber()
{
  return Number;
};

CList::~CList()
{
   Clear();
};

CListItem *CList::GetLast()
{
   return Last;
};

CListItem *CList::GetFirst()
{
   return First;
};

#endif  //_LIST_TA_CPP
