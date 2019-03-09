#ifndef   _LIST_TA_H
#define   _LIST_TA_H
#include "wndws.h"

//Base class. It is needed for making dynamic arrays (lists)
class CListItem
{
   protected:
     CListItem  *Next;                                           //next item in list
     CListItem  *Previous;                                       //previous item in list

   public:
     CListItem();                                                //construcor
     void SetNext (CListItem *);                                 //set next item in list
     CListItem *GetNext();                                       //get next item in list
     void SetPrevious (CListItem *);                             //set previous item in list
     CListItem *GetPrevious();                                   //get previous item in list
     virtual ~CListItem();
};

//List of CListItem elements
class CList
{
   public:
     CListItem *First;                                           //First item in list
     CListItem *Current;                                         //Current item in list - please do not use
     CListItem *Last;                                            //Last item in list
     DWORD Number;                                               //Number of items  

     CList();
     virtual ~CList();
     virtual bool Add(CListItem *, int = LAEnd);                 //add item
     virtual bool Delete (CListItem *&);                         //delete item
     virtual bool Clear();                                       //delete all items
     CListItem *GetLast();										 //Get last item in list
     CListItem *GetFirst();										 //Get First item in list
     DWORD GetNumber();
     DWORD ElementSize;                                          //size of list item

     enum {
             LABeginning,//used as Add function second parameter, means: add item in the beginning of a list
             LAEnd       //used as Add function second parameter, means: add item in the end of a list
          };
};

#endif  //_LIST_TA_H
