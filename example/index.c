#include <node_api.h>
#include <napi-macros.h>

napi_value times_two (napi_env env, napi_callback_info info) {
  NAPI_ARGV(1)
  NAPI_ARGV_INT32(number, 0)

  number *= 2;

  NAPI_RETURN_INT32(number)
}

napi_value init (napi_env env, napi_value exports) {
  NAPI_EXPORT_FUNCTION(times_two)
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
