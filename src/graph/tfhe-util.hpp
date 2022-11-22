#ifndef YSHR_TFHEPP_UTIL_HPP
#define YSHR_TFHEPP_UTIL_HPP

#include <fstream>
#include <tfhe++.hpp>

using SecretKey = TFHEpp::SecretKey;

SecretKey get_skey() { return TFHEpp::SecretKey(); }

#endif