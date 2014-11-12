class TGraph;
class TGraph2D;
class TH1D;
class TH2D;


TGraph   make_TGraph(const Table1D& flux);
TGraph2D make_TGraph2D(const Table2D& flux);
TH1D     make_TH1D(const Table1D &flux);
TH2D     make_TH2D(const Table2D &flux);

