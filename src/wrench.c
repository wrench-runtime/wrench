#include <assert.h>

#include <wren.h>
#include <wren_runtime.h>

#include "readfile.h"
#include "argparse.h"

#define REGISTER_PLUGIN(NAME) WrenForeignMethodFn wrt_plugin_init_##NAME(int handle); wrt_register_plugin(#NAME,wrt_plugin_init_##NAME)

static const char *const usage[] = {
    "wrench [script] [[--] args]",
    "wrench [script]",
    NULL,
};

int main(int argc, const char *argv[])
{  

  char* modulePath = NULL;

  struct argparse_option options[] = {
      OPT_HELP(),
      OPT_STRING('m', "modules", &modulePath, "module path to use"),
      OPT_END(),
  };

  struct argparse argparse;
  argparse_init(&argparse, options, usage, 0);
  argparse_describe(&argparse, "\nA brief description of what the program does and how it works.", "\nAdditional description of the program after the description of the arguments.");
  argc = argparse_parse(&argparse, argc, argv);


  if(modulePath == NULL) modulePath = "./wren_modules";

  printf("Module Path: %s \n", modulePath);
  wrt_init(modulePath);
  WrenVM* vm = wrt_new_wren_vm(true); 
  
  #include "static_plugins.in"

  char* script;
  if(argc < 1){
    argparse_help_cb(&argparse, options);
  }
  else {
    wrt_run_main(vm, argv[0]);
  }

  return 0;
}
