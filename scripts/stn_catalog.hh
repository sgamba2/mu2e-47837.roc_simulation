//-----------------------------------------------------------------------------
// a 'dataset' here is a histogram file plus data fields for plotting attributes
//-----------------------------------------------------------------------------
#ifndef __Stntuple_val_stn_catalog_hh__
#define __Stntuple_val_stn_catalog_hh__

#include "Stntuple/val/stn_book.hh"
#include "Stntuple/val/stn_dataset.hh"
#include "Stntuple/val/hist_file.hh"
//-----------------------------------------------------------------------------
// book is a list of datasets, list owns its pointers
//-----------------------------------------------------------------------------
class stn_catalog : public TNamed {
public:
  TObjArray*           fListOfBooks;

  stn_catalog(const char* Name = "") ;

  ~stn_catalog() ;

  int AddBook(stn_book* Book);

  stn_book* Book(int I) { return (stn_book*) fListOfBooks->UncheckedAt(I); }

  stn_book* FindBook(const char* Name) const ;
};

#endif
