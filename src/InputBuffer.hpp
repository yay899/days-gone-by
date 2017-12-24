#ifndef KBBUFF
#define KBBUFF

#include "libtcod.hpp"
#include <vector>
#include <stddef.h>

//To use, call
//	KBBuffer::getInstance()->fun();

class KBBuffer{
public:
  static KBBuffer* getInstance();
  TCOD_key_t nextKey();
  void addKey(TCOD_key_t key);
private:
  static std::vector<TCOD_key_t> keys;
  KBBuffer(){
    //keys = std::vector<TCOD_key_t>();
  };
  KBBuffer(KBBuffer const&){
    //keys = std::vector<TCOD_key_t>();
  };
  KBBuffer& operator = (KBBuffer const&);
  static KBBuffer* buff;

};

#endif
