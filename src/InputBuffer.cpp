#include "InputBuffer.hpp"
#include <vector>
#include <stddef.h>

KBBuffer* KBBuffer::buff = nullptr;
std::vector<TCOD_key_t> KBBuffer::keys = std::vector<TCOD_key_t>();


KBBuffer* KBBuffer::getInstance(){
  if(buff==nullptr){
    buff = new KBBuffer;
  }
	return buff;
}
/*KBBuffer::~KBBuffer(){
  delete keys;
}*/
void KBBuffer::addKey(TCOD_key_t key){
  keys.push_back(key);
}
TCOD_key_t KBBuffer::nextKey(){
  if(keys.empty()){
    TCOD_key_t none;
    none.vk = TCODK_NONE;
    return none;
  }
  TCOD_key_t key = keys[0];
  keys.erase(keys.begin());
  return key;
}
