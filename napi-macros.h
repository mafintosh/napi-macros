#ifndef NAPI_MACROS
#define NAPI_MACROS

#define NAPI_INIT() \
  static void napi_macros_init(napi_env env, napi_value exports); \
  napi_value napi_macros_init_wrap (napi_env env, napi_value exports) { \
    napi_macros_init(env, exports); \
    return exports; \
  } \
  NAPI_MODULE(NODE_GYP_MODULE_NAME, napi_macros_init_wrap) \
  static void napi_macros_init (napi_env env, napi_value exports)

#define NAPI_METHOD(name) \
  napi_value name (napi_env env, napi_callback_info info)

#define NAPI_UV_THROWS(err, fn) \
  err = fn; \
  if (err < 0) { \
    napi_throw_error(env, uv_err_name(err), uv_strerror(err)); \
    return NULL; \
  }

#define NAPI_EXPORT_SIZEOF(name) \
  napi_value name##_sizeof; \
  napi_create_uint32(env, sizeof(name), &name##_sizeof); \
  napi_set_named_property(env, exports, "sizeof_" #name, name##_sizeof);

#define NAPI_EXPORT_UINT32(name) \
  napi_value name##_uint32; \
  napi_create_uint32(env, name, &name##_uint32); \
  napi_set_named_property(env, exports, #name, name##_uint32);

#define NAPI_EXPORT_INT32(name) \
  napi_value name##_int32; \
  napi_create_uint32(env, name, &name##_int32); \
  napi_set_named_property(env, exports, #name, name##_int32);

#define NAPI_EXPORT_FUNCTION(name) \
  napi_value name##_fn; \
  napi_create_function(env, NULL, 0, name, NULL, &name##_fn); \
  napi_set_named_property(env, exports, #name, name##_fn);

#define NAPI_EXPORT_UTF8(name, len) \
  napi_value name##_utf8; \
  napi_create_string_utf8(env, name, len, &name##_utf8); \
  napi_set_named_property(env, exports, #name, name##_utf8);

#define NAPI_EXPORT_STRING(name) \
  NAPI_EXPORT_UTF8(name, NAPI_AUTO_LENGTH)

#define NAPI_RETURN_INT32(name) \
  napi_value return_int32; \
  napi_create_int32(env, name, &return_int32); \
  return return_int32;

#define NAPI_RETURN_UINT32(name) \
  napi_value return_uint32; \
  napi_create_uint32(env, name, &return_uint32); \
  return return_uint32;

#define NAPI_RETURN_UTF8(name, len) \
  napi_value return_utf8; \
  napi_create_string_utf8(env, name, len, &return_uint32); \
  return return_utf8;

#define NAPI_RETURN_STRING(name) \
  NAPI_RETURN_UTF8(name, NAPI_AUTO_LENGTH)

#define NAPI_ARGV(n) \
  napi_value argv[n]; \
  size_t argc = n; \
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

#define NAPI_ARGV_UTF8(name, size, i) \
  char name[size]; \
  size_t name##_len; \
  if (napi_get_value_string_utf8(env, argv[i], (char *) &name, size, &name##_len) != napi_ok) { \
    napi_throw_error(env, "EINVAL", "Expected string"); \
    return NULL; \
  }

#define NAPI_ARGV_UINT32(name, i) \
  uint32_t name; \
  if (napi_get_value_uint32(env, argv[i], &name) != napi_ok) { \
    napi_throw_error(env, "EINVAL", "Expected unsigned number"); \
    return NULL; \
  }

#define NAPI_ARGV_INT32(name, i) \
  int32_t name; \
  if (napi_get_value_int32(env, argv[i], &name) != napi_ok) { \
    napi_throw_error(env, "EINVAL", "Expected number"); \
    return NULL; \
  }

#define NAPI_ARGV_BUFFER_CAST(type, name, i) \
  type name; \
  size_t name##_len; \
  napi_get_buffer_info(env, argv[i], (void **) &name, &name##_len);

#define NAPI_ARGV_BUFFER(name, i) \
  NAPI_ARGV_BUFFER_CAST(char *, name, i)

#endif
