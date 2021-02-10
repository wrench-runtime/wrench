#include <assert.h>

#include <wren.h>
#include <wren_runtime.h>

#include "readfile.h"

#define REGISTER_PLUGIN(NAME) WrenForeignMethodFn wrt_plugin_init_##NAME(int handle); wrt_register_plugin(#NAME,wrt_plugin_init_##NAME)

int main(int argc, char *argv[])
{  
  wrt_init();

  WrenVM* vm = wrt_new_wren_vm(true); 
  
  #include "static_plugins.in"

  char* script;
  if(argc < 2){
    script = read_file_string("main.wren");
  }
  else {
    script = read_file_string(argv[1]);
  }
  assert(script != NULL);
  WrenInterpretResult result = wrenInterpret(vm, "main", script);
  free(script);
  if(result == WREN_RESULT_SUCCESS){
    wrt_call_update_callbacks(vm);
  }
  return 0;
}
