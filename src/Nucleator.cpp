#include"Nucleator.hpp"

void RandomUniformNucleator::nucleation(Domain& domain) 
{
    std::uniform_int_distribution xdist(0, (int)domain.dimX()-1);
    std::uniform_int_distribution ydist(0, (int)domain.dimY()-1);
    std::uniform_int_distribution zdist(0, (int)domain.dimZ()-1);
    for(m_int s = 0; s < _statesNumber; s++)
    {
        m_int x = xdist(_rand);
        m_int y = ydist(_rand);
        m_int z = zdist(_rand);
        domain(x,y,z) = s;
    }
}

void UniformNucleator2D::nucleation(Domain& domain)
{
    m_int sX = domain.dimX()/floor(sqrt(_statesNumber));
    m_int sY = domain.dimY()/ceil(sqrt(_statesNumber)); 

    m_int x = sX/2; m_int y = sY/2;
    for(m_int s = 0; s < _statesNumber; s++)
    {
        domain(x,y,0) = s;
        x += sX;
        if( x >= domain.dimX())
        {
            x = sX/2;
            y += sY;
            if( y >= domain.dimY()) break;
        }
    }
}