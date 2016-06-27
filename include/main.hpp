#ifndef __CLASIFICATION_OPENFILE_HPP__
#include <openfile.hpp>
#endif

#ifndef __CLASIFICATION_CLASSIFY_HPP__
#include <classify.hpp>
#endif

#ifndef __CLASIFICATION_RBT_HPP__
#include <rbt.hpp>
#endif

/*
#ifndef __CLASIFICATION_CHECK_HPP__
#include <check.hpp>
#endif

#ifndef __CLASIFICATION_MEASURE_HPP__
#include <measure.hpp>
#endif
*/

double Result::_construct_time_of_naive_dtree = 0;
double Result::_construct_time_of_dtree = 0;
double Result::_latency_of_simpleSearch = 0;
double Result::_latency_of_RBTDtreeSearch = 0;
double Result::_latency_of_RBTNDtreeSearch = 0;
long unsigned Dtree::_number_of_node_of_dtree = 0;
long unsigned MR::_counterForDIndex = 0;
long unsigned MR::_number_of_node_of_mr = 0;
long unsigned RBT::_number_of_node_of_rbt = 0;
vector<long unsigned>* MR::_maxDIndex = NULL;
double Result::_latency_of_sequential = 0;
unsigned Rule::_number_of_rule = 0;
