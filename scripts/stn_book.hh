//-----------------------------------------------------------------------------
// a 'dataset' here is a histogram file plus data fields for plotting attributes
//-----------------------------------------------------------------------------
#ifndef __Stntuple_val_stn_book_hh__
#define __Stntuple_val_stn_book_hh__

#include "TString.h"
#include "TObjArray.h"

#include "hist_file.hh"
#include "stn_dataset.hh"

class stn_catalog;
//-----------------------------------------------------------------------------
// book is a list of datasets, list owns its pointers
//-----------------------------------------------------------------------------
class stn_book  : public TNamed {
public:
  TString                fHistDir;
  TObjArray*             fListOfDatasets;
  stn_catalog*           fCatalog;

  stn_book(const char* Name = "", const char* HistDir = "");
  ~stn_book();
  
  const char* HistDir() { return fHistDir.Data(); }

  int AddDataset(stn_dataset_t* Ds) {
    int rc = fListOfDatasets->GetEntriesFast();
    fListOfDatasets->Add(Ds);
    return rc;
  }
  
  stn_dataset_t* Dataset (int I) { return (stn_dataset_t*) fListOfDatasets->UncheckedAt(I) ; }

  stn_dataset_t* FindDataset(const char* DsID) const ;
  stn_dataset_t* NewDataset (const char* DsID, const char* Name,
                             long int NEvents, long int NGenEvents, float LumiSF = -1.) ;

  hist_file_t*   NewHistFile (const char* DsID, const char* ProductionJob, const char* AnalysisJob);
  
  hist_file_t*   FindHistFile(const char* DsID, const char* ProductionJob, const char* AnalysisJob) const ;
  
};

#endif
