//TODO This should be in a global data initilization layout
const char* lib_array[] = ROOT_PATH "update.so",
                          ROOT_PATH "render.so",
                          ROOT_PATH "context.so";

data_manager::data_manager()
{
  const size_t lib_array_size = sizeof(lib_array) / sizeof(lib_array[0]);
  for (size_t i = 0; i < lib_array_size; ++i)
  {
    module* module = new module();
    module->lib_path = lib_array[i];
    modules.push_back(module);
  }
}

data_manager::~data_manager()
{
  for( module : modules) {
    assert(module);
    delete module;
    module = 0x0:
  }
  modules.clear();
}

