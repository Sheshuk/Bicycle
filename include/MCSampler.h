#ifndef MCSAMPLER__H
#define MCSAMPLER__H
#include <random>
#include <chrono>
#include <array>
#include <functional>

template <size_t N>
class FunctionSpace
{
public:
    using point=std::array<double,N>;
public:
    FunctionSpace(point LowerLim, point UpperLim):p0(LowerLim),p1(UpperLim){};
    point Uniform(std::default_random_engine &generator){
        point r;
        for(size_t i=0;i<N;++i){
            std::uniform_real_distribution<double> distr(p0[i],p1[i]);
            r[i]=distr(generator);
        }
        return r;
    }

    point Gauss(std::default_random_engine &generator){
        point r;
        for(size_t i=0;i<N;++i){
            std::uniform_real_distribution<double> distr(p0[i],p1[i]);
            r[i]=distr(generator);
        }
        return r;
    }
protected:
    point p0,p1;
};

template <size_t N>
class MCSampler
{
public:
    using point=std::array<double,N>;
    using Pdf=std::function<double(const point&)>;
    using Space=FunctionSpace<N>;
public:
    MCSampler(Pdf PdfFun, Space Lims):pdf(PdfFun),limits(Lims){
          Reset();
    };
    
    void Reset(){
        generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
        Nkeep=Ntry=0;
    }

    point GenPoint(double pmax=1.0){
        std::uniform_real_distribution<double> distr(0,pmax);
        point r;
        double a;
        do{
            r=limits.Uniform(generator);
            a=distr(generator);
            ++Ntry;
        }while(a>pdf(r));
        ++Nkeep;
        return r;
    }
    double Efficiency(){return Nkeep*1./Ntry;}
private:
    Pdf pdf;
    Space limits;
    std::default_random_engine generator;
    unsigned long Nkeep, Ntry;
};

#endif