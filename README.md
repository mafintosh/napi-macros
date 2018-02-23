# napi-macros

Set of utility macros to make writing [N-API](https://nodejs.org/dist/latest-v9.x/docs/api/n-api.html) modules a little easier.

```
npm install napi-macros
```

Then add the following to your target in your binding.gyp file

```
"include_dirs": [
  "<!(node -e \"require('napi-macros')\")"
],
```

These patterns mostly reflect how I use N-API so far. Feel free
to PR more.

## Usage

``` c
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
```

Full working example can be found in the [example/](https://github.com/mafintosh/napi-macros/tree/master/example) folder.

## API

#### `NAPI_ARGV(n)`

Setup up argv boilerplate. `n` is how many arguments you are expecting.
Expects the `napi_env` to be in scope as `env` and the `napi_callback_info` to be in scope as `info`.

#### `NAPI_ARGV_BUFFER(name, index)`

Get a buffer out of the arguments at the corresponding index.
Sets `char *name` and `size_t name_len` with the buffer and buffer length.

#### `NAPI_ARGV_BUFFER_CAST(type, name, index)`

Get a buffer out and cast the pointer to the specified type.
Note that the type should include the pointer star, i.e.

``` c
NAPI_ARGV_BUFFER_CAST(uv_udp_t *, handle, 0)
```

Will cast the 1st argument as `uv_udp_t` pointer.

#### `NAPI_ARGV_UINT32(name, index)`

Get an argument as a uint32.
Will throw if argument is not the right type.

#### `NAPI_ARGV_INT32(name, index)`

Get an argument as an int32.
Will throw if argument is not the right type.

#### `NAPI_ARGV_UTF8(name, length, index)`

Get an argument as a utf8 string.

`name` will be a `char[length]` array.

Will throw if argument is not the right type.

#### `NAPI_EXPORT_FUNCTION(fn)`

Will export a function in the Init method. Expects the env and `exports` to be in scope.
The name of the exported function is the same name as the c function.

#### `NAPI_EXPORT_SIZEOF(struct)`

Export the size of a strict. The exported name is `sizeof_{struct-name}`.

#### `NAPI_EXPORT_UINT32(name)`

Export a uint32.
The name of the exported number is the same name as the c variable.

#### `NAPI_EXPORT_INT32(name)`

Export an int32.
The name of the exported number is the same name as the c variable.

#### `NAPI_EXPORT_UTF8(name, len)`

Export a utf8 string. `len` should be the length of the string.
The name of the exported string is the same name as the c variable.

#### `NAPI_EXPORT_STRING(name)`

Export a null terminated string.
The name of the exported string is the same name as the c variable.

#### `NAPI_RETURN_UINT32(name)`

Returns a uint32.

#### `NAPI_RETURN_INT32(name)`

Returns an int32.

#### `NAPI_RETURN_UTF8(name, len)`

Return a utf8 string. `len` should be the length of the string.

#### `NAPI_RETURN_STRING(name)`

Return a null terminated string.

#### `NAPI_UV_THROWS(err, fn)`

Checks if a libuv call fails and if so, throws an error.

``` c
int err;
NAPI_UV_THROWS(err, uv_ip4_addr((char *) &ip, port, &addr))
```

## License

MIT