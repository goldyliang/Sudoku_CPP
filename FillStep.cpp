/*
 * FillStep.cpp
 *
 *  Created on: 2014��6��19��
 *      Author: Liang
 */

#include "FillStep.h"
#include "Resolver.h"

#include "Board.h"


using std::cout;
using std::endl;


FillStep::~FillStep()
{
	return;
}

void FillStep::init (NUM_T x, NUM_T y, NUM_T n)
{
//    this->bd = bd;
//    this->rs = rs;
    this->x = x;
    this->y = y;
    this->n = n;
    this->solved = false;
}


void FillStep::first()
{
    i=1;
}

bool FillStep::next()
{
    i++;
    return true;
}

bool FillStep::isLast()
{
    return (i >= candCount());
}

void FillStep::applyFill(Board & bd)
{
	bd.fill(x,y,n);
}

void FillStep::revertFill(Board & bd)
{
	bd.erase(x,y);
}

void FillStep::print(ostream &os, bool brief) const
{
//	if (!os) os=(&cout);
	os << "(" << x << "," << y << ")-" << n << "---";
}

/*NumCandStep::NumCandStep (Board * bd, NUM_T x, NUM_T y) : FillStep(bd,x,y,0)
{
}*/

/*void NumCandStep::init (Board * bd, NUM_T x, NUM_T y)
{
	this->bd = bd;
	this->x=x;
	this->y=y;
}*/

//ARRAY_9_9_T<NumCandStep*> NumCandStep::p_NumCandSteps;


/*NumCandStep::NumCandStep (Board * bd, Resolver * rs, NUM_T x, NUM_T y): FillStep(bd,rs,x,y,0)
{
    this->numCands.makeFullList();

    //NumCandStep::p_NumCandSteps[x][y] = this;
}
*/

void NumCandStep::init (NUM_T x, NUM_T y)
{
    FillStep::init(x,y,0);
    this->numCands.makeFullList();

}


NUM_T NumCandStep::candCount() const
{
	return numCands.numCount();
}

void NumCandStep::first()
{
	this->n = numCands.getFirst();
	FillStep::first();
}

bool NumCandStep::next()
{
	n = numCands.getNext(n);
    FillStep::next();
	return n;
}



void NumCandStep::print(ostream &os, bool brief) const
{
//	if (!os) os=(&cout);

	FillStep::print(os);

	if (!brief)
	    numCands.print(os);

	os<<endl;
}

/*bool NumCandStep::solved() const
{
	if (bd->get(x,y)==0)
		return false;
	else
		return true;
}*/

bool NumCandStep::removeCand (NUM_T cand)
{
    this->numCands.remove(cand);
    return numCands.numCount() > 0;
}


//array< array<PosCandStep*,10> , NUM_AREAS> PosCandStep::p_PosCandSteps;
/*

PosCandStep::PosCandStep (Board * bd, Resolver *rs, Area ar, NUM_T n) : FillStep(bd,rs,0,0,n), ar(ar)
{
    this->posCands.makeFullList();

   // PosCandStep::p_PosCandSteps [ar.getID()][n] = this;
 //   init ();
}
*/

void PosCandStep::init (Area ar, NUM_T n)
{
    FillStep::init (0,0,n);

    this->ar=ar;

    this->posCands.makeFullList();

}


NUM_T PosCandStep::candCount() const
{
	return posCands.numCount();
}

void PosCandStep::first()
{
	curPos=posCands.getFirst();
	ar.getPos(curPos,x,y);
    FillStep::first();

}

bool PosCandStep::next()
{
	curPos=posCands.getNext(curPos);
	if (curPos>0)
		ar.getPos(curPos,x,y);

    FillStep::next();

	return curPos;

}

void PosCandStep::print(ostream &os, bool brief) const
{
//	if (!os) os =(&cout);

	FillStep::print(os);

	this->ar.print(os);

	if (!brief) {
	    os << ":";
	    this->posCands.print(os);
	}

    os << endl;

	//ar->print(os);
}

/*bool PosCandStep::solved() const
{
    // ?????
	return posCands.numCount()==0;
}*/

bool PosCandStep::removeCand (NUM_T cand)
{
    this->posCands.remove(cand);
    return posCands.numCount() > 0;
}


FillStepList::FillStepList() : pStep(NULL)
{
    m_list.resize(10);
    numCandSteps.resize(10);
    posCandSteps.resize(NUM_AREAS);

    for (NUM_T x=1;x<=9;x++)
        for (NUM_T y=1;y<=9;y++)
        {
 //           candList[x][y].makeFullList();
            NumCandStep &st=numCandSteps[x][y];
            st.init (x,y);
            st.it = add ( &st);
//            FillSteps.add ( std::make_shared <NumCandStep> (&bd,this,x,y) );
        }

//  areas.resize(27);

//    NUM_T i=0;
    for (NUM_T y=1;y<=9;y++)
    {
//        areas[i].init(bd,ROW,y);

        Area ar(ROW,y);

        for (NUM_T n=1;n<=9;n++)
        {

            PosCandStep &st=posCandSteps[ar.getID()][n];

            st.init (ar,n);
            st.it = add ( & st);


//            FillSteps.add ( std::make_shared <PosCandStep> (&bd, this, Area(ROW,y), n) );
        }

//        i++;
    }

    for (NUM_T x=1;x<=9;x++)
    {
//        areas[i].init(bd,COL,x);
        Area ar(COL,x);

        for (NUM_T n=1;n<=9;n++)
        {

            PosCandStep &st=posCandSteps[ar.getID()][n];

            st.init (ar,n);

            st.it = add ( & st);


//            FillSteps.add ( std::make_shared <PosCandStep> (&bd, this,Area(COL,x), n) );
        }

//        i++;
    }

    for (NUM_T anum=1; anum<=9; anum++)
    {
 //       areas[i].init(bd,SQR,anum);

        Area ar(SQR,anum);

        for (NUM_T n=1;n<=9;n++)
        {
            PosCandStep &st=posCandSteps[ar.getID()][n];

            st.init (ar,n);

            st.it = add ( & st);

//            FillSteps.add ( std::make_shared <PosCandStep> (&bd, this,Area(SQR,anum), n) );
        }

 //       i++;
    }


}

FillStepList::FillStepList (FillStepList& ls):
        //bd(ls.bd),
        //rs(ls.rs),
        numCandSteps(ls.numCandSteps),
        posCandSteps(ls.posCandSteps)
        // copy constructor
{
    this->m_list.resize(10);

    for (NUM_T x=1;x<=9;x++)
        for (NUM_T y=1;y<=9;y++)
        {
            NumCandStep &st=numCandSteps[x][y];
            if (!st.solved)
                st.it = add ( &st);
            else st.it = m_list[st.candCount()].end();
        }

    for (int aid=0;aid<NUM_AREAS;aid++)
        for (NUM_T n=1;n<=9;n++)
        {
            PosCandStep &st=posCandSteps[aid][n];
            if (!st.solved)
                st.it = add (&st);
            else st.it = m_list[st.candCount()].end();
        }

    if ( typeid(*ls.pStep) == typeid(NumCandStep) )
    {
        NumCandStep *st = dynamic_cast <NumCandStep*> (ls.pStep);
        pStep = & numCandSteps[st->x][st->y];
    } else
    {
        PosCandStep *st = dynamic_cast <PosCandStep*> (ls.pStep);
        pStep = & posCandSteps[st->ar.getID()][st->n];
    }
}

FillStepList& FillStepList:: operator = (FillStepList && ls) noexcept
{
    if (this == &ls) return *this;

    //bd=ls.bd;
    //rs=ls.rs;
    numCandSteps=std::move(ls.numCandSteps);
    posCandSteps=std::move(ls.posCandSteps);
    pStep = ls.pStep;

    this->m_list=std::move(ls.m_list);

    /*
    this->m_list.resize(10);

    for (NUM_T n=1;n<=9;n++)
        m_list[n].clear();

    for (NUM_T x=1;x<=9;x++)
        for (NUM_T y=1;y<=9;y++)
        {
            NumCandStep &st=numCandSteps[x][y];
            if (!st.solved)
                st.it = add ( &st);
            else st.it = m_list[st.candCount()].end();
        }

    for (int aid=0;aid<NUM_AREAS;aid++)
        for (NUM_T n=1;n<=9;n++)
        {
            PosCandStep &st=posCandSteps[aid][n];
            if (!st.solved)
                st.it = add (&st);
            else st.it = m_list[st.candCount()].end();
        } */
    return *this;
}



FillStepList & FillStepList::operator = (FillStepList & ls)
{
    if (this==&ls) return *this;

    //bd=ls.bd;
    //rs=ls.rs;
    numCandSteps=ls.numCandSteps;
    posCandSteps=ls.posCandSteps;

    for (NUM_T n=1;n<=9;n++)
        m_list[n].clear();

    for (NUM_T x=1;x<=9;x++)
        for (NUM_T y=1;y<=9;y++)
        {
            NumCandStep &st=numCandSteps[x][y];
            if (!st.solved)
                st.it = add ( &st);
            else st.it = m_list[st.candCount()].end();
        }

    for (int aid=0;aid<NUM_AREAS;aid++)
        for (NUM_T n=1;n<=9;n++)
        {
            PosCandStep &st=posCandSteps[aid][n];
            if (!st.solved)
                st.it = add (&st);
            else st.it = m_list[st.candCount()].end();
        }

    if ( typeid(*ls.pStep) == typeid(NumCandStep) )
    {
        NumCandStep *st = dynamic_cast <NumCandStep*> (ls.pStep);
        pStep = & numCandSteps[st->x][st->y];
    } else
    {
        PosCandStep *st = dynamic_cast <PosCandStep*> (ls.pStep);
        pStep = & posCandSteps[st->ar.getID()][st->n];
    }

    return *this;
}


stepIterator FillStepList::add (FillStep * st)
{
    NUM_T cnt=st->candCount();
    m_list[cnt].push_back(st);
    //m_list.push_back (st);
    auto it=m_list[cnt].end();

    it--;
    return it;//m_list[cnt].end()-1;
}

bool FillStepList::removeCandAndMove (FillStep * st, NUM_T cand) // return false if no candidates
{
    if (st->solved)
        return true;

    NUM_T cnt=st->candCount();

    m_list [cnt].erase (st->it);

    if (!st->removeCand (cand))
        return false;

    cnt = st->candCount();
    m_list[cnt].push_back(st);

    stepIterator it_new=m_list[cnt].end();

    it_new--;
    st->it = it_new;

    return true;
//    return it_new;//m_list[cnt].end()-1;
}

void FillStepList::markSolvedAndMove (FillStep * st)
{
    if (st->solved)
        return;

    NUM_T cnt=st->candCount();
    m_list [cnt].erase (st->it);
    st->solved = true;
    st->it = m_list[cnt].end();
}


FillStep* FillStepList::getBestStep(bool & done)
{

    done = false;

    for (NUM_T candCnt = 1; candCnt <=9; candCnt ++)
    {
        if (!m_list[candCnt].empty())
        {
            pStep = *m_list[candCnt].begin();
            return pStep;
        }
    }

    done = true;
    return NULL;

/*    FillStep* best = NULL;

    int minCandNum=10;
    done=true;

    auto it = m_list.begin();
    auto ed = m_list.end();

    //return *it;

    while (it!=ed)
    {
        FillStep * st = *it++;

        if (!st->solved()) {
            done=false;
            int cnt=st->candCount();
            if (cnt==0) {

                return NULL;
            }


            if (cnt< minCandNum) {
                minCandNum = cnt;
                best = st;

                if (cnt<=1)
                    break;
            }

        }
    }

    return best;*/
}

/*void FillStepList::updatePos (FillStep_Ptr st)
{
    return;
}*/

bool FillStepList::markSolved (NUM_T x, NUM_T y, NUM_T n)
{
    markSolvedAndMove (&numCandSteps[x][y]);

    // TODO, move numCandSteps[x][y]

    Area::forEachThreeAreas (x,y,
            [&] (const Area &a) -> bool  {
        NUM_T i;
        a.getPosIdx(x,y,i);
        int aid=a.getID();
        markSolvedAndMove (&posCandSteps[aid][n]);
        return true;
    } );

    /*
    Area ars[3];
    Area::getThreeAreas(x,y,ars);

    for (NUM_T ari=0;ari<3;ari++)
    {
        NUM_T i;
        ars[ari].getPosIdx(x,y,i);
        int aid=ars[ari].getID();

        markSolvedAndMove (&posCandSteps[aid][n]);
    } */

    return true;
}

bool FillStepList::markUnFillable (NUM_T x, NUM_T y, NUM_T n)
{

    if (n!=0)
    {
        if (!removeCandAndMove(&numCandSteps[x][y], n))
            return false;
    }

    // TODO, move numCandSteps[x][y]

    return Area::forEachThreeAreas ( x, y,
            [&] (const Area & a) ->bool {

        NUM_T i;
        a.getPosIdx(x,y,i);
        int aid=a.getID();

        if (n>0)
            return removeCandAndMove (&posCandSteps[aid][n],i);
        else {
            for (NUM_T nn=1;nn<=9;nn++)
                 if (!removeCandAndMove( &posCandSteps[aid][nn], i))
                    return false;
            return true;
        }
    } );

    /*
    Area ars[3];
    Area::getThreeAreas(x,y,ars);

    for (NUM_T ari=0;ari<3;ari++)
    {
        NUM_T i;
        ars[ari].getPosIdx(x,y,i);
        int aid=ars[ari].getID();

        if (n>0)
        {
            if (!removeCandAndMove (&posCandSteps[aid][n],i))
                return false;
        }
        else
            for (NUM_T nn=1;nn<=9;nn++)
                 if (!removeCandAndMove( &posCandSteps[aid][nn], i))
                    return false;
    }
    return true; */
}


bool FillStepList::updateSteps (NUM_T x, NUM_T y, NUM_T n)
{
    markSolved (x,y,n);

    markUnFillable(x,y,0); // [x,y] can not fill any numbers

    for (NUM_T xx=1;xx<=9;xx++)
    {
        if (!markUnFillable(xx,y,n))
            return false;
    }

    for (NUM_T yy=1;yy<=9;yy++)
    {
        if (!markUnFillable(x,yy,n))
            return false;
    }

    Area ar(SQR,x,y);

    for (NUM_T i=1;i<=9;i++)
    {
        NUM_T xx,yy;
        ar.getPos(i,xx,yy);
        if (!markUnFillable(xx,yy,n))
            return false;
    }

    return true;
}

void FillStepList::printInfo (ostream & os)
{


    //return *it;

    os<<"Best step:"<<(long int)pStep<<"--";
    if (pStep) pStep->print(os);
    os<<endl;

    for (NUM_T y=1;y<=9;y++)
    {
        for (NUM_T x=1;x<=9;x++)
        {
            os<<(long int)(&numCandSteps[x][y])<<"-"<< (long int)(*numCandSteps[x][y].it);
            os<<"Solved:"<<numCandSteps[x][y].solved<<"---";
            numCandSteps[x][y].print(os);
        }
        os<<endl;
    }

    for (int i=0;i<NUM_AREAS;i++)
    {
        Area a(i);
        a.print(os);
        os<<endl;
        for (NUM_T n=1;n<=9;n++)
        {
            os<<(long int)(&posCandSteps[i][n])<<"-"<< (long int)(*posCandSteps[i][n].it);
            os<<"Solved:"<<posCandSteps[i][n].solved<<"---";
            posCandSteps[i][n].print(os);
        }
    }

    for (NUM_T cnt=1;cnt<=9;cnt++)
    {
        os << "m_list[" << cnt <<"]:" <<endl;
        auto it = m_list[cnt].begin();
        auto ed = m_list[cnt].end();
        while (it!=ed)
        {
            FillStep * st = *it++;

            os<<(long int)(st);
            st->print(os);
        }
    }
}


