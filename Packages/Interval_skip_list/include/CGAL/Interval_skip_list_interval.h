// ======================================================================
//
// Copyright (c) 2003 GeometryFactory
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : 
// release_date  : 
//
// file          : include/CGAL/Interval_skip_list_interval.h
// package       : Interval_skip_list
// revision      : $Revision$
// revision_date : $Date$
// author(s)     : Andreas Fabri
//
// coordinator   : GeometryFactory (<Andreas.Fabri@geometryfactory.com>)
//
// ======================================================================

#ifndef CGAL_INTERVAL_SKIP_LIST_INTERVAL_H
#define CGAL_INTERVAL_SKIP_LIST_INTERVAL_H

#include <cassert>
#include <stdio.h>
#include <iostream>
#include <CGAL/Random.h>
#include <list>


namespace CGAL {

  template <class Value_>
  class Interval_skip_list_interval
  {
  public:
    typedef Value_ Value;

  private:
    char lbound_;  // '(' = non-strict left bound, '[' = strict left bound
    char rbound_; //  ')' = non-strict right bound, ']' = strict right bound
    Value inf_;
    Value sup_;  // left and right boundary values
  public:

    Interval_skip_list_interval(){}
    Interval_skip_list_interval(char lb, 
				const Value& inf_, 
				const Value& sup_, 
				char rb);
    const Value& inf() const {return inf_;}
    const Value& sup() const {return sup_;}
    char lbound() const {return lbound_;}
    char rbound() const {return rbound_;}
    bool contains(const Value& V) const;

    // true iff this contains (l,r)
    bool contains_interval(const Value& l, const Value& r) const;  

    bool operator==(const Interval_skip_list_interval& I) const 
    {
      return ( (inf() == I.inf()) && (sup() == I.sup()) && 
	       (lbound() == I.lbound()) && (rbound() == I.rbound()) );
    }

    bool operator!=(const Interval_skip_list_interval& I) const 
    {
      return ! (*this == I);
    }
  };



  template <class V>
  std::ostream& operator<<(std::ostream& os, 
			   const Interval_skip_list_interval<V>& i)
  {
    os << i.lbound() << i.inf() << ", " << i.sup() << i.rbound();
    return os;
  }


  template <class V>
  Interval_skip_list_interval<V>::Interval_skip_list_interval(char lb, 
							      const Value& i, 
							      const Value& s, 
							      char rb)
    : lbound_(lb), rbound_(rb), inf_(i), sup_(s)
  {
    if ( !( (lb=='(') || (lb=='[') ) ) {
      printf("Error:  bad inf_ bound.\n");
      exit(1);
    }
    if ( !( (rb==')')|| (rb==']')) ) {
      printf("Error:  bad sup_ bound.\n");
      exit(1);
    }
    if ( inf_ > sup_ )
      {
	std::cerr << "Error: " << *this << std::endl;
	exit(1);
      }
  }


  template <class V>
  bool
  Interval_skip_list_interval<V>::contains_interval(const Value& i, 
						    const Value& s) const
    // true iff this contains (l,r)
  {
    return( (inf() <= i) && (sup() >= s) );
  }


  template <class V>
  bool
  Interval_skip_list_interval<V>::contains(const Value& v) const
  {
    // return true if this contains V, false otherwise
    if((v > inf()) && (v < sup()))
      return true;
    else if ((v == inf()) && lbound() == '[')
      return true;
    else if ((v == sup()) && rbound() == ']')
      return true;
    else
      return false;
  }




} // namespace CGAL

#endif // CGAL_INTERVAL_SKIP_LIST_INTERVAL_H
