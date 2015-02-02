#ifndef ROOTUTILS__H
#define ROOTUTILS__H 
#include "TGraph.h"
#include "TGraph2D.h"
#include "TH1D.h"
#include "TH2D.h"

#include "Axis.h"
#include "ArrayT.h"
#include "TableT.h"



TGraph   make_TGraph(const Table<1>& flux);
TGraph2D make_TGraph2D(const Table<2>& flux);
TH1D     make_TH1D(const Table<1> &flux,const char* title);
TH2D     make_TH2D(const Table<2> &flux,const char* title);

#endif
