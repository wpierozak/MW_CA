#include<iostream>
#include"GenerationManager.hpp"
#include"GeneratorCA.hpp"
#include"GeneratorMC.hpp"
#include"postproc.hpp"

int main(int argc, const char** argv)
{
    if(argc < 6)
    {
        std::cout<< "Argc: " << argc << " - aborting\n"; 
        return -1;
    }
    m_int dimX = std::stoi(argv[1]);
    m_int dimY = std::stoi(argv[2]);
    m_int dimZ = std::stoi(argv[3]);
    m_int statesNumber = std::stoi(argv[4]);
    m_int itrLimit = std::stoi(argv[5]);

    std::cout<< "Starting\n";

    GenerationManager gen(dimX, dimY, dimZ, itrLimit);

    {
        Random::vecrand_n rands;
        rands.push_back({std::shared_ptr<Neighbourhood>(new Moore), 0.9});
        rands.push_back({std::shared_ptr<Neighbourhood>(new Neumann), 0.1});
        gen.setNeighbourhood(std::shared_ptr<Neighbourhood>(new Moore));
    }

    {
        std::shared_ptr<BC> bc(new Periodic(dimX, dimY, dimZ));
        gen.setBC(bc);
    }

    {
        std::shared_ptr<Rule> rule(new MC(0.5));
        //std::shared_ptr<Rule> rule(new MostNumerous);
        gen.setRule(rule);
    }

    {
        gen.setThreadsNumber(12);
    }

    gen.nucleate(std::shared_ptr<Nucleator>(new RandomUniformNucleator(statesNumber)));

    try
    {
        //gen.startMC();
        gen.start<GeneratorMC>();
        Domain& d = gen.domain();
        std::vector<color> n;
        toBmp(d, gen.stateNumber(), "/home/wiktor/Desktop/MW/MW_CA/res/", n);
        MS_Statistic ms;
        ms.measure(d, statesNumber);
        m_float sum = 0.0;
        for(auto p : ms.grainsCount)
        {
            //std::cout<< p.first << ' ' << p.second << std::endl;
            sum += p.second;
        }
        std::cout << sum;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }


    std::cout<< "Finish\n";
    return 0;
}
