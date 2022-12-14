#ifndef YSHR_TFHEPP_UTIL_HPP
#define YSHR_TFHEPP_UTIL_HPP

#include <fstream>
#include <graph.hpp>
#include <tfhe++.hpp>

using SecretKey = TFHEpp::SecretKey;
using Lvl1 = TFHEpp::lvl1param;
using TRGSWLvl1FFT = TFHEpp::TRGSWFFT<Lvl1>;
using TLWELvl1 = TFHEpp::TLWE<Lvl1>;
using GateKey = TFHEpp::GateKey;
using CircuitKey = TFHEpp::CircuitKey<TFHEpp::lvl02param, TFHEpp::lvl21param>;
using TRLWELvl1 = TFHEpp::TRLWE<Lvl1>;

struct BKey {
  std::shared_ptr<GateKey> gkey;
  std::shared_ptr<TFHEpp::TLWE2TRLWEIKSKey<TFHEpp::lvl11param>>
      tlwel1_trlwel1_ikskey;
  std::shared_ptr<CircuitKey> circuit_key;

  BKey() {}

  BKey(const SecretKey &skey)
      : gkey(std::make_shared<GateKey>(skey)),
        tlwel1_trlwel1_ikskey(
            std::make_shared<TFHEpp::TLWE2TRLWEIKSKey<TFHEpp::lvl11param>>()),
        circuit_key(std::make_shared<CircuitKey>(skey)) {
    TFHEpp::tlwe2trlweikskkgen<TFHEpp::lvl11param>(*tlwel1_trlwel1_ikskey,
                                                   skey);
  }
};

TRGSWLvl1FFT encrypt_to_TRGSWLvl1FFT(Sigma s, const SecretKey &skey) {
  return TFHEpp::trgswfftSymEncrypt<Lvl1>({s == Sigma::ZERO ? false : true},
                                          Lvl1::α, skey.key.lvl1);
}

TRLWELvl1 trivial_TRLWELvl1(int num) {
  TRLWELvl1 ret = {};
  if (num == 0) {
    return ret;
  }
  int remainder = 0;
  int quotient = num;
  for (int i = 0; i < 10; i++) {
    if (quotient <= 0) {
      break;
    }
    remainder = quotient % 2;
    quotient = quotient / 2;

    if (remainder != 0) {
      ret[1][i] = (1u << 31); // 1/2
    }
  }
  return ret;
}

bool decrypt_TLWELvl1_to_bool(const TLWELvl1 &c, const SecretKey &skey) {
  // Use {0, 1/2} as message space
  uint32_t phase = c[Lvl1::n];
  for (size_t i = 0; i < Lvl1::n; i++)
    phase -= c[i] * skey.key.lvl1[i];
  return (phase + (1u << 30 /* 1/4 */)) > (1u << 31 /* 1/2 */);
}

#endif